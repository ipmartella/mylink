#ifndef CLI_H
#define CLI_H
#include <iostream>
#include <collection_storage.h>

namespace mylink {
namespace cli {

int command_line_shell(int argc, const char** argv, BookmarkCollectionStorageBackend& backend, std::ostream& stdout = std::cout);
std::string basic_usage();

} //namespace cli
} //namespace mylink

#endif // CLI_H
