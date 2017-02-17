//  Created by Neesarg Banglawala on 12th Feb, 2017.
//  Work completed on 16th Feb, 2017.
//  Copyright (c) 2017 Neesarg Banglawala. All rights reserved.
#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

class InputManager {
public:
  // Set value of variable filePath = given path
  InputManager(string path);

  // Will read every line one-by-one & returns that line
  // File will also be closed at first empty line or EOF
  string readFileLineByLine();

  // Will return pair of Base & Child from a string returned by readFileLineByLine()
  // If only one element is in the line, It Will return pair(baseName, "NULL")
  // If pattern not found, It will return pair("ERROR", "ERROR")
  pair<string, string> getBaseAndChildFrom(string line);

private:
  // Indicates the status of file
  bool fileIsOpened;

  // Stores path of file
  string filePath;
};
