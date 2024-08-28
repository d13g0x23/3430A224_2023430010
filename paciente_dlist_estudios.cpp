#include <iostream>
#include <string>

using namespace std;

struct Paciente {
    string nombre;
    int edad;
    double peso;
    double altura;
    Paciente* siguiente;
};


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

// Se le hizo una pequeña modificación para calcular el IMC al mostrarlo
void mostrarPacientes(Paciente* cabeza) {
    Paciente* temp = cabeza;
    while (temp!= nullptr) {
        cout << "Nombre: " << temp->nombre << endl;
        cout << "Edad: " << temp->edad << " años" << endl;
        cout << "Peso: " << temp->peso << " kg" << endl;
        cout << "Altura: " << temp->altura << " m" << endl;
        cout << "IMC: " << temp->peso / (temp->altura * temp-> altura) << endl;
        cout << "-----------------------------------" << endl;
        temp = temp->siguiente;
    }
}

// Calcula el promedio de las edades
double promedioEdad(Paciente* cabeza) {
    int sumaEdades = 0;
    int contador = 0;
    Paciente* temp = cabeza;
    while (temp != nullptr) {
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

int main() {
    Paciente* listaPacientes = nullptr;

    agregarPaciente(listaPacientes, "Nicolas Morales", 19, 70.5, 1.71);
    agregarPaciente(listaPacientes, "Emilio Hernandez", 25, 60.2, 1.65);
    agregarPaciente(listaPacientes, "Sofia Leon", 40, 80.0, 1.80);

    cout << "Lista de Pacientes: " << endl;
    mostrarPacientes(listaPacientes);

    // Ahora calcula y muestra el promedio de edad y peso
    cout << "Promedio de edades del grupo: " << promedioEdad(listaPacientes) << " años" << endl;
    cout << "Promedio de peso del grupo: " << promedioPeso(listaPacientes) << " kg" << endl;

    while (listaPacientes != nullptr) {
        Paciente* temp = listaPacientes;
        listaPacientes = listaPacientes->siguiente;
        delete temp;
    }

    return 0;
}
