/*
* NEWorld: A free game with similar rules to Minecraft.
* Copyright (C) 2016 NEWorld Team
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef SESSION_H__
#define SESSION_H__
#include <boost/core/noncopyable.hpp>
#include <queue>
#include "network.h"

class Session : public std::enable_shared_from_this<Session>
{
public:
    Session(tcp::socket socket)
        : m_socket(std::move(socket))
    {
    }

    void start()
    {
        doRead();
        doUpdate();
    }

private:
    void doUpdate();
    void doRead();
    void doWrite();
    void addRequest(Packet packet)
    {
        m_packets.push(packet);
    }

    tcp::socket m_socket;
    std::queue<Packet> m_packets; //packets need sent
    Packet m_packetRead;
    char* m_dataBuffer;
};

#endif // SESSION_H__