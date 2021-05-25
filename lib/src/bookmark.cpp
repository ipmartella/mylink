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

const std::string& Bookmark::url() const {
    return url_;
}
