#ifndef HELPER_H
#define HELPER_H

#include "branch.h"
#include "product.h"
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <iomanip>
//#include <conio.h>
//#include <windows.h>
#include <locale.h>
#include <string>
#include <sstream>
#include <cmath>


struct slista {
    string cont;
    slista *prox;
};


void invertir(slista **s) {
    slista *actual = *s;
    slista *prox = NULL;
    slista *prev = NULL;
    while (actual) {
        prox = actual->prox;
        actual->prox = prev;
        prev = actual;
        actual = prox;
    }
    *s = prev;

}

void mostrar(slista *s) {
    while (s) {
        cout << s->cont << endl << "----------------" << endl;
        s = s->prox;
    }
}


slista *SL(string val, slista *p) {
    slista *r = new slista;
    r->cont = val;
    r->prox = p;
    return r;
}

void agregar(slista **s, string cont) {
    if (*s) {
        slista *r = SL(cont, *s);
        *s = r;
    }
}


slista *split(string input, char charray) {
    slista *result = SL("", NULL);
    slista *temp = NULL;
    if (input.length() > 0) {
    
        for (int i = 0; i < input.length(); i++) {
            if (input[i] != charray) {
                result->cont += input[i];
            }
            else {
                agregar(&result, "");
            }
        }
        if (result->cont == "") {
            temp = result;
            result = result->prox;
            delete temp;
        }
    }
    invertir(&result);
    return result;
}


// ------------------------
// ------------------------
// ------------------------
// ------------------------



/*     FUNCTIONS      */

int length(string& line) {
    int count = 0;
    while (line[count] != '\0') {
        count++;
    }
    return count;
}

bool onlySpace(const std::string & str) {
    bool result = true;
    for (size_t i = 0; i < sizeof(str); i++) {
        if (!isspace(static_cast<unsigned char>(str[i]))) {
            result = false;
            break;
        }
    }
    return result;
}

bool isValid(string str){
    return !onlySpace(str) && length(str) > 0 && length(str) < 35;
}

bool find(const char* arr, int size, char charc) {
    for (int i = 0; i < size; i++) {
        if (arr[i] == charc) {
            return true;
        }
    }
    return false;
}

void replaceTrash(string& line) {
    char invalidChars[50] = "!@#$%^&*()_+=-/\\`~|'\".<:;[]{}?/";
    int size = sizeof(invalidChars) - 1;

    string newline;
    for (char& c : line) {
        if (!find(invalidChars, size, c)) {
            newline += c;
        }
    }
    line = newline;
}


/*---------------------------------*/
//        FILE MANAGMENT

void destroy(slista **n) {
    slista *temp = NULL;
    while (*n) {
        temp = *n;
        delete temp;
        *n = (*n)->prox;
    }
}

int len(slista *s) {
    int c = 0;
    while (s) { c++; s = s->prox; }
    return c;
}

slista *next(slista **n) {
    slista *temp = *n;
    *n = (*n)->prox;
    delete temp;
    return *n;
}

product *stringToProduct(char* s , product **P) {
    if (s) {
        slista *attrs = split(s, ',');
        int sl = len(attrs);
        if (sl >= 3) {
            addProduct(P , attrs->cont , attrs->prox->cont , attrs->prox->prox->cont , 0 , 0 , 0);
        }
    }
}

branch *stringToBranch(char* s , branch **B) {
    if (s) {
        slista *attrs = split(s, ',');
        int sl = len(attrs);
        if (sl >= 6) {
            addBranch(B , attrs->cont , attrs->prox->cont , attrs->prox->prox->cont, attrs->prox->prox->prox->cont, 
            attrs->prox->prox->prox->prox->cont, attrs->prox->prox->prox->prox->prox->cont);
        }
    }
}

void readProducts(product**P) {
    char *i = NULL;
    FILE *archivo;
    archivo = fopen("products.txt" , "r");
    if (!archivo) return;

    while (!feof(archivo))
    {
        if (fscanf(archivo, "%m[^\n]%*c", &i) == 1) {
            stringToProduct(i , P);
            i = NULL;
        }
    }
    delete i;
}

void readBranches(branch**B) {
    char *i = NULL;
    FILE *archivo;
    archivo = fopen("branches.txt" , "r");
    if (!archivo) return;

    while (!feof(archivo))
    {
        if (fscanf(archivo, "%m[^\n]%*c", &i) == 1) {
            stringToBranch(i , B);
            i = NULL;
        }
    }
    delete i;
}


void readInventory(branch*B , product*P) {
    char *i = NULL;
    FILE *archivo;
    archivo = fopen("inventory.txt" , "r");
    if (!archivo) return;
    branch *sB = NULL;
    product *sP = NULL;
    slista *branchCode, *productList, *pttr;
    while (!feof(archivo))
    {
        if (fscanf(archivo, "%m[^\n]%*c", &i) == 1) {
            branchCode = split(i, '|');
            if (len(branchCode) >= 2) {
                sB = searchBranchByCode(B , branchCode->cont); 
                productList = split(branchCode->prox->cont, ';'); 
                while (productList) {
                    pttr = split(productList->cont, ',');
                    if (pttr && len(pttr) >= 4) {
                        sP = searchProductByCode(P , pttr->cont);
                        addProductToBranch(sB, sP, stoi(pttr->prox->cont), stoi(pttr->prox->prox->cont), stof(pttr->prox->prox->prox->cont));
                    }
                    productList = next(&productList);
                    destroy(&pttr);
                }
                i = NULL;
            }
        }
    }
    // Vaciado de memoria
    if (i) {delete i;}
    destroy(&branchCode);
}


// Write branchs in .txt
void saveBranchs(branch*B) { 
    ofstream archivo("branchs.txt");
    if (archivo.is_open())
    {
        while (B)
        {
            archivo << B->code << "," << B->name << "," << B->city << "," << B->state << "," << B->tlf << "," << B->address << "\n";
            B = B->next;
        }
    }
    archivo.close();
}

// Take products of .txt
/*void readProducts(product** P, product** L) { // Update the function to delete the trash in line
    ifstream archivo("products.txt");
    if (archivo.fail()) return;
    string code, n, d,line;
    while (getline(archivo, line))
    {
        replaceTrash(line);
        istringstream ss(line);
        string dato;

        for (int i = 1; i < 4; i++)
        {
            getline(ss, dato, ',');
            switch (i)
            {
                case 1:
                    code = dato;
                case 2:
                    n = dato;
                    break;
                case 3:
                    d = dato;
                    break;
            }
        }
        addProduct(P, code, n, d, 0, 0 , 0);
    }
    archivo.close();
}*/
// Write products in .txt
void saveProducts(product* P) {
    ofstream file("products.txt");
    if (file.is_open())
    {
        while (P)
        {
            file << P->code << "," << P->name << "," << P->description << "\n";
            P = P->next;
        }
    }
    file.close();
}

// Take the products inside each branch
void readProductsOfBranch(branch*B , product*P ){
    ifstream archivo("inventory.txt");
    if (archivo.fail()) return;
    string codeB, codeP , line;
    int am , minAm;
    float price , temp;
    branch*selectedB;
    product*selectedP;
    while (getline(archivo , line))
    {
        replaceTrash(line);
        istringstream ss(line);
        string data;
        for (int i = 0; i < 5; i++)
        {
            getline(ss , data , ',');
            switch (i)
            {
                case 0:
                    codeB = data;
                    break;
                case 1:
                    codeP = data;
                    break;
                case 2:
                    am = stoi(data);
                    break;
                case 3:
                    minAm = stoi(data);
                    break;
                case 4:
                    price = stof(data);
                    getline(ss, data, ',');
                    temp = stof(data) / 100;
                    price += temp;
                    break;
            }
        }
        selectedB = searchBranchByCode(B , codeB);
        selectedP = searchProductByCode(P , codeP);
        if (selectedB && selectedP && am >= minAm && price > 0)
        {
            addProductToBranch(selectedB , selectedP , am , minAm, price);
        }
    }
    archivo.close();
}

void saveProductsOfBranch(branch*B){
    ofstream archivo("inventory.txt");
    if (archivo.fail()) return;
    while (B)
    {
        product*P = B->products; 
        while (P)
        {
            double p = P->price;
            double temp1;
            double temp2 = modf(p, &temp1);
            int temp3 = static_cast<int>(temp2 * 100);
            archivo << B->code<<","<<P->code<<","<<P->amount<<","<<P->minAmount<<","<<temp1<<","<<temp3<<"\n";
            P = P->next;
        }
        B = B->next;
    }
    archivo.close();
}


#endif // BRANCH_H