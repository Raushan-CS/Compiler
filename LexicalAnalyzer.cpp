#include <iostream>
#include <string>
#include <regex>

enum TokenType {
    KEYWORD,
    IDENTIFIER,
    CONSTANT,
    OPERATOR,
    SPECIAL_SYMBOL,
    INVALID
};

struct Token {
    TokenType type;
    std::string value;
};

TokenType getTokenType(const std::string& token) {
    std::regex keywordRegex("(auto|break|case|char|const|continue|default|do|double|else|enum|extern|float|for|goto|if|int|long|register|return|short|signed|sizeof|static|struct|switch|typedef|union|unsigned|void|volatile|while)\\b");
    std::regex identifierRegex("[a-zA-Z_][a-zA-Z0-9_]*");
    std::regex constantRegex("\\b(\\d+\\.\\d*|\\d*\\.\\d+|\\d+)[fF]?|[0-9]+");
    std::regex operatorRegex("[\\+\\-\\*/%=&|\\^<>!]");
    std::regex specialSymbolRegex("[\\(\\)\\{\\}\\[\\];,]");

    if (std::regex_match(token, keywordRegex)) return KEYWORD;
    if (std::regex_match(token, identifierRegex)) return IDENTIFIER;
    if (std::regex_match(token, constantRegex)) return CONSTANT;
    if (std::regex_match(token, operatorRegex)) return OPERATOR;
    if (std::regex_match(token, specialSymbolRegex)) return SPECIAL_SYMBOL;
    return INVALID;
}

void analyzeTokens(const std::string& input) {
    std::istringstream iss(input);
    std::string token;
    while (iss >> token) {
        TokenType type = getTokenType(token);
        std::string typeName;
        switch (type) {
            case KEYWORD:
                typeName = "Keyword";
                break;
            case IDENTIFIER:
                typeName = "Identifier";
                break;
            case CONSTANT:
                typeName = "Constant";
                break;
            case OPERATOR:
                typeName = "Operator";
                break;
            case SPECIAL_SYMBOL:
                typeName = "Special Symbol";
                break;
            case INVALID:
                typeName = "Invalid";
                break;
        }
        std::cout << "Token: " << token << ", Type: " << typeName << std::endl;
    }
}

int main() {
    std::string input = "int main() { return 0; }";
    analyzeTokens(input);
    return 0;
}
