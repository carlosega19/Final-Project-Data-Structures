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
    string axS;
    enum TYPE T;
    ABBgen *left;
    ABBgen *right;
};

ABBgen *NG(bill *b, string ax = "") {
    ABBgen *r = new ABBgen;
    r->data = b;
    r->axS = ax;
    r->T = T_BILL;
    r->left = NULL;
    r->right = NULL;

    return r;
}

ABBgen *NG(detail *b, string ax = "") {
    ABBgen *r = new ABBgen;
    r->data = b;
    r->axS = ax;
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
string reprData(ABBgen *t) {
    if (t) {
        switch (t->T) {
            case T_BILL:
                return ((bill*) t->data)->code + "      " + ((bill*) t->data)->date + "      " + to_string( ((bill*) t->data)->total ) + "       " + t->axS;
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

void insertABBgen(ABBgen**N, bill *data, string ax = "") {
    ABBgen *temp = NG(data, ax);
    if (*N) {
        if (compareGen(*N, temp)) {
            insertABBgen(&(*N)->left, data, ax);
        }
        else if (compareGen(temp, *N )) {
            insertABBgen(&(*N)->right, data, ax);
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
            printFmt(reprData((*N)), 100);
            cout << "\t\n"; 
        }
        inorderGen(&(*N)->right);
        
        ABBgen *t = *N;
        *N = NULL;
        delete t;
    }
}

void billsClientResume(branch *branches, people *client) {
    bill *ax;
    ABBgen *resume = NULL;

    while (branches) {
        ax = branches->bills->first;
        while (ax) {
            if (ax->clientId == client->ID) insertABBgen(&resume, ax, branches->name);
            ax = ax->next;
        }
        branches = branches->next;
    }
    if (resume) {
        cout << "\n\t3.1 Resumen de facturas\n\n\tCliente: [ "<<client->name<<"]\n";
        cout << "\n--------------------------------------\n\tRESUMEN DE FACTURAS \n--------------------------------------\n";
        printFmt("Factura ", 15);
        printFmt("Fecha ", 15);
        printFmt("Monto ", 15);
        printFmt("Tienda ", 15);
        cout << "\n--------------------------------------\n";
        inorderGen(&resume);
        cout << "\n\n\t";
    }
}

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
    if (resume) inorderGen(&resume);
}

#endif //REPORTS_H