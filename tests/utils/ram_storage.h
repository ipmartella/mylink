#ifndef RAMSTORAGE_H
#define RAMSTORAGE_H

#include <storage_backend.h>

class RamStorage : public mylink::StorageBackend
{
public:
    RamStorage(std::vector<mylink::Bookmark> initial_bookmarks);
    std::vector<mylink::Bookmark> read_all() const override;
    void write_all(std::vector<mylink::Bookmark> bookmarks) override;

    std::vector<mylink::Bookmark>& data();
    const std::vector<mylink::Bookmark>& data() const;
    ~RamStorage() = default;
private:
    std::vector<mylink::Bookmark> bookmarks_;
};

#endif // RAMSTORAGE_H
