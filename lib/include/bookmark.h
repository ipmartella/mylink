#ifndef BOOKMARK_HPP
#define BOOKMARK_HPP
#include <string>

namespace mylink {

struct Bookmark {
public:
    Bookmark(const std::string& url);
    const std::string& url() const;
    bool same_url_as(const Bookmark& other) const;

private:
    std::string url_;
};

} //namespace mylink


#endif // BOOKMARK_HPP
