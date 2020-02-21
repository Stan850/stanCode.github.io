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
#include <cstdlib>

#define MAX_NODE_NUMBER 5000 




using namespace std;

//functions below checks if all arguments are valid following the appropriate command by calling 
//other functions that individually check for errors
//note if resistor_name is not a parameter, it is checked in main
//resistorstream.clear() will only clear flags
//resistorstream.str("") will clear the stream
bool checkInsertInput(stringstream &resistorstream, double &resistorVal, int &nodeid, int &nodeid1);
bool checkModifyRInput(stringstream &resistorstream, double & resistorVal);
void printR(stringstream & resistorstream, string & resistor_name);
bool checkForFailandEOF(stringstream &resistorstream);
bool checkResistorVal(stringstream &resistorstream, double &resistorVal);
bool checkNodeId(stringstream &resistorstream, int &nodeid);
bool checkForTooManyArg(stringstream &resistorstream);
void printNode(stringstream & resistorstream, string & resistor_name, int & nodeid);
void ignoreWhitespaceAtTheEnd(stringstream & resistorstream);
void deleteR(stringstream & resistorstream, string & resistor_name);

/*
 * 
 */
int main(int argc, char** argv) {

    string line;
    string command;
    string resistor_name;
    double resistorVal;
    int nodeid;
    int nodeid1;

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
            } else if (checkInsertInput(resistorstream, resistorVal, nodeid, nodeid1) == true) {
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
            } else if (checkModifyRInput(resistorstream, resistorVal) == true) {
                //true means the input is valid
                cout << "Modified: resistor " << resistor_name << " to " << setprecision(2)
                        << fixed << resistorVal << " Ohms" << endl;
            }
            resistor_name = ""; //again clear it for the same reason above (also to be safe)
            
        } else if (command == "printR") {

            printR(resistorstream, resistor_name);
            resistor_name = "";

        } else if (command == "printNode") {
            //printNode will decide what to output based on the input
            printNode(resistorstream, resistor_name, nodeid);

        } else if (command == "deleteR") {
            deleteR(resistorstream, resistor_name);
            resistor_name = "";
        } else {
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

bool checkInsertInput(stringstream &resistorstream, double &resistorVal, int &nodeid, int &nodeid1) {

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
    if (checkNodeId(resistorstream, nodeid) == false) {
        return (false);
    }
    if (checkForFailandEOF(resistorstream) == true) {
        return (false);
    }
    resistorstream >> nodeid1;
    if (checkNodeId(resistorstream, nodeid1) == false) {
        return (false);
    }

    if (nodeid == nodeid1) {
        cout << "Error: both terminals of resistor connect to node " << nodeid << endl;
        resistorstream.clear();
        resistorstream.str("");
        return (false);
    }
    //ignore white spaces so EOF can be checked for too many args 
    ignoreWhitespaceAtTheEnd(resistorstream);
    //false here means an EOF has not been read, there are more characters in the stream
    if (checkForTooManyArg(resistorstream) == false) { 
        return (false);
    }
    
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

bool checkNodeId(stringstream &resistorstream, int &nodeid) {
    
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
    if (nodeid < 0 || nodeid > MAX_NODE_NUMBER) {
        cout << "Error: node " << nodeid << " is out of permitted range 0-5000\n";
        resistorstream.clear();
        resistorstream.str("");
        return (false);
    } else return (true);
}

bool checkModifyRInput(stringstream &resistorstream, double & resistorVal) {

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
    } else return (true);
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

void printR(stringstream & resistorstream, string & resistor_name) {

    resistorstream >> resistor_name;
    if (checkForFailandEOF(resistorstream) == true) {
        return;
    }
    ignoreWhitespaceAtTheEnd(resistorstream);
    if (checkForTooManyArg(resistorstream) == false) {
        return;
    } else if (resistor_name == "all") {
        cout << "Print: all resistors \n";
    } else {
        cout << "Print: resistor " << resistor_name << endl;
    }
    return;
}

void printNode(stringstream & resistorstream, string & resistor_name, int & nodeid) {
    
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
                cout << "Print: all nodes \n";
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
    } else if (checkNodeId(resistorstream, nodeid) == true) {
        ignoreWhitespaceAtTheEnd(resistorstream);
        if (checkForTooManyArg(resistorstream) == true) {
            cout << "Print: node " << nodeid << endl;
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

void deleteR(stringstream & resistorstream, string & resistor_name) {
    
    //this function behaves similarly to printR
    resistorstream >> resistor_name;
    if (checkForFailandEOF(resistorstream) == true) {
        return;
    }
    ignoreWhitespaceAtTheEnd(resistorstream);
    if (checkForTooManyArg(resistorstream) == false) {
        return;
    } else if (resistor_name == "all") {
        cout << "Deleted: all resistors \n";
    } else {
        cout << "Deleted: resistor " << resistor_name << endl;
    }
    return;
}
