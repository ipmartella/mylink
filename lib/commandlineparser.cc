#include "commandlineparser.hpp"
#include <stdexcept>

using namespace mylink;

CommandLineParser::CommandLineParser()
{

}

void CommandLineParser::parse(int argc, char **argv)
{
    if(argc == 0) {
        throw std::invalid_argument("argc cannot be 0");
    }

}
