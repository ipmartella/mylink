#include <markdown_storage.h>

#include <string>
#include <regex>
#include <stdexcept>

using namespace mylink;

namespace {

const std::regex regexp_simple(R"(^\s*-\s*(\S+)\s*$)");

Bookmark matches(const std::string& line) {
    std::smatch match;
    if(std::regex_match(line, match, regexp_simple)) {
        return Bookmark{match[1]};
    } else {
        throw std::out_of_range{"No match"};
    }
}

} //namespace

Bookmark mylink::parse_markdown_line(const std::string& line) {
    try {
        return matches(line);
    }  catch (std::out_of_range) {
        return INVALID_BOOKMARK;
    }
}
