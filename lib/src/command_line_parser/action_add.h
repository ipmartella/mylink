#ifndef COMMAND_LINE_ACTION_ADD_H
#define COMMAND_LINE_ACTION_ADD_H

#include "parser_impl.h"
#include <collection.h>
#include <iostream>

namespace mylink {
namespace impl {

void action_add(const ParsedCommandLine& command_line,
                         mylink::BookmarkCollection& collection,
                         std::ostream& out_stream);

} //namespace impl
} //namespace mylink

#endif // COMMAND_LINE_ACTION_ADD_H
