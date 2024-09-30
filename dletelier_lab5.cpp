#include <iostream>
#include <fstream>
#include <cstdlib>
#include <limits>

using namespace std;

class Nodo {
    public:
        int valor;
        Nodo* izquierdo;
        Nodo* derecho;
        int altura;

    Nodo(int v) : valor(v), izquierdo(nullptr), derecho(nullptr), altura(1) {}
};

/*
    Obtiene la altura de un nodo
    Retorna la altura del nodo o 0 si es nulo
*/
int altura(Nodo* N) {
    return N == nullptr ? 0 : N->altura;
}

/*
    Obtiene el factor de equilibrio (FE) de un nodo
    Retorna el FE del nodo o 0 si es nulo
*/
int obtenerFactorEquilibrio(Nodo* N) {
    return N == nullptr ? 0 : altura(N->derecho) - altura(N->izquierdo);
}

/*
    Rota hacia la derecha
    El parametro "y" representa el nodo desbalanceado
    Retorna el nuevo nodo raiz después de la rotación
*/
Nodo* rotacionDerecha(Nodo* y) {
    Nodo* x = y->izquierdo;
    Nodo* T2 = x->derecho;

    x->derecho = y;
    y->izquierdo = T2;

    y->altura = max(altura(y->izquierdo), altura(y->derecho)) + 1;
    x->altura = max(altura(x->izquierdo), altura(x->derecho)) + 1;

    return x;
}

/*
    Rota hacia la izquierda
    El parametro "x" representa el nodo desbalanceado
    Retorna el nuevo nodo raiz después de la rotación
*/
Nodo* rotacionIzquierda(Nodo* x) {
    Nodo* y = x->derecho;
    Nodo* T2 = y->izquierdo;

    y->izquierdo = x;
    x->derecho = T2;

    x->altura = max(altura(x->izquierdo), altura(x->derecho)) + 1;
    y->altura = max(altura(y->izquierdo), altura(y->derecho)) + 1;

    return y;
}

/*
    Inserta un valor en el árbol
    Retorna el nuevo nodo raiz del subárbol después de la inserción
    Si el valor ya existe, muestra un mensaje y no lo inserta
*/
Nodo* insertar(Nodo* nodo, int valor) {
    if (nodo == nullptr) return new Nodo(valor);

    if (valor < nodo->valor)
        nodo->izquierdo = insertar(nodo->izquierdo, valor);
    else if (valor > nodo->valor)
        nodo->derecho = insertar(nodo->derecho, valor);
    else {
        cout << "El valor " << valor << " ya existe en el árbol.\n";
        return nodo; // Para valores duplicados
    }

    nodo->altura = max(altura(nodo->izquierdo), altura(nodo->derecho)) + 1;
    int balance = obtenerFactorEquilibrio(nodo);

    if (balance < -1 && valor < nodo->izquierdo->valor)
        return rotacionDerecha(nodo);

    if (balance > 1 && valor > nodo->derecho->valor)
        return rotacionIzquierda(nodo);

    if (balance < -1 && valor > nodo->izquierdo->valor) {
        nodo->izquierdo = rotacionIzquierda(nodo->izquierdo);
        return rotacionDerecha(nodo);
    }

    if (balance > 1 && valor < nodo->derecho->valor) {
        nodo->derecho = rotacionDerecha(nodo->derecho);
        return rotacionIzquierda(nodo);
    }

    return nodo;
}

/*
    Encuentra el nodo con el valor mínimo en un subárbol
    Retorna el nodo con el valor mínimo
*/
Nodo* minValueNode(Nodo* nodo) {
    Nodo* actual = nodo;
    while (actual->izquierdo != nullptr)
        actual = actual->izquierdo;
    return actual;
}

/*
    Elimina un nodo del árbol
    Retorna el nuevo nodo raíz del subárbol después de la eliminación
*/
Nodo* eliminar(Nodo* raiz, int valor) {
    if (raiz == nullptr) return raiz;

    if (valor < raiz->valor)
        raiz->izquierdo = eliminar(raiz->izquierdo, valor);
    else if (valor > raiz->valor)
        raiz->derecho = eliminar(raiz->derecho, valor);
    else {
        if ((raiz->izquierdo == nullptr) || (raiz->derecho == nullptr)) {
            Nodo* temp = raiz->izquierdo ? raiz->izquierdo : raiz->derecho;

            if (temp == nullptr) {
                temp = raiz;
                raiz = nullptr;
            } else 
                *raiz = *temp;
            delete temp;
        } else {
            Nodo* temp = minValueNode(raiz->derecho);
            raiz->valor = temp->valor;
            raiz->derecho = eliminar(raiz->derecho, temp->valor);
        }
    }

    if (raiz == nullptr) return raiz;

    raiz->altura = max(altura(raiz->izquierdo), altura(raiz->derecho)) + 1;

    int balance = obtenerFactorEquilibrio(raiz);

    // Realiza las rotaciones necesarias para equilibrar el árbol
    if (balance < -1 && obtenerFactorEquilibrio(raiz->izquierdo) <= 0)
        return rotacionDerecha(raiz);

    if (balance < -1 && obtenerFactorEquilibrio(raiz->izquierdo) > 0) {
        raiz->izquierdo = rotacionIzquierda(raiz->izquierdo);
        return rotacionDerecha(raiz);
    }

    if (balance > 1 && obtenerFactorEquilibrio(raiz->derecho) >= 0)
        return rotacionIzquierda(raiz);

    if (balance > 1 && obtenerFactorEquilibrio(raiz->derecho) < 0) {
        raiz->derecho = rotacionDerecha(raiz->derecho);
        return rotacionIzquierda(raiz);
    }

    return raiz;
}

/*
    Genera el grafo de la estructura del árbol en formato Graphviz
*/
void generarGrafo(Nodo* raiz, ofstream& archivo) {
    if (raiz != nullptr) {
        archivo << raiz->valor << "[label=\"" << raiz->valor << " (FE=" << obtenerFactorEquilibrio(raiz) << ")\"];\n";
        if (raiz->izquierdo != nullptr) {
            archivo << raiz->valor << " -> " << raiz->izquierdo->valor << ";\n";
            generarGrafo(raiz->izquierdo, archivo);
        } else {
            archivo << "null" << raiz->valor << " [shape=point];\n";
            archivo << raiz->valor << " -> null" << raiz->valor << ";\n";
        }
        if (raiz->derecho != nullptr) {
            archivo << raiz->valor << " -> " << raiz->derecho->valor << ";\n";
            generarGrafo(raiz->derecho, archivo);
        } else {
            archivo << "null" << raiz->valor << "d [shape= point];\n";
            archivo << raiz->valor << " -> null" << raiz->valor << "d;\n";
        }
    }
}

/*
    Lee números enteros válidos desde la entrada
    Retorna un número entero válido ingresado por el usuario
*/
int leerEntero() {
    int valor;
    while (true) {
        cin >> valor;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Entrada no válida. Por favor, ingrese un parametro valido: ";
        } else {
            return valor;
        }
    }
}

/*
    Imprime los nodos del árbol en orden ascendente
*/
void imprimirEnOrden(Nodo* raiz) {
    if (raiz != nullptr) {
        imprimirEnOrden(raiz->izquierdo);
        cout << raiz->valor << " ";
        imprimirEnOrden(raiz->derecho);
    }
}

int main() {
    Nodo* raiz = nullptr;
    int opcion, valor, nuevoValor;
    do {
        cout << "\nMenu\n";
        cout << "1. Insertar\n2. Eliminar\n3. Modificar\n4. Generar Grafo\n5. Salir\nOpción: ";
        opcion = leerEntero();
        switch (opcion) {
            case 1:
                cout << "Ingrese un valor: ";
                valor = leerEntero();
                raiz = insertar(raiz, valor);
                break;
            case 2:
                if (raiz == nullptr) {
                    cout << "El árbol está vació.\n";
                } else {
                    cout << "Nodos disponibles: ";
                    imprimirEnOrden(raiz);
                    cout << "\nIngrese un valor a eliminar: ";
                    valor = leerEntero();
                    raiz = eliminar(raiz, valor);
                }
                break;
            case 3:
                if (raiz == nullptr) {
                    cout << "El árbol está vació.\n";
                } else {
                    cout << "Nodos disponibles: ";
                    imprimirEnOrden(raiz);
                    cout << "\nIngrese un valor a modificar: ";
                    valor = leerEntero();
                    raiz = eliminar(raiz, valor);
                    cout << "Ingrese un nuevo valor: ";
                    nuevoValor = leerEntero();
                    raiz = insertar(raiz, nuevoValor);
                }
                break;
            case 4: {
                ofstream archivo("grafo.txt");
                archivo << "digraph G {\n";
                generarGrafo(raiz, archivo);
                archivo << "}\n";
                archivo.close();
                system("dot -Tpng -ografo.png grafo.txt");
                system("eog grafo.png");
                break;
            }
            case 5:
                cout << "Saliendo...\n";
                break;
            default:
                cout << "Opción inválida\n";
        }
    } while (opcion != 5);

    return 0;
}
