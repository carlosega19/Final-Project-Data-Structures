// The name of this file is provisional
/*
    AVL FORMAT
*/
#ifndef BILL_H
#define BILL_H
#include <iostream>
using namespace std;

// ESTRUCTURAS Y NOMBRES PROVISIONALES

struct details
{
    string code;
    int amount;
    float price;
    /*POINTER*/
    details*next;
};

struct bill
{
    int BF;
    string numberBill;
    string clientId;
    float total;
    details *detailBill;
    
    /*POINTERS*/
    bill*l;
    bill*r;
};

bill *newBill(string num, string cId, float t) {
    bill *nbill = new bill;
    nbill->numberBill = num;
    nbill->clientId = cId;
    nbill->total = t;
    /* DEFAULT */
    nbill->BF = 0;
    nbill->l = NULL;
    nbill->r = NULL;
}

/*BALANCE FUNCTIONS*/

/*------------------------------*/

int addBill(bill**B, string num, string cId, float t) {
    return 0;
}


#endif //BILL_H