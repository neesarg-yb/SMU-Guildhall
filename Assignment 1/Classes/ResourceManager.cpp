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
        // CASE I:
        // Base is in, so child will not be there
        // Append child behind it

        // CASE II:
        // Child is in, remove its reference
        // Append Child behind newly created Base
        // Add Base reference to Registry

    // CASE III:
    // Create new Base
    // Append Child behind it
    // Register it to Registry

}
