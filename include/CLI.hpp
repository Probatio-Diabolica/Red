#ifndef CLI_HPP
#define CLI_HPP


#include<string>

#include"Client.hpp"


class CLI
{
public:
    CLI(const std::string& host,int port);
    void run();

private:
    Client m_redisClient;
};

#endif
