#ifndef ABIERTA_HPP
#define ABIERTA_HPP

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream> // Necesario para la lectura de coordenadas

#include "grafo.hpp"
// Usar std:: para evitar la contaminación global del namespace
// o añadir 'using namespace std;' si lo prefieres.
// Aquí usamos 'std::' para mayor seguridad.

struct Nodo
{
    // id del vertice
    int id;
    // g(n): costo acumulado desde nodo inicial hasta el nodo actual
    int g;
    //    # h(n): estimación del costo restante desde nodo actual n hasta nodo objetivo
    int h;
    //    # f(n): costo estimado del camino pasando por n
    int f = g + h;

    int id_padre;
};



// 2. DECLARACIÓN DE LA CLASE GRAFO
class ListaAbierta
{
    public:
        std::vector<Nodo> lista;


        // Constructor por defecto
        ListaAbierta();

        void insertar_nodo();
        Nodo pop();
        void lista_prioridad(int g, int h);
};

#endif // ABIERTA_HPP