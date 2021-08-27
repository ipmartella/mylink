#include <markdown_storage.h>
#include <string>
#include <regex>
#include <stdexcept>
#include <fstream>

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


Bookmark convert_plain_url_list_item_to_bookmark(const std::string& line) {
    static const std::regex regexp_simple(R"(^\s*[\*-]\s*(\S+)\s*$)");
    std::smatch match;
    if(std::regex_match(line, match, regexp_simple)) {
        return Bookmark{match[1]};
    } else {
        return INVALID_BOOKMARK;
    }
}

Bookmark convert_markdown_link_list_item_to_bookmark(const std::string& line) {
    static const std::regex regexp_markdown_link(R"(\s*[\*-]\s*\[(.+)\]\((.*)\)\s*$)");
    std::smatch match;
    if(std::regex_match(line, match, regexp_markdown_link)) {
        return Bookmark{match[2], match[1]};
    } else {
        return INVALID_BOOKMARK;
    }
}

Bookmark parse_markdown_line(const std::string& line) {
    const auto conversion_functions = {
        convert_markdown_link_list_item_to_bookmark,
        convert_plain_url_list_item_to_bookmark
    };

    Bookmark bookmark = INVALID_BOOKMARK;
    for(const auto conversion_func : conversion_functions) {
        try {
            bookmark = conversion_func(line);
            if(!bookmark.is_url_same_as(INVALID_BOOKMARK)) {
                return bookmark;
            }
        } catch(std::invalid_argument&) {
            bookmark = INVALID_BOOKMARK;
        }
    }
    return INVALID_BOOKMARK;
}

BookmarkCollection read_bookmarks_from_stream(std::istream& stream) {
    BookmarkCollection bookmarks;
    std::string line;
    while(std::getline(stream, line, '\n')) {
        Bookmark new_bookmark = INVALID_BOOKMARK;
        new_bookmark = parse_markdown_line(line);

        if(!new_bookmark.is_url_same_as(INVALID_BOOKMARK)) {
            bookmarks.add(new_bookmark);
        }
    }

    return bookmarks;
}

std::string escape_link_title(const std::string& title) {
    static const std::regex square_bracket_regex{R"((\[|\]))"};
    return std::regex_replace(title, square_bracket_regex, "\\$&");
}

std::string convert_to_markdown_line(const Bookmark& bookmark) {
    std::stringstream markdown_line_builder;
    markdown_line_builder << "- ";
    if(bookmark.get_title().empty()) {
        markdown_line_builder << bookmark.get_url();
    } else {
        markdown_line_builder << "[" << escape_link_title(bookmark.get_title()) << "](" << bookmark.get_url() << ")";
    }
    return markdown_line_builder.str();
}

} //namespace


/**
* @brief Construct a new MarkdownStorageBackend, backed by a disk file named <filepath>.
* @param filepath Path of the Markdown file to save/load. The path must be accessible by the running process.
*/
MarkdownStorageBackend::MarkdownStorageBackend(const std::string &filename) : filepath_(filename)
{ }

/**
 * @brief Saves a BookmarkCollection to Markdown.
 *
 * Each Bookmark in the given <collection> is stored in the file on a separate line, terminated by '\n'.
 *
 * If the collection is empty, a empty file will be written (existing files will be truncated).
 * For each Bookmark in the BookmarkCollection without title, this method will add a line to the file with the following format:
 * - url
 *
 * For each Bookmark in the BookmarkCollection with a title, this method will add a line to the file with the following format:
 * - [title](url)
 *
 * Square brackets in the title will be escaped with a backslash (i.e. "My [blog]" --> "My \[blog\]")
 *
 * The order in which Bookmarks are written to file is not specified.
 *
 * @param collection BookmarkCollection to save.
 */
void MarkdownStorageBackend::save(const BookmarkCollection &collection)
{
    std::ofstream output_file{filepath_, std::ios_base::out | std::ios_base::trunc};
    for(const auto& bookmark : collection) {
        output_file << convert_to_markdown_line(bookmark) << '\n';
    }
}

/**
* @brief Loads a BookmarkCollection from Markdown.
*
* If the file is empty or it does not exist, this method returns an empty BookmarkCollection.
* The file is expected to contain at most one valid Bookmark per line (lines are delimited by '\n').
* Valid line formats for Bookmarks are:
* * url
* - url
* * [title](url)
* - [title](url)
*
* Invalid lines are silently ignored. Leading and trailing whitespace is always trimmed.
*
* @return BookmarkCollection read from the file
*/
BookmarkCollection MarkdownStorageBackend::load()
{
    std::ifstream stream{filepath_};
    return read_bookmarks_from_stream(stream);
}

std::string MarkdownStorageBackend::get_path() const {
    return filepath_;
}

void MarkdownStorageBackend::set_path(const std::string &path) {
    filepath_ = path;
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
        CHECK(bookmark.is_url_same_as(INVALID_BOOKMARK));
    }

    void line_is_parsed_with_url(const std::string& line, const std::string& expected_url) {
        INFO("Line:<", line, ">");
        auto bookmark = parse_markdown_line(line);
        CHECK_EQ(bookmark.get_url(), expected_url);
    }

    void line_is_parsed_with_url_and_title(const std::string& line, const std::string& expected_url, const std::string& expected_title) {
        INFO("Line:<", line, ">");
        auto bookmark = parse_markdown_line(line);
        CHECK_EQ(bookmark.get_url(), expected_url);
        CHECK_EQ(bookmark.get_title(), expected_title);
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
    GIVEN("Variations of <- [Test url](http://www.mytesturl.org)>")
    {
        std::vector<std::string> lines_with_titles = {
            "- [Test url](http://www.mytesturl.org)\n",
            " - [Test url](http://www.mytesturl.org)   ",
            " \t - [Test url](http://www.mytesturl.org)   ",
            "\t-[Test url](http://www.mytesturl.org)   ",
            "* [Test url](http://www.mytesturl.org)\r\n",
            " * [Test url](http://www.mytesturl.org)   \r",
            " \t * [Test url](http://www.mytesturl.org)   ",
            "\t*[Test url](http://www.mytesturl.org)   ",
        };

        for(const auto& line: lines_with_titles) {
            line_is_parsed_with_url_and_title(line, "http://www.mytesturl.org", "Test url");
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
                CHECK(bookmarks.contains("https://www.wikipedia.org"));
                CHECK(bookmarks.contains("https://www.github.org"));
                CHECK(bookmarks.contains("https://www.myurl.com/index/test"));
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
                CHECK(bookmarks.contains("https://www.wikipedia.org"));
                CHECK(bookmarks.contains("https://www.github.org"));
                CHECK(bookmarks.contains("https://www.myurl.com/index/test"));
            }
        }
    }
}

SCENARIO("Convert Bookmark to Markdown line") {
    GIVEN("A bookmark with a plain URL") {
        Bookmark plain_url_bookmark("http://www.wikipedia.org");

        WHEN("The bookmark is exported") {
            std::string markdown_line = convert_to_markdown_line(plain_url_bookmark);
            THEN("The line is like: - http://www.url.org") {
                CHECK_EQ(markdown_line, "- http://www.wikipedia.org");
            }
        }
    }
}


//"- http://www.wikipedia.org\n"
//"- http://www.url.org\n"
//"- [Test URL](http://www.mytesturl.org/test/index)\n"
//"- [\\[Title with square brackets\\]](http://www.mytesturl.org/test/square)\n");
//
#endif
