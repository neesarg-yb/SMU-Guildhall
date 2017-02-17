//  Created by Neesarg Banglawala on 12th Feb, 2017.
//  Work completed on 16th Feb, 2017.
//  Copyright (c) 2017 Neesarg Banglawala. All rights reserved.
#pragma once

#include "Node.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

// Everything related to handling independentBaseNodes and its whole structure will be done by this class
class ResourceManager {
  public:
    ResourceManager();

    // Lists all nodes that do not have any baseNode(s) currently
    // This vector is like door to every node structures
    vector<Node *> independentBaseNodes;

    // Deletes all childern of nodes as well as it self
    // Also removes references from independentBaseNodes variable
    void deleteAllIndependentBaseNodesSafely();

    // Use DFS graph seach algorithm of Node class, for every independentBaseNodes
    // It will be used before addition of any Node into the system
    // To keep the whole structure without any redundancies
    Node* searchForNode(string nodeName);

    // It will add "base <-- child" in the system
    // Will also ensure that only single copy of any Node is being added!
    // Will also check and set childNode's usability
        // There are several CASEs according to the reference of childNode & baseNode
        // All are handled nicely in the function implementation, with comments
    void addBaseAndChildNodesFromStringsToGame(string childName, string baseName);

    // Deletes a node. Also,
    //  -> delete links of that node from its childNodes
    //  -> delete links of that node from its baseNodes
    //  -> make all childNodes not-usable
    void deleteNodeNamed(string nodeName);
  private:
};
