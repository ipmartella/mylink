#ifndef MARKDOWN_STORAGE_H
#define MARKDOWN_STORAGE_H

#include <collection_storage.h>

namespace mylink {

/**
 * @brief Stores and loads BookmarkCollection objects to Markdown files.
 *
 */
class MarkdownStorageBackend : public BookmarkCollectionStorageBackend {
public:
    /**
     * @brief Construct a new MarkdownStorageBackend, backed by a disk file named <filepath>.
     * @param filepath Path of the Markdown file to save/load. The path must be accessible by the running process.
     */
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
