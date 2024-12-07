#include <fstream>
#include <iostream>
#include <regex>
#include <string>
#include <unordered_map>
#include <vector>

using map_grid = std::vector<std::vector<char>>;
using coord = std::pair<int, int>;

map_grid loadfile(std::string &filename) {
  map_grid resulting_map;

  std::ifstream fs(filename);
  std::string line{};

  while (std::getline(fs, line)) {
    std::vector<char> row;
    for (size_t i = 0; i < line.length(); i++) {
      row.push_back(line[i]);
    }
    resulting_map.push_back(row);
  }
  return resulting_map;
}

void part_one(map_grid &lab_map) {}
int main() {
  std::string fname = "test_input.txt";

  map_grid the_map = loadfile(fname);
  std::cout << the_map.size() << std::endl;
  std::cout << the_map[1].size() << std::endl;
  part_one(the_map);
  for (size_t row = 0; row < the_map.size(); row++) {
    for (size_t col = 0; col < the_map[0].size(); col++) {
      std::cout << the_map[row][col] << " ";
    }
    std::cout << std::endl;
  }
}