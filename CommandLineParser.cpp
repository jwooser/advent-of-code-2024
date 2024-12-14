#include "CommandLineParser.h"
#include <string>

CommandLineParser::CommandLineParser(int argc, const char** argv) :
	mBegin{ argv }, mEnd{ argc + argv } {}

std::string_view CommandLineParser::getCmdOption(std::string_view option) const {
    auto itr = std::find(mBegin, mEnd, option);
    if (itr != mEnd && ++itr != mEnd) {
        return *itr;
    }
    return "";
}

std::string_view CommandLineParser::getCmdOptionOrDefaultVal(std::string_view option, std::string_view defaultVal) const {
    auto val = getCmdOption(option);
    if (val == "") {
        return defaultVal;
    }
    return val;
}

bool CommandLineParser::cmdOptionExists(std::string_view option) const {
    return std::find(mBegin, mEnd, option) != mEnd;
}
