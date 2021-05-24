#include "doctest.h"
#include <sstream>
#include <stored_collection.h>
#include "utils/ram_storage.h"

using namespace mylink;

struct TestCollection {
    TestCollection(std::vector<Bookmark> initial_bookmarks = {}) : storage{initial_bookmarks}, collection{storage} {}
    size_t size() const { return storage.data().size(); }
    bool containsBookmark(Bookmark target) const {
        for(const auto& bookmark : storage.data() ) {
            if(bookmark.url == target.url) {
                return true;
            }
        }
        return false;
    }
    bool containsBookmarks(std::vector<Bookmark> targets) const {
        for(const auto& bookmark : targets) {
            if(!containsBookmark(bookmark)) {
                return false;
            }
        }
        return true;
    }

    RamStorage storage;
    StoredCollection collection;
};


SCENARIO("Add bookmark to collection") {

    GIVEN("An empty collection") {
        TestCollection test_collection;

        WHEN("I add a bookmark") {
            Bookmark new_bookmark{"https://www.wikipedia.org"};
            test_collection.collection.add(new_bookmark);

            THEN("The collection contains only the new bookmark") {
                CHECK_EQ(test_collection.size(), 1);
                CHECK(test_collection.containsBookmark(new_bookmark));
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
            test_collection.collection.add(new_bookmark);

            THEN("The collection contains new bookmark and the old ones") {
                CHECK_EQ(test_collection.size(), existing_bookmarks.size() + 1);
                CHECK(test_collection.containsBookmark(new_bookmark));
            }

        }

    }

}

TEST_CASE("Add an existing link to a collection") {
    //Given: an existing collection

    //When: I add a link that already exists

    //Then: The link is not added to the collection
}
