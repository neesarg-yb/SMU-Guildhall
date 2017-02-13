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
          // cout<<"Operating to delete: "<<childNode[i]->name<<endl;

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

      // For every base nodes of the currentChild
      for(int cb = currentChild->baseNode.size(); cb>=1; cb--) {
        Node * cbNode = currentChild->baseNode[cb-1];
        // cout<<"  Currently in: "<<cbNode->name<<endl;

        // For its every childNode
        for(int cbc = cbNode->childNode.size(); cbc>= 1; cbc--) {
        Node *cbcNode = cbNode->childNode[cbc-1];
        // cout<<"    On: "<<cbcNode->name<<endl;

        // Find reference of currentChild Node
        if(cbcNode->name == nameOfChild) {
          // cout<<"       Found: "<< nameOfChild<<"; removing its reference!"<<endl;

          // Remove its reference
          cbNode->childNode.erase(cbNode->childNode.begin() + cbc-1);

          // if this cbNode was the only last one left,
          // delete currentChild Node, also.
          if(cb == 1) {
            // cout<<"  ========= All references of "<<nameOfChild<<" removed! Now, deleting node itself!!"<<endl;
            delete cbcNode;
            }
          break;
          }
        }
      }
    }

    Node* Node::findNodeNamedUsingDFS(string searchingForNode) {
        cout<<"DFS: Finding node: "<<searchingForNode<<"; In baseNode named: "<<this->name<<"."<<endl;
        // It will contain Nodes which are already visited
        vector<string> *visitedVector = new vector<string>;

        // Call the recursive helper function to find that Node v
        return DFSUtil(this, searchingForNode, visitedVector);
    }

    Node* Node::DFSUtil(Node *findFrom, string searchingForNode, vector<string> *visited) {
      // variable to store return value
      Node *result = NULL;

      // add that name to visitedVector
      visited->push_back(findFrom->name);
      // cout<<"DFS: pushed_back: "<<findFrom->name<<" in visited."<<endl;

      // If node found
      if(findFrom->name == searchingForNode) {
        // cout<<"DFS: FOUND!! "<<searchingForNode<<endl;
        result = findFrom;
        return result;
      }

      // Recursion for its childNode(s)
      // cout<<"DFS: Searching for its childNodes"<<endl;
      for(int c=0; c<findFrom->childNode.size(); c++) {
        // Next child to check
        Node * nextChild = findFrom->childNode[c];
        // cout<<"DFS: in childNode: "<<nextChild->name<<" for loop"<<endl;

        if(nextChild->searchThisNodeInVector(visited)) {
          // Node is already visited
          // Do nothing, NULL will be returned at the end

          // Desplay visited vector
          // cout<<"\nDFS: Current visited vector:"<<endl;
          for(int j=0; j<visited->size(); j++) {
            cout<<visited->at(j)<<endl;
          }

          // cout<<"DFS: "<<nextChild->name<<" is already visited"<<endl;
        } else {
          // This Node is not visited
          // Do DFS on it
          // cout<<"DFS: "<<nextChild->name<<" is not visited"<<endl;
          result = DFSUtil(nextChild, searchingForNode, visited);

          // If we got the reference, return it to end the search
          if(result != NULL) {
            return result;
          }
        }
      }

      return result;
    }

    bool Node::searchThisNodeInVector(vector<string> *v) {
      // Go through every elements of the vector
      for(int i=0; i<v->size(); i++) {
        // If name found; return true
        if(v->at(i) == this->name) {
          return true;
        }
      }

      // Node's name not found!
      return false;
    }
