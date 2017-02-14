//  Created by Neesarg Banglawala on 12th Feb, 2017.
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

    // Don't forget to make it private, later on
    vector<Node *> independentBaseNodes;

    // Deletes all childern of nodes as well as it self
    // Also removes references from independentBaseNodes variable
    void deleteAllIndependentBaseNodesSafely();

    // Use DFS graph seach algorithm of Node class, for every independentBaseNodes
    // It will be used before addition of any Node into the system
    // To keep the whole structure without any redundancy
    Node* searchForNode(string nodeName);

    // It will add base <--- child in the system
    // Will also ensure that only single copy of any Node is being included!
    void addBaseAndChildNodesFromStringsToGame(string childName, string baseName);

    // Deletes a node. Also,
    //  -> delete links of that node from its childNodes
    //  -> delete links of that node from its baseNodes
    //  -> make all childNodes inactive
    void deleteNodeNamed(string nodeName);
  private:

    // addBaseAndChildNodesFromStringsToGame() function will pass on this on
    // Will consider following operations in check
        // (1) Add baseNode link in childNode
        // (2) Add childNode link in baseNode
        // (3) Set-up or recheck value of node.usable
        //      -> Usable if,
        //            *  every reliesOnNodes are there in baseNodes vector
        //      -> Not Usable if,
        //            * every reliesOnNodes are not present in baseNodes vector
    void addBaseAndChildNodesSafely(Node *baseNode, Node *childNode);
};
