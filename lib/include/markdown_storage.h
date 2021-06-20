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

    /**
     * @brief Loads a BookmarkCollection from Markdown.
     *
     * If the file is empty or it does not exist, this method returns an empty BookmarkCollection.
     *
     *
     * @return BookmarkCollection read from the file
     */
    BookmarkCollection load() override;

private:
    std::string filepath_;
};


} // namespace mylink

#endif // MARKDOWN_STORAGE_H
