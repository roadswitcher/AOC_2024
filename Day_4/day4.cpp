#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

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
    for (auto i = 0; i < line.length(); i++) {
      row.push_back(line[i]);
    }
    puzzle.push_back(row);
    height++;
  }

  std::cout << "Puzzle is " << width << " x " << height << " in size.\n";

  return puzzle;
}

void print_puzzle(wordsearch puzzle) {
  for (size_t row = 0; row < puzzle.size(); row++) {
    for (size_t col = 0; col < puzzle[row].size(); col++) {
      std::cout << puzzle[row][col] << " ";
    }
    std::cout << std::endl;
  }
}

int count_occurrences(std::string line, std::string substring) {
  int count{0};
  size_t pos_substr = line.find(substring, 0);
  while (pos_substr != std::string::npos) {
    count++;
    pos_substr = line.find(substring, pos_substr + 1);
  }
  return count;
}

std::vector<std::string> get_diagonals_out(wordsearch puzzle,
                                           std::string searchword) {
  std::vector<std::string> diagonals{};
  int height = puzzle.size();
  int width = puzzle[0].size();
  int buffer_size = searchword.length();

  // Get main diagonal, top left->bottom right
  std::string tmp_string = "";
  int startrow = 0;
  int startcol = 0;

  auto row = startrow;
  auto col = startcol;
  while (row < height) {
    tmp_string += puzzle[row][col];
    row++;
    col++;
  }
  diagonals.push_back(tmp_string);

  // Get other diagonal
  tmp_string = "";
  startrow = height - 1;
  startcol = 0;

  row = startrow;
  col = startcol;
  while (col < width) {
    tmp_string += puzzle[row][col];
    row--;
    col++;
  }

  diagonals.push_back(tmp_string);

  // Get lesser diags, down and right
  // above main diag, down and to right
  startrow = 0;
  for (auto startcol = 1; startcol <= (width - buffer_size); startcol++) {
    int row = startrow;
    int col = startcol;
    tmp_string = "";
    while (col < width) {
      tmp_string += puzzle[row][col];
      row++;
      col++;
    }
    diagonals.push_back(tmp_string);
  }
  // below main diag, down and to right
  startcol = 0;
  for (auto startrow = 1; startrow <= (height - buffer_size); startrow++) {
    int row = startrow;
    int col = startcol;
    tmp_string = "";
    while (row < height) {
      tmp_string += puzzle[row][col];
      row++;
      col++;
    }
    diagonals.push_back(tmp_string);
  }
  // below main diag, up and to right
  startrow = height - 1;
  for (auto startcol = 1; startcol <= (width - buffer_size); startcol++) {
    int row = startrow;
    int col = startcol;
    tmp_string = "";
    while (col < width) {
      tmp_string += puzzle[row][col];
      row--;
      col++;
    }
    diagonals.push_back(tmp_string);
  }
  // above main diag, up and to right
  startcol = 0;
  for (auto startrow = height - 2; startrow >= buffer_size - 1; startrow--) {
    int row = startrow;
    int col = startcol;
    tmp_string = "";
    while (row >= 0) {
      tmp_string += puzzle[row][col];
      row--;
      col++;
    }
    diagonals.push_back(tmp_string);
  }

  return diagonals;
}

void part_one(wordsearch puzzle, std::string str) {
  int num_found{0};
  std::string rev_str = str;
  std::reverse(rev_str.begin(), rev_str.end());

  int strlength = str.length();
  int height = puzzle.size();
  int width = puzzle[0].size();

  // search the *rows*
  for (auto row = 0; row < height; row++) {
    std::string row_text;
    for (auto ch : puzzle[row]) {
      row_text += ch;
    }
    num_found += count_occurrences(row_text, str);
    num_found += count_occurrences(row_text, rev_str);
  }

  // search the *columns*
  for (auto col = 0; col < width; col++) {
    std::string col_text;
    for (auto row = 0; row < puzzle.size(); row++) {
      col_text += puzzle[row][col];
    }
    num_found += count_occurrences(col_text, str);
    num_found += count_occurrences(col_text, rev_str);
  }
  // search the *diagonals*
  // I'm feeling _unnecessarily annoyed by diagonals_
  auto diagonals = get_diagonals_out(puzzle, str);
  for (auto line : diagonals) {
    num_found += count_occurrences(line, str);
    num_found += count_occurrences(line, rev_str);
  }

  std::cout << "Part 1: Number found: " << num_found << "\n";
}

void part_two(wordsearch puzzle) {
  // Look for X-MAS
  int count{0};
  int height = puzzle.size();
  int width = puzzle[0].size();
  char xmas_a = 'A';

  for (auto row = 1; row < height - 1; row++) {
    for (auto col = 1; col < width - 1; col++) {
      if (puzzle[row][col] == xmas_a) {
        auto tl = puzzle[row - 1][col - 1];
        auto tr = puzzle[row - 1][col + 1];
        auto bl = puzzle[row + 1][col - 1];
        auto br = puzzle[row + 1][col + 1];
        if ((br == bl && tr == tl) || (tl == bl && tr == br)) {
          count += 1;
        }
      }
    }
  }
  std::cout << "Part Two count: " << count << "\n";
}
int main() {
  // std::string fname = "test_input.txt";
  std::string fname = "input.txt";
  std::string str = "XMAS";

  wordsearch puzzle = load_puzzle(fname);
  // print_puzzle(puzzle);
  std::cout << "\n\n";

  part_one(puzzle, str);
  part_two(puzzle);
}