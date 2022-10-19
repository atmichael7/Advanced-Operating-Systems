#include "filesys.h"


Filesys::Filesys(string diskname, int numberofblocks, int blocksize){
  // need to set the root size then set the fat size

  // check if there is a file system on the disk already
  string buffer;
  getblock(1, buffer);
  if (buffer[0] == "#"){ // means the disk is not formatted
    buildfs();
    fssynch();
  }
  else{ // disk has been formatted already so read it in
    readfs();
  }
}

// might need to change the string block input to buffer since thats what he did in the notes
int addblock(string file, string block){
  int allocate = fat[0];
  if (allocate <= 0){
    cout <, "No space on disk!";
    return 0;
  }

  int blockid = getfirstblock(file);
  if (blockid == 0){
    // update the root
    for (int i = 0; i < filename.size(); i++){
      firstblock[i] = allocate;
      break;
    }
  }
  else{
    // update fat... find the end of file
    while (fat[blockid] != 0){
      blockid = fat[blockid];
    }
    // fat[blockid] = 0;
    fat[blockid] = allocate;
  }
  fat[0] = fat[fat[0]];
  fat[allocate] = 0;
  fssynch();

  putblock(allocate, buffer);

  return allocate;
}

//##############################################################################

int delblock(string file, int blocknumber){return 1;}
int readblock(string file, int blocknumber, string& buffer){return 1;}
int writeblock(string file, int blocknumber, string buffer){return 1;}
int nextblock(string file, int blocknumber){return 1;}

//##############################################################################

int fsclose(){
  // do nothing
}

//##############################################################################

int newfile(string file){
  // create empty file
  // -1 means file already exists
  // 0 no room left
  // 1 success

  // check if file already exists
  for (int i = 0; i < filename.size(); i++){
    if (filename[i] == file){
      return -1;
    }
  }

  // see if there are some xxxxxx in the filename vector
  for (int i = 0; i < filename.size(); i++){
    if (filename[i] == "xxxxxx"){
      // know we have an entry to put the file at
      filename[i] = file;
      firstblock[i] = 0;
      synch(); // need to save the root directory after changes
      return 1;
    }
    return 0; // otherwise there is no space so return 0
  }
}

//##############################################################################

int rmfile(string file){
    // remove file that is empty
    // -1 file diskname
    // 0 file not empty
    // 1 success

    for (int i = 0; i < filename.size(); i++){
      if (filename[i] == file){
        if (firstblock[i] == 0){
          // found the file and its firstblock is empty
          filename[i] = "xxxxxx";
          fssynch();
          return 1;
        }
        // firstblock is not zero thus not empty
        return 0;
      }
      // file does not exist
      return -1;
    }
}

//##############################################################################

int getfirstblock(string file){
  // -1 file does not exist  if the first block is zero
  // return firstblock number of the file

  for (int i = 0; i < filename.size(); i++){
    if (filename[i] == file){
      // found file so return its first block
      return firstblock[i];
    }
  }
  // could not find the file after the loop, thus does not exist
  return -1;
}

//##############################################################################

Filesys::readfs(){
  string buffer1, buffer2;
  getblock(1, buffer1);
  for (int = 0; i < fatsize; i++){
    string b;
    getblock(i+2, b);
    buffer2 += b;
  }

  istringstream instream 1;
  istringstream instream 2;
  instream1.str(buffer1);
  instream2.str(buffer2);

  filename.clear();
  firstblock.clear();
  for (int i = 0; i < rootsize; i++){
    string f;
    int b;
    instream1 >> f >> b;
    filename.push_back(f);
    firstblock.push_back(b);
  }

  for (int i = 0; i < getnumberofblocks; i++){
    int k;
    instream2 >> k;
    fat.push_back(k);
  }
  return 1;
}

//##############################################################################
// PRIVATE FUNCTIONS FROM THE HEADER FILE
//##############################################################################

int rootsize;           // maximum number of entries in ROOT
int fatsize;            // number of blocks occupied by FAT
vector<string> filename;   // filenames in ROOT
vector<int> firstblock; // firstblocks in ROOT
vector<int> fat;             // FAT

// builds the file system
int buildfs(){
  for (int i = 0; i < rootsize; i++){
    filename.push_back("XXXXXX");
    firstblock.push_back(0);
  } // after the loop the root has been built

  // populate the index 0 through fatsize+2 of the FAT
  fat.push_back(2+fatsize);
  fat.push_back(-1);
  for (int i = 0; i < fatsize; i++){
    fat.push_back(-1);
  }

  // now populate the rest of the FAT so start at the index 2+fatsize
  for (int i = 2+fatsize; i < getnumberofblocks(); i++){
    fat.push_back(i+1);
  }

  // so the tailend isnt pointing to something that doesnt exist in the space
  fat[fat.size()-1] = 0;

  return 1; // success
}

int readfs() // reads the file system

// writes the FAT and ROOT to the sdisk
int fssynch(){
  // synch file system
  // call this whenever modifying any part of the FAT or the root
  ostringstream outstream1, outstream2;
  for (int i = 0; i < firstblock.size(); i++){
    outstream2 << fat[i] << " "; // writing to FAT
  }

  string buffer1 = outstream1.str();
  string buffer2 = outstream2.str();

  vector <string> blocks1 = block(buffer1, getblocksize());
  vector <string> blocks2 = block(buffer2, getblocksize());

  putblock(1, blocks1[0]); // putting root into the index 1

  for (int i = 0; i < blocks2.size(); i++){
    putblock(fatsize()=2+i, blocks2[i]);
  }
  return 1;
}
