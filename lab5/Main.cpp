/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: oparnica
 *
 * Created on November 19, 2017, 9:27 PM
 */

#include<iostream>
#include<sstream>
#include<string>
#include<iomanip>
#include<cstdlib>
#include "TreeNode.h"
#include "TreeDB.h"
#include "DBentry.h"

using namespace std;

void insertNewEntry(stringstream & datastream, string name, unsigned int IPaddress, string activeflag, TreeDB* & treepoint);
void findTheName(stringstream & datastream, string name, TreeDB* & treepoint);
void printAllEntries(TreeDB* & treepoint);
void printprobes(stringstream & datastream, string name, TreeDB* & treepoint);
void updatestatus(stringstream & datastream, string name, string status, TreeDB* & treepoint);
void countActive(TreeDB* & treepoint);
void clearAll(TreeDB* & treepoint);
void removeANode(stringstream & datastream, string name, TreeDB* & treepoint);




//datastream.clear() will only clear flags
//datastream.str("") will clear the stream

/*
 * 
 */
int main() {

    string line;
    string command;
    string name; //this is the key
    string status;
    unsigned int IPaddress;
    string activeflag;

    TreeDB* treepoint = new TreeDB();



    cout << "> ";
    getline(cin, line);

    while (!cin.eof()) {

        stringstream datastream(line);

        datastream >> command;


        if (command == "insert") {

            insertNewEntry(datastream, name, IPaddress, activeflag, treepoint);

        } else if (command == "find") {

            findTheName(datastream, name, treepoint);

        } else if (command == "printall") {

            printAllEntries(treepoint);

        } else if (command == "printprobes") {

            printprobes(datastream, name, treepoint);

        } else if (command == "removeall") {

            clearAll(treepoint);

        } else if (command == "updatestatus") {

          updatestatus(datastream, name, status, treepoint);
          
        } else if (command == "countactive") {
            
            countActive(treepoint);

        } else if (command == "remove") {

          removeANode(datastream, name, treepoint);
            
        } else {
            cout << "Error: invalid command\n";
            datastream.clear();
            datastream.str("");
        }
        command = "";
        cout << "> ";
        getline(cin, line);
    }
    //empty the binary tree to avoid memory leaks
    treepoint -> clear();
    delete treepoint;
    return 0;
}

//define any additional functions for parsing here

void insertNewEntry(stringstream & datastream, string name, unsigned int IPaddress, string activeflag, TreeDB* & treepoint) {
    bool active;

    datastream >> name;
    datastream >> IPaddress;
    datastream >> activeflag;

    if (activeflag == "active") {
        active = true;
    } else {
        active = false;
    }
    //creates the new entry
    DBentry* newEntry = new DBentry(name, IPaddress, active);
    if (treepoint -> insert(newEntry) == false) {
        //if insert returns false then, entry already exists
        cout << "Error: entry already exists" << endl;
        delete newEntry;
    } else {
        cout << "Success" << endl;
    }

}

void findTheName(stringstream & datastream, string name, TreeDB* & treepoint) {

    datastream >> name;
    DBentry* tempoint = treepoint -> find(name);

    if (tempoint == NULL) {
        return;
        
    } else {
        //the node exists so we can print it
        //tempoint -> printContent();
        cout << *(tempoint);
    }
    return;
}

void printAllEntries(TreeDB* & treepoint) {
    
    //printAll will check if we have an empty binary tree
    treepoint -> printAll();

}

void printprobes(stringstream & datastream, string name, TreeDB* & treepoint){
    
    datastream >> name;
    DBentry* tempt = treepoint -> find(name);
    
    //make sure the entry still exists
    if (tempt == NULL) {
        return;
    }
    else {
        treepoint -> printProbes();
    }
    return;
}

void updatestatus(stringstream & datastream, string name, string status, TreeDB* & treepoint){
    bool active = false; //set to false just for initialization purposes
    
    datastream >> name;
    datastream >> status;
    
    //invoke the following function to check if the entry containing "name" exists
    DBentry* tempt = treepoint -> find(name);
    
    if(tempt == NULL){
        return;
    }
    else {
        //convert bools into proper strings
        if(status == "active"){
            active = true;
        }
        else {
            active = false;
        }
        tempt -> setActive(active);
        cout << "Success" << endl;
    }
    
}

void countActive(TreeDB* & treepoint){
    
    treepoint -> countActive();   
}
    
void clearAll(TreeDB* & treepoint){
    
    treepoint -> clear();
    cout << "Success" << endl;
    
}   

void removeANode(stringstream & datastream, string name, TreeDB* & treepoint){
    
    datastream >> name;
    
    if(treepoint -> remove(name) == false){
      //remove returns false if entry does not exist
      return;
}
    else{
        cout << "Success" << endl;
        return;
    }
}