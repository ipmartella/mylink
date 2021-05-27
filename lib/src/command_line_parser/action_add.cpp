#include "action_add.h"
#include "../private_exceptions.h"
#include <commandlineparser.h>

using namespace mylink;
using namespace mylink::impl;

namespace {

std::string extract_url(const ParsedCommandLine& command_line)
{
    constexpr size_t index_for_url = 2;
    if (command_line.hasPositional(index_for_url)) {
        return command_line.getPositional(index_for_url);
    } else {
        throw invalid_command{};
    }
}

} //namespace

void mylink::impl::execute_run_command(const ParsedCommandLine& command_line,
                                     Collection& collection,
                                     std::ostream& out_stream)
{
    try {
        auto url = extract_url(command_line);
        collection.add(url);
    }  catch (invalid_command ex) {
        out_stream << commandline_add_usage();
    }
}

std::string mylink::commandline_add_usage() {
    return "ADD USAGE\n";
}
