#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <string>
#include <sstream>

struct unsolved_equation{
  int result;
  std::vector<int> terms;
  std::vector<char> operations;
};

using calibration_list = std::vector<unsolved_equation>;

calibration_list loader(const std::string& filename){
  std::ifstream fs(filename);
  std::string line{};
  calibration_list list;

  while(std::getline(fs, line)){
    std::istringstream iss(line);
    std::string substring{};
    unsolved_equation eqn;
    std::vector<int> terms;

    std::getline(iss, substring, ':');
    eqn.result = std::stoi(substring);
    std::cout << "result " << eqn.result << "\n";
    
    while(std::getline(iss, substring, ',')){
      std::cout << substring << " ";
      eqn.terms.push_back(std::stoi(substring));
    }
    std::cout << "\n";
    list.push_back(eqn);
  }
  return list;
}

int main(){
  std::string fname = "test_input.txt";
  calibration_list calibrations = loader(fname);

}