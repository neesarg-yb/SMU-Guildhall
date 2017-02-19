//  Created by Neesarg Banglawala on 19th Feb, 2017.
//  Work completed on <ddth Month, YYYY>
//  Copyright (c) 2017 Neesarg Banglawala. All rights reserved.
#include<iostream>
#include<fstream>

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
};

bool readNextByte(char &byte, ifstream &file);
void readBinaryTree(Node *&base, ifstream &file);
void printBinaryTree(Node *root, int level);


  /**********************************/
 /********** MAIN FUNCTION *********/
/**********************************/
int main() {
  char byte;
  Node *root;

  ifstream myfile ("input.txt", ios::binary);

  readBinaryTree(root, myfile);
  cout<<endl<<"Tree(at 90 degree):"<<endl;
  printBinaryTree(root, 0);


}


  /**********************************/
 /****** FUNCTION DEFINITIONS ******/
/**********************************/
Node::Node(char sym) {
  symbol = sym;
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
