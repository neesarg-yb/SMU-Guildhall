//  Created by Neesarg Banglawala on 12th Feb, 2017.
//  Copyright (c) 2017 Neesarg Banglawala. All rights reserved.
#pragma once

#include "Node.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

// Everything related to adding Nodes, removing it, creating new link, searching for a Node, etc. will be done by this class
// (Not even started yet!)
class ResourceManager {
  public:
    ResourceManager();

    // Don't forget to make it private, later on
    vector<Node *> independentBaseNodes;

    // Deletes all childern of nodes as well as it self
    // Also removes references from independentBaseNodes variable
    void deleteAllIndependentBaseNodesSafely();

    // Implement graph seach algorithm
    // It will be used before addition of any Node into the system
    // To keep the whole structure without any redundancy
    Node* searchForNode(string nodeName);

    void addBaseAndChildNodesFromStringsToGame(string childName, string baseName);


  private:
};
