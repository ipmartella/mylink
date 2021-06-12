#include <bookmark.h>
#include <regex>
#include <algorithm>

using namespace mylink;

namespace {



void throw_if_url_is_empty(const std::string& url) {
    if(url.empty()) {
        throw std::invalid_argument("URL cannot be empy or whitespace-only");
    }
}

void throw_if_contains_whitespace(const std::string& url) {
    static const std::regex contains_whitespace(R"(\s)");
    std::smatch match;
    if(std::regex_search(url, match, contains_whitespace)) {
        throw std::invalid_argument("URL cannot contain whitespace");
    }
}

void throw_if_not_start_with_number_or_letter(const std::string& url) {
    static const std::regex starts_with_letters_or_numbers(R"(^[a-zA-Z0-9])");
    std::smatch match;
    if(!std::regex_search(url, match, starts_with_letters_or_numbers)) {
        throw std::invalid_argument("URL must start with a ASCII letter or a number");
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
    throw_if_contains_whitespace(url_);
    throw_if_not_start_with_number_or_letter(url_);
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
