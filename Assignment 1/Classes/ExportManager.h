//  Created by Neesarg Banglawala on 12th Feb, 2017.
//  Copyright (c) 2017 Neesarg Banglawala. All rights reserved.
#pragma once

#include "Node.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

class ExportManager {
public:
  // Initalize with current independentBaseNodes' pointer
  ExportManager(vector<Node *> *independentBaseNodes);

  // Save current structure of nodes to file
  // Saved file can be used again as resource file for the program
      // To maintain this usability, I haven't changes notation style
      // And because of it, there is no hint of a node's usability in saved file
  void saveToFile();

private:
  // To point to independentBaseNodes of theResourceManager
  vector<Node *> *independentBaseNodes;

  // DFS traverse function
  // Major work of saveToFile() is done by this method
  // all notations get pushed_back in producedNotation vector
  void DFSTraverseUtil(Node* traverseNode, vector<string> *producedNotation, vector<string> *visited);
};
