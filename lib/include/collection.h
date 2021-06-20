#ifndef COLLECTION_HPP
#define COLLECTION_HPP

#include "bookmark.h"
#include <unordered_map>

namespace mylink {

/**
 * @brief A collection of Bookmarks, each with a unique URL.
 *
 * The BookmarkCollection class allows you to add/remove/edit a unordered collection of Bookmarks.
 * All Bookmarks in this collection have a different URL.
 */
class BookmarkCollection {
public:
    using bookmark_container_type = std::unordered_map<std::string, Bookmark>;
    using iterator = bookmark_container_type::iterator;
    using const_iterator = bookmark_container_type::const_iterator;

    void add(const Bookmark& bookmark);

    //void remove(const std::string& url);
    //void remove(const Bookmark& bookmark);

    size_t size() const;
    Bookmark operator[](const std::string& url) const;

    bool contains(const std::string &url) const;

    //iterator begin();
    //iterator end();
    //const_iterator begin() const;
    //const_iterator end() const;

    virtual ~BookmarkCollection() = default;

private:
    /**
     * @brief Container for all Bookmarks.
     */
    bookmark_container_type bookmarks_;
};

} //namespace mylink

#endif // COLLECTION_HPP
