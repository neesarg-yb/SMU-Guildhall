//  Created by Neesarg Banglawala on 12th Feb, 2017.
//  Work completed on 16th Feb, 2017.
//  Copyright (c) 2017 Neesarg Banglawala. All rights reserved.
#include "ExportManager.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

ExportManager::ExportManager(vector<Node *> *independentBaseNodes) {
  // Get reference of independentBaseNodes & store it locally
  this->independentBaseNodes = independentBaseNodes;
  cout<<"ExportManager initalized, size: "<<this->independentBaseNodes->size()<<endl;
}


void ExportManager::saveToFile() {
  // for every independentBaseNodes
      // Use DFS to traverse - it will have a universal visited vector<string> *
      //                        (so it doesn't traverse through visited node, again)
        // While traversing:
                // add "childName baseName" in vector<string> *constructedNotations
  vector<string> *constructedNotations = new vector<string>;
  vector<string> *visited = new vector<string>;

  // For every independentBaseNodes
  for(int i=0; i<independentBaseNodes->size(); i++) {
    // Do the main task!
    DFSTraverseUtil(independentBaseNodes->at(i), constructedNotations, visited);
  }
  delete visited;

  // Export constructedNotations according to user
  char choice = '0';
  cout<<"1: Save to resource.txt file"<<endl;
  cout<<"2: Save to new file"<<endl;
  cout<<"\n(Warning: Because of the notation style, \"not-usable\" nodes will be saved as \"usable\"..)"<<endl;
  cout<<"\nChoice number = ";
  cin>>choice;
  while (getchar() != '\n'); // Clear input buffer; it will be helpful in main.cpp's while loop

  // To write in file
  ofstream myfile;

  // Behave according to choice
  switch (choice) {
    case '1':
      // Save to resource.txt
      myfile.open ("resource.txt");

      // For every constructedNotations
      for(int i=0; i<constructedNotations->size(); i++) {
        // Write every constructedNotations to file
        myfile << constructedNotations->at(i) << endl;
      }

      cout<<"\nIt should be saved in resource.txt file by now.."<<endl;
      break;

    case '2': {
      // Save to other file
      string fileName = "new";
      cout<<"Filename : ";
      cin>>fileName;
      while (getchar() != '\n'); // Clear input buffer; it will be helpful in main.cpp's while loop
      fileName = fileName + ".txt";

      myfile.open (fileName);
      // For every constructedNotations
      for(int i=0; i<constructedNotations->size(); i++) {
        // Write it in file
        myfile << constructedNotations->at(i) << endl;
      }

      cout<<"\nIt should be saved in "<<fileName<<" file by now.."<<endl;
      break;
    }

    default:
      // Not a valid choice
      cout<<"\nExportManager: No valid choice selected!"<<endl;
      break;
  }

  // Closing fileOperation
  myfile.close();


  delete constructedNotations;
}


void ExportManager::DFSTraverseUtil(Node* traverseNode, vector<string> *producedNotation, vector<string> *visited) {

  // add node's name to visitedVector
  visited->push_back(traverseNode->name);

  // Recursion for all of its childNode(s)
  for(int c=0; c<traverseNode->childNode.size(); c++) {

    // Get one childNode to work on
    Node * nextChild = traverseNode->childNode[c];

    ////////////////////////////////////////////////////
    // Got in; do the stuff of constructing notation  //
    //------------------------------------------------//
    // Here traverseNode is being visited first time. //
    // nextChild's discovery for traverseNode is also //
    //                      firt time because of it.  //
    ////////////////////////////////////////////////////
    // So, Generate notation for this link. It will be unique
    producedNotation->push_back( (nextChild->name + " " + traverseNode->name) );


    if(nextChild->searchThisNodeInVector(visited)) {
      // its chilNode is already visited
      // Do nothing

    } else {
      // This childNode is not visited
      // Traverse it
      DFSTraverseUtil(nextChild, producedNotation, visited);
    }
  }
}
