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
  if(baseName == "ERROR" || childName == "ERROR") {
    // Ignore these input

  } else if(childName == "NULL") {
    // Add this base to independentBaseNodes
    Node *baseNodeReference = searchForNode(baseName);

    // got baseName successfully
    // Check for duplications
    if(baseNodeReference != NULL) {
      // CASE I: Base is already there in the system
      cout<<"ResourceManager: "<<baseName<<" is already in the system!"<<endl;
    } else {
      // CASE II: Base not found!
      baseNodeReference = new Node;
      baseNodeReference->name = baseName;
      baseNodeReference->usable = true;

      independentBaseNodes.push_back(baseNodeReference);
    }

  } else {
    // got baseName and childName, successfully
    // cout<<"gotIt: "<<baseName<<", "<<childName<<endl;

    // Search for baseNode in game's existing structure
        // get baseNodeReference
        Node *baseNodeReference = searchForNode(baseName);
    // Search for childNode in game's existing structure
        // get childNodeReference
        Node *childNodeReference = searchForNode(childName);

    // VI-Cases on diffrent cases
          if(baseNodeReference == NULL && childNodeReference == NULL) {
            // cout<<"Yup! b&c == NULL!"<<endl;
            // CASE I: Base and Child both are not present in the game
            // create both new; and pass into addBaseAndChildNodesSafely()
            baseNodeReference = new Node;
            baseNodeReference->name = baseName;

            childNodeReference = new Node;
            childNodeReference->name = childName;

            // Add baseNode first
            // Add reference of its new childNode in it
            // Make it usable
            independentBaseNodes.push_back(baseNodeReference);
            baseNodeReference->childNode.push_back(childNodeReference);
            baseNodeReference->usable = true;

            // Setup childNode for the system
            // Add reference of its baseNode in it
            // Add baseNode name to its reliesOnNodes vector
            // Make it usable
            childNodeReference->baseNode.push_back(baseNodeReference);
            childNodeReference->reliesOnNodes.push_back(baseName);
            childNodeReference->usable = true;

          } else if(baseNodeReference != NULL && childNodeReference != NULL) {
            // cout<<"Yup! b&c != NULL!"<<endl;

            // CASE II: Base and Child both are in the game   | I.E. bothNodeReferences != NULL
            // If both are linked; Link can't be changed
            // If not linked => add a link

            // Check if link Exist!
            bool linkExists = false;

            if(baseNodeReference->childNode.size() != 0) {
              for(int i=0; i<baseNodeReference->childNode.size(); i++) {
                // cout<<"i1 = "<<i<<endl;
                // Search in childNodes of the baseNode
                if(baseNodeReference->childNode.at(i) == childNodeReference) {
                  linkExists = true;
                  break;
              }
            }

            }
            if(linkExists == false && baseNodeReference->baseNode.size() != 0) {
              // Search in baseNodes of the baseNode
              for(int i=0; i<baseNodeReference->baseNode.size(); i++) {
                // cout<<"i2 = "<<i<<endl;
                if(baseNodeReference->baseNode.at(i) == childNodeReference) {
                  linkExists = true;
                  break;
                }
              }
            }

            // If not: add it
            if(linkExists == false) {
                // cout<<"\nYAY! Link not exist!!"<<endl;
                // Run add operation
                // Check if childNode is in independentBaseNodes
                for(int i=0; i<independentBaseNodes.size(); i++) {
                  if(independentBaseNodes.at(i) == childNodeReference) {
                    // if Yes:
                    // Remove the childNode's reference from there
                    independentBaseNodes.erase(independentBaseNodes.begin() + i);
                    break;
                  }
                }

                //     Now add reference of childNode in baseNode
                //     Add reference of baseNode in childNode
                //     Add baseNode name in reliesOnNodes vector of childNode

                //////////////////////////////////////////////////////////////////////////
                //     Change childNode's usability; it can affect by this operation    //
                //////////////////////////////////////////////////////////////////////////


                baseNodeReference->childNode.push_back(childNodeReference);
                childNodeReference->baseNode.push_back(baseNodeReference);
                // if baseNode not present in reliesOnNodes, add it
                if( childNodeReference->searchNameInVectorOfString(baseNodeReference->name, childNodeReference->reliesOnNodes) != true ) {
                  // Not present, Add it
                  childNodeReference->reliesOnNodes.push_back(baseNodeReference->name);
                } else {
                  // baseNodeReference is already in reliesOnNodes
                  // Do not add it again
                  cout<<"ResourceManager: baseNode already present in reliesOnNodes!"<<endl;
                }
                if(childNodeReference->isUsable() == true) {
                  childNodeReference->markUsableAs(true);
                } else {
                  childNodeReference->markUsableAs(false);
                  // childNodeReference->description();
                }

            } else {
              // If exist; can't change it
              cout<<"ERROR: Can't change the link between "<<baseNodeReference->name<<" & "<<childNodeReference->name<<". It is already there in system."<<endl;
            }

          } else if(baseNodeReference != NULL && childNodeReference == NULL) {
            // cout<<"Yup! b != NULL, c == NULL!"<<endl;

            // CASE III: Base is in the game; but Child isn't | I.E. childNodeReference == NULL
            childNodeReference = new Node;
            childNodeReference->name = childName;

            // Setup childNode for the system
            // Add its link to the existing baseNode
            // Add baseNode's link in itself(childNode)
            // Add baseNode's name in reliesOnNodes of itself
            // Check if all reliesOnNodes are in baseNode vector & in usable state
                    // If yes-> mark childNode as usable
                    // If no->  mark it as not usable
            baseNodeReference->childNode.push_back(childNodeReference);
            childNodeReference->baseNode.push_back(baseNodeReference);
            childNodeReference->reliesOnNodes.push_back(baseNodeReference->name);
            if(childNodeReference->isUsable() == true) {
              childNodeReference->usable = true;
            } else {
              childNodeReference->usable = false;
            }

          } else if(baseNodeReference == NULL && childNodeReference != NULL) {
            // cout<<"Yup! b == NULL, c != NULL!"<<endl;
            // CASE IV: Child is in the game; but Base isn't  | I.E. baseNodeReference == NULL
            baseNodeReference = new Node;
            baseNodeReference->name = baseName;
            baseNodeReference->usable = true;

            // Check if childNode is in independentBaseNodes
            for(int i=0; i<independentBaseNodes.size(); i++) {
              if(independentBaseNodes.at(i) == childNodeReference) {
                // if Yes:
                // Remove the childNode's reference from there
                independentBaseNodes.erase(independentBaseNodes.begin() + i);
                break;
              }
            }

            //     Add new baseNode in independentBaseNodes
            //     Now add reference of childNode in baseNode
            //     Add reference of baseNode in childNode
            //     Add baseNode name in reliesOnNodes vector of childNode
            //     Don't change childNode's usability; it won't affect by this operation
            independentBaseNodes.push_back(baseNodeReference);
            baseNodeReference->childNode.push_back(childNodeReference);
            childNodeReference->baseNode.push_back(baseNodeReference);
            // if baseNode not present in reliesOnNodes, add it
            if( childNodeReference->searchNameInVectorOfString(baseNodeReference->name, childNodeReference->reliesOnNodes) != true ) {
              // Not present, Add it
              childNodeReference->reliesOnNodes.push_back(baseNodeReference->name);
            } else {
              // baseNodeReference is already in reliesOnNodes
              // Do not add it again
              cout<<"ResourceManager: baseNode already present in reliesOnNodes!"<<endl;
            }

            if(childNodeReference->isUsable() == true) {
              childNodeReference->markUsableAs(true);
            } else {
              childNodeReference->markUsableAs(false);
              // childNodeReference->description();
            }

          } else {
            cout<<"ERROR: NO INPUT CASES MATCHED!!"<<endl;
          }
  }


}

Node* ResourceManager::searchForNode(string nodeName) {
  Node* result = NULL;
  // For every independentBaseNodes
  // Run DFS search to find node
  for(int i=0; i<independentBaseNodes.size(); i++) {
    result = independentBaseNodes[i]->findNodeNamedUsingDFS(nodeName);
    if(result != NULL) {
      // Node found; return it!
      return result;
    } else {
      // keep going
    }
  }

  // result will be NULL
  return result;
}


void ResourceManager::saveCurrentStructureInResourcesFile() {
  ofstream myfile;
  myfile.open ("example.txt");
  myfile << "Writing this to a file.\n";
  myfile.close();

}

void ResourceManager::deleteNodeNamed(string nodeName) {
  // get link to thatNode
  Node *gotNode = searchForNode(nodeName);

  if(gotNode != NULL) {
    // If gotNode is from independentBaseNodes
        // First delete its entry from independentBaseNodes
        // Then hand it over to deleteThisNode()
    if(gotNode->baseNode.size() == 0) {
      // If no baseNode, then its in independentBaseNodes
      for(int i=0; i<independentBaseNodes.size(); i++) {
        if(independentBaseNodes.at(i)->name == gotNode->name) {
          // Found its entry; remove it
          independentBaseNodes.erase(independentBaseNodes.begin() + i);
          cout<<"Entry of: "<<gotNode->name<<" erased from independentBaseNodes."<<endl;
          break;
        }
      }
    }

    cout<<"ResourceManager: node found, passing it to deleteThisNode()!"<<endl;
    vector<Node *> *leftChildNode = gotNode->deleteThisNode();
    // Add them to independentBaseNodes
    for(int i=0; i<leftChildNode->size(); i++) {
      independentBaseNodes.push_back(leftChildNode->at(i));
    }
    delete leftChildNode;
  } else {
    cout<<"ResourceManager: to delete, node not found!"<<endl;
  }
}
