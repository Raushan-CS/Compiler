#include <iostream>
#include <regex>

// For (ab*c + (def)+ + a*d+e)+
bool matchRegex(std::string inputString) {
    std::regex regexPattern("(ab*c|(def)+|(a*d+e))+");
    return std::regex_match(inputString, regexPattern);
}

int main() {
    std::vector<std::string> testStrings = {"abc", "abbbc", "def", "defdef", "ade", "adeade", "abbbbcd", "de", "adee", "abcdef", "defdefdef", "adeee"};
    for (const auto& testString : testStrings) {
        std::cout << testString << ": " << (matchRegex(testString) ? "true" : "false") << std::endl;
    }
    return 0;
}
