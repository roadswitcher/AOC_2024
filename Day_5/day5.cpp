#include <fstream>
#include <iostream>
#include <regex>
#include <set>
#include <unordered_map>
#include <vector>

using page_order_rules = std::unordered_map<int, std::set<int>>;
using update_pages = std::vector<std::vector<int>>;

std::pair<page_order_rules, update_pages> load_file(const std::string &fname) {

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
                      page_order_rules &rules) {
  int idx = update_pageset.size() - 1;
  while (idx > 0) {
    std::set<int> checkvals = rules[update_pageset[idx]];
    for (int i = 0; i < idx; i++) {
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

update_pages part_one(page_order_rules &rules, update_pages &updatesets) {
  int valid_update_count{0};
  update_pages invalid_updates;

  int sum_of_middles{0};

  for (size_t idx = 0; idx < updatesets.size(); idx++) {
    std::vector<int> update = updatesets[idx];
    if (pageset_is_valid(update, rules)) {
      sum_of_middles += update[update.size() / 2];
      valid_update_count++;
    } else {
      invalid_updates.push_back(update);
    }
  }

  std::cout << "Part 1: " << sum_of_middles << " w/ " << valid_update_count
            << " valid updates\n";
  return invalid_updates;
}

void part_two(update_pages &invalid_pagesets, page_order_rules &rules) {
  update_pages sorted_pagesets;
  int sum{0};
  std::cout << "Invalid Pageset count: " << invalid_pagesets.size() << "\n";

  for (size_t idx = 0; idx < invalid_pagesets.size(); idx++) {
    std::vector<int> pageset = invalid_pagesets[idx];
    std::cout << std::endl;
    for (int num : pageset) {
      std::cout << num << " ";
    }
    std::cout << std::endl;
    // You can write Fortran in any language.
    do {
      if (pageset_is_valid(pageset, rules)) {
        sum += pageset[pageset.size() / 2];
        std::cout << std::endl;
        for (int num : pageset) {
          std::cout << num << " ";
        }
        std::cout << std::endl;
      }
    } while (std::next_permutation(pageset.begin(), pageset.end()));
  }
  std::cout << "Part 2: " << sum << "\n";
}

int main() {
  // std::string fname = "test_input.txt";
  std::string fname = "input.txt";
  page_order_rules rules;
  update_pages updates;

  std::tie(rules, updates) = load_file(fname);
  std::cout << "Number of updates : " << updates.size() << "\n";

  update_pages bad_updates = part_one(rules, updates);
  part_two(bad_updates, rules);
}
