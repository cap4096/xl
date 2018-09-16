#include <string>
#include "serialize.hh"

struct Line {
    int level;
    std::string line;
};


namespace {
    std::string to_string(const Line& line) {
        return "level: " + to_string(line.level) + ", line: \"" + line.line + "\"";
    }
}
