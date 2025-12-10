#include <iostream> // Para cout
#include "grafo.hpp"
#include "abierta.hpp"
#include "cerrada.hpp"
#include "algoritmo.hpp"
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

    A_star a_star;
    a_star.a_star(vertice1, vertice2, nombre_mapa, fichero_salida);
    
   

    return 0;
}