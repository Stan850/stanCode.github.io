/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Rparser.h
 * Author: oparnica
 *
 * Created on October 10, 2017, 2:19 PM
 */

#ifndef RPARSER_H
#define RPARSER_H

#include<iostream>
#include<sstream>
#include<string>
#include<iomanip>
#include<cstdlib>
#include "Node.h"
#include "Resistor.h"

bool checkInsertInput(stringstream &resistorstream, double &resistorVal, int &nodeid, int &nodeid1, string &resistor_name, int maxResistors, int maxNodeNumber, int &rescount);
bool checkModifyRInput(stringstream &resistorstream, double & resistorVal, int maxResistors, string Tempname);
void printR(stringstream & resistorstream, string & resistor_name, int maxResistors);
bool checkForFailandEOF(stringstream &resistorstream);
bool checkResistorVal(stringstream &resistorstream, double &resistorVal);
bool checkNodeId(stringstream &resistorstream, int &nodeid, int maxNodeNumber);
bool checkForTooManyArg(stringstream &resistorstream);
void printNode(stringstream & resistorstream, string & resistor_name, int & nodeid, int maxNumberNode);
void ignoreWhitespaceAtTheEnd(stringstream & resistorstream);
void deleteR(stringstream & resistorstream, string & resistor_name, int &rescount, int maxResistors, int maxNodeNumber);
void setMaxVals(stringstream & resistorstream, int &maxNodeNumber, int &maxResistors, int &rescount);
bool checkToInsertRintoResAr(stringstream &resistorstream, double &resistorVal, int &nodeid, int &nodeid1, string resistor_name, int &maxResistors, int &maxNodeNumber, int &rescount);
bool checkForSpaceinNodeAr(int &nodeid, int &nodeid1, int rescount);
void insertRintoRresAr(double resistorVal, int nodeid, int nodeid1, string resistor_name, int &rescount);
void printname(string resistor_name, int maxResistors);
void printAll(int maxResistors);
void modifyRes(string Tempname, double resistorVal, int maxResistors);
void printNAll(int maxNodeNumber);
void printN(int node);
void deleteArrays(int &rescount, int numResistors, int maxNodeNumber);
int Rparser();


#endif /* RPARSER_H */

