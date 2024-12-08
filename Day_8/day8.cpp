#include <fstream>
#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>

using map_grid = std::vector<std::vector<char>>;
// using coord = std::pair<int, int>;
struct coord {
  int y{};
  int x{};
  char freq{};
};

map_grid loadfile(const std::string &filename) {
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

std::vector<coord> find_towers(const map_grid &map) {
  int width = map[0].size();
  int height = map.size();
  std::vector<coord> tower_list{};

  for (auto row = 0; row < width; row++) {
    for (auto col = 0; col < height; col++) {
      char freq = map[row][col];
      if (freq != '.') {
        // Found a tower
        coord tower_coord;
        tower_coord.freq = freq;
        tower_coord.x = col;
        tower_coord.y = row;
        tower_list.emplace_back(tower_coord);
      }
    }
  }
  return tower_list;
}

void print_map(const map_grid &map){
  int rows = map.size();
  int cols = map[0].size();

  for (size_t row = 0; row < map.size(); row++) {
    for (size_t col = 0; col < map[0].size(); col++) {
      std::cout << map[row][col] << " ";
    }
    std::cout << std::endl;
  }
}


void part_one(map_grid &lab_map) {
  // antinode count
}
int main() {
  std::string fname = "test_input.txt";

  map_grid the_map = loadfile(fname);
  std::cout << "rows " << the_map.size() << std::endl;
  std::cout << "cols " << the_map[1].size() << std::endl;

  print_map(the_map);
  

  part_one(the_map);
}