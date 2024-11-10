//server.cpp
#include <iostream>
#include <ctime>
#include <arpa/inet.h>
#include <unistd.h>
using namespace std;

int main()
{
    int s = socket(AF_INET, SOCK_DGRAM, 0); // создание сокета UDP
    if (s == -1) {
        cerr << "Error creating socket" << endl;
        return 1;
    }

    struct sockaddr_in server_addr; // настройка структуры
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(3306);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    if (bind(s, (struct sockaddr*) &server_addr, sizeof(server_addr)) == -1) {
        cerr << "Error binding socket" << endl;
        close(s);
        return 1;
    }

    while (true) {
        struct sockaddr_in client_addr;
        unsigned int addr_len = sizeof(client_addr);
        char buf[256];

        // получает сообщение от клиента
        ssize_t rc = recvfrom(s, buf, sizeof(buf), 0, (struct sockaddr*)&client_addr, &addr_len);
        if (rc == -1) {
            cerr << "Error receiving data" << endl;
            close(s);
            return 1;
        }

        buf[rc] = '\0'; //добавляет завершающий нулевой символ в конец buf
        cout << buf; // выводит полученное сообщение

        time_t current_time = time(0); // получает текущее время
        string datetime = ctime(&current_time); // преобразует время в строку

        // отправляет время
        ssize_t sent_bytes = sendto(s, datetime.c_str(), datetime.length(), 0, (struct sockaddr*)&client_addr, addr_len);
        if (sent_bytes == -1) {
            cerr << "Error sending data" << endl;
            close(s);
            return 1;
        }
    }

    close(s); // закрывает сокет
    return 0;
}
