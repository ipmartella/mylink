#include "mock_storage_backend.h"

using namespace mylink;


test::MockStorageBackend::MockStorageBackend(const BookmarkCollection &initial_collection) :
    mylink::BookmarkCollectionStorageBackend{},
    saved_collection_{nullptr},
    loaded_collection_{std::make_shared<BookmarkCollection>(initial_collection)}
{}

void mylink::test::MockStorageBackend::save(const BookmarkCollection &collection)
{
    saved_collection_ = std::make_shared<BookmarkCollection>(collection);
}

BookmarkCollection test::MockStorageBackend::load()
{
    return *loaded_collection_;
}

void test::MockStorageBackend::reset()
{
    saved_collection_.reset();
    loaded_collection_.reset();
}

std::shared_ptr<BookmarkCollection> test::MockStorageBackend::get_saved_collection() const
{
    return saved_collection_;
}

void test::MockStorageBackend::set_loaded_collection(const BookmarkCollection &collection)
{
    loaded_collection_ = std::make_shared<BookmarkCollection>(BookmarkCollection{collection});
}
