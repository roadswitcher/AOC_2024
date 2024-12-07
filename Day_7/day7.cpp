#include <cmath>
#include <cstdint>
#include <cstring>
#include <fstream>
#include <iostream>
#include <optional>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

struct calibration_equation {
  uint64_t result{};
  std::vector<int> terms;
  std::vector<char> operations;
};

using calibration_list = std::vector<calibration_equation>;

calibration_list loader(const std::string &filename) {
  std::ifstream fs(filename);
  std::string line{};
  calibration_list list;

  while (std::getline(fs, line)) {
    std::istringstream iss(line);
    std::string substring{};
    calibration_equation eqn;

    std::getline(iss, substring, ':');
    eqn.result = std::stoull(substring);

    uint64_t tmp{};
    while (iss >> tmp) {
      eqn.terms.push_back(tmp);
    }

    list.push_back(eqn);
  }
  return list;
}

void print_eqn(const calibration_equation &eqn) {
  int num_terms = eqn.terms.size();
  std::cout << eqn.result << " : ";
  int term{0};
  while (term <= num_terms - 2) {
    std::cout << eqn.terms[term] << " " << eqn.operations[term] << " ";
    term += 1;
  }
  std::cout << eqn.terms[num_terms - 1] << std::endl;  
}

bool check_equation(calibration_equation &eqn) {
  uint64_t computed_sum = (uint64_t)eqn.terms[0];

  for (uint64_t idx = 0; idx < eqn.operations.size(); idx++) {
    auto next_term = eqn.terms[idx + 1];
    auto op = eqn.operations[idx];
    if (op == '|') { // concatentate this
      computed_sum = std::stoull(std::to_string(computed_sum) + std::to_string(next_term));
    }
    if (op == '*') {
      computed_sum *= next_term;
    }
    if (op == '+') {
      computed_sum += next_term;
    }
  }

  return (computed_sum == eqn.result);
}

uint64_t sum_test_vals(const calibration_list &eqns) {
  uint64_t sum = 0;
  for (auto &eqn : eqns) {
    sum += eqn.result;
  }
  return sum;
}

std::vector<std::vector<char>> binary_permutations(const int &num_ops) {
  std::vector<std::vector<char>> permutations(1 << num_ops);
  for (int i = 0; i < (1 << num_ops); i++) {
    std::string tmp = "";
    for (auto bit = 0; bit < num_ops; bit++) {
      char ch = (i & (1 << bit)) ? '*' : '+';
      permutations[i].push_back(ch);
    }
  }
  return permutations;
}

std::vector<std::vector<char>> trinary_permutations(const int &num_ops) {
  int num_perms = 1;
  std::vector ops = {'*', '+', '|'}; // Using single pipe to keep it char-based
  for (int i = 0; i < num_ops; i++) {
    num_perms *= 3;
  }
  std::vector<std::vector<char>> permutations;

  for (int i = 0; i < num_perms; i++) {
    std::vector<char> perm;
    int temp = i;
    for (int j = 0; j < num_ops; j++) {
      perm.push_back(ops[temp % 3]);
      temp /= 3;
    }
    permutations.push_back(perm);
  }
  return permutations;
}

void part_one(calibration_list &eqns) {
  calibration_list valid_eqns;
  calibration_list invalid_eqns;
  uint64_t sum{0};

  for (auto &eqn : eqns) {
    const int num_of_ops = eqn.terms.size() - 1;
    calibration_equation test_eqn;
    std::vector<std::vector<char>> permutations =
        binary_permutations(num_of_ops);

    test_eqn.result = eqn.result;
    test_eqn.terms = eqn.terms;
    bool validated = false;
    for (size_t i = 0; i < permutations.size(); i++) {
      test_eqn.operations = permutations[i];
      validated = check_equation(test_eqn);
      if (validated) {
        valid_eqns.push_back(test_eqn);
        sum += test_eqn.result;
        break;
      }
    }
    if (!validated) {
      invalid_eqns.push_back(eqn);
    }
  }
  std::cout << "Pt 1: Num valid eqns: " << valid_eqns.size()
            << " Sum of results: " << sum << "\n";
  std::cout << "Invalid count: " << invalid_eqns.size() << std::endl;
}

void part_two(calibration_list &eqns) {
  calibration_list valid_binary_eqns;
  calibration_list valid_trinary_eqns;
  calibration_list invalid_eqns;
  uint64_t sum{0};

  // check binary first
  for (auto &eqn : eqns) {
    const int num_of_ops = eqn.terms.size() - 1;
    calibration_equation test_eqn;
    std::vector<std::vector<char>> binary_perms =
        binary_permutations(num_of_ops);
    std::vector<std::vector<char>> trinary_perms =
        trinary_permutations(num_of_ops);

    test_eqn.result = eqn.result;
    test_eqn.terms = eqn.terms;
    bool validated = false;

    for (size_t i = 0; i < binary_perms.size(); i++) {
      test_eqn.operations.clear();
      test_eqn.operations = binary_perms[i];
      validated = check_equation(test_eqn);
      if (validated) {
        valid_binary_eqns.push_back(test_eqn);
        sum += test_eqn.result;
        break;
      }
    }
    if (!validated) { // If we passed thru here, it's possibly trinary
      for (size_t i = 0; i < trinary_perms.size(); i++) {
        test_eqn.operations.clear();
        test_eqn.operations = trinary_perms[i];
        validated = check_equation(test_eqn);
        if (validated) {
          valid_trinary_eqns.push_back(test_eqn);
          sum += test_eqn.result;
          break;
        }
      }
    }

    if (!validated) {
      // std::cout << "BAD ";
      // print_eqn(test_eqn);
      invalid_eqns.push_back(eqn);
    }
  }

  std::cout << "Pt 2: Num valid eqns: " << valid_binary_eqns.size()
            << "\nTrinary " << valid_trinary_eqns.size()
            << " \nSum of results: " << sum << "\n";
  std::cout << "Invalid count: " << invalid_eqns.size() << std::endl;
}

int main() {
  std::string fname = "input.txt";
  calibration_list calibrations = loader(fname);

  part_one(calibrations);
  part_two(calibrations);
}