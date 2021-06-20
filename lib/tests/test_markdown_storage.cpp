#include <doctest.h>
#include <markdown_storage.h>
#include <fstream>

using namespace mylink;

SCENARIO("Reading BookmarkCollections from a file") {
    GIVEN("A non-existing file") {
        const std::string test_file = "/tmp/mylink_nonexisting";
        std::remove(test_file.c_str());

        WHEN("I load the BookmarkCollection") {
            auto collection = MarkdownStorageBackend(test_file).load();
            THEN("The BookmarkCollection is empty") {
                CHECK_EQ(collection.size(), 0);
            }
        }
    }

    GIVEN("A empty file") {
        const std::string empty_file = "/tmp/mylink_empty";
        std::ofstream{empty_file, std::ios_base::out | std::ios_base::trunc}; //Create file and write to it

        WHEN("I load the BookmarkCollection") {
            auto collection = MarkdownStorageBackend(empty_file).load();
            THEN("The BookmarkCollection is empty") {
                CHECK_EQ(collection.size(), 0);
            }
        }
    }
}
