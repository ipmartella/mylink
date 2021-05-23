#ifndef COMMAND_LINE_ACTION_ADD_H
#define COMMAND_LINE_ACTION_ADD_H

#include <collection.h>
#include <iostream>
#include <argh.h>

void parse_add_command(const argh::parser &command_line,
                       mylink::Collection& collection,
                       std::ostream& out_stream);

#endif // COMMAND_LINE_ACTION_ADD_H
