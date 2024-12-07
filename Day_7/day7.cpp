#include <fstream>
#include <iostream>
#include <optional>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>
#include <cstdint>


struct calibration_equation {
  uint64_t result{};
  std::vector<uint64_t> terms;
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

bool check_equation(calibration_equation &eqn) {
  uint64_t result = eqn.terms[0];

  for (size_t op = 0; op < eqn.operations.size(); op++) {
    if (eqn.operations[op] == '+') {
      result += eqn.terms[op + 1];
    } else {
      result *= eqn.terms[op + 1];
    }
  }
  return result == eqn.result;
}

void print_eqn(const calibration_equation &eqn) {
  int num_terms = eqn.terms.size();
  std::cout << eqn.result << ":";
  int term{0};
  while(term<=num_terms-2){
    std::cout << eqn.terms[term] << " " << eqn.operations[term] << " ";
    term+=1;
  }
  std::cout << eqn.terms[num_terms-1] << std::endl;
}

uint64_t sum_test_vals(const calibration_list& eqns){
  uint64_t sum = 0;
  for (auto& eqn : eqns){
    sum += eqn.result;
  }
  return sum;
}

std::vector<std::vector<char>> computed_op_permutations(const int &num_ops) {
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

void part_one(calibration_list &eqns) {
  calibration_list valid_eqns;
  uint64_t sum{0};

  for (auto &eqn : eqns) {
    const int num_of_ops = eqn.terms.size() - 1;
    calibration_equation test_eqn;
    std::vector<std::vector<char>> permutations =
        computed_op_permutations(num_of_ops);

    test_eqn.result = eqn.result;
    test_eqn.terms = eqn.terms;

    for (size_t i = 0; i < permutations.size(); i++) {
      test_eqn.operations = permutations[i];
      bool validated = check_equation(test_eqn);
      if (validated) {
        print_eqn(test_eqn);
        valid_eqns.push_back(test_eqn);
        sum+=test_eqn.result;
        break;
      }
    }
  }
  std::cout << "Pt 1: Num valid eqns: " << valid_eqns.size() << " Sum of results: " << sum << "\n";
}
int main() {
  std::string fname = "input.txt";
  calibration_list calibrations = loader(fname);

  part_one(calibrations);
}