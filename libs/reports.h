#ifndef REPORTS_H
#define REPORTS_H

#include <iostream>

#include "branch.h"
#include "product.h"
#include "people.h"

// provisional

// Se accede asi (a la referencia del nodo): (*(*N)->data)

// abb generico
enum TYPE {
    T_BILL = 1,
    T_DETAIL = 2,
    T_UNDEFINED = 0
};


struct ABBgen {
    void *data;
    enum TYPE T;
    ABBgen *left;
    ABBgen *right;
};

ABBgen *NG(bill *b) {
    ABBgen *r = new ABBgen;
    r->data = b;
    r->T = T_BILL;
    r->left = NULL;
    r->right = NULL;

    return r;
}

ABBgen *NG(detail *b) {
    ABBgen *r = new ABBgen;
    r->data = b;
    r->T = T_DETAIL;
    r->left = NULL;
    r->right = NULL;

    return r;
}

int compareGen(ABBgen *a, ABBgen *b) {
    if (a->T == b->T) {
        switch (a->T) {
            case T_BILL:
                return compare(((bill*) a->data)->code,  ((bill*) b->data)->code);
                break;
            case T_DETAIL:
                return compare(((detail*) a->data)->code,  ((detail*) b->data)->code);
                break;
            case T_UNDEFINED:
                return 0;
                break;
        }
    }
    return 0;
}

string reprCode(ABBgen *t) {
    if (t) {
        switch (t->T) {
            case T_BILL:
                return ((bill*) t->data)->code;
                break;
            case T_DETAIL:
                return ((detail*) t->data)->code;
                break;
            default:
                return "<Undefined type object>";
                break;
        }
    }
    return "\0";
}

void insertABBgen(ABBgen**N, bill *data) {
    ABBgen *temp = NG(data);
    if (*N) {
        if (compareGen(*N, temp)) {
            insertABBgen(&(*N)->left, data);
        }
        else if (compareGen(temp, *N )) {
            insertABBgen(&(*N)->right, data);
        }
        else return;
    } else *N = temp;
}

void insertABBgen(ABBgen**N, detail *data) {
    ABBgen *temp = NG(data);
    if (*N) {
        if (compareGen(*N, temp)) {
            insertABBgen(&(*N)->left, data);
        }
        else if (compareGen(temp, *N )) {
            insertABBgen(&(*N)->right, data);
        }
        else return;
    } else *N = temp;
}

void inorderGen(ABBgen**N) {
    if (*N)
    {
        inorderGen(&(*N)->left);
        if ((*N)->data) {
            printFmt(reprCode((*N)), 10);
            cout << "\t|\n"; 
        }
        inorderGen(&(*N)->right);
        
        ABBgen *t = *N;
        *N = NULL;
        delete t;
    }
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


void productClientResume(branch *branches, people *client) {
    bill *ax;
    detail *dt;
    ABBgen *resume = NULL;

    while (branches)
    {
        ax = branches->bills->first;
        while (ax) {
            dt = ax->detailBill;
            
            while (dt) {
                if (ax->clientId == client->ID) insertABBgen(&resume, dt);
                dt = dt->next;
            }    
            ax = ax->next;
        }
        branches = branches->next;
    }
    if (resume) inorderProd(&resume);
}

#endif //REPORTS_H