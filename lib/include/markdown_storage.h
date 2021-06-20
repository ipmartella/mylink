#ifndef MARKDOWN_STORAGE_H
#define MARKDOWN_STORAGE_H

#include <collection_storage.h>

namespace mylink {

/**
 * @brief Stores and loads a BookmarkCollection to/from a given Markdown file.
 */
class MarkdownStorageBackend : public BookmarkCollectionStorageBackend {
public:
    MarkdownStorageBackend(const std::string& filepath);

    void save(const BookmarkCollection &collection) override;
    BookmarkCollection load() override;

private:
    /**
     * @brief Path of the Markdown file to be used for loading/saving BookmarkCollections
     */
    std::string filepath_;
};


} // namespace mylink

#endif // MARKDOWN_STORAGE_H
