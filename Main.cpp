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


//functions below checks if all arguments are valid following the appropriate command by calling 
//other functions that individually check for errors
//note if resistor_name is not a parameter, it is checked in main

//resistorstream.clear() will only clear flags
//resistorstream.str("") will clear the stream

/*
 * 
 */
int main(int argc, char** argv) {

    
    NodeList* nodelist = new NodeList();
    Rparser(*nodelist);
    
    //completed in order to prevent memory leaks
    nodelist -> deleteAllNodes();
    delete nodelist;
    nodelist = NULL;
    
    
    
    return(0);
}

