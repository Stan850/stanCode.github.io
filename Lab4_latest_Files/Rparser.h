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
#include "NodeList.h"

bool checkInsertInput(stringstream &resistorstream, double &resistorVal, int &nodeid, int &nodeid1, string &resistor_name, NodeList & nodelist);
bool checkModifyRInput(stringstream &resistorstream, double & resistorVal, NodeList & nodelist, string Tempname);
void printR(stringstream & resistorstream, string & resistor_name, NodeList & nodelist);
bool checkForFailandEOF(stringstream &resistorstream);
bool checkResistorVal(stringstream &resistorstream, double &resistorVal);
bool checkNodeId(stringstream &resistorstream);
bool checkForTooManyArg(stringstream &resistorstream);
void printNode(stringstream & resistorstream, string & resistor_name, int & nodeid, NodeList & nodelist);
void ignoreWhitespaceAtTheEnd(stringstream & resistorstream);
void deleteR(stringstream & resistorstream, string & resistor_name, NodeList & nodelist);
void setV(stringstream & resistorstream, int nodeid, double voltage, NodeList & nodelist);
void unsetV(stringstream & resistorstream, int nodeid, NodeList & nodelist);
void solveVoltages(NodeList & nodelist);
bool checkToInsertRintoResAr(stringstream &resistorstream, double &resistorVal, int &nodeid, int &nodeid1, string resistor_name, NodeList & nodelist);
bool insertRintoRresAr(double resistorVal, int nodeid, int nodeid1, string resistor_name, NodeList & nodelist);
void printname(string resistor_name, NodeList & nodelist);
void printAll(int maxResistors);
void modifyRes(string Tempname, double resistorVal, NodeList & nodelist);
void printNAll(NodeList & nodelist);
void printN(int node, NodeList & nodelist);
Node* createNode(int nodeid, double resistorVal, string resistor_name, int nodepoints[2]);
bool createNecessaryNodes(NodeList & nodelist, int inputId, double resistorVal, string resistor_name, int nodepoints[2]);
int Rparser(NodeList & nodelist);


#endif /* RPARSER_H */
