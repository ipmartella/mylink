#include "markdown_storage.h"

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

#ifdef MYLINK_TEST_IN_CODE
#include <doctest.h>
#include <string>
#include <vector>


namespace {
    void line_is_parsed_but_no_result(const std::string& line)
    {
        INFO("Line:<", line, ">");
        auto bookmark = parse_markdown_line(line);
        CHECK(bookmark.same_url_as(INVALID_BOOKMARK));
    }

    void line_is_parsed_with_url(const std::string& line, const std::string& expected_url) {
        INFO("Line:<", line, ">");
        auto bookmark = parse_markdown_line(line);
        CHECK_EQ(bookmark.url(), expected_url);
    }
} //namespace

SCENARIO("Covert Markdown to bookmark")
{
    GIVEN("A empty line")
    {
        std::vector<std::string> empty_lines = {"", " ", "\t", "\n", "\r\n", " \t     "};
        for (const auto& line : empty_lines) {
            line_is_parsed_but_no_result(line);
        }
    }

    GIVEN("Variations of <- https://www.wikipedia.org>")
    {
        std::vector<std::string> empty_lines = {
            "- https://www.wikipedia.org",
            " - https://www.wikipedia.org  ",
            "  \t - \thttps://www.wikipedia.org  ",
            "\t-https://www.wikipedia.org",
            "-https://www.wikipedia.org\r\n",
            "-https://www.wikipedia.org \n",
        };

        for (const auto& line : empty_lines) {
            line_is_parsed_with_url(line, "https://www.wikipedia.org");
        }
    }
    GIVEN("Variations of <* https://www.wikipedia.org>")
    {
        std::vector<std::string> empty_lines = {
            "* https://www.wikipedia.org",
            " * https://www.wikipedia.org  ",
            "  \t * \thttps://www.wikipedia.org  ",
            "\t*https://www.wikipedia.org",
            "*https://www.wikipedia.org\r\n",
            "*https://www.wikipedia.org \n",
        };

        for (const auto& line : empty_lines) {
            line_is_parsed_with_url(line, "https://www.wikipedia.org");
        }
    }
}

#endif
