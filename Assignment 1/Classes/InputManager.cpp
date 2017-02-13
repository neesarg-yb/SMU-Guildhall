//  Created by Neesarg Banglawala on 12th Feb, 2017.
//  Copyright (c) 2017 Neesarg Banglawala. All rights reserved.
#include "InputManager.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

InputManager::InputManager(string path) {
  // Stting up filePath
  filePath = path;

  cout<<"\nFile Manager initalized with path: \""<< filePath <<"\" "<<endl;
}

string InputManager::readFileLineByLine() {
  // Initalize stream to read input file
  static ifstream myfile (filePath);

  // Attempt to open myFile
  if (myfile.is_open()) {
    fileIsOpened = true;

    // File opened, read it line by line
    string line;
    getline(myfile, line);

    if(line == "") {
      // Close the file
      myfile.close();
      filePath = "";
      cout<< "FILE CLOSED!\n"<<endl;
    }

    return line;
    }
  else {
    // File is not opened
    fileIsOpened = false;
    cout<<"\n!!! ERROR: File \""<<filePath<<"\" could not be opened.. !!!\n";
    return "";
  }
}

pair<string, string> InputManager::getBaseAndChildFrom(string line) {
  // Initalizing pair to return; if it get any errors in between
  pair<string, string> baseChildPair = make_pair("ERROR","ERROR");

  if(line != "") {
    // Get position of blank to split line in its components
    int blankAt = line.find(" ");

    if(blankAt != 0) {
      // Everything is okay; make a pair of two words
      baseChildPair = make_pair(line.substr(blankAt+1), line.substr(0, blankAt));
    } else {
      // Either blank not found or it is at first location of the line; which is wrong
      cout<<"\n!!! ERROR: getBaseAndChildFrom-> blankAt == 0.. !!!\n";
    }
  } else {
    // Line is empty
    cout<<"\n!!! ERROR: getBaseAndChildFrom-> line == \"\".. !!!\n";
  }

  return baseChildPair;
}
