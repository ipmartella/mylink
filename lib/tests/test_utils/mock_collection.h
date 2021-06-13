#ifndef MOCK_COLLECTION_H
#define MOCK_COLLECTION_H
#include "collection.h"

namespace mylink {
namespace test {

class MockCollection : public Collection {
public:
    void add(const Bookmark& bookmark) override {
        add_calls_.push_back(bookmark);
    }
    size_t size() const override { return 0; }

    const std::vector<Bookmark>& readAddCalls() { return add_calls_; }

private:
    std::vector<Bookmark> add_calls_;
};

} //namespace test
} //namespace mylink

#endif // MOCK_COLLECTION_H
