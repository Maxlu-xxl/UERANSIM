#include "ctl_layer.hpp"

static constexpr const size_t MAX_PDU_COUNT = 128;
static constexpr const int MAX_PDU_TTL = 3000;

namespace nr::ue
{

RlsCtlLayer::RlsCtlLayer(TaskBase *base, RlsSharedContext *shCtx)
    : m_shCtx{shCtx}, m_servingCell{}, m_mainTask{}, m_udpTask{}, m_pduMap{}, m_pendingAck{}
{
    m_logger = base->logBase->makeUniqueLogger(base->config->getLoggerPrefix() + "rls-ctl");
}

void RlsCtlLayer::onStart(NtsTask* mainTask, RlsUdpTask* udpTask)
{
    m_mainTask = mainTask;
    m_udpTask = udpTask;
}

void RlsCtlLayer::onQuit()
{
}

void RlsCtlLayer::handleRlsMessage(int cellId, rls::RlsMessage &msg)
{
    if (msg.msgType == rls::EMessageType::PDU_TRANSMISSION_ACK)
    {
        auto &m = (rls::RlsPduTransmissionAck &)msg;
        for (auto pduId : m.pduIds)
            m_pduMap.erase(pduId);
    }
    else if (msg.msgType == rls::EMessageType::PDU_TRANSMISSION)
    {
        auto &m = (rls::RlsPduTransmission &)msg;
        if (m.pduId != 0)
            m_pendingAck[cellId].push_back(m.pduId);

        if (m.pduType == rls::EPduType::DATA)
        {
            if (cellId != m_servingCell)
            {
                // NOTE: Data packet may be received from a cell other than serving cell
                //  Ignore the packet if this is the case. Other cell can only send RRC, but not DATA
                return;
            }

            auto w = std::make_unique<NmUeRlsToRls>(NmUeRlsToRls::DOWNLINK_DATA);
            w->psi = static_cast<int>(m.payload);
            w->data = std::move(m.pdu);
            m_mainTask->push(std::move(w));
        }
        else if (m.pduType == rls::EPduType::RRC)
        {
            auto w = std::make_unique<NmUeRlsToRls>(NmUeRlsToRls::DOWNLINK_RRC);
            w->cellId = cellId;
            w->rrcChannel = static_cast<rrc::RrcChannel>(m.payload);
            w->data = std::move(m.pdu);
            m_mainTask->push(std::move(w));
        }
        else
        {
            m_logger->err("Unhandled RLS PDU type");
        }
    }
    else
    {
        m_logger->err("Unhandled RLS message type");
    }
}

void RlsCtlLayer::handleSignalChange(int cellId, int dbm)
{
    auto w = std::make_unique<NmUeRlsToRls>(NmUeRlsToRls::SIGNAL_CHANGED);
    w->cellId = cellId;
    w->dbm = dbm;
    m_mainTask->push(std::move(w));
}

void RlsCtlLayer::handleUplinkRrcDelivery(int cellId, uint32_t pduId, rrc::RrcChannel channel, OctetString &&data)
{
    if (pduId != 0)
    {
        if (m_pduMap.count(pduId))
        {
            m_pduMap.clear();

            auto w = std::make_unique<NmUeRlsToRls>(NmUeRlsToRls::RADIO_LINK_FAILURE);
            w->rlfCause = rls::ERlfCause::PDU_ID_EXISTS;
            m_mainTask->push(std::move(w));
            return;
        }

        if (m_pduMap.size() > MAX_PDU_COUNT)
        {
            m_pduMap.clear();

            auto w = std::make_unique<NmUeRlsToRls>(NmUeRlsToRls::RADIO_LINK_FAILURE);
            w->rlfCause = rls::ERlfCause::PDU_ID_FULL;
            m_mainTask->push(std::move(w));
            return;
        }

        m_pduMap[pduId].endPointId = cellId;
        m_pduMap[pduId].id = pduId;
        m_pduMap[pduId].pdu = data.copy();
        m_pduMap[pduId].rrcChannel = channel;
        m_pduMap[pduId].sentTime = utils::CurrentTimeMillis();
    }

    rls::RlsPduTransmission msg{m_shCtx->sti};
    msg.pduType = rls::EPduType::RRC;
    msg.pdu = std::move(data);
    msg.payload = static_cast<uint32_t>(channel);
    msg.pduId = pduId;

    m_udpTask->send(cellId, msg);
}

void RlsCtlLayer::handleUplinkDataDelivery(int psi, OctetString &&data)
{
    rls::RlsPduTransmission msg{m_shCtx->sti};
    msg.pduType = rls::EPduType::DATA;
    msg.pdu = std::move(data);
    msg.payload = static_cast<uint32_t>(psi);
    msg.pduId = 0;

    m_udpTask->send(m_servingCell, msg);
}

void RlsCtlLayer::onAckControlTimerExpired()
{
    int64_t current = utils::CurrentTimeMillis();

    std::vector<uint32_t> transmissionFailureIds;
    std::vector<rls::PduInfo> transmissionFailures;

    for (auto &pdu : m_pduMap)
    {
        auto delta = current - pdu.second.sentTime;
        if (delta > MAX_PDU_TTL)
        {
            transmissionFailureIds.push_back(pdu.first);
            transmissionFailures.push_back(std::move(pdu.second));
        }
    }

    for (auto id : transmissionFailureIds)
        m_pduMap.erase(id);

    if (!transmissionFailures.empty())
    {
        auto w = std::make_unique<NmUeRlsToRls>(NmUeRlsToRls::TRANSMISSION_FAILURE);
        w->pduList = std::move(transmissionFailures);
        m_mainTask->push(std::move(w));
    }
}

void RlsCtlLayer::onAckSendTimerExpired()
{
    auto copy = m_pendingAck;
    m_pendingAck.clear();

    for (auto &item : copy)
    {
        if (!item.second.empty())
            continue;

        rls::RlsPduTransmissionAck msg{m_shCtx->sti};
        msg.pduIds = std::move(item.second);

        m_udpTask->send(item.first, msg);
    }
}

void RlsCtlLayer::handleSapMessage(NmUeRlsToRls &msg)
{
    switch (msg.present)
    {
    case NmUeRlsToRls::SIGNAL_CHANGED:
        handleSignalChange(msg.cellId, msg.dbm);
        break;
    case NmUeRlsToRls::RECEIVE_RLS_MESSAGE:
        handleRlsMessage(msg.cellId, *msg.msg);
        break;
    case NmUeRlsToRls::UPLINK_DATA:
        handleUplinkDataDelivery(msg.psi, std::move(msg.data));
        break;
    case NmUeRlsToRls::UPLINK_RRC:
        handleUplinkRrcDelivery(msg.cellId, msg.pduId, msg.rrcChannel, std::move(msg.data));
        break;
    case NmUeRlsToRls::ASSIGN_CURRENT_CELL:
        m_servingCell = msg.cellId;
        break;
    default:
        m_logger->unhandledNts(msg);
        break;
    }
}

} // namespace nr::ue