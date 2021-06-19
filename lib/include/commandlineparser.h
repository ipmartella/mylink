#ifndef COMMANDLINEPARSER_HPP
#define COMMANDLINEPARSER_HPP

#include <collection.h>
#include <iostream>

namespace mylink {
class CommandLineParser
{
public:
    CommandLineParser(BookmarkCollection& collection, std::ostream& stdout);
    void parse(int argc, const char** argv);

private:
    BookmarkCollection& collection_;
    std::ostream& out_stream_;
};

std::string commandline_usage();
std::string commandline_add_usage();

} //namespace mylink

#endif // COMMANDLINEPARSER_HPP
