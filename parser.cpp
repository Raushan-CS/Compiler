#include <iostream>
#include <string>

class Parser {
public:
    Parser(const std::string& input) : input(input), index(0) {}

    bool parse() {
        bool result = parseS();
        if (result && index == input.length()) {
            std::cout << "String accepted by the grammar." << std::endl;
            return true;
        } else {
            std::cout << "String not accepted by the grammar." << std::endl;
            return false;
        }
    }

private:
    std::string input;
    size_t index;

    bool match(char expected) {
        if (index < input.length() && input[index] == expected) {
            index++;
            return true;
        }
        return false;
    }

    bool parseS() {
        if (index < input.length()) {
            if (parseA() && parseB() && parseC())
                return true;
        }
        return false;
    }

    bool parseA() {
        size_t savedIndex = index;
        if (match('a') && match('b') && parseA()) {
            return true;
        }
        index = savedIndex;
        return true;
    }

    bool parseB() {
        size_t savedIndex = index;
        if (match('b')) {
            return true;
        }
        index = savedIndex;
        if (match('b') && parseC()) {
            return true;
        }
        index = savedIndex;
        return false;
    }

    bool parseC() {
        size_t savedIndex = index;
        if (match('c') && parseC()) {
            return true;
        }
        index = savedIndex;
        if (match('c')) {
            return true;
        }
        index = savedIndex;
        return false;
    }
};

int main() {
    std::string input;
    std::cout << "Enter a string: ";
    std::cin >> input;

    Parser parser(input);
    parser.parse();

    return 0;
}
