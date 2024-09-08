#include <iostream>
#include <stack>
#include <vector>
#include <string>
#include <limits> 

using namespace std;

struct Contenedor {
    int numero;
    string empresa;
};

/*
    Limpia la entrada del cin en caso de errores. Restablece
    el estado de cin con cin.clear() y descarta cualquier entrada no
    válida utilizando cin.ignore(). Esto asegura que no queden datos no
    deseados en el buffer de entrada
*/
void limpiarEntrada() {
    cin.clear(); 
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
}

/*
    Muestra el contenido de cada pila de contenedores. Recorre cada pila y
    muestra los números y las empresas de los contenedores en orden. Para no
    alterar las pilas originales, usa una pila temporal temp para
    desapilar y mostrar los datos
*/
void mostrarPilas(const vector<stack<Contenedor>> &pilas) {
    for (size_t i = 0; i < pilas.size(); i++) {  
        cout << "Pila " << i + 1 << ":";
        stack<Contenedor> temp = pilas[i];
        while (!temp.empty()) {
            cout << temp.top().numero << "/" << temp.top().empresa << " ";
            temp.pop();
        }
        cout << endl;
    }
}

/*
    Agrega un nuevo contenedor a la primera pila que tenga espacio.
    Recorre las pilas buscando una con menos de maxHeight contenedores y,
    si encuentra una, añade el contenedor a esa pila. Si no encuentra
    espacio, muestra un error
*/
void agregarContenedor(vector<stack<Contenedor>> &pilas, int maxHeight, Contenedor nuevo) {
    for (size_t i = 0; i < pilas.size(); i++) {  
        if (pilas[i].size() < static_cast<size_t>(maxHeight)) {  
            pilas[i].push(nuevo);
            cout << "Contenedor " << nuevo.numero << "/" << nuevo.empresa << " agregado a la Pila " << i + 1 << endl;
            return;
        }
    }
    cout << "No hay espacio para agregar el contenedor." << endl;
}

/*
    Mueve contenedores de una pila temporal temp a las pilas principales,
    respetando el límite de maxHeight. Trata de colocar cada contenedor en las 
    pilas hasta que estén todas llenas o los contenedores se hayan colocado. Si no
    hay espacio; retorna false
*/
bool moverContenedores(vector<stack<Contenedor>>& pilas, int maxHeight, stack<Contenedor>& temp) {
    while (!temp.empty()) {
        bool colocado = false;
        for (size_t i = 0; i < pilas.size(); i++) {  
            if (pilas[i].size() < static_cast<size_t>(maxHeight)) {  
                pilas[i].push(temp.top());
                cout << "Contenedor " << temp.top().numero << "/" << temp.top().empresa << " movido a la Pila " << i + 1 << endl;
                temp.pop();
                colocado = true;
                break;
            }
        }
        if (!colocado) {
            cout << "No hay espacio suficiente para mover los contenedores." << endl;
            return false;
        }
    }
    return true;
}

/*
    Retira un contenedor de una de las pilas, segun su número y empresa.
    Recorre cada pila buscando el contenedor, almacenando temporalmente los
    contenedores superiores en una pila temporal temp mientras encuentra el 
    contenedor. Luego, usa moverContenedores para volver a colocar los contenedores
    temporalmente movidos
*/
void retirarContenedor(vector<stack<Contenedor>>& pilas, int maxHeight, int numero, const string &empresa) {
    bool encontrado = false;
    for (size_t i = 0; i < pilas.size(); i++) {  
        stack<Contenedor> temp;  
        
        while (!pilas[i].empty()) {
            Contenedor contenedor = pilas[i].top();
            pilas[i].pop();
            if (contenedor.numero == numero && contenedor.empresa == empresa) {
                encontrado = true;
                cout << "Contenedor " << contenedor.numero << "/" << contenedor.empresa << " retirado de la Pila " << i + 1 << endl;
                break;
            } else {
                temp.push(contenedor);  
            }
        }
        if (encontrado) {
            moverContenedores(pilas, maxHeight, temp);
            mostrarPilas(pilas);
            return;
        }
    }
    if (!encontrado) {
        cout << "El Contenedor no fue encontrado." << endl;
    }
}

int main() {
    int maxHeight, numPilas, opcion, numero;
    string empresa;

    
    while (true) {
        cout << "Ingrese el número máximo de contenedores por pila (n): ";
        cin >> maxHeight;
        if (cin.fail() || maxHeight <= 0) {
            cout << "Entrada inválida. Por favor, ingrese un número entero positivo." << endl;
            limpiarEntrada(); 
        } else {
            break;
        }
    }

    
    while (true) {
        cout << "Ingrese el número máximo de pilas (m): ";
        cin >> numPilas;
        if (cin.fail() || numPilas <= 0) {
            cout << "Entrada inválida. Por favor, ingrese un número entero positivo." << endl;
            limpiarEntrada();
        } else {
            break;
        }
    }

    vector<stack<Contenedor>> pilas(numPilas); // Inicializa m pilas de contenedores

    do {
        cout << "\nAgregar Contenedor [1]\nRetirar Contenedor [2]\nMostrar Pilas [3]\nSalir [4]\nOpción: ";
        cin >> opcion;

        
        if (cin.fail()) {
            cout << "Entrada inválida. Por favor, ingrese un número válido." << endl;
            limpiarEntrada();
            continue;
        }

        switch (opcion) {
            case 1:
                
                while (true) {
                    cout << "Ingrese número de contenedor: ";
                    cin >> numero;
                    if (cin.fail() || numero <= 0) {
                        cout << "Entrada inválida. Por favor, ingrese un número entero positivo." << endl;
                        limpiarEntrada();
                    } else {
                        break;
                    }
                }

                cout << "Ingrese nombre de la empresa: ";
                cin >> empresa;  
                agregarContenedor(pilas, maxHeight, {numero, empresa});
                break;

            case 2:
                
                while (true) {
                    cout << "Ingrese número de contenedor para retirar: ";
                    cin >> numero;
                    if (cin.fail() || numero <= 0) {
                        cout << "Entrada inválida. Por favor, ingrese un número entero positivo." << endl;
                        limpiarEntrada();
                    } else {
                        break;
                    }
                }

                cout << "Ingrese nombre de la empresa: ";
                cin >> empresa;
                retirarContenedor(pilas, maxHeight, numero, empresa);
                break;
            
            case 3:
                mostrarPilas(pilas);
                break;

            case 4:
                cout << "Saliendo del programa..." << endl;
                break;

            default:
                cout << "Opción inválida." << endl;
                break;
        }
    } while (opcion != 4);

    return 0;
}
