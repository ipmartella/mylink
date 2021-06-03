#ifndef MOCK_COLLECTION_H
#define MOCK_COLLECTION_H
#include "collection.h"

namespace mylink {
namespace test {

class MockCollection : public Collection {
public:
    virtual void add(const Bookmark& bookmark) override {
        add_calls_.push_back(bookmark);
    }

    const std::vector<Bookmark>& readAddCalls() { return add_calls_; }

private:
    std::vector<Bookmark> add_calls_;
};

} //namespace test
} //namespace mylink

#endif // MOCK_COLLECTION_H
