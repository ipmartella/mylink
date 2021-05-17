#ifndef COMMANDLINEPARSER_HPP
#define COMMANDLINEPARSER_HPP


namespace mylink {
class CommandLineParser
{
public:
    CommandLineParser();
    void parse(int argc, char** argv);
};

} //namespace mylink

#endif // COMMANDLINEPARSER_HPP
