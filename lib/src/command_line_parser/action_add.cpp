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

std::string extract_title(const ParsedCommandLine& command_line)
{
    return command_line.getOption(option_title_short, option_title_long, "");
}

} //namespace

void mylink::impl::action_add(const ParsedCommandLine& command_line,
                                     Collection& collection,
                                     std::ostream& out_stream)
{
    try {
        auto url = extract_url(command_line);
        auto title = extract_title(command_line);
        collection.add(Bookmark{url, title});
    }  catch (invalid_command ex) {
        out_stream << commandline_add_usage();
    }
}

std::string mylink::commandline_add_usage() {
    return "Usage: mylink add <url>\n"
           "\n"
           "Adds <url> to the default bookmark collection file\n"
           "\n";
}
