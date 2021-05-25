#include <markdown_storage.h>

#include <string>
#include <regex>
#include <stdexcept>

using namespace mylink;

namespace {

class no_match_found : public std::domain_error {
public:
    no_match_found(const std::regex& regex, const std::string& target)
        : std::domain_error{"Regexp does not match"}, regex_{regex}, target_{target} {}

    const std::regex& regex() { return regex_; }
    const std::string& target() { return target_; }

private:
    std::regex regex_;
    std::string target_;
};

const std::regex regexp_simple(R"(^\s*[\*-]\s*(\S+)\s*$)");

Bookmark convert_plain_url_list_item_to_bookmark(const std::string& line) {
    std::smatch match;
    if(std::regex_match(line, match, regexp_simple)) {
        return Bookmark{match[1]};
    } else {
        throw no_match_found(regexp_simple, line);
    }
}

} //namespace

Bookmark mylink::parse_markdown_line(const std::string& line) {
    try {
        return convert_plain_url_list_item_to_bookmark(line);
    }  catch (no_match_found) {
        return INVALID_BOOKMARK;
    }
}
