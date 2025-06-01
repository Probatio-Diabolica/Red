#ifndef CLIENT_HPP
#define CLIENT_HPP


#include <string>
#include <iostream>
#include <netdb.h>
#include <sys/socket.h>
#include <unistd.h>
#include <cstring>

class Client
{
public:
    Client(const std::string& host,int port);
    ~Client();

    [[__nodiscard__]] bool connectToServer();
    void kill();

private:
    std::string m_host;
    int m_port;
    int m_sockfd;
};

#endif
