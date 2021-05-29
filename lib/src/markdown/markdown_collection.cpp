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

void add_bookmark_to_stream(const Bookmark& bookmark, std::iostream& stream) {
    std::vector<Bookmark> bookmarks = read_bookmarks_from_stream(stream);
    if (!bookmark_in_collection(bookmark, bookmarks)) {
        bookmarks.push_back(bookmark);
        write_bookmarks_to_stream(bookmarks, stream);
    }
}

} //namespace

MarkdownCollection::MarkdownCollection(const std::string& markdown_file_name) : filename_{markdown_file_name} {}

void MarkdownCollection::add(const Bookmark& bookmark)
{
    std::fstream stream(filename_);
    add_bookmark_to_stream(bookmark, stream);
}

#ifdef MYLINK_TEST_IN_CODE
#include <doctest.h>
#include <sstream>

SCENARIO("Read and write from a stream") {

    GIVEN("A empty stream") {
        std::stringstream stream;

        WHEN("I write something")
        {
            stream << "pippo";
            THEN("I can read that back"){
                std::string content;
                stream >> content;
                CHECK_EQ(content, "pippo");
            }
        }
    }

    GIVEN("A populated stream") {
        std::stringstream stream;
        stream << "Pippo\n";
        stream << "Pluto\n";

        WHEN("I read everything")
        {
            std::string line;
            while(std::getline(stream, line, '\n')) {
                //Do nothing
            }

            AND_WHEN("I write something later") {
                stream.clear();
                stream << "pippo";
                THEN("I can read that back"){
                    std::string content;
                    stream >> content;
                    CHECK_EQ(content, "pippo");
                }
            }
        }
    }
}

SCENARIO("Adding bookmarks to streams") {

    GIVEN("A empty stream") {
        std::stringstream stream;

        WHEN("I add a bookmark in Markdown format") {
            Bookmark new_bookmark{"http://www.wikipedia.org"};
            add_bookmark_to_stream(new_bookmark, stream);

            THEN("The stream contains the bookmark") {
                auto saved_bookmarks = read_bookmarks_from_stream(stream);
                CHECK_EQ(saved_bookmarks.size(), 1);
                CHECK_EQ(saved_bookmarks[0].get_url(), "http://www.wikipedia.org");
            }
        }
    }

    GIVEN("A populated stream") {
        std::stringstream stream;
        std::vector<Bookmark> initial_bookmarks{
            Bookmark("http://www.wikipedia.org"),
            Bookmark("http://www.myurl.org"),
        };
        write_bookmarks_to_stream(initial_bookmarks, stream);

        WHEN("I add a new bookmark in Markdown format") {
            Bookmark new_bookmark{"http://www.test.org"};
            add_bookmark_to_stream(new_bookmark, stream);

            THEN("The stream contains the bookmark + all the previous ones") {
                auto saved_bookmarks = read_bookmarks_from_stream(stream);
                CHECK_EQ(saved_bookmarks.size(), 3);
                CHECK(saved_bookmarks[0].same_url_as(initial_bookmarks[0]));
                CHECK(saved_bookmarks[1].same_url_as(initial_bookmarks[1]));
                CHECK(saved_bookmarks[2].same_url_as(new_bookmark));
            }
        }

        WHEN("I add an existing bookmark in Markdown format") {
            add_bookmark_to_stream(initial_bookmarks[0], stream);
            add_bookmark_to_stream(initial_bookmarks[1], stream);

            THEN("The stream contains only the initial bookmarks") {
                auto saved_bookmarks = read_bookmarks_from_stream(stream);
                CHECK_EQ(saved_bookmarks.size(), 2);
                CHECK(saved_bookmarks[0].same_url_as(initial_bookmarks[0]));
                CHECK(saved_bookmarks[1].same_url_as(initial_bookmarks[1]));
            }
        }
    }

}

#endif
