#include <doctest.h>
#include <markdown_storage.h>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <envlib.h>

using namespace mylink;

namespace {

std::vector<std::string> read_lines_from_file(const std::string& filepath) {
    std::vector<std::string> lines;
    std::ifstream input_file{filepath};

    for(std::string line; std::getline(input_file, line, '\n');) {
        lines.push_back(line);
    }

    return lines;
}

void write_string_to_file(const std::string& filepath, const std::string& content) {
    std::ofstream output_file(filepath);
    output_file << content;
}

bool lines_contain_string(const std::vector<std::string>& lines, const std::string& line) {
    return std::find(lines.begin(), lines.end(), line) != lines.end();
}


} //namespace

SCENARIO("Reading BookmarkCollections from a file") {
    GIVEN("A non-existing file") {
        const std::string test_file = mylink::utils::get_system_temporary_directory() + "mylink_nonexisting";
        std::remove(test_file.c_str());

        WHEN("I load the BookmarkCollection") {
            auto collection = MarkdownStorageBackend(test_file).load();
            THEN("The BookmarkCollection is empty") {
                CHECK_EQ(collection.size(), 0);
            }
        }
    }

    GIVEN("A empty file") {
        const std::string empty_file = mylink::utils::get_system_temporary_directory() + "mylink_empty";
        std::ofstream{empty_file, std::ios_base::out | std::ios_base::trunc}; //Create file and write to it

        WHEN("I load the BookmarkCollection") {
            auto collection = MarkdownStorageBackend(empty_file).load();
            THEN("The BookmarkCollection is empty") {
                CHECK_EQ(collection.size(), 0);
            }
        }
    }

    GIVEN("A file containing different formats of bookmarks") {
        const std::string test_file_name = mylink::utils::get_system_temporary_directory() + "mylink_testload";
        {
            std::ofstream test_file{test_file_name, std::ios_base::out | std::ios_base::trunc};
            test_file << "# My bookmarks\n";
            test_file << "* http://www.url1.org\n";
            test_file << "- http://www.url2.org\n";
            test_file << "------------------------\n";
            test_file << "* [Title3](http://www.url3.org)\n";
            test_file << "- [Title4](http://www.url4.org)\n";
            test_file << "* www.url5.org\t\t\r\n";
            test_file << "\n";
            test_file << "     - www.url6.org";
            test_file.close();
        }

        WHEN("I load the BookmarkCollection") {
            auto collection = MarkdownStorageBackend(test_file_name).load();

            THEN("The BookmarkCollection contains the different Bookmarks") {
                CHECK_EQ(collection.size(), 6);
                CHECK(collection.contains("http://www.url1.org"));
                CHECK(collection.contains("http://www.url2.org"));
                CHECK_EQ(collection["http://www.url3.org"].get_title(), "Title3");
                CHECK_EQ(collection["http://www.url4.org"].get_title(), "Title4");
                CHECK(collection.contains("http://www.url5.org"));
                CHECK(collection.contains("http://www.url6.org"));
            }
        }
    }
}

SCENARIO("Writing BookmarkCollections to Markdown") {
    GIVEN("A empty BookmarkCollection") {
        const BookmarkCollection empty_collection;

        WHEN("I save the collection to a new file") {
            const std::string test_file = mylink::utils::get_system_temporary_directory() + "mylink_save1";
            std::remove(test_file.c_str());

            MarkdownStorageBackend(test_file).save(empty_collection);

            THEN("The file is empty") {
                auto lines = read_lines_from_file(test_file);
            }
        }
        WHEN("I save the collection to an existing file") {
            const std::string test_file = mylink::utils::get_system_temporary_directory() + "mylink_save1";
            write_string_to_file(test_file, "TEST TEST\n");

            MarkdownStorageBackend(test_file).save(empty_collection);

            THEN("The file is empty") {
                auto lines = read_lines_from_file(test_file);
            }
        }
    }

    GIVEN("A non-empty BookmarkCollection") {
        BookmarkCollection collection;
        std::vector<Bookmark> bookmarks = {
            Bookmark("http://www.url1.org"),
            Bookmark("http://www.url2.org"),
            Bookmark("http://www.url3.org", "Title 3"),
            Bookmark("http://www.url4.org", "Title [4]"),
        };

        for(const auto& bookmark : bookmarks) {
            collection.add(bookmark);
        }

        WHEN("I write the BookmarkCollection to a empty file") {
            const std::string test_file = mylink::utils::get_system_temporary_directory() + "mylink_save2";
            std::remove(test_file.c_str());

            MarkdownStorageBackend(test_file).save(collection);

            THEN("The Bookmarks are in the file") {
                auto lines = read_lines_from_file(test_file);
                CHECK_EQ(lines.size(), bookmarks.size());
                CHECK(lines_contain_string(lines, "- http://www.url1.org"));
                CHECK(lines_contain_string(lines, "- http://www.url2.org"));
                CHECK(lines_contain_string(lines, "- [Title 3](http://www.url3.org)"));
                CHECK(lines_contain_string(lines, R"(- [Title \[4\]](http://www.url4.org))"));
            }
        }

        WHEN("I write the BookmarkCollection to a non-empty file") {
            const std::string test_file = mylink::utils::get_system_temporary_directory() + "mylink_save3";
            write_string_to_file(test_file, "TEST TEST\n");

            MarkdownStorageBackend(test_file).save(collection);

            THEN("The Bookmarks are in the file") {
                auto lines = read_lines_from_file(test_file);
                CHECK_EQ(lines.size(), bookmarks.size());
                CHECK(lines_contain_string(lines, "- http://www.url1.org"));
                CHECK(lines_contain_string(lines, "- http://www.url2.org"));
                CHECK(lines_contain_string(lines, "- [Title 3](http://www.url3.org)"));
                CHECK(lines_contain_string(lines, R"(- [Title \[4\]](http://www.url4.org))"));
            }
        }
    }


}
