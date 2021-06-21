#ifndef CLI_H
#define CLI_H
#include <iostream>

namespace mylink {
namespace cli {

int command_line_shell(int argc, const char** argv, std::ostream& stdout);
std::string commandline_usage();

} //namespace cli
} //namespace mylink

#endif // CLI_H
