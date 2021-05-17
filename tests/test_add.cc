#include "doctest.h"
#include <sstream>
#include "markdown_collection.hpp"

using namespace mylink;


TEST_CASE("Add a link, to a empty collection") {
    //Given: an empty collection

    //When: I add a new link

    //Then: The collection contains the link

    //And Then: Nothing else
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
