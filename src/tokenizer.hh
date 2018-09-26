#include <string>
#include <variant>
#include <memory>
#include <vector>
#include <map>
#include <stack>

#include <fstream>

enum class TokenType : int {
    INVALID,
    SPACE,
    BEGIN,
    END,
    LIT_STRING,
    LIT_FLOAT,
    LIT_INTEGER
};

using TokenValue = std::variant<std::string, float, int>;

struct Token
{
    TokenType type;
    std::string value;
};
