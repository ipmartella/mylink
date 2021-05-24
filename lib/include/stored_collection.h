#ifndef STOREDCOLLECTION_HPP
#define STOREDCOLLECTION_HPP
#include <vector>
#include <string>
#include <collection.h>
#include <storage_backend.h>

namespace mylink {

class StoredCollection : public Collection
{
public:
    explicit StoredCollection(StorageBackend& backend);
    void add(const Bookmark bookmark);

    ~StoredCollection() = default;

private:
    StorageBackend& backend_;
};

} //namespace mylink

#endif // STOREDCOLLECTION_HPP
