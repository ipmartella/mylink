#ifndef COLLECTION_HPP
#define COLLECTION_HPP

#include "bookmark.h"
#include <vector>

namespace mylink {

class Collection {
public:
//    using iterator = std::vector<Bookmark>::iterator;
//    using const_iterator = std::vector<Bookmark>::const_iterator;

    virtual void add(const Bookmark& bookmark) = 0;
//    virtual size_t size() const = 0;
//    virtual iterator begin() = 0;
//    virtual iterator end() = 0;
//    virtual const_iterator begin() const = 0;
//    virtual const_iterator end() const = 0;

    virtual ~Collection() = default;
};

} //namespace mylink

#endif // COLLECTION_HPP
