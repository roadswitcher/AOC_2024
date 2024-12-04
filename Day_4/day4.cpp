#include <cstdint>
#include <fstream>
#include <iostream>
#include <regex>
#include <string>
#include <vector>

std::vector<std::vector<char>> load_puzzle(std::string filename) {
  std::ifstream fs(filename);
  std::string line{};
  std::vector<std::vector<char>> puzzle{};
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

void print_puzzle(std::vector<std::vector<char>> puzzle){
  for (size_t row=0; row<puzzle.size(); row++){
    for (size_t col=0; col<puzzle[row].size(); col++){
      std::cout << puzzle[row][col];
    }
    std::cout << std::endl;
  }
}

int main() {
  std::string fname = "test_input.txt";

  std::vector<std::vector<char>> puzzle = load_puzzle(fname);
  print_puzzle(puzzle);
  // part_one(puzzle);
  // part_two(puzzle);
}