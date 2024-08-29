#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct Paciente {
    string nombre;
    int edad;
    double peso;
    double altura;
    Paciente* siguiente; 
};

// Agrega un nuevo paciente a la lista
void agregarPaciente(Paciente*& cabeza, const string& nombre, int edad, double peso, double altura) {
    Paciente* nuevoPaciente = new Paciente{nombre, edad, peso, altura, nullptr};
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

// Muestra todos los datos correspondientes a cada paciente
void mostrarPacientes(Paciente* cabeza) {
    Paciente* temp = cabeza;
    while (temp!= nullptr) {
        cout << "Nombre: " << temp->nombre << endl;
        cout << "Edad: " << temp->edad << " años" << endl;
        cout << "Peso: " << temp->peso << " kg" << endl;
        cout << "Altura: " << temp->altura << " m" << endl;
        cout << "IMC: " << temp->peso / (temp->altura * temp->altura) << endl;
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

// Carga pacientes desde un archivo txt
void cargarDesdeArchivo(Paciente*& cabeza, const string& nombreArchivo) {
    ifstream archivo(nombreArchivo);
    if (!archivo) {
        cerr << "Error al abrir el archivo" << endl;
        return;
    }

    string nombre;
    int edad;
    double peso, altura;

    while (archivo >> nombre >> edad >> peso >> altura) {
        agregarPaciente(cabeza, nombre, edad, peso, altura);
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
void mostrarMenu(Paciente*& listaPacientes) {
    int opcion;
    string nombre;
    int edad;
    double peso, altura;
    string nombreArchivo;

    do {
        cout << "\nMenú de Gestión de Pacientes\n";
        cout << "1. Agregar paciente" << endl;
        cout << "2. Mostrar pacientes" << endl;
        cout << "3. Calcular promedio de edades" << endl;
        cout << "4. Calcular promedio de pesos" << endl;
        cout << "5. Eliminar paciente" << endl;
        cout << "6. Cargar pacientes desde archivo (txt)" << endl;
        cout << "7. Salir" << endl;
        cout << "Ingrese una opción: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                cout << "\n";
                cout << "Ingrese un nombre: ";
                cin >> nombre;
                cout << "Ingrese la edad: ";
                cin >> edad;
                cout << "Ingrese el peso: ";
                cin >> peso;
                cout << "Ingrese altura: ";
                cin >> altura;
                agregarPaciente(listaPacientes, nombre, edad, peso, altura);
                break;
            case 2:
                cout << "\n";
                mostrarPacientes(listaPacientes);
                break;
            case 3:
                cout << "\n";
                cout << "Promedio de edad: " << promedioEdad(listaPacientes) << " años" << endl;
                break;
            case 4:
                cout << "\n";
                cout << "Promedio de peso: " << promedioPeso(listaPacientes) << " kg" << endl;
                break;
            case 5:
                cout << "\n";
                cout << "Ingrese el nombre del paciente a eliminar: ";
                cin >> nombre;
                cout << "¡Eliminado con exito!" << endl;
                eliminarPaciente(listaPacientes, nombre);
                break;
            case 6:
                cout << "\n";
                cout << "Ingrese el nombre del archivo (nombre_archivo.txt): ";
                cin >> nombreArchivo;
                cout << "¡Cargado con exito!" << endl;
                cargarDesdeArchivo(listaPacientes, nombreArchivo);
                break;
            case 7:
                cout << "\n";
                liberarMemoria(listaPacientes);
                cout << "Saliendo..." << endl;
                break;
            default:
                cout << "Opción invalida. Intente nuevamente" << endl;              
        }
    } while (opcion != 7);
}

int main() {
    Paciente* listaPacientes = nullptr;
    mostrarMenu(listaPacientes);
    return 0;
}
