#ifndef MARKDOWN_STORAGE_H
#define MARKDOWN_STORAGE_H

#include <bookmark.h>

namespace mylink {

Bookmark parse_markdown_line(const std::string& line);
const Bookmark INVALID_BOOKMARK{"_INVALID_"};

} // namespace mylink

#endif // MARKDOWN_STORAGE_H
