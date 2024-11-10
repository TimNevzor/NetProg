
#include <iostream>
#include <cstring>
#include <arpa/inet.h>
#include <unistd.h>
using namespace std;
int main()
{
	char msg[] = "Good morning, mr sir\n";
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(3306);
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    int s = socket(AF_INET, SOCK_DGRAM, 0);
    if (s == -1)
    {
        cerr << "Error creating socket" << endl;
        return 1;
    }
    ssize_t sent_bytes = sendto(s, msg, sizeof(msg), 0, (const struct sockaddr*)&addr, sizeof(addr));
    if (sent_bytes == -1)
    {
        cerr << "Error sending data" << endl;
        close(s);
        return 1;
    }
    cout << "We send: " << msg;
    char buf[256];
    socklen_t addr_len = sizeof(addr);
    ssize_t recv_len = recvfrom(s, buf, sizeof(buf), 0, (struct sockaddr*)&addr, &addr_len);
    if (recv_len == -1)
    {
        cerr << "Error receiving data" << endl;
        close(s);
        return 1;
    }
    buf[recv_len] = '\0';
    cout << "We receive: " << buf;
    close(s);
    return 0;
}
