#ifndef PEOPLE_H
#define PEOPLE_H


#include <iostream>
#include <string>

using namespace std;

struct people {
    string ID;
    string name;
    people* next;
};

people *getLast(people *p) {
    if (p) {
        while (p && (p->next)) {
            p = p->next;
        }
        return p;

    } return NULL;

}
// Función para limpiar la pantalla
void clrScr() {
    cout << "\033[2J\033[H";
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
    if (cedula.length() < 7 || cedula.length() > 8) {
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
void addPerson(people** P, string id, string name) {
    people* newP = new people;
    newP->ID = id;
    newP->name = name;
    newP->next = NULL;
    if (*P) {      
        people *aux = *P;
        while (aux && aux->next) {
            if (aux->ID == id) return;
            aux = aux->next;
        }
        aux->next =  newP;
    } else {
        *P = newP;
    }
}


// Función para buscar un patrón en una cadena
bool find(string main, string pat) {
    for (int i = 0; i <= main.length() - pat.length(); i++) {
        bool found = true;
        for (int j = 0; j < pat.length(); j++) {
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
        cout << "Cedula: " << P->ID << ", Nombre y Apellido: " << P->name << endl;
        P = P->next;
    }
}

// Función para eliminar una persona de la lista
void deletePerson(people** P, string id) {
    if (!P) return;
    
    people* ax = *P;
    people* temp = NULL;
    
    if (ax->ID == id) {
        temp = ax;
        *P = (*P)->next;
        delete temp;
        return;
    } else {
        while (ax->next && ax->next->ID != id) ax = ax->next;
        if (ax->next) {
            temp = ax->next;
            ax->next = temp->next;
            delete temp;
        }
    }
}

// Función para consultar por nombre
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

// Función para mostrar todas las cédulas disponibles
void printID(people* P) {
    while (P != NULL) {
        cout << "Cedula: " << P->ID << endl;
        P = P->next;
    }
}

// Función para consultar por cédula
void consultPersonByID(people* P, string id) {
    people* person = searchPeopleByID(P, id);
    if (person) {
        cout << "Nombre y Apellido: " << person->name << ", Cedula: " << person->ID << endl;
    } else {
        cout << "No se encontro el cliente con la cedula indicada." << endl;
    }
}

// Función para consultar cliente por nombre / apellido o cédula
void consultCustomer(people* P) {
    int opcion;
    string consulta; // Para almacenar el nombre, apellido o cédula a consultar

    do {
        clrScr();
        cout << "\n\tCONSULTAR CLIENTE" << endl;
        cout << "1. Consultar por Nombre" << endl;
        cout << "2. Consultar por Cedula" << endl;
        cout << "0. Volver al Menu Anterior" << endl;
        cout << "Su opcion (0-3): ";
        cin >> opcion;
        cin.ignore();

        switch (opcion) {
            case 1:
                cout << "Ingrese el nombre a buscar: ";
                getline(cin, consulta);
                cout << "Resultados para el nombre '" << consulta << "':" << endl;
                consultByName(P, consulta);
                break;
            case 2:
                cout << "Cédulas disponibles en el sistema:" << endl;
                printID(P);
                cout << "Ingrese la cédula a buscar: ";
                getline(cin, consulta);
                consultPersonByID(P, consulta);
                break;
            case 0:
                cout << "Volviendo al menú anterior..." << endl;
                break;
            default:
                cout << "Opción no válida. Intente de nuevo." << endl;
                break;
        }

        if (opcion != 0) {
            cout << "\nPresione Enter para continuar...";
            getchar(); // Esperar a que el usuario presione Enter
        }
    } while (opcion != 0);
}
/*
// Función para modificar los datos de un cliente
people* maintenancePeople(people* P) {
    int opcion;
    string id, name;
    people* cliente = NULL;

    do {
        clrScr();
        cout << "MANTENIMIENTO PERSONAS" << endl;
        cout << "1. Agregar Cliente" << endl;
        cout << "2. Modificar Cliente" << endl;
        cout << "3. Eliminar Cliente" << endl;
        cout << "4. Consultar" << endl;
        cout << "5. Mostrar Todos los Clientes" << endl;
        cout << "0. Volver al Menu Anterior" << endl;
        cout << "Su opcion (0-5): ";
        cin >> opcion;
        cin.ignore();

        switch (opcion) {
            case 1:
                clrScr();
                cout << "\n\t - Ingrese Cedula: ";
                getline(cin, id);
                if (!validateID(id)) {
                    cout << "\nCedula invalida. Debe contener entre 7 y 8 digitos numericos." << endl;
                    cout << "\nPresione Enter para continuar...";
                    getchar();
                    break;
                }

                cout << "\n\t - Ingrese Nombre y Apellido: ";
                getline(cin, name);
                if (!validateName(name)) {
                    cout << "El nombre y el apellido no deben contener numeros." << endl;
                    cout << "\nPresione Enter para continuar...";
                    getchar();
                    break;
                }

                if (searchPeopleByID(P, id) != NULL) {
                    cout << "\nCedula ya existente. Ingrese una cedula unica." << endl;
                    cout << "\nPresione Enter para continuar...";
                    getchar();
                    break;
                }

                P = addPerson(P, id, name); 
                cout << "\n\t- Cliente agregado exitosamente! -" << endl;
                cout << "\nPresione Enter para continuar...";
                getchar();
                break;

            case 2:
                clrScr();
                cout << "\nMODIFICAR CLIENTE" << endl;
                showPeople(P);
                cout << "\n\t - Ingrese la cedula del cliente a modificar: ";
                getline(cin, id);
                cliente = searchPeopleByID(P, id);
                if (cliente) {
                    clrScr();
                    cout << "\n\tInformacion actual del cliente:\n" << endl;
                    cout << "Cedula: " << cliente->ID << ", Nombre y Apellido: " << cliente->name << endl;

                    int opcionModificar;
                    do {
                        cout << "\n\t1. Modificar Nombre y Apellido" << endl;
                        cout << "\t2. Modificar Cedula" << endl;
                        cout << "\t0. Volver al menu anterior" << endl;
                        cout << "\n\tSu opcion (0-2): ";
                        cin >> opcionModificar;
                        cin.ignore();

                        switch (opcionModificar) {
                            case 1:
                                cout << "\n\t - Ingrese el nuevo Nombre y Apellido: ";
                                getline(cin, name);
                                if (!validateName(name)) {
                                    cout << "El nombre y el apellido no deben contener numeros." << endl;
                                    break;
                                }
                                cliente->name = name;
                                cout << "\n\t- Nombre y Apellido modificados exitosamente! -" << endl;
                                break;
                            case 2:
                                cout << "\n\t - Ingrese la nueva Cedula: ";
                                getline(cin, id);
                                if (!validateID(id)) {
                                    cout << "\nCedula invalida. Debe contener entre 7 y 8 digitos numericos." << endl;
                                    break;
                                }
                                if (searchPeopleByID(P, id) != NULL) {
                                    cout << "\nCedula ya existente. Ingrese una cedula unica." << endl;
                                    break;
                                }
                                cliente->ID = id;
                                cout << "\n\t- Cedula modificada exitosamente! -" << endl;
                                break;
                            case 0:
                                cout << "Volviendo al menu anterior..." << endl;
                                break;
                            default:
                                cout << "Opcion no valida. Intente de nuevo." << endl;
                                break;
                        }
                    } while (opcionModificar != 0);
                } else {
                    cout << "No se encontro el cliente con la cedula indicada." << endl;
                }
                cout << "\nPresione Enter para continuar...";
                getchar();
                break;
            case 3:
                clrScr();
                cout << "\nELIMINAR CLIENTE" << endl;
                showPeople(P);
                cout << "\n\t - Ingrese la cedula del cliente a eliminar: ";
                getline(cin, id);
                // Verificar si el cliente existe antes de intentar eliminarlo
                cliente = searchPeopleByID(P, id);
                if (cliente) {
                    P = deletePerson(P, id);
                    cout << "\n\t- Cliente eliminado exitosamente! -" << endl;
                } else {
                    cout << "\n\t- No se encontró el cliente con la cedula indicada." << endl;
                }
                cout << "\nPresione Enter para continuar...";
                getchar();
                break;
                
            case 4:
                consultCustomer(P);
                break;

            case 5:
                clrScr();
                cout << "\n\tLISTA DE CLIENTES" << endl;
                showPeople(P);
                cout << "\nPresione Enter para continuar...";
                getchar();
                break;

            case 0:
                cout << "Volviendo al menu anterior..." << endl;
                break;

            default:
                cout << "Opcion no valida. Intente de nuevo." << endl;
                break;
        }

    } while (opcion != 0);
    return P;
}

int main() {
    people* head = NULL;

    head = maintenancePeople(head);

    while (head) {
        people* temp = head;
        head = head->next;
        delete temp;
    }

    return 0;
}
*/

#endif