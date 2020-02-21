/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */


/* 
 * File:   main.cpp
 * Author: oparnica
 *
 * Created on September 26, 2017, 1:07 PM
 */
#include<iostream>
#include<sstream>
#include<string>
#include<iomanip>
#include<cstdlib>
#include "Node.h"
#include "Resistor.h"
#include "Rparser.h"
#include "NodeList.h"
#include "ResistorList.h"

using namespace std;




//functions below checks if all arguments are valid following the appropriate command by calling 
//other functions that individually check for errors
//note if resistor_name is not a parameter, it is checked in main
//resistorstream.clear() will only clear flags
//resistorstream.str("") will clear the stream

/*
 * 
 */
int Rparser(NodeList & nodelist) {

    string line;
    string command;
    string resistor_name;
    double resistorVal;
    int nodeid;
    int nodeid1;
    double voltage;



    cout << "> ";
    getline(cin, line);

    while (!cin.eof()) {

        stringstream resistorstream(line);

        resistorstream >> command;


        if (command == "insertR") {

            resistorstream >> resistor_name;
            if (resistor_name == "all") {
                cout << "Error: resistor name cannot be the keyword \"all\"" << endl;
                resistorstream.clear();
                resistorstream.str("");
            } else if (checkInsertInput(resistorstream, resistorVal, nodeid, nodeid1, resistor_name, nodelist) == true) {
                cout << "Inserted: resistor " << resistor_name << " " << setprecision(2)
                        << fixed << resistorVal << " Ohms " << nodeid << " -> " << nodeid1 << endl;
            }
            resistor_name = "";
            //clears the string because whitespace will not updated the string contents of the name
            //if the name contained "all" previously and for the next input whitespace is entered
            //the program would output the same error, b/c the string was not cleared

        } else if (command == "modifyR") {
            resistorstream >> resistor_name;

            if (resistor_name == "all") {
                cout << "Error: resistor name cannot be the keyword \"all\"" << endl;
                resistorstream.clear();
                resistorstream.str("");
            } else if (checkModifyRInput(resistorstream, resistorVal, nodelist, resistor_name) == true) {

            }
            resistor_name = ""; //again clear it for the same reason above (also to be safe)

        } else if (command == "printR") {

            printR(resistorstream, resistor_name, nodelist);
            resistor_name = "";

        } else if (command == "printNode") {
            //printNode will decide what to output based on the input
            printNode(resistorstream, resistor_name, nodeid, nodelist);

        } else if (command == "deleteR") {
            deleteR(resistorstream, resistor_name, nodelist);
            resistor_name = "";
        } else if (command == "setV") {
            setV(resistorstream, nodeid, voltage, nodelist);
        } else if (command == "unsetV") {            
            unsetV(resistorstream, nodeid, nodelist);
        }
        else if (command == "unsetV") {
       
            unsetV(resistorstream, nodeid, nodelist);
        }
        else if(command == "solve"){
            solveVoltages(nodelist);
        }
        else {
            cout << "Error: invalid command\n";
            resistorstream.clear();
            resistorstream.str("");
        }
        command = "";
        cout << "> ";
        getline(cin, line);
    }
 
    return 0;
}

bool checkInsertInput(stringstream &resistorstream, double &resistorVal, int &nodeid, int &nodeid1, string &resistor_name, NodeList & nodelist) {

    //here we want to know if we reach an EOF too soon (it also checks for type mismatches)
    if (checkForFailandEOF(resistorstream) == true) {
        return (false);
    }
    resistorstream >> resistorVal;
    //need to check if EOF is reached too soon or for rresistorVal is an invalid argument
    if (checkResistorVal(resistorstream, resistorVal) == false) {
        return (false);
    }
    if (checkForFailandEOF(resistorstream) == true) {
        return (false);
    }
    resistorstream >> nodeid;
    if (checkNodeId(resistorstream) == false) {
        return (false);
    }
    if (checkForFailandEOF(resistorstream) == true) {
        return (false);
    }
    resistorstream >> nodeid1;
    if (checkNodeId(resistorstream) == false) {
        return (false);
    }

    //ignore white spaces so EOF can be checked for too many args 
    ignoreWhitespaceAtTheEnd(resistorstream);
    //false here means an EOF has not been read, there are more characters in the stream
    if (checkForTooManyArg(resistorstream) == false) {
        return (false);
    }

    /*if (checkToInsertRintoResAr(resistorstream, resistorVal, nodeid, nodeid1, resistor_name, nodelist) == false) {
        return (false); //means that there is no space to add or same name 
    }
    */
    if (nodeid == nodeid1) {
        cout << "Error: both terminals of resistor connect to node " << nodeid << endl;
        resistorstream.clear();
        resistorstream.str("");
        return (false);
    }
     if(insertRintoRresAr(resistorVal, nodeid, nodeid1, resistor_name, nodelist) == true){
     return(true);
     }
     else return (false);
}

bool checkForFailandEOF(stringstream &resistorstream) {

    //if a fail flag is raised, its because of 1 of 2 cases below
    if (resistorstream.fail()) {
        if (resistorstream.eof()) {
            cout << "Error: too few arguments\n";
            resistorstream.clear();
            resistorstream.str("");
        } else {
            cout << "Error: invalid argument\n";
            resistorstream.clear();
            resistorstream.str("");
        }
        return (true);
    }
    return (false);
}

bool checkResistorVal(stringstream &resistorstream, double &resistorVal) {

    if (checkForFailandEOF(resistorstream) == true) {
        return (false);
    }
    //if we "6feffwfnwfn" is entered we want to output an error otherwise
    //the stream will only assign 6 to resistorVal and not complain unless
    //it wants to extract more input of int or double
    if (resistorstream.peek() != -1 && (resistorstream.peek() != ' ')) {
        cout << "Error: invalid argument\n";
        resistorstream.clear();
        resistorstream.str("");
        return (false);
    }
    if (resistorVal < 0) {
        cout << "Error: negative resistance\n";
        resistorstream.clear();
        resistorstream.str("");
        return (false);
    }
    return (true);
}

bool checkNodeId(stringstream &resistorstream) {

    //again check for EOFs that pop up too soon
    if (checkForFailandEOF(resistorstream) == true) {
        return (false);
    }
    if (resistorstream.peek() != -1 && (resistorstream.peek() != ' ')) {
        cout << "Error: invalid argument\n";
        resistorstream.clear();
        resistorstream.str("");
        return (false);
    }
    else return (true);
}

bool checkModifyRInput(stringstream &resistorstream, double & resistorVal, NodeList & nodelist, string Tempname) {

    if (checkForFailandEOF(resistorstream) == true) {
        return (false);
    }

    resistorstream >> resistorVal;
    if (checkResistorVal(resistorstream, resistorVal) == false) {
        return (false);
    }
    //again to check EOF properly, need to ignore white spaces after the last correct argument
    ignoreWhitespaceAtTheEnd(resistorstream);
    if (checkForTooManyArg(resistorstream) == false) {
        return (false);
    } else {
        modifyRes(Tempname, resistorVal, nodelist);
        return (true);
    }
}

bool checkForTooManyArg(stringstream &resistorstream) {

    //no EOF means there is still content left in the stream
    if (!resistorstream.eof()) {
        cout << "Error: too many arguments\n";
        resistorstream.clear();
        resistorstream.str("");
        return (false);
    }
    return (true);
}

void printR(stringstream & resistorstream, string & resistor_name, NodeList & nodelist) {

    resistorstream >> resistor_name;
    if (checkForFailandEOF(resistorstream) == true) {
        return;
    }
    ignoreWhitespaceAtTheEnd(resistorstream);
    if (checkForTooManyArg(resistorstream) == false) {
        return;  
    } else {
        printname(resistor_name, nodelist);
    }
    return;
}

void printNode(stringstream & resistorstream, string & resistor_name, int & nodeid, NodeList & nodelist) {

    //ignores white space because we want to check for EOF at the end if no args are entered
    ignoreWhitespaceAtTheEnd(resistorstream);

    //we check for EOF here because otherwise after nodeid is entered it would complain
    //for too few args b/c it is encountered
    //not the case for other functions because they all either take more than one input
    //or first argument is a string
    if (resistorstream.eof()) {
        cout << "Error: too few arguments\n";
        resistorstream.clear();
        resistorstream.str("");
        return;
    }
    resistorstream >> nodeid;

    //don't output an error yet because the input could be the string "all", so clear fail flags
    if (resistorstream.fail()) {
        resistorstream.clear();
        resistorstream >> resistor_name;
        if (resistor_name == "all") {
            ignoreWhitespaceAtTheEnd(resistorstream);
            if (checkForTooManyArg(resistorstream) == true) {
                printNAll(nodelist);
            }
        } else {
            //if not an int or all, then we have an error
            cout << "Error: invalid argument\n";
            resistorstream.clear();
            resistorstream.str("");
            resistor_name = "";
            return;
        }
        //at this point we have to check if the node value we have is valid
    } else if (checkNodeId(resistorstream) == true) {
        ignoreWhitespaceAtTheEnd(resistorstream);
        if (checkForTooManyArg(resistorstream) == true) {
            printN(nodeid, nodelist);
        }
    }
    return;
}

void ignoreWhitespaceAtTheEnd(stringstream & resistorstream) {
    while (resistorstream.peek() == ' ') {
        resistorstream.ignore(1, '\n');
    }
    return;
}

void deleteR(stringstream & resistorstream, string & resistor_name, NodeList & nodelist) {

    //this function behaves similarly to printR
    resistorstream >> resistor_name;
    if (checkForFailandEOF(resistorstream) == true) {
        return;
    }
    ignoreWhitespaceAtTheEnd(resistorstream);
    if (checkForTooManyArg(resistorstream) == false) {
        return;
    } else if (resistor_name == "all") {
        nodelist.deleteRall();
        cout << "Deleted: all resistors" << endl;        
    } else {
        nodelist.deleteRes(resistor_name);
        
    }
} 

Node* createNode(int nodeid, double resistorVal, string resistor_name, int nodepoints[2]) {
    Node* newNode = new Node(nodeid, resistor_name, resistorVal, nodepoints);
    return (newNode);
}

bool insertRintoRresAr(double resistorVal, int nodeid, int nodeid1, string resistor_name, NodeList & nodelist) {
   
    int nodepoints[2] = {nodeid, nodeid1};
    //id array used to store node IDs temporarily

    if (nodelist.checkIfRExistsAlready(resistor_name) == true){
        cout << "Error: Resistor " << resistor_name << " already exists" << endl;
        return (false);
    }   
    
    else if (nodelist.getHead() == NULL) {
        Node* newNode1 = createNode(nodeid, resistorVal, resistor_name, nodepoints);
        Node* newNode2 = createNode(nodeid1, resistorVal, resistor_name, nodepoints);
        
        //want to know which one should be added to the head and which one to the tail
        if(nodeid < nodeid1){
        nodelist.insertAtHead(newNode1);
        nodelist.insertAtTail(newNode2);
        }
        else{
        nodelist.insertAtHead(newNode2);
        nodelist.insertAtTail(newNode1);
        }
        return(true);
    }
    
    else {
     if (createNecessaryNodes(nodelist, nodeid, resistorVal, resistor_name, nodepoints) == false){
         //means that the node already exists but we still need to add resistors
     nodelist.findNodeAndInsert(nodeid, resistor_name, resistorVal, nodepoints);
     
    }
     if (createNecessaryNodes(nodelist, nodeid1, resistorVal, resistor_name, nodepoints) == false){
         //means that the node already exists but we still need to add resistors
     nodelist.findNodeAndInsert(nodeid1, resistor_name, resistorVal, nodepoints);
    
    }
return(true);     
}
}

bool createNecessaryNodes(NodeList & nodelist, int inputId, double resistorVal, string resistor_name, int nodepoints[2]){
    if (nodelist.checktoSeeIfNodesExist(inputId) == false){
       Node* newNode = new Node(inputId, resistor_name, resistorVal, nodepoints);
       //we insert at the middle but will still check in that function if we insert at head or tail       
       nodelist.insertAtMiddle(newNode);
       return(true);
    }
    else return(false);
}

void printname(string resistor_name, NodeList & nodelist) {
    
    //Before doing any printing check if the resistor already exists
    if (nodelist.checkIfRExistsAlready(resistor_name) == false){
        cout << "Error: resistor " << resistor_name << " not found" << endl;
        return;
    }
    cout << "Print: "<< endl;
    nodelist.findRandPrint(resistor_name);
    return;
}


void modifyRes(string Tempname, double resistorVal, NodeList & nodelist) {

    if(nodelist.checkIfRExistsAlready(Tempname) == false){
      cout << "Error: resistor " << Tempname << " not found" << endl;
      return;
    }
   //node exists so now we can modify it
   nodelist.findRandModify(Tempname, resistorVal);
     
}


void printNAll(NodeList & nodelist) {
    cout << "Print:" << endl;
    //node is the index  of the nodeArray

    nodelist.printAllNodes();
       
    return;
}


void printN(int node, NodeList & nodelist) {
    cout << "Print:" << endl;
    
    nodelist.printNode(node);
    
}

void setV(stringstream & resistorstream, int nodeid, double voltage, NodeList & nodelist){
    resistorstream >> nodeid;
    resistorstream >> voltage;
    
    nodelist.setNodeVoltage(nodeid, voltage);
}

void unsetV(stringstream & resistorstream, int nodeid, NodeList & nodelist){
     resistorstream >> nodeid;   
    
     nodelist.unsetNodeVoltage(nodeid);
}

void solveVoltages(NodeList & nodelist){
    //condition below means that no nodes have set voltage
    if (nodelist.checkForSetVoltage() == false){
        cout << "Error: no nodes have their voltage set" << endl;
        return;
    }
    else {
       //first solve then print the voltages of all of the nodes
        nodelist.solveNodeVoltages();
        nodelist.printUpdatedNodes();

}
    return;
}
