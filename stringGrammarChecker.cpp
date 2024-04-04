#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

class RegularGrammar {
public:
    RegularGrammar(const std::unordered_map<char, std::vector<std::string>>& productions) : productions(productions) {}

    bool isStringAccepted(const std::string& str) {
        for (const auto& production : productions) {
            if (matchesProduction(production.second, str))
                return true;
        }
        return false;
    }

private:
    std::unordered_map<char, std::vector<std::string>> productions;

    bool matchesProduction(const std::vector<std::string>& alternatives, const std::string& str) {
        for (const auto& alt : alternatives) {
            size_t pos = 0;
            bool matched = true;
            for (char ch : alt) {
                if (std::isupper(ch)) { // Non-terminal symbol
                    if (pos < str.length() && str[pos] == ch) {
                        pos++;
                    } else {
                        matched = false;
                        break;
                    }
                } else { // Terminal symbol
                    if (pos < str.length() && str[pos] == ch) {
                        pos++;
                    } else {
                        matched = false;
                        break;
                    }
                }
            }
            if (matched && pos == str.length()) {
                return true;
            }
        }
        return false;
    }
};

int main() {
    std::unordered_map<char, std::vector<std::string>> productions = {
        {'S', {"aA", "bB", "c"}},
        {'A', {"dA", "e"}},
        {'B', {"fB", "g"}}
    };

    RegularGrammar grammar(productions);

    std::string input;
    std::cout << "Enter a string to check if it is accepted by the grammar: ";
    std::cin >> input;

    if (grammar.isStringAccepted(input)) {
        std::cout << "String is accepted by the grammar." << std::endl;
    } else {
        std::cout << "String is not accepted by the grammar." << std::endl;
    }

    return 0;
}
