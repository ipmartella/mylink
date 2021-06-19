#include <collection.h>

using namespace mylink;

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
        bookmarks_.emplace(bookmark.get_url(), bookmark);
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
    return bookmarks_.at(url);
}
