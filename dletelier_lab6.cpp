#include <iostream>
#include <fstream>
#include <limits.h>
#include <vector>
#include <stdlib.h>

using namespace std;

// Encuentra el vértice con la distancia mínima
int distanciaMinima(vector<int>& dist, vector<bool>& sptSet, int N) {
    int min = INT_MAX, min_index;

    // Recorre todos los nodos para encontrar el vértice con la distancia mínima
    for (int v = 0; v < N; v++) {
        // Busca el vértice no procesado con la menor distancia
        if (!sptSet[v] && dist[v] <= min) {
            min = dist[v]; // Actualiza la distancia mínima
            min_index = v; // Guarda el índice del vértice mínimo
        }
    }
    return min_index;    
}

// Imprime el arreglo de distancias
void printearDistancias(const vector<int>& dist, int N) {
    cout << "\nNodo \t Distancia desde el origen\n";
    for (int i = 0; i < N; i++) {
        cout << i << " \t\t " << dist[i] << "\n";
    }
}

// Escribe el grafo en un archivo para Graphviz
void escribirGraphviz(const vector<vector<int>>& graph, int N) {
    ofstream archivo("grafo.txt");
    archivo << "digraph G {\n";
    archivo << "graph [rankdir=LR];\n";
    archivo << "node [style=filled fillcolor=\"#00ff005f\"];\n";

    // Recorre la matriz de distancias y escribe las aristas con los pesos correspondientes
    for (int i = 0; i < N; i++) {
        for (int i2 = 0; i2 < N; i2++) {
            // Solo añade conexiones existentes (distancias, no -1)
            if (graph[i][i2] != -1 && i != i2) {
                archivo << i << " -> " << i2 << " [label=" << graph[i][i2] << "];\n"; // Representa una arista
            }
        }
    }
    archivo << "}\n";
    archivo.close();

    // Genera la imagen del grafo usando Graphviz
    system("dot -Tpng grafo.txt -o grafo.png");

    // Abre la imagen grafo.png
    system("eog grafo.png"); // '&' en segundo plano
}

// Algoritmo Dijkstra
void dijkstra(const vector<vector<int>>& graph, int origen, int N) {
    vector<int> dist(N, INT_MAX); // Arreglo de distancias
    vector<bool> sptSet(N, false); // Conjunto de nodos procesados

    dist [origen] = 0;

    // Procesa todos los vértices
    for (int contar = 0; contar < N - 1; contar++) {
        // Elige el vértice con la distancia mínima no procesado
        int k = distanciaMinima(dist, sptSet, N);
        sptSet[k] = true; // Narca el vértice como procesado

        // Actualiza la distancia de los vértices adyacentes del vértice seleccionado
        for (int v = 0; v < N; v++) {
            /*
                Se actualiza dist[v] si no ha sido procesado, hay un camino  desde k a v,
                y el nuevo camino es más corto que el anterior
            */
            if (!sptSet[v] && graph[k][v] != -1 && dist[k] != INT_MAX && dist[k] + graph[k][v] < dist[v]) {
                dist[v] = dist[k] + graph[k][v];
            }
        }
    }
    printearDistancias(dist, N);
}

int main() {
    int N;
    cout << "Ingrese el número de nodos: ";
    cin >> N;

    if (N <= 2) {
        cout << "El número de nodos debe ser mayor que 2.\n";
        return -1;
    }

    // Crea una matriz de NxN para representar el grafo de distancias
    vector<vector<int>> graph(N, vector<int>(N));

    cout << "\nIngrese la matriz de distancias (use -1 para indicar la ausencia de conexión):\n";
    cout << "\nEjemplo de Formato de entrada:\nn1 n2 n3\nn4 n5 n6\nn7 n8 n9\n" << endl;

    for (int i = 0; i < N; i++) {
        for (int k = 0; k < N; k++) {
            cin >> graph[i][k];
        }
    }

    cout << "\nMatriz de distancias ingresada:\n";
    for (int i = 0; i < N; i++) {
        for (int k = 0; k < N; k++) {
            cout << graph[i][k] << " ";
        }
        cout << "\n";
    }

    int origen;
    cout << "\nIngrese el vértice de origen: ";
    cin >> origen;

    // Llama a la función Dijkstra
    dijkstra(graph, origen, N);

    // Genera el archivo Graphviz
    escribirGraphviz(graph, N);

    return 0;
}
