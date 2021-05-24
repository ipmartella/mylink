#include "ram_storage.h"

RamStorage::RamStorage(std::vector<mylink::Bookmark> initial_bookmarks) : bookmarks_{initial_bookmarks}
{}

std::vector<mylink::Bookmark> RamStorage::read_all() const
{
    return bookmarks_;
}

void RamStorage::write_all(std::vector<mylink::Bookmark> bookmarks)
{
    bookmarks_ = bookmarks;
}

std::vector<mylink::Bookmark>& RamStorage::data()
{
    return bookmarks_;
}

const std::vector<mylink::Bookmark>& RamStorage::data() const
{
    return bookmarks_;
}
