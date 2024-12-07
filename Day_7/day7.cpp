#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <string>
#include <sstream>
#include <optional>

struct calibration_equation{
  int result;
  std::vector<int> terms;
  std::vector<char> operations;
};

using calibration_list = std::vector<calibration_equation>;

calibration_list loader(const std::string& filename){
  std::ifstream fs(filename);
  std::string line{};
  calibration_list list;

  while(std::getline(fs, line)){
    std::istringstream iss(line);
    std::string substring{};
    calibration_equation eqn;

    std::getline(iss, substring, ':');
    eqn.result = std::stoi(substring);
    
    int tmp{};
    while(iss>>tmp){
      eqn.terms.push_back(tmp);
    }

    list.push_back(eqn);
  }
  return list;
}

bool check_equation(calibration_equation& eqn){
  int result = eqn.terms[0];

  for(size_t op = 0; op<eqn.operations.size(); op++){
    if(eqn.operations[op]=='+'){
      result += eqn.terms[op+1];
    } else {
      result *= eqn.terms[op+1];
    }
  }
  return result == eqn.result;
}


void part_one(calibration_list& eqns){
  calibration_list valid_eqns;

  for(auto& eqn : eqns){
    int num_of_ops = eqn.terms.size();
    calibration_equation test_eqn;

    test_eqn.result = eqn.result;
    test_eqn.terms = eqn.terms;
    // iterate over all values of unsigned int of appropriate size
    // ( this will, by default, generate all permutations of 0 and 1 and we only have two operations)
    // for(unsigned long int i = 0; i < (1<<num_of_ops) ; i++){
    unsigned long int i = 0;
    do{
      for(auto bit=0; bit<num_of_ops; bit++){
        test_eqn.operations.clear();
        // 0 = add 1 = mul
        char op = ( i & ( 1 << bit )) ? '*' : '+';
        test_eqn.operations.push_back(op);
      }

      // std::cout << test_eqn.result << " " << test_eqn.terms.size() << " " << eqn.terms.size() <<"\n";
      if(check_equation(test_eqn)){
        valid_eqns.push_back(test_eqn);
        break;
      }

      i++;
    
    } while (i < ( 1<<num_of_ops));
  }
  std::cout << "Pt 1: Num valid eqns: " << valid_eqns.size() << "\n";

}
int main(){
  std::string fname = "test_input.txt";
  calibration_list calibrations = loader(fname);
  for(auto eqn:calibrations){
    std::cout << eqn.result <<"\n";
    std::cout << eqn.terms.size() << "\n";
  }
  // part_one(calibrations);

}