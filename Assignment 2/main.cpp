//  Created by Neesarg Banglawala on 19th Feb, 2017.
//  Work completed on <ddth Month, YYYY>
//  Copyright (c) 2017 Neesarg Banglawala. All rights reserved.
#include<iostream>
#include<fstream>
#include<utility>
#include<vector>

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

bool readNextByte(char &byte, ifstream &file);
bool readNextInt(int &number, ifstream &file);
void readBinaryTree(Node *&base, ifstream &file);
void writeNextByte(char &byte, ofstream &fout);
void writeBinaryTree(Node *&root, ofstream &fout);
void printBinaryTree(Node *root, int level);
void deleteBinaryTree(Node *root);

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

  ofstream fout(outFile, ios::binary);
  if(!fout.good()) {
    cout<<"ERROR: can not open \""<<outFile<<"\" file.."<<endl;
    return 1;
  }

  if(operation == operationType::COMPRESS) {
    // COMPRESSION
    // Frequency of each byte
    int charFreq[256] = {0};

    // Calculate frequency
    char gotChar;
    while(readNextByte(gotChar, fin) == true) {
      charFreq[gotChar+128]++;  // +128 to convert range from [-128, 127] to [0, 256]
    }


    // Print frequency
    for(int i=0; i<256; i++) {
      if(charFreq[i] > 0) cout<<i<<" "<<(char)(i-128)<<": "<<charFreq[i]<<endl;
    }



  } else if(operation == operationType::EXPAND) {
    // EXPANSION

  }


  fin.close();
  fout.close();
  return 0;
}
// char byte;
// Node *root = NULL;
//
// ifstream fin ("input.txt", ios::binary);
//
// readBinaryTree(root, fin);
// readNextByte(byte, fin);
// if(byte == '-') {
//   cout<<"NOTE: Tree is constructed successfully!"<<endl;
// } else {
//   cout<<"ERROR: After tree instructions, end flag not found!"<<endl;
//   return 1;
// }
// fin.close();
//
// cout<<endl<<"Tree(at 90 degree):"<<endl;
// printBinaryTree(root, 0);
//
// ofstream fout ("output.nzp", ios::binary | ios::trunc);
// writeBinaryTree(root, fout);
// byte='-';
// writeNextByte(byte, fout);
// fout.close();
//
// deleteBinaryTree(root);



  /**********************************/
 /****** FUNCTION DEFINITIONS ******/
/**********************************/
Node::Node(char sym) {
  symbol = sym;

  nodeCount++;
  cout<<"+ Node: new created. Updated count = "<<nodeCount<<endl;
}

Node::~Node() {
  nodeCount--;
  cout<<"- Node: deleted. Updated count = "<<nodeCount<<endl;
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

// read next integer from file; return cases are same as readNextByte
bool readNextInt(int &number, ifstream &file) {
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

    // If flow reaches here, e.i. write operation is successfully done
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
