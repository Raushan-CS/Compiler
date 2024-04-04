 #include <iostream>
#include <regex>

// for ((a + b)*(c + d)*)+ + ab*c*d
bool matchRegex(std::string inputString) {
    std::regex regexPattern("((a|b)*(c|d)*)+|ab*c*d");
    return std::regex_match(inputString, regexPattern);
}

int main() {
    std::vector<std::string> testStrings = {"", "a", "b", "c", "d", "ab", "ac", "ad", "bc", "bd", "cd", "aaabbbccc", "abccd", "abccdcd", "abcccd", "abbbccc"};
    for (const auto& testString : testStrings) {
        std::cout << testString << ": " << (matchRegex(testString) ? "true" : "false") << std::endl;
    }
    return 0;
}
