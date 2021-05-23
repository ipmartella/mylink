#ifndef PRIVATE_EXCEPTIONS_H
#define PRIVATE_EXCEPTIONS_H

#include <stdexcept>

namespace mylink::impl {

class invalid_command : public std::logic_error {
public:
    invalid_command() : std::logic_error{"Invalid syntax"} {};
};

}

#endif // PRIVATE_EXCEPTIONS_H
