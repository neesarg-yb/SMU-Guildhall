#include "Node.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

    Node::Node() {
      cout << "constructed new Node: [" << this << "]\n";
      name = "";
      inventory = 0;
    }

    Node::~Node() {
      cout << "deleted Node at: [" << this << "]\n";
    }

    void Node::deleteAllChildNodes() {
      for(int i = childNode.size()-1; i>=0; i--) {
          childNode[i]->deleteAllChildNodes();

          delete childNode[i];
          childNode.pop_back();
      }

      // cout<<"\n!!! Note: Child nodes of Node \""<<name<<"\" are delete, current count = "<<childNode.size()<<endl;
    }

    void Node::addChildNode(Node * aNode) {
      if(aNode->baseNode.size() == 0) {
        childNode.push_back(aNode);
        aNode->addBaseNode(this);
      } else {
        cout<< "\n!!! ERROR: node \""<< aNode->name <<"\" already have one baseNode.. !!!\n";
      }
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
        level++;
        makeGraphOfThis(aNode->childNode[i], level);
        level--;
      }
    }
