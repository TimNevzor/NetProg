//daytime.cpp
#include <iostream>
#include <arpa/inet.h> //inet_addr() htons()
#include <unistd.h> //socket(), sendto() recvfrom()
using namespace std;
int main()
{
    char msg[] = "Good morning, mr sir\n"; //сообщение, к-ое отправится пользователю
    struct sockaddr_in addr; //настройка структуры
    addr.sin_family = AF_INET;
    addr.sin_port = htons(3306);
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    int s = socket(AF_INET, SOCK_DGRAM, 0); //создание сокета UDP
    if (s == -1) {
        cerr << "Error creating socket" << endl;
        return 1;
    }//отправляет сообщение
    ssize_t sent_bytes = sendto(s, msg, sizeof(msg), 0, (const struct sockaddr*)&addr, sizeof(addr));
    if (sent_bytes == -1) {
        cerr << "Error sending data" << endl;
        close(s); 
        return 1;
    }
    cout << "We send: " << msg; //выводит сообщение
    char buf[256]; //получает ответ от сервера
    socklen_t addr_len = sizeof(addr);
    ssize_t recv_len = recvfrom(s, buf, sizeof(buf), 0, (struct sockaddr*)&addr, &addr_len);
    if (recv_len == -1) {
        cerr << "Error receiving data" << endl;
        close(s);
        return 1;
    }
    buf[recv_len] = '\0';
    cout << "We receive: " << buf; //выводит ответ
    close(s); //закрывает сокет
    return 0;
}
