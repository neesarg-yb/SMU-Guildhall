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
#include "Classes/ResourceManager.h"
#include "Classes/InputManager.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <tuple>

using namespace std;


Node* getNodeNamedFromVector(string, vector<Node *>);
void displayStructureOfNodesInVector(vector<Node *> baseNodes);

int main(int argc, char const *argv[]) {
  ResourceManager theResourceManager;

  // Stting up file InputManager
  InputManager fileInput = InputManager("input.txt");

  // Read txt file till end
  string line = fileInput.readFileLineByLine();

  while (line != ""){
    // get input pair from file and add it via theResourceManager
    pair<string, string> baseAndChild = fileInput.getBaseAndChildFrom(line);
    theResourceManager.addBaseAndChildNodesFromStringsToGame(baseAndChild.first, baseAndChild.second);

    line = fileInput.readFileLineByLine();
  }

///////////////// TEST--CODE /////////////////

  Node *ore = new Node;
  ore->name = "ore";
  theResourceManager.independentBaseNodes.push_back(ore);

  Node *ore2 = new Node;
  ore2->name = "ore2";
  theResourceManager.independentBaseNodes.push_back(ore2);

  Node *bullets = new Node;
  bullets->name = "bullets";
  ore->addChildNode(bullets);

  Node *turret = new Node;
  turret->name = "turret";

  Node *handgun = new Node;
  handgun->name = "handgun";
  bullets->addChildNode(handgun);

  Node *bombs = new Node;
  bombs->name = "bombs";
  ore->addChildNode(bombs);
  bombs->addChildNode(turret);
  bombs->addChildNode(handgun);

  Node *tank = new Node;
  tank->name = "tank";
  handgun->addChildNode(tank);
  turret->addChildNode(tank);

  bullets->description();
  ore->description();

  // For all independentBaseNodes, display its current structure
  displayStructureOfNodesInVector(theResourceManager.independentBaseNodes);

  // Delete all independentBaseNodes' with their children
  theResourceManager.deleteAllIndependentBaseNodesSafely();

  // For all independentBaseNodes, display its current structure, now
  displayStructureOfNodesInVector(theResourceManager.independentBaseNodes);

///////////////// TEST--CODE /////////////////

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


void displayStructureOfNodesInVector(vector<Node *> baseNodes) {
  // For all independentBaseNodes in given vector
  for(int indN = baseNodes.size(); indN >=1; indN--) {

    cout<<"\n\n--------- Structure of \""<<baseNodes[indN-1]->name<<"\" --------- "<<endl;
    baseNodes[indN-1]->makeGraphOfThis();
    cout<<"\n--------- ----------------- --------- \n"<<endl;
  }
}


/*
 *  CODE TO TEST NODE CLASS!
 *  NODE CREATIONS, DELETION, GRAPH & ETC..
 *

 ///////////////// TEST--CODE /////////////////

   Node *ore = new Node;
   ore->name = "ore";
   theResourceManager.independentBaseNodes.push_back(ore);

   Node *ore2 = new Node;
   ore2->name = "ore2";
   theResourceManager.independentBaseNodes.push_back(ore2);

   Node *bullets = new Node;
   bullets->name = "bullets";
   ore->addChildNode(bullets);

   Node *turret = new Node;
   turret->name = "turret";

   Node *handgun = new Node;
   handgun->name = "handgun";
   bullets->addChildNode(handgun);

   Node *bombs = new Node;
   bombs->name = "bombs";
   ore->addChildNode(bombs);
   bombs->addChildNode(turret);
   bombs->addChildNode(handgun);

   Node *tank = new Node;
   tank->name = "tank";
   handgun->addChildNode(tank);
   turret->addChildNode(tank);

   bullets->description();
   ore->description();

   // For all independentBaseNodes, display its current structure
   displayStructureOfNodesInVector(theResourceManager.independentBaseNodes);

   // Delete all independentBaseNodes' with their children
   theResourceManager.deleteAllIndependentBaseNodesSafely();

   // For all independentBaseNodes, display its current structure, now
   displayStructureOfNodesInVector(theResourceManager.independentBaseNodes);

 ///////////////// TEST--CODE /////////////////

*
*
*/
