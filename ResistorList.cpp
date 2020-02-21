/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include <iostream>
#include<cstdlib>
#include<iomanip>
#include <string>
#include "Resistor.h"
#include "ResistorList.h"
#include "Node.h"
#include "NodeList.h"

//made ResistorList a friend class of resistor class for easier manipulation of the resistor objects, same was done with 
//NodeList classes and Node
//still does not remove purpose of private variables, they can only be shared between the friends

ResistorList::ResistorList() {

}

ResistorList::~ResistorList() {


}

void ResistorList::insertR(string resistor_name, double resistorVal, int endpoints_[2]) {
    if (resistorhead == NULL) {
        resistorhead = new Resistor(resistor_name, resistorVal, endpoints_);
        numRes++; //keeps track of how many resistors are at a node
        return;
    }
    Resistor* temp = resistorhead;
    while (temp -> next != NULL) {
        temp = temp -> next;
    }
    temp -> next = new Resistor(resistor_name, resistorVal, endpoints_);
    numRes++;

}

void ResistorList::checkForR(string resistorname, int & rescount) {
    Resistor* temp = resistorhead;

    if (resistorhead == NULL) {
        return;
    }
    while (temp != NULL) {
        if ((temp -> name) == resistorname) {
            rescount++; //again we need to keep track of how many resistors we find (should appear max 2 times)
            return;
        }
        temp = temp -> next;
    }
    return;

}

bool ResistorList::printResInfo(string resistorname) {
    Resistor* temp = resistorhead;

    if (resistorhead == NULL) {

        return (false); //didn't print anything
    }
    while (temp != NULL) {
        //print only once the name is found
        if (temp -> name == resistorname) {
            temp -> print();
            return (true);
        }
        temp = temp -> next;
    }
    return (false);
}

void ResistorList::printNode(int nodeid) {
    Resistor* temp = resistorhead;

    if (temp == NULL) {
        return;
    } else {
        cout << "Connections at node " << nodeid << ": " << numRes << " resistor(s)" << endl;
        while (temp != NULL) {
            //thread through the ResistorList to print the resistor info
            temp -> print();
            temp = temp -> next;
        }
    }
    return;
}

void ResistorList::modifyRes(string resistorname, double resistorVal, int & numTimesModified) {
    Resistor* temp = resistorhead;
    double oldResVal = 0.0;
    
    //we use a counter to keep track of how many times a resistor shows up (which should be either 0 or 2)
    while (temp != NULL) {
        if (temp -> name == resistorname) {
            oldResVal = temp -> getResistance();
            temp -> resistance = resistorVal;
            numTimesModified++; //increment this every time we change something about the resistor
            if (numTimesModified == 2) {
                cout << "Modified: resistor " << resistorname << " from " << setprecision(2)
                        << fixed << oldResVal << " Ohms " << "to " << setprecision(2)
                        << fixed << temp -> getResistance() << " Ohms" << endl;
            }
            return;
        }
        temp = temp -> next;
    }
    return;
}

void ResistorList::deleteSelectedRes(string resistorname, int & numTimesDeleted) {
    Resistor* temp = resistorhead;
    Resistor* nptr = NULL;

    if (resistorhead == NULL) {
        return;
    }
    //check at the head of the list
    if ((temp -> name == resistorname) && (temp == resistorhead)) {
        resistorhead = temp -> next;
        delete temp;
        numRes = numRes - 1;
        numTimesDeleted++;
        
    } else {
        //here we use 2 pointers, one that follows the other, to keep track of the previous node object
        nptr = temp;
        temp = temp -> next;
        while (temp != NULL) {
            if (temp -> name == resistorname) {
                nptr -> next = temp -> next;
                numTimesDeleted++;
                delete temp;
                numRes = numRes - 1;
            }
            temp = temp -> next;
            nptr = nptr -> next;

        }
    }
    if(numTimesDeleted == 2){
        cout << "Deleted: resistor " << resistorname << endl;
    }
    return;
}

void ResistorList::deleteAll(){
    Resistor* temp = resistorhead;
    
    
    if(resistorhead == NULL){
        return;
    }
    else
        while(temp != NULL){
            resistorhead = temp -> next;
            delete temp;
            numRes = numRes - 1;
            temp = resistorhead;
        }
    resistorhead = NULL;
}

double ResistorList::calculateleftpart(){
    //we calculate the left part of the voltage equation in this function
    Resistor* temp = resistorhead;
    double inverseResSum = 0.0;
    
    while(temp != NULL){
        inverseResSum = inverseResSum + (1 / (temp -> resistance));
        temp = temp -> next;     
    }
    return( 1 / inverseResSum);
    
}

Resistor* ResistorList::getHead(){
    return resistorhead;
}

