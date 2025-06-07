#include "../include/CommandHandler.hpp"

#include <regex>
#include <string>
#include <string_view>
#include <vector>
#include <ranges>

std::vector<std::string> CommandHandler::splitArgs(const std::string &input)
{

    static std::regex pattern(R"((\"[^\"]+\"|\S+))");
    
    std::sregex_iterator begin(input.begin(),input.end(),pattern),end;
    std::vector<std::string> tokens;
    tokens.reserve(std::distance(begin,end));

    for(const auto& match : std::ranges::subrange(begin,end))
    {
        std::string token = match.str();
  

        //quote removal
        if(token.size() >= 2 and token.front() == '\"' and token.back() == '\"')
        {
            token = token.substr(1,token.size() - 2);
        }

        tokens.emplace_back(std::move(token));
    }

    return tokens;
}



/* 
* -> start of an array
$ -> bulk of an array
+ -> args
*/

std::string CommandHandler::toRESP(const std::vector<std::string> &tokens)
{
    std::string resp;
    resp.resize(64);

    resp+="*" + std::to_string(tokens.size()) + "\r\n"; //number of tokens

    for(std::string_view token:tokens) //inserts the lenght and value of a token
    {
        resp+= "$" + std::to_string(token.size())+"\r\n"; 
        resp+=token;
        resp+="\r\n";
    }

    return resp;
}
