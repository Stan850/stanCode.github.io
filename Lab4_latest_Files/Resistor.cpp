/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <iostream>
#include<cstdlib>
#include<iomanip>
#include "Node.h"
#include "Resistor.h"



Resistor::Resistor(string name_,double resistance_,int endpoints_[2]){
    
   resistance = resistance_;
   name = name_;
   endpointNodeIDs[0] = endpoints_[0];
   endpointNodeIDs[1] = endpoints_[1];
}

Resistor::~Resistor(){
 next = NULL;   
}


string Resistor::getName() const{

return name;

}

double Resistor::getResistance() const{
    
    return resistance;
}

void Resistor::setResistance (double resistance_){
    
    resistance = resistance_;
   
}
int Resistor::returnOppNode(int nodeid){
    int oppNode = 0;
    
    if(endpointNodeIDs[0] != nodeid){
        return (endpointNodeIDs[0]);
    } 
    else return(endpointNodeIDs[1]); 
    
}

Resistor* Resistor::getNext(){
    return next;
}

void Resistor::print(){
    
   
    cout << left << setw(20) << name << right << setw(8) << setprecision(2) << fixed << resistance << " Ohms " << endpointNodeIDs[0] << " -> " << endpointNodeIDs[1] << endl;
    
}


