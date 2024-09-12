#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <ctime>
#include <cstdlib>

void loadDictionary(const std::string& filename, std::vector<std::string>& words) {
    std::ifstream file(filename);
    std::string word;
    while (file >> word) {
        words.push_back(word);
    }
}

std::string getRandomWord(const std::vector<std::string>& words) {
    return words[rand() % words.size()];
}

void typingTest(const std::vector<std::string>& words) {
    std::string input;
    int correctCount = 0;
    int totalWords = 10; // Number of words to test

    for (int i = 0; i < totalWords; ++i) {
        std::string word = getRandomWord(words);
        std::cout << "Type the word: " << word << std::endl;
        std::cin >> input;

        if (input == word) {
            std::cout << "Correct!" << std::endl;
            ++correctCount;
        } else {
            std::cout << "Incorrect. The correct word was: " << word << std::endl;
        }
    }

    std::cout << "You typed " << correctCount << " out of " << totalWords << " words correctly." << std::endl;
}

int main() {
    srand(static_cast<unsigned int>(time(0)));

    std::vector<std::string> words;
    std::string filename = "dictionary.txt";

    loadDictionary(filename, words);

    if (words.empty()) {
        std::cerr << "Error: Could not load dictionary or it is empty." << std::endl;
        return 1;
    }

    typingTest(words);

    return 0;
}