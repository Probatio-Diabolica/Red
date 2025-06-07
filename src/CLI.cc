#include "../include/CLI.hpp"
#include <cstddef>
#include <string>
#include <unordered_map>
#include <functional>
#include <ostream>
#include <vector>

/////////////////////////////////////////////////////////////////
//static functions only

static std::string trimWhitespaces(const std::string& str)
{
    size_t start = str.find_last_not_of(" \t\n\r\f\v");
    if(start == std::string::npos) return "";
    size_t end = str.find_first_not_of(" \t\n\r\f\v");
    return str.substr(start,end-start+1);
}

static void displayHelp()
{
    std::cout << "red 1.0.0\n\n"
              << "Usage:\n"
              << "  With both host and port:\n"
              << "      ./red -h <host> -p <port>\n"
              << "  With default host (127.0.0.1):\n"
              << "      ./red -p <port>\n"
              << "  With default port (6379):\n"
              << "      ./red -h <host>\n"
              << "  One-shot command execution:\n"
              << "      ./red <command> [arguments]\n\n"
              << "Interactive Mode (REPL):\n"
              << "  Run without arguments:\n"
              << "      ./red\n"
              << "  Then type Redis commands directly.\n\n"
              << "Built-in commands:\n"
              << "  help   - Display this help message\n"
              << "  quit   - Exit the CLI\n\n"
              << "Examples:\n"
              << "  ./red status\n"
              << "  ./red SET mykey \"Hello World\"\n"
              << "  ./red GET mykey\n\n"
              << "Preferences (set in ~/.redrc):\n"
              << "  :set hints    Enable online command hints\n"
              << "  :set nohints  Disable online command hints\n"
              << std::endl;

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

    std::cout << "Connected to redis at " << m_redisClient.getSockfd() << '\n';

    while(true)
    {
        std::cout<< m_host << ':' << m_port << "> " << std::flush;

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

        const  std::string reply = RedisResponseParser::parseRESPReply(m_redisClient.getSockfd());
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


    std::cout<< RedisResponseParser::parseRESPReply(m_redisClient.getSockfd());
}
