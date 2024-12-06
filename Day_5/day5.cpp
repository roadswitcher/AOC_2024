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
  page_order_rules pagerules{};
  update_pages updatesets{};

  while (std::getline(fs, line) && line != "") {
    std::smatch match;
    // std::cout << line << std::endl;

    if (std::regex_match(line, match, page_regex)) {
      int page = std::stoi(match[1].str());
      int must_be_followed_by = std::stoi(match[2].str());
      pagerules[page].insert(must_be_followed_by);
    }
  }
  while (std::getline(fs, line)) {
    std::istringstream pagenums(line);
    // std::cout << line << "\n";
    std::vector<int> pageset{};
    std::string page;
    for (; std::getline(pagenums, page, ',');) {
      // std::cout << page << "\n";
      pageset.push_back(std::stoi(page));
    }
    updatesets.push_back(pageset);
  }
  return std::pair(pagerules, updatesets);
}

void part_one(page_order_rules &rules, update_pages &updatesets) {}

int main() {
  std::string fname = "test_input.txt";
  page_order_rules rules;
  update_pages updates;

  std::tie(rules, updates) = load_file(fname);
  part_one(rules, updates);
}
