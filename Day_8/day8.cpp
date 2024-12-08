#include <fstream>
#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>

using map_grid = std::vector<std::vector<char>>;
using tower_pair = std::pair<coord,coord>;

struct coord {
  int y{};
  int x{};
  char type{};
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

std::vector<coord> find_locations(const map_grid &map) {
  int width = map[0].size();
  int height = map.size();
  std::vector<coord> tower_list{};

  for (auto row = 0; row < width; row++) {
    for (auto col = 0; col < height; col++) {
      char freq = map[row][col];
      if (freq != '.') {
        // Found a tower
        coord tower_coord;
        tower_coord.type = freq;
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

std::vector<tower_pair> find_pairs(const map_grid &map){

}

std::pair<coord, coord> find_antinodes(const tower_pair &towerpair ){

}

void part_one(map_grid &map) {
  // We know we have N towers of M different frequencies
  // - Find all the towers coords and freqs
  auto tower_list = find_locations(map);
  // - Pass that info to a function that builds lists of 'pairs'
  // - write a function that computes antinode locations per pair
  // final steps:
  // - for each pair, record antinode locations on a map, no worry about overwrites
  // - count antinodes on the map

}


int main() {
  std::string fname = "test_input.txt";

  map_grid map = loadfile(fname);
  std::cout << "rows " << map.size() << std::endl;
  std::cout << "cols " << map[1].size() << std::endl;

  print_map(map);
  

  part_one(map);
}