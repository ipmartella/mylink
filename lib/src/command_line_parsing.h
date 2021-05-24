#ifndef COMMAND_LINE_PARSING_H
#define COMMAND_LINE_PARSING_H

#include <memory>
#include <string>

namespace mylink {
namespace impl {

class ParsedCommandLine
{
public:
    ParsedCommandLine(int argc, const char** argv);
    ~ParsedCommandLine();

    bool hasPositional(int index) const;
    bool hasOption(const std::string& option) const;
    std::string getPositional(const size_t index) const;
    std::string getOption(const std::string& option, const std::string& default_value) const;

private:
    struct impl;
    std::unique_ptr<impl> impl_;
};

} //namespace impl
} //namespace mylink

#endif // COMMAND_LINE_PARSING_H