#include <algorithm>
#include <fstream>
#include <iostream>
#include <numeric>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

using location_vector = std::vector<int>;

std::pair<location_vector, location_vector>
read_location_lists(const std::string &filename) {
  location_vector a, b;
  std::string line{};
  int tmp_a, tmp_b;

  std::ifstream fs(filename);
  while (std::getline(fs, line)) {
    std::istringstream values(line);
    values >> tmp_a >> tmp_b;
    a.push_back(tmp_a);
    b.push_back(tmp_b);
  }
  std::sort(a.begin(), a.end());
  std::sort(b.begin(), b.end());
  return std::pair(a, b);
}

std::vector<int> difference_list(location_vector &a, location_vector &b) {
  std::vector<int> result(a.size());
  for (size_t i = 0; i < a.size(); ++i) {
    result[i] = abs(a[i] - b[i]);
  }
  return result;
}

auto similarity_metric(location_vector &a, location_vector &b) {
  std::unordered_map<int, int> freq_map_b;
  int result{};

  for (auto &elem : b) {
    freq_map_b[elem]++;
  }

  for (auto &elem : a) {
    result += elem * freq_map_b[elem];
  }
  return result;
}

auto part1(location_vector &a, location_vector &b) {
  auto differences = difference_list(a, b);
  return std::reduce(differences.begin(), differences.end());
}

auto part2(location_vector &a, location_vector &b) {
  return similarity_metric(a, b);
}

int main() {
  location_vector list_a, list_b;
  std::tie(list_a, list_b) = read_location_lists("input.txt");

  std::cout << part1(list_a, list_b) << "\n";
  std::cout << part2(list_a, list_b) << "\n";

  return 0;
}
