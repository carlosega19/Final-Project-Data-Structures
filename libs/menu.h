/*
    In this file are all the functions to interact with the user.
*/
#ifndef MENU_H
#define MENU_H

#include <iostream>
#include <iomanip>
#include "branch.h"
#include "product.h"
#include "helper.h"
using namespace std;
/*------ MENU MANAGMENT ------*/
int lineWidth = 120;
string line(lineWidth, '-');



void printCreators() {
    string names = "REALIZADO POR:    Andres De Quintal   Y   Carlos Gali�o";
    cout << setw((lineWidth + names.length()) / 2) << names << endl;
    cout << line << endl;
}

void menuHeader() {
    string title = "SISTEMA DE INVENTARIO Y FACTURACION";
    cout << line << endl;
    cout << setw((lineWidth + title.length()) / 2) << title << endl;
    cout << line << endl;
}

// MAIN MENU
void menu() {
	system("cls");
	// Ancho total deseado de la l?nea
	string subtitle = "MENU PRINCIPAL";
	string op1 = "1. MANTENIMIENTO";
	string op2 = "2. FACTURACION";
	string op3 = "3. REPORTES";
	string op0 = "0. SALIR.";
	string msg = "Su opcion (0-3) : _|";

	menuHeader();
	cout << setw((lineWidth + length(subtitle)) / 2) << subtitle << endl;
	cout << line << endl;
	cout << setw((lineWidth + length(op1)) / 2) << op1 << endl;
	cout << setw((lineWidth + length(op2)) / 2) << op2 << endl;
	cout << setw((lineWidth + length(op3)) / 2) << op3 << endl;
	cout << setw((lineWidth + length(op0)) / 2) << op0 << endl;
	cout << setw((lineWidth + length(msg)) / 2) << msg << endl;
	cout << line << endl;
	printCreators();
}

// MANTENIENCE
void menuMant() {
	system("cls");
	menuHeader();
	string subtitle = "1. MANTENIMIENTO";
	string op1 = "1. PRODUCTOS";
	string op2 = "2. SUCURSALES";
	string op3 = "3. PERSONAS";
	string op0 = "0. VOLVER.";
	string msg = "Su opcion (0-3) : _|";

	cout << setw((lineWidth + length(subtitle)) / 2) << subtitle << endl;
	cout << line << endl;
	cout << setw((lineWidth + length(op1)) / 2) << op1 << endl;
	cout << setw((lineWidth + length(op2)) / 2) << op2 << endl;
	cout << setw((lineWidth + length(op3)) / 2) << op3 << endl;
	cout << setw((lineWidth + length(op0)) / 2) << op0 << endl;
	cout << setw((lineWidth + length(msg)) / 2) << msg << endl;
	cout << line << endl;
}

// MATENIENCE__PRODUCTS
void menuMantProds() {
	system("cls");
	menuHeader();

	string subtitle = "1.1 MANTENIMIENTO PRODUCTOS";
	string op1 = "1.1. 1. AGREGAR";
	string op2 = "1.1. 2. MODIFICAR";
	string op3 = "1.1. 3. ELIMINAR";
	string op4 = "1.1. 4. CONSULTA POR CODIGO";
	string op5 = "1.1. 5. CONSULTA POR DESCRIPCION";
	string op6 = "1.1. 6. MOSTRAR TODOS LOS PRODUCTOS";
	string op0 = "0. VOLVER A MENU ANTERIOR.";
	string msg = "Su opcion (0-6) : _|";


	cout << setw((lineWidth + length(subtitle)) / 2) << subtitle << endl;
	cout << line << endl;
	cout << setw((lineWidth + length(op1)) / 2) << op1 << endl;
	cout << setw((lineWidth + length(op2)) / 2) << op2 << endl;
	cout << setw((lineWidth + length(op3)) / 2) << op3 << endl;
	cout << setw((lineWidth + length(op4)) / 2) << op4 << endl;
	cout << setw((lineWidth + length(op5)) / 2) << op5 << endl;
	cout << setw((lineWidth + length(op6)) / 2) << op6 << endl;
	cout << setw((lineWidth + length(op0)) / 2) << op0 << endl;
	cout << setw((lineWidth + length(msg)) / 2) << msg << endl;
	cout << line << endl;
}

void optionsModProduct(product*selected) {
    system("cls");
    menuHeader();
    string subtitle = "MODIFICAR";
    string op1 = "1. NOMBRE";
    string op2 = "2. DESCRIPCION";
    string op3 = "3. CODIGO";
    string op0 = "0. VOLVER A MENU ANTERIOR.";
    string msg = "Su opcion (0-5) : _|";

    cout << setw((lineWidth + length(subtitle)) / 2) << subtitle << endl;
    cout << line << endl;
    cout << setw((lineWidth + length(op1)) / 2) << op1 << endl;
    cout << setw((lineWidth + length(op2)) / 2) << op2 << endl;
    cout << setw((lineWidth + length(op3)) / 2) << op3 << endl;
    cout << setw((lineWidth + length(op0)) / 2) << op0 << endl;
    cout << setw((lineWidth + length(msg)) / 2) << msg << endl;
    cout << line << endl;
    cout << "\n\n\tSUCURSAL ENCONTRADA: \n";
    cout << "\n\t - " << selected->name << " [" << selected->code << "]";
    cout << "\n\t\t ~ Descripcion: " << selected->description;
    cout << "\n\n\tIngresa la opcion a modificar: ";
}

/*--------------- BRANCHES AND PRODUCTS MENUS ---------------*/
void createProduct(product**P , product**L){
    string code , name , description;
    bool invalidCode = true;
    cin.ignore();
    do // IF THE CODE IS ALREADY TAKES, THE USER IS OBLIGATED TO TRY ANOTHER CODE
    {
        cout << "\n\t- Escribe el CODIGO del nuevo PRODUCTO: ";
        getline(cin, code);
        invalidCode = searchProductByCode(*P , code);
        if (invalidCode) cout << "\n\t\t-- CODIGO YA EXISTENTE --\n\n";
    } while (invalidCode);

    cout << "\n\t- Escribe el NOMBRE del nuevo PRODUCTO: ";
    getline(cin, name);
    cout << "\n\t- Escribe la DESCRIPCION del nuevo PRODUCTO: ";
    getline(cin, description);
    if (cin.fail())
    {
        cin.clear();
        cin.ignore();
    }
    if (!isValid(code) || !isValid(name) || !isValid(description)) {
        cout << " \n\n\t\t-- CAMPOS LLENADOS INCORECTAMENTE --\n\n"; 
    }
    else
    {
        cout << "\n\n\t\t-- PRODUCTO AGREGADO --\n\n";
        addProduct(P , L , code , name , description , 0 , 0 , 0);
    }
    system("pause");
}
/*  Functions to see products*/
void printProducts(product*P) {
    if (!P) return;
    cout << "\n\t - " << P->name << " [" << P->code << "]";
    printProducts(P->next);
}

void showAllProducts(product*P) {
    system("cls");
    menuHeader();
    string subtitle = "LISTA DE PRODUCTOS";
    cout << setw((lineWidth + length(subtitle)) / 2) << subtitle << endl;
    cout << line << endl;
    printProducts(P);
    cout << "\n\n";
}

void headerProducts(string line) {
    
    cout << line << endl;
    string subtitle = "LISTA DE PRODUCTOS";
    cout << setw((length(line) + length(subtitle)) / 2) << subtitle << endl;
    cout << line << endl;
    cout << setw(10) << internal << "CODIGO"
        << setw(25) << internal << "NOMBRE"
        << setw(35) << internal << "DESCRIPCION"<<endl;
    cout << line << endl;
}

void printProductsInTable(product* P) {
    cout << setw(10) << internal << P->code
        << setw(25) << internal << P->name<<"   " 
        << setw(35) << internal << P->description << endl;
}
/*--------------------------------------------------------------------------------------------*/
product* selectProductByCode(product* P) {
    string codeSelect;
    showAllProducts(P);
    cin.ignore();
    cout << "\n\n\n\tIngrese el codigo del producto entre []: ";
    getline(cin, codeSelect);
    if (codeSelect.empty() || codeSelect == "0") return NULL;
    return searchProductByCode(P, codeSelect);
}

void menuModProduct(product* P) {
    system("cls");
    menuHeader();
    string subtitle = "CONSULTAR SUCURSAL POR DESCRIPCION";
    string op0 = "0. VOLVER A MENU ANTERIOR.";
    cout << setw((lineWidth + length(subtitle)) / 2) << subtitle << endl;
    cout << setw((lineWidth + length(op0)) / 2) << op0 << endl;
    cout << line << endl;
    product* selected = selectProductByCode(P); // THE USER SELECT A PRODUCT
    if (!selected)
    {
        cout << "\n\n\t\t\t-- PRODUCTO NO SELECCIONADO --\n\n";
    }
    else {
        int op;
        string userEntry;
        float userPrice;
        do
        {
            optionsModProduct(selected);
            cin >> op;
            cin.ignore();
            if (cin.fail())
            {
                cin.clear();
                cin.ignore();
                op = -1;
            }
            switch (op)
            {
                case 1:
                    cout << "Nombre anterior: " << selected->name << endl;
                    fflush(stdin);
                    cout << "Nuevo nombre: ";
                    getline(cin, userEntry);
                    cout << "\n\tSeguro que desea MODIFICAR? \n\t(1) CONFIRMAR\n\t(0) Cancelar\n\t=> ";
                    cin >> op;
                    if (op == 1)
                    {
                        selected->name = userEntry;
                    }
                    else op = -1;
                    break;
                case 2:
                    cout << "Descripcion anterior: " << selected->description << endl;
                    fflush(stdin);
                    cout << "Nueva descripcion: ";
                    getline(cin, userEntry);
                    cout << "\n\tSeguro que desea MODIFICAR? \n\t(1) CONFIRMAR\n\t(0) Cancelar\n\t=> ";
                    cin >> op;
                    if (op == 1)
                    {
                        selected->description = userEntry;
                    }
                    else op = -1;
                    break;
                case 3:
                {
                    bool invalidCode = true;
                    cout << "Codigo anterior: " << selected->code << endl;
                    fflush(stdin);
                    do
                    {
                        cout << "Nuevo codigo: ";
                        getline(cin, userEntry);
                        invalidCode = searchProductByCode(P , userEntry);
                        if (invalidCode)
                        {
                        cout << "\n\t\t\t-- CODIGO YA EXISTENTE --\n\n";
                        }
                    } while (invalidCode);
                    cout << "\n\tSeguro que desea MODIFICAR? \n\t(1) CONFIRMAR\n\t(0) Cancelar\n\t=> ";
                    cin >> op;
                    if (op == 1)
                    {
                        selected->code = userEntry;
                    }
                    else op = -1;
                    break;
                }
            }
        fflush(stdin);
        } while (op != 0);
    }
    system("pause");
}

void menuConsultProductByCode(product* B) {
    system("cls");
    menuHeader();
    string subtitle = "CONSULTAR PRODUCTO POR CODIGO";
    cout << setw((lineWidth + length(subtitle)) / 2) << subtitle << endl;
    cout << line << endl;
    product* selected = selectProductByCode(B);
    if (selected)
    {
        system("cls");
        menuHeader();
        cout << setw((lineWidth + length(subtitle)) / 2) << subtitle << endl;
        cout << line << endl;
        cout << "\n\tPRODUCTO ENCONTRADO: \n";
        cout << "\n\t - " << selected->name << " [" << selected->code << "]";
        cout << "\n\t\t ~ Descripcion: " << selected->description << "\n\n";
        system("pause");
    }
    else {
        cout << "\n -- PRODUCTO INEXISTENTE --\n\n\n";
    }
}

void menuConsultProductByType(product* B) { // CAMBIAR EL "TYPE"
    system("cls");
    menuHeader();
    string userInput;
    string subtitle = "CONSULTAR PRODUCTOS POR DESCRIPCION";
    string op0 = "0. VOLVER A MENU ANTERIOR.";
    cout << setw((lineWidth + length(subtitle)) / 2) << subtitle << endl;
    cout << line << endl;
    cout << setw((lineWidth + length(op0)) / 2) << op0 << endl;
    cout << line << endl;
    cin.ignore();
    cout << "\n\tIngresa la descripcion: ";
    getline(cin, userInput);
    if (userInput == "0") return;

    cout << "\n\tPRODUCTOS ENCONTRADOS: \n";
    product* selected = searchProductByType(B, userInput);
    if (!selected) {
        cout << "\n\n\t\tNINGUNO...\n\n";
        return;
    }
    headerProducts(line);
    while (selected)
    {
        printProductsInTable(selected);
        selected = searchProductByType(selected->next, userInput);
    }
    cout << line << "\n\n\t";
    system("pause");
}

void menuConsultProductByDesc(product* B) {
    string subtitle = "CONSULTAR PRODUCTO POR DESCRIPCION";
    string op1 = "1. DESCRIPCION";
    string op0 = "0. VOLVER A MENU ANTERIOR.";
    int op;
    do
    {
        system("cls");
        menuHeader();
        cout << setw((lineWidth + length(subtitle)) / 2) << subtitle << endl;
        cout << line << endl;
        cout << setw((lineWidth + length(op1)) / 2) << op1 << endl;
        cout << setw((lineWidth + length(op0)) / 2) << op0 << endl;
        cout << line << endl;
        cin >> op;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore();
            op = -1;
        }
        switch (op)
        {
            case 1:
                menuConsultProductByType(B);
                op = 0;
                break;
        }
    } while (op != 0);
}

void menuDelProduct(product**P , product**L) {
    system("cls");
    menuHeader();
    string subtitle = "ELIMINAR PRODUCTO";
    string op0 = "0. VOLVER A MENU ANTERIOR.";
    cout << setw((lineWidth + length(subtitle)) / 2) << subtitle << endl;
    cout << setw((lineWidth + length(op0)) / 2) << op0 << endl;
    cout << line << endl;
    product* selected = selectProductByCode(*P);
    if (selected)
    {
        cout << "\n\t - " << selected->name << " [" << selected->code << "]";
        cout << "\n\t\t ~ Descripcion: " << selected->description << "\n\n";
        cout << "\n\tSeguro que desea ELIMINAR? \n\t(1) CONFIRMAR\n\t(0) Cancelar\n\t=> ";
        int op;
        cin >> op;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore();
            op = -1;
        }
        if (op == 1)
        {
            deleteProduct(P , L , selected->code);
            cout << "\n\n\t\t-- PRODUCTO ELIMINADO --\n\n";
        }
    }
    system("pause");
}

#endif // MENU_H