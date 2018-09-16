#include <vector>
#include <map>
#include <string>
#include <memory>

#include "serialize.hh"

struct Line {
    int level;
    std::string line;
};

struct File {
    const std::string filePath;
    std::vector<Line> lines;

    File(const std::string& p_filePath) : filePath(p_filePath) {}
};


struct FileLocation {
    std::shared_ptr<File> file;
    int line;
    int column;
};

struct ErrorMessage {
    FileLocation location;
    std::string message;
};

struct FileStore{
    std::map<std::string, std::shared_ptr<File>> files;
    std::vector<ErrorMessage> errorMessages;

    void addErrorMessage(std::shared_ptr<File> file, int line, int column, const std::string& message);
    void load(const std::string& path);

};


namespace {
    std::string to_string(const Line& line) {
        return "{ level: " + to_string(line.level) + ", line: " + to_string(line.line) + " }";
    }

    std::string to_string(const FileLocation& loc){
        return 
            "{ file: " + to_string(loc.file->filePath) + 
            ", line: " + to_string(loc.line) + 
            ", column: " + to_string(loc.column) + 
            " }";
    }

    std::string to_string(const File& file) {
        return "{ filePath: " + file.filePath + ", lines: " + to_string(file.lines) + " }";
    }

    std::string to_string(const ErrorMessage& m) {
        return 
            "{ location: " + to_string(m.location) + 
            ", message: " + to_string(m.message) +
            "  }";
    }
}


