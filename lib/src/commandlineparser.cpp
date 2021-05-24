#include "command_line_action_add.h"
#include "command_line_parsing.h"
#include "private_exceptions.h"
#include <commandlineparser.h>
#include <functional>
#include <map>
#include <stdexcept>

using namespace mylink;
using namespace mylink::impl;

namespace {

using ActionParser = std::function<void(const ParsedCommandLine&, Collection&, std::ostream&)>;

void run_action(const std::string& action,
                const ParsedCommandLine& command_line,
                Collection& collection,
                std::ostream& out_stream)
{
    static const std::map<std::string, ActionParser> sActionParsers = {{"add", execute_run_command}};
    sActionParsers.at(action)(command_line, collection, out_stream);
}


std::string extract_action(const ParsedCommandLine& command_line)
{
    constexpr size_t index_for_action = 1;
    if (command_line.hasPositional(index_for_action)) {
        return command_line.getPositional(index_for_action);
    } else {
        throw invalid_command{};
    }
}

void throw_if_impossible_arguments(int argc, const char**) {
    if(argc == 0) {
        throw std::invalid_argument("argc cannot be zero");
    }
}

} //namespace


CommandLineParser::CommandLineParser(Collection &collection, std::ostream &stdout = std::cout) : collection_(collection), out_stream_(stdout)
{}

void CommandLineParser::parse(int argc, const char **argv)
{
    try {
        throw_if_impossible_arguments(argc, argv);

        ParsedCommandLine command_line{argc, argv};
        auto action = extract_action(command_line);

        try {
            run_action(action, command_line, collection_, out_stream_);
        }  catch (std::out_of_range ex) {
            throw invalid_command{};
        }
    }  catch (invalid_command ex) {
        out_stream_ << commandline_usage();
    }
}


