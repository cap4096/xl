#include "file_store.hh"
#include <stack>
#include <fstream>
#include <iostream>

namespace {
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

                case '#':  // Handle comment
                    ignoreRest = true;
                    break;

                default:
                    if(beginningOfLine) { start = c; }
                    beginningOfLine = false;
                    finish = c+1;
                    break;
            }
            column++;
        }

        r.line = std::string(start, finish);

        return r;
    }

}

void FileStore::addErrorMessage(std::shared_ptr<File> file, int line, int column, const std::string& message)
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


std::shared_ptr<File> FileStore::load(const std::string& filePath) {
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
            addErrorMessage(file, lineNo, tabCol, std::string("Tabs are not allowed."));
        }

        // Handle indentation level!
        if(lr.introSpaces != colStack.top()){
            if(lr.introSpaces>colStack.top()){
                colStack.push(lr.introSpaces);
            }else{
                while(lr.introSpaces>colStack.top()){
                    if(colStack.size()>0){
                        colStack.pop();
                    }
                    if(lr.introSpaces!=colStack.top()){
                        addErrorMessage(file, lineNo, lr.introSpaces, std::string("Invalid indentation."));
                    }
                }
            }
        }

        Line l;

        l.level = colStack.size()-1;
        l.line  = lr.line;

        file->lines.push_back(l);
    }

    return file;
}



namespace dbg {
    std::string dump(const Line& line) {
        return
            "{ level: " + dump(line.level) +
            ", line: " + dump(line.line) +
            " }";
    }

    std::string dump(const FileLocation& loc){
        return
            "{ file: " + dump(loc.file->filePath) +
            ", line: " + dump(loc.line) +
            ", column: " + dump(loc.column) +
            " }";
    }

    std::string dump(const File& file) {
        return
            "{ filePath: " + dump(file.filePath) +
            ", lines: " + dump(file.lines) +
            " }";
    }

    std::string dump(std::shared_ptr<File> file){
        return
            "{ filePath: " + dump(file->filePath) +
            ", lines: " + dump(file->lines) +
            " }";
    }


    std::string dump(const ErrorMessage& m) {
        return
            "{ location: " + dump(m.location) +
            ", message: " + dump(m.message) +
            "  }";
    }

    std::string dump(const LineResult& lr){
        return
           "{ introSpaces: " + dump(lr.introSpaces) +
           ", tabs: " + dump(lr.tabs) +
           ", line: " + dump(lr.line) +
            "  }";
    }

}
