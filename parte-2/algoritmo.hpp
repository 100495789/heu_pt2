#ifndef ALGORITMO_HPP
#define ALGORITMO_HPP

#include <iostream> // Para cout
#include <string>
#include <vector>
#include <cmath>
#include <queue>
#include "grafo.hpp"
#include "abierta.hpp"
#include "cerrada.hpp"

#define oo 0x3f3f3f3f

using namespace std;



class A_star{

    private:
        double longitud_destino;
        double latitud_destino;
        int id_destino;
        int id_origen;
        double funcion_heuristica(double nodo_longitud, double nodo_latitud);
        Nodo crear_nodo(int id, double longitud, double latitud, int g, double h, int nodoPadre);
        void escribir_solucion(const string& file_path,const vector<Nodo>& camino);
        bool exito = false;


public:

    A_star();
    ListaAbierta abierta;
    ListaCerrada cerrada;
    Grafo grafo;

    int coste_final;
    int num_expansiones = 0;
    int num_nodos_expandidos = 0;
    
    bool a_star(int v_origen, int v_destino, string mapa_path, string output);
    
};


class Dijkstra{
    private:
        int id_destino;
        int id_origen;
        vector<int> distancias; // vector para rastrear las distancias mínimas
        vector<int> padres; // vector para rastrear los padres de cada nodo
        priority_queue<Nodo, vector<Nodo>, Comparacion_Dijkstra> cola_prioridad;

        void imprimir_camino(string output_path);

    public:
        Grafo grafo;
        int coste_final;
        int num_expansiones = 0;
        int num_nodos_expandidos = 0;
        
        Dijkstra(); 

        void dijkstra(int v_origen, int v_destino, string mapa_path, string output);
        //void inicializar_nodos(vector<Vertice> vertices);
        //vector<Nodo> buscar_vecinos(Nodo nodo);
    };

#endif