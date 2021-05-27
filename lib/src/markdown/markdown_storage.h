#ifndef MARKDOWN_STORAGE_H
#define MARKDOWN_STORAGE_H

#include <bookmark.h>

namespace mylink {

Bookmark parse_markdown_line(const std::string& line);
std::string convert_to_markdown_line(const Bookmark& bookmark);
const Bookmark INVALID_BOOKMARK{"_INVALID_"};

} // namespace mylink

#endif // MARKDOWN_STORAGE_H
