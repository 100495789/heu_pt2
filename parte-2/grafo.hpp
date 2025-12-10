#ifndef GRAFO_HPP
#define GRAFO_HPP

#include <iostream>
#include <vector>
#include <utility>
#include <string>
#include <fstream>
#include <sstream> // Necesario para la lectura de coordenadas
using namespace std;

// Usar std:: para evitar la contaminación global del namespace
// o añadir 'using namespace std;' si lo prefieres.
// Aquí usamos 'std::' para mayor seguridad.

// 1. ESTRUCTURA VERTICE
struct Vertice
{
    int id; 
    int longitud;
    int latitud;
};

// 2. ESTRUCTURA ARCO
struct Arco
{   
    int idDestino;
    int coste;
};

// 3. DECLARACIÓN DE LA CLASE GRAFO
class Grafo
{
    public:
        std::vector<Vertice> vertices;
        std::vector<std::vector<Arco>> lista_adjaciencia;

        int num_vertices = 0;
        int num_arcos = 0;
        
    
        // Constructor por defecto
        Grafo();

        // Funciones de Lectura y Creación
        void leer_fichero_coordenadas(const std::string nombre_mapa);
        void añadir_vertices (int id, int longi, int latitud);
        void leer_fichero_grafico(const std::string nombre_mapa);
        void añadir_arcos(int v_origen, int v_destino, int coste);
        pair<int, int> buscar_vertice(int id);
        // Funciones de Impresión y Utilidad
        void mostrar_vertices();
        void imprimir_lista();
        void mostrar_lista_adyacencia(int v_inicio, int v_fin = 10);
};

#endif // GRAFO_HPP