#include <iostream>
#include <vector>
#include <unordered_map>
#include <sstream>

// Structure to represent production rules
struct Production {
    char nonTerminal;
    std::vector<std::string> alternatives;
};

// Function to eliminate left recursion
std::vector<Production> eliminateLeftRecursion(const std::vector<Production>& productions) {
    std::vector<Production> updatedProductions;
    std::unordered_map<char, std::vector<std::string>> newNonTerminals;

    for (const auto& prod : productions) {
        char nonTerminal = prod.nonTerminal;
        std::vector<std::string> leftRecursive;
        std::vector<std::string> rightRecursive;
        
        for (const auto& alt : prod.alternatives) {
            if (alt[0] == nonTerminal) {
                leftRecursive.push_back(alt.substr(1) + nonTerminal + "'");
            } else {
                rightRecursive.push_back(alt + nonTerminal + "'");
            }
        }
        
        if (!leftRecursive.empty()) {
            newNonTerminals[nonTerminal].swap(rightRecursive);
            newNonTerminals[nonTerminal].push_back("");
            newNonTerminals[nonTerminal + '\''].swap(leftRecursive);
            newNonTerminals[nonTerminal + '\''].push_back("");
        } else {
            updatedProductions.push_back(prod);
        }
    }

    for (const auto& [nonTerminal, alternatives] : newNonTerminals) {
        updatedProductions.push_back({nonTerminal, alternatives});
    }

    return updatedProductions;
}

// Function to format productions
std::string formatProductions(const std::vector<Production>& productions) {
    std::stringstream ss;
    for (const auto& prod : productions) {
        ss << prod.nonTerminal << " -> ";
        for (size_t i = 0; i < prod.alternatives.size(); ++i) {
            if (i > 0)
                ss << " | ";
            ss << prod.alternatives[i];
        }
        ss << "\n";
    }
    return ss.str();
}

int main() {
    // Sample grammar with left recursion
    std::vector<Production> productions = {
        {'S', {"Sa", "b"}},
        {'A', {"Ac", "d"}}
    };

    // Eliminate left recursion
    std::vector<Production> updatedProductions = eliminateLeftRecursion(productions);

    // Format and print updated productions
    std::cout << "Updated Productions:\n";
    std::cout << formatProductions(updatedProductions);

    return 0;
}
