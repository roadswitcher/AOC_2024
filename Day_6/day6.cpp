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
  char dir{};
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

coord where_is_guard(const map_grid &map) {
  int width = map[0].size();
  int height = map.size();
  std::unordered_set<char> guard_facing = {'^', '>', '<', 'v'};
  coord guard_location{};

  for (auto row = 0; row < width; row++) {
    for (auto col = 0; col < height; col++) {
      char ch = map[row][col];
      if (ch == '^' || ch == 'v' || ch == '>' || ch == '<') {
        guard_location.y = row;
        guard_location.x = col;
        guard_location.dir = ch;
        return guard_location;
      }
    }
  }
  return guard_location;
}

int dists(const coord& guard, const map_grid &map) {
  int width = map[0].size();
  int height = map.size();
  int first_obstacle{0};
  int edge{};
  

}
void part_one(map_grid &lab_map) {
  // where is guard
}
int main() {
  std::string fname = "test_input.txt";

  map_grid the_map = loadfile(fname);
  std::cout << the_map.size() << std::endl;
  std::cout << the_map[1].size() << std::endl;

  for (size_t row = 0; row < the_map.size(); row++) {
    for (size_t col = 0; col < the_map[0].size(); col++) {
      std::cout << the_map[row][col] << " ";
    }
    std::cout << std::endl;
  }

  auto guard = where_is_guard(the_map);
  std::cout << guard.y << " " << guard.x << " " << guard.dir << std::endl;
  part_one(the_map);
}