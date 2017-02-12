//  Created by Neesarg Banglawala on 12th Feb, 2017.
//  Copyright (c) 2017 Neesarg Banglawala. All rights reserved.
#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

class InputManager {
public:
  bool fileIsOpened;

  string readFileLineByLine();
  pair<string, string> getBaseAndChildFrom(string line);

  InputManager(string path);

private:
  string filePath;

};
