#include <markdown_collection.h>
#include <fstream>
#include "markdown_storage.h"

using namespace mylink;

namespace {
bool bookmark_in_collection(const Bookmark& target, const std::vector<Bookmark>& bookmarks)
{
    for (const auto& bookmark : bookmarks) {
        if (bookmark.same_url_as(target)) {
            return true;
        }
    }
    return false;
}

void add_bookmark_to_file(const Bookmark& bookmark, const std::string& filename) {
    std::vector<Bookmark> bookmarks = read_bookmarks_from_file(filename);
    if (!bookmark_in_collection(bookmark, bookmarks)) {
        bookmarks.push_back(bookmark);
        write_bookmarks_to_file(bookmarks, filename);
    }
}


} //namespace

MarkdownCollection::MarkdownCollection(const std::string& markdown_file_name) : filename_{markdown_file_name} {}

void MarkdownCollection::add(const Bookmark& bookmark)
{
    add_bookmark_to_file(bookmark, filename_);
}

#ifdef MYLINK_TEST_IN_CODE
#include <doctest.h>

SCENARIO("Adding bookmarks to files") {

    GIVEN("A empty file") {
        const std::string test_file = "/tmp/mylink_test1";
        std::remove(test_file.c_str());

        WHEN("I add a bookmark in Markdown format") {
            Bookmark new_bookmark{"http://www.wikipedia.org"};
            add_bookmark_to_file(new_bookmark, test_file);

            THEN("The stream contains the bookmark") {
                auto saved_bookmarks = read_bookmarks_from_file(test_file);
                CHECK_EQ(saved_bookmarks.size(), 1);
                CHECK_EQ(saved_bookmarks[0].get_url(), "http://www.wikipedia.org");
            }
        }
    }

    GIVEN("A populated stream") {
        const std::string test_file = "/tmp/mylink_test2";
        std::remove(test_file.c_str());
        std::vector<Bookmark> initial_bookmarks{
            Bookmark("http://www.wikipedia.org"),
            Bookmark("http://www.myurl.org"),
        };
        write_bookmarks_to_file(initial_bookmarks, test_file);

        WHEN("I add a new bookmark in Markdown format") {
            Bookmark new_bookmark{"http://www.test.org"};
            add_bookmark_to_file(new_bookmark, test_file);

            THEN("The stream contains the bookmark + all the previous ones") {
                auto saved_bookmarks = read_bookmarks_from_file(test_file);
                CHECK_EQ(saved_bookmarks.size(), 3);
                CHECK(saved_bookmarks[0].same_url_as(initial_bookmarks[0]));
                CHECK(saved_bookmarks[1].same_url_as(initial_bookmarks[1]));
                CHECK(saved_bookmarks[2].same_url_as(new_bookmark));
            }
        }

        WHEN("I add an existing bookmark in Markdown format") {
            add_bookmark_to_file(initial_bookmarks[0], test_file);
            add_bookmark_to_file(initial_bookmarks[1], test_file);

            THEN("The stream contains only the initial bookmarks") {
                auto saved_bookmarks = read_bookmarks_from_file(test_file);
                CHECK_EQ(saved_bookmarks.size(), 2);
                CHECK(saved_bookmarks[0].same_url_as(initial_bookmarks[0]));
                CHECK(saved_bookmarks[1].same_url_as(initial_bookmarks[1]));
            }
        }
    }

}

#endif
