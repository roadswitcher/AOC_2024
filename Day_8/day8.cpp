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
  }
  return filtered_result;
}

std::vector<tower_pair> find_pairs(const std::vector<coord> locations) {
  std::vector<tower_pair> pairs;
  // given a vector of locations of a specific type, return vector of all the
  // pairs
  for (size_t i = 0; i < locations.size(); i++) {
    for (size_t j = i + 1; j < locations.size(); j++) {
      pairs.push_back({locations[i], locations[j]});
    }
  }

  return pairs;
}

std::vector<coord> process_antinodes(const tower_pair &towerpair,
                                     map_grid &map) {
  int cols = map[0].size();
  int rows = map.size();
  auto a = std::move(towerpair.first);
  auto b = std::move(towerpair.second);
  std::vector<coord> antinodes;
  int dx = b.x - a.x;
  int dy = b.y - a.y;
  a.x = a.x - dx;
  a.y = a.y - dy;
  b.x = b.x + dx;
  b.y = b.y + dy;
  if (a.x >= 0 && a.x < cols && a.y >= 0 && a.y < rows) {
    antinodes.push_back(a);
    // std::cout << "A x/y " << a.x << "/" << a.y << "\n";
  }
  if (b.x >= 0 && b.x < cols && b.y >= 0 && b.y < rows) {
    antinodes.push_back(b);
    // std::cout << "B x/y " << b.x << "/" << b.y << "\n";
  }
  return antinodes;
}

std::vector<coord> process_antinodes_part_two(const tower_pair &towerpair,
                                              map_grid &map) {
  int cols = map[0].size();
  int rows = map.size();
  auto a = std::move(towerpair.first);
  auto b = std::move(towerpair.second);
  int dx = towerpair.second.x - towerpair.first.x;
  int dy = towerpair.second.y - towerpair.first.y;

  std::vector<coord> antinodes;
  // process a->b direction till out of bounds
  while (a.x >= 0 && a.x < cols && a.y >= 0 && a.y < rows) {
    antinodes.push_back(a);
    a.x -= dx;
    a.y -= dy;
  }

  // process b->a direction till out of bounds
  while (b.x >= 0 && b.x < cols && b.y >= 0 && b.y < rows) {
    antinodes.push_back(b);
    b.x += dx;
    b.y += dy;
  }
  return antinodes;
}

void part_one(map_grid &map) {
  // We know we have N towers of M different frequencies
  // - Find all the towers coords and freqs, and determine # of freqs
  auto tower_list = find_locations(map);
  auto freqs = get_the_types(tower_list);
  map_grid antinode_map(map.size(), std::vector<char>(map[0].size(), '.'));

  for (auto freq : freqs) {
    // - Pass that info to a function that builds lists of 'pairs'
    std::vector<tower_pair> tower_pairs =
        find_pairs(filtered_coords(tower_list, freq));
    // std::cout << "There are " << tower_pairs.size() << " pairs on freq " <<
    // freq << std::endl;
    // - write a function that processes antinode locations per pair
    for (auto pair : tower_pairs) {
      auto antinodes = process_antinodes(pair, antinode_map);
      for (auto antinode : antinodes) {
        antinode_map[antinode.y][antinode.x] = '#';
      }
    }
  }
  print_map(antinode_map);
  // - count antinodes on the map
  std::cout << "Pt 1 Number of antinodes: "
            << find_locations(antinode_map).size() << std::endl;
}

void part_two(map_grid &map) {
  // We know we have N towers of M different frequencies
  // - Find all the towers coords and freqs, and determine # of freqs
  auto tower_list = find_locations(map);
  auto freqs = get_the_types(tower_list);
  map_grid antinode_map(map.size(), std::vector<char>(map[0].size(), '.'));

  for (auto freq : freqs) {
    // - Pass that info to a function that builds lists of 'pairs'
    std::vector<tower_pair> tower_pairs =
        find_pairs(filtered_coords(tower_list, freq));
    // std::cout << "There are " << tower_pairs.size() << " pairs on freq " <<
    // freq << std::endl;
    // - write a function that processes antinode locations per pair
    for (auto pair : tower_pairs) {
      auto antinodes = process_antinodes_part_two(pair, antinode_map);
      for (auto antinode : antinodes) {
        antinode_map[antinode.y][antinode.x] = '#';
      }
    }
  }
  print_map(antinode_map);

  // - count antinodes on the map
  std::cout << "Pt 2 Number of antinodes: "
            << find_locations(antinode_map).size() << std::endl;
}
int main() {
  // std::string fname = "test_input.txt";
  // std::string fname = "test_pt2.txt";
  std::string fname = "input.txt";

  map_grid map = loadfile(fname);

  part_one(map);
  part_two(map);
}