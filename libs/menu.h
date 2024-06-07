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

void optionsModBranch(branch*selected){
    system("cls");
    menuHeader();
    string subtitle = "MODIFICAR";
	string op1 = "1. NOMBRE";
	string op2 = "2. ESTADO";
	string op3 = "3. CIUDAD";
	string op4 = "4. DIRECCION";
	string op5 = "5. TELEFONO";
    string op6 = "6. CODIGO";
	string op0 = "0. VOLVER A MENU ANTERIOR.";
	string msg = "Su opcion (0-5) : _|";

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
    cout << "\n\tSUCURSAL ENCONTRADA: \n";
    cout << "\n\t - " << selected->name << " [" << selected->code << "]";
    cout << "\n\t\t ~ Direccion: " << selected->city << ", " << selected->state << ", " << selected->address;
    cout << "\n\t\t ~ Telefono: " << selected->tlf << "\n\n";
    cout << "\nIngresa la opcion a modificar: ";
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

void tableProducts(product* P) {
    cout << "\n\n";
    string line = "|-------------------------------------------------------------------------------|";
    headerProducts(line);
    while (P)
    {
        printProductsInTable(P);
        P = P->next;
    }
    cout << line << "\n\n\t";
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
/*--------------------------------------------------------------------------------------------------------------------*/
/*----------- BRANCHES -----------*/
void menuMantBranchs(){
    system("cls");
	menuHeader();
    string subtitle = "1.1 MANTENIMIENTO SUCURSALES";
	string op1 = "1.2.1. AGREGAR";
	string op2 = "1.2.2. MODIFICAR";
	string op3 = "1.2.3. ELIMINAR";
	string op4 = "1.2.4. CONSULTA POR CODIGO";
	string op5 = "1.2.5. CONSULTA POR DESCRIPCION";
	string op6 = "1.2.6. MOSTRAR TODAS LAS SUCURSALES";
	string op7 = "1.2.7. INVENTARIO";
	string op0 = "0. VOLVER A MENU ANTERIOR.";
	string msg = "Su opcion (0-7) : _|";

    cout << setw((lineWidth + length(subtitle)) / 2) << subtitle << endl;
	cout << line << endl;
	cout << setw((lineWidth + length(op1)) / 2) << op1 << endl;
	cout << setw((lineWidth + length(op2)) / 2) << op2 << endl;
	cout << setw((lineWidth + length(op3)) / 2) << op3 << endl;
	cout << setw((lineWidth + length(op4)) / 2) << op4 << endl;
	cout << setw((lineWidth + length(op5)) / 2) << op5 << endl;
	cout << setw((lineWidth + length(op6)) / 2) << op6 << endl;
	cout << setw((lineWidth + length(op7)) / 2) << op7 << endl;
	cout << setw((lineWidth + length(op0)) / 2) << op0 << endl;
	cout << setw((lineWidth + length(msg)) / 2) << msg << endl;
	cout << line << endl;
}

void createBranch(branch**B , branch**L , unordered_map<string, branch*> &tableB) {
	string name , city , state , address , tlf , code;
    bool invalidCode = true;
    cin.ignore();
    do
    {
        cout << "\n\t- Escribe el CODIGO de la nueva SUCURSAL: ";
        getline(cin, code);
        fflush(stdin);
        invalidCode = searchBranchByCode(*B, code);
        if (invalidCode)
        {
            cout << "\n\t\t -- CODIGO YA EXISTENTE -- \n\n";
        }
    } while (invalidCode);

    fflush(stdin);
	cout << "\n\t- Escribe el NOMBRE de la nueva SUCURSAL (max.30): "; 
	getline(cin ,name);
	fflush(stdin);
	cout << "\n\t- Escribe el ESTADO de la nueva SUCURSAL (max.30): ";  
	getline(cin, state);
	fflush(stdin);
	cout << "\n\t- Escribe la CIUDAD de la nueva SUCURSAL (max.30): ";  
	getline(cin, city);
	fflush(stdin);
	cout << "\n\t- Escribe la DIRECCION de la nueva SUCURSAL (max.30): ";  
	getline(cin, address);
	fflush(stdin);
	cout << "\n\t- Escribe el NUMERO TELEFONICO de la nueva SUCURSAL - (xxx) xxxxxxx: ";  
	getline(cin, tlf);
	fflush(stdin);

	if (!isValid(name) || !isValid(city) || !isValid(state) || !isValid(address) || !isValid(address) || !isValid(code)) {
		cout << " \n\n\t\t-- CAMPOS LLENADOS INCORRECTAMENTE --\n\n"; //Provisional
	}
	else
	{
		addBranch(B, L, code, name, city, state, address, tlf, tableB); 
        cout << "\n\t\t-- SUCURSAL AGREGADA --\n\n\n\t";
	}
    system("pause");
}

void printBranchs(branch*B) {
	if (!B) return;
	cout << "\n\t - " << B->name << " [" << B->code<<"]\n";
	//cout << "\n\t\t ~ Direccion: "<<B->city<<", "<<B->state<<", "<<B->address;
	//cout << "\n\t\t ~ Telefono: "<<B->tlf<<"\n\n";
	printBranchs(B->next);
}

void headerBranchs(const string& line) {
    cout << line << endl;
    string subtitle = "LISTA DE SUCURSALES";
    cout << setw((line.length() + subtitle.length()) / 2) << subtitle << endl;
    cout << line << endl;
    cout << setw(9) << "CODIGO"
        << setw(15) << "NOMBRE"
        << setw(15) << "CIUDAD"
        << setw(10) << "ESTADO"
        << setw(15) << "TELEFONO"
        << setw(50) << "DIRECCION" << endl;
    cout << line << endl;
}

void printBranchsInTable(branch* B) {
    cout << setw(9) << B->code
        << setw(15) << B->name
        << setw(15) << B->city
        << setw(10) << B->state
        << setw(15) << B->tlf
        << "   " << setw(50) << B->address << endl;
}

void tableBranchs(branch* B) {
    string line = "|----------------------------------------------------------------------------------------------------------------------|";
    headerBranchs(line);
    while (B)
    {
        printBranchsInTable(B);
        B = B->next;
    }
    
    cout << line << "\n\n\t";
}

branch* selectBranchByCode(branch* B) {
    string codeSelect;
    printBranchs(B);
    cin.ignore();
    cout << "\n\n\n\tIngrese el codigo de la sucursal: ";
    getline(cin, codeSelect);
    if (codeSelect.empty() || codeSelect == "0") return NULL;  
    return searchBranchByCode(B, codeSelect);
}


void menuModBranch(branch *B){
    branch* selected = selectBranchByCode(B);
    if (!selected)
    {
        cout << "\n\n\t\t-- SUCURSAL NO SELECCIONADA --\n\n";
        system("pause");
    }
    else{
        int op;
        string userEntry = "ABC";
        do
        {
            optionsModBranch(selected);
            cin >> op;
            cin.ignore();
            switch (op)
            {
                case 1:
                    cout<<"Nombre anterior: "<<selected->name<<endl;
                    cout<<"Nuevo nombre: ";
                    if (isValid(userEntry))
                    {
                        getline(cin, userEntry);
                        cout << "\n\tSeguro que desea modificar? \n\t(1) CONFIRMAR\n\t(0) Cancelar\n\t=> ";
                        cin >> op;
                        if (cin.fail())
                        {
                            cin.clear();
                            cin.ignore();
                        }
                        if (op == 1)
                        {
                            selected->name = userEntry;
                        }
                        else op = -1;
                    }
                    else {
                        cout << "\n\n\t\t-- DATO INVALIDO --\n\n\t";
                    }
                    
                    break;
                case 2:
                    cout<<"Estado anterior: "<<selected->state<<endl;
                    cout<<"Nuevo estado: ";
                    if (isValid(userEntry))
                    {
                        getline(cin, userEntry);
                        cout << "\n\tSeguro que desea modificar? \n\t(1) CONFIRMAR\n\t(0) Cancelar\n\t=> ";
                        cin >> op;
                        if (cin.fail())
                        {
                            cin.clear();
                            cin.ignore();
                        }
                        if (op == 1)
                        {
                            selected->state = userEntry;
                        }
                        else op = -1;
                    }
                    else {
                        cout << "\n\n\t\t-- DATO INVALIDO --\n\n\t";
                    }
                    
                    break;
                case 3:
                    cout<<"Ciudad anterior: "<<selected->city<<endl;
                    cout<<"Nueva ciudad: ";
                    if (isValid(userEntry))
                    {
                        getline(cin, userEntry);
                        cout << "\n\tSeguro que desea modificar? \n\t(1) CONFIRMAR\n\t(0) Cancelar\n\t=> ";
                        cin >> op;
                        if (cin.fail())
                        {
                            cin.clear();
                            cin.ignore();
                        }
                        if (op == 1)
                        {
                            selected->city = userEntry;
                        }
                        else op = -1;
                    }
                    else {
                        cout << "\n\n\t\t-- DATO INVALIDO --\n\n\t";
                    }
                    
                    break;
                case 4:
                    cout<<"Direccion anterior: "<<selected->address<<endl;
                    cout<<"Nueva direccion: ";
                    if (isValid(userEntry))
                    {
                        getline(cin, userEntry);
                        cout << "\n\tSeguro que desea modificar? \n\t(1) CONFIRMAR\n\t(0) Cancelar\n\t=> ";
                        cin >> op;
                        if (cin.fail())
                        {
                            cin.clear();
                            cin.ignore();
                        }
                        if (op == 1)
                        {
                            selected->address = userEntry;
                        }
                        else op = -1;
                    }
                    else {
                        cout << "\n\n\t\t-- DATO INVALIDO --\n\n\t";
                    }
                    
                    break;
                case 5:
                    cout<<"Telefono anterior: "<<selected->tlf<<endl;
                    cout<<"Nuevo telefono: ";
                    if (isValid(userEntry))
                    {
                        getline(cin, userEntry);
                        cout << "\n\tSeguro que desea modificar? \n\t(1) CONFIRMAR\n\t(0) Cancelar\n\t=> ";
                        cin >> op;
                        if (cin.fail())
                        {
                            cin.clear();
                            cin.ignore();
                        }
                        if (op == 1)
                        {
                            selected->tlf = userEntry;
                        }
                        else op = -1;
                    }
                    else {
                        cout << "\n\n\t\t-- DATO INVALIDO --\n\n\t";
                    }
                    break;
                case 6:
                    bool invalidCode = true;
                    cout << "Codigo anterior: " << selected->code << endl;
                    do
                    {
                        cout << "Nuevo codigo: ";
                        getline(cin, userEntry);
                        if (isValid(userEntry))
                        {
                            invalidCode = searchBranchByCode(B, userEntry);

                            if (invalidCode)
                            {
                                cout << "\n\t\t\t-- CODIGO YA EXISTENTE --\n\n";
                            }
                        }
                        else
                        {
                            cout << "\n\n\t\t-- DATO INVALIDO --\n\n\t";
                        }
                        
                    } while (invalidCode);
                    cout << "\n\tSeguro que desea modificar? \n\t(1) CONFIRMAR\n\t(0) Cancelar\n\t=> ";
                    cin >> op;
                    if (cin.fail())
                    {
                        cin.clear();
                        cin.ignore();
                    }
                    if (op == 1)
                    {
                        selected->code = userEntry;
                    }
                    else op = -1;
                    break;
            }
        } while (op != 0);
    }
}

void menuConsultBranchByCode(branch*B){
    system("cls");
    menuHeader();
    string subtitle = "CONSULTAR SUCURSAL POR CODIGO";
    cout << setw((lineWidth + length(subtitle)) / 2) << subtitle << endl;
	cout << line << endl;
    branch* selected = selectBranchByCode(B);
    if (selected)
    {
        system("cls");
        menuHeader();
        cout << setw((lineWidth + length(subtitle)) / 2) << subtitle << endl;
        cout << line << endl;
        cout << "\n\tSUCURSAL ENCONTRADA: \n";
        cout << "\n\t - " << selected->name << " [" << selected->code<<"]";
        cout << "\n\t\t ~ Direccion: "<<selected->city<<", "<<selected->state<<", "<<selected->address;
        cout << "\n\t\t ~ Telefono: "<<selected->tlf<<"\n\n";
        system("pause");
    }
    else{
        cout<<"\n -- Sucursal INEXISTENTE --\n\n\n";
    }
}

/**/

void menuConsultByState(branch*B ){
    system("cls");
    menuHeader();
    string userInput;
    string subtitle = "CONSULTAR SUCURSAL POR ESTADO";
    string op0 = "0. VOLVER A MENU ANTERIOR.";
    cout << setw((lineWidth + length(subtitle)) / 2) << subtitle << endl;
	cout << line << endl;
    cout << setw((lineWidth + length(op0)) / 2) << op0 << endl;
    cout << line <<endl;
    cin.ignore();
    cout << "\nIngresa el estado: ";
    getline(cin , userInput);
    if (userInput == "0") return;
    cout << "\n\tSUCURSALES ENCONTRADAS: \n";
    branch* selected = searchBranchByState(B , userInput);
    if (!selected) {
        cout << "\n\n\t\tNINGUNA...\n\n\t";
        system("pause");
        return;
    }
    headerBranchs(line);
    while (selected)
    {
        printBranchsInTable(selected);
        selected = searchBranchByState(selected->next, userInput);
    }
    cout << line << "\n\n\t\t\t";
    system("pause");
}

void menuConsultByCity(branch* B) {
    system("cls");
    menuHeader();
    string userInput;
    string subtitle = "CONSULTAR SUCURSAL POR CIUDAD";
    string op0 = "0. VOLVER A MENU ANTERIOR.";
    cout << setw((lineWidth + length(subtitle)) / 2) << subtitle << endl;
    cout << line << endl;
    cout << setw((lineWidth + length(op0)) / 2) << op0 << endl;
    cout << line << endl;
    cin.ignore();
    cout << "\nIngresa la ciudad: ";
    getline(cin, userInput);
    if (userInput == "0") return;
    cout << "\n\tSUCURSALES ENCONTRADAS: \n";
    branch* selected = searchBranchByCity(B, userInput);
    if (!selected) {
        cout << "\n\n\t\tNINGUNA...\n\n\t";
        system("pause");
        return;
    }
    headerBranchs(line);
    while (selected)
    {
        printBranchsInTable(selected);
        selected = searchBranchByCity(selected->next, userInput);
    }
    cout << line << "\n\n\t\t\t";
    system("pause");
}

void menuConsultBranchByDesc(branch*B){
    string subtitle = "CONSULTAR SUCURSAL POR DESCRIPCION";
    string op1 = "1. ESTADO";
	string op2 = "2. CIUDAD";
    string op0 = "0. VOLVER A MENU ANTERIOR.";
    int op = -1;
    do
    {
        system("cls");
        menuHeader();
        cout << setw((lineWidth + length(subtitle)) / 2) << subtitle << endl;
        cout << line << endl;
        cout << setw((lineWidth + length(op1)) / 2) << op1 << endl;
        cout << setw((lineWidth + length(op2)) / 2) << op2 << endl;
        cout << setw((lineWidth + length(op0)) / 2) << op0 << endl;
        cout << line <<endl;
        cin >> op;
        switch (op)
        {
            case 1:
                menuConsultByState(B);
                op = 0;
                break;
            case 2:
                menuConsultByCity(B);
                break;
        }
    } while (op != 0);
}

void menuDeleBranch(branch**B,branch**L){
    system("cls");
    menuHeader();
    string subtitle = "ELIMINAR SUCURSAL";
    cout << setw((lineWidth + length(subtitle)) / 2) << subtitle << endl;
    cout << line << endl;

    branch*selected = selectBranchByCode(*B);
    if (selected)
    {
        cout << "\n\tSUCURSAL ENCONTRADA: \n";
        cout << "\n\t - " << selected->name << " [" << selected->code << "]";
        cout << "\n\t\t ~ Direccion: " << selected->city << ", " << selected->state << ", " << selected->address;
        cout << "\n\t\t ~ Telefono: " << selected->tlf << "\n\n";
        cout << "\n\tSeguro que desea eliminar? \n\t(1) CONFIRMAR\n\t(0) Cancelar\n\t=> ";
        int op;
        cin >> op;
        if (op == 1) {
            deleteBranch(B, L, selected->code);
            cout << "\n\t-- SUCURSAL ELIMINADA --\n\n";
        }
    }
    else{
        cout << "\n\n\t\t-- SUCURSAL NO SELECCIONADA --\n\n";
    }
    system("pause");
}
/*--------------------------------------------------------------------------------------------------------------------*/
/*          MENU INVENTORY MANAGMENT      */
void menuAddProductToBranch(branch*B, product*P) {
    int am, minAm;
    float price;
    system("cls");
    menuHeader();
    string subtitle = "1.2.7.2 AGREGAR PRODUTO A SUCURSAL";
    string op0 = "0. VOLVER A MENU ANTERIOR.";
    cout << setw((lineWidth + length(subtitle)) / 2) << subtitle << endl;
    cout << setw((lineWidth + length(op0)) / 2) << op0 << endl;
    cout << line << endl;
    product* selected = selectProductByCode(P);
    if (selected)
    {
        if (searchProductByCode(B->products , selected->code))
        {
            cout << "\n\n\t-- Este producto ya esta agregado --\n\n\n";
            system("pause");
            return;
        }
        cout << "\n\t - " << selected->name << " [" << selected->code << "]";
        cout << "\n\t\t ~ Descripcion: " << selected->description << "\n\t\t ~ Precio: " << selected->price << "$\n\n";
        cout << "\n\tIngresa la cantidad minima del producto: "; cin >> minAm;
        cout << "\n\tIngresa la cantidad del producto: "; cin >> am;
        cout << "\n\tIngresa el precio del producto: "; cin >> price;
        if ((am < minAm) || price < 0 || cin.fail())
        {
            cout << "\n\t-- DATOS INVALIDOS --\n\n";
            cin.clear();
            cin.ignore();
        }
        else {
            cout << "\n\tSeguro que desea agregar? \n\t(1) CONFIRMAR\n\t(0) Cancelar\n\t=> ";
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
                addProductToBranch(B, selected , am , minAm , price);
                cout << "\n\n\t\t-- PRODUCTO AGREGADO A SUCURSAL --\n\n";
            }
        }
    }
    else
    {
        cout << "\n -- PRODUCTO INEXISTENTE --\n\n\n";
    }
    system("pause");
}

void printProductssOfBranch(product*P) {
    if (!P) return;
    cout << "\n\t - " << P->name << " [" << P->code << "]";
    cout << "\n\t\t ~ Descripcion: " << P->description;
}

void headerProductsOfBranch(string line) {
    cout << line << endl;
    string subtitle = "LISTA DE PRODUCTOS";
    cout << setw((length(line) + length(subtitle)) / 2) << subtitle << endl;
    cout << line << endl;
    cout << setw(10) << internal << "CODIGO"
        << setw(15) << internal << "NOMBRE"
        << setw(17) << internal << "EXISTENCIA"
        << setw(17) << internal << "EXISTENCIA MIN."
        << setw(13) << internal << "PRECIO" << endl;
    cout << line << endl;
}

void printProductsInTableOfBranch(product* P) {
    while (P) {
        cout << setw(10) << internal << P->code
            << setw(15) << internal << P->name
            << setw(15) << internal << P->amount
            << setw(15) << internal << P->minAmount
            << setw(15) << fixed << setprecision(2) << P->price << endl;
        P = P->next;
    }
}

void tableProductsOfBranch(product* P) {
    string line = "|----------------------------------------------------------------------------|";
    headerProductsOfBranch(line);
    printProductsInTableOfBranch(P);
    cout << line << "\n\n\t";
}

void menuDelProductOfBranch(product**P , product**L) {
    system("cls");
    menuHeader();
    string subtitle = "1.2.7.2. 3 BORRAR PRODUCTO DE SUCURSAL";
    string op0 = "0. VOLVER A MENU ANTERIOR.";
    cout << setw((lineWidth + length(subtitle)) / 2) << subtitle << endl;
    cout << setw((lineWidth + length(op0)) / 2) << op0 << endl;
    cout << line << endl;
    product* selected = selectProductByCode(*P);
    if (selected)
    {
        cout << "\n\t - " << selected->name << " [" << selected->code << "]";
        cout << "\n\t\t ~ Descripcion: " << selected->description << "\n\t\t ~ Precio: " << selected->price << "$\n\n";
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
            deleteProduct(P, L, selected->code);
            cout << "\n\t-- PRODUCTO ELIMINADO --\n\n";
        }
    }
    else
    {
        cout << "\n -- PRODUCTO INEXISTENTE --\n\n";
    }
    system("pause");
}

void optionsMenuInventory(branch*selected){
    system("cls");
        menuHeader();
        string op1 = "1.2.7.1. SELECCIONAR SUCURSAL";
        string op2 = "1.2.7.2. AGREGAR PRODUCTOS";
        string op3 = "1.2.7.3. ELIMINAR PRODUCTOS";
        string op4 = "1.2.7.4. MODIFICAR INVENTARIO";
        string op5 = "1.2.7.5. MOSTRAR TODOS LOS PRODUCTOS";
        string op0 = "0. VOLVER A MENU ANTERIOR.";
        string msg = "\n\n\tSu opcion (0-5) : _";

        cout << setw((lineWidth + length(op1)) / 2) << op1 << endl;
        cout << setw((lineWidth + length(op2)) / 2) << op2 << endl;
        cout << setw((lineWidth + length(op3)) / 2) << op3 << endl;
        cout << setw((lineWidth + length(op4)) / 2) << op4 << endl;
        cout << setw((lineWidth + length(op5)) / 2) << op5 << endl;
        cout << setw((lineWidth + length(op0)) / 2) << op0 << endl;
        cout << setw((lineWidth + length(msg)) / 2) << msg << endl;
        cout << line << endl;
        cout << "\n\tSucursal seleccionada: ";
        if (!selected)
        {
            cout << "\t\tSeleccone una sucursal para continuar...\n";
        }
        else
        {
            cout << selected->name << " [" << selected->code << "]\n\n";
        }
        cout << msg;
}

void optionsModProductOfBranch(product*selected){
    system("cls");
    menuHeader();
    string subtitle = "MODIFICAR";
    string op1 = "1. NOMBRE";
    string op2 = "2. DESCRIPCION";
    string op3 = "3. PRECIO";
    string op4 = "4. CODIGO";
    string op5 = "5. CANTIDAD";
    string op6 = "6. CANTIDAD MINIMA";
    string op0 = "0. VOLVER A MENU ANTERIOR.";
    string msg = "Su opcion (0-5) : _";

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
    cout << "\n\tPRODUCTO ENCONTRADO: \n";
    cout << "\n\t - " << selected->name << " [" << selected->code << "]";
    cout << "\n\t\t ~ Descripcion: " << selected->description;
    cout << "\n\t\t ~ Precio: " << selected->price << "$";
    cout << "\n\t\t ~ Cantidad: " << selected->amount << "";
    cout << "\n\t\t ~ Cantidad MINIMA: " << selected->minAmount << "\n\n";
    cout << "\nIngresa la opcion a modificar: ";
}

void menuModProductOfBranch(product* P) {
    int op , userAm;
    float userPrice;
    string userEntry;
    system("cls");
    menuHeader();
    string subtitle = "MODIFICAR INVENTARIO";
    cout << setw((lineWidth + length(subtitle)) / 2) << subtitle << endl;
    cout << line << endl;
    product* selected = selectProductByCode(P);
    if (selected)
    {
        do
        {
            optionsModProductOfBranch(selected);
            cin >> op;
            fflush(stdin);
            switch (op)
            {
                case 1:
                        fflush(stdin);
                        cout << "Nombre anterior: " << selected->name << endl;
                        fflush(stdin);
                        cout << "Nuevo nombre: ";
                        getline(cin, userEntry);
                        cout << "\n\tSeguro que desea MODIFICAR? \n\t(1) CONFIRMAR\n\t(0) Cancelar\n\t=> ";
                        cin >> op;
                        if (cin.fail())
                        {
                            cin.clear();
                            cin.ignore();
                            op = -1;
                        }
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
                        if (cin.fail())
                        {
                            cin.clear();
                            cin.ignore();
                            op = -1;
                        }
                        if (op == 1)
                        {
                            selected->description = userEntry;
                        }
                        else op = -1;
                        break;
                    case 3:
                        cout << "Precio anterior: " << selected->price << endl;
                        fflush(stdin);
                        cout << "Nuevo precio: ";
                        cin >> userPrice;
                        cout << "\n\tSeguro que desea MODIFICAR? \n\t(1) CONFIRMAR\n\t(0) Cancelar\n\t=> ";
                        cin >> op;
                        if (cin.fail())
                        {
                            cin.clear();
                            cin.ignore();
                            op = -1;
                        }
                        if (op == 1)
                        {
                            selected->price = userPrice;
                        }
                        else op = -1;
                        break;
                    case 4:
                        {
                            bool invalidCode = true;
                            cout << "Codigo anterior: " << selected->code << endl;
                            do
                            {
                                fflush(stdin);
                                cout << "Nuevo codigo: ";
                                getline(cin, userEntry);
                                invalidCode = searchProductByCode(P, userEntry);
                                if (invalidCode)
                                {
                                    cout << "\n\t\t\t-- CODIGO YA EXISTENTE --\n\n";
                                }
                            } while (invalidCode);
                            cout << "\n\tSeguro que desea MODIFICAR? \n\t(1) CONFIRMAR\n\t(0) Cancelar\n\t=> ";
                            cin >> op;
                            if (cin.fail())
                            {
                                cin.clear();
                                cin.ignore();
                                op = -1;
                            }
                            if (op == 1)
                            {
                                selected->code = userEntry;
                            }
                            else op = -1;
                            break;
                        }
                    case 5:
                        cout << "Cantidad anterior: "<<selected->amount<<endl;
                        cout << "Nueva cantidad: "; cin >> userAm;
                        cout << "\n\tSeguro que desea MODIFICAR? \n\t(1) CONFIRMAR\n\t(0) Cancelar\n\t=> ";
                        cin >> op;
                        if (cin.fail())
                        {
                            cin.clear();
                            cin.ignore();
                            op = -1;
                        }
                        if (op == 1)
                        {
                            if (selected->minAmount > userAm)
                            {
                                cout << "\n\t\t-- Cantidad INVALIDA --\n\n";
                            }
                            else
                            {
                                selected->amount = userAm;
                            }
                        }
                        else op = -1;
                        break;
                    case 6:
                        cout << "Minima cantidad anterior: " << selected->minAmount << endl;
                        cout << "Nueva cantidad: "; cin >> userAm;
                        cout << "\n\tSeguro que desea MODIFICAR? \n\t(1) CONFIRMAR\n\t(0) Cancelar\n\t=> ";
                        cin >> op;
                        if (cin.fail())
                        {
                            cin.clear();
                            cin.ignore();
                            op = -1;
                        }
                        if (op == 1)
                        {
                            if (userAm > selected->amount)
                            {
                                cout << "\n\t\t-- Cantidad INVALIDA --\n\n";
                            }
                            else
                            {
                                selected->minAmount = userAm;
                            }
                        }
                        else op = -1;
                        break;
            }
            fflush(stdin);
        } while (op != 0);
    }
}

void menuInventory(branch*B , product*P) {
    int op;
    branch* selected = NULL;
    do
    {
        optionsMenuInventory(selected);
        cin >> op;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore();
            op = -1;
        }
        fflush(stdin);
        if (!selected && (op != 0 && op != 1))
        {
            cout << "\n\t\t\t-- SUCURSAL NO SELECCIONADA --\n\n\n";
            op = -1;
            system("pause");
        }
        switch (op)
        {
            case 1:
                selected = selectBranchByCode(B);
                cout << "\n\n";
                break;
            case 2:
                menuAddProductToBranch(selected, P);
                break;
            case 3:
                menuDelProductOfBranch(&selected->products, &selected->lastP);
                break;    
            case 4:
                menuModProductOfBranch(selected->products);
                break;
            case 5:
                cout << "\n\n\t\tPRODUCTOS DE " << selected->name<<"\n\n";
                //showAllProducts(selected->products);
                tableProductsOfBranch(selected->products);
                cout << "\n\n";
                system("pause");
                break;
        }
    } while (op != 0);
}
/*--------------------------------------------------------------------------------------------------------------------*/
#endif // MENU_H