#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <ctime>
#include <cstdlib>
#include <chrono>

// ANSI color codes for eye-friendly colors
const std::string LIGHT_GREEN = "\033[1;32m";
const std::string CYAN = "\033[1;36m";
const std::string RESET = "\033[0m";

void loadDictionary(const std::string& filename, std::vector<std::string>& lines) {
    std::ifstream file(filename);
    std::string line;
    while (std::getline(file, line)) {
        lines.push_back(line);
    }
}

int getRandomStartingIndex(const std::vector<std::string>& lines, int linesToTest) {
    return rand() % (lines.size() - linesToTest + 1);
}

void typingTest(const std::vector<std::string>& lines, int linesToTest) {
    std::string input;
    int correctCount = 0;
    std::vector<std::string> typedLines;
    int totalCharacters = 0; // For calculating symbols per minute
    int totalWords = 0;      // For calculating words per minute

    int startingIndex = getRandomStartingIndex(lines, linesToTest);

    // Start measuring time
    auto startTime = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < linesToTest; ++i) {
        std::string line = lines[startingIndex + i];
        std::cout << "Type the following line:" << std::endl;
        std::cout << line << std::endl;
        std::getline(std::cin, input);
        typedLines.push_back(input);  // Store the typed input

        totalCharacters += input.length();     // Count characters
        totalWords += input.length() > 0 ? 1 : 0;  // Count words based on spaces
        for (char ch : input) {
            if (ch == ' ') ++totalWords; // Additional word counting for spaces
        }

        if (input == line) {
            std::cout << "Correct!" << std::endl;
            ++correctCount;
        } else {
            std::cout << "Incorrect. The correct line was: " << line << std::endl;
        }
    }

    // Stop measuring time
    auto endTime = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = endTime - startTime;
    double typingTimeSeconds = duration.count();
    double typingTimeMinutes = typingTimeSeconds / 60.0;

    std::cout << "\nYou typed " << correctCount << " out of " << linesToTest << " lines correctly." << std::endl;

    // Show the typed lines
    std::cout << "\nHere are the lines you typed:" << std::endl;
    for (const std::string& typedLine : typedLines) {
        std::cout << typedLine << std::endl;
    }

    // Calculate Symbols per minute and Words per minute
    double symbolsPerMinute = totalCharacters / typingTimeMinutes;
    double wordsPerMinute = totalWords / typingTimeMinutes;

    // Highlight results with friendly eye colors
    std::cout << LIGHT_GREEN << "\n--- Typing Test Results ---" << RESET << std::endl;
    std::cout << CYAN << "Total time: " << typingTimeSeconds << " seconds" << RESET << std::endl;
    std::cout << CYAN << "Symbols per minute: " << symbolsPerMinute << RESET << std::endl;
    std::cout << CYAN << "Words per minute: " << wordsPerMinute << RESET << std::endl;
}

int main() {
    srand(static_cast<unsigned int>(time(0)));

    std::vector<std::string> lines;
    std::string filename = "dictionary.txt";

    loadDictionary(filename, lines);

    if (lines.empty()) {
        std::cerr << "Error: Could not load dictionary or it is empty." << std::endl;
        return 1;
    }

    int linesToTest;
    std::cout << "How many lines would you like to type? ";
    std::cin >> linesToTest;
    std::cin.ignore();  // Ignore remaining newline in input buffer

    typingTest(lines, linesToTest);

    return 0;
}
