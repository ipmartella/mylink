#ifndef MOCK_STORAGE_BACKEND_H
#define MOCK_STORAGE_BACKEND_H

#include <collection_storage.h>
#include <memory>

namespace mylink {
namespace test {


class MockStorageBackend : public mylink::BookmarkCollectionStorageBackend
{
public:
    MockStorageBackend(const BookmarkCollection& initial_collection = BookmarkCollection{});
    void save(const mylink::BookmarkCollection &collection) override;
    mylink::BookmarkCollection load() override;
    void reset();

    ~MockStorageBackend() = default;

private:
    mylink::BookmarkCollection collection_;
};

} //namespace test
} //namespace mylink

#endif // MOCK_STORAGE_BACKEND_H
