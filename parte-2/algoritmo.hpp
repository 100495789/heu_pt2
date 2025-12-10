#ifndef ALGORITMO_HPP
#define ALGORITMO_HPP

#include <iostream> // Para cout
#include <string>
#include <vector>
#include <cmath>
#include "grafo.hpp"
#include "abierta.hpp"
#include "cerrada.hpp"


using namespace std;



class A_star{

    private:
        int longitud_destino;
        int latitud_destino;
        int id_destino;

        Grafo grafo;
        ListaAbierta abierta;
        ListaCerrada cerrada;
        bool exito = false;


public:

    A_star();
    

    void a_star(int v_origen, int v_destino, string mapa_path, string output);
    float funcion_heuristica(int nodo_longitud, int nodo_latitud);
    vector<Arco> expandir_nodo(Nodo nodo);
    Nodo crear_nodo(int id, int longitud, int latitud, int g, int h, int nodoPadre);


};

#endif