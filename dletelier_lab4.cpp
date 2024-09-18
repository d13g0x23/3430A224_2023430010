#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <limits>

using namespace std;

/*
    Estructura que representa un nodo en el árbol binario
*/
struct Nodo {
    int dato;
    Nodo *izquierdo, *derecho;
};

/*
    Crea un nuevo nodo cone el valor dado y retorna el puntero al nodo creado
*/
Nodo* crearNodo(int valor) {
    Nodo* nuevoNodo = new Nodo();
    nuevoNodo->dato = valor;
    nuevoNodo->izquierdo = nuevoNodo->derecho = nullptr;
    return nuevoNodo;
}

/*
    Busca un valor en el árbol binario de búsqueda
*/
bool buscar(Nodo* raiz, int valor) {
    if (raiz == nullptr)
        return false; // No se encontró el valor
    if (raiz->dato == valor)
        return true; // El valor ya está en el árbol
    if (valor < raiz->dato)
        return buscar(raiz->izquierdo, valor);
    else
        return buscar(raiz->derecho, valor);
}

/*
    Inserta un valor en el árbol binario de búsqueda. Retorna la nueva raíz
*/
Nodo* insertar(Nodo* raiz, int valor) {
    if (raiz == nullptr)
        return crearNodo(valor);

    if (valor < raiz->dato)
        raiz->izquierdo = insertar(raiz->izquierdo, valor);
    else if (valor > raiz->dato)
        raiz->derecho = insertar(raiz->derecho, valor);

    return raiz;
}

/*
    Encuentra el nodo con el valor mínimo en un subárbol
*/
Nodo* buscarMinimo(Nodo* nodo) {
    while (nodo && nodo->izquierdo != nullptr)
        nodo = nodo->izquierdo;
    return nodo;
}

/*
    Elimina un nodo con un valor dado y retorna la nueva raíz del árbol
*/
Nodo* eliminar(Nodo* raiz, int valor) {
    if (raiz == nullptr)
        return raiz;

    if (valor < raiz->dato)
        raiz->izquierdo = eliminar(raiz->izquierdo, valor);
    else if (valor > raiz->dato)
        raiz->derecho = eliminar(raiz->derecho, valor);
    else {
        if (raiz->izquierdo == nullptr) {
            Nodo* temp = raiz->derecho;
            delete raiz;
            return temp;
        }
        else if (raiz->derecho == nullptr) {
            Nodo* temp = raiz->izquierdo;
            delete raiz;
            return temp;
        }

        Nodo* temp = buscarMinimo(raiz->derecho);
        raiz->dato = temp->dato;
        raiz->derecho = eliminar(raiz->derecho, temp->dato);
    }
    return raiz;
}

/*
    Recorre el árbol en preorden y muestra los valores
*/
void preorden(Nodo* raiz) {
    if (raiz != nullptr) {
        cout << raiz->dato << " ";
        preorden(raiz->izquierdo);
        preorden(raiz->derecho);
    }
}

/*
    Recorre el árbol en inorden y muestra los valores
*/
void inorden(Nodo* raiz) {
    if (raiz != nullptr) {
        inorden(raiz->izquierdo);
        cout << raiz->dato << " ";
        inorden(raiz->derecho);
    }
}

/*
    Recorre el árbol en postorden y muestra los valores
*/
void postorden(Nodo* raiz) {
    if (raiz != nullptr) {
        postorden(raiz->izquierdo);
        postorden(raiz->derecho);
        cout << raiz->dato << " ";
    }
}

/*
    Genera el grafo del árbol en formato Graphviz y lo guarda en un archivo
*/
void generarGrafo(Nodo* raiz, ofstream &archivo) {
    if (raiz != nullptr) {
        if (raiz->izquierdo != nullptr)
            archivo << raiz->dato << " -> " << raiz->izquierdo->dato << ";" << endl;
        if (raiz->derecho != nullptr)
            archivo << raiz->dato << " -> " << raiz->derecho->dato << ";" << endl;

        generarGrafo(raiz->izquierdo, archivo);
        generarGrafo(raiz->derecho, archivo);    
    }
}

/*
    Crea el archivo Graphviz y genera la imagen del árbol
*/
void generarArchivoGraphviz(Nodo* raiz) {
    ofstream archivo("grafo.txt");
    archivo << "digraph G {" << endl;
    archivo << "node [style=filled fillcolor=yellow];" << endl;
    generarGrafo(raiz, archivo);
    archivo << "}" << endl;
    archivo.close();

    system("dot -Tpng -ografo.png grafo.txt"); // Genera la imagen usnado Graphviz
}

/*
    Valida la entrada del usuario y asegura que solo se ingresen números enteros
*/
int obtenerNumero() {
    int numero;
    while (true) {
        cout << "Ingrese un número: ";
        cin >> numero;
        if (cin.fail()) {
            cout << "Entrada no válida. Intente nuevamente.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        } else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return numero;
        }
    }
}
int main() {
    Nodo* raiz = nullptr;
    int opcion, valor;

    do {
        cout << "\nMenu:\n";
        cout << "1. Insertar número\n";
        cout << "2. Eliminar número\n";
        cout << "3. Modificar número\n";
        cout << "4. Mostrar Preorden\n";
        cout << "5. Mostrar Inorden\n";
        cout << "6. Mostrar Postorden\n";
        cout << "7. Generar Grafo\n";
        cout << "8. Salir\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        if (cin.fail()) {
            cout << "Opción no válida. Intente nuevamente.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        switch (opcion) {
            case 1:
                valor = obtenerNumero();
                if (buscar(raiz, valor)) {
                    cout << "El número " << valor << " ya está en el árbol. No se permiten duplicados.\n";
                } else {
                    raiz = insertar(raiz, valor);
                }
                break;
            case 2:
                valor = obtenerNumero();
                raiz = eliminar(raiz, valor);
                break;
            case 3:
                int nuevoValor;
                cout << "Ingrese el número a modificar:\n ";
                valor = obtenerNumero();
                cout << "Ingrese el nuevo valor:\n ";
                nuevoValor = obtenerNumero();
                if (buscar(raiz, nuevoValor)) {
                    cout << "El nuevo número " << nuevoValor << " ya está en el árbol. No se permiten duplicados.\n";
                } else {
                    raiz = eliminar(raiz, valor);
                    raiz = insertar(raiz, nuevoValor);
                }
                break;
            case 4:
                cout << "Recorrido Preorden: ";
                preorden(raiz);
                cout << endl;
                break;
            case 5:
                cout << "Recorrido Inorden: ";
                inorden(raiz);
                cout << endl;
                break;
            case 6:
                cout << "Recorrido Postorden: ";
                postorden(raiz);
                cout << endl;
                break;
            case 7:
                generarArchivoGraphviz(raiz);
                cout << "Grafo generado como grafo.png\n";
                break;
            case 8:
                cout << "Saliendo...\n";
                break;
            default:
                cout << "Opcion Invalida.\n";
        }
    } while (opcion != 8);

    return 0;
}
