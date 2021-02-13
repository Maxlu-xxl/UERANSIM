//
// This file is a part of UERANSIM open source project.
// Copyright (c) 2021 ALİ GÜNGÖR.
//
// The software and all associated files are licensed under GPL-3.0
// and subject to the terms and conditions defined in LICENSE file.
//

#pragma once

#include <string>
#include <udp/server.hpp>
#include <utility>
#include <utils/constants.hpp>
#include <utils/network.hpp>
#include <vector>

namespace app
{

struct CliMessage
{
    enum class Type
    {
        EMPTY = 0,
        ECHO,
        ERROR,
        RESULT,
        COMMAND
    } type{};

    std::string nodeName{};
    std::string value{};
    InetAddress clientAddr{};

    static CliMessage Error(InetAddress addr, std::string msg, std::string node = "")
    {
        CliMessage m{};
        m.type = Type::ERROR;
        m.value = std::move(msg);
        m.nodeName = std::move(node);
        m.clientAddr = addr;
        return m;
    }

    static CliMessage Result(InetAddress addr, std::string msg, std::string node = "")
    {
        CliMessage m{};
        m.type = Type::RESULT;
        m.value = std::move(msg);
        m.nodeName = std::move(node);
        m.clientAddr = addr;
        return m;
    }

    static CliMessage Echo(InetAddress addr, std::string msg)
    {
        CliMessage m{};
        m.type = Type::ECHO;
        m.value = std::move(msg);
        m.nodeName = "";
        m.clientAddr = addr;
        return m;
    }

    static CliMessage Command(InetAddress addr, std::string msg, std::string node = "")
    {
        CliMessage m{};
        m.type = Type::COMMAND;
        m.value = std::move(msg);
        m.nodeName = std::move(node);
        m.clientAddr = addr;
        return m;
    }
};

class CliServer
{
  private:
    Socket m_socket;

  public:
    explicit CliServer() : m_socket{Socket::CreateAndBindUdp({cons::CMD_SERVER_IP, 0})}
    {
    }

    ~CliServer()
    {
        m_socket.close();
    }

    [[nodiscard]] InetAddress assignedAddress() const;

    CliMessage receiveMessage();
    void sendMessage(const CliMessage &msg);
};

} // namespace app