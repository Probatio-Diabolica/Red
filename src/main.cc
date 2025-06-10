#include<iostream>
#include <pwd.h>
#include <sys/types.h>
#include <unistd.h>
#include <vector>
#include "../include/CLI.hpp"



std::string getHost()
{
    std::string host;
    uid_t id = getuid();
    passwd* pw = getpwuid(id);

    if(pw && pw->pw_name) host=pw->pw_name;
    else host = "127.0.0.1";

    return host;
}



int main(int argc, char* argv[])
{
    std::string host = getHost();
    int port = 2005;
    int i =1;
    std::vector<std::string> tokens;
    //getting the cli args
    while(i<argc)
    {
        std::string arg = argv[i];
        if(arg=="-h" and i+1 < argc)
        {
            ++i;
            host = argv[i];
        }
        else if(arg=="-p" and i + 1 < argc)
        {
            ++i;
            port = std::stoi(argv[i]);
        }
        else 
        {
            while(i < argc)
            {
                tokens.push_back(argv[i]);
                ++i;
            }
        }
        ++i;
    }
    

    //hendling the RESP protocol
    CLI cli(host,port);
    cli.run(tokens);
}
