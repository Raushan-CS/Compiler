#include <iostream>
#include <string>
#include <unordered_set>

// Function to check if a word is a noun
bool isNoun(const std::string& word) {
    // A simple approach: check if the word ends with "s" or "es"
    size_t length = word.length();
    return (length > 1 && (word[length - 1] == 's' || (word[length - 1] == 'e' && word[length - 2] == 's')));
}

// Function to check if a word is a verb
bool isVerb(const std::string& word) {
    // A simple approach: check if the word ends with "ed", "ing", or "s" (for 3rd person singular)
    size_t length = word.length();
    return (length > 1 && (word.substr(length - 2) == "ed" || word.substr(length - 3) == "ing" || (word[length - 1] == 's' && word[length - 2] != 's')));
}

// Function to check if a word is an adjective
bool isAdjective(const std::string& word) {
    // A simple approach: check if the word ends with "y" or "ous"
    size_t length = word.length();
    return (length > 1 && (word[length - 1] == 'y' || (word.substr(length - 3) == "ous")));
}

// Function to check if a word is an adverb
bool isAdverb(const std::string& word) {
    // A simple approach: check if the word ends with "ly"
    size_t length = word.length();
    return (length > 1 && (word.substr(length - 2) == "ly"));
}

// Function to check if a word is a pronoun
bool isPronoun(const std::string& word) {
    // A simple approach: check if the word is in a predefined set of pronouns
    static const std::unordered_set<std::string> pronouns = {"I", "you", "he", "she", "it", "we", "they"};
    return pronouns.count(word);
}

int main() {
    std::string word;
    std::cout << "Enter a word: ";
    std::cin >> word;

    if (isNoun(word))
        std::cout << word << " is a noun." << std::endl;
    else if (isVerb(word))
        std::cout << word << " is a verb." << std::endl;
    else if (isAdjective(word))
        std::cout << word << " is an adjective." << std::endl;
    else if (isAdverb(word))
        std::cout << word << " is an adverb." << std::endl;
    else if (isPronoun(word))
        std::cout << word << " is a pronoun." << std::endl;
    else
        std::cout << word << " is not classified." << std::endl;

    return 0;
}
