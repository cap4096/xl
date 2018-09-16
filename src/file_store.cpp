#include "file_store.hh"
#include <stack>
#include <fstream>

namespace {
    struct LineResult {
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

                case '#':  // Handle comment
                    ignoreRest = true;
                    break;

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


void FileStore::load(const std::string& filePath) {
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
                colStack.pop();
                if(lr.introSpaces!=colStack.top()){
                    addErrorMessage(file, lineNo, lr.introSpaces, std::string("Invalid indentation."));
                }
            }
        }            
    }
}

