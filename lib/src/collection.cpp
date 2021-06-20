#include <collection.h>
#include <algorithm>
#include <cctype>
#include <unordered_map>

using namespace mylink;

namespace {

/**
 * @brief Naively converts a ASCII string to lowercase. It will probably blow-up in case of non-ASCII inputs.
 * @param ascii_input ASCII input to convert
 * @return The input string converted to lowercase
 */
std::string ascii_to_lower(const std::string& ascii_input) {
    std::string lowercase;
    std::transform(ascii_input.begin(), ascii_input.end(),
                   std::back_inserter(lowercase),
                   [](char c) { return std::tolower(c);} );
    return lowercase;
}



} //namespace

/**
 * @brief Adds a Bookmark to this BookmarkCollection, if a Bookmark with the same URL does not already exist.
 *
 * If a Bookmark with the same URL already exist, this method does nothing.
 *
 * @param bookmark Bookmark to be added
 */
void BookmarkCollection::add(const Bookmark &bookmark)
{
    if(bookmarks_.count(bookmark.get_url()) == 0) {
        bookmarks_.emplace(ascii_to_lower(bookmark.get_url()), bookmark);
    }
}

/**
 * @brief Returns the number of Bookmarks in this BookmarkCollection.
 * @return the number of Bookmarks in this BookmarkCollection
 */
size_t BookmarkCollection::size() const
{
    return bookmarks_.size();
}

/**
 * @brief Returns the Bookmark associated with <url>, or throws std::out_of_range if the URL cannot be found.
 * @param url URL to search for
 * @return Bookmark for <url>
 * @throws std::out_of_range if there are no Bookmarks with <url>
 */
Bookmark BookmarkCollection::operator[](const std::string &url) const
{
    return bookmarks_.at(ascii_to_lower(url));
}

/**
 * @brief Checks if a Bookmark with the given <url> is contained in this BookmarkCollection
 * @param url URL to search for (case-insensitive)
 * @return true if a Bookmark with the given <url> is in this BookmarkCollection, false otherwise
 */
bool BookmarkCollection::contains(const std::string &url) const
{
    return bookmarks_.count(ascii_to_lower(url)) > 0;
}
