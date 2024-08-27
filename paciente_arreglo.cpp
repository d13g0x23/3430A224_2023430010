#include <iostream>

using namespace std;

struct Paciente {
    string nombre;
    int edad;
    double peso;
    double altura;
};

int main() {

    Paciente pacientes[3];

    pacientes[0].nombre = "Nicolas Morales";
    pacientes[0].edad = 19;
    pacientes[0].peso = 70.5;
    pacientes[0].altura = 1.71;

    pacientes[1].nombre = "Emilio Hernandez";
    pacientes[1].edad = 25;
    pacientes[1].peso = 60.2;
    pacientes[1].altura = 1.65;

    pacientes[2].nombre = "Sofia Leon";
    pacientes[2].edad = 40;
    pacientes[2].peso = 80.0;
    pacientes[2].altura = 1.80;


    int i=0;
    while (i!=3) {
        cout << "Nombre: " << pacientes[i].nombre << endl;
        cout << "Edad: " << pacientes[i].edad << " años" << endl;
        cout << "Peso: " << pacientes[i].peso << " kg" << endl;
        cout << "Altura: " << pacientes[i].altura << " m" << endl;
        cout << "----------------------------------" << endl;
        i++;
    }
}
   