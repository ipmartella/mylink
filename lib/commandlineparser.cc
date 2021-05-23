#include "commandlineparser.hpp"
#include <stdexcept>

using namespace mylink;

CommandLineParser::CommandLineParser(Collection &collection) : CommandLineParser(collection, std::cout)
{}

CommandLineParser::CommandLineParser(Collection &collection, std::ostream &stdout) : collection_(collection), out_stream_(stdout)
{}

void CommandLineParser::parse(int argc, const char **argv)
{
    if(argc == 0) {
        throw std::invalid_argument("argc cannot be 0");
    } else if(argc==1) {
        out_stream_ << commandline_usage();
        return;
    }

    const std::string command{argv[1]};
    if(command == "add") {
        return;
    } else {
        out_stream_ << commandline_usage();
    }
}

std::string mylink::commandline_usage() {
    return "USAGE\n";
}
