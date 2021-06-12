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
    static const std::regex trim_url_regex(R"(^\s*(\S*)\s*$)");
    std::smatch match;
    std::regex_match(input_url, match, trim_url_regex);
    return match[1];
}

std::string extract_protocol(const std::string& url) {
    static const std::regex protocol_regex(R"(^([a-zA-Z]+)://.*)");
    std::smatch match;
    if(std::regex_match(url, match, protocol_regex)) {
        return match[1];
    } else {
        return "";
    }
}

const std::string DEFAULT_PROTOCOL = "http://";

} //namespace




Bookmark::Bookmark(const std::string& url, const std::string &title) : url_{trim_url(url)}, title_{title} {
    throw_if_url_is_empty(url_);
    throw_if_contains_whitespace(url_);
    throw_if_not_start_with_number_or_letter(url_);
    if(extract_protocol(url_).empty()) {
        url_ = DEFAULT_PROTOCOL + url_;
    }
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

TEST_CASE("Extract protocol tests") {
    CHECK_EQ(extract_protocol("http://www.wikipedia.org"), "http");
    CHECK_EQ(extract_protocol("https://www.wikipedia.org"), "https");
    CHECK_EQ(extract_protocol("ftp://www.wikipedia.org"), "ftp");
    CHECK_EQ(extract_protocol("file://home/user/file"), "file");
    CHECK_EQ(extract_protocol("localhost"), "");
    CHECK_EQ(extract_protocol("www.wikipedia.org"), "");
    CHECK_EQ(extract_protocol("127.0.0.1:3128"), "");
    CHECK_EQ(extract_protocol("localhost:3128"), "");
}

#endif
