#include <iostream>
#include <string>

using namespace std;

struct people {
    string ID;
    string nameAndSecondName;
    people* next;
};

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

// Función para validar que la cedula tenga solo numeros y tenga entre 7 y 8 dígitos
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

// Función para encontrar una persona por su cedula
people* foundPeopleByID(people* P, string id) {
    if (!P) return NULL;
    if (P->ID == id) return P;
    return foundPeopleByID(P->next, id);
}

// Función para agregar una nueva persona a la lista
void addPerson(people** P, people** L, string id, string nameAndSecondName) {
    people* newP = new people;
    newP->ID = id;
    newP->nameAndSecondName = nameAndSecondName;
    newP->next = NULL;

    if (!(*P)) {
        *P = newP;
        *L = newP;
    } else {
        (*L)->next = newP;
        *L = newP;
    }
}

// Función para convertir una cadena a minúsculas
string tolow(string cad) {
    for (int i = 0; i < cad.length(); i++) {
        if (cad[i] >= 'A' && cad[i] <= 'Z') {
            cad[i] += 'a' - 'A'; // Convertir caracteres mayúsculas a minúsculas
        }
    }
    return cad;
}

// Función para comprobar si una subcadena está contenida en una cadena
int find(string main, string pat) {
    for (int i = 0; i <= main.length() - pat.length(); i++) {
        bool found = true;
        for (int j = 0; j < pat.length(); j++) {
            if (main[i + j] != pat[j]) {
                found = false;
                break;
            }
        }
        if (found) return 1;
    }
    return 0;
}

// Función para mostrar todas las personas en la lista
void showPeople(people* P) {
    if (!P) {
        cout << "\t - No hay clientes en la lista" << endl;
        return;
    }

    while (P != NULL) {
        cout << "Cedula: " << P->ID << ", Nombre y Apellido: " << P->nameAndSecondName << endl;
        P = P->next;
    }
}

// Función para eliminar una persona de la lista
void deletePeople(people** P, people** L, string id) {
    if (!(*P)) return;
    people* ax = *P, * temp;
    if (ax->ID == id) {
        temp = ax;
        *P = (*P)->next;
        delete temp;
        if (!(*P)) *L = NULL;
    } else {
        while (ax->next && ax->next->ID != id) ax = ax->next;
        if (ax->next) {
            if (ax->next == *L) {
                temp = ax->next;
                ax->next = temp->next;
                delete temp;
                *L = ax;
            } else {
                temp = ax->next;
                ax->next = temp->next;
                delete temp;
            }
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
        string lowerNameToCompare = tolow(P->nameAndSecondName);

        // Comparar las cadenas convertidas
        if (find(lowerNameToCompare, lowerName)) {
            cout << "CEDULA: " << P->ID << ", Nombre / Apellido: " << P->nameAndSecondName << endl;
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
void consultByID(people* P, string id) {
    people* person = foundPeopleByID(P, id);
    if (person) {
        cout << "Nombre y Apellido: " << person->nameAndSecondName << ", Cedula: " << person->ID << endl;
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
        cout << "Su opcion (0-2): ";
        cin >> opcion;
        cin.ignore();

        if (cin.fail() || opcion < 0 || opcion > 2) {
            cin.clear();
            while (cin.get() != '\n'); 
            cout << "Opción no válida. Intente de nuevo." << endl;
            continue;
        }

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
            while (cin.get() != '\n'); // Limpiar buffer de entrada hasta encontrar nueva línea
        }
    } while (opcion != 0);
}

// Función para modificar los datos de un cliente
void maintenancePeople(people* P, people* L) {
    int opcion;
    string id, nameAndSecondName;
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

        if (cin.fail() || opcion < 0 || opcion > 5) {
            cin.clear();
            while (cin.get() != '\n');
            cout << "Opción no válida. Intente de nuevo." << endl;
            continue;
        }

        switch (opcion) {
            case 1:
                clrScr();
                cout << "\n\t - Ingrese Cedula: ";
                getline(cin, id);
                if (!validateID(id)) {
                    cout << "\nCedula invalida. Debe contener entre 7 y 8 digitos numericos." << endl;
                    cout << "\nPresione Enter para continuar...";
                    while (cin.get() != '\n'); 
                    break;
                }

                cout << "\n\t - Ingrese Nombre y Apellido: ";
                getline(cin, nameAndSecondName);
                if (!validateName(nameAndSecondName)) {
                    cout << "El nombre y el apellido no deben contener numeros." << endl;
                    cout << "\nPresione Enter para continuar...";
                    while (cin.get() != '\n'); 
                    break;
                }

                addPerson(&P, &L, id, nameAndSecondName);
                cout << "\nCliente Agregado Exitosamente." << endl;
                cout << "\nPresione Enter para continuar...";
                while (cin.get() != '\n'); 
                break;

            case 2:
                clrScr();
                cout << "\n\t - Ingrese Cedula: ";
                getline(cin, id);
                if (!validateID(id)) {
                    cout << "\nCedula invalida. Debe contener entre 7 y 8 digitos numericos." << endl;
                    cout << "\nPresione Enter para continuar...";
                    while (cin.get() != '\n'); 
                    break;
                }

                cliente = foundPeopleByID(P, id);
                if (cliente == NULL) {
                    cout << "\nCliente no encontrado." << endl;
                    cout << "\nPresione Enter para continuar...";
                    while (cin.get() != '\n'); 
                    break;
                }

                cout << "\n\t - Ingrese Nuevo Nombre y Apellido: ";
                getline(cin, nameAndSecondName);
                if (!validateName(nameAndSecondName)) {
                    cout << "El nombre y el apellido no deben contener numeros." << endl;
                    cout << "\nPresione Enter para continuar...";
                    while (cin.get() != '\n'); 
                    break;
                }

                cliente->nameAndSecondName = nameAndSecondName;
                cout << "\nCliente Modificado Exitosamente." << endl;
                cout << "\nPresione Enter para continuar...";
                while (cin.get() != '\n'); 
                break;

            case 3:
                clrScr();
                if (!P) {
                    cout << "\t - No hay clientes disponibles para eliminar." << endl;
                    cout << "\nPresione Enter para continuar...";
                    while (cin.get() != '\n'); 
                    break;
                }

                cout << "\n\t - Ingrese Cedula del Cliente a Eliminar: ";
                getline(cin, id);
                if (!validateID(id)) {
                    cout << "\nCedula invalida. Debe contener entre 7 y 8 digitos numericos." << endl;
                    cout << "\nPresione Enter para continuar...";
                    while (cin.get() != '\n'); 
                    break;
                }

                cliente = foundPeopleByID(P, id);
                if (cliente == NULL) {
                    cout << "\nCliente no encontrado." << endl;
                    cout << "\nPresione Enter para continuar...";
                    while (cin.get() != '\n'); 
                    break;
                }

                deletePeople(&P, &L, id);
                cout << "\nCliente Eliminado Exitosamente." << endl;
                cout << "\nPresione Enter para continuar...";
                while (cin.get() != '\n'); 
                break;

            case 4:
                consultCustomer(P);
                break;

            case 5:
                clrScr();
                cout << "\n\t - Clientes Registrados:" << endl;
                showPeople(P);
                cout << "\nPresione Enter para continuar...";
                while (cin.get() != '\n'); 
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
            while (cin.get() != '\n'); 
        }
    } while (opcion != 0);
}

// Función principal para ejecutar el programa
int main() {
    people* P = NULL;
    people* L = NULL;
    maintenancePeople(P, L);
    return 0;
}
