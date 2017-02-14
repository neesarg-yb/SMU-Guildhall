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

// It is there because of TEST--CODE
// Most probably I'll delete this function in end
void displayStructureOfNodesInVector(vector<Node *> baseNodes);

int main(int argc, char const *argv[]) {
  // Setting up ResourceManager: It handles the whole system
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

  displayStructureOfNodesInVector(theResourceManager.independentBaseNodes);

  // getchar();

  theResourceManager.deleteAllIndependentBaseNodesSafely();
  return 0;
}


void displayStructureOfNodesInVector(vector<Node *> baseNodes) {
  // For all independentBaseNodes in given vector
  for(int indN = baseNodes.size(); indN >=1; indN--) {

    cout<<"\n\n--------- Structure of \""<<baseNodes[indN-1]->name<<"\" --------- "<<endl;
    baseNodes[indN-1]->makeGraphOfThis();
    cout<<"\n--------- ----------------- --------- \n"<<endl;
  }
}
