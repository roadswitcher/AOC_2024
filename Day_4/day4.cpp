#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using wordsearch = std::vector<std::vector<char>>;

wordsearch load_puzzle(std::string filename) {
  std::ifstream fs(filename);
  std::string line{};
  wordsearch puzzle{};
  int width{0};
  int height{0};

  while (std::getline(fs, line)) {
    std::vector<char> row;
    width = line.length();
    for (auto i = 0; i<line.length(); i++){
      row.push_back(line[i]);
    }
    puzzle.push_back(row);
    height++;
  }

  std::cout << "Puzzle is " << width << " x " << height << " in size.\n";

  return puzzle;
}

void print_puzzle(wordsearch puzzle){
  for (size_t row=0; row<puzzle.size(); row++){
    for (size_t col=0; col<puzzle[row].size(); col++){
      std::cout << puzzle[row][col];
    }
    std::cout << std::endl;
  }
}

int count_occurrences(std::string line, std::string substring){
  int count{0};
  size_t pos_substr = line.find(substring, 0);
  while (pos_substr != std::string::npos) {
    count++;
    pos_substr = line.find(substring, pos_substr + 1);
  }
  return count;
}

void part_one(wordsearch puzzle, std::string str){
  int num_found{0};
  std::string rev_str = str;
  std::reverse(rev_str.begin(), rev_str.end());

  int strlength = str.length();
  int height = puzzle.size();
  int width = puzzle[0].size();
  // OK, this is how it's going down.
  // - First, search for the word reading L->R
  //   in each row starting at column 0, ending
  //   at column (width - length of word)
  // - Then, search by row for the word reading 
  //   BACKWARDS, but starting at 0+length of word
  // - Then, we do the diagonals but be mindful of
  //   the edges compared to length of the word

  // search the *rows*
  for (auto row = 0; row<height; row++){
    std::string row_text;
    for( auto ch : puzzle[row]){
      row_text+=ch;
    }
    num_found += count_occurrences(row_text, str);
    num_found += count_occurrences(row_text, rev_str);
  }
  
  // search the *columns*
  for (auto col = 0; col<width; col++){
    std::string col_text;
    for( auto row =0; row<puzzle.size(); row++){
      col_text += puzzle[row][col];
    }
    num_found += count_occurrences(col_text, str);
    num_found += count_occurrences(col_text, rev_str);
  }
  // search the *diagonals*


  std::cout << "Part 1: Number found: " << num_found << "\n";

}

int main() {
  std::string fname = "test_input.txt";
  std::string str = "XMAS";

  wordsearch puzzle = load_puzzle(fname);
  print_puzzle(puzzle);
  // int height = puzzle.size();
  // int width = (height > 0) ? puzzle[0].size() : 0;
  // std::cout << width << " wide x " << height << " high\n.";

  part_one(puzzle, str);
  // part_two(puzzle);
}