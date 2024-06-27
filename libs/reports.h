#ifndef REPORTS_H
#define REPORTS_H

#include <iostream>

#include "branch.h"
#include "product.h"
#include "people.h"

// provisional

// Se accede asi (a la referencia del nodo): (*(*N)->dir)
struct ABBbill
{
    bill *dir;

    /* POINTERS */
    ABBbill *left;
    ABBbill *right;
};





// struct abbGenerico {
//     void *data;
//     abbGenerico *left;
//     abbGenerico *right;
// };
// // data = *context;
// void interpretar(abbGenerico *a) {
//     mostrar( (context*)(a->data) );

// }
// //data = int*
// void interpretar(abbGenerico *a) {
//     mostrar( (int*) (a->data) );
// }



ABBbill *newRep(bill *dir) {
    ABBbill *n = new ABBbill;
    n->dir = dir;
    n->left = NULL;
    n->right = NULL;
    return n;
}

void insertAbbBill(ABBbill**N, bill *dir) {
    if (*N) {
        if (compare( ((*N)->dir)->code, (dir)->code)) insertAbbBill(&(*N)->left, dir);
        else if (compare( (dir)->code, ((*N)->dir)->code)) insertAbbBill(&(*N)->right, dir);
        else return;
    }else *N = newRep(dir);
}

void inorderBill(ABBbill**N) {
    if (*N)
    {
        inorderBill(&(*N)->left);
        if ((*N)->dir) {
            cout << (*N)->dir->code << "   |   "; 
        }
        inorderBill(&(*N)->right);
        
        ABBbill *t = *N;
        *N = NULL;
        delete t;
    }
}


void billsClientResume(branch *branches, people *client) {
    bill *ax;
    ABBbill *resume = NULL;

    while (branches) {
        ax = branches->bills->first;
        while (ax) {
            if (ax->clientId == client->ID) insertAbbBill(&resume, ax);
            ax = ax->next;
        }
        branches = branches->next;
    }
    if (resume) inorderBill(&resume);
}

/*
ENUNCIADOS DE REPORTES

3.1.Dada la cedula de un cliente:
    3.1.1 Mostrar el resumen de todas sus facturas ordenado por número de factura (o fecha)
    indicando los totales en cada una. Por ejemplo:

*/



// ABB PRODUCTOS ------------------------------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------------------------------------

struct ABBprod
{
    detail *dir;

    //  POINTERS
    ABBprod *left;
    ABBprod *right;
};


ABBprod *newProd(detail *dir) {
    ABBprod *n = new ABBprod;
    n->dir = dir;
    n->left = NULL;
    n->right = NULL;
    return n;
}

void insertAbbProd(ABBprod**N, detail *dir) {
    if (*N) {
        if (compare( ((*N)->dir)->code, (dir)->code)) insertAbbProd(&(*N)->left, dir);
        else if (compare( (dir)->code, ((*N)->dir)->code)) insertAbbProd(&(*N)->right, dir);
        else {
            (*N)->dir->amount += dir->amount;
        }
    }else *N = newProd(dir);
}

void inorderProd(ABBprod**N) {
    if (*N)
    {
        inorderProd(&(*N)->left);
        cout << (*N)->dir->name << "    |    ";
        inorderProd(&(*N)->right);

        ABBprod *t = *N;
        *N = NULL;
        delete t;
    }
}

void productClientResume(branch *branches, people *client) {
    bill *ax;
    detail *dt;
    ABBprod *resume = NULL;

    while (branches)
    {
        ax = branches->bills->first;
        while (ax) {
            dt = ax->detailBill;
            
            while (dt) {
                if (ax->clientId == client->ID) insertAbbProd(&resume, dt);
                dt = dt->next;
            }    
            ax = ax->next;
        }
        branches = branches->next;
    }
    if (resume) inorderProd(&resume);
}

#endif //REPORTS_H