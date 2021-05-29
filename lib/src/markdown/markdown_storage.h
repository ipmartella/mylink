#ifndef MARKDOWN_STORAGE_H
#define MARKDOWN_STORAGE_H

#include <bookmark.h>
#include <vector>
#include <iostream>

namespace mylink {

Bookmark parse_markdown_line(const std::string& line);
std::string convert_to_markdown_line(const Bookmark& bookmark);

std::vector<Bookmark> read_bookmarks_from_stream(std::istream &markdown_stream);
void write_bookmarks_to_stream(const std::vector<Bookmark>& bookmarks, std::ostream& markdown_stream);


} // namespace mylink

#endif // MARKDOWN_STORAGE_H
