#include "inc/common.h"

#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <iostream>

#include <thread>

int main()
{
    struct sockaddr_in addr;

    int sock = socket(AF_INET, SOCK_STREAM, 0);
    addr.sin_family = AF_INET ;
    addr.sin_port = htons(PORT);
    addr.sin_addr.s_addr = inet_addr(ADDRESS.c_str());

    if(bind(sock, (sockaddr*)&addr, sizeof(addr)) == -1)
    {
        return -1;
    }

    if(listen(sock, 10) == -1)
    {
        return -2;
    }

    sockaddr_in sadr;
    unsigned int addr_size = sizeof(sockaddr_in);

    auto fd = accept(sock, (sockaddr*)&sadr, &addr_size);

    char buff[1024];
    int bytecount;
    bool connected {false};
    std::string user = "Unknown";
    while (true)
    {
        bytecount = recv(fd, buff, sizeof(buff), 0);
        if (bytecount <= 0)
        {
            break;
        }


        PbMessage payload;
        payload.ParseFromArray(buff, bytecount);

        auto res = genMessage(PbMessage::ACK, user);
        if (!connected)
        {
            if (payload.type() != PbMessage::USER)
            {
                std::cout << "Received data from unknown client!" << std::endl;
                res.set_type(PbMessage::NACK);
            }
            else
            {
                connected = true;
                user = payload.msg();
                res.set_msg(user);
                std::cout << "Hello " << user << std::endl;
            }
        }
        else
        {
            if (payload.type() == PbMessage::END)
            {
                std::cout << "Bye " << user << std::endl;
                user = "Unknown";
                connected = false;
            }
            else
            {
                std::cout << "Received <" << payload.msg() << "> from " << user << std::endl;
            }
        }

        std::vector<char> pkt(res.ByteSizeLong());
        res.SerializeToArray(pkt.data(), pkt.size());
        send(fd, pkt.data(), pkt.size(), MSG_NOSIGNAL);
    }

    std::cout << "Client disconected!" << std::endl;

    close(fd);
    close(sock);
}
