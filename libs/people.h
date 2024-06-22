
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

#endif