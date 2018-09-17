#ifndef C4A6CFD7_6133_EFA5_647A_7D5E916F196D
#define C4A6CFD7_6133_EFA5_647A_7D5E916F196D
#include <vector>
#include <map>
#include <string>
#include <memory>

#include "gtypes.hh"

struct LineResult {
        std::vector<int> tabs;
        int introSpaces = 0;
        std::string line;
};

struct Line {
    int level;
    std::string line;
};

struct File {
    const std::string filePath;
    std::vector<Line> lines;

    File(const std::string& p_filePath) :
        filePath(p_filePath) {}
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
    std::shared_ptr<File> load(const std::string& path);

};

#endif /* C4A6CFD7_6133_EFA5_647A_7D5E916F196D */
