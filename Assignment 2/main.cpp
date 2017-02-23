//  Created by Neesarg Banglawala on 19th Feb, 2017.
//  Work completed on 21st Feb, 2017.
//  Copyright (c) 2017 Neesarg Banglawala. All rights reserved.
/*
 *
 *    Use g++ compiler to compiler. C++ 11 is used
 *
 *
 *    ##-------------------HOW TO USE----------------------##
 *    -> To compress: ./a.out -c inputFileName outputFileName
 *    -> To expand  : ./a.out -e inputFileName outputFileName
 *
 *
 */

#include<iostream>
#include<fstream>
#include<utility>
#include<vector>
#include<map>

using namespace std;



  /**********************************/
 /*********** DECLARATION **********/
/**********************************/
class Node{
public:
  char symbol;
  Node* left;
  Node* right;

  Node(char sym);
  ~Node();
};

enum operationType {
  COMPRESS,
  EXPAND,
  FAULT,
};

// Prints every bits of the byte; made it to debug
void printBitsOfByte(char byte);
// Reads next byte
bool readNextByte(char &byte, ifstream &file);
// Reads an unsignedInt(4 bytes)
bool readNextUnsignedInt(unsigned int &number, ifstream &file);
void writeNextByte(char &byte, ofstream &fout);
void writeNextUnsignedInt(unsigned int &number, ofstream &file);
// Deserialise a binary tree from file
void readBinaryTree(Node *&base, ifstream &file);
// Serialise the binary to file
void writeBinaryTree(Node *&root, ofstream &fout);
// Prints binary tree at +90degree angle; used it to debug
void printBinaryTree(Node *root, int level);
// creates SyntaxTree from vector
void createBinaryTree(Node *&root, vector< pair<Node*, int> > &leaves);
// deletes every created nodes. I used it when program exists
void deleteBinaryTree(Node *root);
// compare & return true of i<j; This function is used to sort vector
bool compareLeaves(const pair<Node*, int>&i, const pair<Node*, int>&j);

//  build map of (character, bitSequence) from binary tree
void generateCharBitCodePairFromTree(Node *&root, map<char, string> &bitCodes, string currentBitSequence);
// compress file, & return number of bytes the function compressed
unsigned int writeCompressedFileWithBitcodeMap(ifstream &sourceFile, map<char, string> &bitCodes, ofstream &targetFile);

// build map of (bitSequence, character); used it in expand operation
void generateCharodePairFromTree(Node *&root, map<string, char> &charCodes, string currentBitSequence);
// expands file, & return number of bytes written
// This method was inefficient, so later decided to not use it
// And used the next written function "writeExpandedFileWithTreeUptoBytes()", instead.
unsigned int writeExpandedFileWithCharcodeMapUptoBytes(ifstream &sourceFile, map<string, char> &charCodes, ofstream &targetFile, unsigned int bytesToExpand);
// expands file, & return number of bytes written
//    ( I'm writing this new function to improve
//      efficiency of the expand operation. )
unsigned int writeExpandedFileWithTreeUptoBytes(ifstream &sourceFile, Node *&root, ofstream &targetFile, unsigned int bytesToExpand);
// To keep track of all created nodes

static int nodeCount = 0;



  /**********************************/
 /********** MAIN FUNCTION *********/
/**********************************/
int main(int argc, char* argv[]) {
  operationType operation = operationType::FAULT;
  string inFile, outFile;

  // Working with commandline arguments
  if(argc == 4) {
    // Setting up arguments
    if( (string)argv[1] == "-c" ) {
      operation = operationType::COMPRESS;
      inFile = argv[2];
      outFile = argv[3];
    } else if( (string)argv[1] == "-e" ) {
      operation = operationType::EXPAND;
      inFile = argv[2];
      outFile = argv[3];
    }
  }

  // If wrong command, tell user to use proper instructions
  if(operation == operationType::FAULT) {
    cout<<"ERROR: Enter proper arguments!"<<endl;
    cout<<" -> To compress: \"./a.out -c inputFileName outputFileName\""<<endl;
    cout<<" -> To expand  : \"./a.out -e inputFileName outputFileName\""<<endl;
    return 1;
  } else {
    cout<<"inputFile: "<<inFile<<endl;
    cout<<"outputFile: "<<outFile<<endl;
  }

  // Start operating
  cout<<"\n---------------------";
  cout<<"\n Operating on file..";
  cout<<"\n---------------------"<<endl;

  // setup file streams
  ifstream fin(inFile, ios::binary);
  if(!fin.good()) {
    cout<<"ERROR: can not open \""<<inFile<<"\" file.."<<endl;
    return 1;
  }

  ofstream fout(outFile, ios::binary | ios::trunc);
  if(!fout.good()) {
    cout<<"ERROR: can not open \""<<outFile<<"\" file.."<<endl;
    return 1;
  }


  if(operation == operationType::COMPRESS) {
    /////////////////
    // COMPRESSION //
    /////////////////

    // Frequency of each byte
    int charFreq[256] = {0};


    // Calculate frequency
    char gotChar;
    while(readNextByte(gotChar, fin) && !fin.eof()) {
      charFreq[gotChar+128]++;  // +128 to convert range from [-128, 127] to [0, 256]. Have to do it because of the sign bit!
    }


    // Store all the leaf nodes
    vector< pair<Node*, int> > leaves;
    // total number of bytes to write (as data)
    unsigned int totalBytes = 0;
    // Create a leaves vector & calculate total data bytes to write
    for(int i=0; i<256; i++) {
      if(charFreq[i] > 0) {
        Node * node = new Node((char)(i-128));
        int frequency = charFreq[i];
        totalBytes += frequency;

        leaves.push_back( make_pair(node, frequency) );
      }
    }


    // Create binary tree to generate unique bitCodes for each byte
    Node *treeRoot;
    createBinaryTree(treeRoot, leaves);
    // printBinaryTree(treeRoot, 0);


    // Get map of <each character, its bitCode>
    map<char, string> bitCodes;
    string tempString = "";
    generateCharBitCodePairFromTree(treeRoot, bitCodes, tempString);


    // Serialise binary tree
    writeBinaryTree(treeRoot, fout);
    // Write '-' to signal that tree serialisation instructions are finished
    fout.put('-');


    // Write totalBytes in output file
    writeNextUnsignedInt(totalBytes, fout);
    cout<<"Total bytes = "<<totalBytes<<endl;

    // Write '-' to signal that compressed code starts from here
    fout.put('-');


    // Display Bitcodes
    // cout<<"\nBitcodes:"<<endl;
    // for(auto elem : bitCodes) {
    //   std::cout << elem.first << "->" << elem.second<<endl;
    // }

    // reset fin to start of file, moving on phase 2: compression!
    fin.clear();
    fin.seekg (0, ios::beg);


    // write in outputFile to compress
    unsigned int compressedTotalBytes = 0;
    compressedTotalBytes = writeCompressedFileWithBitcodeMap(fin, bitCodes, fout);

    // Check whether all the data was compressed or not
    if(compressedTotalBytes == totalBytes) {
      cout<<"successfully compressed all data!\n"<<endl;
    } else {
      cout<<"\nERROR: Operation failed!"<<endl<<"Only "<<compressedTotalBytes<<" out of "<<totalBytes<<" bytes got compressed!"<<endl;
    }

    // delete all the nodes, now program will exit
    deleteBinaryTree(treeRoot);


  } else if(operation == operationType::EXPAND) {
    ///////////////
    // EXPANSION //
    ///////////////

    // Deserialise tree of bitCodes
    Node *rootTree;
    readBinaryTree(rootTree, fin);
    cout<<"\nTree created!"<<endl;


    // Read '-' to ensure that binary serialisation instructions where correct
    char next;
    next = (char)fin.get();
    if(next != '-') {
      cout<<"FILE CORRUPTED: Could not confirm the end of tree!"<<endl;
    }

    // Get number of bytes to expand
    unsigned int bytesToExpand = 0;
    if(readNextUnsignedInt(bytesToExpand, fin)) {
      cout<<"Total Bytes = "<<bytesToExpand<<endl;
    } else {
      cout<<"FILE CORRUPTED: Could not get length of file!"<<endl;
    }

    // Read '-' to ensure start of compressed data
    next = 0;
    next = (char)fin.get();
    if(next != '-') {
      cout<<"FILE CORRUPTED: Could not confirm start of compressed data!"<<endl;
    }


    // expand the remaining file
    unsigned int expandedBytes = 0;
    // This is the 2nd method, where I directly use tree to generate codeSequence
    // Previously I was using a map, to find the sequence. Which was inefficient!
    // This one is much more efficient
    expandedBytes = writeExpandedFileWithTreeUptoBytes(fin, rootTree, fout, bytesToExpand);

    // This method was inefficient, so developed the new function written above (this one took too long to complete expand operation)
    //  -> expandedBytes = writeExpandedFileWithCharcodeMapUptoBytes(fin, charCodes, fout, bytesToExpand);

    // Confirm expandedBytes
    if(expandedBytes != bytesToExpand) {
      cout<<"ERROR: Expanded only "<<expandedBytes<<" bytes out of expected "<<bytesToExpand<<" bytes!"<<endl;
    } else {
      cout<<"Operation successfull!\n"<<endl;
    }


    deleteBinaryTree(rootTree);

  }


  fin.close();
  fout.close();
  return 0;
}



  /**********************************/
 /****** FUNCTION DEFINITIONS ******/
/**********************************/
Node::Node(char sym) {
  symbol = sym;
  left = NULL;
  right = NULL;

  nodeCount++;
  // cout<<"+ Node: new created. Updated count = "<<nodeCount<<endl;
}

Node::~Node() {
  nodeCount--;
  // cout<<"- Node: deleted. Updated count = "<<nodeCount<<endl;
}

// Deletes all the nodes present in binary tree
void deleteBinaryTree(Node *root) {
  if(root == NULL)
    return;

  deleteBinaryTree(root->left);
  deleteBinaryTree(root->right);
  delete root;
}

// read next byte from &file and store it to &byte
// if can't read ahead, return false
// if operation successfull, return true
bool readNextByte(char &byte, ifstream &file) {
  if(file.is_open() && file.good()) {
    file.get(byte);
    return true;
  } else {
    cout<<"Can't read next byte"<<endl;
    return false;
  }
}

// read next unsigned integer from file; return cases are same as readNextByte
bool readNextUnsignedInt(unsigned int &number, ifstream &file) {
  if(file.is_open() && file.good()) {
    file.read ((char *) &number, sizeof(number));
    return true;
  } else {
    cout<<"Can't read next integer"<<endl;
    return false;
  }
}

// writes given byte to the file
void writeNextByte(char &byte, ofstream &fout) {
  if(fout.is_open()) {
    // File is opened
    if(fout.good()) {
      fout.put(byte);
    }
  } else {
    cout<<"ERROR: writeNextByte failed, file is closed!"<<endl;
  }
}

// write given unsigned int to the file
// Note: MAX number can be 4294967295!!
void writeNextUnsignedInt(unsigned int &number, ofstream &file) {
  if(file.is_open() && file.good()) {
    file.write ((char *) &number, sizeof(number));
  } else {
    cout<<"Can't read next integer"<<endl;
  }
}

// Deserialise binary tree and root will be stored in *&base
void readBinaryTree(Node *&base, ifstream &file) {
  char byte;
  // If can't read next byte, return
  if (!readNextByte(byte, file))
    return;

  // got byte, construct node and recur for its left & right
  if (byte == 'q') {
    // Its one of the intermediate node
    base = new Node('@');
    readBinaryTree(base->left, file);
    readBinaryTree(base->right, file);

  } else if(byte == 'l') {
    // next char will be a leaf node
    if(readNextByte(byte, file)) {
      base = new Node(byte);
      base->left = NULL;
      base->right = NULL;
    } else {
      cout<<"ERROR: Syntax error, Leaf node not found!"<<endl;
    }
  } else {
    cout<<"ERROR: Syntax error, unidentified flag!"<<endl;
  }
}

// Serialise binary tree from root to file
void writeBinaryTree(Node *&root, ofstream &fout) {
  if(root == NULL) {
    // In left or right of the leaf node
    // do nothing
    return;

  } else {
    char sym;
    if(root->left != NULL && root->right != NULL) {
      // intermediate node
      sym = 'q';
      writeNextByte(sym, fout);

    } else if(root->left == NULL && root->right == NULL) {
      // leaf node
      sym = 'l';
      writeNextByte(sym, fout);
      //next write symbol of the current node
      writeNextByte(root->symbol, fout);

    } else {
      cout<<"ERROR: Tree is not a completed binary Tree!!"<<endl;
      return;
    }

    // If flow reaches here, i.e. write operation is successfully done
    // Do the same for root's left & right
    writeBinaryTree(root->left, fout);
    writeBinaryTree(root->right, fout);

  }
}

// Prints binary Tree at +90 degree angle
void printBinaryTree(Node *root, int level) {
  // if in leaf node, return
  if(root == NULL)
    return;

  // increase branch level
  level++;

  printBinaryTree(root->right, level);
  // print blanks according level
  for(int i=0; i<level; i++) cout<<"   ";
  // Print node's symbol
  cout<<root->symbol<<endl;
  printBinaryTree(root->left, level);
}

void createBinaryTree(Node *&root, vector< pair<Node*, int> > &leaves) {
  if(leaves.size() == 1) {
    // Return the tree

    cout<<"Tree is created, returning it.."<<endl;
    // Vector have just one node, operation done!
    // It is the root node of tree
    root = leaves.at(0).first;
    return;
  } else if(leaves.size() > 1) {
    // Create the tree

    // Sort the vector: low freq -> high freq
    sort(leaves.begin(), leaves.end(), compareLeaves);

    // get reference of two lowest frequency having pair from vector
    pair<Node*, int> first, second;
    first = leaves.at(0);
    second = leaves.at(1);

    // remove that two pairs from vector
    leaves.erase(leaves.begin() + 0);
    leaves.erase(leaves.begin() + 0);

    // create new node & combined frequency
    Node *newComb = new Node('@');
    newComb->left = first.first;
    newComb->right = second.first;
    int newFrequency = first.second + second.second;

    // create new pair to add to leaves vector
    pair<Node *, int> newNodeFreqPair = make_pair(newComb, newFrequency);

    // Add it to vector
    leaves.push_back(newNodeFreqPair);

    // Call recursion
    createBinaryTree(root, leaves);
  } else {
    // Vector is empty
    cout<<"ERROR: unexpected empty vector!!"<<endl;
  }
}

// Helper function to sort
bool compareLeaves(const pair<Node*, int>&i, const pair<Node*, int>&j) {
    return i.second < j.second;
}

void generateCharBitCodePairFromTree(Node *&root, map<char, string> &bitCodes, string currentBitSequence) {
  if(root->left == NULL && root->right == NULL) {
    // Reached to leaf node
    bitCodes.insert( pair<char, string>(root->symbol, currentBitSequence) );

    return;
  }

  generateCharBitCodePairFromTree(root->left, bitCodes, currentBitSequence + '1');
  generateCharBitCodePairFromTree(root->right, bitCodes, currentBitSequence + '0');
}

void generateCharodePairFromTree(Node *&root, map<string, char> &charCodes, string currentBitSequence) {
  if(root->left == NULL && root->right == NULL) {
    // Reached to leaf node
    charCodes.insert( pair<string, char>(currentBitSequence, root->symbol) );

    return;
  }

  generateCharodePairFromTree(root->left, charCodes, currentBitSequence + '1');
  generateCharodePairFromTree(root->right, charCodes, currentBitSequence + '0');
}

unsigned int writeCompressedFileWithBitcodeMap(ifstream &sourceFile, map<char, string> &bitCodes, ofstream &targetFile) {
  // Setup variables to use in this function
  unsigned int totalCompressedBytes = 0;
  char oneChar = 0;
  char outChar = 0;
  int counter = 0;
  string bitSequence = "";

  // Read every byte
  while (readNextByte(oneChar, sourceFile) && !sourceFile.eof()) {
    // Find its bitCode
    map<char, string>::iterator it = bitCodes.find(oneChar);
    if(it == bitCodes.end()) {
      cout<<"ERROR: bitCode not found!! unexpected!"<<endl;
      return totalCompressedBytes;
    }
    bitSequence = it->second;

    // Operate for each bits of whole bitCode sequence
    while (bitSequence.length() > 0) {
      // Convert from (char) '1' to (bool/int) 1, & append to outChar
      bool bit = ( bitSequence.at(0) == '1' ? 1 : 0);
      outChar = (outChar << 1) | bit;
      counter++;
      bitSequence.erase(bitSequence.begin() + 0);

      // If outChar have date of a whole byte
      if(counter == 8) {
        // write outChar in file and reset counter
        writeNextByte(outChar, targetFile);
        outChar = 0;
        counter = 0;
      }
    }
    // +1 to count of bytes processed
    totalCompressedBytes++;
  }

  // Every fully generated outChar is written
  // Write remaining bits, too.
  if(counter > 0) {
    // make new outChar out of remaining bits
    outChar = (outChar << (8 - counter));

    // write outChar and reset counter
    writeNextByte(outChar, targetFile);
    outChar = 0;
    counter = 0;
  }
  return totalCompressedBytes;
}

void printBitsOfByte(char byte) {
  for(int i=7; i>=0; i--) {
    bool bit = (byte >> i) & 1 ;
    cout<<bit<<" ";
  }
  cout<<endl;
}

unsigned int writeExpandedFileWithCharcodeMapUptoBytes(ifstream &sourceFile, map<string, char> &charCodes, ofstream &targetFile, unsigned int bytesToExpand) {
  unsigned int bytesExpanded = 0;
  char gotByte = 0;
  string collectedBitSequence = "";

  // read bit-by-bit
  // To do so.. get new byte 1st
  while(readNextByte(gotByte, sourceFile) && !sourceFile.eof()) {
    // add each bits to collectedBitSequence one-by-one
    for(int i=7; i>=0; i--) {
      bool bit = (gotByte >> i) & 1 ;
      collectedBitSequence += ( (bit == 1) ? '1' : '0' );

      // Check if whole bitSequence is formed
      map<string, char>::iterator it = charCodes.find(collectedBitSequence);
      if(it != charCodes.end()) {
        // found one symbol
        writeNextByte(it->second, targetFile);
        bytesExpanded++;

        // If all work is done, exit
        if(bytesExpanded == bytesToExpand) return bytesExpanded;

        // reset variables
        collectedBitSequence = "";
      }

    }
  }
  return bytesExpanded;
}

unsigned int writeExpandedFileWithTreeUptoBytes(ifstream &sourceFile, Node *&root, ofstream &targetFile, unsigned int bytesToExpand) {
  Node *currentNode = root;
  unsigned int bytesExpanded = 0;
  char gotByte = 0;

  // read bit-by-bit
  // To do so.. get new byte 1st
  while(readNextByte(gotByte, sourceFile) && !sourceFile.eof()) {
    // operate on each bits one-by-one, to find leaf node from tree
    for(int i=7; i>=0; i--) {
      bool bit = (gotByte >> i) & 1 ;
      // Go to left or right of the current node (according to the bit we got)
      if(bit == 1) {
        currentNode = currentNode->left;  // left
      } else if (bit == 0) {
        currentNode = currentNode->right; // right
      } else {
        cout<<"ERROR: bit isn't 0 or 1!"<<endl;
        return bytesExpanded;
      }

      // If this node is leaf node, write its symbol in file
      if(currentNode->left == NULL && currentNode->right == NULL) {
        // (1) Write that symbol
        // (2) increase number of bytesExpanded
        // (3) point currentNode to root, again.
        writeNextByte(currentNode->symbol, targetFile);
        bytesExpanded ++;
        currentNode = root;

        // If all bytesExpanded, return
        if(bytesExpanded == bytesToExpand) {
          return bytesExpanded;
        }
      }
    }
  }

  return bytesExpanded;
}
