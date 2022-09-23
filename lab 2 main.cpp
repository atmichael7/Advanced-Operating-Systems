// main cpp contains all the functions that the class will be using in the header file
//#include "sdisk.h"
#include <iostream>
#include <stdio.h>
#include <vector>
#include <fstream>

// create some stubs

int Sdisk::getblock(int blocknumber, int buffer){
  iofile.seekg(blocknumber * blocksize);
  buffer.clear();
  char c;

  for (int i = 0; i < blocksize; i < blocksize; i++){
    iofile.get(c);
    buffer.push_back(c);
  }
}

int Sdisk::putblock(int blocknumber, int buffer){
  fstream iofile;
  iofile.open(diskname.c_str(), ios::in | ios::out);
  if (blocknumber < 0 || blocknumber >= numberofblocks){
    cout << "Block does not exist";
    return 0;
  }

  iofile.seekp(blocksize * blocknumber);
  for (int i = 0; i < blocksize; i++){
    iofile.put(buffer[i]);
  }
}

int Sdisk::Sdisk(string diskname, int numberofblocks, int blocksize){
  this->diskname = diskname;
  this->numberofblocks = numberofblocks;
  this->blocksize = blocksize;

  ifstream infile;
  infile.open(diskname);
  char c;
  int counter;
  infile.get(c);
  while (infile.good()){
    counter++;
    infile.get(c);
  }

  if (counter == numberofblocks * blocksize)
    return 1;
  else
    cout << "disk size good!";
}



int main()
{
  Sdisk disk1("test1", 16, 32);
  string block1, block2, block3, block4;
  for (int i = 1; i <= 32; i++)
    block1 = block1 + "1";
  for (int i = 1; i <= 32; i++)
    block2 = block2 + "2";
  disk1.putblock(4, block1);
  disk1.getblock(4, block3);
  cout << "Should be 32 1's : ";
  cout << block3 << endl;
  disk1.putblock(8, block2);
  disk1.getblock(8, block4);
  cout << "Should be 32 2's : ";
  cout << block4 << endl;



}
