#ifndef BOOKMARK_HPP
#define BOOKMARK_HPP
#include <string>


namespace mylink {

/**
 * @brief The Bookmark represents a URL and its metadata
 *
 * All Bookmarks MUST have a URL.
 * All strings are considered valid URLs, if after trimming leading and trailing whitespace the match one of the following formats:
 * - Empty strings
 * - Strings containing whitespace characters
 * - Strings not starting with a ASCII letter or a number
 *
 * When a URL does not specify protocol, then 'http' is used as default protocol (i.e. 'localhost' => 'http://localhost').
 *
 * Bookmarks MAY have a title, which is a (possibly empty) string of characters.
 */
class Bookmark {
public:
    explicit Bookmark(const std::string& url, const std::string& title = "");
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
