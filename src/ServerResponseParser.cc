#include "../include/ServerResponseParser.hpp"
#include <string>
#include <sys/socket.h>
#include <sys/types.h>

/////////////////////////////////////////////////////////////
// static helper functions

//reads a single byte/character from the socket, returns true if only a single byte is read
static bool readByte(int sockfd, char& c)
{
    ssize_t bytesRead=recv(sockfd, &c, 1, 0);

    return (bytesRead==1);
}

static std::string readLine(int sockfd)
{
    std::string line;
    char byte;
    while(readByte(sockfd, byte))
    {
        if(byte=='\r')
        {
            //read and break, because the next char/byte is expected to have '\n'
            readByte(sockfd, byte);
            break;
        }
        line.push_back(byte);
    }
    return line;
}

///////////////////////////////////////////////////////////


std::string ServerResponseParser::parseRESPReply(int sockfd)
{
    char prefix;
    if(!readByte(sockfd, prefix)) return ("Error:: Failed to read response: no data received or connection closed.");
    switch (prefix) 
    {
        case '+': return parseSimpleString(sockfd);
        case '-': return parseSimpleError(sockfd);
        case ':': return parseInterger(sockfd);
        case '$': return parseBulkString(sockfd);
        case '*': return parseArray(sockfd);
        default : return "Error:: Unknown data type.";
    }
}
   
std::string ServerResponseParser::parseSimpleString(int sockfd)
{
    return  readLine(sockfd);
}

std::string ServerResponseParser::parseSimpleError(int sockfd)
{
    return "Error:: " + readLine(sockfd);
}

std::string ServerResponseParser::parseInterger(int sockfd)
{
    return readLine(sockfd);
}

std::string ServerResponseParser::parseBulkString(int sockfd)
{
    const int length = std::stoi(readLine(sockfd));    
    if(length == -1) return "[nil]";

    std::string bulk(length,'\0');
    int totalRead = 0;

    while(totalRead < length)
    {
        ssize_t bytesRead = recv(sockfd, bulk.data()+totalRead, length-totalRead, 0);

        if(bytesRead <= 0 )
        {
            return "Error:: Incomplete bulk data";
        }
        totalRead += bytesRead;
    }

    //gotta cosume the trailing CRLF/ "\r\n"
    char crlf[2];

    if(recv(sockfd,crlf,2,0) != 2) return "Error:: failed to read the CRLF after the bulk data";

    return bulk;
}

std::string ServerResponseParser::parseArray(int sockfd)
{
    int count = std::stoi(readLine(sockfd));

    if(count == -1) return "[nil]";

    std::string result;

    result.reserve(128);
    
    for(int i =0; i <count ; ++i)
    {
        result += parseRESPReply(sockfd);
        
        if(i != count -1) result += '\n';
    }
    
    return  result;
}
        
