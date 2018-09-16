#include <string>
#include <variant>
#include <memory>
#include <vector>
#include <map>
#include <stack>

#include <fstream>


struct Line {
    int level;
    std::string line;
};

static inline std::string to_string(const Line& line)
{
    return "level: " + std::to_string(line.level) + ", line: \"" + line.line + "\"";
}

struct File {
    const std::string filePath;
    std::vector<Line> lines;

    File(const std::string& p_filePath) : filePath(p_filePath) {}
};

static inline std::string to_string(const File& file)
{
    return "{ filePath: " + file.filePath + ", lines: " + to_string(file.lines) + " }";
}

struct FileLocation {
    std::shared_ptr<File> file;
    int line;
    int column;
};

struct ErrorMessage {
    FileLocation location;
    std::string message;
};


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



File load(const std::string& filePath);

File load(const std::string& filePath)
{
    while(!inFile.eof()){
        std::getline(inFile, line);

        bool ignoreRest = false;
        bool beginningOfTheLine = true;
        int  spaceCount = 0;


        for(auto c : line){
            if(!ignoreRest){
                switch(c){
                    case ' ': // Whilespace
                    if(beginningOfTheLine){
                        spaceCount++;
                    }
                    break;

                    case '#': // Comment, ignore rest of line. 
                    beginningOfTheLine = false;
                    ignoreRest = true;
                    break;

                    case '\t': // Tab is not allowed!
                    break;

                    default:
                    if(beginningOfTheLine){
                        if(spaceCount!=colStack.top()){
                            if(spaceCount>colStack.top()){
                                colStack.push(spaceCount);
                            }else{
                                colStack.pop();
                                if(colStack.top()!=spaceCount){

                                }

                            }
                        }

                        beginningOfTheLine = false;
                    }
                    beginningOfTheLine = false;
                    break;
                }
            }
        }

        file.lines.push_back(line);
    }

    return file;
}









enum class TokenType : int {
    INVALID,
    LIT_STRING,
    LIT_FLOAT,
    LIT_INTEGER
};

using TokenValue = std::variant<std::string, float, int>;

struct Token
{ 
    TokenType type;
    TokenValue value;
};

struct TokenizerResult {
    bool  succes;
    Token token;
};