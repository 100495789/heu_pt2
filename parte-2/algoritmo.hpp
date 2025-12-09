#ifndef ALGORITMO_HPP
#define ALGORITMO_HPP

#include <iostream> // Para cout
#include <string>
#include <vector>

#include "grafo.hpp"
#include "abierta.hpp"
#include "cerrada.hpp"


using namespace std;



class A_star{
public:
    bool exito = false;

    A_star();
    Grafo grafo;
    ListaAbierta abierta;
    ListaCerrada cerrada;

    void a_star(int v_origen, int v_destino, string mapa_path, string output);
    int funcion_heuristica();
    vector<Arco> expandir_nodo(Nodo nodo);
    Nodo crear_nodo(int id, int g, int h, int nodoPadre);


};

#endif