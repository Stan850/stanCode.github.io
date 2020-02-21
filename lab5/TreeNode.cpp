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

TreeNode::TreeNode(DBentry* _entryPtr){
    
    left = NULL;
    entryPtr = _entryPtr;
    right = NULL;
    
}

TreeNode::~TreeNode(){
    left = NULL;
    delete entryPtr;
    right = NULL;  
}


 void TreeNode::setLeft(TreeNode* newLeft){
     
     left = newLeft;
 }
 
 void TreeNode::setRight(TreeNode* newRight){
     
     right = newRight;    
 }
 
TreeNode* TreeNode::getLeft() const{
    
    return(left);
}

TreeNode* TreeNode::getRight() const{
    
    return(right);
}

 DBentry* TreeNode::getEntry() const{
     
     return(entryPtr);
 }