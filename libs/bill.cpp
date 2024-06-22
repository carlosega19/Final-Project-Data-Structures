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

// Nombre provisional (no se como ponerle)
dipolo *createBillsList() {
    dipolo *bills = new dipolo;
    bills->first = NULL;
    bills->last = NULL;
    return bills;
}


bill *newBill(string code, string cId, string date, float t) {
    bill *nbill = new bill;
    nbill->code = code;
    nbill->date = date;
    nbill->clientId = cId;
    nbill->total = t;
    
    nbill->next = NULL;
    nbill->prev = NULL;
    return nbill;
}

int compare(string code1, string code2) {
    return stoi(code1) > stoi(code2);
}

int isEqual(string code1, string code2) {
    return stoi(code1) == stoi(code2);
}

// Insertar ordenadamente por codigo de factura
bool addBill(dipolo**P, string code, string cId, string date, float t) {
    if (!(*P)->first || compare((*P)->first->code, code))
    {
        if ((*P)->first && (*P)->first->code == code) return false;
        bill *newB = newBill(code, cId, date, t);

        newB->next = (*P)->first;
        if ((*P)->first) (*P)->first->prev = newB;
        else (*P)->last = newB;
        (*P)->first = newB;
    }
    else {
        bill *ax = (*P)->first;
        while (ax->next && compare(code, ax->next->code)) {            
            ax = ax->next;
        }
        if (ax->next && ax->next->code == code) return false;
        else {
            bill *newB = newBill(code, cId, date, t);
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
void deleteBill(dipolo**P, string code) {
    bill *ax = (*P)->first;
    while (ax && !isEqual(ax->code, code)) {
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


// Buscar factura por codigo
bill *searchBillByCode(bill*B, string code) { 
    while (B && !isEqual(B->code, code)){
        B = B->next
    }
    return B;
}

// Funcion de uso para pruebas
/*void printBills(bill*B) {
    while (B)
    {
        cout << B->code << endl;
        B = B->next;
    }
}*/

void printBills(bill*B) {
    while (B)
    {
        cout << B->code << endl;
        B = B->prev;
    }
}


int main() {
    dipolo *bills = createBillsList();
    
    addBill(&bills, "10", "", "",0);
    addBill(&bills, "1", "", "",0);
    addBill(&bills, "5", "", "",0);
    addBill(&bills, "2", "", "",0);
    addBill(&bills, "2", "", "",0);
    addBill(&bills, "20", "", "",0);
    printBills(bills->last);
    
    cout << "\n\n";
    system("pause");
    cout << "\n\n";

    deleteBill(&bills, "20");
    printBills(bills->last);


    cout << "\n\n";
    system("pause");
    return 0;
}

#endif //BILL_H