#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <vector>
#include <sstream>

// Function to convert regular expression to regular grammar
std::unordered_map<char, std::vector<std::string>> regexToRegularGrammar(const std::string& regex) {
    // Implement conversion from regex to regular grammar
    // For simplicity, let's assume that we have already implemented this conversion

    // For demonstration purposes, let's just return a sample regular grammar
    return {
        {'S', {"aB", "cd", "PQ"}},
        {'B', {"bB", ""}},
        {'P', {"xy", ""}},
        {'Q', {"zQ", ""}}
    };
}

// Function to format regular grammar
std::string formatGrammar(const std::unordered_map<char, std::vector<std::string>>& grammar) {
    std::stringstream ss;
    for (const auto& [nonTerminal, productions] : grammar) {
        ss << nonTerminal << " --> ";
        for (size_t i = 0; i < productions.size(); ++i) {
            if (i > 0)
                ss << " | ";
            ss << productions[i];
        }
        ss << "\n";
    }
    return ss.str();
}

// Function to write grammar to a file
void writeGrammarToFile(const std::string& grammar, const std::string& filename) {
    std::ofstream file(filename);
    if (file.is_open()) {
        file << grammar;
        std::cout << "Grammar has been written to " << filename << std::endl;
        file.close();
    } else {
        std::cerr << "Unable to open file: " << filename << std::endl;
    }
}

int main() {
    std::string regex;
    std::cout << "Enter a regular expression: ";
    std::getline(std::cin, regex);

    // Convert regular expression to regular grammar
    std::unordered_map<char, std::vector<std::string>> regularGrammar = regexToRegularGrammar(regex);

    // Format the grammar
    std::string formattedGrammar = formatGrammar(regularGrammar);

    // Write grammar to a file
    std::string filename = "regular_grammar.txt";
    writeGrammarToFile(formattedGrammar, filename);

    return 0;
}
