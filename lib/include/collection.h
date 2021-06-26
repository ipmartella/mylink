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

    class iterator {
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = Bookmark;
        using difference_type = int;
        using pointer = Bookmark*;
        using reference = Bookmark&;

        explicit iterator();
        explicit iterator(bookmark_container_type::iterator underlying_iterator);
        iterator& operator++();
        reference operator*() const;
        bool operator==(const iterator& other) const;
        bool operator!=(const iterator& other) const;

    private:
        bookmark_container_type::iterator underlying_iterator_;
    };

    class const_iterator {
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = const Bookmark;
        using difference_type = int;
        using pointer = const Bookmark*;
        using reference = const Bookmark&;

        explicit const_iterator();
        explicit const_iterator(bookmark_container_type::const_iterator underlying_iterator);
        const_iterator& operator++();
        reference operator*() const;
        bool operator==(const const_iterator& other) const;
        bool operator!=(const const_iterator& other) const;

    private:
        bookmark_container_type::const_iterator underlying_iterator_;
    };

    void add(const Bookmark& bookmark);

    //void remove(const std::string& url);
    //void remove(const Bookmark& bookmark);

    size_t size() const;
    Bookmark operator[](const std::string& url) const;

    bool contains(const std::string &url) const;

    iterator begin();
    iterator end();
    const_iterator begin() const;
    const_iterator end() const;

    bool operator==(const BookmarkCollection& other) const;

    virtual ~BookmarkCollection() = default;

private:
    /**
     * @brief Container for all Bookmarks.
     */
    bookmark_container_type bookmarks_;
};

} //namespace mylink

#endif // COLLECTION_HPP
