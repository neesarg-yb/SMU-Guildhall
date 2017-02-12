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
