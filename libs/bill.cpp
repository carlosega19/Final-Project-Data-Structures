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
/*
I I -> ABC
B
AC

D D -> ABC
B
CA
ROTACIONES DOBLES
DI -> ABC ROT DOBLE IZQUIERDA
C
AB

ID -> ABC ROT DOBLE DERECHA
C
BA
*/


/*BALANCE FUNCTIONS*/
void LL(bill**B) {
    bill*ax = (*B)->left;
    (*B)->left = ax->right;
    ax->right = *B;
    *B = ax;
    ax->BF = 0;
    (*B)->BF = 0;
}
void RR(bill**B) {
    bill*ax = (*B)->right;
    (*B)->right = ax->left;
    ax->left = *B;
    *B = ax;
    (*B)->BF = 0;
    ax->BF = 0;
}
void LR(bill**B) {
    bill*ax = (*B)->left;
    bill*bx = ax->right;
    (*B)->left = bx->right;
    ax->right = bx->left;
    bx->left = ax;
    bx->right = *B;
    *B = bx;
    
    ax->BF = 0;
    bx->BF = 0;
    (*B)->BF = 0;
}
void RL(bill**B) {
    bill*ax = (*B)->right;
    bill*bx = ax->left;
    (*B)->right = bx->left;
    ax->left = bx->right;
    bx->right = ax;
    bx->left = *B;
    *B = bx;
    
    ax->BF = 0;
    bx->BF = 0;
    (*B)->BF = 0;
}
/*------------------------------*/
/*
void rotacionIzqIzq(nodo**P){
    nodo*ax = *P;
    *P = (*P)->izq;
    ax->izq = (*P)->der;
    (*P)->der = ax;
    ax->peso = 0;
    (*P)->peso = 0;
}

void rotacionDerDer(nodo**P){
    nodo*ax = *P;
    *P = (*P)->der;
    ax->der = (*P)->izq;
    (*P)->izq = ax;
    ax->peso = 0;
    (*P)->peso = 0;
}

void rotacionIzqDer(nodo**P){
    nodo*ax = *P;
    nodo*bx = (*P)->izq;
    *P = bx->der;
    bx->der = (*P)->izq;
    ax->izq = (*P)->der;
    (*P)->izq = bx; (*P)->der = ax;
    ax->peso = 0; 
    bx->peso = 0; 
    (*P)->peso = 0;
}

void rotacionDerIzq(nodo**P){
    nodo*ax = *P;
    nodo*bx = (*P)->der;
    *P = bx->izq;
    ax->der = (*P)->izq;
    bx->izq = (*P)->der;
    (*P)->izq = ax;
    (*P)->der = bx;
    ax->peso = 0; 
    bx->peso = 0; 
    (*P)->peso = 0;
}
*/

/*------------------------------*/
int compare(string num1, string num2) {
    return stoi(num1) > stoi(num2);
}

void inorden(bill*B) {
    if (B)
    {
        inorden(B->left);
        cout << B->code << "     ";
        inorden(B->right);
    }
}
// NO FUNCIONA
int addBill(bill**B, string num, string cId, string date, float t) {
    int res = 0;
    if (*B) {
        if (compare((*B)->code, num)) { // a es mayor que b
            res = addBill(&(*B)->left, num, cId, date, t);
            if (res) (*B)->BF += -1;
            if ((*B)->BF < -1) {
                if (compare((*B)->left->code, num)) {
                    LL(B);
                } else LR(B);
                return 0;
            }
        }
        else if (compare(num , (*B)->code)) { // b es mayor que a
            res = addBill(&(*B)->right, num, cId, date, t);
            if (res) (*B)->BF += 1;
            if ((*B)->BF > 1) {
                if (compare(num, (*B)->right->code)) {
                    RR(B);
                } else RL(B);
                return 0;
            }
        }
        else return 0; // a == b
    }
    else {
        *B = newBill(num, cId, date, t);
        return 1;
    }
}

void replaceBills(bill *b1, bill *b2) {
    swap(b1->code, b2->code);
    swap(b1->date, b2->date);
    swap(b1->total, b2->total);
    swap(b1->detailBill, b2->detailBill);
    swap(b1->clientId, b2->clientId);
}

bill *mayor(bill**B, bill**t) {
    if (!(*B)->right) {
        *t = *B;
        *B = (*t)->left;
        return *t;
    }
    return mayor(&(*B)->right, t);
}

int deleteBill(bill**B, string num){
    if (*B)
    {
        if (compare((*B)->code, num)) {
            int res = deleteBill(&(*B)->left, num);
            if (res) (*B)->BF += 1;
            if ((*B)->BF > 1)
            {
                if ((*B)->right && (*B)->right->right) RR(B);
                else RL(B);
                return 0;
            }                
        }
        else if (compare(num , (*B)->code)) {
            int res = deleteBill(&(*B)->right, num);
            if (res) (*B)->BF += -1;
            if ((*B)->BF < -1) {
                if ((*B)->left && (*B)->left->left) LL(B);
                else LR(B);
                return 0;
            }
        }
        else {
            bill *t = *B;
            if (!(*B)->left && !(*B)->right) *B = NULL;
            else if (!(*B)->right) *B = (*B)->left;
            else if (!(*B)->left)  *B = (*B)->right;
            else replaceBills(*B, mayor(&(*B)->left, &t));
            delete t;
            return 1;
        }
    }
    return 0;
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