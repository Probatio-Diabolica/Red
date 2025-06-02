#include "../include/Client.hpp"
#include <cstring>
#include <netdb.h>
#include <sys/socket.h>
#include <sys/types.h>

Client::Client(const std::string& host,int port)
    :m_host(host),m_port(port),m_sockfd(-1) {}


Client::~Client()
{
    kill();
}

//opens a TCP connection to the redis server 
bool Client::connectToServer()
{   
    struct addrinfo addrInfoHints, *addrInfoList = nullptr;
    
    std::memset(&addrInfoHints, 0 , sizeof(addrInfoHints));  //clean the hints structure
    
    addrInfoHints.ai_family = AF_UNSPEC;
 
    addrInfoHints.ai_socktype = SOCK_STREAM; 

    std::string portStr = std::to_string(m_port);
    
    //DNS resolution and a valid struc generation on addInfoHints
    int err = getaddrinfo(m_host.c_str(),portStr.c_str(),&addrInfoHints,&addrInfoList);
    
    //catch the failure for resolving the DNS
    if(err!=0)
    {
        std::cerr << "Failed to resolve address for host '" << m_host << "' on port " << m_port << ": " << gai_strerror(err) << "\n";
        return 0;
    }

    for(auto addr = addrInfoList;addr != nullptr ; addr  = addr->ai_next)
    {
        m_sockfd = socket(addr->ai_family, addr->ai_socktype, addr->ai_protocol);
        
        if(m_sockfd == -1) continue;
        
        if(connect(m_sockfd,addr->ai_addr,addr->ai_addrlen)==0) break; //we got our connection established

        close(m_sockfd); 

        m_sockfd = -1;
    }

    freeaddrinfo(addrInfoList);

    if(m_sockfd == -1)
    {
        std::cerr<< "Host unreachable...\n";
        return false;
    }

    return true;   
}

//graceful shutdown of the connection
void Client::kill()
{
    if(m_sockfd != -1)
    {
        close(m_sockfd);
        m_sockfd = -1;
    }
}

int Client::getSockfd() const
{
    return m_sockfd;
}

bool Client::sendRESP(const std::string& command)
{
    if(m_sockfd == -1) return false;
    ssize_t sent = send(m_sockfd, command.c_str(), command.size(), 0);
    return (sent == (ssize_t)command.size());
}
