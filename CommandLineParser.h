#pragma once

#include <string_view>
#include <algorithm>

class CommandLineParser {
public:
    CommandLineParser(int argc, const char** argv);

    std::string_view getCmdOption(std::string_view option) const;
    
    std::string_view getCmdOptionOrDefaultVal(std::string_view option, std::string_view defaultVal) const;

    bool cmdOptionExists(std::string_view option) const;

private:
    const char** mBegin;
    const char** mEnd;
};
