#include "parser_impl.h"
#include <argh.h>

using namespace mylink::cli;

namespace {

auto get_parameter(argh::parser& parser, const CommandLineParameter& parameter) {
    if(parameter.has_long_version()) {
        return parser({parameter.get_short_version()});
    } else {
        return parser({parameter.get_short_version().c_str(), parameter.get_long_version().c_str()});
    }
}

auto get_parameter(argh::parser& parser, const CommandLineParameter& parameter, const std::string& default_value) {
    if(parameter.has_long_version()) {
        return parser({parameter.get_short_version()}, default_value);
    } else {
        return parser({parameter.get_short_version().c_str(), parameter.get_long_version().c_str()}, default_value);
    }
}

auto get_flag(argh::parser& parser, const CommandLineFlag& flag) {
    if(flag.has_long_version()) {
        return parser[flag.get_short_version()];
    } else {
        return parser[{flag.get_short_version().c_str(), flag.get_long_version().c_str()}];
    }
}


} //namespace

struct ParsedCommandLine::impl
{
    argh::parser arg_parser;
};

ParsedCommandLine::ParsedCommandLine(int argc, const char** argv, const std::vector<CommandLineParameter>& recognized_parameters)
    : impl_(std::make_unique<ParsedCommandLine::impl>())
{
    for(const auto& parameter : recognized_parameters) {
        impl_->arg_parser.add_param(parameter.get_short_version());
        if(parameter.has_long_version()) {
            impl_->arg_parser.add_param(parameter.get_long_version());
        }
    }

    impl_->arg_parser.parse(argc, argv);
}

ParsedCommandLine::~ParsedCommandLine() = default;

bool ParsedCommandLine::hasPositional(int index) const
{
    return static_cast<bool>(impl_->arg_parser(index));
}

bool ParsedCommandLine::hasParameter(const CommandLineParameter& parameter) const
{
    return static_cast<bool>(get_parameter(impl_->arg_parser, parameter));
}

bool ParsedCommandLine::hasFlag(const CommandLineFlag &flag) const
{
    return get_flag(impl_->arg_parser, flag);
}

std::string ParsedCommandLine::getPositional(const size_t index) const
{
    if (hasPositional(index)) {
        return impl_->arg_parser[index];
    } else {
        throw std::out_of_range("Positional not available");
    }
}

std::string ParsedCommandLine::getParameter(const CommandLineParameter& parameter,
                                            const std::string& default_value) const
{
    return get_parameter(impl_->arg_parser, parameter, default_value).str();
}
