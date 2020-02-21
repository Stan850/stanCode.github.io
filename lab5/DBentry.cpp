/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */


#include <iostream>
#include <cstdlib>
#include <string>
#include "TreeNode.h"
#include "TreeDB.h"
#include "DBentry.h"




DBentry::DBentry(){
    
    
}

DBentry::DBentry(string _name, unsigned int _IPaddress, bool _active){
    
  name = _name;
  IPaddress = _IPaddress;
  active = _active;
  
}

DBentry::~DBentry(){
    
//define once you get to remove/delete etc.
    
}

void DBentry::setName(string _name) {

    name = _name;
}

void DBentry::setIPaddress(unsigned int _IPaddress) {

    IPaddress = _IPaddress;
}

void DBentry::setActive(bool _active) {
    
    active = _active;
}

string DBentry::getName() const {

    return(name);

}

unsigned int DBentry::getIPaddress() const{
    
    return(IPaddress);
}

 bool DBentry::getActive() const{
     
     return(active);
 }
 
 //I don't use this function, was only used to debug my code
 void DBentry::printContent(){
     
      string tempActive;
     if(active == true){
         tempActive = "active";
     }
     else {
         tempActive = "inactive";
     }
     cout << name << " : " << IPaddress << " : " << tempActive << endl; //the operator function will print contents of the objects thats sent to it
                                                                                       //it isn't invoked on a function
     
     
 }
 
 
 ostream&  operator<<(ostream& os, const DBentry& rhs){
     string tempActive;
  
     if(rhs.active == true){
         tempActive = "active";
     }
     else {
         tempActive = "inactive";
     }
     os << rhs.name << " : " << rhs.IPaddress << " : " << tempActive << endl; //the operator function will print contents of the objects thats sent to it
                                                                                       //it isn't invoked on a function
     
 }
 
 
 

