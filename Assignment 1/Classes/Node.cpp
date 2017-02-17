//  Created by Neesarg Banglawala on 12th Feb, 2017.
//  Work completed on 16th Feb, 2017.
//  Copyright (c) 2017 Neesarg Banglawala. All rights reserved.
#include "Node.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

static int totalNodesConstructed;

// Initalize with default values
    Node::Node() {
      totalNodesConstructed++;
      cout << "constructed new Node: [" << this << "]; Updated count = "<<totalNodesConstructed<<"\n";
      name = "";
      usable = false;
    }

// Deconstructer
    Node::~Node() {
      totalNodesConstructed--;
      // Print message when it gets deleted
      cout << "deleted Node at: [" << this << "]; Updated count = "<<totalNodesConstructed<<"\n";
    }


    void Node::deleteAllChildNodes() {
      for(int i = childNode.size()-1; i>=0; i--) {
          // Recursion
          childNode[i]->deleteAllChildNodes();

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
      cout<<endl<<"-------------------"<<endl;
      cout<<"        INFO       "<<endl;
      cout<<"-------------------"<<endl;
      cout<<"Object Name: \""<<name<<"\", Type: \"Node\","<<endl;
      cout<<"Base Nodes: "<<baseNode.size()<<", ( ";
      // Display presentBase nodes
      for(int i=0; i<baseNode.size(); i++) {
        cout<<baseNode.at(i)->name<<" ";
      }
      cout<<")"<<endl;

      cout<<"Child Nodes: "<<childNode.size()<<", ( ";
      // Display presentBase nodes
      for(int i=0; i<childNode.size(); i++) {
        cout<<childNode.at(i)->name<<" ";
      }
      cout<<")"<<endl;

      cout<<"Relies on Nodes: "<<reliesOnNodes.size()<<", ( ";
      // Display presentBase nodes
      for(int i=0; i<reliesOnNodes.size(); i++) {
        cout<<reliesOnNodes.at(i)<<" ";
      }
      cout<<")"<<endl;

      cout<<"Usable: "<<usable<<endl;
    }


    void Node::addBaseNode(Node * base) {
      baseNode.push_back(base);
    }


    void Node::makeGraphOfThis() {
      // to keep track of hierarchy levels
      int level = 0;

      vector<string> *alreadyPlottedGraph = new vector<string>;

      // to display hierarchy
      for(int i = level; i > 0; i--) {
        cout<<"     ";
      }

      // display Node name
      cout<<"||"<<this->name;
      // display its usability
      if(this->usable == true) {
        cout<<" (usable)";
      } else {
        cout<<" (not usable)";
      }

      if(this->childNode.size() != 0) {
        cout<<":";
      }
      cout<<endl;

      alreadyPlottedGraph->push_back(this->name);
      // Recursion for all childNode
      for(int i=0; i< this->childNode.size(); i++) {
        level++;
        makeGraphOfThis(this->childNode[i], level, alreadyPlottedGraph);
        level--;
      }

      delete alreadyPlottedGraph;
    }


    void Node::makeGraphOfThis(Node * aNode, int currentLevel, vector<string> *alreadyPlotted) {

      // to keep track of hierarchy levels
      static int level = currentLevel;

      // to display hierarchy
      for(int i = level; i > 0; i--) {
        cout<<"     ";
      }

      // display Node name
      cout<<"<-"<<aNode->name;
      // display its usability
      if(aNode->usable == true) {
        cout<<" (usable)";
      } else {
        cout<<" (not usable)";
      }


      if(aNode->searchThisNodeInVector(alreadyPlotted) == false) {
        alreadyPlotted->push_back(aNode->name);


        if(aNode->childNode.size() != 0) {
          cout<<":";
        }
        cout<<endl;

        // Recursion for all childNode
        for(int i=0; i< aNode->childNode.size(); i++) {
          // Handling hierarchy levels
          level++;
          makeGraphOfThis(aNode->childNode[i], level, alreadyPlotted);
          level--;
        }



      } else {
        cout<<" ~link~"<<endl;
      }
    }

    void Node::deleteItSafely(Node * currentChild) {
      string nameOfChild = currentChild->name;

      // For every base nodes of the currentChild
      for(int cb = currentChild->baseNode.size(); cb>=1; cb--) {
        Node * cbNode = currentChild->baseNode[cb-1];

        // For its every childNode
        for(int cbc = cbNode->childNode.size(); cbc>= 1; cbc--) {
        Node *cbcNode = cbNode->childNode[cbc-1];

        // Find reference of currentChild Node
        if(cbcNode->name == nameOfChild) {
          // Remove its reference
          cbNode->childNode.erase(cbNode->childNode.begin() + cbc-1);

          // if this cbNode was the only last one left,
          // delete currentChild Node, also.
          if(cb == 1) {
            delete cbcNode;
            }
          break;
          }
        }
      }
    }

    Node* Node::findNodeNamedUsingDFS(string searchingForNode) {
        // It will contain Nodes which are already visited
        vector<string> *visitedVector = new vector<string>;

        // Call the recursive helper function to find that Node v
        // Save its result in this variable
        Node *operationResult = DFSUtil(this, searchingForNode, visitedVector);
        delete visitedVector;

        return operationResult;
    }

    Node* Node::DFSUtil(Node *findFrom, string searchingForNode, vector<string> *visited) {
      // variable to store return value
      Node *result = NULL;

      // add that name to visitedVector
      visited->push_back(findFrom->name);
      // If node found
      if(findFrom->name == searchingForNode) {
        result = findFrom;
        return result;
      }

      // Recursion for its childNode(s)
      for(int c=0; c<findFrom->childNode.size(); c++) {
        // Next child to check
        Node * nextChild = findFrom->childNode[c];
        if(nextChild->searchThisNodeInVector(visited)) {
          // Node is already visited
          // Do nothing, NULL will be returned at the end

        } else {
          // This Node is not visited
          // Do DFS on it
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

    bool Node::isUsable() {
      // Check if all reliesOnNodes are in baseNode vector & in usable state
              // If yes-> mark childNode as usable
              // If no->  mark it as not usable
      bool allReliesOnNodesPresentAsUsable = true;

      // Check for any not present reliesOnNodesNode
      int totalReliesOnNodes = this->reliesOnNodes.size();
      for(int i=0; i<totalReliesOnNodes; i++) {
        // Search for a node name in vector of Node*
          if( searchNodeNamedIsPresentAsUsableInItsBaseNodes(this->reliesOnNodes.at(i)) == false) {
              allReliesOnNodesPresentAsUsable = false;
              break;
          }
      }

      return allReliesOnNodesPresentAsUsable;
    }


    bool Node::searchNodeNamedIsPresentAsUsableInItsBaseNodes(string nodeName) {
      bool result = false;

      // For every baseNode(s)
      for(int i=0; i<baseNode.size(); i++) {
        if(baseNode.at(i)->name == nodeName) {
          // baseNode is there
          if(baseNode.at(i)->usable == true) {
            // baseNode is usable
            result = true;
            break;

          } else {
            // baseNode is not-usable
          }

        } else {
          // baseNode not found
        }
      }

      return result;
    }

    vector<Node *> * Node::deleteThisNode() {
      // For all of its baseNode
          // Remove its entry

      for(int i=0; i<baseNode.size(); i++) {
        // In baseNode.at(i)
        Node *bN = baseNode.at(i);

        // Find its entry in its childNode(s)
        for(int j=0; j<bN->childNode.size(); j++) {
          // current childNode
          Node *bcN = bN->childNode.at(j);

          if(bcN->name == this->name) {
            // Remove its reference
            bN->childNode.erase(bN->childNode.begin() + j);
            break;
          }
        }
      }


      // For all its childNode(s)
          // Remove reference of itself from baseNode vector
          // Mark childNode as not-usable, Recursively!
          // If childNode does not have any other parentNode
              // Attach that childNode to independentBaseNodes vector
      // delete thisNode
      vector<Node *> *leftChildren = new vector<Node *>;

      // For all its childNode(s)
      for(int i=0; i<childNode.size(); i++) {
        // current childNode
        Node* cNode = childNode.at(i);

        // Find baseNode's entry from currentChildNode
        // N Remove it
        for(int e=0; e < cNode->baseNode.size(); e++) {
          // Current baseNode entry
          Node* cbNode = cNode->baseNode.at(e);

          // Found entry
          if(cbNode->name == this->name) {
            // Remove its reference
            cNode->baseNode.erase(cNode->baseNode.begin() + e);
            break;
          }
        }

        // Mark childNode not-usable, Recursively!!
        cNode->markUsableAs(false);

        // Check if childNode not have any parentNode
        if(cNode->baseNode.size() == 0) {
          // Attach it to independentBaseNodes vector
          leftChildren->push_back(cNode);
        }
      }

      // Done with its childNode(s)
      // delete thisNode
      delete this;

      return leftChildren;
    }

    void Node::markUsableAs(bool isUsable) {
      // If want to mark all child not-usable
            // Just mark it
      // If want to mark usable
            // You have to check for usability first
      if(isUsable == false) {
        // Mark recursivly all false
        this->usable = false;

        for(int i=0; i<childNode.size(); i++) {
          childNode.at(i)->markUsableAs(false);
        }
      } else {
        // Want to mark usable = true
        // Check before marking
        if(this->isUsable() == true) {
          // It has all reliesOnNodes baseNode(s)
          this->usable = true;

          for(int i=0; i<childNode.size(); i++) {
            childNode.at(i)->markUsableAs(true);
            }

          } else {
            // It does not have all reliesOn baseNode(s)
            // It should be false already

          }
        }
    }

    bool Node::searchNameInVectorOfString(string nodeName, vector<string> v) {
      // Go through every elements of the vector
      for(int i=0; i<v.size(); i++) {
        // If name found; return true
        if(v.at(i) == nodeName) {
          return true;
        }
      }

      // Node's name not found!
      return false;
    }
