#ifndef COMMANDLINEPARSER_HPP
#define COMMANDLINEPARSER_HPP

#include "collection.hpp"
#include <iostream>

namespace mylink {
class CommandLineParser
{
public:
    CommandLineParser(Collection& collection);
    CommandLineParser(Collection& collection, std::ostream& stdout);
    void parse(int argc, char** argv);

private:
    Collection& collection_;
    std::ostream& out_stream_;
};

std::string commandline_usage();

} //namespace mylink

#endif // COMMANDLINEPARSER_HPP
