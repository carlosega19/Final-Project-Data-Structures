#include <iostream>
#include <string>

using namespace std;

struct people {
    string ID;
    string nameAndSecondName;
    people* next;
};

// Función para limpiar la pantalla
void clearScreen() {
    cout << "\033[2J\033[H";
}

// Función para validar que el nombre y apellido no contengan números
bool validateName(const string& name) {
    for (char c : name) {
        if (isdigit(c)) {
            return false;
        }
    }
    return true;
}

// Función para validar que la cedula tenga solo numeros y tenga entre 7 y 8 dígitos
bool validateID(const string& cedula) {
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
people* foundPeopleByID(people* head, const string& id) {
    people* current = head;
    while (current != NULL) {
        if (current->ID == id) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

// Función para agregar una nueva persona a la lista
bool addPerson(people** head, people** last, const string& id, const string& nameAndSecondName) {
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
    if (foundPeopleByID(*head, id) != NULL) {
        cout << "\nCedula ya existente. Ingrese una cedula unica." << endl;
        return false;
    }

    // Crear nuevo cliente
    people* newPerson = new people;
    newPerson->ID = id;
    newPerson->nameAndSecondName = nameAndSecondName;
    newPerson->next = NULL;

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
/* Función para cargar personas desde el archivo
void loadPeopleFromFile(const char* nombreArchivo, people** head, people** last) {
    FILE* archivo = fopen(nombreArchivo, "r");

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
            string id, nameAndSecondName;
            id = strtok(linea, ",");
            nameAndSecondName = strtok(NULL, "\n");
            addPerson(head, last, id, nameAndSecondName);
        }
    }

    fclose(archivo);
}*/

//Función para guardar personas en un archivo
void guardarPersonasEnArchivo(const char* nombreArchivo, const people* cabeza) {
    FILE* archivo = fopen(nombreArchivo, "w");

    if (!archivo) {
        cerr << "Error al abrir el archivo " << nombreArchivo << endl;
        return;
    }

    fprintf(archivo, "@@@@@@\n"); // Inicio del bloque de personas

    const people* temp = cabeza;
    while (temp != NULL) {
        fprintf(archivo, "%s, %s\n", temp->ID.c_str(), temp->nameAndSecondName.c_str());
        temp = temp->next;
    }

    fprintf(archivo, "@@@@@@\n"); // Fin del bloque de personas

    fclose(archivo);
    cout << nombreArchivo << endl;
}

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
void consultByName(const people* head, const string& nombreConsulta) {
    const people* temp = head;
    bool encontrado = false;

    while (temp != NULL) {
        if (temp->nameAndSecondName.find(nombreConsulta) != string::npos) {
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
void consultByID(const people* head, const string& cedulaConsulta) {
    const people* temp = head;
    bool encontrado = false;

    while (temp != NULL) {
        if (temp->ID == cedulaConsulta) {
            cout << "Nombre y Apellido: " << temp->nameAndSecondName << ", Cedula: " << temp->ID << endl;
            encontrado = true;
            break;         }
        temp = temp->next;
    }

    if (!encontrado) {
        cout << "No se encontro el cliente con la cedula indicada." << endl;
    }
}

// Función para consultar cliente por nombre / apellido o cédula
void consultCustomer(const people* head) {
    int opcion;
    string consulta; // Para almacenar el nombre, apellido o cédula a consultar

    do {
        clearScreen();
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
                consultByName(head, consulta);
                break;
            case 2:
                cout << "Cédulas disponibles en el sistema:" << endl;
                printID(head);
                cout << "Ingrese la cédula a buscar: ";
                getline(cin, consulta);
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
            cout << "\nPresione Enter para continuar...";
            cin.get(); // Esperar a que el usuario presione Enter
        }
    } while (opcion != 0);
}

// Función para modificar los datos de un cliente
void maintenancePeople(people** head, people** last) {
    int opcion;
    string id, nameAndSecondName;
    people* cliente = NULL; 

    do {
        clearScreen();
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
        cin.ignore();

        switch (opcion) {
            case 1:
                clearScreen();
                cout << "\n\t - Ingrese Cedula: ";
                getline(cin, id);
                cout << "\n\t - Ingrese Nombre y Apellido: ";
                getline(cin, nameAndSecondName);
                if (!addPerson(head, last, id, nameAndSecondName)) {
                    cout << "\nPresione Enter para continuar...";
                    cin.get();
                } else {
                    cout << "\n\t- Cliente agregado exitosamente! -" << endl;
                    cout << "\nPresione Enter para continuar...";
                    cin.get();
                }
                break;
            case 2:
                clearScreen();
                cout << "\nMODIFICAR CLIENTE" << endl;
                showPeople(*head);
                cout << "\n\t - Ingrese la cedula del cliente a modificar: ";
                getline(cin, id);
                cliente = foundPeopleByID(*head, id);
                if (cliente) {
                    // Mostrar información actual del cliente
                    clearScreen();
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
                        cin.ignore(); 

                        switch (opcionModificar) {
                            case 1:
                                cout << "Ingrese nuevo nombre y apellido: ";
                                getline(cin, nameAndSecondName);
                                if (!validateName(nameAndSecondName)) {
                                    cout << "Nombre no valido. No debe contener numeros." << endl;
                                } else {
                                    cliente->nameAndSecondName = nameAndSecondName;
                                    cout << "Nombre modificado correctamente." << endl;
                                }
                                break;
                            case 2:
                                cout << "Ingrese nueva cedula: ";
                                getline(cin, id);
                                if (id.length() > 8 || !validateID(id)) {
                                    cout << "Cedula no valida. Debe tener máximo 8 digitos numericos." << endl;
                                } else {
                                    cliente->ID = id;
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
                            clearScreen();
                            cout << "Informacion actualizada del cliente:" << endl;
                            cout << "CEDULA: " << cliente->ID << ", NOMBRE / APELLIDO: " << cliente->nameAndSecondName << endl;
                        }
                    } while (opcionModificar != 0);
                } else {
                    cout << "Cliente no encontrado." << endl;
                }
                break;
            case 3:
                clearScreen();
                cout << "ELIMINAR CLIENTE" << endl;
                showPeople(*head);
                cout << "\n\t - Ingrese la cedula del cliente a eliminar: ";
                getline(cin, id);
                cliente = foundPeopleByID(*head, id);
                if (cliente) {
                    // Mostrar información del cliente a eliminar
                    clearScreen();
                    cout << "Informacion del cliente a eliminar:" << endl;
                    cout << "CEDULA: " << cliente->ID << ", NOMBRE / APELLIDO: " << cliente->nameAndSecondName << endl;

                    // Confirmación de eliminación
                    char confirmacion;
                    cout << "\n\t - Desea ELIMINAR al cliente? (1: SI / 2: NO): ";
                    cin >> confirmacion;
                    cin.ignore(); 

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
                clearScreen();
                consultCustomer(*head);
                break;
            case 5:
                clearScreen();
                showPeople(*head);
                cout << "\nPresione Enter para continuar...";
                cin.get();
                break;
            case 0:
                break;
            default:
                cout << "Opcion no valida. Intente de nuevo." << endl;
                break;
        }
    } while (opcion != 0);

    // Guardar los cambios realizados en el archivo
    guardarPersonasEnArchivo("people.txt", *head);
}

int main() {
    people* listaPersonas = NULL;
    people* ultimaPersona = NULL;

    // Cargar personas desde el archivo
    //loadPeopleFromFile("people.txt", &listaPersonas, &ultimaPersona);

    // Realizar el mantenimiento de personas
    maintenancePeople(&listaPersonas, &ultimaPersona);

    return 0;
}