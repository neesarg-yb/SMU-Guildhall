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
  // Will just set variable filePath with given path
  InputManager(string path);

  // Will read every line one-by-one & returns that line
  // File will also be closed at EOF, by this function
  string readFileLineByLine();

  // Will return pair of Base & Childe from a string
  pair<string, string> getBaseAndChildFrom(string line);

private:
  // Indicates the status of file
  bool fileIsOpened;

  // Stores path of file
  string filePath;
};
