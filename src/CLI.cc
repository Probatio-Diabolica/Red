#include "../include/CLI.hpp"
#include <string>
#include <ostream>
#include <vector>

/////////////////////////////////////////////////////////////////
//static functions only

static std::string trimWhitespaces(const std::string& str)
{
    const auto begin = str.find_first_not_of(" \t\n\r\f\v");
    if (begin == std::string::npos)
        return "";

    const auto end = str.find_last_not_of(" \t\n\r\f\v");
    return str.substr(begin, end - begin + 1);
}


static void displayHelp()
{
    std::cout << R"(red v1.0.0 - A lightweight CLI for Violet

Usage:
  Run with host and port:
    ./red -h <host> -p <port>

  Use default host (127.0.0.1):
    ./red -p <port>

  Use default port (6379):
    ./red -h <host>

  One-shot command execution:
    ./red <command> [arguments...]

  Interactive mode (REPL):
    ./red
    → Type commands directly like SET, GET, etc.

Built-in CLI commands:
  help      Show this help message
  quit      Exit the CLI

Examples:
  ./red status
  ./red SET mykey "Hello, World!"
  ./red GET mykey

Preferences (optional ~/.redrc):
  :set hints      Enable inline command hints
  :set nohints    Disable hints

)" << '\n';
}
//////////////////////////////////////////////////////////////////

CLI::CLI(const std::string& host,int port)
    :m_host(host),m_port(port),m_redisClient(host,port)
{
        
}


void CLI::run(const std::vector<std::string>& commandTokens)
{
    if(!m_redisClient.connectToServer()) return;

    if(!commandTokens.empty())
    {
        queryRedis(commandTokens);
        return ;
    }

    std::cout << "Connected to server at " << m_port << '\n';

    while(true)
    {
        std::cout<< m_host << '@' << m_port << "> " << std::flush;

        std::string line;

        if(!std::getline(std::cin, line)) break;


        
        line = trimWhitespaces(line);

        if(line == "quit" or  line == "exit")
        {
            std::cout<< "Goodbye\n";
            break;
        }

        if(line == "help")
        {
            displayHelp();
            continue;
        }

        const auto tokens = CommandHandler::splitArgs(line);

        if(tokens.empty()) continue;

        const std::string respCommand = CommandHandler::toRESP(tokens);
        if(!m_redisClient.sendRESP(respCommand))
        {
            std::cerr << "Error :: failed to send command. \n";
            break;
        }

        const  std::string reply = ServerResponseParser::parseRESPReply(m_redisClient.getSockfd());
        std::cout<< reply  << '\n';

    }
}

void CLI::queryRedis(const std::vector<std::string>& commandTokens)
{
    if(commandTokens.empty()) return;

    const std::string respCommand = CommandHandler::toRESP(commandTokens);
    if(!m_redisClient.sendRESP(respCommand))
    {
        std::cerr <<  "ERROR:: failed to send command";
        return;
    }


    std::cout<< ServerResponseParser::parseRESPReply(m_redisClient.getSockfd());
}
