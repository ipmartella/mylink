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
    std::shared_ptr<mylink::BookmarkCollection> get_saved_collection() const;
    void set_loaded_collection(const BookmarkCollection& collection);


    ~MockStorageBackend() = default;



private:
    std::shared_ptr<mylink::BookmarkCollection> saved_collection_ = nullptr;
    std::shared_ptr<mylink::BookmarkCollection> loaded_collection_ = nullptr;
};

} //namespace test
} //namespace mylink

#endif // MOCK_STORAGE_BACKEND_H
