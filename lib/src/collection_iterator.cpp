#include <collection.h>

using namespace mylink;

BookmarkCollection::iterator BookmarkCollection::begin()
{
    return iterator(bookmarks_.begin());
}

BookmarkCollection::iterator BookmarkCollection::end()
{
    return iterator(bookmarks_.end());
}

BookmarkCollection::const_iterator BookmarkCollection::begin() const
{
    return const_iterator(bookmarks_.begin());
}

BookmarkCollection::const_iterator BookmarkCollection::end() const
{
    return const_iterator(bookmarks_.end());
}

bool BookmarkCollection::operator==(const BookmarkCollection &other) const
{
    return bookmarks_ == other.bookmarks_;
}

BookmarkCollection::iterator::iterator() : underlying_iterator_{} {}

BookmarkCollection::iterator::iterator(BookmarkCollection::bookmark_container_type::iterator underlying_iterator) : underlying_iterator_{underlying_iterator} {}

BookmarkCollection::iterator &BookmarkCollection::iterator::operator++()
{
    underlying_iterator_++;
    return *this;
}

BookmarkCollection::iterator::reference BookmarkCollection::iterator::operator*() const
{
    return underlying_iterator_->second;
}

bool BookmarkCollection::iterator::operator==(const BookmarkCollection::iterator &other) const
{
    return underlying_iterator_ == other.underlying_iterator_;
}

bool BookmarkCollection::iterator::operator!=(const BookmarkCollection::iterator &other) const
{
    return !operator==(other);
}


BookmarkCollection::const_iterator::const_iterator() : underlying_iterator_{} {}

BookmarkCollection::const_iterator::const_iterator(BookmarkCollection::bookmark_container_type::const_iterator underlying_iterator) : underlying_iterator_{underlying_iterator} {}

BookmarkCollection::const_iterator &BookmarkCollection::const_iterator::operator++()
{
    underlying_iterator_++;
    return *this;
}

BookmarkCollection::const_iterator::reference BookmarkCollection::const_iterator::operator*() const
{
    return underlying_iterator_->second;
}

bool BookmarkCollection::const_iterator::operator==(const BookmarkCollection::const_iterator &other) const
{
    return underlying_iterator_ == other.underlying_iterator_;
}

bool BookmarkCollection::const_iterator::operator!=(const BookmarkCollection::const_iterator &other) const
{
    return !operator==(other);
}
