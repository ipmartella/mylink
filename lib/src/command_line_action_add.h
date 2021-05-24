#ifndef COMMAND_LINE_ACTION_ADD_H
#define COMMAND_LINE_ACTION_ADD_H

#include "command_line_parsing.h"
#include <collection.h>
#include <iostream>

namespace mylink {
namespace impl {

void parse_add_command(const ParsedCommandLine& command_line,
                       mylink::Collection& collection,
                       std::ostream& out_stream);

} //namespace impl
} //namespace mylink

#endif // COMMAND_LINE_ACTION_ADD_H
