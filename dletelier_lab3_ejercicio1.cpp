#include <iostream>

using namespace std;

class Pila {
    private:
    /*
        *pila: Arreglo dinámico que guarda los datos
        tope: el tope de la pila :v
        max: el tamaño máximo de la pila xdd
    */
        int *pila;
        int tope;
        int max;

    public:

    Pila(int tamMax) {
        max = tamMax;
        pila = new int[max];
        tope = 0; // Al inicio esta vacía
    }

    ~Pila() {
        delete[] pila; // Libera memoria -> *pila usa memoria dinámica 
    }

    // Verifica si está vacía la pila
    bool estaVacia() {
        return (tope == 0);
    }

    // Verifica si está llena la pila
    bool estaLlena() {
        return (tope == max);
    }

    // Agrega un elemento a la pila
    void push(int dato) {
        if (estaLlena()) {
            cout << "Desbordamiento, Pila Llena" << endl;
            return;
        } else {
            pila[tope] = dato;
            tope++;
        }
    }

    // Elimina un elemento de la pila
    void pop() {
        if (estaVacia()) {
            cout << "Subdesbordamiento, Pila Vacía" << endl;
        } else {
            tope--;
            cout << "Elemento eliminado: " << pila[tope] << endl;
        }
    }

    // Muestra el contenido de la pila
    void mostrarPila() {
        if (estaVacia()) {
            cout << "La Pila está Vacía" << endl;
        } else {
            cout << "Elementos en la Pila: " << endl;
            for (int i = tope - 1; i >= 0; i--) {
                cout << "|" << pila[i] << "|" << endl;
            }
        }
    }
};

int main() {
    int tamMax, opcion, dato;
    cout << "Ingrese el tamaño máximo de la pila: ";
    cin >> tamMax;

    Pila pila(tamMax);

    do {
        cout << "\nAgregar/Push [1]\nRemover/Pop [2]\nVer Pila [3]\nSalir [4]\nOpción: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                cout << "Ingrese un número: ";
                cin >> dato;
                pila.push(dato);
                break;
            case 2:
                pila.pop();
                break;
            case 3:
                pila.mostrarPila();
                break;
            case 4:
                cout << "Saliendo..." << endl;
                break;
            default:
                cout << "Opción inválida" << endl;
                break;
        }
    } while (opcion != 4);

    return 0;
}