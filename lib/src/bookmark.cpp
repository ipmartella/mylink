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

void throw_if_invalid_format(const std::string& input_url) {
    static std::regex url_starts_with_protocol_or_slash(R"(^(([a-zA-z]+:)|\/)\S*$)");
    std::smatch match;
    if(!std::regex_match(input_url, match, url_starts_with_protocol_or_slash)) {
        throw std::invalid_argument("URL must start with a protocol (like http://) or with a /");
    }
}

std::string trim_url(const std::string& input_url) {
    static std::regex trim_url_regex(R"(^\s*(\S*)\s*$)");
    std::smatch match;
    std::regex_match(input_url, match, trim_url_regex);
    return match[1];
}

} //namespace




Bookmark::Bookmark(const std::string& url, const std::string &title) : url_{trim_url(url)}, title_{title} {
    throw_if_url_is_empty(url_);
    throw_if_invalid_format(url_);
}

const std::string& Bookmark::get_url() const {
    return url_;
}

const std::string& Bookmark::get_title() const {
    return title_;
}

bool Bookmark::is_url_same_as(const Bookmark &other) const {
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
