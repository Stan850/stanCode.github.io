/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   NodeList.h
 * Author: oparnica
 *
 * Created on November 6, 2017, 11:03 PM
 */

#ifndef NODELIST_H
#define NODELIST_H
#define MIN_ITERATION_CHANGE 0.0001


class NodeList
{
private:
    Node* head = NULL;
    int lowID = 0;
    int maxID = 0;
    
public:
    NodeList();
    ~NodeList();
    
   bool checkifNodeExists(int nodeid);
   void insertAtMiddle(Node* nodepoint);
   void insertAtHead(Node* nodepoint);
   void insertAtTail(Node* nodepoint);
   bool checkIfRExistsAlready(string resistorname); 
   void findRandPrint(string resistorname);
   void printNode(int nodeid);
   void printAllNodes();
   void findRandModify(string resistorname, double resistorVal);
   void setNodeVoltage(int inputID, double newVoltage);
   void deleteRes(string resistorname);
   void deleteRall();
   void deleteAllNodes();
   void unsetNodeVoltage(int inputID);
   bool checkForSetVoltage();
   void solveNodeVoltages();
   double getNodeVoltage(int oppID);
   double calculateRightPart(int nodeid, ResistorList* head);
   void printUpdatedNodes();
   
   
   bool checktoSeeIfNodesExist(int nodeid);
   void findNodeAndInsert(int targetID, string resistor_name, double resistorVal, int endpoints_[2]);
   
   Node* getHead();
    
};

#endif /* NODELIST_H */

