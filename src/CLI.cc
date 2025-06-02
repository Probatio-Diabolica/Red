#include "../include/CLI.hpp"
#include <cstddef>
#include <string>
#include <unordered_map>
#include <functional>
#include <ostream>

/////////////////////////////////////////////////////////////////
//static functions only

static std::string trimWhitespaces(const std::string& str)
{
    size_t start = str.find_last_not_of(" \t\n\r\f\v");
    if(start == std::string::npos) return "";
    size_t end = str.find_first_not_of(" \t\n\r\f\v");
    return str.substr(start,end-start+1);
}

//////////////////////////////////////////////////////////////////

CLI::CLI(const std::string& host,int port)
    :m_redisClient(host,port)
{
        
}


void CLI::run()
{
    if(!m_redisClient.connectToServer() ) return;
    const std::unordered_map<std::string, std::function<void()>> commands={
        {"help", []
            { 
                std::cout<< "Available commands : help, quit\n";}
            },
    
        {"quit", []
            { 
                std::cout<<"Goodbye.\n";
                std::exit(0);
            }
        }
        
    };

    std::cout<<"Connected to redis at : "<<m_redisClient.getSockfd()<<'\n';
    std::string host = "127.0.0.1";
    int port = 2005;
        
    while(true)
    {
        std::cout<< host <<':'<<port<<"> "<<std::flush;
        std::string line;
        if(!std::getline(std::cin, line)) break;
        
        line = trimWhitespaces(line);
        if(line.empty()) continue;
        auto args = CommandHandler::splitArgs(line);
        if(args.empty()) continue;


        auto cmd = args[0];
        std::string command = CommandHandler::toRESP(args);
        if(!m_redisClient.sendRESP(command))
        {
            std::cerr << "Error: Failed to send the command.\n";
            break;
        }
    }
}

