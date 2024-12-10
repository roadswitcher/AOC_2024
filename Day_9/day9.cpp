#include <iostream>
#include <fstream>
#include <vector>

using block_fs = std::vector<int>;



void add_file(const int& size, int& file_id, block_fs& filesystem){
  for( auto s=0; s< size; s++){
    filesystem.push_back(file_id);
  }
  file_id++;
}

void add_space(const int& size, block_fs &filesystem){
  for ( auto s=0; s<size; s++){
    filesystem.push_back(-1);
  }
}

void part_one(std::string fname){
  std::ifstream fs(fname);
  block_fs filesystem;
  int block=0;
  int file_id{0};
  char ch;
  while(fs.get(ch)){
    int size = ch - '0';
    if(block%2==0){
      add_file(size, file_id, filesystem);
    } else {
      add_space(size, filesystem);
    }
    block++;    
  }

  std::cout << "\n" << filesystem.size() << std::endl << std::endl;
  for(int blk=0; blk<=filesystem.size(); blk++){
    std::cout<<filesystem[blk]<<std::endl;
  }

}
int main(){

  std::string fname = "input.txt";

  part_one(fname);

}