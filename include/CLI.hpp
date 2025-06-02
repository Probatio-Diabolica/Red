#ifndef CLI_HPP
#define CLI_HPP


#include<string>

#include"Client.hpp"
#include"CommandHandler.hpp"

class CLI
{
public:
    CLI(const std::string& host,int port);

    // Runs the interactive Redis CLI loop, handling user input and sending commands to the server.
    void run();

private:
    Client m_redisClient;
};

#endif
