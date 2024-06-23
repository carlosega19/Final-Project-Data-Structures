// The name of this file is provisional
/*
    AVL FORMAT
*/
#ifndef BILL_H
#define BILL_H
#include <iostream>
using namespace std;

// ESTRUCTURAS Y NOMBRES PROVISIONALES

struct detail
{
    string code;
    string name;
    int amount;
    int price;
    /*POINTER*/
    detail*next;
};

struct bill
{
    string code;
    string clientId;
    string date;
    int total;
    detail *detailBill;
    
    /* POINTERS */
    bill *next;
    bill *prev;
};

struct dipolo
{
    bill*first;
    bill*last;
};

detail *newDetail(string code, string name, int amount) {
    detail *r = new detail;
    r->code = code;
    r->name = name;
    r->amount = amount;

    return r;
}

//  Idea (hacer un dipolo?)


// Nombre provisional (no se como ponerle)
dipolo *createBillsList() {
    dipolo *bills = new dipolo;
    bills->first = NULL;
    bills->last = NULL;
    return bills;
}


bill *newBill(string code, string cId, string date) {
    bill *nbill = new bill;
    nbill->code = code;
    nbill->date = date;
    nbill->clientId = cId;
    nbill->total = 0;
    
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
bool addBill(dipolo**P, bill *newB, detail *prods) {
    if (!(*P)->first || compare((*P)->first->code, newB->code))
    {
        if ((*P)->first && (*P)->first->code == newB->code) return false;
        
        newB->detailBill = prods;
        newB->next = (*P)->first;
        if ((*P)->first) (*P)->first->prev = newB;
        else (*P)->last = newB;
        (*P)->first = newB;
    }
    else {
        bill *ax = (*P)->first;
        while (ax->next && compare(newB->code, ax->next->code)) {            
            ax = ax->next;
        }
        if (ax->next && ax->next->code == newB->code) return false;
        else {
            newB->detailBill = prods;
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
        B = B->next;
    }
    return B;
}

void addDeatail(detail**D, product*P, int amount) {
    detail *newD = newDetail(P->code, P->name, amount);
    newD->price = amount*(P->price);
    newD->next = *D;
    *D = newD;
}

int totalPrice(detail*B) {
    return B ? B->price + totalPrice(B->next) : 0;
}

#endif //BILL_H