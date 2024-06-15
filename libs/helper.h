#ifndef HELPER_H
#define HELPER_H

#include "branch.h"
#include "product.h"
#include <iostream>
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

void stringToProduct(char* s , product **P) {
    if (s) {
        slista *attrs = split(s, ',');
        int sl = len(attrs);
        if (sl >= 3) {
            addProduct(P , attrs->cont , attrs->prox->cont , attrs->prox->prox->cont , 0 , 0 , 0);
        }
    }
}

void stringToBranch(char* s , branch **B) {
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
    fclose(archivo);
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
    fclose(archivo);
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
                mostrar(productList);
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
    fclose(archivo);
}


// Write branchs in .txt
void saveBranchs(branch*B) { 
    FILE*archivo = fopen("branches.txt" , "w");
    while (B)
    {
        fprintf(archivo , "%s,%s,%s,%s,%s,%s\n" , B->code.c_str(), 
            B->name.c_str(), B->city.c_str(), B->state.c_str(), B->tlf.c_str(), B->address.c_str());
        B = B->next;
    }
    fclose(archivo);
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
    FILE*archivo = fopen("products.txt" , "w");
    while (P)
    {
        fprintf(archivo , "%s,%s,%s\n" , P->code.c_str(), P->name.c_str(), P->description.c_str());
        P = P->next;
    }
    fclose(archivo);
}

void saveProductsOfBranch(branch*B){
    FILE* file = fopen("inventory.txt" , "w");
    product*P;
    while (B)
    {
        fprintf(file, "%s|" , B->code.c_str());
        P = B->products;
        while (P)
        {
            fprintf(file , "%s,%d,%d,%.2f;" , P->code.c_str(), P->amount, P->minAmount, P->price);
            P = P->next;
        }
        fprintf(file , "\n");
        B = B->next;
    }
}


#endif // BRANCH_H