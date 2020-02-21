/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <iostream>
#include <cstdlib>
#include <string>
#include<iomanip>
#include "Node.h"
#include "NodeList.h"
#include "ResistorList.h"


NodeList::NodeList() {


}

NodeList::~NodeList() {


}

bool NodeList::checkifNodeExists(int nodeidcpy) {
    //nodeidcpy = the nodeid requested by user 
    Node* temp = head;
    while (temp != NULL) {
        if ((temp -> nodeid) == nodeidcpy) {
            return (true);
        }
        temp = temp -> next;

    }
    return (false);
}

void NodeList::insertAtMiddle(Node* nodepoint) {
    Node* temp2 = nodepoint;
    int localNodeid = temp2 -> nodeid;
    Node* temp1 = head;
    if (head == NULL) {
        head = nodepoint;
        //update lowID, we are adding the first node to the list
        lowID = localNodeid;
        return;
    }
    else if ((temp2 -> nodeid) < lowID) {
        //node belongs to the head of the list
        insertAtHead(temp2);
    } else if ((temp2 -> nodeid) > maxID) {
        insertAtTail(temp2);
    } else if ((localNodeid > lowID) && (localNodeid < maxID)) {
        
        while ((temp1 -> nodeid != localNodeid) && (temp1 -> next != NULL)) {

            if ((localNodeid > (temp1 -> nodeid)) && (localNodeid < (temp1 -> next -> nodeid))) { //means that the nodeid of the node to be inserted is greater than nodeid of current node and less than nodeid of next node               
            
                temp2 -> next = temp1 -> next;
                temp1 -> next = temp2;
            } else {
                temp1 = temp1 -> next;
                
            }
        }

    }

    return;
}

void NodeList::insertAtHead(Node* nodepoint) {

    //we have checked previously for an empty list
    Node* temp = nodepoint;
    temp -> next = head;
    head = temp;
    lowID = temp -> nodeid;

}

void NodeList::insertAtTail(Node* nodepoint) {
    Node* temp = head;

    while (temp -> next != NULL) {
        temp = temp -> next; //keep shifting the node pointer temp
    }
    temp -> next = nodepoint;
    maxID = (temp -> next) -> nodeid;
    nodepoint -> next = NULL;
}

Node* NodeList::getHead() {
    return (head);
}

bool NodeList::checktoSeeIfNodesExist(int inputId) {
    Node* temp = head;

    while (temp != NULL) {
        //keep sweeping through until you find the node with the correct node
        if (temp -> nodeid == inputId) {
            return (true);
        }
        temp = temp -> next;
    }
    return (false);
}

bool NodeList::checkIfRExistsAlready(string resistorname) {
    int rescount = 0;

    Node* temp = head;

    while (temp != NULL) {
        (temp -> resistorobject) -> checkForR(resistorname, rescount);
        temp = temp -> next;
    }
    //for the resistor to exist, it should occur twice
    if (rescount == 2) {
        return (true);
    } else return (false);
}

void NodeList::findNodeAndInsert(int targetID, string resistor_name, double resistorVal, int endpoints_[2]) {

    Node* temp = head;

    while (temp != NULL) {
        if (temp -> nodeid == targetID) {
            //invoke the insertR method on the resistorlist object located in the node
            (*(temp -> resistorobject)).insertR(resistor_name, resistorVal, endpoints_);
            return;
        }
        temp = temp -> next;
    }


}

void NodeList::findRandPrint(string resistorname) {
    Node* temp = head;

    if (temp == NULL) {
        return;
    }
    while (temp != NULL) {
        //print function invoked on the following object
        if ((*(temp -> resistorobject)).printResInfo(resistorname) == true) {
            return;
        }
        temp = temp -> next;
    }

    return;

}

void NodeList::printNode(int nodeid) {
    Node* temp = head;
    if (temp == NULL) {
        cout << "Error: node " << nodeid << "not found" << endl;
        return;
    } else if (checktoSeeIfNodesExist(nodeid) == false) {
        cout << "Error: node " << nodeid << " not found" << endl;
        return;
    } else {
        //keep traversing while you don't find the node with nodeid and while temp doesn't point to NULL
        while ((temp-> nodeid != nodeid) && (temp != NULL)) {
            temp = temp -> next;
        }
        (temp -> resistorobject) -> printNode(nodeid);
    }
    return;

}

void NodeList::printAllNodes() {
    Node* temp = head;

    if (temp == NULL) {
        return;
    } else {
        while (temp != NULL) {
            (temp -> resistorobject) -> printNode(temp -> nodeid);
            temp = temp -> next; //update temp
        }
    }
    return;
}

void NodeList::findRandModify(string resistorname, double resistorVal) {
    Node* temp = head;
    int numTimesModified = 0;

    //no need to check if head points to NULL bc we know the resistor exists
    while (temp != NULL) {
        (temp -> resistorobject) -> modifyRes(resistorname, resistorVal, numTimesModified);
        if (numTimesModified == 2) {
            return;
        }
        temp = temp -> next;
    }

}

void NodeList::setNodeVoltage(int inputID, double newVoltage) {
    Node* temp = head;

    if (checktoSeeIfNodesExist(inputID) == false) {
        cout << "Error: node " << inputID << " not found" << endl;
    } else
        while (temp != NULL) {
            if (temp -> nodeid == inputID) {
                temp -> voltage = newVoltage; //update to new voltage
                temp -> voltageIsFixed = true; //will indicate voltage for this node is set
                cout << "Set: node " << inputID << " to " << newVoltage << " Volts " << endl;
                return;
            }
            temp = temp -> next;
        }
}

void NodeList::deleteRes(string resistorname) {
    Node* temp = head;
    int numTimesDeleted = 0;

    if (checkIfRExistsAlready(resistorname) == false) {
        cout << "Error: resistor " << resistorname << " not found" << endl;
        return;
    } else
        while (temp != NULL) {
            (temp -> resistorobject) -> deleteSelectedRes(resistorname, numTimesDeleted);
            if (numTimesDeleted == 2) {
                return;
            }
            temp = temp -> next;
        }
}

void NodeList::deleteRall(){
    Node* temp = head;
    
    while (temp != NULL){
        (temp -> resistorobject) -> deleteAll();
        temp -> voltageIsFixed = false; 
        temp = temp -> next;
        
    }
    
}

void NodeList::deleteAllNodes(){
    Node *temp = head;
    
    while(temp != NULL){
        if((temp -> resistorobject) != NULL){
            //need to check if there are remaining linked lists in some nodes
            (temp -> resistorobject) -> deleteAll();
        }
        head = temp -> next;
        delete temp;
        temp = head;
    }
}

void NodeList::unsetNodeVoltage(int inputID) {
    Node* temp = head;

    if (checktoSeeIfNodesExist(inputID) == false) {
        cout << "Error: node " << inputID << " not found" << endl;
    } else
        while (temp != NULL) {
            if (temp -> nodeid == inputID) {
                temp -> voltage = 0; //set voltage back to zero
                temp -> voltageIsFixed = false; //will indicate that voltage for this node is unset
                cout << "Unset: the solver will determine the voltage of node " << inputID << endl;
                return;
            }
            temp = temp -> next;
        }
}

bool NodeList::checkForSetVoltage(){
    Node* temp = head;
    
    if(temp == NULL){       
        return (false);
    }
    
    else{
        while (temp != NULL){
        //checking if the voltage is not set
        if(temp -> voltageIsFixed == true){
            return (true);
        }
        temp = temp -> next;
    }
          
}
    return(false);
}

void NodeList::solveNodeVoltages(){
    bool convergenceAchieved = false;    
    Node* temp = head;
    double newVoltage = 0.0;
    double newVoltagelftprt = 0; //left part of voltage equation
    double newVoltageRightprt = 0; //right part of voltage equation
    double nodeVoltageDifference = 0.0;
    
    while ((convergenceAchieved == false)){
      convergenceAchieved = true;
      temp = head;
    
      while (temp != NULL){
          
         if((temp -> voltageIsFixed == false) && (temp -> resistorobject != NULL)){
             //compute the left hand side
             newVoltagelftprt = ((temp -> resistorobject) -> calculateleftpart());
             //compute the right hand side
             newVoltageRightprt = calculateRightPart((temp -> nodeid), (temp -> resistorobject));
             //multiply both sides by each other to get Vo
             newVoltage = newVoltagelftprt * newVoltageRightprt;
             nodeVoltageDifference = (((temp -> voltage) > newVoltage ) ? (temp -> voltage) - newVoltage : newVoltage - (temp -> voltage));
         
             temp -> voltage = newVoltage; //update the node's voltage
             
             
             if (nodeVoltageDifference >= MIN_ITERATION_CHANGE){
                 convergenceAchieved = false; //if it turns to true for all nodes, this condition will not run ever so we exit while loop above
             }
         }
         temp = temp -> next;
      }  
        
    }
       
}

double NodeList::getNodeVoltage(int oppID){
    Node* temp = head;
    
    while((temp != NULL) || ((temp -> nodeid) != oppID)){
        if((temp -> nodeid) == oppID){

            return (temp -> voltage);
        }
        
        temp = temp -> next;
    }  
}

double NodeList::calculateRightPart(int nodeid, ResistorList* head){
    Resistor* temp = (head -> getHead());
    double rightPartSum = 0.0;
    //need to use accessor functions from resistor class, bc we don't have access to the private variables (next, etc) outside
    while (temp != NULL){
       rightPartSum = rightPartSum + (getNodeVoltage((temp -> returnOppNode(nodeid))) / (temp -> getResistance()));
       temp = temp -> getNext(); 
    }
    return(rightPartSum);
}


void NodeList::printUpdatedNodes(){
    
    //we end up in fact printing the voltages of all nodes
    Node* temp = head;
    cout << "Solve:" << endl;
    
    while(temp != NULL){
                   
        cout << "  Node " << temp -> nodeid << ": " << temp -> voltage << " V" << endl;       
        temp = temp -> next;
    }
    
    
}