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
    std::cout << row << std::endl;

    height++;
  }

  std::cout << "Puzzle is " << width << " x " << height << " in size.\n";

  return puzzle;
}


int main() {
  std::string fname = "test_input.txt";

  auto puzzle = load_puzzle(fname);

  // part_one(puzzle);
  // part_two(puzzle);
}