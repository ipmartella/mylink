#include <stored_collection.h>

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

} //namespace

StoredCollection::StoredCollection(StorageBackend &backend) : backend_{backend} { }

void StoredCollection::add(const Bookmark bookmark)
{
    std::vector<Bookmark> bookmarks = backend_.read_all();
    if (!bookmark_in_collection(bookmark, bookmarks)) {
        bookmarks.push_back(bookmark);
        backend_.write_all(bookmarks);
    }
}
