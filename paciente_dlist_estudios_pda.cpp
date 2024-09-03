#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <limits>
#include <cmath>
#include <set>

using namespace std;

struct Paciente {
    string nombre; 
    int edad;
    double altura;
    double peso;
    double ac1;
    double imc;
    int prioridad;
    Paciente* siguiente;
};

struct Cola {
    Paciente* frente;
    Paciente* final;
    int tamano;

    Cola() : frente(nullptr), final(nullptr), tamano(0) {}
};

// Encola a un paciente en la cola
void encolar(Cola& cola, Paciente* paciente) {
    if (cola.final == nullptr) {
        cola.frente = paciente;
        cola.final = paciente;
    } else {
        cola.final->siguiente = paciente;
        cola.final = paciente;
    }
    cola.tamano++;
}

// Desencola a un paciente de la cola
Paciente* desencolar(Cola& cola) {
    if (cola.frente == nullptr) {
        return nullptr;
    }
    Paciente* pacienteAtendido = cola.frente;
    cola.frente = cola.frente->siguiente;
    if (cola.frente == nullptr) {
        cola.final = nullptr;
    }
    cola.tamano--;
    return pacienteAtendido;
}

// Obtiene el tamaño de la cola
int obtenerTamanoCola(const Cola& cola) {
    return cola.tamano;
}

// Limpia la cola
void limpiarCola(Cola& cola) {
    while (cola.frente != nullptr) {
        Paciente* temp = cola.frente;
        cola.frente = cola.frente->siguiente;
        delete temp;
    }
    cola.final = nullptr;
    cola.tamano = 0;
}

// Agrega un nuevo paciente a la lista
void agregarPaciente(Paciente*& cabeza, const string& nombre, int edad, double altura, double peso, double ac1) {
    double imc = peso / (altura * altura);
    int prioridad = (imc > 30 || ac1 > 6.5) ? 3: (imc > 25 || ac1 > 5.7) ? 2 : 1;

    Paciente* nuevoPaciente = new Paciente{nombre, edad, altura, peso, ac1, imc, prioridad, nullptr};
    if (cabeza == nullptr) {
        cabeza = nuevoPaciente;
    } else {
        Paciente* temp = cabeza;
        while (temp->siguiente != nullptr) {
            temp = temp->siguiente;
        }
        temp->siguiente = nuevoPaciente;
    }
}

// Ordena pacientes en una cola de prioridad (de mayor a menor)
void ordenarPorPrioridad(Paciente* cabeza) {
    if (cabeza == nullptr) return;

    bool swapped;
    do {
        swapped = false;
        Paciente* i = cabeza;
        while (i->siguiente != nullptr) {
            if (i->prioridad > i->siguiente->prioridad) {
                swap(i->nombre, i->siguiente->nombre);
                swap(i->edad, i->siguiente->edad);
                swap(i->altura, i->siguiente->altura);
                swap(i->peso, i->siguiente->peso);
                swap(i->imc, i->siguiente->imc);
                swap(i->ac1, i->siguiente->ac1);
                swap(i->prioridad, i->siguiente->prioridad);
                swapped = true;
            }
            i = i->siguiente;
        }
    } while (swapped);
}

// Muestra todos los datos correspondientes a cada paciente en el orden original
void mostrarPacientesEnLaLista(Paciente* cabeza) {
    Paciente* temp = cabeza;
    while (temp != nullptr) {
        cout << "Nombre: " << temp->nombre << endl;
        cout << "Edad: " << temp->edad << " años" << endl;
        cout << "Altura: " << temp->altura << " m" << endl;
        cout << "Peso: " << temp->peso << " kg" << endl;
        cout << "IMC: " << temp->imc << endl;
        cout << "A1C: " << temp->ac1 << endl;
        cout << "Prioridad: " << temp->prioridad << endl;
        cout << "----------------------------------------" << endl;
        temp = temp->siguiente;
    }
}

// Muestra todos los datos correspondientes a cada paciente en orden de prioridad
void mostrarPacientesOrdenadosPorPrioridad(Paciente* cabeza) {
    ordenarPorPrioridad(cabeza);
    Paciente* temp = cabeza;
    while (temp != nullptr) {
        cout << "Nombre: " << temp->nombre << endl;
        cout << "Edad: " << temp->edad << " años" << endl;
        cout << "Altura: " << temp->altura << " m" << endl;
        cout << "Peso: " << temp->peso << " kg" << endl;
        cout << "IMC: " << temp->imc << endl;
        cout << "A1C: " << temp->ac1 << endl;
        cout << "Prioridad: " << temp->prioridad << endl;
        cout << "----------------------------------------" << endl;
        temp = temp->siguiente;
    }
}

// Calcula el promedio de las edades
double promedioEdad(Paciente* cabeza) {
    int sumaEdades = 0;
    int contador = 0;
    Paciente* temp = cabeza;
    while (temp!= nullptr) {
        sumaEdades += temp->edad;
        contador++;
        temp = temp->siguiente;
    }
    return contador > 0 ? static_cast<double>(sumaEdades) / contador : 0.0f;
}

// Calcula el promedio de los pesos
double promedioPeso(Paciente* cabeza) {
    double sumaPesos = 0;
    int contador = 0;
    Paciente* temp = cabeza;
    while (temp != nullptr) {
        sumaPesos += temp->peso;
        contador++;
        temp = temp->siguiente;
    }
    return contador > 0 ? sumaPesos / contador : 0.0f;
}

// Elimina un paciente por su nombre
void eliminarPaciente(Paciente*& cabeza, const string& nombre) {
    if (cabeza == nullptr) return;

    if (cabeza->nombre == nombre) {
        Paciente* temp = cabeza;
        cabeza = cabeza->siguiente;
        delete temp;
    } else {
        Paciente* temp = cabeza;
        while (temp->siguiente != nullptr && temp->siguiente->nombre != nombre) {
            temp = temp->siguiente;
        }
        if (temp->siguiente != nullptr) {
            Paciente* eliminar = temp->siguiente;
            temp->siguiente = eliminar->siguiente;
            delete eliminar;
        }
    }
}

// Busca y muestra pacientes por su valor de IMC
void buscarPorIMC(Paciente* cabeza) {
    double imc;
    bool valido = false;
    while (!valido) {
        cout << "Ingrese el valor de IMC a buscar (Margen de Error: 0.1): ";
        cin >> imc;

        if (cin.fail() || imc < 0) {
            cin.clear(); // Limpia el estado de error
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignora la entrada incorrecta
            cout << "Valor de IMC inválido. Intente nuevamente." << endl;
        } else {
            valido = true;
        }   
    }

    Paciente* temp = cabeza;
    bool encontrado = false;
    const double margenError = 0.1; // Margen de error al comparar IMC
    set<double> imcsMostrados; // Para evitar mostrar IMCs repetidos 

    while (temp != nullptr) {
        if (fabs(temp->imc - imc) < margenError) {
            if (imcsMostrados.find(temp->imc) == imcsMostrados.end()) {
                cout << "\n";
                cout << "Nombre: " << temp->nombre << endl;
                cout << "IMC: " << temp->imc << endl;
                cout << "----------------------------------------" << endl;
                imcsMostrados.insert(temp->imc); // Agrega el IMC al set para evitar repeticiones
                encontrado = true;
            }
        }
        temp = temp->siguiente;
    }
    if (!encontrado) {
        cout << "No se encontraron pacientes con el IMC ingresado." << endl;
    }  
}

// Busca y muestra pacientes por su valor de AC1
void buscarPorAC1(Paciente* cabeza) {
    double ac1;
    bool valido = false;
    while (!valido) {
        cout << "Ingrese el valor A1C a buscar (Margen de Error: 0.1): ";
        cin >> ac1;

        if (cin.fail() || ac1 < 0) {
            cin.clear(); // Limpia el estado de error
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignora la entrada incorrecta
            cout << "Valor A1C inválido. Intente nuevamente." << endl;
        } else {
            valido = true;
        }
    }

    Paciente* temp = cabeza;
    bool encontrado = false;
    const double margenError = 0.1; // Margen de error al comparar los ac1
    set<double> ac1sMostrados; // Para almacenar
    while (temp != nullptr) {
        if (fabs(temp->ac1 - ac1) < margenError) {
            cout << "\n";
            cout << "Nombre: " << temp->nombre << endl;
            cout << "AC1: " << temp->ac1 << endl;
            cout << "----------------------------------------" << endl;
            encontrado = true;
        }
        temp = temp->siguiente;
    }
    if (!encontrado) {
        cout << "No se encontraron pacientes con el A1C ingresado." << endl;
    }
}

// Carga pacientes desde un archivo CSV
void cargarDesdeCSV(Paciente*& cabeza, const string& nombreArchivo) {
    ifstream archivo(nombreArchivo);
    if (!archivo) {
        cerr << "Error al abrir el archivo" << endl;
        return;
    }

    string linea;

    // Salta la primera linea 
    getline(archivo, linea);

    string nombre;
    int edad;
    double peso, altura, ac1;

    while (getline(archivo, linea)) {
        stringstream ss(linea);
        getline(ss, nombre, ',');
        ss >> edad;
        ss.ignore(1);
        ss >> altura;
        ss.ignore(1);
        ss >> peso;
        ss.ignore(1);
        ss >> ac1;

        agregarPaciente(cabeza, nombre, edad, altura, peso, ac1);
    }

    archivo.close();
}

// Libera memoria xddd :v
void liberarMemoria(Paciente*& cabeza) {
    while (cabeza != nullptr) {
        Paciente* temp = cabeza;
        cabeza = cabeza->siguiente;
        delete temp;
    }
}

// Muestra el menú y ejecuta las opciones
void mostrarMenu(Paciente*& listaPacientes, Cola& cola) {
    int opcion;
    string nombre;
    int edad;
    double peso, altura, ac1;
    string nombreArchivo;

    do {
        cout << "\nMenú de Gestión de Pacientes\n";
        cout << "1. Agregar paciente" << endl;
        cout << "2. Mostrar pacientes en orden original" << endl;
        cout << "3. Mostrar pacientes ordenados por prioridad" << endl;
        cout << "4. Calcular promedio de edades" << endl;
        cout << "5. Calcular promedio de pesos" << endl;
        cout << "6. Eliminar paciente" << endl;
        cout << "7. Buscar pacientes por IMC" << endl;
        cout << "8. Buscar pacientes por A1C" << endl;
        cout << "9. Cargar pacientes desde CSV" << endl;
        cout << "10. Encolar paciente" << endl;
        cout << "11. Desencolar paciente" << endl;
        cout << "12. Mostrar tamaño de la cola" << endl;
        cout << "13. Limpiar cola" << endl;
        cout << "14. Salir" << endl;
        cout << "Ingrese una opción: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                cout << "\n";
                cout << "Ingrese un nombre: ";
                cin >> nombre;
                cout << "Ingrese la edad: ";
                cin >> edad;
                cout << "Ingrese altura: ";
                cin >> altura;
                cout << "Ingrese el peso: ";
                cin >> peso;
                cout << "Ingrese el valor AC1: ";
                cin >> ac1;
                
                agregarPaciente(listaPacientes, nombre, edad, altura, peso, ac1);
                break;
            case 2:
                cout << "\n";
                mostrarPacientesEnLaLista(listaPacientes);
                break;
            case 3:
                cout << "\n";
                mostrarPacientesOrdenadosPorPrioridad(listaPacientes);
                break;
            case 4:
                cout << "\n";
                cout << "Promedio de edad: " << promedioEdad(listaPacientes) << " años" << endl;
                break;
            case 5:
                cout << "\n";
                cout << "Promedio de peso: " << promedioPeso(listaPacientes) << " kg" << endl;
                break;
            case 6:
                cout << "\n";
                cout << "Ingrese el nombre del paciente a eliminar: ";
                cin >> nombre;
                eliminarPaciente(listaPacientes, nombre);
                cout << "¡Eliminado con exito!" << endl;
                break;
            case 7:
                cout << "\n";
                buscarPorIMC(listaPacientes);
                break;
            case 8:
                cout << "\n";
                buscarPorAC1(listaPacientes);
                break;
            case 9:
                cout << "\n";
                cout << "Ingrese el nombre del archivo (nombre_archivo.csv): ";
                cin >> nombreArchivo;
                cargarDesdeCSV(listaPacientes, nombreArchivo);
                cout << "¡Cargado con éxito!" << endl;
                break;
            case 10:
                if (listaPacientes != nullptr) {
                    Paciente* pacienteEnCola = new Paciente(*listaPacientes);
                    pacienteEnCola->siguiente = nullptr;
                    encolar(cola, pacienteEnCola);
                    cout << "Paciente encolado con éxito" << endl;
                } else {
                    cout << "No hay pacientes en la lista para encolar" << endl;
                }
                break;
            case 11: {
                Paciente* pacienteAtendido = desencolar(cola);
                if (pacienteAtendido!= nullptr) {
                    cout << "Paciente atendido: " << pacienteAtendido->nombre << endl;
                    delete pacienteAtendido;
                } else {
                    cout << "No hay pacientes en la cola para atender" << endl;
                }
                break;
            }
            case 12:
                cout << "Tamaño de la cola: " << obtenerTamanoCola(cola) << endl;
                break;
            case 13:
                limpiarCola(cola);
                cout << "Cola limpia con éxito" << endl;
                break;  
            case 14:
                cout << "\n";
                liberarMemoria(listaPacientes);
                limpiarCola(cola);
                cout << "Saliendo..." << endl;
                break;
            default:
                cout << "Opción invalida. Intente nuevamente" << endl;              
        }
    } while (opcion != 14);
}

int main() {
    Paciente* listaPacientes = nullptr;
    Cola colaPacientes;

    mostrarMenu(listaPacientes, colaPacientes);;
    liberarMemoria(listaPacientes);
    limpiarCola(colaPacientes);

    return 0;
}
