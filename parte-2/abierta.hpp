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
    // g(n): costo acumulado desde nodo inicial hasta el nodo actual
    int g;
    //    # h(n): estimación del costo restante desde nodo actual n hasta nodo objetivo
    int h;
    //    # f(n): costo estimado del camino pasando por n
    int f;

    int id_padre;

};

class Comparacion {
    public:
        Comparacion ();

        using is_transparent = void;
        bool operator() (const Nodo& nodo_max, const Nodo& nodo_nuevo) const;
        bool operator() (const int& id_a, const Nodo& nodo_b) const;
        bool operator() (const Nodo& nodo_a, const int& id_b) const;
};


// 2. DECLARACIÓN DE LA CLASE GRAFO
class ListaAbierta
{
    public:
        
        //priority_queue<Nodo, vector<Nodo>, Comparacion> lista;
        set<Nodo, Comparacion> lista;


        // Constructor por defecto
        ListaAbierta();

        //Nodo buscar_nodo(int id);
        void insertar_nodo(Nodo nodo);
        Nodo pop();
        void imprimir_nodos();
        std::set<Nodo, Comparacion>::iterator buscar_nodo(int id);
        //void lista_prioridad(int g, int h);
};

#endif // ABIERTA_HPP