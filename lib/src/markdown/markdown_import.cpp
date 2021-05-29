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
    } catch(std::invalid_argument) {
        return INVALID_BOOKMARK;
    }
}

std::vector<Bookmark> mylink::read_bookmarks_from_stream(std::istream& stream) {
    stream.clear();
    stream.seekg(0);
    std::vector<Bookmark> bookmarks;
    std::string line;
    while(std::getline(stream, line, '\n')) {
        auto new_bookmark = parse_markdown_line(line);
        if(!new_bookmark.same_url_as(INVALID_BOOKMARK)) {
            bookmarks.push_back(new_bookmark);
        }
    }

    return bookmarks;
}

#ifdef MYLINK_TEST_IN_CODE
#include <doctest.h>
#include <string>
#include <vector>
#include <sstream>


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
        CHECK_EQ(bookmark.get_url(), expected_url);
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

    GIVEN("A line with only dashes ----------------") {
        std::vector<std::string> empty_lines = {
            "-----------------------",
            " - ------------------",
        };

        for (const auto& line : empty_lines) {
            line_is_parsed_but_no_result(line);
        }
    }
}

SCENARIO("Convert Markdown stream to Bookmarks") {
    GIVEN("A empty stream") {
        std::stringstream stream;

        WHEN("The stream is read") {
            auto bookmarks = read_bookmarks_from_stream(stream);

            THEN("No bookmarks are returned") {
                CHECK_EQ(bookmarks.size(), 0);
            }
        }
    }

    GIVEN("A stream of Bookmarks") {
        std::stringstream stream;
        stream << "- https://www.wikipedia.org\n";
        stream << "* https://www.github.org\r\n";
        stream << "- https://www.myurl.com/index/test";

        WHEN("The stream is read") {
            auto bookmarks = read_bookmarks_from_stream(stream);

            THEN("The bookmarks are read") {
                CHECK_EQ(bookmarks.size(), 3);
                CHECK_EQ(bookmarks[0].get_url(), ("https://www.wikipedia.org"));
                CHECK_EQ(bookmarks[1].get_url(), ("https://www.github.org"));
                CHECK_EQ(bookmarks[2].get_url(), ("https://www.myurl.com/index/test"));
            }
        }
    }

    GIVEN("A stream of Bookmarks, containing also spurious lines") {
        std::stringstream stream;
        stream << "# First article\n";
        stream << "- https://www.wikipedia.org\n";
        stream << "My useless comment\n";
        stream << "\n";
        stream << "* https://www.github.org\r\n";
        stream << " -----------------\n";
        stream << " * ************** *\n";
        stream << "- https://www.myurl.com/index/test";

        WHEN("The stream is read") {
            auto bookmarks = read_bookmarks_from_stream(stream);

            THEN("The bookmarks are read") {
                CHECK_EQ(bookmarks.size(), 3);
                CHECK_EQ(bookmarks[0].get_url(), ("https://www.wikipedia.org"));
                CHECK_EQ(bookmarks[1].get_url(), ("https://www.github.org"));
                CHECK_EQ(bookmarks[2].get_url(), ("https://www.myurl.com/index/test"));
            }
        }
    }
}

#endif
