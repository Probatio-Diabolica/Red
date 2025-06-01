#include<iostream>
#include "../include/CLI.hpp"
/*
 *TODO::
 *  Client
 *  Command Handler
 *  Response parser
 *  CLI
 *
 *  CONNECTION=> TCP connection
 *  Parsing :: 
 *      > Command parsing: conversion of commands into RESP formats
 *      
 *      > Redis response parser
 * 
 * CLI::
 *      this will be the client, it will do the follwoing:
 *          > handle the redis responses
 *          > parse the redis responses
 *          >send the commands to the server
 * 
 *
 * */

int main(int argc, char* argv[])
{
    std::string host = "127.0.0.1";
    int port = 2005;
    int i =1;

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
        else break;
        ++i;
    }
    

    //hendling the RESP protocol
    CLI cli(host,port);
    cli.run();
}
