#ifndef STORAGE_BACKEND_H
#define STORAGE_BACKEND_H

#include <vector>
#include <bookmark.h>


namespace mylink {

class StorageBackend {
public:
    virtual std::vector<Bookmark> read_all() const = 0;
    virtual void write_all(std::vector<Bookmark> bookmarks) = 0;
    virtual ~StorageBackend() = default;
};

} //namespace mylink

#endif // STORAGE_BACKEND_H
