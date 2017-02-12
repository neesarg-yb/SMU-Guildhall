//  Created by Neesarg Banglawala on 12th Feb, 2017.
//  Copyright (c) 2017 Neesarg Banglawala. All rights reserved.
#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

class Node {
  public:
    string name;
    int inventory;

    // Parent Node
    vector<Node *> baseNode;
    // Child Node
    vector<Node *> childNode;

    Node();  // constructer
    ~Node(); // Deconstructer

    // Add childNode to aNode
    void addChildNode(Node * aNode);

    // Recursively deletes all the child nodes
    // Works in the "deepest first" manner
    void deleteAllChildNodes();

    // Print informations about that node: name, type, baseNode & childNodes
    void description();

    // Creates commandline graph
    void makeGraphOfThis();

  private:
    // Adds baseNode
    // It's a private function; so no count cross-check is applied
    void addBaseNode(Node * base);

    // Supporting private function of makeGraphOfThis()
    // Works on Recursion
    // Major work is done by this function
    void makeGraphOfThis(Node * aNode, int currentLevel);
};
