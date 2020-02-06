#include <iostream>
#include <string>
#include <sstream>
#include <cmath>

using namespace std; 

// global variable 
int firstpoly[10000] = {0}; 
string fp = "";
int secondpoly[10000] = {0}; 
string sp = "";
string operation;

int finalpoly[10000] = {0};

/* • In this programming assignment you are asked to implement a sparse polynomial equation
calculator using two different data structures. One implementation of this calculator should
use array and the other should use linked list. It’s advised that your implementation should
contain at least 5 functions: readPoly, writePoly, addPoly, mulPoly, squPoly in order to
read, write add, multiply and square sparse polynomials. */

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
                firstpoly[power] = coefficient;
                // fp += t + " ";

            }
            else {
                secondpoly[power] = coefficient;
               // sp += t + " ";
            }
        }
        count++;
    }

    /* 
        for (int i = 0; i < 10000; i++){
            if (firstpoly[i]!=0){
                cout << firstpoly[i] << " " << i << " ";
            }
        }

        for (int i = 0; i < 10000; i++){
            if (secondpoly[i]!=0){
                cout << secondpoly[i] << " " << i << " ";
            }
        }
    
    cout << endl;
    cout << coefficients << endl; 
    cout << powers << endl;
    cout << operation << endl; 
    */
}

void writePoly(){
  for (int i = 0; i < 10000; i++){
        if (finalpoly[i]!=0){
            cout << finalpoly[i] << " " << i << " ";
        }
  }

  /* 
  cout << endl;
  for (int i = 0; i < 10000; i++){
        if (secondpoly[i]!=0){
            cout << secondpoly[i] << " " << i << " ";
        }
  }
  
  cout << endl;
  cout << "fp: " << fp << endl;
  cout << "sp: " << sp << endl;
  */
}

void addPoly(){
    for (int i = 0; i < 10000; i++){
        if (firstpoly[i] != 0){
            finalpoly[i] = firstpoly[i];
        }
        if (secondpoly[i]!=0){
            finalpoly[i] += secondpoly[i];
        }
        if (finalpoly[i] != 0){ 
            finalpoly[i] %= (int) pow(10,6);
        }
    }
}

void mulPoly(){
    int tpow = 0;
    int tcoeff = 0;
    for (int i = 0; i < 10000; i++){
        for (int j = 0; j < 10000; j++){
            if (firstpoly[i]!=0 && secondpoly[j]!=0){
                tpow = i + j; 
                tpow = tpow % (int) pow(10,4);
                tcoeff = (firstpoly[i] * secondpoly[j]) % (int) pow(10,6);
                finalpoly[tpow] += tcoeff;
            }
        }
    }
}

void squPoly(){
    for (int i = 0; i < 10000; i++){
        if (firstpoly[i] != 0){
            secondpoly[i] = firstpoly[i];
        }
    }   
    mulPoly();
}

int main(int argc,char* argv[]){
    
    int poly[10000] = {0}; //initialize entire array to 0 
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

    
}


