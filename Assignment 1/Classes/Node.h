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

    vector<Node *> baseNode;
    vector<Node *> childNode;

    Node();  // constructer
    ~Node(); // Deconstructer
    void addChildNode(Node * aNode);
    void deleteAllChildNodes();
    void description();
    void makeGraphOfThis();

  private:
    void addBaseNode(Node * base);
    void makeGraphOfThis(Node * aNode, int currentLevel);
};
