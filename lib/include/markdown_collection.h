#ifndef MARKDOWNCOLLECTION_HPP
#define MARKDOWNCOLLECTION_HPP
#include <vector>
#include <string>
#include <collection.h>

namespace mylink {

class MarkdownCollection : public BookmarkCollection
{
public:
    explicit MarkdownCollection(const std::string& markdown_file_name);
    void add(const Bookmark& bookmark) override;
    size_t size() const override;

    ~MarkdownCollection() = default;

private:
    std::string filename_;
};

} //namespace mylink

#endif // MARKDOWNCOLLECTION_HPP
