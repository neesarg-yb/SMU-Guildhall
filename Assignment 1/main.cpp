/*
 *
 *  To compile: g++ main.cpp Classes/Node.cpp Classes/Registry.cpp Classes/InputManager.cpp 
 *
 */
#include "Classes/Node.h"
#include "Classes/Registry.h"
#include "Classes/InputManager.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <tuple>

using namespace std;

void makeGraphOfBase(Node *);
Node* getNodeNamedFromVector(string, vector<Node *>);
void addChildAndBaseNodesFromStrings(string, string);

int main(int argc, char const *argv[]) {
  Registry baseRegistry;

  // Stting up file InputManager
  InputManager fileInput = InputManager("input.txt");
  // Read txt file till end
  string line = fileInput.readFileLineByLine();
  while (line != ""){
    // get input pair from file and add it via baseRegistry
    pair<string, string> baseAndChild = fileInput.getBaseAndChildFrom(line);
    baseRegistry.addBaseAndChildNodesFromStrings(baseAndChild.first, baseAndChild.second);

    line = fileInput.readFileLineByLine();
  }

  return 0;
}

Node* getNodeNamedFromVector(string name, vector<Node *> fromRegistry) {
  // Go through all elements
  for(int i=0; i<fromRegistry.size(); i++) {
    // If found the node
    if(fromRegistry[i]->name == name) {
      return fromRegistry[i];
    }
  }

  // Node not found
  return NULL;
}
