#include <iostream>
#include <string> // Para usar string

using namespace std; // Para usar cout sin std::

int es_par(int num){
    return (num % 2 == 0); // Retorna true si es par, false si es impar
}

int largo_string(const string& cadena){
    int largo = 0;
    for (auto it = cadena.begin(); it != cadena.end(); ++it) { // Para considerar caracteres raros (Me daba problemas con la ñ)
        if ((*it & 0xC0) != 0x80) {
            largo++;
        }
    }
    return largo;
}

int main(){
    int num;
    string cadena;

    cout<<"Ingrese un número: ";
    cin>>num;
    cout<<"Su número es: "<<num<<endl; // endl para saltar linea

    bool v_par = es_par(num); // llama a la funcion es_par retornando un booleano
    if (v_par == true ) {
        cout<<"Su número es par."<<endl;
    } else {
        cout<<"Su número es impar."<<endl;
    }

    cin.get(); // Captura el '\n' residual, tipo para limpiar la entrada

    cout<<"Ingrese una cadena de texto (string): ";
    getline(cin, cadena); // Captura la cadena completa 

    int largo_cadena = largo_string(cadena); // llama a la funcion largo_string retornando el largo
    cout<<"El largo de la cadena ingresada es: "<<largo_cadena<<endl;

    return 0;
}