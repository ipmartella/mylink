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

    RamStorage storage;
    StoredCollection collection;
};


SCENARIO("Add bookmark to collection") {

    GIVEN("An empty collection") {
        TestCollection test_collection;

        WHEN("I add a bookmark") {
            Bookmark new_bookmark{"http://www.wikipedia.org"};
            test_collection.collection.add(new_bookmark);

            THEN("The collection contains only the new bookmark") {
                CHECK_EQ(test_collection.size(), 1);
                CHECK(test_collection.containsBookmark(new_bookmark));
            }
        }
    }
}

TEST_CASE("Add a new link, to an existing collection") {
    //Given: an existing collection

    //When: I add a new link

    //Then: The link is added to the collection
}

TEST_CASE("Add an existing link to a collection") {
    //Given: an existing collection

    //When: I add a link that already exists

    //Then: The link is not added to the collection
}
