/*
EE441 Data Structures Homework-3, 18.01.2022
Nevin Sehbal Soyuslu - 2305340

Input: processesXXX.txt

Output: (In the terminal)
Linked List Process ID order
Linked List number of visited nodes while search & deletion
Linked List number of visited nodes while insertion

Binary Search Tree Process ID order
Binary Search Tree number of visited nodes while search & deletion
Binary Search Tree number of visited nodes while insertion

Personal Comments:
Linked List insertion time complexity is O(1), however it requires O(n) to traverse the elements.
Its search takes only one cycle, since the element we want is always in the head.
Therefore, as number of processes increase, the number of visited nodes for insertion increases.

Binary search tree insertion time complexity is O(1), however it requires O(log(n)) to traverse the elements.
Therefore, binary search tree is more advantageous in insertion compared to Linked List.
Its search is takes more time than Linked List search, since the element we want is in the leftmost branch.

Overall, as the number of processes get higher,
total number of nodes visited (search+insertion) gets smaller in
Binary Search Tree OS Scheduler compared to Linked List OS Scheduler.
*/

#include <iostream>
#include <stdio.h>
#include <fstream>

using namespace std;

// Struct: Node
// Each Node has 4 members
// ProcessID, ArrivalTime, RunTime, Priority
// Each Node has 3 nodes linked to it: next, right, left
// next is used for linked list implementation
// right and left node is used for binary search tree implementation
typedef struct Node{
    int processID;
    int arrivalTime;
    int runTime;
    int priority;
    Node *next;
    Node *right;
    Node *left;
};

/*
Class: Linked List
members:
"head" node,
num of nodes visited while inserting,
num of nodes visited while searching.
Functions:
insertNew->
    inserts nodes to the linked list according to their
    priority, the most prior process is in the beginning of the list.
deleteProcess-> deletes and returns the Node in front of
    the linked list (head), since it is the most prior one.
    Also, it updates the head to the next node.
isEmpty -> checks if head node is NULL or not, returns boolean
getNumInsertVisit-> returns the number of visited nodes during insertion
getNumSearchVisit-> returns the number of visited nodes during searching & deletion
*/
class LinkedList
{
private:
    Node *head;
    int insertNumNodes = 0;
    int searchNumNodes = 0;
public:
    LinkedList();
    void insertNew(Node *);
    Node *deleteProcess(void);
    bool isEmpty(void);
    int getNumInsertVisit(void);
    int getNumSearchVisit(void);
};


/*
Class: Binary Search Tree
members:
"root" node,
num of nodes visited while inserting,
num of nodes visited while searching.
Functions:
insertNew->
    inserts nodes to the binary search tree according to their
    priority, the most prior process is in the leftmost node.
deleteProcess-> deletes and returns the Node which is in the leftmost place,
    since it is the most prior one. If the deleted node has right child,
    this child is connected to the parent node of the deleted Node.
    Also, if leftmost Node is root, the right child of the root is updated as root.
isEmpty -> checks if head node is NULL or not, returns boolean
getNumInsertVisit-> returns the number of visited nodes during insertion
getNumSearchVisit-> returns the number of visited nodes during searching & deletion
*/
class BinarySearchTree
{
private:
    Node *root;
    int insertNumNodes = 0;
    int searchNumNodes = 0;
public:
    BinarySearchTree();
    void insertNew(Node *);
    Node *deleteProcess(void);
    bool isEmpty(void);
    int getNumInsertVisit(void);
    int getNumSearchVisit(void);
};

int main(){
/***************** Begin Linked List Implementation ********************************/
    cout<<"\nI am in Linked List Search now.\n"<<endl;
    LinkedList RQ; // linkedlist object is named ad RQ
    int insertVisitRQ=0,searchVisitRQ=0;
    ifstream processesFile; /* input file stream */
    processesFile.open("processes1000.txt");
    int numProcesses; /* number of processes */
    processesFile >> numProcesses; /* read from file */
    Node process[numProcesses]; /* create Node array */
    int processID, arrivalTime, runTime, priority;
    for(int i=0; i<numProcesses; ++i){
    /* read 4 integers from file */
    processesFile >> processID >> arrivalTime >> runTime >> priority;
    /* construct i'th element of the array */
    process[i].processID = processID;
    process[i].arrivalTime = arrivalTime;
    process[i].runTime = runTime;
    process[i].priority = priority;
    }
    processesFile.close();
    /* end of reading from file */
    int time = 0; // CPU time
    bool CPUBusy = false; // is the CPU currently running a process
    int processIndex = 0; // index of the process awaiting insertion in RQ
    Node *currentProcess = process;
    while (processIndex < numProcesses || !(RQ.isEmpty()) || CPUBusy){
     if (processIndex < numProcesses){ // there are processes not inserted into RQ
         if (process[processIndex].arrivalTime == time){ // if the process arrived now
         RQ.insertNew(&process[processIndex]); // insert it into RQ
         processIndex = processIndex + 1;
         } // next process awaits insertion
     }
     if (CPUBusy == true){ // CPU is running a process
        currentProcess->runTime = currentProcess->runTime-1;
        }// 1 clock cycle elapsed

     if (currentProcess->runTime == 0){ // if it was last cycle of the process
         cout<<currentProcess->processID<<" "; // process finished execution
         CPUBusy = false;
         } // CPU is no longer running a process

     if (CPUBusy == false && !(RQ.isEmpty())){
     // CPU is not running a process but there are processes awaiting execution
     currentProcess = RQ.deleteProcess(); // select new process
     CPUBusy = true; // CPU is now running a process
    }
    time = time + 1; // 1 clock cycle elapsed
    }
    insertVisitRQ = RQ.getNumInsertVisit(); //get number of visited nodes while inserting
    searchVisitRQ = RQ.getNumSearchVisit(); //get number of visited nodes while searching & deleting
    cout<<"\n\nLinked List:"<<endl;
    cout<<searchVisitRQ<<" nodes visited for searching"<<endl;
    cout<<insertVisitRQ<<" nodes visited for insertion"<<endl;

/***************** Begin Binary Search Tree Implementation ********************************/
    cout<<"\n\nI am in Binary Search tree now.\n"<<endl;
    BinarySearchTree BST; // Binary Search Tree object is created as BST
    int insertVisitBST=0,searchVisitBST=0;
    ifstream processesFile2; /* input file stream */
    processesFile2.open("processes1000.txt");
    int numProcesses2; /* number of processes */
    processesFile2 >> numProcesses2; /* read from file */
    Node process2[numProcesses2]; /* create Node array */
    int processID2, arrivalTime2, runTime2, priority2;
    for(int i=0; i<numProcesses2; ++i){
    /* read 4 integers from file */
    processesFile2 >> processID2 >> arrivalTime2 >> runTime2 >> priority2;
    /* construct i'th element of the array */
    process2[i].processID = processID2;
    process2[i].arrivalTime = arrivalTime2;
    process2[i].runTime = runTime2;
    process2[i].priority = priority2;
    }
    processesFile2.close();
    /* end of reading from file */
    int time2 = 0; // CPU time
    bool CPUBusy2 = false; // is the CPU currently running a process
    int processIndex2 = 0; // index of the process awaiting insertion in RQ
    Node *currentProcess2 = process2;
    while (processIndex2 < numProcesses2 || !(BST.isEmpty()) || CPUBusy2){
     if (processIndex2 < numProcesses2){ // there are processes not inserted into RQ
         if (process2[processIndex2].arrivalTime == time2){ // if the process arrived now
         BST.insertNew(&process2[processIndex2]); // insert it into RQ
         processIndex2 = processIndex2 + 1;
         } // next process awaits insertion
     }
     if (CPUBusy2 == true){ // CPU is running a process
        currentProcess2->runTime = currentProcess2->runTime-1;
        }// 1 clock cycle elapsed

     if (currentProcess2->runTime == 0){ // if it was last cycle of the process
         cout<<currentProcess2->processID<<" "; // process finished execution
         CPUBusy2 = false;
         } // CPU is no longer running a process

     if (CPUBusy2 == false && !(BST.isEmpty())){
     // CPU is not running a process but there are processes awaiting execution
     currentProcess2 = BST.deleteProcess(); // select new process
     CPUBusy2 = true; // CPU is now running a process
    }
    time2 = time2 + 1; // 1 clock cycle elapsed
    }
    insertVisitBST = BST.getNumInsertVisit();
    searchVisitBST = BST.getNumSearchVisit();
    cout<<"\n\nBinary Search Tree:"<<endl;
    cout<<searchVisitBST<<" nodes visited for searching"<<endl; //get number of visited nodes while inserting
    cout<<insertVisitBST<<" nodes visited for insertion"<<endl; //get number of visited nodes while searching & deleting
    return 0;
}

LinkedList::LinkedList()
{
    head = NULL;
}

void LinkedList::insertNew(Node *newProcess)
{
    Node *index = head;
    if(head == NULL){
        head = newProcess;
        head->next = NULL;
        insertNumNodes++;
        return;
    }
    if(newProcess->priority<index->priority){
        newProcess->next = index;
        head = newProcess;
        return;
    }
    while(index->next != NULL){
        if(newProcess->priority<index->next->priority){
            newProcess->next = index->next;
            index->next = newProcess;
            return;
        }
        insertNumNodes++;
        index = index->next;
    }
    index->next = newProcess;
    newProcess->next = NULL;
}

Node* LinkedList::deleteProcess(void)
{
    Node *deletedNode = head;
    head = head->next;
    searchNumNodes++;
    return deletedNode;
}
bool LinkedList::isEmpty(void)
{
    return (head==NULL);
}

int LinkedList::getNumInsertVisit(void)
{
    return insertNumNodes;
}
int LinkedList::getNumSearchVisit(void)
{
    return searchNumNodes;
}

BinarySearchTree::BinarySearchTree()
{
    root = NULL;
}
void BinarySearchTree::insertNew(Node *newProcess)
{
    Node *idx = root;
    if(root == NULL){
    root = newProcess;
    root->right = NULL;
    root->left = NULL;
    insertNumNodes++;
    return;
    }
    while(1){
        if(newProcess->priority<idx->priority){
            if(idx->left == NULL){
            idx->left = newProcess;
            newProcess->left = NULL;
            newProcess->right = NULL;
            return;
            }
            else idx = idx->left;
        }
        if(newProcess->priority>idx->priority){
            if(idx->right == NULL){
                idx->right = newProcess;
                newProcess->left = NULL;
                newProcess->right = NULL;
                return;
                }
            else idx = idx->right;
        }
        insertNumNodes++;
    }
}

Node* BinarySearchTree::deleteProcess(void)
{
    Node *leftmost_node = root;
    Node *leftmost_node_parent = root;
    if(leftmost_node->left==NULL){
        root = leftmost_node->right;
        searchNumNodes++;
        return leftmost_node;
        }
    while(leftmost_node->left!=NULL){
        leftmost_node_parent=leftmost_node;
        leftmost_node=leftmost_node->left;
        searchNumNodes++;
        }
    if((leftmost_node->right)!=NULL){
        leftmost_node_parent->left = leftmost_node->right;
        }
    else leftmost_node_parent->left=NULL;
    return leftmost_node;
}

bool BinarySearchTree::isEmpty(void)
{
    return (root==NULL);
}

int BinarySearchTree::getNumInsertVisit(void)
{
    return insertNumNodes;
}
int BinarySearchTree::getNumSearchVisit(void)
{
    return searchNumNodes;
}
