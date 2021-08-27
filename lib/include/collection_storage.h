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

    /**
     * @brief Sets the storage path for this BookmarkCollectionStorageBackend.
     *
     * The meaning of the <path> depends on the specific backend.
     *
     * @param path Path to be used by this BookmarkCollectionStorageBackend.
     */
    virtual void set_path(const std::string& path) = 0;

    /**
     * @brief Gets the storage path for this BookmarkCollectionStorageBackend.
     *
     * The meaning of the <path> depends on the specific backend.
     *
     * @return the path used by this BookmarkCollectionStorageBackend.
     */
    virtual std::string get_path() const = 0;

    ~BookmarkCollectionStorageBackend() = default;
};

} //namespace mylink


#endif // COLLECTION_STORAGE_H
