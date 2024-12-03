#include <cstdint>
#include <fstream>
#include <iostream>
#include <regex>
#include <string>

uint64_t find_muls(auto line) {
  auto begin = std::sregex_iterator(line.begin(), line.end(), multiply_pattern);
  auto end = std::sregex_iterator();
  uint64_t accumulator{0};
  // use capture groups, because reasons
  std::regex multiply_pattern(R"(mul\((\d+),(\d+)\))");

  for (auto it = begin; it != end; ++it) {
    std::smatch match = *it;
    int num1 = std::stoi(match[1].str());
    int num2 = std::stoi(match[2].str());
    accumulator += num1 * num2;
  }
  return accumulator;
}

void process_file(std::string filename) {
  std::ifstream fs(filename);
  std::string line{};
  uint64_t accumulated_sum{0};

  while (std::getline(fs, line)) {
    accumulated_sum += find_muls(line);
  }
  std::cout << accumulated_sum << "\n";
}

int main() {
  std::string fname = "input.txt";

  process_file(fname);

}