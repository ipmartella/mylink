#include "parser_impl.h"
#include <argh.h>

using namespace mylink::impl;

struct ParsedCommandLine::impl
{
    argh::parser arg_parser;
};

ParsedCommandLine::ParsedCommandLine(int argc, const char** argv)
    : impl_(std::make_unique<ParsedCommandLine::impl>())
{
    impl_->arg_parser.add_params({option_title_short, option_title_long});
    impl_->arg_parser.parse(argc, argv);
}

ParsedCommandLine::~ParsedCommandLine() = default;

bool ParsedCommandLine::hasPositional(int index) const
{
    return static_cast<bool>(impl_->arg_parser(index));
}

bool ParsedCommandLine::hasOption(const std::string& option) const
{
    return static_cast<bool>(impl_->arg_parser(option));
}

std::string ParsedCommandLine::getPositional(const size_t index) const
{
    if (hasPositional(index)) {
        return impl_->arg_parser[index];
    } else {
        throw std::out_of_range("Positional not available");
    }
}

std::string ParsedCommandLine::getOption(const std::string& option,
                                         const std::string& default_value) const
{
    return impl_->arg_parser(option, default_value).str();
}

std::string ParsedCommandLine::getOption(const std::string& short_option, const std::string& long_option,
                                         const std::string& default_value) const
{
    return impl_->arg_parser({short_option.c_str(), long_option.c_str()}, default_value).str();
}
