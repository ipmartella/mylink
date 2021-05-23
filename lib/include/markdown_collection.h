#ifndef MARKDOWNCOLLECTION_HPP
#define MARKDOWNCOLLECTION_HPP
#include <vector>
#include <string>
#include <collection.h>

namespace mylink {

class MarkdownCollection : public Collection
{
public:
    explicit MarkdownCollection();
    void add(const Bookmark bookmark);


private:
    std::vector<Bookmark> bookmarks_;
};

} //namespace mylink

#endif // MARKDOWNCOLLECTION_HPP
