#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>

using namespace std;

void intercambiar(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int particion(int* arreglo, int bajo, int alto) {
    int pivote = arreglo[alto]; // Elige el último elemento como pivote
    int i = bajo - 1;

    for (int k = bajo; k <= alto - 1; k++) {
        // Si el elemento actual es menor o igual al pivote
        if (arreglo[k] <= pivote) {
            i++;
            intercambiar(&arreglo[i], &arreglo[k]);
        }
    }
    intercambiar(&arreglo[i + 1], &arreglo[alto]); // Mueve el pivote a su posición correcta
    return (i + 1); // Devuelve el indice del pivote
}

void quickSort(int* arreglo, int bajo, int alto) {
    if (bajo < alto) {
        int pi = particion(arreglo, bajo, alto);

        // De forma recursiva ordena los subarreglos
        quickSort(arreglo, bajo, pi - 1); // Elementos antes del pivote
        quickSort(arreglo, pi + 1, alto); // Elementos después del pivote
    }
}

void seleccion(int* arreglo, int limite_arr) {
    for (int i = 0; i < limite_arr - 1; i++) {
        int indice_minimo = i; // Suponiendo que el primer elemento es el mínimo

        // Busca el elemento mínimo en el resto del arreglo
        for (int k = i + 1; k < limite_arr; k++) {
            if (arreglo[k] < arreglo[indice_minimo]) {
                indice_minimo = k; // Actualiza el índice del mínimo
            }
        }
        intercambiar(&arreglo[indice_minimo], &arreglo[i]);
    }
}

void llenarArreglo(int* arreglo, int limite_arr) {
    for (int i = 0; i < limite_arr; i++) {
        arreglo[i] = rand() % 10000 + 1;
    }
}

void mostrarArreglo(int* arreglo, int limite_arr) {
    for (int i = 0; i < limite_arr; i++) {
        cout << "a[" << i << "]=" << arreglo[i] << " ";
    }
    cout << endl;
}

int main(int argc, char **argv) {
    if (argc != 3) {
        cout << "Uso: " << argv[0] << " <tamaño_del_arreglo> <mostrar_contenido (s/n)>" << endl;
        return 1;
    }

    const int limite_arr = atoi(argv[1]);
    char ver = argv[2][0];

    if (limite_arr < 3) {
        cout << "\nEl número de elementos debe ser mayor que 2." << endl;
        return 1;
    }

    if (ver != 's' && ver != 'n') {
        cout << "\nEl parámetro VER debe ser 's' o 'n'" << endl;
        return 1;
    }

    // Dos arreglos dinámicos, uno para cada algoritmo
    int *arreglo_seleccion = new int[limite_arr];
    int *arreglo_quicksort = new int[limite_arr];

    srand(static_cast<unsigned int>(time(0)));
    llenarArreglo(arreglo_seleccion, limite_arr);

    for (int i = 0; i < limite_arr; i++) {
        arreglo_quicksort[i] = arreglo_seleccion[i];
    }

    if (ver == 's') {
        mostrarArreglo(arreglo_seleccion, limite_arr);
    }

    auto inicio1 = chrono::high_resolution_clock::now();
    seleccion(arreglo_seleccion, limite_arr);
    auto fin1 = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> duration_ms_s = (fin1 - inicio1);

    auto inicio2 = chrono::high_resolution_clock::now();
    quickSort(arreglo_quicksort, 0, limite_arr - 1);
    auto fin2 = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> duration_ms_q = (fin2 - inicio2);

    cout << "-----------------------------------------" << endl;
    cout << "Método            |Tiempo" << endl;
    cout << "-----------------------------------------" << endl;
    cout << "Seleccion         |" << duration_ms_s.count() << " milisegundos" << endl;
    cout << "Quicksort         |" << duration_ms_q.count() << " milisegundos" << endl;
    cout << "-----------------------------------------" << endl;

    if (ver == 's') {
        cout << "Selección: ";
        cout << "\n";
        mostrarArreglo(arreglo_seleccion, limite_arr);

        cout << "\nQuicksort: ";
        cout << "\n";
        mostrarArreglo(arreglo_quicksort, limite_arr);
    }
    
    delete[] arreglo_seleccion;
    delete[] arreglo_quicksort;

    return 0;
}