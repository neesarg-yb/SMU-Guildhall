//  Created by Neesarg Banglawala on 12th Feb, 2017.
//  Work completed on 16th Feb, 2017.
//  Copyright (c) 2017 Neesarg Banglawala. All rights reserved.
#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

class Node {
  public:
    string name; // name of the node
    bool usable; // true; if all reliesOnNodes are present in baseNode(as usable state) vector

    // Parent Node
    vector<Node *> baseNode;
    // Child Node
    vector<Node *> childNode;
    // List of all the baseNode(s) on which current node relies (to be usable)
    vector<string> reliesOnNodes;

    Node();  // constructer; to keep track of no. of node(s) created
    ~Node(); // Deconstructer; to keep track of no. of node(s) deleted

    // Add childNode to aNode
    void addChildNode(Node * aNode);

    // Recursively deletes all the child nodes
    // Works in the "deepest first" manner
    void deleteAllChildNodes();

    // Print informations about that node: name, type, baseNode, childNodes, reliesOnNodes & usability
    void description();

    // Creates commandline graph of all childNodes and links of it
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
    // If childNode does not have any other baseNode,
        // returns vector<Node *> of childNode(s) who does not have any Parents
        // So that childNode(s) can be added to indepndentBaseNodes vector of theResourceManager
    vector<Node *> * deleteThisNode();

    // Marks a node and all its childNode(s) as suggested by isUsable bool
    // Works recursively!
    // If user suggested to mark as usable = true,
        // This function will ensure its usability before marking it as a true
    void markUsableAs(bool isUsable);

    // Search for a name in vector of strings
    // This function is created to call before vector.push_back operations of reliesOnNodes; will help to avoid duplicate entries
    // When childNode is existing one, we need to cross-check its usability using this function
    bool searchNameInVectorOfString(string nodeName, vector<string> v);

    // Search for a name of current Node in vector of strings
    // This function is created to support DFSUtil method
    bool searchThisNodeInVector(vector<string> *v);

  private:
    // Adds baseNode
    // It's a private function; so no count cross-check is applied
    void addBaseNode(Node * base);

    // Supporting private function of makeGraphOfThis()
    // Works on Recursion
    // Major work is done by this function
    void makeGraphOfThis(Node * aNode, int currentLevel, vector<string> *alreadyPlotted);


    // First of all, removes all references of the currentChild from its childNode(s)
    // After that, delete currentChild node itself
    // Note: Situation of multiple references is created because of links to multiple baseNode(s) of a single childNode
    void deleteItSafely(Node * currentChild);

    // Helper function of findNodeNamedUsingDFS()
    // Recursively does the job
    Node* DFSUtil(Node *findFrom, string searchingForNode, vector<string> *visited);

    // Helps to find whether the node is usable or not
    bool searchNodeNamedIsPresentAsUsableInItsBaseNodes(string nodeName);

};
