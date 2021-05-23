#include "commandlineparser.hpp"
#include <argh.h>
#include <stdexcept>
#include <map>
#include <functional>

using namespace mylink;

class invalid_command : public std::logic_error {
public:
    invalid_command() : std::logic_error{"Invalid syntax"} {};
};

CommandLineParser::CommandLineParser(Collection &collection, std::ostream &stdout = std::cout) : collection_(collection), out_stream_(stdout)
{}

void throw_if_impossible_arguments(int argc, const char**) {
    if(argc == 0) {
        throw std::invalid_argument("argc cannot be zero");
    }
}

void throw_if_missing_arguments(int argc) {
    if(argc == 1) {
        throw invalid_command{};
    }
}

argh::parser parse_command_line(int argc, const char **argv) {
    argh::parser argh_parser;
    argh_parser.parse(argc, argv);
    return argh_parser;
}

std::string extract_action(const argh::parser& command_line) {
    constexpr size_t index_for_action = 1;
    if(command_line(index_for_action)){
        return command_line[index_for_action];
    } else {
        throw invalid_command{};
    }
}


using ActionParser = std::function<void(const argh::parser&, Collection&, std::ostream&)>;

std::string extract_url(const argh::parser &command_line){
    constexpr size_t index_for_url = 2;
    if(command_line(index_for_url)) {
        return command_line[index_for_url];
    } else {
        throw invalid_command{};
    }
}

void parse_add_command(const argh::parser &command_line,
                       Collection& collection,
                       std::ostream& out_stream) {
    try {
        auto url = extract_url(command_line);
        collection.add(url);
    }  catch (invalid_command ex) {
        out_stream << commandline_add_usage();
    }
}


const std::map<std::string, ActionParser> sActionParsers = {
    {"add", parse_add_command}
};


void CommandLineParser::parse(int argc, const char **argv)
{
    try {
        throw_if_impossible_arguments(argc, argv);

        auto command_line = parse_command_line(argc, argv);
        auto action = extract_action(command_line);

        try {
            auto parser_for_action = sActionParsers.at(action);
            parser_for_action(command_line, collection_, out_stream_);
        }  catch (std::out_of_range ex) {
            throw invalid_command{};
        }
    }  catch (invalid_command ex) {
        out_stream_ << commandline_usage();
    }
}


std::string mylink::commandline_usage() {
    return "USAGE\n";
}

std::string mylink::commandline_add_usage() {
    return "ADD USAGE\n";
}
