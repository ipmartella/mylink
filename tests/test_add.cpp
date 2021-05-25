#include "doctest.h"
#include "utils/ram_storage.h"
#include <sstream>
#include <stored_collection.h>

using namespace mylink;

struct TestCollection {
    TestCollection(std::vector<Bookmark> initial_bookmarks = {}) : storage{initial_bookmarks}, collection{storage} {}
    size_t size() const { return storage.data().size(); }
    bool contains_bookmark(Bookmark target) const
    {
        for(const auto& bookmark : storage.data() ) {
            if(bookmark.same_url_as(target)){
                return true;
            }
        }
        return false;
    }
    bool contains_bookmarks(std::vector<Bookmark> targets) const
    {
        for(const auto& bookmark : targets) {
            if (!contains_bookmark(bookmark)) {
                return false;
            }
        }
        return true;
    }

    void add_bookmark(Bookmark bookmark) { collection.add(bookmark); }

    RamStorage storage;
    StoredCollection collection;
};


SCENARIO("Add bookmark to collection") {

    GIVEN("An empty collection") {
        TestCollection test_collection;

        WHEN("I add a bookmark") {
            Bookmark new_bookmark{"https://www.wikipedia.org"};
            test_collection.add_bookmark(new_bookmark);

            THEN("The collection contains only the new bookmark") {
                CHECK_EQ(test_collection.size(), 1);
                CHECK(test_collection.contains_bookmark(new_bookmark));
            }
        }
    }

    GIVEN("An existing collection") {
        std::vector<Bookmark> existing_bookmarks {
            Bookmark{"https://www.wikipedia.org"},
            Bookmark{"https://en.cppreference.com"}
        };

        TestCollection test_collection{existing_bookmarks};

        WHEN("I add a new bookmark") {
            Bookmark new_bookmark{"https://isocpp.github.io/"};
            test_collection.add_bookmark(new_bookmark);

            THEN("The collection contains new bookmark and the old ones") {
                CHECK_EQ(test_collection.size(), existing_bookmarks.size() + 1);
                CHECK(test_collection.contains_bookmark(new_bookmark));
                CHECK(test_collection.contains_bookmarks(existing_bookmarks));
            }
        }

        WHEN("I add an existing bookmark")
        {
            Bookmark existing_bookmark = existing_bookmarks.at(0);
            test_collection.add_bookmark(existing_bookmark);

            THEN("The collection stays the same")
            {
                CHECK_EQ(test_collection.size(), existing_bookmarks.size());
                CHECK(test_collection.contains_bookmarks(existing_bookmarks));
            }
        }
    }
}
