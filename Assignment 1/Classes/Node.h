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
    bool usable;

    // Parent Node
    vector<Node *> baseNode;
    // Child Node
    vector<Node *> childNode;
    // Relies On
    vector<string> reliesOnNodes;

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

    // Finds node
    // If present, will return its references
    // If not found, returns NULL
    Node* findNodeNamedUsingDFS(string searchingForNode);

    // Check whether Node is usable or not
    // To be usable: all reliesOnNodes should be present in baseNode vector in usable state
    bool isUsable();

    // It deletes current node
    // Also marks its childNode(s) as not-usable
    // If childNode does not have anyother baseNode,
    // returns vector<Node *> of childNode(s) who does not have any Parents
    vector<Node *> * deleteThisNode();

    // Marks a node and all its childNode(s) not-usable
    // Recursively!
    void markNotUsable();

  private:
    // Adds baseNode
    // It's a private function; so no count cross-check is applied
    void addBaseNode(Node * base);

    // Supporting private function of makeGraphOfThis()
    // Works on Recursion
    // Major work is done by this function
    void makeGraphOfThis(Node * aNode, int currentLevel, vector<string> *alreadyPlotted);


    // First of all, removes all references of the currentChild
    // After that, delete currentChild node itself
    // Note: Situation of multiple references is created because of multiple baseNode(s) of a single childNode
    void deleteItSafely(Node * currentChild);

    // Helper function of findNodeNamedUsingDFS()
    // Recursively does the job
    Node* DFSUtil(Node *findFrom, string searchingForNode, vector<string> *visited);

    // Search for a name of current Node in vector of strings
    // This function is created to support DFSUtil method
    bool searchThisNodeInVector(vector<string> *v);

    // Helps to find whether the node is usable or not
    bool searchNodeNamedIsPresentAsUsableInItsBaseNodes(string nodeName);

};
