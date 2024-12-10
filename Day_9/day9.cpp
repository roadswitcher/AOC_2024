#include <fstream>
#include <iostream>
#include <vector>

using block_fs = std::vector<int>;

void add_file(const int &size, int &file_id, block_fs &filesystem) {
  for (auto s = 0; s < size; s++) {
    filesystem.push_back(file_id);
  }
  ++file_id;
}

void add_space(const int &size, block_fs &filesystem) {
  for (auto s = 0; s < size; s++) {
    filesystem.push_back(-1);
  }
}

void print_fs(const block_fs &filesystem) {
  for (int blk = 0; blk <= filesystem.size(); blk++) {
    if (filesystem[blk] > -1) {
      std::cout << filesystem[blk];
    } else {
      std::cout << ".";
    }
  }
  std::cout << std::endl;
}

bool process_free_space(block_fs &filesystem) {
  int leftmost_empty = -1;
  int rightmost_nonempty = -1;
  bool not_done = true;

  for (int i = 0; i < filesystem.size(); i++) {
    if (filesystem[i] == -1) {
      leftmost_empty = i;
      break;
    }
  }
  for (int j = filesystem.size() - 1; j > 0; --j) {
    if (filesystem[j] > -1) {
      rightmost_nonempty = j;
      break;
    }
  }

  if (leftmost_empty != -1 && rightmost_nonempty != -1 &&
      leftmost_empty != rightmost_nonempty &&
      leftmost_empty < rightmost_nonempty) {
    std::swap(filesystem[leftmost_empty], filesystem[rightmost_nonempty]);
  } else {
    return false;
  }

  print_fs(filesystem);

  return true;
}

long int compute_checksum(const block_fs &filesystem){
  long int checksum{0};

  for(int blk=0; blk<filesystem.size(); blk++){
    if(filesystem[blk]>0){
      checksum += ( blk * filesystem[blk] );
    }
  }
  return checksum;
}

void part_one(std::string fname) {
  std::ifstream fs(fname);
  block_fs filesystem;
  int block = 0;
  int file_id=0;
  char ch;
  while (fs.get(ch)) {
    int size = ch - '0';
    if (block % 2 == 0) {
      add_file(size, file_id, filesystem);
    } else {
      add_space(size, filesystem);
    }
    block++;
  }

  print_fs(filesystem);

  bool not_done = true;
  while (not_done) {
    not_done = process_free_space(filesystem);
  }

  print_fs(filesystem);

  std::cout << "Pt 1 checksum: " << compute_checksum(filesystem) << std::endl;
}

int main() {
  std::string fname = "test_input.txt";
  part_one(fname);
//  part_two(fname);
}
