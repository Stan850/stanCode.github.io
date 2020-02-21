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


TreeDB::TreeDB(){
   root = NULL;
   probesCount = 0;
      
}

TreeDB::~TreeDB(){
    probesCount = 0;
    root = NULL; 
}

bool TreeDB::insert(DBentry* newEntry){
    bool inserted = false;
    
    if(root == NULL){
       // in this case the tree is empty
       root = new TreeNode(newEntry);
       //we inserted properly, so return true
       return(true); 
    }
    else{
    inserted = tree_Insert(root, newEntry);
    return(inserted);
    }  
}


DBentry* TreeDB::find(string name){
    
    probesCount = 0;
    //reset probesCount before counting
    return(findEntry(root, name));
   
}

DBentry* TreeDB::findEntry(TreeNode* treeNode, string req_name){
    
    if(treeNode == NULL){
        cout << "Error: entry does not exist" << endl;
        return(NULL);
    }
    //if a recursive call is made (means we'll make a comparison) and we compare with the first entry, increment probesCount
    probesCount++; 
    if( (treeNode -> getEntry() -> getName() ) == req_name){
       //return the pointer to the entry when found       
        return (treeNode -> getEntry());
    }
    else if( (treeNode -> getEntry() -> getName()) >  req_name){
         //traverse to the left
        return(findEntry(treeNode -> getLeft(), req_name));
    }
    else if ( (treeNode -> getEntry() -> getName()) < req_name){
       //traverse to the right
        return(findEntry(treeNode -> getRight(), req_name));
    }
}



bool TreeDB::tree_Insert(TreeNode* treeNode, DBentry* newEntry){
    
    if( (newEntry -> getName()) ==  (treeNode -> getEntry() -> getName())  ){
        return(false);
    }
    
    if( (newEntry -> getName()) < (treeNode -> getEntry() -> getName()) ){
        if((treeNode -> getLeft()) == NULL){
            //insert once we reach the "smallest" entry in the left subtree of the appropriate node and it doesn't have a left child
          TreeNode* temp1 = new TreeNode(newEntry);
          treeNode -> setLeft(temp1);
          return(true);
        }
        else {
            //otherwise keep traversing to the left
            return (tree_Insert(treeNode -> getLeft(), newEntry));
        }      
        }
    else if( (newEntry -> getName()) > (treeNode -> getEntry() -> getName()) ) {
        if(treeNode -> getRight() == NULL){
            //insert once we reach the "largest" entry in the right subtree of the appropriate node and it doesn't have a right child
            TreeNode* temp2 = new TreeNode(newEntry);
            treeNode -> setRight(temp2);
            return(true);
        }
        else {
            //otherwise keep traversing to the right
          return (tree_Insert(treeNode -> getRight(), newEntry));
        }
        
    }       
}

void TreeDB::printAll(){
       
      PrintAllEntries(root);    
   }


void TreeDB::PrintAllEntries(TreeNode* treeNode){
    
    if(treeNode == NULL){
        return;
    }
    PrintAllEntries(treeNode -> getLeft());
    
  //  treeNode -> getEntry() -> printContent();
    cout << *(treeNode -> getEntry());
    PrintAllEntries(treeNode -> getRight());
    return;
    
}

void TreeDB::printProbes() const{
       
    cout << probesCount << endl;   
             
   }

void TreeDB::countActive () const{
    int numActive = 0;
    
    //call the recursive function, send the root so we can traverse the BST
    countRecrActive(root, numActive);
    cout << numActive << endl;
}

void TreeDB::countRecrActive(TreeNode* treeNode, int & numActive) const{
    //the traversing in this function is the same as in printall
    //traverse to the left until you reach no left child
    //return and print the entry contents
    //traverse to the right and repeat the same as above for the other nodes
    if(treeNode == NULL){
        return;
    }
    countRecrActive(treeNode -> getLeft(), numActive);
    if( (treeNode -> getEntry() -> getActive()) == true){
        numActive++;
    }
    countRecrActive(treeNode -> getRight(), numActive);
    return;   
}


void TreeDB::clear(){
    
    removeAll(root);
    root = NULL;    
}


void TreeDB::removeAll(TreeNode* treeNode){
    
    //if not met, it means we still have a left or right subtree
    if(treeNode == NULL){
        return;
    } 
    //first traverse through the left subtree until you hit NULL
    removeAll(treeNode -> getLeft());
    //then traverse through the right subtree until you hit NULL
    removeAll(treeNode -> getRight());
    //now delete the node knowing that its a leaf
    delete treeNode;
    treeNode = NULL;
}

DBentry* TreeDB::findMaxLeftSubRightName(TreeNode* treeNode){
    
    if(treeNode -> getRight() == NULL){
        return(treeNode -> getEntry());
    }
    return(findMaxLeftSubRightName(treeNode -> getRight()));  
}

bool TreeDB::remove(string name){
    DBentry* checkFind = find(name);
    if(checkFind == NULL){
        return(false);
    }   
    //this pointer will follow the treeNode pointer for deletion (like in linked lists)
    TreeNode* treefollow = root; 
    removeNode(root, treefollow, name);  
    return(true);
}


void TreeDB::removeNode(TreeNode* treeNode, TreeNode* treeTemp, string name){
    
    if((treeNode -> getEntry() -> getName()) > name ){
        treeTemp = treeNode;
        //keep searching to the left if name is less than name of the entry visited "treeNode actually"
        removeNode(treeNode -> getLeft(), treeTemp, name);
        return;
    } 

    else if ( (treeNode -> getEntry() -> getName()) < name){
        treeTemp = treeNode;
         //keep searching to the right if name is greater than name of the entry visited "treeNode actually"
        removeNode(treeNode -> getRight(), treeTemp, name);
        return;
    }
    else {
        //treeNode has no children
        if((treeNode -> getLeft() == NULL) && (treeNode -> getRight() == NULL)){ 
            //first check if we only have one node in the BST, we consider as a subcase for the other major cases n this function
            if(treeNode == root){ 
               delete root;
               root = NULL;
               return;
            }
            delete treeNode;
            if(treeTemp -> getRight() == treeNode){
                //purpose is to avoid dangling pointers
                treeTemp -> setRight(NULL); 
            }
            else{
                //purpose is to avoid dangling pointers
                treeTemp -> setLeft(NULL);

            }
            return;
        }
        //treeNode has only right child
        else if((treeNode -> getLeft() == NULL) && ( treeNode -> getRight() != NULL)){ 
            if(treeNode == root){
                root = root -> getRight();
                delete treeNode;
                return;
            }
            TreeNode* tempt = treeNode;
            //check if the right pointer of the node treeTemp points to is the treeNode pointer
            if(treeTemp -> getRight() == treeNode){ 
            treeTemp -> setRight(treeNode -> getRight());
            }
            //this means that the left pointer of the node treeTemp points to is the treeNode pointer
            else { 
                treeTemp -> setLeft(treeNode -> getRight());
            }
            delete tempt;
            return;
        }
        //treeNode has only left child
        else if((treeNode -> getLeft() != NULL) && (treeNode -> getRight() == NULL)){ 
            if(treeNode == root){
                root = root -> getLeft();
                delete treeNode;
                return;
            }
            TreeNode* tempt = treeNode;
            if(treeTemp -> getRight() == treeNode){
                //set the right pointer of the parent to point to the left child of the node to be deleted 
                treeTemp -> setRight(treeNode -> getLeft());
            }
            else {
            //set the left pointer of the parent to point to the left child of the node to be deleted 
            treeTemp -> setLeft(treeNode -> getLeft());
            }
            delete tempt;
            return;
        }
        else { //we reach the case where the node has both children
         
            DBentry* maxPtr = findMaxLeftSubRightName(treeNode-> getLeft());
            //overwrite the contents of the node to be "deleted" with the contents from the max node that we actually will delete
            treeNode -> getEntry() -> setName(maxPtr -> getName());
            treeNode -> getEntry() -> setIPaddress(maxPtr -> getIPaddress());
            treeNode -> getEntry() -> setActive(maxPtr -> getActive());
            treeTemp = treeNode;
            removeNode(treeNode -> getLeft(), treeTemp, (treeNode -> getEntry() -> getName()));
        }
         
    
}
    return;
}
