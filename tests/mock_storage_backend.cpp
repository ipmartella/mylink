#include "mock_storage_backend.h"

using namespace mylink;


test::MockStorageBackend::MockStorageBackend(const BookmarkCollection &initial_collection) :
    mylink::BookmarkCollectionStorageBackend{},
    collection_{initial_collection}
{}

void mylink::test::MockStorageBackend::save(const BookmarkCollection &collection)
{
    collection_ = collection;
}

BookmarkCollection test::MockStorageBackend::load()
{
    return collection_;
}

void test::MockStorageBackend::reset()
{
    collection_ = BookmarkCollection{};
}
