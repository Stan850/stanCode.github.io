/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
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

using namespace std;
/* Node* nodeArray;
 Resistor** ResistorArray;*/
Node* nodeArray = NULL;
Resistor** ResistorArray = NULL;




//functions below checks if all arguments are valid following the appropriate command by calling 
//other functions that individually check for errors
//note if resistor_name is not a parameter, it is checked in main
//resistorstream.clear() will only clear flags
//resistorstream.str("") will clear the stream

/*
 * 
 */
int Rparser() {

    string line;
    string command;
    string resistor_name;
    double resistorVal;
    int nodeid;
    int nodeid1;



    int maxResistors = 0;
    int maxNodeNumber = 0;
    int rescount = 0; 
    //used to keep track of the next available index in 
    //the resistor array


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
            } else if (checkInsertInput(resistorstream, resistorVal, nodeid, nodeid1, resistor_name, maxResistors, maxNodeNumber, rescount) == true) {
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
            } else if (checkModifyRInput(resistorstream, resistorVal, maxResistors, resistor_name) == true) {

            }
            resistor_name = ""; //again clear it for the same reason above (also to be safe)

        } else if (command == "printR") {

            printR(resistorstream, resistor_name, maxResistors);
            resistor_name = "";

        } else if (command == "printNode") {
            //printNode will decide what to output based on the input
            printNode(resistorstream, resistor_name, nodeid, maxNodeNumber);

        } else if (command == "deleteR") {
            deleteR(resistorstream, resistor_name, rescount, maxResistors, maxNodeNumber);
            resistor_name = "";
        } else if (command == "maxVal") {
            setMaxVals(resistorstream, maxNodeNumber, maxResistors, rescount);
        } else {
            cout << "Error: invalid command\n";
            resistorstream.clear();
            resistorstream.str("");
        }
        command = "";
        cout << "> ";
        getline(cin, line);
    }
    //delete everything before program ends
    deleteArrays(rescount, maxResistors, maxNodeNumber);
    delete []ResistorArray;
    ResistorArray = NULL;
    delete []nodeArray;
    nodeArray = NULL;

    return 0;
}

bool checkInsertInput(stringstream &resistorstream, double &resistorVal, int &nodeid, int &nodeid1, string &resistor_name, int maxResistors, int maxNodeNumber, int &rescount) {

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
    if (checkNodeId(resistorstream, nodeid, maxNodeNumber) == false) {
        return (false);
    }
    if (checkForFailandEOF(resistorstream) == true) {
        return (false);
    }
    resistorstream >> nodeid1;
    if (checkNodeId(resistorstream, nodeid1, maxNodeNumber) == false) {
        return (false);
    }

    //ignore white spaces so EOF can be checked for too many args 
    ignoreWhitespaceAtTheEnd(resistorstream);
    //false here means an EOF has not been read, there are more characters in the stream
    if (checkForTooManyArg(resistorstream) == false) {
        return (false);
    }

    if (checkToInsertRintoResAr(resistorstream, resistorVal, nodeid, nodeid1, resistor_name, maxResistors, maxNodeNumber, rescount) == false) {
        return (false); //means that there is no space to add or same name 
    }

    if (nodeid == nodeid1) {
        cout << "Error: both terminals of resistor connect to node " << nodeid << endl;
        resistorstream.clear();
        resistorstream.str("");
        return (false);
    }
    insertRintoRresAr(resistorVal, nodeid, nodeid1, resistor_name, rescount);
    return (true);
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

bool checkNodeId(stringstream &resistorstream, int &nodeid, int maxNodeNumber) {

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
    if (nodeid < 0 || nodeid > maxNodeNumber) {
        cout << "Error: node " << nodeid << " is out of permitted range 0-" << maxNodeNumber << endl;
        resistorstream.clear();
        resistorstream.str("");
        return (false);
    } else return (true);
}

bool checkModifyRInput(stringstream &resistorstream, double & resistorVal, int maxResistors, string Tempname) {

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
        modifyRes(Tempname, resistorVal, maxResistors);
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

void printR(stringstream & resistorstream, string & resistor_name, int maxResistors) {

    resistorstream >> resistor_name;
    if (checkForFailandEOF(resistorstream) == true) {
        return;
    }
    ignoreWhitespaceAtTheEnd(resistorstream);
    if (checkForTooManyArg(resistorstream) == false) {
        return;
    } else if (resistor_name == "all") {
        printAll(maxResistors);
    } else {
        printname(resistor_name, maxResistors);
    }
    return;
}

void printNode(stringstream & resistorstream, string & resistor_name, int & nodeid, int maxNodeNumber) {

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
                printNAll(maxNodeNumber);
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
    } else if (checkNodeId(resistorstream, nodeid, maxNodeNumber) == true) {
        ignoreWhitespaceAtTheEnd(resistorstream);
        if (checkForTooManyArg(resistorstream) == true) {
            printN(nodeid);
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

void deleteR(stringstream & resistorstream, string & resistor_name, int &rescount, int maxResistors, int maxNodeNumber) {

    //this function behaves similarly to printR
    resistorstream >> resistor_name;
    if (checkForFailandEOF(resistorstream) == true) {
        return;
    }
    ignoreWhitespaceAtTheEnd(resistorstream);
    if (checkForTooManyArg(resistorstream) == false) {
        return;
    } else if (resistor_name == "all") {
        deleteArrays(rescount, maxResistors, maxNodeNumber);
        cout << "Deleted: all resistors" << endl;
    } else {
        cout << "Deleted: resistor " << resistor_name << endl;
    }
    return;
}

void setMaxVals(stringstream & resistorstream, int &maxNodeNumber, int &maxResistors, int &rescount) {

    if (ResistorArray != NULL || nodeArray != NULL) {
        //need to check if they point to nothing otherwise seg fault would occur when trying to delete
        deleteArrays(rescount, maxResistors, maxNodeNumber);
        //empty any preallocated arrays
        delete []ResistorArray;
        ResistorArray = NULL;
        delete []nodeArray;
        //prevents memory leak
        nodeArray = NULL;
        //set both pointers (that pointed to the arrays) to NULL
    }

    resistorstream >> maxNodeNumber;
    resistorstream >> maxResistors;

    if ((maxNodeNumber < 0) || (maxNodeNumber == 0)) {
        cout << "Error: maxVal arguments must be greater than 0" << endl;
        resistorstream.str("");
        return;
    } else if ((maxResistors < 0) || (maxResistors == 0)) {
        cout << "Error: maxVal arguments must be greater than 0" << endl;
        resistorstream.str("");
        return;
    } else {
        cout << "New network: max node number is " << maxNodeNumber << "; max resistors is " << maxResistors << endl;
        nodeArray = new Node[maxNodeNumber + 1];
        ResistorArray = new Resistor*[maxResistors];
        for (int r = 0; r < maxResistors; r++) {
            //r refers to the index of the resistor array
            ResistorArray[r] = NULL;
            //initialize all pointers to NULL, later one will point to a dynamically created object
        }
    }
}

bool checkToInsertRintoResAr(stringstream &resistorstream, double &resistorVal, int &nodeid, int &nodeid1, string resistor_name, int &maxResistors, int &maxNodeNumber, int &rescount) {

    bool availablespace = false;
    string TempName = resistor_name;
    // i keeps track of index of ResistorArray
    for (int i = 0; i < maxResistors; i++) {
        if (ResistorArray[i] == NULL) {
            availablespace = true;
        }
    }
    if (availablespace == false) {
        cout << "Error: resistor array is full" << endl;
        return (false);
    }

    if (checkForSpaceinNodeAr(nodeid, nodeid1, rescount) == false) {
        return (false);
    }
    // k keeps track of index of ResistorArray  this time used to retrieve resistor names from objects
    for (int k = 0; k < maxResistors; k++) {

        if (ResistorArray[k] != NULL) {
            if (ResistorArray[k]->getName() == TempName) {
                cout << "Error: resistor " << ResistorArray[k]->getName() << " already exists" << endl;
                return (false);
            }
        }

    }
    return (true);
    //means all that we are now ready to insert the resistor

}

bool checkForSpaceinNodeAr(int &nodeid, int &nodeid1, int rescount) {
    bool node1avail = false;
    bool node2avail = false;

    node1avail = nodeArray[nodeid].canAddResistor(rescount);
    node2avail = nodeArray[nodeid].canAddResistor(rescount);
    if ((node1avail == false) || (node2avail == false)) {
        //had to check if either node was full
        cout << "Error: node is full" << endl;
    } else {
        return true;
    }
}

void insertRintoRresAr(double resistorVal, int nodeid, int nodeid1, string resistor_name, int &rescount) {
    //creates a local/temp array only to send information to addResistor member function
    int nodepoints[2] = {nodeid, nodeid1};

    ResistorArray[rescount] = new Resistor(rescount, resistor_name, resistorVal, nodepoints);
    //access the nodeArray at the user requested nodes (a.k.a the indices) and invoke addResistor on the objects at those indices
    nodeArray[nodeid].addResistor(rescount);
    nodeArray[nodeid1].addResistor(rescount);
    //increment number of resistors added by 1
    rescount++;
    return;
}

void printname(string resistor_name, int maxResistors) {

    bool found = false;
    // j keeps track of index of ResistorArray
    for (int j = 0; j < maxResistors; j++) {

        if (ResistorArray[j] != NULL) {
            if (ResistorArray[j]->getName() == resistor_name) {
                found = true;
                cout << "Print:" << endl;
                ResistorArray[j]->print();
            }
        }
    }
    if (found == false) {
        cout << "Error: resistor " << resistor_name << " not found" << endl;
    }
    return;
}

void printAll(int maxResistors) {
    cout << "Print:" << endl;
     // i keeps track of index of ResistorArray
    for (int i = 0; i < maxResistors; i++) {

        if (ResistorArray[i] != NULL) {
            //invoke print member function on object pointed to by ResistorArray[i]
            ResistorArray[i]->print();
        }
    }
}

void modifyRes(string Tempname, double resistorVal, int maxResistors) {

    double oldResVal = 0.0;
    //used to temporarily store the old resistance value
    bool found = false;


    for (int i = 0; i < maxResistors; i++) {
        if (ResistorArray[i] != NULL) {
            if (ResistorArray[i]->getName() == Tempname) { 
                //means we found the object that has the same name 
                //retrieve old value first
                oldResVal = ResistorArray[i]->getResistance();
                ResistorArray[i]->setResistance(resistorVal);
                cout << "Modified: resistor " << Tempname << " from " << setprecision(2)
                        << fixed << oldResVal << " Ohms " << "to " << setprecision(2)
                        << fixed << ResistorArray[i]->getResistance() << " Ohms" << endl;
                found = true;
                return;
            }
        }
    }
    if (found == false) {
        cout << "Error: resistor " << Tempname << " not found" << endl;
    }
    return;
}

void printNAll(int maxNodeNumber) {
    cout << "Print:" << endl;
    //node is the index  of the nodeArray
    for (int node = 0; node < (maxNodeNumber + 1); node++) {
        nodeArray[node].printInfoFromIndices(node);
    }
    return;
}

void printN(int node) {
    cout << "Print:" << endl;
    nodeArray[node].printInfoFromIndices(node);

}

void deleteArrays(int &rescount, int maxResistors, int maxNodeNumber) {
    for (int i = 0; i < maxResistors; i++) {
        if (ResistorArray[i] != NULL) {
            //delete all the objects
            delete ResistorArray[i];
            //set the pointers inside to NULL
            ResistorArray[i] = NULL;
        }
    }
    //reset the number of resistors stored in resistorArray to 0
    rescount = 0; 
    //go down the nodeArray and reset the numres value and resID arrays
    for (int j = 0; j < (maxNodeNumber + 1); j++) {
        nodeArray[j].resetNodeObjects();

    }
}