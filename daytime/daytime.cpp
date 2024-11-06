#include <iostream>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <iomanip>

void errHandler(const char* why, const int exitCode = 1)
{   std::cerr<< why << std::endl;
    exit(exitCode);
}

int main(int argc, char** argv)
{
    sockaddr_in * selfAddr = new (sockaddr_in);
    selfAddr->sin_family = AF_INET; // интернет протокол IPv4
    selfAddr->sin_port = 0;
    selfAddr->sin_addr.s_addr = 0;
    
    sockaddr_in * remoteAddr = new (sockaddr_in);
    remoteAddr->sin_family = AF_INET; // интернет протокол IPv4
    remoteAddr->sin_port = htons(13648);
    remoteAddr->sin_addr.s_addr = inet_addr("127.0.0.1");
    
    char* buf = new char[256];
    strcpy(buf,"Good morning, sir\n");
    int msgLen = strlen(buf);
    
    int s = socket(AF_INET, SOCK_STREAM, 0); // TCP
    if (s==-1)
        errHandler("Error open socket",11);
    
    int rc = bind(s,(const sockaddr*) selfAddr ,sizeof(sockaddr_in));
    if (rc==-1){
        close(s);
        errHandler("Error bind socket with local addres",12);
    }
    
    rc = connect(s, (const sockaddr*) remoteAddr, sizeof(sockaddr_in));
    if (rc == -1) {
        close(s);
        errHandler("Error connect socket with remote server", 13);
    } else {
    std::cout << "Connected to server successfully" << std::endl;
    }
    
    rc = send(s, buf, msgLen, 0);
    if (rc==-1){
        close(s);
        errHandler("Error send answer",14);
    }
    std::cout << "We send: " << buf << std::endl;
    
    rc = recv(s, buf, 256, 0);
    if (rc==-1){
        close(s);
        errHandler("Error receive answer",15);
    }
    buf[rc] = '\0';
    std::cout << "We receive: " << buf << std::endl;
    
    close(s);
    delete selfAddr;
    delete remoteAddr;
    delete[] buf;
    
    return 0;
}
