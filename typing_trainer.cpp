#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <ctime>
#include <cstdlib>

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

    int startingIndex = getRandomStartingIndex(lines, linesToTest);

    for (int i = 0; i < linesToTest; ++i) {
        std::string line = lines[startingIndex + i];
        std::cout << "Type the following line:" << std::endl;
        std::cout << line << std::endl;
        std::getline(std::cin, input);
        typedLines.push_back(input);  // Store the typed input

        if (input == line) {
            std::cout << "Correct!" << std::endl;
            ++correctCount;
        } else {
            std::cout << "Incorrect. The correct line was: " << line << std::endl;
        }
    }

    std::cout << "\nYou typed " << correctCount << " out of " << linesToTest << " lines correctly." << std::endl;

    // Show the typed lines
    std::cout << "\nHere are the lines you typed:" << std::endl;
    for (const std::string& typedLine : typedLines) {
        std::cout << typedLine << std::endl;
    }
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
