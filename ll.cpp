#include <iostream>
#include <string>
#include <sstream>
#include <cmath>

using namespace std; 

// global variables 
struct Node {
    int coefficient;
    int power;
    Node *next;
};

struct LinkedList {
  Node *head;
  Node *tail;
};

// global variables 
LinkedList *firstpoly = new LinkedList;
LinkedList *secondpoly = new LinkedList;
LinkedList *finalpoly = new LinkedList;
string fp = "";
string sp = "";
string operation;

void addLink(LinkedList *list, int coeff, int pow){
    if (list->head==NULL) {
        list->head = new Node;
        list->head->coefficient = coeff; 
        list->head->power = pow;
        list->head->next = NULL;
        list->tail = list->head;
    } 
    else {
        Node *front = list->head;
        Node *newlink = new Node;
        newlink->coefficient = coeff;
        newlink->power = pow; 

        // first link
        if (newlink->power < front->power){
            newlink->next = front; 
            list->head = newlink;
        }
        else if (newlink->power == front->power){
            front->coefficient += newlink->coefficient;
        }
        else{ 
            while (front->next != NULL && front->next->power < newlink->power){
                front = front->next;
            }
            // last link
            if (front->next != NULL && front->next->power == newlink->power){
                front->next->coefficient += newlink->coefficient;
            }
            else if (front == NULL) {
                list->tail->next = newlink;
                list->tail = list->tail->next;
                list->tail->next = NULL;
            }
            else{
                newlink->next = front->next;
                front->next = newlink;
            }
        }
    }
}
/* • In this programming assignment you are asked to implement a sparse polynomial equation
calculator using two different data structures. One implementation of this calculator should
use array and the other should use linked list. It’s advised that your implementation should
contain at least 5 functions: readPoly, writePoly, addPoly, mulPoly, squPoly in order to
read, write, add, multiply and square sparse polynomials. */

/* coefficient, power */


void readPoly(string equation){ 
    string coefficients = ""; 
    string powers = "";

    istringstream iss(equation);
    string t;
    int count = 0;
    int coefficient = 0; 
    int power = 0;
    bool first = true;

    while(iss >> t) {
        if ((t == "+") || (t == "*")  || (t=="**")) {
            operation = t;
            first = false;
            count = -1;
        }
        else if (count%2==0){
            coefficient = stoi(t);
            coefficients += t + " ";
            if (first) {
                fp += t + " ";
            }
            else {
                sp += t + " ";
            }
        }
        else if (count%2==1){
            power = stoi(t);
            powers += t + " ";
            if (first) {
                addLink(firstpoly, coefficient, power);
                fp += t + " ";
            }
            else {
                addLink(secondpoly, coefficient, power);
                sp += t + " ";
            }
        }
        count++;
    }
}

void writePoly(){
   
    /* 
    cout << "fp: ";
    for (const Node *pf = firstpoly->head; pf!=NULL; pf = pf->next) {
        cout << pf->coefficient << " " << pf->power << " ";
    }
    cout << "\nsp: ";
    for (const Node *ps = secondpoly->head; ps!=NULL; ps = ps->next) {
        cout << ps->coefficient << " " << ps->power << " ";
    }
    cout << "\nfinal: ";
    */
    for (const Node *p = finalpoly->head; p!=NULL; p = p->next) {
        cout << p->coefficient << " " << p->power << " ";
    }
}

void addPoly(){
    
    bool added = false;
    for (const Node *pf = firstpoly->head; pf!=NULL; pf = pf->next) {
        addLink(finalpoly, pf->coefficient, pf->power);
    }

    for (Node *sp = secondpoly->head; sp!=NULL; sp = sp->next) {
        addLink(finalpoly, sp->coefficient, sp->power);
    }

    for (Node *fp = finalpoly->head; fp!=NULL; fp = fp->next) {
        fp->coefficient %= (int) pow(10,6);
    }
    
}

void mulPoly(){
    int tpow = 0;
    int tcoeff = 0; 
    Node *n = finalpoly->head;
    for ( Node *pf = firstpoly->head; pf!=NULL; pf = pf->next) {
         for (Node *ps = secondpoly->head; ps!=NULL; ps = ps->next) {
             tpow = pf->power + ps->power; 
             tpow %= (int) pow(10,4);
             tcoeff = (pf->coefficient * ps->coefficient) % (int) pow(10,6);
             addLink(finalpoly, tcoeff, tpow);
        }  
    }
    
}

void squPoly(){
    for (Node *p=firstpoly->head; p!=NULL; p = p->next) {
        addLink(secondpoly, p->coefficient, p->power);
    }
    mulPoly();
}

void freeLinkedList(LinkedList* list){
    Node *current = list->head; 
    Node *n;
    while(current != NULL){
        n = current->next;
        delete current;
        current = n;
    }
    delete list;
}

int main(int argc,char* argv[]){
    
    readPoly(argv[1]);
    
    if (operation == "+"){
        addPoly();
    }
    else if (operation == "*"){
        mulPoly();
    }
    else if (operation == "**"){
        squPoly();
    }

    writePoly();

    freeLinkedList(firstpoly);
    freeLinkedList(secondpoly);
    freeLinkedList(finalpoly);
}