// main.cpp : This file contains the 'main' function. Program execution begins and ends there.
/*
INTEGRANTES
MANUEL NEGRON
CARLOS GALI�O
ANDRES DE QUINTAL
*/
#include <iostream>
#include <string>
#include <string.h>

using namespace std;

#if defined(__linux__)
#define PLATFORM_NAME "linux"
#else
#define PLATFORM_NAME "windows"
#endif

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
    int price;
    product* next;
};

struct detail {
    string code;
    string name;
    int amount;
    int price;
    /*POINTER*/
    detail* next;
};

struct bill {
    string code;
    string clientId;
    string date;
    int total;
    detail* detailBill;

    /* POINTERS */
    bill* next;
    bill* prev;
};

struct dipolo {
    bill* first;
    bill* last;
};

struct people {
    string ID;
    string name;
	string city; // No lo tenia

    people* next;
};

struct branch {
    string code;
    string name;
    string city;
    string state;
    string address;
    string tlf;
    /*Pointers*/
    product* products;
    dipolo* bills;
    branch* next;
};

//  GLOBAL 
int lineWidth = 120;
string line(lineWidth, '-');


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
/*
string to_string(int num) {
    char *str = new char[50];

    int i = 0;
    while (num > 0) {
        str[i++] = (num % 10) + '0';
        num /= 10;
    }

    str[i] = '\0';

    for (int j = 0; j < i / 2; j++) {
        char tmp = str[j];
        str[j] = str[i - 1 - j];
        str[i - 1 - j] = tmp;
    }

    return str;
}
*/
void obtenerEntrada(string input, string* res) {
    cout << endl << input << "\n\t=> ";
    getline(cin, *res);
}

/////////////////////

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

// ESTRUCTURAS Y NOMBRES PROVISIONALES

detail* newDetail(string code, string name, int amount) {
    detail* r = new detail;
    r->code = code;
    r->name = name;
    r->amount = amount;
    return r;
}

dipolo* createBillsList() {
    dipolo* bills = new dipolo;
    bills->first = NULL;
    bills->last = NULL;
    return bills;
}

bill* newBill(string code, string cId, string date) {
    bill* nbill = new bill;
    nbill->code = code;
    nbill->date = date;
    nbill->clientId = cId;
    nbill->total = 0;

    nbill->next = NULL;
    nbill->prev = NULL;
    return nbill;
}

int compare(string code1, string code2) {
    return to_int(code1) > to_int(code2);
}

int isEqual(string code1, string code2) {
    return to_int(code1) == to_int(code2);
}

int totalPrice(detail* B) {
    return B ? B->price + totalPrice(B->next) : 0;
}

void deleteAsociatedBills(branch **branches, string clientId) {
    branch *act = *branches;
    bill *ax = NULL;
    bill *t = NULL;
    while (act) {
        ax = (act)->bills->first;
        while (ax) { 
            if (ax->clientId == clientId) {
                t = ax;
                ax = ax->next;
                if (t == (act)->bills->first) (act)->bills->first = (act)->bills->first->next;
                if (t == (act)->bills->last) (act)->bills->last = (act)->bills->last->prev;
                if (t->prev) t->prev->next = t->next;
                if (t->next) t->next->prev = t->prev;
                delete t;
                t = NULL;
            } else ax = ax->next;
        }
        act = act->next;
    }
}

// Insertar ordenadamente por codigo de factura CUIDADO
bool addBill(dipolo** P, bill* newB, detail* prods) {
    if (newB->code != "" && (!(*P)->first || compare((*P)->first->code, newB->code))) {
        if ((*P)->first && (*P)->first->code == newB->code) return false;

        newB->detailBill = prods;
        newB->total = totalPrice(prods);
        newB->next = (*P)->first;

        if ((*P)->first) (*P)->first->prev = newB;
        else (*P)->last = newB;
        (*P)->first = newB;
    }
    else {
        bill* ax = (*P)->first;
        while (ax->next && compare(newB->code, ax->next->code)) {
            ax = ax->next;
        }
        if (ax->next && ax->next->code == newB->code) return false;
        else {
            newB->detailBill = prods;
            newB->total = totalPrice(prods);
            newB->next = ax->next;
            newB->prev = ax;
            if (ax->next) ax->next->prev = newB;
            ax->next = newB;
            if (ax == (*P)->last) (*P)->last = newB;
        }
    }
    return true;
}

// Eliminar una factura
void deleteBill(dipolo **P, string code) {
    bill* ax = (*P)->first;
    while (ax && !isEqual(ax->code, code)) {
        ax = ax->next;
    }

    if (ax) {
        bill* t = ax;
        if (ax == (*P)->first) (*P)->first = (*P)->first->next;
        if (ax == (*P)->last) (*P)->last = (*P)->last->prev;
        if (ax->prev) ax->prev->next = ax->next;
        if (ax->next) ax->next->prev = ax->prev;
        delete t;
    }
}

// Buscar factura por codigo
bill* searchBillByCode(bill* B, string code) {
    while (B && !isEqual(B->code, code)) {
        B = B->next;
    }
    return B;
}

void addDeatail(detail** D, product* P, int amount) {
    detail* newD = newDetail(P->code, P->name, amount);
    newD->price = amount * (P->price);
    newD->next = *D;
    *D = newD;
}

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

void addBranch(branch** B, string codeB, string name, string city, string state, string tlf, string address) {
    branch* newB = new branch;
    newB->code = codeB;
    newB->name = name;
    newB->city = city;
    newB->state = state;
    newB->address = address;
    newB->tlf = tlf;
    newB->products = NULL;
    newB->next = *B;

    newB->bills = createBillsList();

    *B = newB;
}

void deleteBranch(branch** B, string z) {
    if (!(*B)) return;
    branch* ax = *B, * temp;
    if (tolow(ax->code) == tolow(z)) {
        temp = ax;
        (*B) = (*B)->next;
        delete temp;
    }
    else {
        while (ax->next && ax->next->code != z) ax = ax->next;
        if (ax->next) {
            temp = ax->next;
            ax->next = temp->next;
            delete temp;
        }
    }
}

void addProductToBranch(branch* B, product* P, int amount, int minAmount, float price) {
    addProduct(&B->products, P->code, P->name, P->description, price, amount, minAmount);
}



people* getLast(people* p) {
    if (p) {
        while (p && (p->next)) {
            p = p->next;
        }
        return p;

    } return NULL;
}

// Función para validar que el nombre y apellido no contengan números
bool validateName(string name) {
    for (char c : name) {
        if (isdigit(c)) {
            return false;
        }
    }
    return true;
}

// Función para validar que la cedula tenga solo números y tenga entre 7 y 8 dígitos
bool validateID(string cedula) {
    if (cedula.length() < 3 || cedula.length() > 10) {
        return false;
    }
    for (char c : cedula) {
        if (!isdigit(c)) {
            return false;
        }
    }
    return true;
}

// Función para encontrar una persona por su cédula
people* searchPeopleByID(people* P, string id) {
    while (P != NULL) {
        if (P->ID == id) {
            return P;
        }
        P = P->next;
    }
    return NULL;
}

// Función para agregar una nueva persona a la lista
void addPerson(people** P, string id, string name, string city) {
    people* newP = new people;
    newP->ID = id;
    newP->name = name;
	newP->city = city;

    newP->next = NULL;
    if (*P) {
        people* aux = *P;
        while (aux && aux->next) {
            if (aux->ID == id) return;
            aux = aux->next;
        }
        aux->next = newP;
    }
    else {
        *P = newP;
    }
}


// Función para buscar un patrón en una cadena
bool find(string main, string pat) {
    for (size_t i = 0; i <= main.length() - pat.length(); i++) {
        bool found = true;
        for (size_t j = 0; j < pat.length(); j++) {
            if (main[i + j] != pat[j]) {
                found = false;
                break;
            }
        }
        if (found) return true;
    }
    return false;
}

// Función para mostrar todas las personas en la lista
void showPeople(people* P) {
    if (!P) {
        cout << "\t - No hay clientes en la lista" << endl;
        return;
    }

    while (P != NULL) {
        cout << "Cedula: " << P->ID << ", Nombre: " << P->name << ",   Ciudad: " << P->city << endl;
        P = P->next;
    }
}

// Función para eliminar una persona de la lista
void deletePerson(branch **branches, people** P, string id) {
    if (!P) return;

    people* ax = *P;
    people* temp = NULL;

    if (ax->ID == id) {
        temp = ax;
        *P = (*P)->next;
        deleteAsociatedBills(branches, ax->ID);
        delete temp;
        return;
    }
    else {
        while (ax->next && ax->next->ID != id) ax = ax->next;
        if (ax->next) {
            temp = ax->next;
            ax->next = temp->next;
            deleteAsociatedBills(branches, ax->ID);
            delete temp;
        }
    }
}

void consultByName(people* P, string name) {
    bool encontrado = false;

    // Convertir el nombre ingresado a minúsculas
    string lowerName = tolow(name);

    while (P != NULL) {
        // Convertir el nombre almacenado a minúsculas para la comparación
        string lowerNameToCompare = tolow(P->name);

        // Comparar las cadenas convertidas
        if (find(lowerNameToCompare, lowerName)) {
            cout << "CEDULA: " << P->ID << ", Nombre / Apellido: " << P->name << endl;
            encontrado = true;
        }
        P = P->next;
    }

    if (!encontrado) {
        cout << "No se encontraron personas con el nombre indicado." << endl;
    }
}

// Función para consultar clientes por cédula
void consultByID(people* P, string id) {
    people* person = searchPeopleByID(P, id);
    if (person) {
        cout << "Cedula: " << person->ID << ", Nombre y Apellido: " << person->name << endl;
    }
    else {
        cout << "No se encontró el cliente con la cédula '" << id << "'." << endl;
    }
}

// Función para imprimir todas las cédulas disponibles
void printIDs(people* P) {
    cout << "\n\t- LISTA DE CÉDULAS - \n";
    cout << "\n" << line << "\n";
    while (P) {
        cout << "\t\t- " << P->ID << endl;
        P = P->next;
    }
    cout << "\n\n\t0. CANCELAR\n";
}

// Módulo para consultar clientes
void consultCustomer(people* P) {
    int opcion;
    string consulta; // Para almacenar el nombre, apellido o cédula a consultar                                                
    do {
        cout << "\n\t - CONSULTAR CLIENTE -\n" << endl;
        cout << "\t1. Consultar por Nombre" << endl;
        cout << "\t2. Consultar por Cedula" << endl;
        cout << "\t0. Volver al Menu Anterior" << endl;
        cout << "\t - Su opcion (0-3): \n";
        cin >> opcion;
        cin.ignore();

        switch (opcion) {
        case 1:
            obtenerEntrada("\n\n\tIngrese el nombre a buscar: ", &consulta);
            cout << "Resultados para el nombre '" << consulta << "':\n" << endl;
            consultByName(P, consulta);
            break;
        case 2:
            printIDs(P);
            obtenerEntrada("\n\t\tIngrese la cédula del cliente: ", &consulta);
            consultByID(P, consulta);
            break;
        case 0:
            cout << "\n\n\tVolviendo al menú anterior...\n\n";
            break;
        default:
            cout << "\n\n\t\t-- Opción no válida --\n\n";
            break;
        }

        if (opcion != 0) {
            cout << "\nPresione Enter para continuar...";
        }
    } while (opcion != 0);
}

void clScr() {
    if (PLATFORM_NAME == "linux") {
        cout << "\033c\033[2J\033[H";
    }
    else {
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
    }
    else { result = h; }
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
    }
    else { result = h; }
    cout << result;
}

//  MANEJO DE STRINGS
struct slista {
    string cont;
    slista* prox;
};

void invertir(slista** s) {
    slista* actual = *s;
    slista* prox = NULL;
    slista* prev = NULL;
    while (actual) {
        prox = actual->prox;
        actual->prox = prev;
        prev = actual;
        actual = prox;
    }
    *s = prev;
}
slista* SL(string val, slista* p) {
    slista* r = new slista;
    r->cont = val;
    r->prox = p;
    return r;
}
void agregar(slista** s, string cont) {
    if (*s) {
        slista* r = SL(cont, *s);
        *s = r;
    }
}
slista* split(string input, char charray) {
    slista* result = SL("", NULL);
    slista* temp = NULL;
    if (input.length() > 0) {

        for (size_t i = 0; i < input.length(); i++) {
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


int entradaValidar(string entrada) {
    int i = 0;
    char t = '\0';
    if (entrada[0]) {
        t = entrada[0];
    }
    while ((i < NS) && (t) && (t != NUM_VALIDO[i])) {
        i++;
    }
    if (t == NUM_VALIDO[i]) {
        return (((int)t) - 48);
    }
    else {
        return (-1);
    }
}

int confirm() {
    string entrada = "";
    obtenerEntrada("\n\tSeguro que desea confirmar? \n\t(1) CONFIRMAR\n\t(0) Cancelar\n ", &entrada);
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

bool isValid(string str) {
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
void destroy(slista** n) {
    slista* temp = NULL;
    while (*n) {
        temp = *n;
        *n = (*n)->prox;
        delete temp;
    }
}
int len(slista* s) {
    int c = 0;
    while (s) { c++; s = s->prox; }
    return c;
}
slista* next(slista** n) {
    slista* temp = *n;
    *n = (*n)->prox;
    delete temp;
    return *n;
}

//      MANEJO BASICO DE FECHAS
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
    obtenerEntrada(prompt, &input);
    slista* fields = split(input, '/');
    if (len(fields) >= 3) {
        return newDate(to_int(fields->cont), to_int(fields->prox->cont), to_int(fields->prox->prox->cont));
    }
    return newDate(0, 0, 0);
}
string getMonth(string input) {
    slista* date = split(input, '/');
    if (len(date) == 3) {
        return date->prox->cont;
    }
    return "";
}
string repr(date d) {
    return to_string(d.day) + "/" + to_string(d.month) + "/" + to_string(d.year);
}

//-----------

void stringToProduct(char* s, product** P) {
    if (s) {
        slista* attrs = split(s, ',');
        int sl = len(attrs);
        if (sl >= 3) {
            addProduct(P, attrs->cont, attrs->prox->cont, attrs->prox->prox->cont, 0, 0, 0);
        }
    }
}

void stringToBranch(char* s, branch** B) {
    if (s) {
        slista* attrs = split(s, ',');
        int sl = len(attrs);
        if (sl >= 6) {
            addBranch(B, attrs->cont, attrs->prox->cont, attrs->prox->prox->cont, attrs->prox->prox->prox->cont,
                attrs->prox->prox->prox->prox->cont, attrs->prox->prox->prox->prox->prox->cont);
        }
    }
}

void stringToPerson(char* s, people** P) {
    if (s) {
        slista* attrs = split(s, ',');
        int sl = len(attrs);
        if (sl >= 2) {
            addPerson(P, attrs->cont, attrs->prox->cont, attrs->prox->prox->cont);
        }
    }
}

void readProducts(product** P) {
    char* i = (char*)calloc(1024, sizeof(char));
    FILE* file = NULL;
    fopen_s(&file, "products.txt", "r");
    if (!file) return;

    while (fgets(i, 1024, file)) {
        i[strcspn(i, "\n")] = '\0';
        stringToProduct(i, P);
    }
    if (i) free(i);
    fclose(file);
}

void readBranches(branch** B) {
    char* i = (char*)calloc(1024, sizeof(char));
    FILE* file = NULL;
    fopen_s(&file, "branches.txt", "r");
    if (!file) return;

    while (fgets(i, 1024, file)) {
        i[strcspn(i, "\n")] = '\0';
        stringToBranch(i, B);
    }

    if (i) free(i);
    fclose(file);
}

void readInventory(branch* B, product* P) {
    char* i = (char*)calloc(1024, sizeof(char));
    FILE* file = NULL;
    fopen_s(&file, "inventory.txt", "r");
    if (!file) return;
    branch* sB = NULL;
    product* sP = NULL;
    slista* branchCode = NULL;
    slista* productList = NULL;
    slista* pttr = NULL;

    while (fgets(i, 1024, file)) {
        branchCode = split(i, '|');
        if (len(branchCode) >= 2) {
            sB = searchBranchByCode(B, branchCode->cont);
            if (!sB) continue;
            productList = split(branchCode->prox->cont, ';');
            while (productList) {

                pttr = split(productList->cont, ',');
                if (pttr && len(pttr) >= 4) {
                    sP = searchProductByCode(P, pttr->cont);
                    if (sP) addProductToBranch(sB, sP, to_int(pttr->prox->cont), to_int(pttr->prox->prox->cont), to_int(pttr->prox->prox->prox->cont));
                }

                productList = next(&productList);
                destroy(&pttr);
            }
        }
    }

    if (i) free(i);
    destroy(&branchCode);
    fclose(file);
}

void readClients(people** P) {
    char* i = (char*)calloc(1024, sizeof(char));
    FILE* file = NULL;
    fopen_s(&file, "clients.txt", "r");
    if (!file) return;

    while (fgets(i, 1024, file)) {
        i[strcspn(i, "\n")] = '\0';
        stringToPerson(i, P);
    }
    if (i) free(i);
    fclose(file);
}

void readBills(branch** B, people** C) {
    char* i = (char*)calloc(1024, sizeof(char));
    FILE* file = NULL;
    fopen_s(&file, "bills.txt", "r");
    if (!file) return;

    bill* newB = NULL;
    detail* newDt = NULL;

    slista* billsList = NULL, * bill = NULL, * codes = NULL, * productsList = NULL, * pttr = NULL;
    product* sP = NULL;
    people* sC = NULL;
    branch* sB = NULL;

    while (fgets(i, 1024, file)) {
        billsList = split(i, '-');
        if (!(billsList->prox)) continue;

        sB = searchBranchByCode(*B, billsList->cont);
        if (!sB) continue;

        billsList = next(&billsList);
        while (billsList) {
            newDt = NULL;

            bill = split(billsList->cont, '|');

            codes = split(bill->cont, ',');

            if (codes && codes->prox) {
                sC = searchPeopleByID(*C, codes->prox->cont);
            }
            else { break; }
            if (!sC) break;
            newB = newBill(codes->cont, sC->ID, codes->prox->prox->cont);
            productsList = split(bill->prox->cont, ';');

            while (productsList) {
                pttr = split(productsList->cont, ',');

                if (!pttr) break;
                sP = searchProductByCode(sB->products, pttr->cont);

                if (!sP) break;

                addDeatail(&newDt, sP, to_int(pttr->prox->cont));

                productsList = next(&productsList);
                destroy(&pttr);
            }
            if (!newDt) break;

            newB->total = totalPrice(newDt);
            addBill(&(sB)->bills, newB, newDt);

            billsList = next(&billsList);
        }
    }
    if (i) free(i);
    fclose(file);
}



// Write branchs in .txt
void saveBranchs(branch* B) {
    FILE* file = NULL;
    fopen_s(&file, "branches.txt", "w");
    while (B) {
        fprintf(file, "%s,%s,%s,%s,%s,%s\n", B->code.c_str(),
            B->name.c_str(), B->city.c_str(), B->state.c_str(), B->tlf.c_str(), B->address.c_str());
        B = B->next;
    }
    fclose(file);
}


// Write products in .txt
void saveProducts(product* P) {
    FILE* file;
    fopen_s(&file, "products.txt", "w");
    while (P) {
        fprintf(file, "%s,%s,%s\n", P->code.c_str(), P->name.c_str(), P->description.c_str());
        P = P->next;
    }
    fclose(file);
}

void saveProductsOfBranch(branch* B) {
    FILE* file = NULL;
    fopen_s(&file, "inventory.txt", "w");
    product* P;
    while (B) {
        fprintf(file, "%s|", B->code.c_str());
        P = B->products;
        while (P) {
            fprintf(file, "%s,%d,%d,%d;", P->code.c_str(), P->amount, P->minAmount, P->price);
            P = P->next;
        }
        fprintf(file, "\n");
        B = B->next;
    }
    fclose(file);
}

void saveClients(people* C) {
    FILE* file = NULL;
    fopen_s(&file, "clients.txt", "w");
    while (C) {
		fprintf(file, "%s,%s,%s\n", C->ID.c_str(), C->name.c_str(), C->city.c_str());
        C = C->next;
    }
    fclose(file);
}

void saveBills(branch* B) {
    FILE* file = NULL;
    fopen_s(&file, "bills.txt", "w");
    bill* bx;
    detail* dx;
    while (B) {
        bx = B->bills->first;

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

string formatNULL(branch* b) {
    if (!b) return " ";
    else return b->name;
}

string formatNULL(people* b) {
    if (!b) return " ";
    else return "C.I." + b->ID + " " + b->name;
}

//      MANEJO DE UN ARBOL BINARIO DE BUSQUEDA AUXILIAR
enum TYPE {
    T_BILL = 1,
    T_DETAIL = 2,
    T_PRODUCT = 3,
    T_BRANCH = 4,
    T_CLIENT = 5,
    T_UNDEFINED = 0
};

//  ESTRUCTURA GENERAL
struct ABBgen {
    void* data;

    string axS;
    int axPr;
    int axAm;

    enum TYPE T;
    ABBgen* left;
    ABBgen* right;
};

//  ABB BRANCH
ABBgen* NG(branch* b) {
    ABBgen* r = new ABBgen;
    r->data = b;
    r->T = T_BRANCH;
    r->left = NULL;
    r->right = NULL;

    return r;
}

// ABB BILL
ABBgen* NG(bill* b, string ax = "") {
    ABBgen* r = new ABBgen;
    r->data = b;
    r->axS = ax;
    r->T = T_BILL;
    r->left = NULL;
    r->right = NULL;

    return r;
}

//  ABB CLIENT
ABBgen* NG(people* b, int am, int pr, string axS) {
    ABBgen* r = new ABBgen;
    r->data = b;
    r->axAm = am;
    r->axPr = pr;
	r->axS = axS;

    r->T = T_CLIENT;
    r->left = NULL;
    r->right = NULL;

    return r;
}

// ABB DETAIL
ABBgen* NG(detail* b, int pr, int am, string axS) {
    ABBgen* r = new ABBgen;
    r->data = b;
    r->axAm = am;
    r->axPr = pr;
    r->axS = axS;

    r->T = T_DETAIL;
    r->left = NULL;
    r->right = NULL;
    return r;
}

// ABB PRODUCT
ABBgen* NG(product* b) {
    ABBgen* r = new ABBgen;
    r->data = b;
    r->axAm = b->amount;
    r->axPr = b->minAmount;
    r->T = T_PRODUCT;
    r->left = NULL;
    r->right = NULL;
    return r;
}


struct branchContainer {
    branch* selBranch;
    int totalSelled;
    int earned;

    /*POINTERS*/
    branchContainer* next;
    ABBgen* clients;
};

branchContainer* constructor(branch* b, branchContainer* bc, ABBgen* c, int t, int e) {
    branchContainer* result = new branchContainer;
    result->selBranch = b;
    result->totalSelled = t;
    result->earned = e;

    result->next = bc;
    result->clients = c;

    return result;
}

void insertContainer(branchContainer** b, branchContainer* h) {
    h->next = *b;
    *b = h;
}

int compareGen(ABBgen* a, ABBgen* b) {
    if (a->T == b->T) {
        switch (a->T) {
        case T_BILL:
            return compare(((bill*)a->data)->code, ((bill*)b->data)->code);
            break;
        case T_DETAIL:
            return compare(((detail*)a->data)->code, ((detail*)b->data)->code);
            break;
        case T_PRODUCT:
            return (((product*)a->data)->amount > ((product*)b->data)->amount);
            break;
        case T_UNDEFINED:
            return 0;
        default:
            return 0;
            break;
        }
    }
    return 0;
}

void tableData(ABBgen* t) {
    if (t) {
        switch (t->T) {
        case T_BILL:
            printFmt(((bill*)t->data)->code, 15);
            printFmt(((bill*)t->data)->date, 15);
            printFmt(to_string(((bill*)t->data)->total), 15);
            printFmt(t->axS, 15);
            break;
        case T_DETAIL:
            printFmt(((detail*)t->data)->code, 15);
            printFmt(((detail*)t->data)->name, 25);
            printFmt(to_string(t->axAm), 15);
            printFmt(to_string(t->axPr), 15);
            printFmt(t->axS, 15);
            break;
        case T_PRODUCT:
            printFmt(((product*)t->data)->code, 15);
            printFmt(((product*)t->data)->name, 25);
            printFmt(to_string(t->axAm), 15);
            printFmt(to_string(t->axPr), 15);
            break;
        case T_CLIENT:
            printFmt(((people*)t->data)->ID, 15);
            printFmt(((people*)t->data)->name, 25);
            printFmt(to_string(t->axAm), 15);
            printFmt(to_string(t->axPr), 15);
			if (t->axS != "") printFmt(t->axS, 15); 
            break;
        default:
            cout << "<Undefined type object>";
            break;
        }
    }
}

void insertABBgen(ABBgen** N, bill* data, string ax = "") {
    ABBgen* temp = NG(data, ax);
    if (*N) {
        if (compareGen(*N, temp)) {
            insertABBgen(&(*N)->left, data, ax);
        }
        else if (compareGen(temp, *N)) {
            insertABBgen(&(*N)->right, data, ax);
        }
        else return;
    }
    else *N = temp;
}

// DETAIL ABB
void insertABBgen(ABBgen** N, detail* data, string axS = "") {
    if (*N) {
        if (compare(((detail*)(*N)->data)->code, data->code)) {
            insertABBgen(&(*N)->left, data, axS);
        }
        else if (compare(data->code, ((detail*)(*N)->data)->code)) {
            insertABBgen(&(*N)->right, data, axS);
        }
        else {
            (*N)->axAm += data->amount;
            (*N)->axPr += data->price;
        };
    }
    else *N = NG(data, data->price, data->amount, axS);
}


// INSERT ABB PRODUCTS 
void insertABBgen(ABBgen** N, product* data) {
    if (*N) {
        if (((product*)(*N)->data)->amount > data->amount) {
            insertABBgen(&(*N)->left, data);
        }
        else if (((product*)(*N)->data)->amount < data->amount) {
            insertABBgen(&(*N)->right, data);
        }
        else return;
    }
    else *N = NG(data);
}

// INSERT ABB BRANCHS
void insertABBgen(ABBgen** N, branch* data) {
    if (*N) {
        if (compare(((branch*)(*N)->data)->code, data->code)) {
            insertABBgen(&(*N)->left, data);
        }
        else if (compare(data->code, ((branch*)(*N)->data)->code)) {
            insertABBgen(&(*N)->right, data);
        }
        else return;
    }
    else *N = NG(data);
}

// INSERT ABB CLIENTS
void insertABBgen(ABBgen** N, people* data, int am, int pr, string axS = "") {
    if (*N) {
        if (compare(((people*)(*N)->data)->ID, data->ID)) {
            insertABBgen(&(*N)->left, data, am, pr);
        }
        else if (compare(data->ID, ((people*)(*N)->data)->ID)) {
            insertABBgen(&(*N)->left, data, am, pr);
        }
        else {
            (*N)->axAm += am;
            (*N)->axPr += pr;
        }
    }
    else *N = NG(data, am, pr, axS);
}

void inorderGen(ABBgen** N) {
    if (*N)
    {
        inorderGen(&(*N)->left);
        if ((*N)->data) {
            tableData(*N);
            cout << "\n";
        }
        inorderGen(&(*N)->right);

        ABBgen* t = *N;
        *N = NULL;
        delete t;
    }
}

void sortByAm(ABBgen** arr, int size) {
    int end = size - 1;
    int l = 0;
    int r = 0;

    for (int i = 0; i < size; i++) {
        for (int j = (end / 2); j > -1; j--) {
            l = (2 * j) + 1;
            r = (2 * j) + 2;

            if (l <= end && arr[j]->axAm > arr[l]->axAm) {
                swap(arr[j], arr[l]);
            }
            if (r <= end && arr[j]->axAm > arr[r]->axAm) {
                swap(arr[j], arr[r]);
            }
        }
        swap(arr[0], arr[end]);
        end--;
    }
}

void showArr(ABBgen** arr, int len) {
    for (int i = 0; i < len; i++) {
        tableData(arr[i]);
        cout << "\n";
    }
}

int lenAbb(ABBgen* N) {
    if (N) {
        return lenAbb(N->left) + lenAbb(N->right) + 1;
    }
    else return 0;
}

void abbToARrr(ABBgen* N, ABBgen** arr, int* i) {
    if (N) {
        abbToARrr(N->left, arr, i);
        arr[*i] = N;
        (*i)++;
        abbToARrr(N->right, arr, i);
    }
}

ABBgen** convertToArr(ABBgen* N, int* size) {
    *size = lenAbb(N);

    ABBgen** arr = (ABBgen**)calloc(*size, sizeof(ABBgen*));
    int pos = 0;
    abbToARrr(N, arr, &pos);
    return arr;
}

void sortAnddShow(ABBgen* N, product* prod) {
    int size = 0;
    ABBgen** arr = convertToArr(N, &size);

    sortByAm(arr, size);

    cout << "\tRESUMEN VENTAS DE [ " << prod->name << " ] por cliente";
    cout << "\n" << line << "\n";
    printFmt("C.I. ", 15);
    printFmt("NOMBRE ", 25);
    printFmt("COMPRADOS ", 15);
    printFmt("GANANCIA ", 15);
    cout << "\n" << line << "\n";
    showArr(arr, size);
    cout << "\n" << line << "\n";

    delete[] arr;
}

void showContainers(branchContainer** b, product* prod) {
    branchContainer* t;
    while (*b) {
        t = *b;
        cout << "\n" << line << "\n";

        printFmt("SUCURSAL", 15);
        printFmt("TOTAL VENDIDO", 15);
        printFmt("TOTAL INGRESOS", 15);
        cout << "\n" << line << "\n";
        printFmt((*b)->selBranch->name, 15);
        printFmt((*b)->totalSelled, 15);
        printFmt((*b)->earned, 15);

        cout << "\n" << line << "\n";
        sortAnddShow((*b)->clients, prod);
        cout << "\n\n";
        *b = (*b)->next;
        delete t;
    }
}

/////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////

void billsClientResume(branch* branches, people* client) {
    bill* ax = NULL;
    ABBgen* resume = NULL;

    while (branches) {
        ax = branches->bills->first;
        while (ax) {
            if (ax->clientId == client->ID) insertABBgen(&resume, ax, branches->name);
            ax = ax->next;
        }
        branches = branches->next;
    }
    if (resume) {
        cout << line << "\n\tResumen de facturas\n\n\tCliente: [ " << client->name << "]";
        cout << "\n" << line << "\n\t\tRESUMEN DE FACTURAS\n" << line << "\n";
        printFmt("Factura ", 15);
        printFmt("Fecha ", 15);
        printFmt("Monto (Bs.) ", 15);
        printFmt("Tienda ", 15);
        cout << "\n" << line << "\n";
        inorderGen(&resume);
        cout << "\n" << line << "\n\n";
    }
}

void productClientResume(branch* branches, people* client) {
    bill* ax;
    detail* dt;
    ABBgen* resume = NULL;

    while (branches) {
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

    if (resume) {
        cout << line << "\n\tResumen de productos adquiridos\n\n\tCliente: [ " << client->name << "]";
        cout << "\n" << line << "\n\tRESUMEN DE FACTURAS\n" << line << "\n";
        printFmt("CODIGO ", 15);
        printFmt("DESCRIPCION ", 25);
        printFmt("CANTIDAD ", 15);
        printFmt("PRECIO (Bs.) ", 15);
        cout << "\n" << line << "\n";
        inorderGen(&resume);
        cout << "\n" << line << "\n\n";
    }
}

// 3.2.1
void branchUnitsResume(branch* selected) {
    ABBgen* resume = NULL;
    bill* ax = selected->bills->first;
    int totalSelled = 0;
    float cost = 0;
    float totalBills = 0;
    float i = 0;
    while (ax) {
        detail* bx = ax->detailBill;
        cost = 0;
        while (bx) {
            insertABBgen(&resume, bx, to_string(searchProductByCode(selected->products, bx->code)->amount) );
            totalSelled += bx->amount;
            cost += bx->price;
            bx = bx->next;
        }
        i++;

        totalBills += cost;
        ax = ax->next;
    }

    if (resume) {
        cout << "\n\tResumen de [ " << selected->name << " ]";
        cout << "\n" << line << "\n\tRESUMEN DE FACTURA\n" << line << "\n";
        printFmt("CODIGO ", 15);
        printFmt("DESCRIPCION ", 25);
        printFmt("VENDIDOS ", 15);
        printFmt("GENERADO ", 15);
        printFmt("EXISTENCIA ", 15);

        cout << "\n" << line << "\n";
        inorderGen(&resume);
        cout << "\n" << line << "\n";
        cout << "\tCANTIDAD VENDIDA: " << totalSelled << "\n";
        cout << "\tCOSTO TOTAL: " << totalBills << "Bs.\n";
        cout << "\tPROMEDIO DE GASTO POR COMPRA: " << totalBills / i << "Bs.\n";
        cout << "\n" << line << "\n\n";
    }
}

void branchInventoryResume(branch* selected) {
    ABBgen* resume = NULL;
    product* ax = selected->products;
    while (ax) {
        insertABBgen(&resume, ax);
        ax = ax->next;
    }
    if (resume) {
        cout << "\n\t\tResumen Inventario de [ " << selected->name << " ]\n";
        cout << "\n" << line << "\n\tRESUMEN DE FACTURAS\n" << line << "\n";
        printFmt("CODIGO ", 15);
        printFmt("NOMBRE ", 25);
        printFmt("EXISTENCIA ", 15);
        printFmt("MIN. EXISTENCIA ", 15);
        cout << "\n" << line << "\n";
        inorderGen(&resume);
        cout << "\n" << line << "\n\n";
    }
}

void branchMonthlyResume(branch* selected, string month) {
    ABBgen* resume = NULL;

    bill* ax = selected->bills->first;
    detail* bx = NULL;
    int earned = 0;
    int totalProducts = 0;
    while (ax) {
        if (getMonth(ax->date) == month) {
            bx = ax->detailBill;
            while (bx) {
                insertABBgen(&resume, bx);
                earned += bx->price;
                totalProducts += bx->amount;
                bx = bx->next;
            }
        }
        ax = ax->next;
    }

    if (resume) {
        cout << "\n\t\tResumen Inventario de [ " << selected->name << " (" << selected->code << ") ]\n";
        cout << "\n" << line << "\n\tRESUMEN DE FACTURAS\n" << line << "\n";
        printFmt("CODIGO ", 15);
        printFmt("NOMBRE ", 25);
        printFmt("TOTAL VENDIDO ", 15);
        printFmt("MIN. EXISTENCIA ", 15);
        cout << "\n" << line << "\n";
        inorderGen(&resume);
        cout << "\n" << line << "\n";
        cout << "\tTotal ingresado: " << earned;
        cout << "\n\tProductos vendidos: " << totalProducts;
        cout << "\n" << line << "\n\n";
    }
}

// MERCADERO 3.1
void statsMarketingByCode(branch* branchs, string month) {
    ABBgen* resume = NULL;

    bill* ax = NULL;
    detail* bx = NULL;
    int earned = 0;
    int totalProducts = 0;

    while (branchs) {
        ax = branchs->bills->first;
        while (ax) {
            if (getMonth(ax->date) == month) {
                bx = ax->detailBill;
                while (bx) {
                    insertABBgen(&resume, bx);
                    earned += bx->price;
                    totalProducts += bx->amount;
                    bx = bx->next;
                }
            }
            ax = ax->next;
        }
        branchs = branchs->next;
    }

    if (resume) {
        cout << "\n\tRESUMEN VENTAS GLOBALES ";
        cout << "\n" << line << "\n\tRESUMEN DE FACTURAS\n" << line << "\n";
        printFmt("CODIGO ", 15);
        printFmt("NOMBRE ", 25);
        printFmt("TOTAL VENDIDO ", 15);
        printFmt("GANANCIA ", 15);
        cout << "\n" << line << "\n";
        inorderGen(&resume);
        cout << "\n" << line << "\n";
        cout << "\tTotal ingresado: " << earned;
        cout << "\n\tProductos vendidos: " << totalProducts;
        cout << "\n" << line << "\n\n";
    }
}




// MERCADERO 3.2
void resumeByBranch(ABBgen* resume, string month) {
    if (resume) {
        resumeByBranch(resume->left, month);
        branchMonthlyResume(((branch*)resume->data), month);
        resumeByBranch(resume->right, month);
    }
}

void statsMarketingByBranch(branch* branchs, string month) {
    ABBgen* resume = NULL;
    while (branchs) {
        insertABBgen(&resume, branchs);
        branchs = branchs->next;
    }
    resumeByBranch(resume, month);
}



void softSwap(branchContainer* a, branchContainer* b) {
    swap(a->selBranch, b->selBranch);
    swap(a->totalSelled, b->totalSelled);
    swap(a->earned, b->earned);
    swap(a->clients, b->clients);
}

void sortContainer(branchContainer** bc) {
    bool sorted = false;
    branchContainer* ax = *bc, * last = NULL;

    while (ax && sorted == false) {
        sorted = true;

        while (ax && ax->next != last) {
            if (ax->totalSelled < ax->next->totalSelled) {
                softSwap(ax, ax->next);
                sorted = false;

            }
            ax = ax->next;
        }
        last = ax;
        ax = *bc;
    }
}

void statsMarketingByQty(branch* branchs, people* clients, product* prod, string month) {
    bill* ax = NULL;
    detail* bx = NULL;
    people* cl = NULL;
    ABBgen* resume = NULL;
    branchContainer* container = NULL;

    int totalPerBranch = 0;
    int totalEarned = 0;

    while (branchs) {
        ax = branchs->bills->first;
        while (ax) {
            if (getMonth(ax->date) == month) {
                bx = ax->detailBill;
                cl = searchPeopleByID(clients, ax->clientId);
                if (cl) {
                    while (bx) {
                        if (bx->code == prod->code) {
                            insertABBgen(&resume, cl, bx->amount, bx->price);
                            totalPerBranch += bx->amount;
                            totalEarned += bx->price;
                        }
                        bx = bx->next;
                    }
                }
            }
            ax = ax->next;
        }

        if (resume) {
            insertContainer(&container, constructor(branchs, NULL, resume, totalPerBranch, totalEarned));
        }
        resume = NULL;
        totalPerBranch = 0;
        totalEarned = 0;

        branchs = branchs->next;
    }

    sortContainer(&container);
    showContainers(&container, prod);
}

// MERCADEO 3.4
void statsMarketingByClientBill(branch* branchs, people* clients, product* prod, string month) {
    bill* ax = NULL;
    detail* bx = NULL;
    people* cl = NULL;
    ABBgen* resume = NULL;
    int earned = 0;
    int totalProducts = 0;

    while (branchs) {
        ax = branchs->bills->first;
        while (ax) {
            if (getMonth(ax->date) == month) {
                bx = ax->detailBill;
                cl = searchPeopleByID(clients, ax->clientId);
                if (cl) {
                    while (bx) {
                        if (bx->code == prod->code) {
                            insertABBgen(&resume, cl, bx->amount, bx->price);
                            earned += bx->price;
                            totalProducts += bx->amount;
                        }
                        bx = bx->next;
                    }
                }
            }
            ax = ax->next;
        }
        branchs = branchs->next;
    }

    if (resume) {
        sortAnddShow(resume, prod);
        cout << "\tTotal ingresado: " << earned;
        cout << "\n\tProductos vendidos: " << totalProducts;
        cout << "\n" << line << "\n\n";
    }
}

// MERCADEO 3.5
void statsMarketingAll(branch *branchs, string month) {
    bill* ax = NULL;
    detail* bx = NULL;

    int selled = 0;
    int earned = 0;

    while (branchs) {
        cout << "\n" << line << "\n\t\tSUCURSAL: " << branchs->name << " [ " << branchs->code << " ]\n" << line;

        selled = 0;
        earned = 0;
        ax = branchs->bills->first;
        while (ax) {
            if (getMonth(ax->date) == month) {
                bx = ax->detailBill;
                while (bx) {
                    earned += bx->price;
                    selled += bx->amount;
                    bx = bx->next;
                }
            }
            ax = ax->next;
        }
        cout << "\n\tProductos vendidos =>  " << selled;
        cout << "\n\tIngresos =>  " << earned << " Bs.";
        if (selled) { cout << "\n\tPromedio de ingresos por producto: " << (float) earned / (float) selled << " Bs. \n" << line << "\n\n"; }
        else { cout << "\n\tNo hubo ingreso\n" << line << "\n\n"; } 
        
        branchs = branchs->next;
    }
}


/*------ MENU MANAGMENT ------*/
const string header = line + "\n\t\tSISTEMA DE INVENTARIO Y FACTURACION\n" + line + "\n";

struct mensajeInformativo {
    string data;
};

mensajeInformativo* MI() {
    mensajeInformativo* m = new mensajeInformativo;
    m->data = "";
    return m;
}

static mensajeInformativo* Mensajero = MI();

void actualizarMensaje(string m) {
    Mensajero->data = m;
}

void printCreators() {
    cout << line << "\nREALIZADO POR: Carlos Galiño, Andrés De Quintal y Manuel Negrón;\n" << line << endl;
}

/*--------------- BRANCHES AND PRODUCTS MENUS ---------------*/
void createProduct(product** P) {
    string code = "", name = "", description = "";
    bool invalidCode = true;
    do
    {
        obtenerEntrada("\n\t- Escribe el CODIGO del nuevo producto: ", &code);
        if (code == "0") return;
        invalidCode = searchProductByCode(*P, code);
        if (invalidCode) cout << "\n\t\t-- CODIGO YA EXISTENTE --\n\n";
    } while (invalidCode);

    obtenerEntrada("\n\t- Escribe el NOMBRE del nuevo producto: ", &name);
	cin.ignore();
    obtenerEntrada("\n\t- Escribe la DESCRIPCION del nuevo producto: ", &description);

    if (confirm()) {
        if ((isValid(code) && isValid(name) && isValid(description))) {
            cout << "\n\n\t\t-- product AGREGADO --\n\n";
            addProduct(P, code, name, description, 0, 0, 0);
        }
        else cout << "\n\nLOS DATOS SON INVALIDOS\n";
    }
}

void printProducts(product* P) {
    if (!P) return;
    cout << "\n\t - " << P->name << " [" << P->code << "]";
    printProducts(P->next);
}

void showAllProducts(product* P) {
    cout << header << endl;
    cout << "LISTA DE PRODUCTOS:\n" << line << endl;
    printProducts(P);
    cout << "\n\n";
}

void headerProducts() {
    cout << line << "\nLISTA DE PRODUCTOS\n" << line << endl; // FIXME
    printFmt("CODIGO", 10);
    printFmt("NOMBRE", 30);
    printFmt("DESCRIPCION", 30);
    cout << endl;
}

void printProductsInTable(product* P) {
    printFmt(P->code, 10);
    printFmt(P->name, 30);
    printFmt(P->description, 30);
    cout << endl;
}

void tableProducts(product* P) {
    cout << "\n\n";
    headerProducts();
    while (P)
    {
        printProductsInTable(P);
        P = P->next;
    }
    cout << line << "\n\n";
}
/*--------------------------------------------------------------------------------------------*/
product* selectProductByCode(product* P) {
    string codeSelect = "";
    showAllProducts(P);
    obtenerEntrada("\n\t0. FINALIZAR\n\n\n\tIngrese el codigo del product entre []: ", &codeSelect);
    if (codeSelect.empty() || codeSelect == "0") return NULL;
    return searchProductByCode(P, codeSelect);
}

void optionsModProduct(product* selected) {
    clScr();
    cout << header << endl;
    cout << "MODIFICAR\n\t1. NOMBRE\n\t2. DESCRIPCION\n\t3. CODIGO\n\t0. VOLVER A MENU ANTERIOR.\n" << line << endl;
    cout << "\n\n\tPRODUCTO ENCONTRADO: \n";
    cout << "\n\t - " << selected->name << " [" << selected->code << "]";
    cout << "\n\t\t ~ Descripcion: " << selected->description;
    cout << "\n\n\tIngresa la opcion a modificar: ";
}

void menuModProduct(product* P) {
    clScr();
    cout << header << endl;
    cout << "CONSULTAR PRODUCTO POR DESCRIPCION\n0. VOLVER AL MENU ANTERIOR.\n" << line << endl;

    product* selected = selectProductByCode(P); // THE USER SELECT A PRODUCT
    if (!selected) {
        cout << "\n\n\t\t\t-- PRODUCTO NO SELECCIONADO --\n\n";
        system("pause");
        return;
    }

    int op;
    string input = "";
    do {
        optionsModProduct(selected);
        obtenerEntrada("\n\n\tSu opcion (0-3): ", &input);
        op = entradaValidar(input);
        switch (op) {
        case 1:
            cout << "Nombre anterior: " << selected->name << endl;
            obtenerEntrada("Nuevo nombre: ", &input);

            if (confirm()) selected->name = input;
            break;
        case 2:
            cout << "Descripcion anterior: " << selected->description << endl;
            obtenerEntrada("Nueva descripcion: ", &input);

            if (confirm()) selected->description = input;
            break;
        case 3:
        {
            bool invalidCode = true;
            cout << "Codigo anterior: " << selected->code << endl;
            do {
                obtenerEntrada("Nuevo codigo: ", &input);
                if (input == "0") return;
                invalidCode = searchProductByCode(P, input);
                if (invalidCode) {
                    cout << "\n\t\t\t-- CODIGO YA EXISTENTE --\n\n";
                }
            } while (invalidCode);

            if (confirm()) selected->code = input;
            break;
        }
        }
    } while (op != 0);
}

void menuConsultProductByCode(product* B) {
    cout << header;
    cout << "\nCONSULTAR product POR CODIGO\n" << line << endl;
    product* selected = selectProductByCode(B);

    if (selected) {
        cout << "\n\tPRODUCTO ENCONTRADO: \n";
        cout << "\n\t - " << selected->name << " [" << selected->code << "]";
        cout << "\n\t\t ~ Descripcion: " << selected->description << "\n\n";
        system("pause");
    }
    else cout << "\n -- PRODUCTO INEXISTENTE --\n\n\n";
    system("pause");
}

void menuConsultProductByType(product* B) { // CAMBIAR EL "TYPE"
    clScr();
    string userInput = "";
    cout << header;
    cout << "\nCONSULTAR PRODUCTOS POR DESCRIPCION\n0. VOLVER A MENU ANTERIOR.\n" << line << endl;
    obtenerEntrada("\n\tIngresa la descripcion: ", &userInput);
    if (userInput == "0") return;

    cout << "\n\tPRODUCTOS ENCONTRADOS: \n";
    product* selected = searchProductByType(B, userInput);
    if (!selected) {
        cout << "\n\n\t\tNINGUNO...\n\n";
        return;
    }
    headerProducts();

    while (selected) {
        printProductsInTable(selected);
        selected = searchProductByType(selected->next, userInput);
    }
    cout << line << "\n\n\t";
    system("pause");
}

void menuConsultProductByDesc(product* B) {
    string input = "";
    int op = 0;
    do {
        clScr();
        cout << header;
        cout << "\nCONSULTAR product POR DESCRIPCION\n\t1. DESCRIPCION\n\t0. VOLVER A MENU ANTERIOR.\n" << line << endl;
        obtenerEntrada("", &input);
        op = entradaValidar(input);
        if (op == 1) {
            menuConsultProductByType(B);
        }
    } while (op != 0);
}

void menuDelProduct(product** P) {
    clScr();
    cout << header;
    cout << "\nELIMINAR PRODUCTO\n0. VOLVER A MENU ANTERIOR.\n" << line << endl;
    product* selected = selectProductByCode(*P);
    if (selected)
    {
        cout << "\n\t - " << selected->name << " [" << selected->code << "]";
        cout << "\n\t\t ~ Descripcion: " << selected->description << "\n\n";
        if (confirm()) {
            deleteProduct(P, selected->code);
        }
    }
}

/*--------------------------------------------------------------------------------------------------------------------*/
/*----------- BRANCHES -----------*/
void createBranch(branch** B) {
    string name, city, state, address, tlf, code;
    bool invalidCode = true;
    do {
        obtenerEntrada("\n\t- Escribe el CODIGO de la nueva branch: ", &code);
        invalidCode = searchBranchByCode(*B, code);
        if (invalidCode)
        {
            cout << "\n\t\t -- CODIGO YA EXISTENTE -- \n\n";
        }
    } while (invalidCode);

    obtenerEntrada("\n\t- Escribe el NOMBRE de la nueva branch (max.30): ", &name);
    obtenerEntrada("\n\t- Escribe el ESTADO de la nueva branch (max.30): ", &state);
    obtenerEntrada("\n\t- Escribe la CIUDAD de la nueva branch (max.30): ", &city);
    obtenerEntrada("\n\t- Escribe la DIRECCION de la nueva branch (max.30): ", &address);
    obtenerEntrada("\n\t- Escribe el NUMERO TELEFONICO de la nueva branch - (xxx) xxxxxxx: ", &tlf);

    if (!isValid(name) || !isValid(city) || !isValid(state) || !isValid(address) || !isValid(address) || !isValid(code)) {
        cout << " \n\n\t\t-- CAMPOS LLENADOS INCORRECTAMENTE --\n\n";
    }
    else
    {
        addBranch(B, code, name, city, state, tlf, address);
        cout << "\n\t\t-- SUCURSAL AGREGADA --\n\n\n\t";
    }
}

void printBranchs(branch* B) {
    if (!B) return;
    cout << "\n\t - " << B->name << " [" << B->code << "]\n";
    printBranchs(B->next);
}

void headerBranchs() {
    cout << line << "\nLISTA DE SUCURSALES\n" << endl;
    printFmt("CODIGO", 10);
    printFmt("NOMBRE", 30);
    printFmt("CIUDAD", 20);
    printFmt("ESTADO", 20);
    printFmt("TELEFONO", 20);
    printFmt("DIRECCION", 40);
    cout << endl << line << endl; // FIXME
}

void printBranchsInTable(branch* B) {
    printFmt(B->code, 10);
    printFmt(B->name, 30);
    printFmt(B->city, 20);
    printFmt(B->state, 20);
    printFmt(B->tlf, 20);
    printFmt(B->address, 40);
    cout << endl;
}

void tableBranchs(branch* B) {
    headerBranchs();
    while (B)
    {
        printBranchsInTable(B);
        B = B->next;
    }

    cout << line << "\n\n\t";
}

branch* selectBranchByCode(branch* B) {
    string codeSelect = "";
    printBranchs(B);
    obtenerEntrada("\n\n\n\tIngrese el codigo de la branch: ", &codeSelect);
    if (codeSelect.empty() || codeSelect == "0") return NULL;
    return searchBranchByCode(B, codeSelect);
}

void menuConsultBranchByCode(branch* B) {
    cout << line << "\nCONSULTAR SUCURSAL POR CODIGO\n" << line;
    branch* selected = selectBranchByCode(B);
    if (selected)
    {
        cout << "\n\n\tSUCURSAL ENCONTRADA: \n";
        cout << "\n\t - " << selected->name << " [" << selected->code << "]";
        cout << "\n\t\t ~ Direccion: " << selected->city << ", " << selected->state << ", " << selected->address;
        cout << "\n\t\t ~ Telefono: " << selected->tlf << "\n\n";
    }
    else cout << "\n -- SUCURSAL INEXISTENTE --\n\n\n";
}


void menuConsultByState(branch* B) {
    cout << header << endl;
    string userInput = "";
    cout << "\n\tCONSULTAR SUCURSAL POR ESTADO\n\t0.VOLVER AL MENU ANTERIOR\n" << line << endl;

    obtenerEntrada("\nIngresa el estado: ", &userInput);

    if (userInput == "0") return;

    cout << "\n\tSUCURSALES ENCONTRADAS: \n";
    branch* selected = searchBranchByState(B, userInput);
    if (!selected) {
        cout << "\n\n\t\tNINGUNA...\n\n\t";
        return;
    }

    headerBranchs();
    while (selected) {
        printBranchsInTable(selected);
        selected = searchBranchByState(selected->next, userInput);
    }
    cout << line << "\n\n\t";
}

void menuConsultByCity(branch* B) {
    cout << header << endl;
    cout << "\n\tCONSULTAR SUCURSAL POR CIUDAD\n\t0. VOLVER A MENU ANTERIOR.\n" << line << endl;
    string userInput = "";
    obtenerEntrada("\nIngresa la ciudad: ", &userInput);

    if (userInput == "0") return;

    cout << "\n\tSUCURSALES ENCONTRADAS: \n";
    branch* selected = searchBranchByCity(B, userInput);
    if (!selected) {
        cout << "\n\n\t\tNINGUNA...\n\n\t";
        system("pause");
        return;
    }

    headerBranchs();
    while (selected) {
        printBranchsInTable(selected);
        selected = searchBranchByCity(selected->next, userInput);
    }
    cout << line << "\n\n\t\t\t";
}



void menuDeleBranch(branch** B) {
    clScr();
    cout << line << "\nELIMINAR SUSCURSAL\n" << line << endl;
    branch* selected = selectBranchByCode(*B);

    if (selected) {
        cout << "\n\tSUCURSAL ENCONTRADA: \n";
        cout << "\n\t - " << selected->name << " [" << selected->code << "]";
        cout << "\n\t\t ~ Direccion: " << selected->city << ", " << selected->state << ", " << selected->address;
        cout << "\n\t\t ~ Telefono: " << selected->tlf << "\n\n";
        if (confirm()) deleteBranch(B, selected->code);
    }
    else {
        cout << "\n\n\t\t-- SUCURSAL NO SELECCIONADA --\n\n";
    }
}
/*---------------------------------------------------------------------------*/
/* PEOPLE */

void headerPeople() {
    cout << "\n\t- LISTA DE PERSONAS - \n\n";
    printFmt("CEDULA", 10);
    printFmt("NOMBRE Y APELLIDO", 30);
	printFmt("CIUDAD", 10);
    cout << endl << line << endl;
}

void printPersonInTable(people* P) {
    printFmt(P->ID, 10);
    printFmt(P->name, 30);
	printFmt(P->city, 10);
    cout << endl;
}

void tablePeople(people* P) {
    headerPeople();
    while (P) {
        printPersonInTable(P);
        P = P->next;
    }
    cout << line << "\n\n";
}

/*--------------------------------------------------------------------------------------------------------------------*/
/*          MENU INVENTORY MANAGMENT      */
void menuAddProductToBranch(branch* B, product* P) {
    int am = 0;
    int minAm = 0;
    float price = 0;
    string entrada = "";
    clScr();
    cout << header;
    cout << "\n\t0. VOLVER\n\n";
    product* selected = selectProductByCode(P);
    if (selected) {
        if (searchProductByCode(B->products, selected->code)) {
            cout << "\n\n\t-- Este product ya esta agregado --\n\n\n";
            system("pause");
            return;
        }

        cout << "\n\t - " << selected->name << " [" << selected->code << "]";
        cout << "\n\t\t ~ Descripcion: " << selected->description << "\n\n";

        obtenerEntrada("\n\tIngresa la cantidad minima del producto: ", &entrada);
        minAm = to_int(entrada);

        obtenerEntrada("\n\tIngresa la cantidad del producto: ", &entrada);
        am = to_int(entrada);

        obtenerEntrada("\n\tIngresa el precio del producto: ", &entrada);
        price = to_int(entrada);

        if ((am < minAm) || price < 0) cout << "\n\t-- DATOS INVALIDOS --\n\n";
        else if (confirm()) addProductToBranch(B, selected, am, minAm, price);
    }
    else cout << "\n -- PRODUCTO INEXISTENTE --\n\n\n";
}

void printProductssOfBranch(product* P) {
    if (!P) return;
    cout << "\n\t - " << P->name << " [" << P->code << "]";
    cout << "\n\t\t ~ Descripcion: " << P->description;
}

void headerProductsOfBranch() {
    cout << line << "\nLISTA DE PRODUCTOS\n" << line << endl;
    printFmt("CODIGO", 10);
    printFmt("NOMBRE", 30);
    printFmt("EXISTENCIA", 20);
    printFmt("EXISTENCIA MIN.", 20);
    printFmt("PRECIO", 20);
    cout << endl << line << endl;
}

void printProductsInTableOfBranch(product* P) {
    while (P) {
        printFmt(P->code, 20);
        printFmt(P->name, 20);
        printFmt(P->amount, 20);
        printFmt(P->minAmount, 20);
        printFmt(P->price, 20);
        cout << endl;
        P = P->next;
    }
}

void tableProductsOfBranch(product* P) {
    headerProductsOfBranch();
    printProductsInTableOfBranch(P);
    cout << line << "\n\n\t";
}

void menuDelProductOfBranch(product** P) {
    cout << header << "\n\tBORRAR PRODUCTO DE SUCURSAL\n\t0. VOLVER A MENU ANTERIOR.\n";
    cout << line << endl;
    product* selected = selectProductByCode(*P);
    if (selected) {
        cout << "\n\t - " << selected->name << " [" << selected->code << "]";
        cout << "\n\t\t ~ Descripcion: " << selected->description << "\n\t\t ~ Precio: " << selected->price << "$\n\n";
        if (confirm()) {
            deleteProduct(P, selected->code);
            cout << "\n\t-- product ELIMINADO --\n\n";
        }
    }
    else cout << "\n -- PRODUCTO INEXISTENTE --\n\n";
}



void optionsModProductOfBranch(product* selected) {
    cout << header << "\n\tMODIFICAR\n\t1. NOMBRE\n\t2. DESCRIPCION\n\t3. PRECIO\n\t4. CODIGO\n\t5. CANTIDAD\n\t6. CANTIDAD MINIMA\n\t0. VOLVER A MENU ANTERIOR.\n" << line << endl;
    cout << "\n\tPRODUCTO ENCONTRADO: \n";

    if (!selected) return;

    cout << "\n\t - " << selected->name << " [" << selected->code << "]";
    cout << "\n\t\t ~ Descripcion: " << selected->description;
    cout << "\n\t\t ~ Precio: " << selected->price << "$";
    cout << "\n\t\t ~ Cantidad: " << selected->amount << "";
    cout << "\n\t\t ~ Cantidad MINIMA: " << selected->minAmount << "\n\n";
    cout << "\nIngresa la opcion a modificar: ";
}


// inventory
void menuModProductOfBranch(product* P) {
    int op = 0;
    int userAm = 0;
    float userPrice = 0;
    string input = "";
    product* selected = selectProductByCode(P);
    do {
        clScr();
        optionsModProductOfBranch(selected);
        obtenerEntrada("", &input);
        op = entradaValidar(input);
        switch (op) {
        case 1:
            cout << "Nombre anterior: " << selected->name << endl;
            obtenerEntrada("Nuevo nombre: ", &input);

            if (confirm()) selected->name = input;
            break;
        case 2:
            cout << "Descripcion anterior: " << selected->description << endl;
            obtenerEntrada("Nueva descripcion: ", &input);
            if (confirm()) selected->description = input;
            break;
        case 3:
            cout << "Precio anterior: " << selected->price << endl;
            obtenerEntrada("Nuevo precio: ", &input);
            userPrice = to_int(input);
            cin >> userPrice;

            if (confirm()) selected->description = input;
            break;
        case 4:
        {
            bool invalidCode = true;
            cout << "Codigo anterior: " << selected->code << endl;
            do
            {
                obtenerEntrada("Nuevo codigo: ", &input);
                invalidCode = searchProductByCode(P, input);
                if (invalidCode)
                {
                    cout << "\n\t\t\t-- CODIGO YA EXISTENTE --\n\n";
                }
            } while (invalidCode || input != "0");
            if (confirm() && input != "0") selected->description = input;
            break;
        }
        case 5:
            cout << "Cantidad anterior: " << selected->amount << endl;
            obtenerEntrada("Nueva cantidad: ", &input);
            userAm = to_int(input);
            if (confirm() && selected->minAmount < userAm) {
                selected->amount = userAm;
            }
            else cout << "\n\t-- CANTIDAD INVALIDA --\n";
            break;
        case 6:
            cout << "Minima cantidad anterior: " << selected->minAmount << endl;
            obtenerEntrada("Nueva cantidad: ", &input);
            userAm = to_int(input);
            if (confirm() && userAm < selected->amount) selected->minAmount = userAm;
            break;
        }
    } while (selected && op != 0);
}

void optionsMenuInventory(branch* selected) {
    cout << header << "\n\t1. SELECCIONAR SUCURSAL\n\t2. AGREGAR PRODUCTOS\n\t3. ELIMINAR PRODUCTOS\n\t4. MODIFICAR INVENTARIO\n\t5. MOSTRAR TODOS LOS PRODUCTOS\n\t0. VOLVER A MENU ANTERIOR.\n" << line;
    cout << "\n\n\t\tSucursal seleccionada: ";
    if (!selected) cout << "\tSeleccone una sucursal para continuar...\n";
    else cout << selected->name << " [" << selected->code << "]\n\n";
}

void menuInventory(branch* B, product* P) {
    branch* selected = NULL;
    char op = '\0';
    do {
        clScr();
        optionsMenuInventory(selected);
        cin >> op;

        cin.ignore();
        if (!selected && (op != '1' && op != '0')) {
            cout << "\n\t\t\t-- SUCURSAL NO SELECCIONADA --\n\n\n";
            op = '\0';
        }
        switch (op) {
        case '1':
            selected = selectBranchByCode(B);
            cout << "\n\n";
            break;
        case '2':
            menuAddProductToBranch(selected, P);
            break;
        case '3':
            menuDelProductOfBranch(&selected->products);
            break;
        case '4':
            menuModProductOfBranch(selected->products);
            break;
        case '5':
            cout << "\n\n\t\tPRODUCTOS DE " << selected->name << "\n\n";
            tableProductsOfBranch(selected->products);
            system("pause");
            break;
        }
    } while (op != '0');
}

people* selectPersonById(people* P) {
    tablePeople(P); // Reemplazar showPeople con tablePeople
    string input;
    obtenerEntrada("\nIngrese la cedula: ", &input);
    return searchPeopleByID(P, input);
}


void printDetailBill(detail* D) {
    printFmt("CODIGO", 20);
    cout << "|";
    printFmt("DESCRIPCION", 30);
    cout << "|";
    printFmt("CANT", 10);
    cout << "|";
    printFmt("PRECIO", 10);
    cout << "|";
    while (D) {
        cout << endl;
        printFmt(D->code, 20);
        cout << "|";
        printFmt(D->name, 30);
        cout << "|";
        printFmt(D->amount, 10);
        cout << "|";
        printFmt(D->price, 10);
        cout << "|";
        D = D->next;
    }
}

void printBill(bill* B) {
    if (!B) return;
    cout << "\n" << line << endl;
    printFmt("Fecha: " + B->date, 20);
    printFmt("Factura " + B->code, 30);
    cout << endl;
    printFmt("C.I.: " + B->clientId, 20);
    cout << endl << line << endl;
    printDetailBill(B->detailBill);
    cout << endl << line << endl;
    cout << "\tTOTAL:   " << B->total;
    cout << endl << line << endl;
}

// Print all bills of a client
void showAllBills(bill* B, people* client) {
    while (B) {
        if (B->clientId == client->ID) {
            printBill(B);
            cout << "\n\n";
        }
        B = B->next;
    }
}

/*  ARREGLAR IMPRIMIR RESUMEN TODO: PULIR ESTA (no se como funciona printFmt())  */
void billsResume(branch* B, people* C) {
    if (!B || !B->bills || !B->bills->first) return;
    bill* ax = B->bills->first;
    
    cout << line << "\n\tRESUMEN DE FACTURAS\n" << line << "\n";
    printFmt("Factura ", 15);
    printFmt("Fecha ", 15);
    printFmt("Monto ", 15);
    cout << "\n" << line << "\n";
    while (ax) {
        if (ax->clientId == C->ID) {
            printFmt(ax->code, 10);
            printFmt(ax->date, 20);
            printFmt(ax->total, 10);
            cout << "\n";
        }
        ax = ax->next;
    }
    cout << "\n--------------------------------------\n";
}

void createBill(branch* B, people* C) {
    detail* dt = NULL;
    string recycle = "";
    date newD = newDate(0, 0, 0);
    product* prod = NULL;
    while (true) {
        clScr();
        prod = selectProductByCode(B->products);
        if (prod) {
            //cout << prod->amount << endl;
            obtenerEntrada("Ingrese la cantidad a agregar: ", &recycle);
            int cant = to_int(recycle);
            if (cant > 0 && cant <= prod->amount) {
                addDeatail(&dt, prod, cant);
            }
            else cout << "\n\t -- CANTIDAD INVALIDA --\n";
        }
        else break;
    }
    obtenerEntrada("\n\tIngrese el codigo de factura: ", &recycle);
    newD = getDate("\n\tIngrese la fecha dd/mm/yyyy: ");

    if (!dt) {
        cout << "\n\t-- NO SE AGREGO NADA --\n\n";
        return;
    }
    bill* newB = newBill(recycle, C->ID, repr(newD));
    newB->detailBill = dt;
    newB->total = totalPrice(dt);

    printBill(newB);
    if (confirm()) {
        addBill(&B->bills, newB, dt);
        cout << "\n\t-- FACTURA AGREGADA --\n\n";
    }
    else cout << "\n\t-- FINALIZADO --\n\n";
}

bill* selectBillByCode(branch *B, people *C) {
    if (!B || !C) return NULL;
    
    billsResume(B, C);
    string input = "";
    obtenerEntrada("\n\tIngrese el codigo de la factura: ", &input);
    return searchBillByCode(B->bills->first, input);
}


// TODO: PULIR ESTA FUNCION
void menuDeleteBill(branch* B, people* C) {
    bill* selected = selectBillByCode(B, C);
    if (selected)
    {
        printBill(selected);
        cout << "\n\n";
        if (confirm()) deleteBill(&B->bills, selected->code);
    }
    else cout << "\n\t-- FACTURA NO ENCONTRADA --\n";
}

/*--------------------------------------------------------------------------------------------------------------------*/

// ------------------------------------------
// ------------------------------------------
// ------------------------------------------
// ------------------------------------------
// ------------------------------------------
// ------------------------------------------




// ------------------------------------------
// ------------------------------------------
// ------------------------------------------
// ------------------------------------------
// ------------------------------------------
// ------------------------------------------

struct context {
    product** products;
    branch** branches;
    people** clients;
    dipolo** bills;

    branch* selectedBranch;
    people* selectedClient;
};

context* newContext(product** p, branch** b, people** c) {
    context* result = new context;
    result->products = p;
    result->branches = b;
    result->clients = c;
    result->selectedBranch = NULL;
    result->selectedClient = NULL;
    return result;
}

struct menuItem {
    menuItem* parent;
    string encabezado;
    int (*comportamiento)(menuItem**, int, context*);
};


void print(string s) {
    cout << s << endl;
}

void print(int s) {
    cout << s << endl;
}


void mostrarMenuActivo(menuItem* mi) {
    print(mi->encabezado);
}


// ------------------------------------------
// ------------------------------------------
// ------------------------------------------
// ------------------------------------------
// ------------------------------------------
// ------------------------------------------




// ------------------------------------------
// ------------------------------------------
// ------------------------------------------
// ------------------------------------------
// ------------------------------------------
// ------------------------------------------


menuItem* menuMantenimiento(menuItem*);
menuItem* controlProductos(menuItem*);
menuItem* controlSucursales(menuItem*);
/* SUCURSALES */
menuItem* menuModBranchs(menuItem*);
menuItem* menuConsultBranchByDesc(menuItem*);
menuItem* menuPeople(menuItem*);
menuItem* menuModifyPeople(menuItem*);
menuItem* menuBilling(menuItem*);
menuItem* menuReports(menuItem*);
menuItem* helperMarketing(menuItem*);
/* PRODUCTOS */


// Original
/*
obtenerEntrada -> cualquier string
entradaValidar -> opcion numerica

PASOS PARA IMPLEMENTAR MENUITEM

    1. CREAR EL OBJETO STRUCT CON ENCABEZADO ETC. ASIGNAR EL CONTROLADOR
    2. DEFINIR SIGNATURE DE EL CREADOR AQUI ARRIBA
    3. CREAR FUNCION DE COMPORTAMIENTO
    4. MODIFICAR LLAMADA ORIGINAL


*/

//obtenerEntrada("Indique el codigo de product para eliminar: ", &entrada);

int controllerMenuBilling(menuItem** activo, int selec, context* ct) {

    switch (selec) {
    case 0:
        if (*activo) {
            actualizarMensaje("");
            *activo = (*activo)->parent;
            return 1;
        }
        else {
            return 0;
        }
    case 1:
        ct->selectedBranch = selectBranchByCode(*ct->branches);
        actualizarMensaje("\n\t\tTienda[ " + formatNULL(ct->selectedBranch) + " ]\tCliente[ " + formatNULL(ct->selectedClient) + " ]");
        break;
    case 2:
        ct->selectedClient = selectPersonById(*ct->clients);
        actualizarMensaje("\n\t\tTienda[ " + formatNULL(ct->selectedBranch) + " ]\tCliente[ " + formatNULL(ct->selectedClient) + " ]");
        break;
    case 3:
        if (ct->selectedBranch && ct->selectedClient) createBill(ct->selectedBranch, ct->selectedClient);
        break;
    case 4:
        printBill(selectBillByCode(ct->selectedBranch, ct->selectedClient));
        break;
    case 5:
        menuDeleteBill(ct->selectedBranch, ct->selectedClient);
        break;
    case 6:
        if ((ct->selectedBranch) && (ct->selectedClient)) showAllBills((ct->selectedBranch)->bills->first, (ct->selectedClient));
        break;
    default:
        break;
    }
    system("pause");
    return 1;
}


int controllerMenuModBranch(menuItem** activo, int selec, context* ct) {
    branch* selected = selectBranchByCode(*ct->branches);
    if (!selected) return 1;
    string input = "";
    switch (selec) {
    case 0:
        if (*activo) {
            actualizarMensaje("");
            *activo = (*activo)->parent;
            return 1;
        }
        else {
            return 0;
        }
    case 1:
        cout << "Nombre anterior: " << selected->name << endl;
        obtenerEntrada("Nuevo nombre: ", &input);
        if (confirm() && isValid(input)) selected->name = input;
        break;
    case 2:
        cout << "Estado anterior: " << selected->state << endl;
        obtenerEntrada("Nueva ciudad: ", &input);
        if (confirm() && isValid(input)) selected->state = input;
        break;
    case 3:
        cout << "Cidudad anterior: " << selected->city << endl;
        obtenerEntrada("Nueva ciudad: ", &input);
        if (confirm() && isValid(input)) selected->city = input;
        break;
    case 4:
        cout << "Direccion anterior: " << selected->address << endl;
        obtenerEntrada("Nueva direccion: ", &input);
        if (confirm() && isValid(input)) selected->address = input;
        break;
    case 5:
        cout << "Telefono anterior: " << selected->tlf << endl;
        obtenerEntrada("Nuevo telefono: ", &input);
        if (confirm() && isValid(input)) selected->tlf = input;
        break;
    default:
        actualizarMensaje("La opcion seleccionada no corresponde a una accion. Intente nuevamente.\n");
        break;
    } return 1;
}


int controllerConsultBranchByDesc(menuItem** activo, int selec, context* ct) {
    switch (selec)
    {
    case 0:
        if (*activo) {
            actualizarMensaje("");
            *activo = (*activo)->parent;
            return 1;
        }
        else {
            return 0;
        }
    case 1:
        menuConsultByState(*(ct->branches));
        break;
    case 2:
        menuConsultByCity(*(ct->branches));
        break;
    }
    system("pause");
    return 1;
}

/*Functions Menu People */

int controllerMenuModifyPeople(menuItem** activo, int selec, context* ct) {
    static people* cliente = NULL;
    string name = "";
    string id = "";

    if (cliente == NULL) {
        cliente = (ct->selectedClient);
    }

    cout << "\n\t- Informacion actual del cliente:\n" << endl;
    cout << "Cedula: " << cliente->ID << ", Nombre y Apellido: " << cliente->name << endl;

    switch (selec) {
    case 0:
        if (*activo) {
            actualizarMensaje("");
            *activo = (*activo)->parent;
            return 1;
        }
        else {
            return 0;
        }
    case 1:
        obtenerEntrada("\n\t - Ingrese el nuevo Nombre y Apellido: ", &name);
        if (!validateName(name)) {
            cout << "El nombre y el apellido no deben contener numeros." << endl;
            return 1;
        }
        cliente->name = name;
        cout << "\n\t- Nombre y Apellido modificados exitosamente! -" << endl;
        cout << "\n\t- Informacion actualizada del cliente:\n" << endl;
        cout << "Cedula: " << cliente->ID << ", Nombre y Apellido: " << cliente->name << endl;
        return 1;
    case 2:
        obtenerEntrada("\n\t - Ingrese la nueva Cedula: ", &id);
        if (!validateID(id)) {
            cout << "\nCedula invalida. Debe contener entre 3 y 10 digitos numericos." << endl;
            return 1;
        }
        if (searchPeopleByID(*(ct->clients), id) != NULL) {
            cout << "\nCedula ya existente. Ingrese una cedula unica." << endl;
            return 1;
        }
        cliente->ID = id;
        cout << "\n\t- Cedula modificada exitosamente! -" << endl;
        cout << "\n\t- Informacion actualizada del cliente:\n" << endl;
        cout << "Cedula: " << cliente->ID << ", Nombre y Apellido: " << cliente->name << endl;
        return 1;

    default:
        cout << "Opcion no valida. Intente de nuevo." << endl;
        return 1;
    }
	system("pause");
}

int controllerMenuPeople(menuItem** activo, int selec, context* ct) {
    string id = "";
    string name = "";
	string city = "";

    people* client = NULL;

    switch (selec) {
    case 0:
        if (*activo) {
            actualizarMensaje("");
            *activo = (*activo)->parent;
            return 1;
        }
        else {
            return 0;
        }

    case 1:
        cout << "\n - AGREGAR CLIENTE - \n";
        obtenerEntrada("\n\t - Ingrese su cedula: ", &id);
        if (!validateID(id)) {
            cout << "\nCedula invalida. Debe contener entre 3 y 10 digitos numericos." << endl;
            system("pause");
            break;
        }
        obtenerEntrada("\n\t - Ingrese su nombre y apellido: ", &name);
        if (!validateName(name)) {
            cout << "\nEl nombre y el apellido no deben contener numeros." << endl;
            system("pause");
            break;
        }

		obtenerEntrada("Ingrese la ciudad: ", &city);

        if (searchPeopleByID(*(ct->clients), id) != NULL) {
            cout << "\nCedula ya existente. Ingrese una cedula unica." << endl;
            system("pause");
            break;
        }


        addPerson(ct->clients, id, name, city);
        cout << "\n\t- Cliente agregado exitosamente! -" << endl;
        system("pause");
        clScr();
        break;

    case 2:
        cout << "\n\t - MODIFICAR CLIENTE - \n" << endl;
        tablePeople(*(ct->clients));
        obtenerEntrada("\n\t - Ingrese la cedula del cliente a modificar: ", &id);
        client = searchPeopleByID(*(ct->clients), id); // Declarar y asignar client
        if (client) {
            ct->selectedClient = client;
            int option;
            do {
                clScr();
                cout << "\n\t- Informacion actual del cliente:\n" << endl;
                cout << "Cedula: " << client->ID << ", Nombre y Apellido: " << client->name << endl;
                cout << "\n\t- MODIFICAR CLIENTE -\n";
                cout << "1. Modificar Nombre y Apellido\n";
                cout << "2. Modificar Cedula\n";
                cout << "0. Volver al Menu Anterior\n";
                cout << "Su opcion (0-2): ";
                cin >> option;
                cin.ignore();
                clScr();
                controllerMenuModifyPeople(activo, option, ct);
            } while (option != 0);
        }
        else {
            cout << "No se encontro el cliente con la cedula indicada." << endl;
            system("pause");
            clScr();
        }
        break;

    case 3:
        cout << "\n - ELIMINAR CLIENTE -\n" << endl;
        tablePeople(*(ct->clients));
        obtenerEntrada("\n\t - Ingrese la cedula del cliente a eliminar: ", &id);

        // Verificar si el cliente existe antes de intentar eliminarlo
        client = searchPeopleByID(*(ct->clients), id);
        if (client) {
            cout << "Cedula: " << client->ID << ", Nombre y Apellido: " << client->name << endl;
            if (confirm() == 1) {
                deletePerson(ct->branches, ct->clients, client->ID);
                cout << "\n\t- Cliente eliminado exitosamente! -" << endl;
            }
        }
        else {
            cout << "\n\t- No se encontró el cliente con la cedula indicada." << endl;
        }
        system("pause");
        clScr();
        break;

    case 4:
        consultCustomer(*(ct->clients));
        system("pause");
        clScr();
        break;

    case 5:
        tablePeople(*(ct->clients));
        system("pause");
        clScr();
        break;

    default:
        cout << "Opcion no valida. Intente de nuevo." << endl;
        system("pause");  // espera nuevo \n para tomar;
        break;
    }
    return 1;
}


int operarMenuPrincipal(menuItem** activo, int selec, context* ct) {
    switch (selec) {
    case 0:
        if (!(*activo)->parent) {
            return 0;
        }
        else {
            actualizarMensaje("");
            *activo = (*activo)->parent;
            return 1;
        }
    case 1:
        *activo = menuMantenimiento(*activo);
        break;
    case 2:
        actualizarMensaje("\n\t\tTienda[   ]\tCliente[   ]");
        *activo = menuBilling(*activo);
        break;
    case 3:
        actualizarMensaje("");
        *activo = menuReports(*activo);
        break;
    default:
        actualizarMensaje("La opcion seleccionada no corresponde a una accion. Intente nuevamente.\n");
        break;
    }
    return 1;
}

int operarMenuMantenimiento(menuItem** activo, int selec, context* ct) {
    switch (selec) {
    case 0:
        if (!(*activo)->parent) {
            return 0;
        }
        else {
            actualizarMensaje("");
            *activo = (*activo)->parent;
            return 1;
        }
    case 1:
        *activo = controlProductos(*activo);
        break;
    case 2:
        *activo = controlSucursales(*activo);
        break;
    case 3:
        *activo = menuPeople(*activo);
        break;
    default:
        actualizarMensaje("La opcion seleccionada no corresponde a una accion. Intente nuevamente.\n");
        break;
    }
    return 1;
}




int controladorMenuProductos(menuItem** activo, int selec, context* ct) {
    string entrada = "";
    switch (selec) {
    case 0:
        if (*activo) {
            actualizarMensaje("");
            *activo = (*activo)->parent;
            return 1;
        }
        else {
            return 0;
        }
    case 1:
        actualizarMensaje("");
        createProduct(ct->products);
        break;
    case 2: // modificar
        actualizarMensaje("");
        menuModProduct(*ct->products);
        break;
    case 3: // eliminar
        actualizarMensaje("");
        menuDelProduct(ct->products);
        break;
    case 4: // consultar por codigo
        actualizarMensaje("");
        menuConsultProductByCode(*ct->products);
        break;
    case 5:
        actualizarMensaje("");
        menuConsultProductByDesc(*ct->products);
        break;
    case 6:
        actualizarMensaje("");
        tableProducts(*ct->products);
        break;
    default:
        actualizarMensaje("La opcion seleccionada no corresponde a una accion. Intente nuevamente.\n");
        break;
    }
    system("pause");
    return 1;
}



int controladorMenuSucursales(menuItem** activo, int selec, context* ct) {
    string entrada = "";
    switch (selec) {
    case 0:
        if (*activo) {
            actualizarMensaje("");
            *activo = (*activo)->parent;
            return 1;
        }
        else {
            return 0;
        }
    case 1: // agregar
        actualizarMensaje("");
        createBranch(ct->branches);
        break;
    case 2: // modificar
        actualizarMensaje("");
        *activo = menuModBranchs(*activo);
        break;
    case 3: // eliminar
        actualizarMensaje("");
        menuDeleBranch(ct->branches);
        break;
    case 4: // consultar por codigo
        actualizarMensaje("");
        menuConsultBranchByCode(*ct->branches);
        break;
    case 5: // Consult by description
        actualizarMensaje("");
        *activo = menuConsultBranchByDesc(*activo); // listo
        break;
    case 6:
        actualizarMensaje("");
        tableBranchs(*ct->branches);
        break;
    case 7:
        actualizarMensaje("");
        menuInventory(*ct->branches, *ct->products);
        break;
    default:
        actualizarMensaje("La opcion seleccionada no corresponde a una accion. Intente nuevamente.\n");
        break;
    }
    system("pause");
    return 1;
}


void helperClientInfo(context* ct) {
    string info = "";
    people* client = NULL;
    int selec = 0;

    do {
        clScr();
        obtenerEntrada(header + "\nESTADISTICAS DE CLIENTE\n\t1. MOSTRAR EL RESUMEN DE TODAS SUS FACTURAS ORDENADO\n\t2. MOSTRAR EL RESUMEN DE LOS PRODUCTOS ADQUIRIDOS\n\t0. VOLVER\n" + line + "\n", &info);
        selec = entradaValidar(info);
        switch (selec) {
        case 0:
            return;
            break;
        case 1:
            obtenerEntrada("Ingrese la cedula de identidad del cliente a buscar: ", &info);
            client = searchPeopleByID((*ct->clients), info);
            if (!client) {
                cout << "\n\t-- Cliente no encontrado --\n\n";
                break;
            }
            billsClientResume(*(ct->branches), client);
            break;
        case 2:
            obtenerEntrada("Ingrese la cedula de identidad del cliente a buscar: ", &info);
            client = searchPeopleByID((*ct->clients), info);
            if (!client) {
                cout << "\n\t-- Cliente no encontrado --\n\n";
                break;
            }
            productClientResume((*ct->branches), client);
            break;
        default:
            cout << "La Opcion es invalida.\n";
            break;
        }
        system("pause");
    } while (1);
}

void helperBranchInfo(context* ct) {
    string info = "";
    branch* selected = NULL;
    int selec = 0;


    do {
        clScr();
        obtenerEntrada(header + "\nESTADISTICAS DE SUCURSAL\n\t1. MOSTRAR INFORMACION DE VENTAS\n\t2. MOSTRAR EL RESUMEN DEL INVENTARIO\n\t3. MOSTRAR EL RESUMEN DE COMPRAS DE UN CLIENTE\n\t0. VOLVER\n" + line + "\n", &info);
        selec = entradaValidar(info);
        switch (selec) {
        case 0:
            return;
            break;
        case 1:
            obtenerEntrada("Ingrese el codigo de la sucursal a buscar: ", &info);
            selected = searchBranchByCode(*(ct->branches), info);
            if (!selected) {
                cout << "\n\t-- Sucursal no encontrada --\n\n";
                system("pause");
                break;
            }
            branchUnitsResume(selected);
            system("pause");
            break;
        case 2:
            obtenerEntrada("Ingrese el codigo de la sucursal a buscar: ", &info);
            selected = searchBranchByCode(*(ct->branches), info);
            if (!selected) {
                cout << "\n\t-- Sucursal no encontrada --\n\n";
                system("pause");
                break;
            }
            branchInventoryResume(selected);
            system("pause");
            break;
        case 3:
            obtenerEntrada("Ingrese el codigo de la sucursal a buscar: ", &info);
            selected = searchBranchByCode(*(ct->branches), info);
            if (!selected) {
                cout << "\n\t-- Sucursal no encontrada --\n\n";
                system("pause");
                break;
            }
            obtenerEntrada("Escribe el MES deseado: ", &info);
            branchMonthlyResume(selected, info);
            system("pause");
            break;
        default:
            cout << "La Opcion es invalida.\n\n";
            system("pause");
            break;
        }
    } while (1);

}



int controllerHelperMarketing(menuItem** activo, int selec, context* ct) {
    string input = "";
    switch (selec) {
    case 0:
        if (*activo) {
            actualizarMensaje("");
            *activo = (*activo)->parent;
            return 1;
        }
        else {
            return 0;
        }
    case 1:
        obtenerEntrada("Escribe el MES deseado: ", &input);
        statsMarketingByCode((*ct->branches), input);
        break;
    case 2:
        obtenerEntrada("Escribe el MES deseado: ", &input);
        statsMarketingByBranch((*ct->branches), input);
        break;
    case 3:
        obtenerEntrada("Escribe el MES deseado: ", &input);
        statsMarketingByQty((*ct->branches), (*ct->clients), selectProductByCode(*ct->products), input);
        break;
    case 4:
        obtenerEntrada("Escribe el MES deseado: ", &input);
        statsMarketingByClientBill((*ct->branches), (*ct->clients), selectProductByCode(*ct->products), input);
        break;
    case 5:
        obtenerEntrada("Escribe el MES deseado: ", &input);
        statsMarketingAll(*ct->branches,  input);
        break;
    }
    system("pause");
    return 1;
}



int controllerMenuReports(menuItem** activo, int selec, context* ct) {
	string city = "";
	string month = "";
	product *sc = NULL;
    switch (selec) {
		case 0:
			if (*activo) {
				actualizarMensaje("");
				*activo = (*activo)->parent;
				return 1;
			}
			else {
				return 0;
			}
		case 1:
			helperClientInfo(ct);
			break;
		case 2:
			helperBranchInfo(ct);
			break;
		case 3:
			*activo = helperMarketing(*activo);
            return 1;
    }

	system("pause");
    return 1;
}



menuItem* controlSucursales(menuItem* parent) {
    menuItem* m = new menuItem;
    m->encabezado = header + "\tCONTROL DE SUCURSALES\n\t1. AGREGAR\n\t2. MODIFICAR\n\t3. ELIMINAR\n\t4. CONSULTAR POR CODIGO\n\t5. CONSULTAR POR DESCRIPCION\n\t6. MOSTRAR TODAS LAS SUCURSALES\n\t7. MOSTRAR INVENTARIO\n\t0. SALIR\n" + line + "\nRealizado por Carlos Galiño, Andrés de Quintal y Manuel Negrón\n" + line;
    m->parent = parent->parent;
    m->comportamiento = controladorMenuSucursales;
    return m;
}


menuItem* controlProductos(menuItem* parent) {
    menuItem* m = new menuItem;
    m->encabezado = header + "\n\tCONTROL DE PRODUCTOS\n\t1. AGREGAR\n\t2. MODIFICAR\n\t3. ELIMINAR\n\t4. CONSULTAR POR CODIGO\n\t5. CONSULTAR POR DESCRIPCION\n\t6. MOSTRAR PRODUCTOS\n\t0. SALIR\n" + line + "\nRealizado por Carlos Galiño, Andrés de Quintal y Manuel Negrón\n" + line;
    m->parent = parent;
    m->comportamiento = controladorMenuProductos;
    return m;
}


menuItem* menuMantenimiento(menuItem* parent) {
    menuItem* m = new menuItem;
    m->encabezado = header + "\t\tMANTENIMIENTO\n" + line + "\n\tOPCIONES DE MENU\n\t1. PRODUCTOS\n\t2. SUCURSALES\n\t3. PERSONAS\n\t0. REGRESAR\n" + line;
    m->parent = parent;
    m->comportamiento = operarMenuMantenimiento;
    return m;

}

menuItem* menuPrincipal() {
    menuItem* m = new menuItem;
    m->encabezado = header + "\tMENU PRINCIPAL\n\t1. MANTENIMIENTO\n\t2. FACTURACION\n\t3. REPORTES\n\t0. SALIR\n" + line + "\nRealizado por Carlos Galiño, Andrés de Quintal y Manuel Negrón;\n" + line;
    m->parent = NULL;
    m->comportamiento = operarMenuPrincipal;
    return m;
}


menuItem* menuConsultBranchByDesc(menuItem* parent) {
    menuItem* m = new menuItem;
    m->encabezado = line + "\n\tCONSULTAR SUCURSAL POR DESCRIPCION\n\t1. ESTADO\n\t2. CIUDAD\n\t0. VOLVER A MENU ANTERIOR.\n" + line + "\nSu opcion (0-2): ";
    m->parent = parent;
    m->comportamiento = controllerConsultBranchByDesc;
    return m;
}

menuItem* menuModBranchs(menuItem* parent) {
    menuItem* m = new menuItem;
    m->encabezado = line + "\n\tMODIFICAR\n\t1. NOMBRE\n\t2. ESTADO\n\t3. CIUDAD\n\t4. DIRECCION\n\t5. TELEFONO\n\t6. CODIGO\n\t0. VOLVER A MENU ANTERIOR.\n" + line + "\nSu opcion (0-6): ";
    m->parent = parent;
    m->comportamiento = controllerConsultBranchByDesc;
    return m;
}

menuItem* menuPeople(menuItem* parent) {
    menuItem* m = new menuItem;
    m->encabezado = header + "\nMANTENIMIENTO PERSONAS\n\t1. AGREGAR CLIENTE\n\t2. MODIFICAR CLIENTE\n\t3. ELIMINAR CLIENTE\n\t4. CONSULTAR\n\t5. MOSTRAR TODOS LOS CLIENTES\n\t0. VOLVER AL MENU ANTERIOR.\n" + line + "\nSu opcion (0-5): \n";
    m->parent = parent;
    m->comportamiento = controllerMenuPeople;
    return m;
}

menuItem* menuModifyPeople(menuItem* parent) {
    menuItem* m = new menuItem;
    m->encabezado = header + "\n\t\nMANTENIMIENTO PERSONAS\n\n\t1. AGREGAR CLIENTE\n\t2. MODIFICAR CLIENTE\n\t3. ELIMINAR CLIENTE\n\t4. CONSULTAR\n\t5. MOSTRAR TODOS LOS CLIENTES\n\t0. VOLVER AL MENU ANTERIOR.\n\n" + line + "\nSu opcion (0-5): \n" + line + "\nRealizado por Carlos Galiño, Andrés de Quintal y Manuel Negrón\n" + line;
    m->parent = parent;
    m->comportamiento = controllerMenuModifyPeople;
    return m;
}

menuItem* menuBilling(menuItem* parent) {
    menuItem* m = new menuItem;
    m->encabezado = header + "\n\t\t2.FACTURACION\n" + line + "\n\t1.SELECCIONAR TIENDA\n\t2.SELECCIONAR CLIENTE\n\t3.AGREGAR PRODUCTOS\n\t4.MOSTRAR FACTURA\n\t5.ELIMINAR FACTURA\n\t6.MOSTRAR RESUMEN FACTURAS\n\t0.VOLVER A MENU ANTERIOR.\n" + line + "\nSu opcion(0 - 6) : ";
    m->parent = parent;
    m->comportamiento = controllerMenuBilling;
    return m;
}

menuItem* menuReports(menuItem* parent) {
    menuItem* m = new menuItem;
    m->encabezado = header + "\n\tREPORTES\n\t1. INGRESAR CLIENTE POR CEDULA\n\t2. INGRESAR TIENDA POR CODIGO\n\t3. MERCADEO\n\t0. VOLVER AL MENU\n" + line;
    m->parent = parent;
    m->comportamiento = controllerMenuReports;
    return m;
}

menuItem* helperMarketing(menuItem* parent) {
    menuItem* m = new menuItem;
    m->encabezado = header + "\n\tREPORTES DE MERCADEO\n\t1. ESTADISTICAS DE VENTAS ORDENADAS POR CODIGO\n\t2. ESTADISTICAS DE VENTAS ORDENADAS POR TIENDA\n\t3. VER ESTADISTICAS DE PRODUCTO POR SUCURSAL\n\t4. VER MONTO TOTAL DE CADA CLIENTE\n\t5. VER INFORMACION DE INGRESOS POR TIENDA\n\t0. VOLVER AL MENU\n" + line;
    m->parent = parent;
    m->comportamiento = controllerHelperMarketing;
    return m;
}


void run() {
    int activo = 1;
    int val = 0;

    string entrada = "";
    menuItem* menuActivo = menuPrincipal();

    branch* branches = NULL;
    product* products = NULL;
    people* clients = NULL;

    readProducts(&products);
    readBranches(&branches);
    readInventory(branches, products);
    readClients(&clients);
    readBills(&branches, &clients);

    context* ct = newContext(&products, &branches, &clients); // Almacenador
    while (activo) {
        clScr();
        print(Mensajero->data);
        if (menuActivo) {
            obtenerEntrada(menuActivo->encabezado, &entrada);
            val = entradaValidar(entrada);
            activo = menuActivo->comportamiento(&menuActivo, val, ct);
        }
        else {
            activo = 0;
        }
    }

    saveProducts(products);
    saveBranchs(branches);
    saveProductsOfBranch(branches);
    saveClients(clients);
    saveBills(branches);
}


int main() {
    setlocale(LC_ALL, "es_ES.UTF-8");
    run();
}

/*
MINI TODO:
- Cuando se borra cliente borrar facturas
    - Revisar TODAS las de reportes:
    en sucursales 3.1 tiene que imprimirse la existencia
*/

