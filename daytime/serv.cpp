#include <arpa/inet.h>
#include <csignal>
#include <ctime>
#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
int main()
{
    int s = socket(AF_INET, SOCK_DGRAM, 0); //создание сокета IPv4 UDP
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(3306);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    bind(s, (struct sockaddr*) &server_addr, sizeof(server_addr));

    while(true)
    {
        struct sockaddr_in client_addr;
        unsigned int addr_len = sizeof(client_addr);
        char buf[256];
        unsigned int rc = recvfrom(s, buf, sizeof(buf), 0, (struct sockaddr*)&client_addr, &addr_len);
        buf[rc] = '\0';
        std::cout << buf;
        time_t current_time = time(0);
        std::string datetime = ctime(&current_time); //принимает указатель типа time_t
        unsigned int sent_bytes = sendto(s, datetime.c_str(), datetime.length(), 0, (struct sockaddr*)&client_addr, addr_len);
    }
    close(s);
    return 0;
}
