#include "sdisk.h"

Sdisk::Sdisk(string diskname, int numberofblocks, int blocksize){
  this->diskname = diskname;
  this->numberofblocks = numberofblocks;
  this->blocksize = blocksize;

  ifstream infile;
  infile.open(diskname);

  if (infile.fail()){
    infile.close();
    ofstream outdisk;
    outdisk.open(diskname.c_str());
    for (int i = 0; i < numberofblocks * blocksize; i++){
      outdisk.put('#');
    }
    cout << "\nFile does not exist, created new file '" << diskname.c_str() << "'\n";
  }

  else{
    char c;
    int counter;
    infile.get(c);
    while (infile.good()){
      counter++;
      infile.get(c);
    }

    if (counter == numberofblocks * blocksize)
      cout << "\nDisk format: FAIL\n";
    else
      cout << "\nDisk format: OK\n";
  }
  return;


}

int Sdisk::getblock(int blocknumber, string& buffer){
  fstream iofile;
  iofile.open(diskname.c_str(), ios::in | ios::out);
  iofile.seekg(blocknumber * blocksize);
  buffer.clear();
  char c;

  for (int i = 0; i < blocksize; i++){
    iofile.get(c);
    buffer.push_back(c);
  }
  return 1;
}


int Sdisk::putblock(int blocknumber, string buffer){
  fstream iofile;
  iofile.open(diskname.c_str(), ios::in | ios::out);
  if (blocknumber < 0 || blocknumber >= numberofblocks){
    cout << "Block does not exist";
    return 0;
  }

  iofile.seekp(blocksize * blocknumber);
  for (int i = 0; i < blocksize; i++){
    iofile.put(buffer.at(i));
  }
  return 1;
}


int Sdisk::getnumberofblocks(){
  return numberofblocks;
}

int Sdisk::getblocksize(){
  return blocksize;
}
