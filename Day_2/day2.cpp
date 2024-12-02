#include <algorithm>
#include <fstream>
#include <iostream>
#include <numeric>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

using input_report=std::vector<int>;

bool report_is_safe(input_report){
  bool result = true; // assuming true till it fails
  // Heard about this on the ADSP podcast -- finally, an excuse to use it?
  std::adjacent_difference(input_report.begin(), input_report.end(), input_report.begin());
  // If any difference is zero, fail
  if ( std::find(input_report.begin(), input_report.end(), 0) != input_report.end() ) result=false;

  // Are all the differences in the range of 1 to 3?
  
  // Are all the differences the same sign?

  return result;
}
void process_reports(filename){
  std::ifstream fs(filename);
  input_report test_report;
  std::string line;
  int a,b,c,d,e;

  int num_safe = 0;

  while (std::getline(fs, line)) {
    std::istringstream values(line);
    values >> a >> b >> c >> d >> e;
    test_report.push_back(a);
    test_report.push_back(b);
    test_report.push_back(c);
    test_report.push_back(d);
    test_report.push_back(e);
  }

}

int main() {
  location_vector list_a, list_b;
  std::tie(list_a, list_b) = read_location_lists("input.txt");

  std::cout << part1(list_a, list_b) << "\n";
  std::cout << part2(list_a, list_b) << "\n";

  return 0;
}
