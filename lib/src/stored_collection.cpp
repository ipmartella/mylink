#include <stored_collection.h>

using namespace mylink;

StoredCollection::StoredCollection(StorageBackend &backend) : backend_{backend} { }

void StoredCollection::add(const Bookmark bookmark)
{
    std::vector<Bookmark> bookmarks = backend_.read_all();
    bookmarks.push_back(bookmark);
    backend_.write_all(bookmarks);
}
