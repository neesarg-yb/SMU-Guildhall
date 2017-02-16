//  Created by Neesarg Banglawala on 12th Feb, 2017.
//  Copyright (c) 2017 Neesarg Banglawala. All rights reserved.
/*
 *
 *  || Makefile commands ||
 *  make: will compile whole project and creates executable "output" file
 *  make clean: will clean created output and .o files
 *  make keepJustOutput: will clean all .o files, not the output file.
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

// Just a silly function to clear console using endl(s) :p
void clearConsole();

void flush_stream(std::istream& stream);


int main(int argc, char const *argv[]) {
  // Setting up ResourceManager: It handles the whole system
  ResourceManager theResourceManager;

  // Stting up file InputManager
  InputManager fileInput = InputManager("resource.txt");

  // Read txt file till end
  string line = fileInput.readFileLineByLine();
  while (line != ""){
    // get input pair from file
    pair<string, string> baseAndChild = fileInput.getBaseAndChildFrom(line);
    // add that pair via theResourceManager
    theResourceManager.addBaseAndChildNodesFromStringsToGame(baseAndChild.first, baseAndChild.second);

    // read next line
    line = fileInput.readFileLineByLine();
  }

  // Display structure 1st time
  clearConsole();
  displayStructureOfNodesInVector(theResourceManager.independentBaseNodes);

  /////////////////////////
  // Input Loop - starts //
  /////////////////////////
  char input;
  cout<<"Press enter to move ahead.. "<<endl;
  while (getchar() != '\n'); // Ignores every other characters untill '\n'

  do {
    cout<<"\n\n-------------------"<<endl;
    cout<<"      Commands     "<<endl;
    cout<<"-------------------"<<endl;
    cout<<"-> q: quit"<<endl;
    cout<<"-> d: delete a node"<<endl;
    cout<<"-> a: add a node or link"<<endl;
    cout<<"-> g: plot graph of current structure"<<endl;
    cout<<"-> i: informations about a node"<<endl;

    // Take user's input
    cout<<"Input = ";
    input = getchar();

    if(input == '\n') {
      cout<<"\nYou should not hit \"just enter\" here!"<<endl;
      cout<<"Hit it again to goto Commands Menu.."<<endl;
    }
    // Ignores every other characters utill it finds '\n'
    while(getchar() != '\n');

    // Switch for operations
    switch (input) {
      case 'q':
      // quit selected
        clearConsole();
        cout<<"\n\n-------------------"<<endl;
        cout<<"       Quit        "<<endl;
        cout<<"-------------------"<<endl;
        cout<<"Deleting all nodes..\nGood Bye!\n"<<endl;
        break;

      case 'd': {
      // delete node selected
        clearConsole();
        cout<<"\n\n-------------------"<<endl;
        cout<<"       Delete     "<<endl;
        cout<<"-------------------"<<endl;

        string userInput;
        cout<<"Node name : ";
        getline(cin, userInput);
        theResourceManager.deleteNodeNamed(userInput);

        break;
      }

      case 'a': {
      // add node or link selected
        clearConsole();
        cout<<"\n\n-------------------"<<endl;
        cout<<"  Add Node & Link "<<endl;
        cout<<"-------------------"<<endl;
        cout<<"-> To add a single node, write : \"node-name\""<<endl;
        cout<<"-> To add multiple nodes, write: \"childName baseName\""<<endl;
        cout<<"-> To add new link, write      : \"existingChildName existingBaseName\""<<endl;
        cout<<"              OR               : one of these two nodes can also be totally new."<<endl;
        cout<<"(Note: Name of a node should not contain any whitespaces!)"<<endl;
        cout<<endl;
        cout<<"-> Exit: When you're finished, just press another enter!\n"<<endl;

        string userInput;
        do{
          cout<<"Add : ";
          getline(cin, userInput);

          // get pair from input string
          pair<string, string> baseAndChildFromUser = fileInput.getBaseAndChildFrom(userInput);
          // add that pair via theResourceManager
          theResourceManager.addBaseAndChildNodesFromStringsToGame(baseAndChildFromUser.first, baseAndChildFromUser.second);
        } while(userInput != "");
        break;
      }

      case 'g':
      // plot graph selected
        clearConsole();
        cout<<"\n\n-------------------"<<endl;
        cout<<"       Graph        "<<endl;
        cout<<"-------------------"<<endl;
        cout<<"Plotting current structure.."<<endl;
        displayStructureOfNodesInVector(theResourceManager.independentBaseNodes);
        break;

      case 'i': {
      // information selected
        clearConsole();
          cout<<"\n\n-------------------"<<endl;
          cout<<"    Information   "<<endl;
          cout<<"-------------------"<<endl;

        string nodeN;
        Node * gotNode;

        cout<<"Search for a node named = ";
        cin>>nodeN;
        cin.sync();
        while(getchar() != '\n');

        gotNode = theResourceManager.searchForNode(nodeN);
        if(gotNode != NULL) {
          gotNode->description();
        } else {
            cout<<"\nNo matching node found!"<<endl;
        }

        break;
      }

      default:
      // no matching commands
        clearConsole();
        cout<<"\nNo matching command found! Try again.."<<endl;
        break;
    }

  } while(input != 'q');

  /////////////////////////
  //  Input Loop - ends  //
  /////////////////////////

  // proceed to quit, delete everything!
  theResourceManager.deleteAllIndependentBaseNodesSafely();

  return 0;
}


void displayStructureOfNodesInVector(vector<Node *> baseNodes) {
  // Display independentBaseNodes
  cout<<"\n\n###################################.."<<endl;
  cout<<"#"<<endl;
  cout<<"#  Nodes without any baseNode = { ";
  for(int i=0; i<baseNodes.size(); i++) {
    cout<<"\""<<baseNodes.at(i)->name <<"\" ";
  }
  cout<<" }"<<endl;
  cout<<"#"<<endl;
  cout<<"###################################.."<<endl;

  // For all independentBaseNodes in given vector
  for(int indN = baseNodes.size(); indN >=1; indN--) {

    cout<<"\n\n--------- Structure of \""<<baseNodes[indN-1]->name<<"\" --------- "<<endl;
    baseNodes[indN-1]->makeGraphOfThis();
    cout<<"\n--------- ----------------- --------- \n"<<endl;
  }
}

void clearConsole() {
  for(int i=0; i<60; i++) {
    cout<<endl;
  }
}

void flush_stream(std::istream& stream)
{
    stream.clear();
    stream.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}
