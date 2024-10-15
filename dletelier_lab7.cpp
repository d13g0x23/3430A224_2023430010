#include <iostream>
#include <vector>
#include <limits.h>
#include <fstream>
#include <cstdlib>

using namespace std;

class Grafo {
    private:
        int N; 
        vector<vector<int>> matriz; 
        vector<pair<int, int>> L; 

    public:
        Grafo(int N) : N(N), matriz(N, vector<int>(N)) {}

        // Lee la matriz de distancias desde la terminar
        void leerMatriz() {
            cout << "Ingrese la matriz de distancias (use 0 para indicar la falta de conexión):\n";
            for (int i = 0; i < N; i++) {
                for (int j = 0; j < N; j++) {
                    cin >> matriz[i][j];
                }
            }
        }

        // Encuentra el nodo con la distancia mínima que no ha sido incluido en el MST
        int encontrarNodoDistanciaMinima(vector<int>& llave, vector<bool>& arbol_costo_minimo) {
            int min = INT_MAX, indice_minimo;

            for (int i = 0; i < N; i++) {
                if (!arbol_costo_minimo[i] && llave[i] < min) {
                    min = llave[i];
                    indice_minimo = i;
                }
            }
            return indice_minimo;
        }

        // El algoritmo PRIM :V
        void algoritmo_PRIM() {
            vector<int> padre(N); 
            vector<int> llave(N, INT_MAX); 
            vector<bool> arbol_costo_minimo(N, false); 

            llave[0] = 0; 
            padre[0] = -1; 

            for (int contar = 0; contar < N - 1; contar++) {
                int w = encontrarNodoDistanciaMinima(llave, arbol_costo_minimo); 
                arbol_costo_minimo[w] = true; 

                for (int k = 0; k < N; k++) {
                    if (matriz[w][k] && !arbol_costo_minimo[k] && matriz[w][k] < llave[k]) {
                        padre[k] = w;
                        llave[k] = matriz[w][k];
                    }
                }
            }

            
            cout << "\nArista   Peso\n";
            for (int i = 1; i < N; i++) {
                L.push_back({padre[i], i});
                cout << padre[i] << " - " << i << "    " << matriz[i][padre[i]] << endl;
            }
        }

        // Genera el grafo original
        void generarGrafoOriginal() {
            ofstream archivo("grafo_original.dot");
            archivo << "graph G {\n";
            archivo << "graph [rankdir=LR];\n";
            archivo << "node [style=filled fillcolor=\"#00ff005f\"];\n";
            for (int i = 0; i < N; i++) {
                for (int k = i + 1; k < N; k++) {
                    if (matriz[i][k] != 0) {
                        archivo << i << " -- " << k << " [label=" << matriz[i][k] << "];\n";
                    }
                }
            }
            archivo << "}\n";
            archivo.close();
            cout << "Archivo 'grafo_original.dot' generado correctamente.\n";

            system("dot -Tpng grafo_original.dot -o grafo_original.png");

        }

        // Genera el grafo con costo minimo
        void generarGrafoMinimo() {
            ofstream archivo("grafo_minimo.dot");
            archivo << "graph G {\n";
            archivo << "graph [rankdir=LR];\n";
            archivo << "node [style=filled fillcolor=\"#00ff005f\"];\n";
            for (auto arista : L) {
                int t = arista.first;
                int a = arista.second;
                archivo << t << " -- " << a << " [label=" << matriz[t][a] << "];\n";
            }
            archivo << "}\n";
            archivo.close();
            cout << "Archivo 'grafo_minimo.dot' generado correctamente.\n";

            system("dot -Tpng grafo_minimo.dot -o grafo_minimo.png");
            
        }

        // Muestra el conjunto L
        void mostrarConjuntoL() {
            cout << "\nConjunto L (aristas del MST):\n";
            for (auto arista : L) {
                cout << arista.first << " - " << arista.second << endl;
            }
        }
};

int main() {
    int N;
    cout << "Ingrese el número de nodos: ";
    cin >> N;

    
    if (N < 2) {
        cout << "El número de nodos debe ser mayor que 2." << endl;
        return 1;
    }

    Grafo grafo(N);

    grafo.leerMatriz();
    grafo.generarGrafoOriginal();
    grafo.algoritmo_PRIM();
    grafo.generarGrafoMinimo();
    grafo.mostrarConjuntoL();

    system("eog grafo_original.png");

    return 0;
}
