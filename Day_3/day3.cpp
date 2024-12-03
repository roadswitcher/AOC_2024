#include <iostream>
#include <regex>
#include <fstream>
#include <string>

// part 1:
// obvious approach:
// - iterate over the file
// - use regex to find non corrupted mul() instructions
// - use an accumulator variable to keep running sum of mul()s as they're found
//   ( use int of appropriate type )


int main(){
  std::string fname = "test_input.txt"

  // use capture groups, because reasons
  std::regex multiply_pattern(R"(mul\((\d+),(\d+)\))");
  
}