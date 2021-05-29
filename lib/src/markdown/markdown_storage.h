#ifndef MARKDOWN_STORAGE_H
#define MARKDOWN_STORAGE_H

#include <bookmark.h>
#include <vector>
#include <iostream>

namespace mylink {

std::vector<Bookmark> read_bookmarks_from_file(const std::string& filename);
void write_bookmarks_to_file(const std::vector<Bookmark>& bookmarks, const std::string& filename);


} // namespace mylink

#endif // MARKDOWN_STORAGE_H
