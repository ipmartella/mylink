#include <bookmark.h>
#include <regex>
#include <algorithm>

using namespace mylink;

namespace {

std::regex empty_url_regex(R"(^\s*$)");


void throw_if_url_is_empty(const std::string& url) {
    if(url.empty()) {
        throw std::invalid_argument("URL cannot be empy or whitespace-only");
    }
}

std::string trim_url(const std::string& input_url) {
    std::regex trim_url_regex(R"(^\s*(\S*)\s*$)");
    std::smatch match;
    std::regex_match(input_url, match, trim_url_regex);
    return match[1];
}

} //namespace




Bookmark::Bookmark(const std::string& url) : url_{trim_url(url)} {
    throw_if_url_is_empty(url_);
}

const std::string& Bookmark::get_url() const {
    return url_;
}

bool Bookmark::same_url_as(const Bookmark &other) const {
    return std::equal(url_.begin(), url_.end(),
                      other.get_url().begin(), other.get_url().end(),
                      [](char a, char b){ return std::tolower(a) == std::tolower(b); }
                      );

}


#ifdef MYLINK_TEST_IN_CODE
#include <doctest.h>

TEST_CASE("Trim url tests") {
    CHECK_EQ(trim_url(" https://www.wikipedia.org"), "https://www.wikipedia.org");
    CHECK_EQ(trim_url("https://www.wikipedia.org "), "https://www.wikipedia.org");
    CHECK_EQ(trim_url("\t https://www.wikipedia.org \r\n"), "https://www.wikipedia.org");
}

#endif
