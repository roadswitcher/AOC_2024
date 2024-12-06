#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using wordsearch = std::vector<std::vector<char>>;

// Function to load the puzzle from a file
wordsearch load_puzzle(const std::string& filename) {
    std::ifstream fs(filename);
    std::string line;
    wordsearch puzzle;

    while (std::getline(fs, line)) {
        puzzle.push_back(std::vector<char>(line.begin(), line.end()));
    }

    std::cout << "Puzzle is " << puzzle[0].size() << " x " << puzzle.size() << " in size.\n";
    return puzzle;
}

// Function to print the puzzle
void print_puzzle(const wordsearch& puzzle) {
    for (const auto& row : puzzle) {
        for (const auto& ch : row) {
            std::cout << ch << " ";
        }
        std::cout << '\n';
    }
}

// Function to count occurrences of a substring in a string
int count_occurrences(const std::string& line, const std::string& substring) {
    int count = 0;
    size_t pos = 0;
    while ((pos = line.find(substring, pos)) != std::string::npos) {
        ++count;
        pos += substring.length();
    }
    return count;
}

// Function to get all diagonals
std::vector<std::string> get_diagonals(const wordsearch& puzzle) {
    std::vector<std::string> diagonals;
    int height = puzzle.size();
    int width = puzzle[0].size();

    // Collect diagonals in all 4 directions
    for (int row = 0; row < height; ++row) {
        for (int col = 0; col < width; ++col) {
            std::string diagonal1, diagonal2, diagonal3, diagonal4;
            for (int i = 0; i < std::min(width - col, height - row); ++i) {
                diagonal1 += puzzle[row + i][col + i]; // main diagonal (top-left to bottom-right)
                diagonal2 += puzzle[row + i][col - i]; // anti-diagonal (bottom-left to top-right)
                diagonal3 += puzzle[row - i][col + i]; // reverse main diagonal (bottom-left to top-right)
                diagonal4 += puzzle[row - i][col - i]; // reverse anti-diagonal (top-left to bottom-right)
            }
            if (!diagonal1.empty()) diagonals.push_back(diagonal1);
            if (!diagonal2.empty()) diagonals.push_back(diagonal2);
            if (!diagonal3.empty()) diagonals.push_back(diagonal3);
            if (!diagonal4.empty()) diagonals.push_back(diagonal4);
        }
    }

    return diagonals;
}

// Part 1 - Find occurrences of a string (including reverse) in rows, columns, and diagonals
void part_one(const wordsearch& puzzle, const std::string& str) {
    int num_found = 0;
    std::string rev_str = str;
    std::reverse(rev_str.begin(), rev_str.end());

    // Search rows
    for (const auto& row : puzzle) {
        std::string row_text(row.begin(), row.end());
        num_found += count_occurrences(row_text, str) + count_occurrences(row_text, rev_str);
    }

    // Search columns
    int width = puzzle[0].size();
    for (int col = 0; col < width; ++col) {
        std::string col_text;
        for (const auto& row : puzzle) {
            col_text += row[col];
        }
        num_found += count_occurrences(col_text, str) + count_occurrences(col_text, rev_str);
    }

    // Search diagonals
    auto diagonals = get_diagonals(puzzle);
    for (const auto& line : diagonals) {
        num_found += count_occurrences(line, str) + count_occurrences(line, rev_str);
    }

    std::cout << "Part 1: Number found: " << num_found << "\n";
}

// Part 2 - Find patterns around 'A' in a 2x2 square
void part_two(const wordsearch& puzzle) {
    int count = 0;
    int height = puzzle.size();
    int width = puzzle[0].size();

    std::vector<std::string> check_patterns = {"MMSS", "MSSM", "SSMM", "SMMS"};

    for (int row = 1; row < height - 1; ++row) {
        for (int col = 1; col < width - 1; ++col) {
            if (puzzle[row][col] == 'A') {
                std::string check_str = {puzzle[row - 1][col + 1], puzzle[row + 1][col + 1], 
                                         puzzle[row + 1][col - 1], puzzle[row - 1][col - 1]};
                if (std::find(check_patterns.begin(), check_patterns.end(), check_str) != check_patterns.end()) {
                    ++count;
                }
            }
        }
    }

    std::cout << "Part Two count: " << count << "\n";
}

int main() {
    std::string fname = "input.txt";
    std::string str = "XMAS";

    wordsearch puzzle = load_puzzle(fname);

    part_one(puzzle, str);
    part_two(puzzle);

    return 0;
}