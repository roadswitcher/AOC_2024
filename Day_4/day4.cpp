#include <cstdint>
#include <fstream>
#include <iostream>
#include <regex>
#include <string>
#include <vector>

using wordsearch = std::vector<std::vector<char>>;

wordsearch load_puzzle(std::string filename) {
  std::ifstream fs(filename);
  std::string line{};
  wordsearch puzzle{};
  int width{0};
  int height{0};

  while (std::getline(fs, line)) {
    std::vector<char> row;
    width = line.length();
    for (auto i = 0; i<line.length(); i++){
      row.push_back(line[i]);
    }
    puzzle.push_back(row);
    height++;
  }

  std::cout << "Puzzle is " << width << " x " << height << " in size.\n";

  return puzzle;
}

void print_puzzle(wordsearch puzzle){
  for (size_t row=0; row<puzzle.size(); row++){
    for (size_t col=0; col<puzzle[row].size(); col++){
      std::cout << puzzle[row][col];
    }
    std::cout << std::endl;
  }
}

void part_one(){}

int main() {
  std::string fname = "test_input.txt";

  wordsearch puzzle = load_puzzle(fname);
  print_puzzle(puzzle);
  // part_one(puzzle);
  // part_two(puzzle);
}