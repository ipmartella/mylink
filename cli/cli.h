#ifndef CLI_H
#define CLI_H
#include <iostream>
#include <collection_storage.h>

namespace mylink {
namespace cli {

constexpr int MYLINK_VERSION_MAJOR = 0;
constexpr int MYLINK_VERSION_MINOR = 1;
constexpr int MYLINK_VERSION_PATCH = 0;

int command_line_shell(int argc, const char** argv, BookmarkCollectionStorageBackend& backend, std::ostream& out_stream = std::cout);
std::string basic_usage();

} //namespace cli
} //namespace mylink

#endif // CLI_H
