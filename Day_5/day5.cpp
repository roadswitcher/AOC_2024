#include <fstream>
#include <iostream>
#include <regex>
#include <set>
#include <unordered_map>
#include <vector>

// using page_order_rules = std::unordered_map<int, std::set<int>>;
// using update_pages = std::vector<std::vector<int>>;

std::pair<std::unordered_map<int, std::set<int>>, std::vector<std::vector<int>>>
load_file(const std::string &fname) {

  std::ifstream fs(fname);
  std::string line{};
  std::regex page_regex(R"((\d+)\|(\d+))");
  std::unordered_map<int, std::set<int>> pagerules{};
  std::vector<std::vector<int>> updatesets{};

  while (std::getline(fs, line) && line != "") {
    std::smatch match;
    if (std::regex_match(line, match, page_regex)) {
      int page = std::stoi(match[1].str());
      int must_be_followed_by = std::stoi(match[2].str());
      pagerules[page].insert(must_be_followed_by);
    }
  }
  while (std::getline(fs, line)) {
    std::istringstream pagenums(line);
    std::vector<int> pageset{};
    std::string page;
    for (; std::getline(pagenums, page, ',');) {
      pageset.push_back(std::stoi(page));
    }
    updatesets.push_back(pageset);
  }
  return std::pair(pagerules, updatesets);
}

bool pageset_is_valid(std::vector<int> update_pageset,
                      std::unordered_map<int, std::set<int>> &rules) {
  int idx = update_pageset.size() - 1;
  while (idx > 0) {
    std::set<int> checkvals = rules[update_pageset[idx]];
    for (size_t i = 0; i < idx; i++) {
      int num = update_pageset[i];
      bool found_in_rules = (checkvals.find(num) != checkvals.end());
      if (found_in_rules) {
        return false;
      }
    }
    --idx;
  }
  return true;
}

void part_one(std::unordered_map<int, std::set<int>> &rules,
              std::vector<std::vector<int>> &updatesets) {

  std::vector<std::vector<int>> valid_updates;
  int sum_of_middles{0};

  for (auto idx = 0; idx < updatesets.size(); idx++) {
    std::vector<int> update = updatesets[idx];
    if(pageset_is_valid(update, rules)){
      valid_updates.push_back(update);
      sum_of_middles += update[update.size()/2];
    }
  }

  std::cout << "Part 1: " << sum_of_middles << "\n";
}

int main() {
  // std::string fname = "test_input.txt";
  std::string fname = "input.txt";

  std::unordered_map<int, std::set<int>> rules;
  std::vector<std::vector<int>> updates;

  std::tie(rules, updates) = load_file(fname);

  // for (const auto &[page, values] : rules) {
  //   std::cout << page << "\n";
  //   for (const auto &pg : values) {
  //     std::cout << pg << " ";
  //   }
  //   std::cout << "\n";
  // }

  std::cout << "Number of updates : " << updates.size() << "\n";

  part_one(rules, updates);
}
