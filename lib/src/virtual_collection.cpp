#include <virtual_collection.h>

using namespace mylink;

VirtualCollection::VirtualCollection() : bookmarks_{} {}

void VirtualCollection::add(const Bookmark &bookmark) {
    bookmarks_.push_back(bookmark);
}
