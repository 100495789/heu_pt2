#ifndef ABIERTA_HPP
#define ABIERTA_HPP

#include <iostream>
#include <string>
#include <set>

using namespace std;

struct Nodo
{
    // id del vertice
    int id;
    int longitud;
    int latitud;

    // g(n): costo acumulado desde nodo inicial hasta el nodo actual
    int g;
    //    # h(n): estimación del costo restante desde nodo actual n hasta nodo objetivo
    float h;
    //    # f(n): costo estimado del camino pasando por n
    float f;

    int id_padre;

    int coste;

};

class Comparacion_A_star {
    public:
        Comparacion_A_star();

        using is_transparent = void;
        bool operator() (const Nodo& nodo_max, const Nodo& nodo_nuevo) const;
        bool operator() (const int& id_a, const Nodo& nodo_b) const;
        bool operator() (const Nodo& nodo_a, const int& id_b) const;
};

class Comparacion_Dijkstra {
    public:
        Comparacion_Dijkstra();

        bool operator() (const Nodo& nodo_max, const Nodo& nodo_nuevo) const;
       
};


// 2. DECLARACIÓN DE LA CLASE GRAFO
class ListaAbierta
{
    public:
        
        //priority_queue<Nodo, vector<Nodo>, Comparacion> lista;
        set<Nodo, Comparacion_A_star> lista;


        // Constructor por defecto
        ListaAbierta();

        //Nodo buscar_nodo(int id);
        void insertar_nodo(Nodo nodo);
        Nodo pop();
        void imprimir_nodos();
        std::set<Nodo, Comparacion_A_star>::iterator buscar_nodo(int id);
        //void lista_prioridad(int g, int h);
};

#endif // ABIERTA_HPP