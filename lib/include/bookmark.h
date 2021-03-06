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
 * URLs are case-insensitive.
 *
 * Bookmarks MAY have a title, which is a (possibly empty) string of characters.
 * Bookmarks compare equal if they have the same URL and title, otherwise they compare false.
 */
class Bookmark {
public:
    explicit Bookmark(const std::string& url, const std::string& title = "");
    const std::string& get_url() const;
    const std::string& get_title() const;
    bool is_url_same_as(const Bookmark& other) const;
    bool operator==(const Bookmark& rhs) const;
    bool operator!=(const Bookmark& rhs) const;

private:
    /**
     * @brief URL for this Bookmark. See class documentation for more details.
     */
    std::string url_;

    /**
     * @brief Title for this Bookmark. See class documentation for more details
     */
    std::string title_;
};

const Bookmark INVALID_BOOKMARK{"invalid://nope"};

} //namespace mylink


#endif // BOOKMARK_HPP
