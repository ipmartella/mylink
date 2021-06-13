#include <markdown_collection.h>
#include <fstream>
#include "markdown_storage.h"

using namespace mylink;

namespace {
bool bookmark_in_collection(const Bookmark& target, const std::vector<Bookmark>& bookmarks)
{
    for (const auto& bookmark : bookmarks) {
        if (bookmark.is_url_same_as(target)) {
            return true;
        }
    }
    return false;
}

} //namespace

MarkdownCollection::MarkdownCollection(const std::string& markdown_file_name) : filename_{markdown_file_name} {}

void MarkdownCollection::add(const Bookmark& bookmark)
{
    std::vector<Bookmark> bookmarks = read_bookmarks_from_file(filename_);
    if (!bookmark_in_collection(bookmark, bookmarks)) {
        bookmarks.push_back(bookmark);
        write_bookmarks_to_file(bookmarks, filename_);
    }
}
