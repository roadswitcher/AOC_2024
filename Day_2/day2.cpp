#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <numeric>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

using input_report = std::vector<int>;

bool report_is_safe(input_report report) {
  // Heard about this on the ADSP podcast -- finally, an excuse to use it?
  std::adjacent_difference(report.begin(), report.end(), report.begin());
  report.erase(report.begin()); // drop the first element

  // If any difference is zero, fail
  if (std::find(report.begin(), report.end(), 0) != report.end())
    return false;

  // Are all the differences in the range of 1 to 3?  Do all elements have the same sign? ( trending DOWN or UP? )
  for (int num : report) {
    if ((abs(num) < 1 || abs(num) > 3) || (report[0] > 0 && num <= 0) || (report[0] < 0 && num >= 0) ) {
      return false;
    }
  }

  return true;
}

bool problem_dampener(input_report report) {
  // If report can be rendered safe removing a single element, it's safe.
  for (int idx = 0; idx < report.size(); idx++) {
    input_report tmp_report;
    for (int j = 0; j < report.size(); j++) {
      if (j != idx)
        tmp_report.push_back(report[j]);
    }
    if (report_is_safe(tmp_report)) {
      return true;
    }
  }
  // Fell thru, return false
  return false;
}

void process_reports(std::string filename) {
  std::ifstream fs(filename);

  std::string line;
  int num_safe = 0;
  int made_safe_by_damping = 0;

  while (std::getline(fs, line)) {
    std::istringstream values(line);
    int num;
    input_report test_report;
    while (values >> num) {
      test_report.push_back(num);
    }

    if (report_is_safe(test_report)) {
      num_safe += 1;
    } else if (problem_dampener(test_report)) {
      made_safe_by_damping += 1;
    }
  }
  std::cout << "Part 1: Number of safe reports: " << num_safe << "\n";
  std::cout << "Part 2: Number of safe reports: "
            << num_safe + made_safe_by_damping << "\n";
}

int main() {
  std::string fname = "input.txt";
  // std::string fname = "test_input.txt";

  process_reports(fname);

  return 0;
}
