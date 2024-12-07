#include <fstream>
#include <iostream>
#include <regex>
#include <unordered_map>
#include <vector>

using labmap = std::vector<std::vector<char>>;

labmap loadfile(std::string& filename){
  labmap resulting_map;
  
  std::ifstream fs(filename);
  std::string line{};
  
  while(std::getline(fs, line)){
    std::vector<char> row;
    for (size_t i = 0; i < line.length(); i++) {
      row.push_back(line[i]);
    }
    resulting_map.push_back(row);
  }
  return resulting_map;
}

int main(){
  std::string fname = "test_input.txt";

  labmap the_map=loadfile(fname);
  std::cout << the_map.size() << std::endl;

}