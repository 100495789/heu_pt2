#include <iostream> // Para cout
#include "grafo.hpp"
#include "abierta.hpp"
#include "cerrada.hpp"
#include "algoritmo.hpp"

#include <chrono>

using namespace std;

int main(int argc, char *argv[]){
    if (argc < 5) {
        cout << "introduzca el siguiente formato: \n ./parte-2.py vertice-1 vertice-2 nombre-del-mapa fichero-salid\n";
        return 1;
    }

    // asignamos las variables de entrada
    int vertice1 = std::stoi(argv[1]);
    int vertice2 = std::stoi(argv[2]);
    string nombre_mapa = argv[3];
    string fichero_salida = argv[4];
    auto start = chrono::high_resolution_clock::now();
    //A_star a_star;
    //a_star.a_star(vertice1, vertice2, nombre_mapa, fichero_salida);
    Dijkstra dijkstra;
    dijkstra.dijkstra(vertice1, vertice2, nombre_mapa, fichero_salida);
    auto end = std::chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed = end - start;
    //cout << "# vertices: " << a_star.grafo.num_vertices << "\n";
    cout << "Dijkstra desde el vertice " << vertice1 << " hasta el vertice " << vertice2 << "\n";
    cout << "# vertices: " << dijkstra.grafo.num_vertices << "\n";
    cout << "# arcos   : " << dijkstra.grafo.num_arcos << "\n";
    //cout << "Solución óptima con coste " <<  << "\n\n";
    
    //cout << "# arcos   : " << a_star.grafo.num_arcos << "\n";
    //cout << "Solución óptima con coste " << a_star.coste_final << "\n\n";
    cout << "Solución óptima con coste " << dijkstra.coste_final << "\n\n";

    cout << "Tiempo de ejecución: " << elapsed.count() << " segundos" << endl;
    //cout << "# expansiones      : " << a_star.num_expansiones << " ( " << a_star.num_nodos_expandidos/elapsed.count() << " nodos/sec)" << "\n";
    cout << endl;
    return 0;
}