#ifndef CLIENT_H
#define CLIENT_H
#include <iostream>
#include <string.h>
#include "helper.h"
using namespace std;

struct people {
    char ID[10];                // Esto NO es un string
    char nameAndSecondName[30]; // cambiar de char [n] a string, para que sea complatible con funciones auxiliares
    people* next;
};


people *getLast(people *p) {
    if (p) {
        while (p && p->next) {
            p = p->next;
        }
        return p;
    } return NULL;

}

// Función para validar que el nombre y apellido no contengan números
bool validateName(const char* nombre) {
    for (int i = 0; i < strlen(nombre); i++) {
        if (nombre[i] >= '0' && nombre[i] <= '9') {
            return false;
        }
    }
    return true;
}

// Función para validar que la cedula tenga solo numeros y tenga entre 7 y 8 dígitos
bool validateID(const char* cedula) {
    int len = strlen(cedula);
    if (len < 7 || len > 8) {
        return false;
    }
    for (int i = 0; i < len; i++) {
        if (cedula[i] < '0' || cedula[i] > '9') {
            return false;
        }
    }
    return true;
}

// Función para encontrar una persona por su cedula
people* foundPeopleByID(people* head, const char* id) {
    people* current = head;
    while (current != nullptr) {
        if (strcmp(current->ID, id) == 0) {
            return current;
        }
        current = current->next;
    }
    return nullptr;
}

// Función para agregar una nueva persona a la lista
bool addPerson(people** head, people** last, const char* id, const char* nameAndSecondName) {
    // Validar cédula
    if (!validateID(id)) {
        cout << "\nCedula invalida. Debe contener entre 7 y 8 digitos numericos." << endl;
        return false;
    }

    // Validar nombre y apellido
    if (!validateName(nameAndSecondName)) {
        cout << "El nombre y el apellido no deben contener numeros." << endl;
        return false;
    }

    // Verificar si la cédula ya existe
    if (foundPeopleByID(*head, id) != nullptr) {
        cout << "\nCedula ya existente. Ingrese una cedula unica." << endl;
        return false;
    }

    // Crear nuevo cliente
    people* newPerson = new people;
    strcpy(newPerson->ID, id);
    strcpy(newPerson->nameAndSecondName, nameAndSecondName);
    newPerson->next = nullptr;

    // Agregar persona a la lista
    if (!(*head)) {
        *head = newPerson;
        *last = newPerson;
    } else {
        (*last)->next = newPerson;
        *last = newPerson;
    }

    return true;
}


// Función para mostrar todas las personas en la lista
void showPeople(people* head) {
    if (head == NULL) {
        cout << "\t - No hay clientes en la lista" << endl;
        return;
    }

    people* current = head;
    while (current != NULL) {
        cout << "Cedula: " << current->ID << ", Nombre y Apellido: " << current->nameAndSecondName << endl;
        current = current->next;
    }
}


// Función para cargar personas desde el archivo
void loadPeopleFromFile(const char* nombreArchivo, people** head, people** last) {
    FILE* archivo = fopen("D://people.txt", "r");

    if (!archivo) {
        cerr << "Error al abrir el archivo " << nombreArchivo << endl;
        return;
    }

    char linea[100];
    bool comenzarLectura = false;

    while (fgets(linea, sizeof(linea), archivo)) {
        if (strstr(linea, "@@@@@@")) {
            comenzarLectura = !comenzarLectura;
            continue;
        }

        if (comenzarLectura) {
            char id[10], nameAndSecondName[40];
            sscanf(linea, "%[^,], %[^\n]", id, nameAndSecondName);
            addPerson(head, last, id, nameAndSecondName);
        }
    }

    fclose(archivo);
}

//Función para guardar personas en un archivo
/*void guardarPersonasEnArchivo(const char* nombreArchivo, const people* cabeza) {
    FILE* archivo = fopen("D://people.txt", "w");

    if (!archivo) {
        cerr << "Error al abrir el archivo " << nombreArchivo << endl;
        return;
    }

    fprintf(archivo, "@@@@@@\n"); // Inicio del bloque de personas

    const people* temp = cabeza;
    while (temp != NULL) {
        fprintf(archivo, "%s, %s\n", temp->ID, temp->nameAndSecondName);
        temp = temp->next;
    }

    fprintf(archivo, "@@@@@@\n"); // Fin del bloque de personas

    fclose(archivo);
    cout << nombreArchivo << endl;
}*/

// Función para eliminar una persona de la lista
void deletePeople(people** head, people** last, people* personaEliminar) {
    if (!(*head)) {
        cout << "La lista esta vacia. No se puede eliminar." << endl;
        return;
    }

    if (personaEliminar == *head) {
        *head = (*head)->next;
        delete personaEliminar;
        if (!(*head)) {
            *last = NULL; 
        }
        return;
    }

    people* temp = *head;
    while (temp && temp->next != personaEliminar) {
        temp = temp->next;
    }

    if (!temp) {
        cout << "Persona no encontrada en la lista." << endl;
        return;
    }

    temp->next = personaEliminar->next;
    delete personaEliminar;
    if (temp->next == NULL) {
        *last = temp; 
    }
}

// Función para consultar por nombre
void consultByName(const people* head, const char* nombreConsulta) {
    const people* temp = head;
    bool encontrado = false;

    while (temp != NULL) {
        if (strstr(temp->nameAndSecondName, nombreConsulta) != NULL) {
            cout << "CEDULA: " << temp->ID << ", Nombre / Apellido: " << temp->nameAndSecondName << endl;
            encontrado = true;
        }
        temp = temp->next;
    }

    if (!encontrado) {
        cout << "No se encontraron personas con el nombre indicado." << endl;
    }
}



// Función para mostrar todas las cédulas disponibles
void printID(const people* head) {
    const people* temp = head;

    while (temp != NULL) {
        cout << "Cedula: " << temp->ID << endl;
        temp = temp->next;
    }
}

// Función para consultar por cédula
void consultByID(const people* head, const char* cedulaConsulta) {
    const people* temp = head;
    bool encontrado = false;

    while (temp != NULL) {
        if (strcmp(temp->ID, cedulaConsulta) == 0) {
            cout << "Nombre y Apellido: " << temp->nameAndSecondName << ", Cedula: " << temp->ID << endl;
            encontrado = true;
            break; // Como la cédula es única, podemos salir del bucle al encontrar la coincidencia
        }
        temp = temp->next;
    }

    if (!encontrado) {
        cout << "No se encontro el cliente con la cedula indicada." << endl;
    }
}

// Función para consultar cliente por nombre / apellido o cédula
void consultCustomer(const people* head) {
    int opcion;
    char consulta[20]; // Para almacenar el nombre, apellido o cédula a consultar

    do {
        clScr();
        cout << "\n\tCONSULTAR CLIENTE" << endl;
        cout << "1. Consultar por Nombre" << endl;
        cout << "2. Consultar por Cedula" << endl;
        cout << "0. Volver al Menu Anterior" << endl;
        cout << "Su opcion (0-3): ";
        cin >> opcion;
        cin.ignore(); // Limpiar el buffer de entrada

        switch (opcion) {
            case 1:
                cout << "Ingrese el nombre a buscar: ";
                cin.getline(consulta, 20);
                cout << "Resultados para el nombre '" << consulta << "':" << endl;
                consultByName(head, consulta);
                break;
            case 2:
                cout << "Cédulas disponibles en el sistema:" << endl;
                printID(head);
                cout << "Ingrese la cédula a buscar: ";
                cin.getline(consulta, 20);
                consultByID(head, consulta);
                break;
            case 0:
                cout << "Volviendo al menú anterior..." << endl;
                break;
            default:
                cout << "Opción no válida. Intente de nuevo." << endl;
                break;
        }

        if (opcion != 0) {
            cout << "\n...";
            cin.ignore(); // Esperar a que el usuario presione Enter
        }
    } while (opcion != 0);
}

void esperarEntrada() {
    cout << "Presione Enter para continuar...";
    cin.get();
};

// Función para modificar los datos de un cliente
void maintenancePeople(people** head, people** last) {
    int opcion;
    char id[10], nameAndSecondName[40];
    people* cliente = NULL; // Declaración fuera del do-while

    do {
        // Mostrar el menú de mantenimiento de personas
        cout << "MANTENIMIENTO PERSONAS" << endl;
        cout << "1. Agregar Cliente" << endl;
        cout << "2. Modificar Cliente" << endl;
        cout << "3. Eliminar Cliente" << endl;
        cout << "4. Consultar" << endl;
        cout << "5. Mostrar Todos los Clientes" << endl;
        cout << "0. Volver al Menu Anterior" << endl;
        cout << "Su opcion (0-5): ";
        cin >> opcion;
        cin.ignore(); // Para limpiar el buffer de entrada

        switch (opcion) {
            case 1:
                clScr();
                cout << "\n\t - Ingrese Cedula: ";
                cin.getline(id, 10);
                cout << "\n\t - Ingrese Nombre y Apellido: ";
                cin.getline(nameAndSecondName, 40);
                if (!addPerson(head, last, id, nameAndSecondName)) {
                    esperarEntrada();
                } else {
                    cout << "\n\t- Cliente agregado exitosamente! -" << endl;
                    esperarEntrada();
                }
                break;
            case 2:
                clScr();
                cout << "\nMODIFICAR CLIENTE" << endl;
                showPeople(*head);
                cout << "\n\t - Ingrese la cedula del cliente a modificar: ";
                cin.getline(id, 10);
                cliente = foundPeopleByID(*head, id);
                if (cliente) {
                    // Mostrar información actual del cliente
                    clScr();
                    cout << "\n\tInformacion actual del cliente:\n" << endl;
                    cout << "Cedula: " << cliente->ID << ", Nombre y Apellido: " << cliente->nameAndSecondName << endl;

                    // Submenú para modificar cliente
                    int opcionModificar;
                    do {
                        cout << "\n\t1. Modificar Nombre" << endl;
                        cout << "\t2. Modificar Cedula" << endl;
                        cout << "\t0. Volver al Menu Anterior" << endl;
                        cout << "\nSu opcion (0-3): ";
                        cin >> opcionModificar;
                        cin.ignore(); // Limpiar el buffer de entrada

                        switch (opcionModificar) {
                            case 1:
                                cout << "Ingrese nuevo nombre y apellido: ";
                                cin.getline(nameAndSecondName, 40);
                                if (!validateName(nameAndSecondName)) {
                                    cout << "Nombre no valido. No debe contener numeros." << endl;
                                } else {
                                    strcpy(cliente->nameAndSecondName, nameAndSecondName);
                                    cout << "Nombre modificado correctamente." << endl;
                                }
                                break;
                            case 2:
                                cout << "Ingrese nueva cedula: ";
                                cin.getline(id, 10);
                                if (strlen(id) > 8 || !validateID(id)) {
                                    cout << "Cedula no valida. Debe tener máximo 8 digitos numericos." << endl;
                                } else {
                                    strcpy(cliente->ID, id);
                                    cout << "Cedula modificada correctamente." << endl;
                                }
                                break;
                            case 0:
                                break;
                            default:
                                cout << "Opcion no valida. Intente de nuevo." << endl;
                                break;
                        }

                        // Mostrar información actualizada del cliente después de cada modificación
                        if (opcionModificar != 0) {
                            clScr();
                            cout << "Informacion actualizada del cliente:" << endl;
                            cout << "CEDULA: " << cliente->ID << ", NOMBRE / APELLIDO: " << cliente->nameAndSecondName << endl;
                        }
                    } while (opcionModificar != 0);
                } else {
                    cout << "Cliente no encontrado." << endl;
                }
                break;
            case 3:
                clScr();
                cout << "ELIMINAR CLIENTE" << endl;
                showPeople(*head);
                cout << "\n\t - Ingrese la cedula del cliente a eliminar: ";
                cin.getline(id, 10);
                cliente = foundPeopleByID(*head, id);
                if (cliente) {
                    // Mostrar información del cliente a eliminar
                    clScr();
                    cout << "Informacion del cliente a eliminar:" << endl;
                    cout << "CEDULA: " << cliente->ID << ", NOMBRE / APELLIDO: " << cliente->nameAndSecondName << endl;

                    // Confirmación de eliminación
                    char confirmacion;
                    cout << "\n\t - Desea ELIMINAR al cliente? (1: SI / 2: NO): ";
                    cin >> confirmacion;
                    cin.ignore(); // Limpiar el buffer de entrada

                    if (confirmacion == '1') {
                        // Eliminar cliente
                        deletePeople(head, last, cliente);
                        cout << "Cliente eliminado exitosamente." << endl;
                    } else {
                        cout << "Operacion cancelada. No se ha eliminado al cliente." << endl;
                    }
                } else {
                    cout << "Cliente no encontrado." << endl;
                }
                break;
            case 4:
                clScr();
                cout << "CONSULTAR CLIENTE" << endl;
                int opcionConsulta;
                do {
                    cout << "\n\t - CONSULTAR POR:\n" << endl;
                    cout << "1. Nombre/Apellido" << endl;
                    cout << "2. Cedula" << endl;
                    cout << "0. Volver al Menu Anterior" << endl;
                    cout << "Su opcion (0-3): ";
                    cin >> opcionConsulta;
                    cin.ignore(); // Limpiar el buffer de entrada

                    switch (opcionConsulta) {
                        case 1: {
                            clScr();
                            cout << "Ingrese el nombre y apellido a buscar: ";
                            cin.getline(nameAndSecondName, 40);
                            consultByName(*head, nameAndSecondName);
                            break;
                        }
    
                        case 2:
                            clScr();
                            printID(*head);
                            cout << "Ingrese la cedula a consultar: ";
                            cin.getline(id, 10);
                            consultByID(*head, id);
                            break;
                        case 0:
                            break;
                        default:
                            cout << "Opcion no valida. Intente de nuevo." << endl;
                            break;
                    }
                } while (opcionConsulta != 0);
                break;

            case 5:
                clScr();
                showPeople(*head);
                esperarEntrada();
                break;
            case 0:
                cout << "Volviendo al menu anterior..." << endl;
                break;
            default:
                cout << "Opcion no valida. Intente de nuevo." << endl;
                break;
        }
    } while (opcion != 0);

    // Guardar los cambios realizados en el archivo
    //guardarPersonasEnArchivo("people.txt", *head);
}


// Función para imprimir personas
void printPeople(people* p) {
    if (!p) return;
    cout << "\n\t - " << p->ID << " [" << p->nameAndSecondName << " " << "]\n";
    printPeople(p->next);
}

/*int main() {
    clearScreen();
    int opcion;
    people* listaPersonas = NULL;
    people* ultimaPersona = NULL;

    loadPeopleFromFile("people.txt", &listaPersonas, &ultimaPersona);

    do {
        clearScreen();
        // Mostrar el menú principal
        cout << "SISTEMA DE INVENTARIO Y FACTURACION" << endl;
        cout << "1. Mantenimiento Personas" << endl;
        cout << "0. Salir" << endl;
        cout << "Su opcion (0-1): ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                maintenancePeople(&listaPersonas, &ultimaPersona);
                break;
            case 0:
                cout << "Saliendo del sistema..." << endl;
                break;
            default:
                cout << "Opcion no valida. Intente de nuevo." << endl;
                break;
        }
    } while (opcion != 0);
    return 0;
}*/

#endif