#ifndef HELPER_H
#define HELPER_H

#include "branch.h"
#include "product.h"
#include "people.h"
//#include "menu.h"
#include <iostream>
#include <string.h>


#if defined(__linux__)
    #define PLATFORM_NAME "linux"
#else
    #define PLATFORM_NAME "windows"
#endif






void clScr() {
    if (PLATFORM_NAME == "linux") {
        cout << "\033c\033[2J\033[H"; // Refrescar la pantalla y borrar el terminal
    } else {
        system("cls");
    }
}

void printFmt(string h, int size) {
        int length = h.length();
        string result = "";
	
	if (size > length) {
        result = h;
        for (int i = 0; i < (size - length); i++) {
                result += " ";
        }
    } 
	else if (size < length) {
        for (int i = 0; i < size; i++) {
                result += h[i];
        }
    } else { result = h; }
    cout << result;
}

void printFmt(int p, int size) {
        string h = to_string(p);
        int length = h.length();
        string result = "";
	
	if (size > length) {
        result = h;
        for (int i = 0; i < (size - length); i++) {
                result += " ";
        }
    } 
	else if (size < length) {
                for (int i = 0; i < size; i++) {
                        result += h[i];
                }
    } else { result = h; }
    cout << result;
}


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
        cout << s->cont <<" --> "; //endl << "----------------" << endl;
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
const string NUM_VALIDO = "1234567890";
const int NS = 10; 

void obtenerEntrada(string input, string *res) {
    cout << input << endl;
    getline(cin, *res); // antes era cin >> *res; esta permite agregar espacios a la entrada.
}

void obtenerEntrada2(string input, string *res) {
    cout << input;
    getline(cin, *res); // antes era cin >> *res; esta permite agregar espacios a la entrada.
}

int entradaValidar(string entrada) {
    int i = 0;
    char t;
    if (entrada[0]) {
        t = entrada[0];
    }
    while ((i < NS) && (t) && (t != NUM_VALIDO[i])) {
        i++;
    }
    if (t == NUM_VALIDO[i]) {
        return (((int) t) - 48);
    } else {
        return (-1);
    }
}

long int pow(int num, int e) {
	long int result = 1;
	for (int i = 0; i < e; i++) {
		result *= num; 
	}
	return result;
}


long int to_int(string s) {
	int index = 0;
	long int result = 0;
	int sl = s.length();
	while ((sl > 0) && (index < sl)) {
		switch (s[index]) {
			case '0':
				index++;
				break;
			case '1':
				result += pow(10, sl - index - 1);
				index++;
				break;
			case '2':
				result += 2 * pow(10, sl - index - 1);
				index++;
				break;
			case '3':
				result += 3 * pow(10, sl - index - 1);
				index++;
				break;
			case '4':
				result += 4 * pow(10, sl - index - 1);
				index++;
				break;
			case '5':
				result += 5 * pow(10, sl - index - 1);
				index++;
				break;
			case '6':
				result += 6 * pow(10, sl - index - 1);
				index++;
				break;
			case '7':
				result += 7 * pow(10, sl - index - 1);
				index++;
				break;
			case '8':
				result += 8 * pow(10, sl - index - 1);
				index++;
				break;
			case '9':
				result += 9 * pow(10, sl - index - 1);
				index++;
				break;
			default:
				index++;
				break;

		}
	}
	return result;
}


string to_string(long int *f) {
	int e = *f;
	string resultado = "";

	while (e > 0) {
		switch (e / 10) {
			case 1:
				resultado += "1";
				break;
			case 2:
				resultado += "2";
				break;
			case 3:
				resultado += "3";
				break;
			case 4:
				resultado += "4";
				break;
			case 5:
				resultado += "5";
				break;
			case 6:
				resultado += "6";
				break;
			case 7:
				resultado += "7";
				break;
			case 8:
				resultado += "8";
				break;
			case 9:
				resultado += "9";
				break;
			case 0:
				resultado += "0";
				break;
			default:
				break;
		}
		e = e / 10;
	}
	return resultado;
}



int confirm() {
    string entrada = "";
    obtenerEntrada2("\n\tSeguro que desea confirmar? \n\t(1) CONFIRMAR\n\t(0) Cancelar\n\t=> ", &entrada);
    if (entradaValidar(entrada)) return 1;
    return 0;
}

int length(string& line) {
    int count = 0;
    while (line[count] != '\0') {
        count++;
    }
    return count;
}

bool onlySpace(const std::string str) {
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


struct date {
    unsigned int day;
    unsigned int month;
    unsigned int year;

};

date newDate(unsigned int day, unsigned int month, unsigned int year) {
    date r;
    r.day = day;
    r.month = month;
    r.year = year;
    return r;
}

date getDate(string prompt) {
    string input = "";
    obtenerEntrada2(prompt, &input);
    slista *fields = split(input, '/');
    if (len(fields) >= 3) {
        return newDate(to_int(fields->cont), to_int(fields->prox->cont), to_int(fields->prox->prox->cont));
    }
    return newDate(0, 0, 0);
}

string getMonth(string input) {
    slista *date = split(input, '/');
    if (len(date) == 3) {
        return date->prox->cont;
    }
    return "";
}

int laterThan(date fst, date scnd) {
    if (fst.year > scnd.year) return 1;
    else if (fst.year < scnd.year) return 0;

    if (fst.month > scnd.month) return 1;
    else if (fst.month < scnd.month) return 0;

    if (fst.day > scnd.day) return 1;
    return 0;

}

string repr(date d) {
    return to_string(d.day) + "/" + to_string(d.month) + "/" + to_string(d.year);

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

void stringToPerson(char *s, people**P) {
    if (s) {
        slista *attrs = split(s, ',');
        int sl = len(attrs);
        if (sl >= 2) {
            addPerson(P, attrs->cont, attrs->prox->cont);
        }
    }
}

void readProducts(product**P) {
    char *i = (char* ) calloc(1024, sizeof(char));
    FILE *file;
    file = fopen("products.txt" , "r");
    if (!file) return;

    while (fgets(i, 1024, file)) {
        i[strcspn(i, "\n")] = '\0';
        stringToProduct(i,P);
    }
    if (i) delete i;
    fclose(file);
}

void readBranches(branch**B) {
    char *i = (char* ) calloc(1024, sizeof(char));
    FILE *file;
    file = fopen("branches.txt" , "r");
    if (!file) return;

    while (fgets(i, 1024, file)) {
        i[strcspn(i, "\n")] = '\0';
        stringToBranch(i,B);
    }
    
    if (i) delete i;
    fclose(file);
}


void readInventory(branch*B , product*P) {
    char *i = (char* ) calloc(1024, sizeof(char));
    FILE *file;
    file = fopen("inventory.txt" , "r");
    if (!file) return;
    branch *sB = NULL;
    product *sP = NULL;
    slista *branchCode, *productList, *pttr;
    
    while (fgets(i, 1024, file)) {
        branchCode = split(i, '|');
        if (len(branchCode) >= 2) {
            sB = searchBranchByCode(B , branchCode->cont);
            if (!sB) continue; 
            productList = split(branchCode->prox->cont, ';');
            while (productList) {

                pttr = split(productList->cont, ',');
                if (pttr && len(pttr) >= 4) {
                    sP = searchProductByCode(P , pttr->cont);
                    if (!sP) continue;
                    addProductToBranch(sB, sP, stoi(pttr->prox->cont), stoi(pttr->prox->prox->cont), stoi(pttr->prox->prox->prox->cont));
                }

                productList = next(&productList);
                destroy(&pttr);
            }
        }
    }
    // Vaciado de memoria
    if (i) {delete i;}
    destroy(&branchCode);
    fclose(file);
}

void readClients(people**P){
    char *i = (char* ) calloc(1024, sizeof(char));
    FILE *file;
    file = fopen("clients.txt" , "r");
    if (!file) return;

    while (fgets(i, 1024, file)) {
        i[strcspn(i, "\n")] = '\0';
        stringToPerson(i , P);
    }
    if (i) delete i;
    fclose(file);
}

void readBills(branch**B, people**C) {  
    char *i = (char* ) calloc(1024, sizeof(char));
    FILE *file;
    file = fopen("bills.txt" , "r");
    if (!file) return;

    bill *newB = NULL;
    detail *newDt = NULL;

    slista *billsList, *bill, *codes,*productsList, *pttr;
    product *sP;
    people *sC = NULL;
    branch *sB = NULL;

    while (fgets(i, 1024, file)) {
        billsList = split(i, '-');
        if (!(billsList->prox)) continue;

        sB = searchBranchByCode(*B, billsList->cont);
        if (!sB) continue;

        billsList = next(&billsList);
        while (billsList) {
            newDt = NULL;


            ////////////
            bill = split(billsList->cont, '|');
            
            codes = split(bill->cont, ',');
            cout << "c";
            if (codes && codes->prox) {
                sC = searchPeopleByID(*C, codes->prox->cont);
            } else { break; }
            cout << "d";
            if (!sC) break;
            newB = newBill(codes->cont, sC->ID, codes->prox->prox->cont);
            productsList = split(bill->prox->cont, ';');
            //////////////
            //cout d
            while (productsList) {
                pttr = split(productsList->cont, ',');
                if (!pttr) break;
                sP = searchProductByCode(sB->products, pttr->cont);
                if (!sP) break;
                addDeatail(&newDt, sP, stoi(pttr->prox->cont));

                productsList = next(&productsList);
                destroy(&pttr);
            }
            if (!newDt) continue;
            newB->total = totalPrice(newDt);
            addBill(&(sB)->bills, newB, newDt);

            billsList = next(&billsList);
        }
    }
    if (i) delete i;
    fclose(file);
}



// Write branchs in .txt
void saveBranchs(branch*B) { 
    FILE*file = fopen("branches.txt" , "w");
    while (B)
    {
        fprintf(file , "%s,%s,%s,%s,%s,%s\n" , B->code.c_str(), 
            B->name.c_str(), B->city.c_str(), B->state.c_str(), B->tlf.c_str(), B->address.c_str());
        B = B->next;
    }
    fclose(file);
}


// Write products in .txt
void saveProducts(product* P) {
    FILE*file = fopen("products.txt" , "w");
    while (P)
    {
        fprintf(file , "%s,%s,%s\n" , P->code.c_str(), P->name.c_str(), P->description.c_str());
        P = P->next;
    }
    fclose(file);
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
    fclose(file);
}

void saveClients(people*C) {
    FILE*file = fopen("clients.txt" , "w");
    while (C)
    {
        fprintf(file , "%s,%s\n" , C->ID.c_str(), C->name.c_str());
        C = C->next;
    }
    fclose(file);
}

// TODO: CAMBIAR LA ESTRUCTURA DEL TXT
void saveBills(branch*B) {
    FILE*file = fopen("bills.txt" , "w");
    bill *bx;
    detail *dx;
    while (B) {
        bx = B->bills->first;
        //if (!bx) continue;
        fprintf(file, "%s-", B->code.c_str());
        while (bx) {
            dx = bx->detailBill;
            if (!dx) break;
            fprintf(file, "%s,%s,%s|", bx->code.c_str(), bx->clientId.c_str(), bx->date.c_str());
            
            while (dx) {
                fprintf(file, "%s,%d;", dx->code.c_str(), dx->amount);
                dx = dx->next;
            }
            fprintf(file, "-");    
            bx = bx->next;
        }
        fprintf(file, "\n");
        B = B->next;
    }
    fclose(file);
}

string formatNULL(branch *b) {
    if (!b) return " ";
    else return b->name;

}

string formatNULL(people *b) {
    if (!b) return " ";
    else return "C.I." + b->ID + " " + b->name;

}


#endif // BRANCH_H
