//  Created by Neesarg Banglawala on 12th Feb, 2017.
//  Copyright (c) 2017 Neesarg Banglawala. All rights reserved.
#include "ResourceManager.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

ResourceManager::ResourceManager() {

}

void ResourceManager::deleteAllIndependentBaseNodesSafely(){
  // For every independentBaseNodes
  for(int indN = independentBaseNodes.size(); indN >=1; indN--) {
    // Firstly, delete its all children
    independentBaseNodes[indN-1]->deleteAllChildNodes();

    // Now, delete its self
    delete independentBaseNodes[indN-1];
    // Remove its reference, too
    independentBaseNodes.pop_back();
  }
}
void ResourceManager::addBaseAndChildNodesFromStringsToGame(string baseName, string childName) {
  cout<<"gotIt: "<<baseName<<", "<<childName<<endl;
  // Search for baseNode in game's existing structure
      // get baseNodeReference
  // Search for childNode in game's existing structure
      // get childNodeReference

  // Switch on diffrent cases
        // CASE I: Base and Child both are not present in the game | I.E. bothNodeReferences == NULL
            /*
             *        { Add it accordingly.. }
             */
        // CASE II: Base and Child both are in the game   | I.E. bothNodeReferences != NULL
            /*
             *        { Add it accordingly.. }
             */
        // CASE III: Base is in the game; but Child isn't | I.E. childNodeReference == NULL
            /*
             *        { Add it accordingly.. }
             */
        // CASE IV: Child is in the game; but Base isn't  | I.E. baseNodeReference == NULL
            /*
             *        { Add it accordingly.. }
             */

}
