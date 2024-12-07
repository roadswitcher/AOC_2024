#include <fstream>
#include <iostream>
#include <optional>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

struct calibration_equation {
  int result;
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
    eqn.result = std::stoi(substring);

    int tmp{};
    while (iss >> tmp) {
      eqn.terms.push_back(tmp);
    }

    list.push_back(eqn);
  }
  return list;
}

bool check_equation(calibration_equation &eqn) {
  int result = eqn.terms[0];

  for (size_t op = 0; op < eqn.operations.size(); op++) {
    if (eqn.operations[op] == '+') {
      result += eqn.terms[op + 1];
    } else {
      result *= eqn.terms[op + 1];
    }
  }
  return result == eqn.result;
}

vector<vector<char>> computed_op_permutations(const int &num_ops) {
  std::vector<std::vector<char>> permutations(1 << num_ops);

  for (unsigned long int i = 0; i < (1 << num_ops); i++) {
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

  for (auto &eqn : eqns) {
    const int num_of_ops = eqn.terms.size();
    calibration_equation test_eqn;
    const vector<vector<char>> permutations = computed_op_permutations(num_of_ops);

    test_eqn.result = eqn.result;
    test_eqn.terms = eqn.terms;

  }
  std::cout << "Pt 1: Num valid eqns: " << valid_eqns.size() << "\n";
}
int main() {
  std::string fname = "test_input.txt";
  calibration_list calibrations = loader(fname);

  part_one(calibrations);
}