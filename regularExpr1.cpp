 #include <iostream>
#include <regex>

// for (0 + 1)* + 0*1*

bool matchRegex(std::string inputString) {
    std::regex regexPattern("(0+1*)*|0*1*");
    return std::regex_match(inputString, regexPattern);
}

int main() {
    std::vector<std::string> testStrings = {"", "0", "1", "00", "01", "10", "11", "001", "010", "101", "110", "0000", "1111"};
    for (const auto& testString : testStrings) {
        std::cout << testString << ": " << (matchRegex(testString) ? "true" : "false") << std::endl;
    }
    return 0;
}
