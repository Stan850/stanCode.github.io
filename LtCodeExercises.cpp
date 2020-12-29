#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>
struct Pairs{
    char key;
    char pair;
};

struct TreeNode{
   int value;
   TreeNode* sibling;
   TreeNode* firstChild;
};

struct dataPoints{
    int value = 0;
    int count = 0;
};

struct Node{
    int value;
    Node* firstChild;
    Node* secondChild;
};
///EXAMPLE ONE: PAST QUESTIONS

char findPair(Pairs* array[], char letter){
    int i = 0;
    while(array[i]->key != letter && i <= sizeof(*array)/sizeof(*array[0])){
       i++;
    }
    return array[i]->pair;
}
bool isIsomorphic(const char* a, const char* b){
    if (strlen(a) != strlen(b)) return false;
    //create an array of structs, each struct has a pair of two letters
    Pairs* isomorphic[strlen(a)];
    for (int i=0; i<= strlen(a); i++){
         isomorphic[i] = new Pairs;
         isomorphic[i]->key = a[i];
         isomorphic[i]->pair = b[i];
    }
    for (int i=0; i<= strlen(a); i++){
        char pairFound = b[i];
        char pairStored = findPair(isomorphic, a[i]);
        if (pairFound != pairStored) return false;
    }

    for (int i = 0; i<=sizeof(*isomorphic)/sizeof(*isomorphic[0]); i++){
        delete isomorphic[i];
        isomorphic[i] = NULL;

    }
    return true;
}

///EXAMPLE TWO: PAST QUESTIONS

void treeTraverse(TreeNode* point){
    std::cout << point->value << std::endl;
    if (point -> firstChild == NULL && point -> sibling == NULL) return;
    else{
        if (point -> firstChild == NULL) treeTraverse(point->sibling);
        else treeTraverse(point->firstChild);
    }
    return;
}


TreeNode* generateTree(int m, int* a){
    TreeNode* first = new TreeNode;
    TreeNode* second;
    TreeNode* head = first;
    int i = 0;
    while (i < m) {
        if (i == (m - 1)) {
            first->value = a[i];
            first->firstChild = NULL;
            first->sibling = NULL;
            i++;
        } else {
            second = new TreeNode;
            if (a[i] % 2 != 0) { // means it is an odd number
                first->value = a[i];
                first->firstChild = second;
                first->sibling = NULL;
            } else {
                first->value = a[i];
                first->firstChild = NULL;
                first->sibling = second;
            }
            first = second;
            i++;
        }
    }
    treeTraverse(head);
    return(head);
}

/// EXAMPLE THREE : PAST QUESTIONS
bool findNum(dataPoints* a[], int num, int size){
  for (int i = 0; i < size; i++){
      if (a[i] == NULL) return false;
      else if (a[i] -> value == num) {
          a[i] -> count = (a[i] -> count)+1;
          return true;
      }
  }
  return false;
}

int gcf(int a, int b)
{
    if (a == 0)
        return b;
    return gcf(b % a, a);
}

int* factors(int num, int fact1){
    int facts[100] = {};
    int j = 0;
    for (int i = fact1; i <= num; i++){
        if (num % i == 0) {
            facts[j] = i;
            j++;
        }
    }
    int* test = facts;
    return test;

}

int finalizePeriod(int* a, int estPeriod, int size) {
    if (estPeriod == size) return size;
    int* facts = factors(size, estPeriod);
    int j = 0;
    for (int i = 0; ((i+estPeriod) < size && facts[j] != 0); i++) {
        if (a[i] != a[i+estPeriod]){
            i = 0;
            j++;
            estPeriod = facts[j];
        }
        if (estPeriod == size) return size;
    }
    return estPeriod;
    }


int MinPeriod(int*a, int n){
    dataPoints* arrayOfNum[1000] = {};
    int store = 0;
    for (int i=0; i<n; i++) {
        if (findNum(arrayOfNum, a[i], n) == 0) {
            arrayOfNum[store] = new dataPoints;
            arrayOfNum[store]->value = a[i];
            arrayOfNum[store]->count = 1;
            store++;
        }
    }
    int predictedCycles = arrayOfNum[0] -> count;
    for (int i=1; arrayOfNum[i] != NULL; i++){
        predictedCycles = gcf(predictedCycles, arrayOfNum[i]-> count);
    }
    return (finalizePeriod(a, n/predictedCycles, n));
}

////ACTUAL TEST!!!!!




int main() {
    //bool isTrue = isIsomorphic("brbin", "apace");
    //std::cout << isTrue;
    //int test[9] = {7,2,4,18,6,9,3,7,18};
    //TreeNode* root = generateTree(9, test);
    //int test[30] = {1,2,3,3,2,1,1,2,3,3,2,1,1,2,3,1,2,3,3,2,1,1,2,3,3,2,1,1,2,3};
    //int period = MinPeriod(test, 30);
    //std::cout << "Minimum period is: " << period << std::endl;
    std::vector<int> A = {-1, -3};
    int answer = solution(A);
    std::cout << answer << std::endl;



    return 0;
}
