#include <iostream>
#include <list>
#include <vector>

// Definición de la clase Graph
class Graph {
private:
    int V; // Número de vértices
    std::list<int> *adj; // Lista de adyacencia

    // Función auxiliar para DFS que realiza la búsqueda recursiva
    void DFSUtil(int v, std::vector<bool> &visited, int t, std::vector<int> &path) {
        // Marcar el nodo actual como visitado y añadirlo al camino
        visited[v] = true;
        path.push_back(v);

        // Si se llega al nodo destino, se imprime el camino y se retorna
        if (v == t) {
            for (int i : path) {
                std::cout << i << " ";
            }
            std::cout << std::endl;
            return;
        }

        // Recur para todos los vértices adyacentes al vértice actual
        for (auto i = adj[v].begin(); i != adj[v].end(); ++i) {
            if (!visited[*i]) {
                DFSUtil(*i, visited, t, path);
                // Si se encontró el nodo destino, se detiene la búsqueda
                if (path.back() == t) {
                    return;
                }
                // Si no se encontró, se elimina el nodo del camino actual y se continúa
                path.pop_back();
            }
        }
    }

public:
    // Constructor de Graph que inicializa el número de vértices y la lista de adyacencia
    Graph(int V) {
        this->V = V;
        adj = new std::list<int>[V];
    }

    // Función para agregar una arista al grafo
    void addEdge(int v, int w) {
        adj[v].push_back(w); // Añade w a la lista de v
    }

    // Función GRAPHdfs que inicia DFS en el nodo s y busca el nodo t
    void GRAPHdfs(int s, int t) {
        // Inicializar todos los vértices como no visitados
        std::vector<bool> visited(V, false);
        std::vector<int> path; // Para almacenar el camino

        // Llamar a la función auxiliar de DFS para imprimir el camino desde s a t
        DFSUtil(s, visited, t, path);
    }

    // Destructor de Graph
    ~Graph() {
        delete[] adj; // Liberar la memoria de la lista de adyacencia
    }
};

int main() {
    // Crear un grafo más complejo
    Graph g(8); // Digamos que hay 8 vértices numerados de 0 a 7
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 3);
    g.addEdge(1, 4);
    g.addEdge(2, 5);
    g.addEdge(3, 7);
    g.addEdge(4, 6);
    g.addEdge(5, 6);
    g.addEdge(6, 7);
    g.addEdge(7, 4); // Ciclo para hacerlo interesante

    // Realizar la búsqueda en profundidad desde diferentes nodos
    std::cout << "Camino desde el nodo 0 al nodo 7:" << std::endl;
    g.GRAPHdfs(0, 7);
    // Respuesta esperada: 0 1 3 7 (el camino exacto puede variar)

    std::cout << "Camino desde el nodo 2 al nodo 7:" << std::endl;
    g.GRAPHdfs(2, 7);
    // Respuesta esperada: 2 5 6 7 (el camino exacto puede variar)

    std::cout << "Camino desde el nodo 0 al nodo 6:" << std::endl;
    g.GRAPHdfs(0, 6);
    // Respuesta esperada: 0 1 4 6 (el camino exacto puede variar)

    std::cout << "Camino desde el nodo 5 al nodo 4:" << std::endl;
    g.GRAPHdfs(5, 4);
    // Respuesta esperada: 5 6 7 4 (el camino exacto puede variar)

    return 0;
}
// file_name: graph_path_dfs.cpp
// exec: g++ -o graph_path_dfs graph_path_dfs.cpp && ./graph_path_dfs
