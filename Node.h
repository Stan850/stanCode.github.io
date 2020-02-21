/* 
 * File:   Node.h
 * Author: JC and VB
 * Author: TSA
 *
 * Updated on August 24, 2016, 01:40 PM
 * Created on October 6, 2013, 12:58 PM
 */

#ifndef NODE_H
#define NODE_H

#include "ResistorList.h"
//#include "Resistor.h"
#include <string>

class Node
{
private:
    
 //  int numRes=0; // number of resistors currently connected
   int nodeid = 0;
   ResistorList* resistorobject = NULL;
   Node* next = NULL;
   double voltage = 0.0;
   bool voltageIsFixed = false;

public:
   Node(int id, string resistor_name, double resistorVal, int nodepoints[2]); 
   ~Node();

   //functions were left here in case if they are needed later
   
   
   
   // Checks to see if the resistor can be added to position rIndex
   // in the resistor array. Returns true if yes, otherwise false.
   //bool canAddResistor(int rIndex);
   
   //void printInfoFromIndices(int node);

   // Updates resIDArray to make the resistor in position rIndex in
   // the resistor array connected to this node.
  // void addResistor (int rIndex); 

   // prints the whole node
   // nodeIndex is the position of this node in the node array.
   //void print (int nodeIndex); 
   
   //void resetNodeObjects();
   
  // int getNodeid();
   //Node* getNext();
   
   friend class NodeList;
};

#endif	/* NODE_H */
