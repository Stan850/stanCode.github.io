/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <iostream>
#include <cstdlib>
#include "Node.h"
#include "Rparser.h"
#include "Resistor.h"

extern Node* nodeArray;
extern Resistor** ResistorArray;

Node::Node(){
   for(int i = 0; i < MAX_RESISTORS_PER_NODE; i++){
       resIDArray[i] = -1;
   }
}
Node::~Node(){

}

bool Node::canAddResistor(int rIndex){
      
    
if (numRes >= MAX_RESISTORS_PER_NODE){
    return (false);
    
}

else {
    return (true);
}
   // Updates resIDArray to make the resistor in position rIndex in
   // the resistor array connected to this node.
}

void Node::addResistor (int rIndex){
    //available index keeps tracks of the next available index to store the
    // the resistor index of a resistor
    
    
    resIDArray[numRes] = rIndex;       
    numRes++;
}
 
void Node::printInfoFromIndices(int node){
    int numResAdded = 0;
    
    //loop used to find how many resistors were added to a node
    for (int i = 0; i < MAX_RESISTORS_PER_NODE; i++){
        if(resIDArray[i] != -1){
            numResAdded++;
        }
    }
    
cout << "Connections at node " << node << ": " << numResAdded << " resistor(s)" <<endl; 
    
    for (int i = 0; i < MAX_RESISTORS_PER_NODE; i++){
        if(resIDArray[i] != -1){
            cout << "  ";
            //we use resIDArray[i] to access the Resistor object using which provides the index we need
            ResistorArray[resIDArray[i]]->print();
        }
    }
}

void Node::resetNodeObjects(){
    numRes = 0;
    //i keeps track of the index of the resIDArray
    for(int i = 0; i < MAX_RESISTORS_PER_NODE; i++){
        //-1 is used because indices all only be >=0
       resIDArray[i] = -1;
   }
}
    