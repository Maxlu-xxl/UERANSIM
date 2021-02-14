//
// This file is a part of UERANSIM open source project.
// Copyright (c) 2021 ALİ GÜNGÖR.
//
// The software and all associated files are licensed under GPL-3.0
// and subject to the terms and conditions defined in LICENSE file.
//

#include "cmd_handler.hpp"

#include <ue/app/task.hpp>
#include <ue/mr/task.hpp>
#include <ue/nas/task.hpp>
#include <ue/rrc/task.hpp>
#include <ue/tun/task.hpp>
#include <utils/common.hpp>
#include <utils/printer.hpp>

#define PAUSE_CONFIRM_TIMEOUT 3000
#define PAUSE_POLLING 10

namespace nr::ue
{

void UeCmdHandler::PauseTasks(TaskBase &base)
{
    base.mrTask->requestPause();
    base.nasTask->requestPause();
    base.rrcTask->requestPause();
}

void UeCmdHandler::UnpauseTasks(TaskBase &base)
{
    base.mrTask->requestUnpause();
    base.nasTask->requestUnpause();
    base.rrcTask->requestUnpause();
}

bool UeCmdHandler::IsAllPaused(TaskBase &base)
{
    if (!base.mrTask->isPauseConfirmed())
        return false;
    if (!base.nasTask->isPauseConfirmed())
        return false;
    if (!base.rrcTask->isPauseConfirmed())
        return false;
    return true;
}

void UeCmdHandler::HandleCmd(TaskBase &base, NwUeCliCommand &msg)
{
    PauseTasks(base);

    uint64_t currentTime = utils::CurrentTimeMillis();
    uint64_t endTime = currentTime + PAUSE_CONFIRM_TIMEOUT;

    bool isPaused = false;
    while (currentTime < endTime)
    {
        currentTime = utils::CurrentTimeMillis();
        if (IsAllPaused(base))
        {
            isPaused = true;
            break;
        }
        utils::Sleep(PAUSE_POLLING);
    }

    if (!isPaused)
    {
        msg.sendError("UE is unable process command due to pausing timeout");
    }
    else
    {
        HandleCmdImpl(base, msg);
    }

    UnpauseTasks(base);
}

void UeCmdHandler::HandleCmdImpl(TaskBase &base, NwUeCliCommand &msg)
{
    switch (msg.cmd->present)
    {
    case app::UeCliCommand::STATUS: {
        Printer printer{};
        printer.appendKeyValue({
            {"cm-state", nr::ue::CmStateName(base.nasTask->mm->m_cmState)},
            {"rm-state", nr::ue::RmStateName(base.nasTask->mm->m_rmState)},
            {"mm-state", nr::ue::MmSubStateName(base.nasTask->mm->m_mmSubState)},
            {"sim-inserted", base.nasTask->mm->m_validSim ? "true" : "false"},
        });
        printer.trim();
        msg.sendResult(printer.makeString());
        break;
    }
    case app::UeCliCommand::INFO: {
        Printer printer{};
        printer.appendKeyValue({
            {"supi", base.config->supi.has_value() ? base.config->supi->toString() : ""},
            {"plmn", base.config->plmn.toString()},
            {"imei", base.config->imei.has_value() ? *base.config->imei : ""},
            {"imeisv", base.config->imeiSv.has_value() ? *base.config->imeiSv : ""},
        });
        printer.trim();
        msg.sendResult(printer.makeString());
        break;
    }
    }
}

} // namespace nr::ue