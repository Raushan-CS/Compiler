#include <iostream>
#include <string>

class PEGParser {
public:
    PEGParser(const std::string& input) : input(input), index(0) {}

    bool parse() {
        // Start parsing from the beginning of the input
        index = 0;
        return parseExpression();
    }

private:
    std::string input;
    size_t index;

    // Helper function to check if the current character is whitespace
    bool isWhitespace(char c) const {
        return (c == ' ' || c == '\t' || c == '\n' || c == '\r');
    }

    // Helper function to consume whitespace characters
    void consumeWhitespace() {
        while (index < input.size() && isWhitespace(input[index])) {
            index++;
        }
    }

    // Helper function to consume a specific character if it matches the current input character
    bool consume(char expected) {
        if (index < input.size() && input[index] == expected) {
            index++;
            return true;
        }
        return false;
    }

    // PEG grammar rules implementation
    bool parseExpression() {
        // Expression = Term ( '+' Term )*
        if (!parseTerm()) {
            return false;
        }
        while (consume('+')) {
            if (!parseTerm()) {
                return false;
            }
        }
        return true;
    }

    bool parseTerm() {
        // Term = Factor ( '*' Factor )*
        if (!parseFactor()) {
            return false;
        }
        while (consume('*')) {
            if (!parseFactor()) {
                return false;
            }
        }
        return true;
    }

    bool parseFactor() {
        // Factor = Number | '(' Expression ')'
        consumeWhitespace();
        if (index < input.size() && isdigit(input[index])) {
            return parseNumber();
        } else if (consume('(')) {
            bool result = parseExpression();
            return consume(')');
        }
        return false;
    }

    bool parseNumber() {
        // Number = [0-9]+
        consumeWhitespace();
        size_t start = index;
        while (index < input.size() && isdigit(input[index])) {
            index++;
        }
        return (index > start);
    }
};

int main() {
    std::string input;
    std::cout << "Enter a mathematical expression (containing integers only): ";
    std::getline(std::cin, input);

    PEGParser parser(input);
    if (parser.parse()) {
        std::cout << "Parsing successful!" << std::endl;
    } else {
        std::cout << "Parsing failed!" << std::endl;
    }

    return 0;
}
