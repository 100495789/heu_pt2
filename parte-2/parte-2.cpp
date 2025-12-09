#include <fstream>  // Para ofstream
#include <iostream> // Para cout
#include "grafo.hpp"
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

    cout << vertice1 <<"\n";
    cout << vertice2 <<"\n";
    cout << nombre_mapa <<"\n";
    cout << fichero_salida <<"\n";

    Grafo grafo;
    grafo.leer_fichero_coordenadas(nombre_mapa);
    grafo.leer_fichero_grafico(nombre_mapa);

    return 0;
}