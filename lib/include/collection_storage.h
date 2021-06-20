#ifndef COLLECTION_STORAGE_H
#define COLLECTION_STORAGE_H
#include <collection.h>

namespace mylink {

/**
 * @brief Interface for all BookmarkCollection Storage Backends
 *
 * You can use a BookmarkCollection Storage Backend to save/load BookmarkCollections to/from persistent storage (such as a disk file, or a database).
 *
 */
class BookmarkCollectionStorageBackend {
public:
    virtual void save(const BookmarkCollection& collection) = 0;
    virtual BookmarkCollection load() = 0;

    ~BookmarkCollectionStorageBackend() = default;
};

} //namespace mylink


#endif // COLLECTION_STORAGE_H
