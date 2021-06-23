#ifndef PARSER_IMPL_H
#define PARSER_IMPL_H

#include <memory>
#include <vector>
#include <string>


namespace mylink {
namespace cli {

class CommandLineParameter {
public:
    CommandLineParameter(const std::string& short_version, const std::string long_version = "") : short_version_{short_version}, long_version_{long_version} {}
    std::string get_short_version() const { return short_version_; }
    std::string get_long_version() const { return long_version_; }
    bool has_long_version() const { return !long_version_.empty(); }

private:
    std::string short_version_;
    std::string long_version_;
};

using CommandLineFlag = CommandLineParameter;

class ParsedCommandLine
{
public:
    ParsedCommandLine(int argc, const char** argv, const std::vector<CommandLineParameter>& recognized_parameters = {});
    ~ParsedCommandLine();

    bool hasPositional(int index) const;
    bool hasParameter(const CommandLineParameter& parameter) const;
    bool hasFlag(const CommandLineFlag& flag) const;
    std::string getPositional(const size_t index) const;
    std::string getParameter(const CommandLineParameter& parameter, const std::string& default_value) const;

private:
    struct impl;
    std::unique_ptr<impl> impl_;
};

} //namespace cli
} //namespace mylink

#endif // PARSER_IMPL_H
