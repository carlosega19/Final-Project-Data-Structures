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
    string code;
    string clientId;
    string date;
    float total;
    details *detailBill;
    
    /* POINTERS */
    bill *next;
    bill *prev;
};

//  Idea (hacer un dipolo?)
struct dipolo
{
    bill*first;
    bill*last;
};


bill *newBill(string num, string cId, string date, float t) {
    bill *nbill = new bill;
    nbill->code = num;
    nbill->date = date;
    nbill->clientId = cId;
    nbill->total = t;
    
    nbill->next = NULL;
    nbill->prev = NULL;
    return nbill;
}

int compare(string num1, string num2) {
    return stoi(num1) > stoi(num2);
}

int isEqual(string num1, string num2) {
    return stoi(num1) == stoi(num2);
}

// Insertar ordenadamente por codigo de factura
bool addBill(dipolo**P, string num, string cId, string date, float t) {
    if (!(*P)->first || compare((*P)->first->code, num))
    {
        if ((*P)->first && (*P)->first->code == num) return false;
        bill *newB = newBill(num, cId, date, t);

        newB->next = (*P)->first;
        if ((*P)->first) (*P)->first->prev = newB;
        else (*P)->last = newB;
        (*P)->first = newB;
    }
    else {
        bill *ax = (*P)->first;
        while (ax->next && compare(num, ax->next->code)) {            
            ax = ax->next;
        }
        if (ax->next && ax->next->code == num) return false;
        else {
            bill *newB = newBill(num, cId, date, t);
            newB->next = ax->next;
            newB->prev = ax;
            if (ax->next) ax->next->prev = newB;
            ax->next = newB;
            if(ax == (*P)->last) (*P)->last = newB;
        }
    }
    return true;
}

// Eliminar una factura
void deleteBill(dipolo**P, string num) {
    bill *ax = (*P)->first;
    while (ax && !isEqual(ax->code, num)) {
        ax = ax->next;
    }

    if (ax) {
        bill *t = ax;
        if (ax == (*P)->first) (*P)->first = (*P)->first->next;
        if (ax == (*P)->last) (*P)->last = (*P)->last->prev; 
        if (ax->prev) ax->prev->next = ax->next;
        if (ax->next) ax->next->prev = ax->prev;
        delete t;
    }
}

// Funcion de uso para pruebas
void printBills(bill*B) {
    while (B)
    {
        cout << B->code << endl;
        B = B->next;
    }
}


int main() {
    dipolo *bills = new dipolo;
    bills->first = NULL;
    bills->last = NULL;
    addBill(&bills, "10", "", "",0);
    addBill(&bills, "1", "", "",0);
    addBill(&bills, "5", "", "",0);
    addBill(&bills, "2", "", "",0);
    addBill(&bills, "2", "", "",0);
    addBill(&bills, "20", "", "",0);
    printBills(bills->first);
    
    cout << "\n\n";
    system("pause");
    cout << "\n\n";

    deleteBill(&bills, "1");
    printBills(bills->first);


    cout << "\n\n";
    system("pause");
    return 0;
}

#endif //BILL_H