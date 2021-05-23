#include "commandlineparser.hpp"
#include "argh.h"
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

    argh::parser argh_parser;
    argh_parser.parse(argc, argv);

    const std::string command{argh_parser[1]};
    if(command == "add") {
        if(!argh_parser(3)) {
            out_stream_ << commandline_add_usage();
        }
    } else {
        out_stream_ << commandline_usage();
    }
}

std::string mylink::commandline_usage() {
    return "USAGE\n";
}

std::string mylink::commandline_add_usage() {
    return "ADD USAGE\n";
}
