#include <iostream>
#include <string>

using namespace std;

struct Paciente { // Se define la estructura Persona
    string nombre;
    int edad;
    double peso;
    double altura;
    Paciente* siguiente; // Apuntados al siguiente paciente en la lista
};

// Agrega un nuevo paciente a la lista
void agregarPaciente(Paciente*& cabeza, const string& nombre, int edad, double peso, double altura) {
    Paciente* nuevoPaciente = new Paciente{nombre, edad, peso, altura, nullptr};
    if (cabeza == nullptr) {
        cabeza = nuevoPaciente;
    } else {
        Paciente* temp = cabeza;
        while (temp->siguiente != nullptr) {
            temp = temp->siguiente; // se mueve al final de la lista
        }
        temp->siguiente = nuevoPaciente; // agrega el nuevo paciente al final
    }
}

// Muestra la lista de pacientes
void mostrarPacientes(Paciente* cabeza) {
    Paciente* temp = cabeza;
    while (temp != nullptr) {
        cout << "Nombre: " << temp->nombre << endl;
        cout << "Edad: " << temp->edad << " años" << endl;
        cout << "Peso: " << temp->peso << " kg" << endl;
        cout << "Altura: " << temp->altura << " m" << endl;
        cout << "-----------------------------" << endl;
        temp = temp->siguiente;
    }
}

// Elimina un paciente por su nombre
void eliminarPaciente(Paciente*& cabeza, const string& nombre) {
    if (cabeza == nullptr) return;

    if (cabeza->nombre == nombre) {
        Paciente* temp = cabeza;
        cabeza = cabeza->siguiente;
        delete temp; // Libera memoria
    } else {
        Paciente* temp = cabeza;
        while (temp->siguiente != nullptr && temp->siguiente->nombre != nombre) {
            temp = temp->siguiente;
        }
        if (temp->siguiente != nullptr) {
            Paciente* eliminar = temp->siguiente;
            temp->siguiente = eliminar->siguiente;
            delete eliminar; // Libera memoria
        }
    }
}

int main(){
    Paciente* listaPacientes = nullptr;

    // Agrega algunos pacientes
    agregarPaciente(listaPacientes, "Nicolas Morales", 19, 70.5, 1.71);
    agregarPaciente(listaPacientes, "Emilio Hernandez", 25, 60.2, 1.65);
    agregarPaciente(listaPacientes, "Sofia Leon", 40, 80.0, 1.80);

    cout << "Lista de Pacientes: " << endl;
    mostrarPacientes(listaPacientes);

    // Elimina un paciente
    cout << "Eliminando a Emilio Hernandez..." << endl;
    eliminarPaciente(listaPacientes, "Emilio Hernandez");
    cout << "-----------------------" << endl;
    cout << "Nueva lista de Pacientes: " << endl;
    mostrarPacientes(listaPacientes);
    cout << "-----------------------" << endl;
    cout << "Lista Actualizada:" << endl;
    mostrarPacientes(listaPacientes);

    // Libera memoria al final
    while (listaPacientes!= nullptr) {
        Paciente* temp = listaPacientes;
        listaPacientes = listaPacientes->siguiente;
        delete temp;
    }

    return 0;

}
