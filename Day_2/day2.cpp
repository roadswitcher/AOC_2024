#include <algorithm>
#include <fstream>
#include <iostream>
#include <numeric>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

using input_report = std::vector<int>;

bool report_is_safe(input_report report) {
  // Heard about this on the ADSP podcast -- finally, an excuse to use it?
  std::adjacent_difference(report.begin(), report.end(), report.begin());
  // If any difference is zero, fail
  if (std::find(report.begin(), report.end(), 0) != report.end())
    return false;

  // Are all the differences in the range of 1 to 3?
  for (int num : report) {
    if (abs(num) < 1 || abs(num) > 3)
      return false;
  }

  // Are all the differences the same sign?
  for (int num : report) {
    if ((report[0] > 0 && num <= 0) || (report[0] < 0 && num >= 0)) {
      return false;
    }
  }

  return true;
}

void process_reports(std::string filename) {
  std::ifstream fs(filename);
  input_report test_report;
  std::string line;
  int a, b, c, d, e;

  int num_safe = 0;

  while (std::getline(fs, line)) {
    std::istringstream values(line);
    std::cout << line << "\n";
    values >> a >> b >> c >> d >> e;
    test_report.push_back(a);
    test_report.push_back(b);
    test_report.push_back(c);
    test_report.push_back(d);
    test_report.push_back(e);

    if (report_is_safe(test_report))
      num_safe += 1;
  }

  std::cout << "Number of safe reports: " << num_safe << "\n";
}

int main() {
  std::string fname = "input.txt";
  process_reports(fname);
  // location_vector list_a, list_b;
  // std::tie(list_a, list_b) = read_location_lists("input.txt");

  // std::cout << part1(list_a, list_b) << "\n";
  // std::cout << part2(list_a, list_b) << "\n";

  return 0;
}
