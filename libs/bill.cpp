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
    string code;
    string clientId;
    string date;
    float total;
    details *detailBill;
    
    /* POINTERS */
    bill*left;
    bill*right;
};

bill *newBill(string num, string cId, string date, float t) {
    bill *nbill = new bill;
    nbill->code = num;
    nbill->date = date;
    nbill->clientId = cId;
    nbill->total = t;

    /* DEFAULT */
    nbill->BF = 0;
    nbill->left = NULL;
    nbill->right = NULL;
}
int main() {
    bill *a = NULL;
    
    addBill(&a,"18","","",0);
    addBill(&a,"16","","",0);
    addBill(&a,"20","","",0);
    inorden(a);

    system("pause");
    deleteBill(&a, "18");
    inorden(a);
    system("pause");
    return 0;
}

#endif //BILL_H