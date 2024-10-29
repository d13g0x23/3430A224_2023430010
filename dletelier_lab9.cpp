#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

// Tamaño de la tabla hash
const int TABLE_SIZE = 20;
vector<int> TablaHash(TABLE_SIZE, -1);

/*
    Retorna el índice de la tabla hash para la clave dada
*/
int Hash(int clave) {
    return clave % TABLE_SIZE;
}

/*
    Calcula la posición en la tabla usando la prueba lineal
*/
int PruebaLineal(int clave, int i) {
    return (Hash(clave) + i) % TABLE_SIZE;
}

/*
    Calcula la posición en la tabla usando la prueba cuadrática
*/
int PruebaCuadratica(int clave, int i) {
    return (Hash(clave) + i * i) % TABLE_SIZE;
}

/*
    Calcula la posición en la tabla usando el doble hashing
*/
int DobleHash(int clave, int i) {
    int hash1 = Hash(clave);
    int hash2 = 1 + (clave % (TABLE_SIZE - 1));
    return (hash1 + i * hash2) % TABLE_SIZE;
}

/*
    Inserta una clave en la tabla hash utilizando el método especificado
*/
void Insertar(int clave, char metodo) {
    int i = 0; // Contador de intentos
    int posicion;
    bool insertado = false; // Indicador de inserción exitosa

    while (i < TABLE_SIZE && !insertado) {
        if (metodo == 'L') {
            posicion = PruebaLineal(clave, i);
        } else if (metodo == 'C') {
            posicion = PruebaCuadratica(clave, i);
        } else if (metodo == 'D') {
            posicion = DobleHash(clave, i);
        } else {
            cout << "Método no válido" << endl;
            return;
        }

        if (TablaHash[posicion] == -1) { // Si la posición está vacía
            TablaHash[posicion] = clave;
            insertado = true; // Marcar como onsertado
            cout << "Clave " << clave << " insertada en posición " << posicion << endl;
        } else {
            cout << "Colisión en posición " << posicion << " para la clave " << clave << " con desplazamiento " << i << endl;
            i++; // Incrementa el intento en caso de colisión
        }
    }

    if (!insertado) {
        cout << "No se pudo insertar la clave " << clave << ". ¡Tabla llena!" << endl;
    }
}

/*
    Busca una clave en la tabla hash utilizando el metódo especificado
*/
void Buscar(int clave, char metodo) {
    int i = 0; // Contador de intentos 
    int posicion; // En la tabla hash
    bool encontrado = false; // Indicador de búsqueda exitosa

    while (i < TABLE_SIZE) {
        if (metodo == 'L') {
            posicion = PruebaLineal(clave, i);
        } else if (metodo == 'C') {
            posicion = PruebaCuadratica(clave, i);
        } else if (metodo == 'D') {
            posicion = DobleHash(clave, i);
        } else {
            cout << "Método no válido" << endl;
            return;
        }

        if (TablaHash[posicion] == clave) { // Si la clave es encontrada
            cout << "Clave " << clave << " encontrada en posición " << posicion << endl;
            encontrado = true; // Marcar como encontrado
            break;
        } else if (TablaHash[posicion] == -1) { // Si se encuentra un espacio vacío
            break;
        } else {
            cout << "Colisión en posición " << posicion << " al buscar clave " << clave << " con desplazamiento " << i << endl;
            i++; // Incrementa el intento en caso de colisión
        }
    }

    if (!encontrado) {
        cout << "Clave " << clave << " no encontrada" << endl;
    }
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        cout << "Uso: " << argv[0] << " N {L|C|D}" << endl;
        return 1;
    }

    int N = atoi(argv[1]);
    char metodo = argv[2][0];
    if (metodo != 'L' && metodo != 'C' && metodo != 'D') {
        cout << "Método no válido. Use 'L' para Lineal, 'C' para Cuadrático o 'D' para Doble Hash" << endl;
        return 1;
    }

    
    srand(time(0));
    vector<int> claves(N);
    for (int i = 0; i < N; i++) {
        claves[i] = rand() % 100;
        cout << "Número aleatorio generado: " << claves[i] << endl;
    }

    /*
    // Para testeo
    vector<int> claves = {23, 42, 5, 66, 14};
    N = claves.size();  // Lo convierte en fijo para el testeo
    cout << "De testeo: {23, 42, 5, 66, 14}" << endl;
    */

    cout << "\nInsertando claves en la Tabla Hash:" << endl;
    for (int i = 0; i < N; i++) {
        Insertar(claves[i], metodo);
    }

    cout << "\nBuscando claves en la Tabla Hash:" << endl;
    for (int i = 0; i < N; i++) {
        Buscar(claves[i], metodo);
    }

    return 0;
}