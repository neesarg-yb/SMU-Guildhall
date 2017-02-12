//  Created by Neesarg Banglawala on 12th Feb, 2017.
//  Copyright (c) 2017 Neesarg Banglawala. All rights reserved.
#include "Node.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

// Initalize with default values
    Node::Node() {
      cout << "constructed new Node: [" << this << "]\n";
      name = "";
      inventory = 0;
    }

// Deconstructer
    Node::~Node() {
      // Print message when it gets deleted
      cout << "deleted Node at: [" << this << "]\n";
    }


    void Node::deleteAllChildNodes() {
      for(int i = childNode.size()-1; i>=0; i--) {
          // Recursion
          childNode[i]->deleteAllChildNodes();
          cout<<"Operating to delete: "<<childNode[i]->name<<endl;
          // Delete that Node pointer and all its references without memory leak
          deleteItSafely(childNode[i]);
      }
    }



    void Node::addChildNode(Node * aNode) {
      // This function allows just any number of Parents for any childNode
        childNode.push_back(aNode);
        aNode->addBaseNode(this);

    }


    void Node::description() {
      cout<<endl<<"Object Name: \""<<name<<"\", Type: \"Node\","<<endl;
      cout<<"Base Nodes: "<<baseNode.size()<<endl;
      cout<<"Child Node: "<<childNode.size()<<endl;
    }


    void Node::addBaseNode(Node * base) {
      baseNode.push_back(base);
    }


    void Node::makeGraphOfThis() {
      // to keep track of hierarchy levels
      int level = 0;

      // to display hierarchy
      for(int i = level; i > 0; i--) {
        cout<<"   ";
      }

      // display Node name
      cout<<"->"<<this->name;
      if(this->childNode.size() != 0) {
        cout<<":";
      }
      cout<<endl;

      // Recursion for all childNode
      for(int i=0; i< this->childNode.size(); i++) {
        level++;
        makeGraphOfThis(this->childNode[i], level);
        level--;
      }
    }


    void Node::makeGraphOfThis(Node * aNode, int currentLevel) {
      // to keep track of hierarchy levels
      static int level = currentLevel;

      // to display hierarchy
      for(int i = level; i > 0; i--) {
        cout<<"   ";
      }

      // display Node name
      cout<<"->"<<aNode->name;

      if(aNode->childNode.size() != 0) {
        cout<<":";
      }
      cout<<endl;

      // Recursion for all childNode
      for(int i=0; i< aNode->childNode.size(); i++) {
        // Handling hierarchy levels
        level++;
        makeGraphOfThis(aNode->childNode[i], level);
        level--;
      }
    }

    void Node::deleteItSafely(Node * currentChild) {
      string nameOfChild = currentChild->name;

      // For every base nodes
      for(int cb = currentChild->baseNode.size(); cb>=1; cb--) {
        Node * cbNode = currentChild->baseNode[cb-1];
        cout<<"Currently in: "<<cbNode->name<<endl;


        // If only one baseNode
        // Just delete the currentChild
        if(cb == 1) {
          cout<<"  Found: "<<nameOfChild<<"; deleting its final reference & node itself!!"<<endl;
          cbNode->childNode.pop_back();
          delete currentChild;
          break;
        }

        // For its every childNode
        for(int cbc = cbNode->childNode.size(); cbc>= 1; cbc--) {
        Node *cbcNode = cbNode->childNode[cbc-1];
        cout<<"  On: "<<cbcNode->name<<endl;

        // Find reference of currentChild Node
        if(cbcNode->name == nameOfChild) {
          cout<<"     Found: "<< nameOfChild<<"; removing its reference!"<<endl;

          // Remove its reference
          cbNode->childNode.erase(cbNode->childNode.begin() + cbc-1);
          break;
        }
        }
      }
        // Find reference pointer
          // Pop it out from vector untill the last one
    }
