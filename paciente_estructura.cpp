#include <iostream>
#include <string>

using namespace std;

struct Paciente { // Defino la estructura Persona
    string nombre;
    int edad;
    double peso;
    double altura;
};

int main() {

    // Creo los pacientes
    Paciente paciente1 = {"Nicolas Morales", 19, 70.5, 1.71};
    Paciente paciente2 = {"Emilio Hernandez", 25, 60.2, 1.65};
    Paciente paciente3 = {"Sofia Leon", 40, 80.0, 1.80};

    // Muestra la info
    cout << "Info. Paciente 1: " << endl; // Paciente 1
    cout << "Nombre: " << paciente1.nombre << endl;
    cout << "Edad: " << paciente1.edad << " años" << endl;
    cout << "Peso: " << paciente1.peso << " kg" << endl;
    cout << "Altura: " << paciente1.altura << " m" << endl << endl;

    cout << "Info. Paciente 2: " << endl; // Paciente 2
    cout << "Nombre: " << paciente2.nombre << endl;
    cout << "Edad: " << paciente2.edad << " años" << endl;
    cout << "Peso: " << paciente2.peso << " kg" << endl;
    cout << "Altura: " << paciente2.altura << " m" << endl << endl;

    cout << "Info. Paciente 3: " << endl; // Paciente 3
    cout << "Nombre: " << paciente3.nombre << endl;
    cout << "Edad: " << paciente3.edad << " años" << endl;
    cout << "Peso: " << paciente3.peso << " kg" << endl;
    cout << "Altura: " << paciente3.altura << " m" << endl << endl;

    return 0;

}
