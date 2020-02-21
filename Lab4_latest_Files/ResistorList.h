/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ResistorList.h
 * Author: oparnica
 *
 * Created on November 6, 2017, 11:02 PM
 */

#ifndef RESISTORLIST_H
#define RESISTORLIST_H

#include <string>
#include <iostream>
#include "Resistor.h"



class ResistorList{
    
private:
    Resistor* resistorhead = NULL;
    int numRes = 0;
    
    
    
public:
   
    ResistorList();
    ~ResistorList();
    
    //all comments about the functions are in their respective cpp files
    void insertR(string resistor_name, double resistorVal, int nodepoints[2]);
    void checkForR(string resistorname, int & rescount);
    bool printResInfo(string resistorname);
    void printNode(int nodeid);
    void modifyRes(string resistorname, double resistorVal, int & numTimesModified);
    void deleteSelectedRes(string resistorname, int & numTimesDeleted);
    void deleteAll();
    double calculateleftpart();
    Resistor* getHead();
   

};

#endif /* RESISTORLIST_H */

