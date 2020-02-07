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

class LinkedList {
    public: 
        LinkedList(){ 
            head = NULL;
            tail = NULL;
        }
        void addLink(int coeff, int pow);
        friend void addPoly();
        friend void mulPoly();
        friend void squPoly();

   
        Node *head;
        Node *tail;
};

// global variables 
LinkedList *firstpoly = new LinkedList;
LinkedList *secondpoly = new LinkedList;
LinkedList *finalpoly = new LinkedList;

string fp = "";
string sp = "";
string operation ="";

void LinkedList::addLink(int coeff, int pow){
    if (this->head==NULL) {
        Node *newlink = new Node; 
        newlink->coefficient = coeff;
        newlink->power = pow;
        newlink->next = NULL;
        this->head = newlink;
        this->tail = newlink;
    } 
    else {
        Node *front = this->head;
        Node *newlink = new Node;
        newlink->coefficient = coeff;
        newlink->power = pow; 
        newlink->next = NULL;

        // first link
        if (newlink->power < front->power){
            newlink->next = front; 
            this->head = newlink;
        }
        else if (newlink->power == front->power){
            front->coefficient += newlink->coefficient;
            delete newlink;
        }
        else{ 
            while (front->next != NULL && front->next->power < newlink->power){
                front = front->next;
            }
            // last link
            if (front->next != NULL && front->next->power == newlink->power){
                front->next->coefficient += newlink->coefficient;
                delete newlink;
            }
            else if (front == NULL) {
                this->tail->next = newlink;
                this->tail = this->tail->next;
                this->tail->next = NULL;
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
                firstpoly->addLink(coefficient, power);
                fp += t + " ";
            }
            else {
                secondpoly->addLink(coefficient, power);
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
        finalpoly->addLink(pf->coefficient, pf->power);
    }

    for (Node *sp = secondpoly->head; sp!=NULL; sp = sp->next) {
        finalpoly->addLink(sp->coefficient, sp->power);
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
             finalpoly->addLink(tcoeff, tpow);
        }  
    }
    
}

void squPoly(){
    for (Node *p=firstpoly->head; p!=NULL; p = p->next) {
        secondpoly->addLink(p->coefficient, p->power);
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
    list->head = NULL;
    list->tail = NULL;
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
