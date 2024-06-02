#ifndef BRANCH_H
#define BRANCH_H

#include <iostream>
#include <unordered_map>
#include "product.h"
using namespace std;

struct branch {
    string code;
    string name;
    string city;
    string state;
    string address;
    string tlf;
    product* products;
    product* lastP;
    branch* next;
};

branch* searchBranchByCode(branch* B, string codeB) {
    if (!B) return NULL;
    if (tolow(B->code) == tolow(codeB)) return B;
    return searchBranchByCode(B->next, codeB);
}

bool searchBranchByCodeToF(branch* B, string codeB) {
    if (!B) return false;
    if (tolow(B->code) == tolow(codeB)) return true;
    return searchBranchByCodeToF(B->next, codeB);
}

branch* searchBranchByState(branch* B, string str) {
    if (!B) return NULL;
    if (tolow(B->state).find(tolow(str)) != string::npos) return B;
    return searchBranchByState(B->next, str);
}

branch* searchBranchByCity(branch* B, string str) {
    if (!B) return NULL;
    if (tolow(B->city).find(tolow(str)) != string::npos) return B;
    return searchBranchByCity(B->next, str);
}

void addBranch(branch** B, branch** L, string codeB, string name, string city, string state, string address, string tlf, unordered_map<string, branch*>& tableB) {
    branch* newB = new branch;
    newB->code = codeB;
    newB->name = name;
    newB->city = city;
    newB->state = state;
    newB->address = address;
    newB->tlf = tlf;
    newB->products = NULL;
    newB->lastP = NULL;

    if (!(*B)) {
        newB->next = *B;
        *B = newB;
        *L = newB;
    }
    else {
        newB->next = NULL;
        (*L)->next = newB;
        *L = newB;
    }
    tableB[newB->code] = newB;
}

void deleteBranch(branch** B, branch** L, string z) {
    if (!(*B)) return;
    branch* ax = *B, * temp;
    if (tolow(ax->code) == tolow(z)) {
        temp = ax;
        (*B) = (*B)->next;
        delete temp;
    }
    else {
        while (ax->next && tolow(ax->next->code) != tolow(z)) ax = ax->next;
        if (ax->next) {
            if (ax->next == *L) {
                temp = ax->next;
                ax->next = temp->next;
                delete temp;
                *L = ax;
            }
            else {
                temp = ax->next;
                ax->next = temp->next;
                delete temp;
            }
        }
    }
}

#endif // BRANCH_H
