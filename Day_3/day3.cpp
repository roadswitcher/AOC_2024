#include <cstdint>
#include <fstream>
#include <iostream>
#include <regex>
#include <string>

int find_muls(auto line) {
  // use capture groups, because reasons
  std::regex multiply_pattern(R"(mul\((\d+),(\d+)\))");
  auto begin = std::sregex_iterator(line.begin(), line.end(), multiply_pattern);
  auto end = std::sregex_iterator();
  int sum{0};

  for (auto it = begin; it != end; ++it) {
    std::smatch match = *it;
    sum += std::stoi(match[1].str()) * std::stoi(match[2].str());
  }
  return sum;
}

void part_one(std::string filename) {
  std::ifstream fs(filename);
  std::string line{};
  int accumulated_sum{0};

  while (std::getline(fs, line)) {
    accumulated_sum += find_muls(line);
  }
  std::cout << accumulated_sum << "\n";
}

void part_two(std::string filename) {
  std::ifstream fs(filename);
  std::string line{};
  // use capture groups, because reasons
  std::regex combined_pattern(R"(mul\((\d{1,3}),(\d{1,3})\)|do\(\)|don't\(\))");
  std::regex multiply_pattern(R"(mul\((\d+),(\d+)\))");

  int sum{0};
  bool enabled=true;

  while (std::getline(fs, line)) {
    auto begin =
        std::sregex_iterator(line.begin(), line.end(), combined_pattern);
    auto end = std::sregex_iterator();
    std::smatch match;

    for (auto it = begin; it != end; ++it) {
      match = *it;
      if (match.str() == "do()") {
        enabled = true;
      } else if (match.str() == "don't()") {
        enabled = false;
      } else if (enabled && std::regex_match(match.str(), multiply_pattern)) {
        sum += std::stoi(match[1].str()) * std::stoi(match[2].str());
      }
    }
  }
  std::cout << sum << "\n";
}

int main() {
  std::string fname = "input.txt";

  part_one(fname);
  part_two(fname);
}