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
        int longitud_destino;
        int latitud_destino;
        int id_destino;
        int id_origen;
    
       
        bool exito = false;


public:

    A_star();
    
    Grafo grafo;
    int coste_final;
    int num_expansiones = 0;
    int num_nodos_expandidos = 0;
    ListaAbierta abierta;
    ListaCerrada cerrada;



    void a_star(int v_origen, int v_destino, string mapa_path, string output);
    float funcion_heuristica(int nodo_longitud, int nodo_latitud);
    vector<Arco> expandir_nodo(Nodo nodo);
    Nodo crear_nodo(int id, int longitud, int latitud, int g, int h, int nodoPadre, int coste);
    void escribir_solucion(const string& file_path,const vector<Nodo>& camino);

};


class Dijkstra{
    private:
        int id_destino;
        int id_origen;
        
    public:
        Grafo grafo;
        int coste_final;
        vector<Nodo> nodos;
        //pair<int, int> pii; // pair<distancia, nodo>
        priority_queue<Nodo, vector<Nodo>, Comparacion_Dijkstra> cola_prioridad;
    
        Dijkstra(); 
        void dijkstra(int v_origen, int v_destino, string mapa_path, string output);
        //void inicializar_nodos(vector<Vertice> vertices);
        void imprimir_camino(vector<int> Dist, vector<int> Prev, string output_path);
        //vector<Nodo> buscar_vecinos(Nodo nodo);
    };

#endif