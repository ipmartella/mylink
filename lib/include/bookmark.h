#ifndef BOOKMARK_HPP
#define BOOKMARK_HPP
#include <string>

namespace mylink {

struct Bookmark {
public:
    Bookmark(const std::string& url, const std::string& title = "");
    const std::string& get_url() const;
    const std::string& get_title() const;
    bool is_url_same_as(const Bookmark& other) const;

private:
    std::string url_;
    std::string title_;
};

const Bookmark INVALID_BOOKMARK{"invalid://nope"};

} //namespace mylink


#endif // BOOKMARK_HPP
