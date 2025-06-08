#ifndef CLI_HPP
#define CLI_HPP


#include<string>

#include "Client.hpp"
#include "CommandHandler.hpp"
#include "ServerResponseParser.hpp"
class CLI
{
public:
    CLI(const std::string& host,int port);

    // Runs the interactive Redis CLI loop, handling user input and sending commands to the server.
    void run(const std::vector<std::string>& commandTokens);

    // Sends a command to the Redis server in RESP format, reads the response, and prints it to stdout.
    void queryRedis(const std::vector<std::string>& commandTokens);


private:
    std::string m_host;
    int m_port;
   Client m_redisClient;
};

#endif
