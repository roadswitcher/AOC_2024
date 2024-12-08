#include <fstream>
#include <iostream>
#include <set>
#include <string>
#include <vector>

struct coord {
  int y{}; // row
  int x{}; // column
  char type{};
};

using map_grid = std::vector<std::vector<char>>;
using tower_pair = std::pair<coord, coord>;

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

void print_map(const map_grid &map) {
  int rows = map.size();
  int cols = map[0].size();

  for (size_t row = 0; row < map.size(); row++) {
    for (size_t col = 0; col < map[0].size(); col++) {
      std::cout << map[row][col] << " ";
    }
    std::cout << std::endl;
  }
}

std::vector<coord> find_locations(const map_grid &map) {
  int width = map[0].size();
  int height = map.size();
  std::vector<coord> tower_list{};

  for (auto row = 0; row < width; row++) {
    for (auto col = 0; col < height; col++) {
      char cell = map[row][col];
      if (cell != '.') {
        // Found a tower
        coord tower_coord;
        tower_coord.type = cell;
        tower_coord.x = col;
        tower_coord.y = row;
        tower_list.emplace_back(tower_coord);
      }
    }
  }
  return tower_list;
}

std::set<char> get_the_types(const std::vector<coord> &locations) {
  std::set<char> types;
  for (auto &location : locations) {
    types.insert(location.type);
  }
  return types;
}

std::vector<coord> filtered_coords(const std::vector<coord> &coords,
                                   const char &type) {
  std::vector<coord> filtered_result;
  for (auto &coord : coords) {
    if (coord.type == type)
      filtered_result.push_back(coord);
      std::cout << "Type: " << coord.type << " matches type " << type << " row/col " << coord.y << "/"<< coord.x << "\n";
  }
  return filtered_result;
}

std::vector<tower_pair> find_pairs(const std::vector<coord> locations) {
  std::vector<tower_pair> pairs;
  // given a vector of locations of a specific type, return vector of all the
  // pairs
  for (size_t i = 0; i < locations.size(); i++) {
    for (size_t j = i+1; j < locations.size(); j++) {
      pairs.push_back({locations[i], locations[j]});
    }
  }

  return pairs;
}

std::pair<coord, coord> find_antinodes(const tower_pair &towerpair) {}

void part_one(map_grid &map) {
  // We know we have N towers of M different frequencies
  // - Find all the towers coords and freqs, and determine # of freqs
  auto tower_list = find_locations(map);
  auto freqs = get_the_types(tower_list);
  map_grid antinode_tracker(map.size(), std::vector<char>(map[0].size(), '.'));
  std::vector<tower_pair> tower_pairs;
  for (auto freq : freqs) {
    // - Pass that info to a function that builds lists of 'pairs'
    tower_pairs.clear();
    tower_pairs = find_pairs(filtered_coords(tower_list, freq));
    std::cout << "There are " << tower_pairs.size() << " pairs on freq " << freq << std::endl;
    for (auto pair:tower_pairs){
      std::cout << "Pair 1 " << pair.first.x << "/" <<pair.first.y << "   "<< pair.second.x << "/" <<pair.second.y << std::endl;
    }

    // - write a function that computes antinode locations per pair
    // final steps:
    // - for each pair, record antinode locations on a map, no worry about
    // overwrites
  }
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