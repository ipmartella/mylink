#ifndef ACTIONS_H
#define ACTIONS_H
#include <iostream>
#include "parser/parser_impl.h"
#include <collection_storage.h>
#include "cli.h"

namespace mylink {
namespace cli {

int action_add(int argc, const char** argv, BookmarkCollectionStorageBackend& backend, std::ostream& out_stream);
std::string action_add_usage();

int action_server(int argc, const char** argv, BookmarkCollectionStorageBackend& backend, std::ostream& out_stream);
std::string action_server_usage();

} //namespace cli
} //namespace mylink

#endif // ACTIONS_H
