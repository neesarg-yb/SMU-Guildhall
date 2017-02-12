//  Created by Neesarg Banglawala on 12th Feb, 2017.
//  Copyright (c) 2017 Neesarg Banglawala. All rights reserved.
/*
 *
 *  || Makefile commands ||
 *  make: will compile whole project and creates executable "output" file
 *  make clean: will clean created output and .o files
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


Node* getNodeNamedFromVector(string, vector<Node *>);

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




/*
 *  CODE TO TEST NODE CLASS!
 *  NODE CREATIONS, DELETION, GRAPH & ETC..
 *

Node *ore = new Node;
ore->name = "ore";
ore->inventory = 2;

Node *bullets = new Node;
bullets->name = "bullets";
bullets->inventory = 1;
ore->addChildNode(bullets);

Node *turret = new Node;
turret->name = "turret";
turret->inventory = 1;

Node *handgun = new Node;
handgun->name = "handgun";
handgun->inventory = 1;
bullets->addChildNode(handgun);

Node *bombs = new Node;
bombs->name = "bombs";
bombs->inventory = 2;
ore->addChildNode(bombs);
bombs->addChildNode(turret);
bombs->addChildNode(handgun); // This should give an ERROR

bullets->description();
ore->description();

cout<<"\n--------- Current Structure --------- "<<endl;
ore->makeGraphOfThis();
cout<<"\n--------- ----------------- --------- "<<endl;

ore->deleteAllChildNodes();
delete ore;

*
*
*/
