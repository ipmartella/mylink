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
    /**
     * @brief Stores the given BookmarkCollection to permanent storage.
     * @param collection Collection to store
     */
    virtual void save(const BookmarkCollection& collection) = 0;

    /**
     * @brief Loads a BookmarkCollection from permanent storage.
     * @return Collection loaded from permanent storage
     */
    virtual BookmarkCollection load() = 0;

    ~BookmarkCollectionStorageBackend() = default;
};

} //namespace mylink


#endif // COLLECTION_STORAGE_H
