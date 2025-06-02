#ifndef COMMAND_HANDLER_HPP
#define COMMAND_HANDLER_HPP

#include<vector>
#include<string>

class CommandHandler
{
public:
    
    //tokenize the args
    static std::vector<std::string> splitArgs(const std::string& input);
    
    //convert the tokens into RESP commands
    static std::string toRESP(const std::vector<std::string>& args); 
};

#endif
