//  Created by Neesarg Banglawala on 12th Feb, 2017.
//  Copyright (c) 2017 Neesarg Banglawala. All rights reserved.
#pragma once

#include "Node.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

class Registry {
  public:
    Registry();
    void addBaseAndChildNodesFromStrings(string childName, string baseName);
    Node* searchForNode(string nodeName);

  private:

};
