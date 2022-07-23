#include "inc/common.h"

#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#include <thread>


std::atomic<bool> read_thread_running {false};
void readThread(int fd)
{
    read_thread_running = true;
    while(read_thread_running)
    {
        char buff[1024];
        int bytecount;
        bytecount = recv(fd, buff, sizeof(buff), MSG_DONTWAIT);
        if (bytecount <= 0)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
            continue;
        }
        PbMessage payload;
        payload.ParseFromArray(buff, bytecount);
        std::cout << "Type "
                  << payload.type()
                  << ", message "
                  << payload.msg()
                  << std::endl;
    }
}

int main()
{
    struct sockaddr_in addr;

    int sock = socket(AF_INET, SOCK_STREAM, 0);
    addr.sin_family = AF_INET ;
    addr.sin_port = htons(PORT);
    addr.sin_addr.s_addr = inet_addr(ADDRESS.c_str());

    int fd = connect(sock, (sockaddr*)&addr, sizeof(addr));
    if(fd == -1)
    {
        return -1;
    }

    std::thread t(readThread, sock);

    auto msg = genMessage(PbMessage::COMMAND, "Hello");
    std::vector<char> pkt(msg.ByteSizeLong());
    msg.SerializeToArray(pkt.data(), pkt.size());
    auto ret = send(sock, pkt.data(), pkt.size(), 0);
    if (ret < 0) return -1;
    std::this_thread::sleep_for(std::chrono::seconds(1));

    msg = genMessage(PbMessage::USER, "Adam");
    pkt.resize(msg.ByteSizeLong());
    msg.SerializeToArray(pkt.data(), pkt.size());
    ret = send(sock, pkt.data(), pkt.size(), 0);
    if (ret < 0) return -1;
    std::this_thread::sleep_for(std::chrono::seconds(1));

    msg = genMessage(PbMessage::COMMAND, "Hello");
    pkt.resize(msg.ByteSizeLong());
    msg.SerializeToArray(pkt.data(), pkt.size());
    ret = send(sock, pkt.data(), pkt.size(), 0);
    if (ret < 0) return -1;
    std::this_thread::sleep_for(std::chrono::seconds(1));

    msg = genMessage(PbMessage::END, "");
    pkt.resize(msg.ByteSizeLong());
    msg.SerializeToArray(pkt.data(), pkt.size());
    ret = send(sock, pkt.data(), pkt.size(), 0);
    if (ret < 0) return -1;
    std::this_thread::sleep_for(std::chrono::seconds(1));

    read_thread_running = false;
    t.join();

    close(fd);
}
