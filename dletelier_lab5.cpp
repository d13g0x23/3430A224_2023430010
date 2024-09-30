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

int altura(Nodo* N) {
    return N == nullptr ? 0 : N->altura;
}

int obtenerFactorEquilibrio(Nodo* N) {
    return N == nullptr ? 0 : altura(N->derecho) - altura(N->izquierdo);
}

Nodo* rotacionDerecha(Nodo* y) {
    Nodo* x = y->izquierdo;
    Nodo* T2 = x->derecho;

    x->derecho = y;
    y->izquierdo = T2;

    y->altura = max(altura(y->izquierdo), altura(y->derecho)) + 1;
    x->altura = max(altura(x->izquierdo), altura(x->derecho)) + 1;

    return x;
}

Nodo* rotacionIzquierda(Nodo* x) {
    Nodo* y = x->derecho;
    Nodo* T2 = y->izquierdo;

    y->izquierdo = x;
    x->derecho = T2;

    x->altura = max(altura(x->izquierdo), altura(x->derecho)) + 1;
    y->altura = max(altura(y->izquierdo), altura(y->derecho)) + 1;

    return y;
}

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

Nodo* minValueNode(Nodo* nodo) {
    Nodo* actual = nodo;
    while (actual->izquierdo != nullptr)
        actual = actual->izquierdo;
    return actual;
}

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
