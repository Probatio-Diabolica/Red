#include "../include/CLI.hpp"

CLI::CLI(const std::string& host,int port)
    :m_redisClient(host,port)
{
    
}


void CLI::run()
{
    if(!m_redisClient.connectToServer() ) return;
    
    std::cout<<"Connected to redis at : \n";
    
}

