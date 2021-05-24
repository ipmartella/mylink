#ifndef BOOKMARK_HPP
#define BOOKMARK_HPP
#include <string>

namespace mylink {

struct Bookmark {
public:
    Bookmark(const std::string& url) : url(url) {}
    const std::string url;
};

} //namespace mylink


#endif // BOOKMARK_HPP
