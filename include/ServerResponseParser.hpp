#ifndef REDIS_RESPONSE_PARSER_HPP
#define REDIS_RESPONSE_PARSER_HPP


#include <string>
class ServerResponseParser {
public:

    // Parses a Redis RESP reply from the given socket and returns it as a string. In case of a failure, it return an empty string
    static std::string parseRESPReply(int sockfd);

private:

    //internal parsers for individual RESP data types read from the socket 

    static std::string parseSimpleString(int sockfd);

    static std::string parseSimpleError(int sockfd);

    static std::string parseInterger(int sockfd);

    static std::string parseBulkString(int sockfd);

    static std::string parseArray(int sockfd);

};

#endif
