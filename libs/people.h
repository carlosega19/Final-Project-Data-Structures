
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
    while (P && P->ID != id) { P = P->next; } return P;
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
    } else {
        cout << "No se encontró el cliente con la cédula '" << id << "'." << endl;
    }
}

// Función para imprimir todas las cédulas disponibles
void printID(people* P) {
    while (P != NULL) {
        cout << "Cedula: " << P->ID << endl;
        P = P->next;
    }
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
                cout << "Ingrese el nombre a buscar: ";
                getline(cin, consulta);
                cout << "Resultados para el nombre '" << consulta << "':\n" << endl;
                consultByName(P, consulta);
                break;
            case 2:
                cout << "Cédulas disponibles en el sistema:" << endl;
                printID(P);
                cout << "Ingrese la cédula a buscar: ";
                getline(cin, consulta);
                consultByID(P, consulta);
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



#endif