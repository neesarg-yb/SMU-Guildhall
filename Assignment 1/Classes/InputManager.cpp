#include "InputManager.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

InputManager::InputManager(string path) {
  filePath = path;
  cout<<"\nFile Manager Initalized with path: \""<< filePath <<"\" "<<endl;
}

string InputManager::readFileLineByLine() {
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
      cout<< "\nFILE CLOSED!\n";
    }

    return line;

    }
  else {
    fileIsOpened = false;
    cout<<"\n!!! ERROR: File \""<<filePath<<"\" could not be opened.. !!!\n";
    return "";

  }
}

pair<string, string> InputManager::getBaseAndChildFrom(string line) {

  pair<string, string> baseChildPair = make_pair("ERROR","ERROR");
  if(line != "") {
    // Get position of blank to split line in its components
    int blankAt = line.find(" ");
    if(blankAt != 0) {
      baseChildPair = make_pair(line.substr(blankAt+1), line.substr(0, blankAt));
      // string childNode = line.substr(0, blankAt);
      // string parentNode = line.substr(blankAt+1);

      // cout << parentNode;
      // cout << " -> " << childNode << endl;
    } else {
      cout<<"\n!!! ERROR: getBaseAndChildFrom-> blankAt == 0.. !!!\n";
    }
  } else {
    cout<<"\n!!! ERROR: getBaseAndChildFrom-> line == \"\".. !!!\n";
  }
  return baseChildPair;
}
