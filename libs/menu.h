/*
    In this file are all the functions to interact with the user.
*/
#ifndef MENU_H
#define MENU_H

#include <iostream>
#include "branch.h"
#include "product.h"
#include "helper.h"
#include "people.h"
#include "bill.h"
using namespace std;




/*------ MENU MANAGMENT ------*/
int lineWidth = 120;
string line(lineWidth, '-');
const string header = line + "\n\t\tSISTEMA DE INVENTARIO Y FACTURACION\n" + line;

struct mensajeInformativo {
    string data;
};

mensajeInformativo *MI() {
    mensajeInformativo *m = new mensajeInformativo;
    m->data = "";
    return m;
}


static mensajeInformativo *Mensajero = MI();
/*const string NUM_VALIDO = "1234567890";
const int NS = 10; ver si los string son terminados en NULL para eliminar este campo */


void actualizarMensaje(string m) {
    Mensajero->data = m;
}

void printCreators() {
    cout << line << "\nREALIZADO POR: Carlos Galiño, Andrés De Quintal y Manuel Negrón;\n" << line << endl;
}

/*--------------- BRANCHES AND PRODUCTS MENUS ---------------*/
void createProduct(product**P){
    string code = "" , name = "", description = "";
    bool invalidCode = true;
    do 
    {
        obtenerEntrada2("\n\t- Escribe el CODIGO del nuevo producto: " , &code);
        if (code == "0") return;
        invalidCode = searchProductByCode(*P , code);
        if (invalidCode) cout << "\n\t\t-- CODIGO YA EXISTENTE --\n\n";
    } while (invalidCode);

    obtenerEntrada2("\n\t- Escribe el NOMBRE del nuevo producto: ", &name);
    obtenerEntrada2("\n\t- Escribe la DESCRIPCION del nuevo producto: ", &description);

    if (confirm())
    {
        if ((isValid(code) && isValid(name) && isValid(description))) {
            cout << "\n\n\t\t-- product AGREGADO --\n\n";
            addProduct(P, code, name, description, 0, 0, 0);
        }
        else cout << "\n\nLOS DATOS SON INVALIDOS\n";
    } 
}
/*  Functions to see products*/
void printProducts(product*P) {
    if (!P) return;
    cout << "\n\t - " << P->name << " [" << P->code << "]";
    printProducts(P->next);
}

void showAllProducts(product*P) {
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
    obtenerEntrada2("\n\n\n\tIngrese el codigo del product entre []: ", &codeSelect);
    if (codeSelect.empty() || codeSelect == "0") return NULL;
    return searchProductByCode(P, codeSelect);
}

void optionsModProduct(product*selected) {
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
    cout << header;
    cout << "CONSULTAR PRODUCTO POR DESCRIPCION\n0. VOLVER AL MENU ANTERIOR.\n" << line << endl;
    
    product* selected = selectProductByCode(P); // THE USER SELECT A PRODUCT
    if (!selected)
    {
        cout << "\n\n\t\t\t-- PRODUCTO NO SELECCIONADO --\n\n";
        system("pause");
        return;
    }
    
    int op;
    string input = "";
    float userPrice;
    do
    {
        optionsModProduct(selected);
        obtenerEntrada2("\nSu opcion (0-5): _|", &input);
        op = entradaValidar(input);
        switch (op)
        {
            case 1:
                cout << "Nombre anterior: " << selected->name << endl;
                obtenerEntrada2("Nuevo nombre: ", &input);
                if (confirm()) selected->name = input;
                break;
            case 2:
                cout << "Descripcion anterior: " << selected->description << endl;
                obtenerEntrada2("Nueva descripcion: ", &input);

                if (confirm()) selected->description = input;
                break;
            case 3:
            {
                bool invalidCode = true;
                cout << "Codigo anterior: " << selected->code << endl;
                do
                {
                    obtenerEntrada2("Nuevo codigo: ", &input);
                    if (input == "0") return;
                    invalidCode = searchProductByCode(P , input);
                    if (invalidCode)
                    {
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
    if (selected)
    {
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
    obtenerEntrada2("\n\tIngresa la descripcion: ", &userInput);
    if (userInput == "0") return;

    cout << "\n\tPRODUCTOS ENCONTRADOS: \n";
    product* selected = searchProductByType(B, userInput);
    if (!selected) {
        cout << "\n\n\t\tNINGUNO...\n\n";
        return;
    }
    headerProducts();
    while (selected)
    {
        printProductsInTable(selected);
        selected = searchProductByType(selected->next, userInput);
    }
    cout << line << "\n\n\t";
    system("pause");
}

void menuConsultProductByDesc(product* B) {
    string input = "";
    int op = 0;
    do
    {
        clScr();
        cout << header;
        cout << "\nCONSULTAR product POR DESCRIPCION\n\t1. DESCRIPCION\n\t0. VOLVER A MENU ANTERIOR.\n" << line << endl;
        obtenerEntrada2("", &input);
        op = entradaValidar(input);
        if (op == 1) {
            menuConsultProductByType(B);
        }
    } while (op != 0);
}

void menuDelProduct(product**P) {
    clScr();
    cout << header;
    cout << "\nELIMINAR PRODUCTO\n0. VOLVER A MENU ANTERIOR.\n" << line << endl;
    product* selected = selectProductByCode(*P);
    if (selected)
    {
        cout << "\n\t - " << selected->name << " [" << selected->code << "]";
        cout << "\n\t\t ~ Descripcion: " << selected->description << "\n\n";
        if (confirm()) {
            deleteProduct(P , selected->code);
        }
    }
}
/*--------------------------------------------------------------------------------------------------------------------*/
/*----------- BRANCHES -----------*/
void createBranch(branch**B) {
	string name, city, state, address, tlf, code;
    bool invalidCode = true;
    do
    {
        obtenerEntrada2("\n\t- Escribe el CODIGO de la nueva branch: ", &code);
        invalidCode = searchBranchByCode(*B, code);
        if (invalidCode)
        {
            cout << "\n\t\t -- CODIGO YA EXISTENTE -- \n\n";
        }
    } while (invalidCode);

	obtenerEntrada2("\n\t- Escribe el NOMBRE de la nueva branch (max.30): ", &name);
	obtenerEntrada2("\n\t- Escribe el ESTADO de la nueva branch (max.30): ", &state);
	obtenerEntrada2("\n\t- Escribe la CIUDAD de la nueva branch (max.30): ", &city);
	obtenerEntrada2("\n\t- Escribe la DIRECCION de la nueva branch (max.30): ", &address);
	obtenerEntrada2("\n\t- Escribe el NUMERO TELEFONICO de la nueva branch - (xxx) xxxxxxx: ", &tlf);

	if (!isValid(name) || !isValid(city) || !isValid(state) || !isValid(address) || !isValid(address) || !isValid(code)) {
		cout << " \n\n\t\t-- CAMPOS LLENADOS INCORRECTAMENTE --\n\n";
	}
	else
	{
		addBranch(B, code, name, city, state, tlf , address); 
        cout << "\n\t\t-- SUCURSAL AGREGADA --\n\n\n\t";
	}
}

void printBranchs(branch*B) {
	if (!B) return;
	cout << "\n\t - " << B->name << " [" << B->code<<"]\n";
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
    obtenerEntrada2("\n\n\n\tIngrese el codigo de la branch: ", &codeSelect);
    if (codeSelect.empty() || codeSelect == "0") return NULL;  
    return searchBranchByCode(B, codeSelect);
}

void menuConsultBranchByCode(branch*B){
    cout << line << "\nCONSULTAR SUCURSAL POR CODIGO\n" << line;
    branch* selected = selectBranchByCode(B);
    if (selected)
    {
        cout << "\n\n\tSUCURSAL ENCONTRADA: \n";
        cout << "\n\t - " << selected->name << " [" << selected->code<<"]";
        cout << "\n\t\t ~ Direccion: "<<selected->city<<", "<<selected->state<<", "<<selected->address;
        cout << "\n\t\t ~ Telefono: "<<selected->tlf<<"\n\n";
    }
    else cout <<"\n -- SUCURSAL INEXISTENTE --\n\n\n";
    getchar();
}


void menuConsultByState(branch*B ){
    cout << header << endl;
    string userInput = "";
    cout << "\n\tCONSULTAR SUCURSAL POR ESTADO\n\t0.VOLVER AL MENU ANTERIOR\n" << line << endl;
    obtenerEntrada2("\nIngresa el estado: " , &userInput);
    if (userInput == "0") return;
    cout << "\n\tSUCURSALES ENCONTRADAS: \n";
    branch* selected = searchBranchByState(B , userInput);
    if (!selected) {
        cout << "\n\n\t\tNINGUNA...\n\n\t";
        return;
    }
    headerBranchs();
    while (selected)
    {
        printBranchsInTable(selected);
        selected = searchBranchByState(selected->next, userInput);
    }
    cout << line << "\n\n\t\t\t";
}

void menuConsultByCity(branch* B) {
    cout << header << endl;
    cout << "\n\tCONSULTAR SUCURSAL POR CIUDAD\n\t0. VOLVER A MENU ANTERIOR.\n" << line << endl;
    string userInput = "";
    obtenerEntrada2("\nIngresa la ciudad: ", &userInput);
    if (userInput == "0") return;
    cout << "\n\tSUCURSALES ENCONTRADAS: \n";
    branch* selected = searchBranchByCity(B, userInput);
    if (!selected) {
        cout << "\n\n\t\tNINGUNA...\n\n\t";
        system("pause");
        return;
    }
    headerBranchs();
    while (selected)
    {
        printBranchsInTable(selected);
        selected = searchBranchByCity(selected->next, userInput);
    }
    cout << line << "\n\n\t\t\t";
    system("pause");
}



void menuDeleBranch(branch**B){
    clScr();
    cout << line << "\nELIMINAR SUSCURSAL\n" << line << endl;
    branch*selected = selectBranchByCode(*B);
    if (selected)
    {
        cout << "\n\tSUCURSAL ENCONTRADA: \n";
        cout << "\n\t - " << selected->name << " [" << selected->code << "]";
        cout << "\n\t\t ~ Direccion: " << selected->city << ", " << selected->state << ", " << selected->address;
        cout << "\n\t\t ~ Telefono: " << selected->tlf << "\n\n";
        if (confirm()) deleteBranch(B , selected->code);
    }
    else {
        cout << "\n\n\t\t-- branch NO SELECCIONADA --\n\n";
    }
    getchar();
}
/*---------------------------------------------------------------------------*/
/* PEOPLE */


/*--------------------------------------------------------------------------------------------------------------------*/
/*          MENU INVENTORY MANAGMENT      */
void menuAddProductToBranch(branch*B, product*P) {
    int am, minAm;
    float price;
    string entrada = "";
    clScr();
    cout << header;
    cout << "\n\t0. VOLVER\n\n";
    product* selected = selectProductByCode(P);
    if (selected)
    {
        if (searchProductByCode(B->products , selected->code))
        {
            cout << "\n\n\t-- Este product ya esta agregado --\n\n\n";
            system("pause");
            return;
        }
        
        cout << "\n\t - " << selected->name << " [" << selected->code << "]";
        cout << "\n\t\t ~ Descripcion: " << selected->description << "\n\n";

        obtenerEntrada2("\n\tIngresa la cantidad minima del producto: ", &entrada);
        minAm = to_int(entrada);

        obtenerEntrada2("\n\tIngresa la cantidad del producto: ", &entrada);
        am = to_int(entrada);
        
        obtenerEntrada2("\n\tIngresa el precio del producto: ", &entrada);
        price = to_int(entrada);
        
        if ((am < minAm) || price < 0) cout << "\n\t-- DATOS INVALIDOS --\n\n";
        else if (confirm()) addProductToBranch(B, selected , am , minAm , price);
    }
    else cout << "\n -- PRODUCTO INEXISTENTE --\n\n\n";
    getchar();
}

void printProductssOfBranch(product*P) {
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
	cout << line << endl;
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

void menuDelProductOfBranch(product**P) {
    cout << header << "\n\tBORRAR PRODUCTO DE SUCURSAL\n\t0. VOLVER A MENU ANTERIOR.\n";
    cout << line << endl;
    product* selected = selectProductByCode(*P);
    if (selected)
    {
        cout << "\n\t - " << selected->name << " [" << selected->code << "]";
        cout << "\n\t\t ~ Descripcion: " << selected->description << "\n\t\t ~ Precio: " << selected->price << "$\n\n";
        if(confirm()) {
            deleteProduct(P,  selected->code);
            cout << "\n\t-- product ELIMINADO --\n\n";
        }
    }
    else cout << "\n -- PRODUCTO INEXISTENTE --\n\n";
    system("pause");
}



void optionsModProductOfBranch(product*selected){
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
    int op , userAm;
    float userPrice;
    string input = "";
    product* selected = selectProductByCode(P);
    do
    {
        clScr();
        optionsModProductOfBranch(selected);
        obtenerEntrada2("", &input);
        op = entradaValidar(input);
        switch (op)
        {
            case 1:
                cout << "Nombre anterior: " << selected->name << endl;
                obtenerEntrada2("Nuevo nombre: ", &input);

                if (confirm()) {
                    selected->name = input;
                    break;
                }
                break;
            case 2:
                cout << "Descripcion anterior: " << selected->description << endl;
                obtenerEntrada2("Nueva descripcion: ", &input);
                if (confirm()) selected->description = input;
                break;
            case 3:
                cout << "Precio anterior: " << selected->price << endl;
                obtenerEntrada2("Nuevo precio: ", &input);
                userPrice = stof(input); // FIXME revisar si el dato es float y evitar errores de entrada
                cin >> userPrice;
                if (confirm()) selected->description = input;
                break;
            case 4:
                {
                    bool invalidCode = true;
                    cout << "Codigo anterior: " << selected->code << endl;
                    do
                    {
                        obtenerEntrada2("Nuevo codigo: ", &input);
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
                cout << "Cantidad anterior: "<<selected->amount<<endl;
                obtenerEntrada2("Nueva cantidad: ", &input);
                userAm = to_int(input);
                if (confirm() && selected->minAmount < userAm) {
                    selected->amount = userAm;
                } else cout << "\n\t-- CANTIDAD INVALIDA --\n";
                break;
            case 6:
                cout << "Minima cantidad anterior: " << selected->minAmount << endl;
                obtenerEntrada2("Nueva cantidad: ", &input);
                userAm = to_int(input);                
                if (confirm() && userAm < selected->amount) selected->minAmount = userAm;
                break;
        }
    } while (selected && op != 0);
}

void optionsMenuInventory(branch*selected){
    cout << line <<"\n1. SELECCIONAR SUCURSAL\n\t2. AGREGAR PRODUCTOS\n\t3. ELIMINAR PRODUCTOS\n\t4. MODIFICAR INVENTARIO\n\t5. MOSTRAR TODOS LOS PRODUCTOS\n\t0. VOLVER A MENU ANTERIOR.\n" << line;
    cout << "\n\n\t\tSucursal seleccionada: ";
    if (!selected) cout << "\tSeleccone una sucursal para continuar...\n";
    else cout << selected->name << " [" << selected->code << "]\n\n";
}

void menuInventory(branch*B , product*P) {
    branch* selected = NULL;
    char op = '\0';
    do
    {
        //clScr();
        optionsMenuInventory(selected);
        cin >> op;
	cin.ignore();
        if (!selected && (op != '1' && op != '0'))
        {
            cout << "\n\t\t\t-- SUCURSAL NO SELECCIONADA --\n\n\n";
            op = '\0';
            getchar();
        }
        switch (op)
        {
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
                cout << "\n\n\t\tPRODUCTOS DE " << selected->name<<"\n\n";
                tableProductsOfBranch(selected->products);
                break;
        }
        system("pause");
    } while (op != '0');
}

people *selectPersonById(people* P) {
    showPeople(P);
    string input;
    obtenerEntrada2("\nIngrese la cedula: ", &input);
    return searchPeopleByID(P, input);
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
    product **products;
    branch **branches;
    people **clients;
    branch **selectedBranch;
    people **selectedClient;
};

context *newContext(product **p, branch **b, people **c, branch *sb, people *sc) {
    context *result = new context;
    result->products = p;
    result->branches = b;
    result->clients = c;
    result->selectedBranch = &sb;
    result->selectedClient = &sc;
    return result;
}

struct menuItem {
    menuItem *parent;
    string encabezado;
    int (*comportamiento)(menuItem**, int, context*);
};


void print(string s) {
    cout << s << endl;
} 

void print(int s) {
    cout << s << endl;
} 


void mostrarMenuActivo(menuItem *mi) {
    print(mi->encabezado);
}





// signature de las funciones de menu

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


menuItem *menuMantenimiento(menuItem*);
menuItem *controlProductos(menuItem*);
menuItem *controlSucursales(menuItem*);
/* SUCURSALES */
menuItem *menuModBranchs(menuItem*);     
menuItem *menuConsultBranchByDesc(menuItem*);
menuItem *menuPeople(menuItem*);
menuItem *menuModifyPeople(menuItem*);
menuItem *menuBilling(menuItem*);

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

int controllerMenuBilling(menuItem **activo, int selec, context *ct) {
    

    switch (selec) {
        case 0:
            if (*activo) {
                actualizarMensaje("");
                *activo = (*activo)->parent;
                return 1;
            }
        case 1:
            *ct->selectedBranch = selectBranchByCode(*ct->branches);
            actualizarMensaje("Tienda[ " + formatNULL(*ct->selectedBranch) + " ]\tCliente[ " + formatNULL(*ct->selectedClient) + " ]");
            return 1;
        case 2:
            *ct->selectedClient = selectPersonById(*ct->clients);
            actualizarMensaje("Tienda[ " + formatNULL(*ct->selectedBranch) + " ]\tCliente[ " + formatNULL(*ct->selectedClient) + " ]");
            return 1;
        default:
            return 1;
    }
}


int controllerMenuModBranch(menuItem **activo, int selec, context *ct) {
    branch *selected = selectBranchByCode(*ct->branches);
    if (!selected) return 1;
    string input = "";
    switch (selec) {
        case 0:
            if (*activo) {
                actualizarMensaje("");
                *activo = (*activo)->parent;
                return 1;
            }
        case 1:
            cout <<"Nombre anterior: "<<selected->name<<endl;
            obtenerEntrada("Nuevo nombre: " , &input);
            if (confirm() && isValid(input)) selected->name = input;
            break;
        case 2:
            cout << "Estado anterior: "<<selected->state<<endl;
            obtenerEntrada("Nueva ciudad: " , &input);
            if (confirm() && isValid(input)) selected->state = input;
            break;
        case 3:
            cout  << "Cidudad anterior: "<<selected->city<<endl;
            obtenerEntrada("Nueva ciudad: " , &input);
            if (confirm() && isValid(input)) selected->city = input;
            break;
        case 4:
            cout << "Direccion anterior: "<<selected->address<<endl;
            obtenerEntrada("Nueva direccion: " , &input);
            if (confirm() && isValid(input)) selected->address = input;
            break;
        case 5:
            cout << "Telefono anterior: "<<selected->tlf<<endl;
            obtenerEntrada("Nuevo telefono: " , &input);
            if (confirm() && isValid(input)) selected->tlf = input;
            break;
        default:
            actualizarMensaje("La opcion seleccionada no corresponde a una accion. Intente nuevamente.\n");
            break;
    } return 1;
}


int controllerConsultBranchByDesc(menuItem **activo, int selec, context*ct) {
    switch (selec)
    {
        case 0:
            if (*activo) {
                actualizarMensaje("");
                *activo = (*activo)->parent;
                return 1;
            }
        case 1:
            menuConsultByState(*(ct->branches));
            break;
        case 2:
            menuConsultByCity(*(ct->branches));
            break;
    }
    print("Presione ENTER para continuar.");
    getchar(); // espera nuevo \n para tomar;
    return 1;
}


int controllerMenuModifyPeople(menuItem **activo, int selec, context *ct) {
    string name = "";
    string id = "";
    people* cliente = NULL;

    switch (selec) {
        case 0:
            cout << "Volviendo al menu anterior..." << endl;
            print("Presione ENTER para continuar.");
            getchar(); // espera nuevo \n para tomar;
            if (*activo) {
                actualizarMensaje("");
                *activo = (*activo)->parent;
                return 1;
            }
            break;
        case 1:
            obtenerEntrada2("\n\t - Ingrese el nuevo Nombre y Apellido: ", &name);
            if (!validateName(name)) {
                cout << "El nombre y el apellido no deben contener numeros." << endl;
                break;
            }
            cliente->name = name;
            cout << "\n\t- Nombre y Apellido modificados exitosamente! -" << endl;
            break;
        case 2:
            obtenerEntrada2("\n\t - Ingrese la nueva Cedula: ", &id);
            
            if (!validateID(id)) {
                cout << "\nCedula invalida. Debe contener entre 7 y 8 digitos numericos." << endl;
                break;
            }
            if (searchPeopleByID(*(ct->clients), id) != NULL) {
                cout << "\nCedula ya existente. Ingrese una cedula unica." << endl;
                break;
            }
            cliente->ID = id;
            cout << "\n\t- Cedula modificada exitosamente! -" << endl;
            break;
        
        default:
            cout << "Opcion no valida. Intente de nuevo." << endl;
            print("Presione ENTER para continuar.");
            getchar(); // espera nuevo \n para tomar;
            break;
    }
    return 1;

}


int controllerMenuPeople(menuItem **activo, int selec, context *ct) {
    string id = "";
    string name = "";
    people* client = NULL;

    switch (selec) {
        case 0:
            cout << "Volviendo al menu anterior..." << endl;
            if (*activo) {
                actualizarMensaje("");
                *activo = (*activo)->parent;
                return 1;
            }
            print("Presione ENTER para continuar.");
            getchar(); // espera nuevo \n para tomar;
            break;

        case 1:
            clScr();
            cout << "\nAGREGAR CLIENTE\n";
            obtenerEntrada2("Ingrese su cedula: ", &id);
            if (!validateID(id)) {
                cout << "\nCedula invalida. Debe contener entre 7 y 8 digitos numericos." << endl;
                cout << "\nPresione Enter para continuar...";
                getchar();
                break;
            }
            obtenerEntrada2("Ingrese su nombre y apellido: ", &name);
            if (!validateName(name)) {
                cout << "El nombre y el apellido no deben contener numeros." << endl;
                cout << "\nPresione Enter para continuar...";
                getchar();
                break;
            }

            if (searchPeopleByID(*(ct->clients), id) != NULL) {
                cout << "\nCedula ya existente. Ingrese una cedula unica." << endl;
                cout << "\nPresione Enter para continuar...";
                getchar();
                break;
            }

            addPerson(ct->clients, id, name); 
            cout << "\n\t- Cliente agregado exitosamente! -" << endl;
            cout << "\nPresione Enter para continuar...";
            getchar();
            break;

        case 2:
            clScr();
            cout << "\nMODIFICAR CLIENTE" << endl;
            showPeople(*(ct->clients));
            obtenerEntrada2("\n\t - Ingrese la cedula del cliente a modificar: ", &id);
            selectPersonById(*(ct->clients));
            /*if (cliente) {
                clrScr();
                cout << "\n\tInformacion actual del cliente:\n" << endl;
                cout << "Cedula: " << cliente->ID << ", Nombre y Apellido: " << cliente->name << endl;
                *activo =  menuModifyPeople(*activo);
                
            } else {
                cout << "No se encontro el cliente con la cedula indicada." << endl;
            }*/
            cout << "\nPresione Enter para continuar...";
            getchar();
            break;
        case 3:
            clScr();
            cout << "\nELIMINAR CLIENTE" << endl;
            showPeople(*(ct->clients));
            obtenerEntrada2("\n\t - Ingrese la cedula del cliente a eliminar: ", &id);
            // Verificar si el cliente existe antes de intentar eliminarlo
            client = searchPeopleByID(*(ct->clients), id);
            if (client) {
                showPeople(client);
                if (confirm() == 1) {
                    deletePerson(ct->clients, client->ID);
                    cout << "\n\t- Cliente eliminado exitosamente! -" << endl;
                }
            } else {
                cout << "\n\t- No se encontró el cliente con la cedula indicada." << endl;
            }
            cout << "\nPresione Enter para continuar...";
            getchar();
            break;
        case 4:
            //consultCustomer(*(ct->clients));
            break;

        case 5:
            clScr();
            cout << "\n\tLISTA DE CLIENTES" << endl;
            showPeople(*(ct->clients));
            cout << "\nPresione Enter para continuar...";
            getchar();
            break;

        default:
            cout << "Opcion no valida. Intente de nuevo." << endl;
            print("Presione ENTER para continuar.");
            getchar(); // espera nuevo \n para tomar;
            break;
    }
    
    return 1;
}


int operarMenuPrincipal(menuItem **activo, int selec, context*ct) {
    menuItem *temp = NULL;
    //branch *cache = NULL;
    if (*activo) {
        switch (selec) {
            case 0:
                //cache = *ct->branches;
                if (!(*activo)->parent) {
                    //guardarLocal(cache, "Data.txt");
                    //cache = NULL;
                    return 0;
                } // refactorizar antes de merge
                actualizarMensaje("");
                *activo = (*activo)->parent;
                return 1;
            case 1:
                *activo = menuMantenimiento(*activo);
                return 1;
            case 2:
                actualizarMensaje("Tienda[   ]\tCliente[   ]");
                *activo = menuBilling(*activo);
                return 1;
            default:
                actualizarMensaje("La opcion seleccionada no corresponde a una accion. Intente nuevamente.\n");
                return 1;
        }
    } return 0;
}
 // 1 productos 2 sucursales 3 personas  0 regresar

int operarMenuMantenimiento(menuItem **activo, int selec, context*ct) {
    menuItem *temp = NULL;
    if (*activo) {
        switch (selec) {
            case 0:
                if (!(*activo)->parent) {
                    return 0;
                } 
                actualizarMensaje("");
                *activo = (*activo)->parent;
                return 1;
            case 1:
                *activo = controlProductos(*activo);
                return 1;
            case 2:
                *activo = controlSucursales(*activo);
                return 1;
            case 3:
            {
                people *p = getLast(*(ct->clients));
                *activo = menuPeople(*activo);
                return 1;
            }
            default:
                actualizarMensaje("La opcion seleccionada no corresponde a una accion. Intente nuevamente.\n");
                return 1;
        }
    } return 0;
}




int controladorMenuProductos(menuItem **activo, int selec ,context*ct) {
    string entrada = "";
    int conf;
    product *p = NULL;
    switch (selec) {
        case 0:
            if (*activo) {
                actualizarMensaje("");
                *activo = (*activo)->parent;
                // guardarLocal(*principal, "Data.txt");
                return 1;
            }
            break;
        case 1:
            actualizarMensaje("");
            createProduct(ct->products);
            print("Presione ENTER para continuar.");
            getchar(); // espera nuevo \n para tomar;
            break;
        case 2: // modificar
            actualizarMensaje("");
            menuModProduct(*ct->products);
            print("Presione ENTER para continuar.");
            getchar(); // espera nuevo \n para tomar;
            break;
        case 3: // eliminar
            actualizarMensaje("");
            menuDelProduct(ct->products);
            print("Presione ENTER para continuar.");
            getchar(); // espera nuevo \n para tomar;
            break;
        case 4: // consultar por codigo
            actualizarMensaje("");
            menuConsultProductByCode(*ct->products);
            print("Presione ENTER para continuar.");
            getchar(); // espera nuevo \n para tomar;
            break;
        case 5:
            actualizarMensaje("");
            menuConsultProductByDesc(*ct->products);
            print("Presione ENTER para continuar.");
            getchar(); // espera nuevo \n para tomar;
            break;
        case 6:
            actualizarMensaje("");
            tableProducts(*ct->products);
            print("Presione ENTER para continuar.");
            getchar(); // espera nuevo \n para tomar;
            break;
        default:
            actualizarMensaje("La opcion seleccionada no corresponde a una accion. Intente nuevamente.\n");
            return 1;
            break;
    }
    return 1;
}



int controladorMenuSucursales(menuItem **activo, int selec, context*ct) {
    string entrada = "";
    branch *s = NULL;
    int conf;
    product *p = NULL;
    switch (selec) {
        case 0:
            if (*activo) {
                actualizarMensaje("");
                *activo = (*activo)->parent;
                // ELIMINAR CUANDO SE TERMINE DE PROBAR CODIFICACION
                return 1;
            }
            break;
        case 1: // agregar
            actualizarMensaje("");
            createBranch(ct->branches);
            print("Presione ENTER para continuar.");
            getchar(); // espera nuevo \n para tomar;
            break;
        case 2: // modificar
            actualizarMensaje("");
            *activo = menuModBranchs(*activo);
            print("Presione ENTER para continuar.");
            getchar(); // espera nuevo \n para tomar;
            break;
        case 3: // eliminar
            actualizarMensaje("");
            obtenerEntrada("Indique el codigo de la branch a eliminar: ", &entrada);
            menuDeleBranch(ct->branches);
            print("Presione ENTER para continuar.");
            getchar(); // espera nuevo \n para tomar;
            break;
        case 4: // consultar por codigo
            actualizarMensaje("");
            obtenerEntrada("Indique el codigo de la branch a consultar: ", &entrada);
            menuConsultBranchByCode(*ct->branches);
            print("Presione ENTER para continuar.");
            getchar(); // espera nuevo \n para tomar;
            break;
        case 5: // Consult by description
            actualizarMensaje("");
            //menuConsultBranchByDesc(*ct->branches);
            *activo = menuConsultBranchByDesc(*activo); // listo
            print("Presione ENTER para continuar.");
            getchar(); // espera nuevo \n para tomar;
            break;
        case 6:
            actualizarMensaje("");
            tableBranchs(*ct->branches);
            print("Presione ENTER para continuar.");
            getchar(); // espera nuevo \n para tomar;
            break;
        case 7:
            actualizarMensaje("");
            menuInventory(*ct->branches , *ct->products);
            print("Presione ENTER para continuar.");
            getchar(); // espera nuevo \n para tomar;
            break;
        default:
            actualizarMensaje("La opcion seleccionada no corresponde a una accion. Intente nuevamente.\n");
            return 1;
            break;
    }
    return 1;
}




menuItem *controlSucursales(menuItem *parent) {
    menuItem *m = new menuItem;
    // refactor m->cabeza = parent->cabeza;
    m->encabezado = "---------------------------------------------------------------------------\n\t\tSISTEMA DE INVENTARIO Y FACTURACION\n---------------------------------------------------------------------------\nCONTROL DE SUCURSALES GLOBAL\n\t1. AGREGAR\n\t2. MODIFICAR\n\t3. ELIMINAR\n\t4. CONSULTAR POR CODIGO\n\t5. CONSULTAR POR DESCRIPCION\n\t6. MOSTRAR TODAS LAS SUCURSALES\n\t7. MOSTRAR INVENTARIO\n\t0. SALIR\n---------------------------------------------------------------------------\nRealizado por Carlos Galiño, Andrés de Quintal y Manuel Negrón;\n---------------------------------------------------------------------------";
    m->parent = parent->parent;
    // refactor m->prox = NULL;
    m->comportamiento = controladorMenuSucursales;
    return m;
}


menuItem *controlProductos(menuItem *parent) {
    menuItem *m = new menuItem;
    // refactor m->cabeza = parent->cabeza;
    m->encabezado = "---------------------------------------------------------------------------\n\t\tSISTEMA DE INVENTARIO Y FACTURACION\n---------------------------------------------------------------------------\nCONTROL DE PRODUCTOS GLOBAL\n\t1. AGREGAR\n\t2. MODIFICAR\n\t3. ELIMINAR\n\t4. CONSULTAR POR CODIGO\n\t5. CONSULTAR POR DESCRIPCION\n\t6. MOSTRAR PRODUCTOS\n\t0. SALIR\n---------------------------------------------------------------------------\nRealizado por Carlos Galiño, Andrés de Quintal y Manuel Negrón;\n---------------------------------------------------------------------------";
    m->parent = parent;
    //refactor m->prox = controlSucursales(m);
    m->comportamiento = controladorMenuProductos;
    return m;
}


menuItem *menuMantenimiento(menuItem *parent) {
    menuItem *m = new menuItem;
    //refactor m->cabeza = parent->cabeza;
    m->encabezado = "---------------------------------------------------------------------------\n\t\t1. MANTENIMIENTO\n---------------------------------------------------------------------------\nOPCIONES DE MENU\n\t1. PRODUCTOS\n\t2. SUCURSALES\n\t3. PERSONAS\n\t0. REGRESAR\n---------------------------------------------------------------------------";
    m->parent = parent;
    // refactor m->prox = controlProductos(m);
    m->comportamiento = operarMenuMantenimiento;
    return m;

}

menuItem *menuPrincipal() {
    menuItem *m = new menuItem;
    // refactor m->cabeza = cargarLocal("Data.txt");
    m->encabezado = "---------------------------------------------------------------------------\n\t\tSISTEMA DE INVENTARIO Y FACTURACION\n---------------------------------------------------------------------------\nMENU PRINCIPAL\n\t1. MANTENIMIENTO\n\t2. FACTURACION\n\t3. REPORTES\n\t0. SALIR\n---------------------------------------------------------------------------\nRealizado por Carlos Galiño, Andrés de Quintal y Manuel Negrón;\n---------------------------------------------------------------------------";
    m->parent = NULL;
    // refactor m->prox = menuMantenimiento(m);
    m->comportamiento = operarMenuPrincipal;
    return m;
}


menuItem *menuConsultBranchByDesc(menuItem *parent) {
    menuItem *m = new menuItem;
    m->encabezado = line + "\nCONSULTAR branch POR DESCRIPCION\n\t1. ESTADO\n\t2. CIUDAD\n\t0. VOLVER A MENU ANTERIOR.\n" + line;
    m->parent = parent;
    m->comportamiento = controllerConsultBranchByDesc;
    return m;
}

menuItem *menuModBranchs(menuItem *parent) {
    menuItem *m = new menuItem;
    m->encabezado = line + "\nMODIFICAR\n\t1. NOMBRE\n\t2. ESTADO\n\t3. CIUDAD\n\t4. DIRECCION\n\t5. TELEFONO\n\t6. CODIGO\n\t0. VOLVER A MENU ANTERIOR.\n" + line;
    m->parent = parent;
    m->comportamiento = controllerConsultBranchByDesc;
    return m;
}

menuItem *menuPeople(menuItem *parent) {
    menuItem *m =  new menuItem;
    m->encabezado = line + "\nMANTENIMIENTO PERSONAS\n\t1. AGREGAR CLIENTE\n\t2. MODIFICAR CLIENTE\n\t3. ELIMINAR CLIENTE\n\t4. CONSULTAR\n\t5. MOSTRAR TODOS LOS CLIENTES\n\t0. VOLVER AL MENU ANTERIOR.\n" + line;
    m->parent = parent;
    m->comportamiento = controllerMenuPeople;
    return m;
}

menuItem *menuModifyPeople(menuItem *parent) {
    menuItem *m = new menuItem;
    m->encabezado = line + "\nMODIFICAR PERSONAS\n\t1. MODIFICAR NOMBRE Y APELLIDO\n\t2. MODIFICAR CEDULA\n\t0. VOLVER AL MENU ANTERIOR\n" + line + "\nSu opcion (0-2): ";
    m->parent = parent;
    m->comportamiento = controllerMenuModifyPeople;
    return m;
}

menuItem *menuBilling(menuItem *parent) {
    menuItem *m = new menuItem;
    m->encabezado = line + "\n\t1. SELECCIONAR TIENDA\n\t2. SELECCIONAR CLIENTE\n\t3. AGREGAR PRODUCTOS\n\t4. MOSTRAR FACTURA\n\t5. ELIMINAR FACTURA\n\t6. MOSTRAR RESUMEN FACTURAS\n\t0. VOLVER A MENU ANTERIOR.\n" + line;
    m->parent = parent;
    m->comportamiento = controllerMenuBilling;
    return m;
}


/*
void optionsMenuBilling(branch*sb, people *sc){
    cout << 
    cout << "\n\n\t\tSucursal seleccionada: ";
    if (sb) cout << selected->name << " [" << selected->code << "]\n\n";

}*/
/*
void menuBilling(branch *branches, people *peopleList, bill *bills) {
    branch *bs = NULL;
    people *cs = NULL;
    do
    {
        // Mostrar todo


        //leer casos
    } while ();
}*/

void run() {
    int activo = 1;
    int val = 0;
    string entrada = "";
    menuItem *menuActivo = menuPrincipal();
    branch *branches = NULL; 
    product *products = NULL;
    people *clients = NULL;
    people *lastclient = NULL;

    readProducts(&products);
    readBranches(&branches);
    readInventory(branches, products);
    readClients(&clients);
    context*ct = newContext(&products , &branches, &clients, NULL, NULL);
    while (activo) {
        clScr(); // Refrescar la pantalla y borrar el terminal
        print(Mensajero->data);
        if (menuActivo) {
            obtenerEntrada(menuActivo->encabezado, &entrada);
            val = entradaValidar(entrada);
            activo = menuActivo->comportamiento(&menuActivo, val, ct);
        } else {
            activo = 0;
        }
    }
    saveProducts(products);
    saveBranchs(branches);
    saveProductsOfBranch(branches);
    saveClients(clients);
    clScr(); // Refrescar la pantalla y borrar el terminal
}


#endif // MENU_H
