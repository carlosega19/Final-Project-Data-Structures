#ifndef REPORTS_H
#define REPORTS_H

#include <iostream>
#include <cstring> 
using namespace std;

// Estructura para detalle de productos en una factura
struct detail {
    string code;
    string name;
    int amount;
    int price;
    detail* next;
};

// Estructura para factura
struct bill {
    string code;
    string clientId;
    string date;
    int total;
    detail* detailBill;
    bill* next;
    bill* prev;
};

struct dipolo
{
    bill*first;
    bill*last;
};

// Estructura para sucursal
struct branch {
    string code;
    string name;
    string city;
    string state;
    string address;
    string tlf;
    branch* next;
    // Lista de facturas para esta sucursal
    dipolo* bills; // bills es un puntero a dipolo
};


// Estructura para personas
struct people {
    string ID;
    string name;
    people* next;
};

// Función para buscar una persona por su ID
people* searchPeopleByID(people* P, string id) {
    while (P != NULL) {
        if (P->ID == id) {
            return P;
        }
        P = P->next;
    }
    return NULL;
}

// Función para buscar una factura por su código en una lista de facturas
bill* searchBillByCode(bill* B, string code) {
    while (B != NULL) {
        if (B->code == code) {
            return B;
        }
        B = B->next;
    }
    return NULL;
}

// Función para imprimir una línea de guiones
void printDashesLine(int length) {
    for (int i = 0; i < length; ++i) {
        cout << "-";
    }
    cout << endl;
}

// Función para imprimir una línea de asteriscos
void printAsterisksLine(int length) {
    for (int i = 0; i < length; ++i) {
        cout << "*";
    }
    cout << endl;
}

//3.1.1 Mostrar Resumenes de facturas 
void generateReports(branch* branchList, people* peopleList, string personID) {
    people* client = searchPeopleByID(peopleList, personID);
    if (!client) {
        cout << "Cliente no encontrado.\n";
        return;
    }

    printDashesLine(97);
    cout << "SISTEMA DE INVENTARIO Y FACTURACION\n";
    printDashesLine(97);
    cout << "3.1.1 Resumen de facturas\n";
    cout << "CLIENTE [ CI: " << client->ID << " " << client->name << " ]\n";
    cout << "                                FACTURA      FECHA       MONTO         SUCURSAL\n";
    printAsterisksLine(97);

    branch* currentBranch = branchList;
    while (currentBranch) {
        dipolo* currentDipolo = currentBranch->bills;
        bill* currentBill = currentDipolo->first;
        while (currentBill) {
            if (currentBill->clientId == personID) {
                cout << "                                   " << currentBill->code << "    " << currentBill->date
                        << "    " << currentBill->total << "    " << currentBranch->name << "\n";
            }
            currentBill = currentBill->next;
        }
        currentBranch = currentBranch->next;
    }

    printAsterisksLine(97);
    cout << "Pulse <0> para volver al menú anterior\n";
    printDashesLine(97);
    pause();
}

//3.1.2 Mostrar Productos Adquiridos por un cliente
void showProductSummary(branch* branchList, people* peopleList, string personID) {
    people* client = searchPeopleByID(peopleList, personID);
    if (!client) {
        cout << "Cliente no encontrado.\n";
        return;
    }

    detail* productDetails = NULL;
    bool found = false;

    // Recorre la lista de sucursales
    branch* currentBranch = branchList;
    while (currentBranch) {
        dipolo* currentDipolo = currentBranch->bills;
        bill* currentBill = currentDipolo->first;
        while (currentBill) {
            if (currentBill->clientId == personID) {
                found = true;

                // Recorre los detalles de la factura actual
                detail* currentDetail = currentBill->detailBill;
                while (currentDetail) {
                    // Agrega el detalle del producto al inicio de la lista
                    detail* newDetail = new detail;
                    newDetail->code = currentDetail->code;
                    newDetail->name = currentDetail->name;
                    newDetail->amount = currentDetail->amount;
                    newDetail->price = currentDetail->price;
                    newDetail->next = productDetails;
                    productDetails = newDetail;

                    currentDetail = currentDetail->next;
                }
            }
            currentBill = currentBill->next;
        }
        currentBranch = currentBranch->next;
    }

    if (!found) {
        cout << "No se encontraron facturas para este cliente.\n";
    } else {
        printDashesLine(97);
        cout << "SISTEMA DE INVENTARIO Y FACTURACION\n";
        printDashesLine(97);
        cout << "3.1.2 Resumen de productos adquiridos\n";
        cout << "CLIENTE [ CI: " << client->ID << " " << client->name << " ]\n";
        printAsterisksLine(97);
        cout << left << setw(15) << "CÓDIGO" << setw(20) << "DESCRIPCION" << setw(10) << "CANT" << setw(10) << "PRECIO\n";
        printAsterisksLine(97);

        // Imprimir los detalles de los productos adquiridos
        detail* current = productDetails;
        while (current) {
            cout << left << setw(15) << current->code << setw(20) << current->name
                    << setw(10) << current->amount << setw(10) << current->price << endl;
            detail* temp = current;
            current = current->next;
            delete temp; 
        }
        printDashesLine(97);
    }

    pause();
}

#endif // BRANCH_H