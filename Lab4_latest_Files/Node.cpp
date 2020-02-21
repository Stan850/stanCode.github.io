/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */


#include <iostream>
#include <cstdlib>
#include <string>
#include "Node.h"
#include "Rparser.h"
#include "Resistor.h"
#include "ResistorList.h"
#include "NodeList.h"


Node::Node(int id, string resistor_name, double resistorVal, int nodepoints[2]){
    nodeid = id;
    resistorobject = new ResistorList();
    (*resistorobject).insertR(resistor_name, resistorVal, nodepoints);
   
   
}
Node::~Node(){
    next = NULL;
    //need to delete what pointer to points to prevent memory leaks
    delete resistorobject;
}




