#ifndef PRODUCT_H
#define PRODUCT_H

#include <iostream>
#include <string>
#include <cctype>
using namespace std;

string tolow(string cad) {
    for (char& c : cad) {
        c = tolower(c);
    }
    return cad;
}

struct product {
    string code;
    string name;
    string description;
    int amount;
    int minAmount;
    float price;
    product* next;
};

product* searchProductByCode(product* P, string str) {
    if (!P) return NULL;
    if (tolow(P->code) == tolow(str)) return P;
    return searchProductByCode(P->next, str);
}

product* searchProductByType(product* P, string des) {
    if (!P) return NULL;
    if (tolow(P->description).find(tolow(des)) != string::npos) return P;
    return searchProductByType(P->next, des);
}

product* searchProductByPrice(product* P, float price) {
    if (!P) return NULL;
    if (P->price == price) return P;
    return searchProductByPrice(P->next, price);
}

void deleteProduct(product** P, string str) {
    if (!(*P)) return;
    product* ax = *P, * temp;
    if (tolow(ax->code) == tolow(str)) {
        temp = ax;
        (*P) = (*P)->next;
        delete temp;
    }
    else {
        while (ax->next && ax->next->code != str) ax = ax->next;
        if (ax->next) {
            temp = ax->next;
            ax->next = temp->next;
            delete temp;
            
        }
    }
}

void addProduct(product** P, string codeP, string name, string description, float price, int amount, int minAmount) {
    product* newP = new product;
    newP->name = name;
    newP->description = description;
    newP->price = price;
    newP->code = codeP;
    newP->amount = amount;
    newP->minAmount = minAmount;
    newP->next = *P;
    *P = newP;
}

#endif // PRODUCT_H
