#include <vector>
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




struct LineResult 
{
    std::vector<int> tabs;
    int introSpaces = 0;
    std::string line;
};

LineResult extractLine(const std::string& line)
{
    LineResult r;

    auto start   = line.cend();
    auto finish  = line.cend();

    auto beginningOfLine = true;
    auto ignoreRest = false;
    
    int  column = 0;

    for(auto c = line.cbegin(); c!=line.cend();++c){
        if(ignoreRest) break;

        switch(*c){
            case ' ':   if(beginningOfLine) { r.introSpaces++; } break;
            case '\t':  // Handle tabs!
                r.tabs.push_back(column); 
                break;

            case '#' ignoreRest = true;

            default:
                if(beginningOfLine) { start = c; }
                beginningOfLine = false;
                finish = c;
                break;
        }
        column++;
    }

    r.line = std::string(start, finish);

    return r;
}


struct FileStore {
    std::map<std::string, std::shared_ptr<File>> files;
    std::vector<ErrorMessage> errorMessages;

    void addFile(const std::string& filePath){
        auto file = std::make_shared<File>;
        files.insert_or_assign(filePath, file);
    }

    void addErrorMessage(std::shared_ptr<File> file, int line, int column, const std::string& message)
    {
        FileLocation loc;

        loc.file = file;
        loc.line = line;
        loc.column = column;

        ErrorMessage m;

        m.location = loc;
        m.message = message;

        errorMessages.push_back(m);
    }

    void load(const std::string& filePath)
    {
        auto file = std::make_shared<File>(filePath);
        std::stack<int> colStack; colStack.push(0);
        std::ifstream inFile(filePath);
        int lineNo = 0;

        while(!inFile.eof()){
            lineNo++;

            std::string line;
            std::getline(inFile, line);

            auto lr = extractLine(line);

            // Tabs are errors.
            for(auto tabCol : lr.tabs){
                addErrorMessage(filePath, lineNo, tabCol, "Tabs are not allowed.");
            }

            // Handle indentation level!
            if(lr.introSpaces != colStack.top()){
                if(lr.introSpaces>colStack.top()){
                    colStack.push(lr.introSpaces);
                }else{
                    colStack.pop();
                    if(lr.introSpaces!=colStack.top()){
                        addErrorMessage(filePath, lineNo, lr.introSpaces, "Invalid indentation.");
                    }
                }
            }            
        }


    }
};

