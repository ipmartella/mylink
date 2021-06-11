#ifndef PARSER_IMPL_H
#define PARSER_IMPL_H

#include <memory>
#include <vector>
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
    std::string getOption(const std::string& short_option, const std::string& long_option, const std::string& default_value) const;

private:
    struct impl;
    std::unique_ptr<impl> impl_;
};

constexpr const char* option_title_long = "--title";
constexpr const char* option_title_short = "-t";

} //namespace impl
} //namespace mylink

#endif // PARSER_IMPL_H
