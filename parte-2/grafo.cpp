#include <fstream>  // Para ofstream
#include <iostream> // Para cout
#include <vector>
#include <string>
#include <utility>
#include <fstream>  // Para ifstream

#include "grafo.hpp"

//https://www.luisllamas.es/cpp-clases/
//info sacada de https://dev.to/greedyboy/como-implementar-grafos-en-c-3ia2
//https://www2.eii.uva.es/fund_inf/cpp/temas/10_ficheros/ficheros_cpp.html?highlight=getline

// Para implementar el grafo vamos a necesitar un par de estructuras:
// 1- Vertice
// 2- Arco que une un vertice a otro


Grafo::Grafo() = default;

void Grafo::leer_fichero_coordenadas(const string nombre_mapa){
    const string coor_fichero = nombre_mapa + ".co";
    ifstream fichero(coor_fichero);

    cout << "estamos dentro" << endl;
    if (!fichero.is_open())
    {
        cout << "Error al abrir " << coor_fichero << "\n";
        exit(EXIT_FAILURE);
    }
            
            
    string linea;
    // ignoramos primeras filas q no nos interesan
    while (fichero >> linea && linea != "v"){

    }
    

    int id, longi, lati;
    string valor ;
    while (fichero){
    // el formato es v 1 -73530767 41085396
        fichero >> id;
        fichero >> longi;
        fichero >> lati;
        añadir_vertices( id, longi, lati);
        fichero >> valor; // tenemos que leer el proximo v al final xq el primero ha silo leido en el bucle anterior
    }
    return ;
}

void Grafo::leer_fichero_grafico(const string nombre_mapa){
    const string graf_fichero = nombre_mapa + ".gr";
    ifstream fichero(graf_fichero);

    cout << "estamos dentro" << endl;
    if (!fichero.is_open())
    {
        cout << "Error al abrir " << graf_fichero << "\n";
        exit(EXIT_FAILURE);
    }
    
    
    string valor ;
    // ignoramos primeras filas q no nos interesan
    while (fichero >> valor && valor != "a"){
        // ignoramos todo
    }
    
    // si salimos es xq hemos llegado al primer vertice y vertice
    int v1, v2, coste;
    
    //lista_adjaciencia.resize(num_vertices + 1);

    while (fichero){
    // el formato es v 1 -73530767 41085396
        fichero >> v1;
        fichero >> v2;
        fichero >> coste;
        añadir_arcos( v1, v2, coste);
        fichero >> valor; // tenemos que leer el proximo v al final xq el primero ha silo leido en el bucle anterior
    }


    return ;
}

void Grafo::añadir_vertices (int id, int longi, int latitud) {
    
    Vertice v;
    v.id = id;
    v.longitud = longi;
    v.latitud = latitud;
    if (id >= (int)vertices.size()) {
        vertices.resize(id + 1);
    }
    vertices[id] = v;
    num_vertices++;
    return;
}

void Grafo::mostrar_vertices()
{ // funcion para comprobar la correcta lectura
    cout << "\nLos vertices;\n\n";
    for (int i = 0; i < 10; ++i) {
        cout  << vertices[i].id << " ";}
    cout << endl << vertices.size() -1 << endl << num_vertices << endl;
    return;
}

void Grafo::añadir_arcos(int v_origen, int v_destino, int coste) {
    Arco a;
    a.idDestino = v_destino;
    a.coste = coste;
    if (v_origen >= (int)lista_adjaciencia.size()) {
        lista_adjaciencia.resize(v_origen + 1);
    }
    
    // dentro del vertice v_origen colocamos ultimo el nuevo arco
    lista_adjaciencia[v_origen].push_back(a); 
    num_arcos++;

}


void Grafo::imprimir_lista(){
    //for(int i = 0; i < lista_adjaciencia.size(); i++){
    for(int i = 0; i < 10; i++){
        cout << "Vertice " << i << ": ";
        
        for(int j = 0; j < lista_adjaciencia[i].size(); j++){
            const Arco& arco = lista_adjaciencia[i][j];
            cout << arco.idDestino << " ";
        }
        cout << "\n";
    }
}

pair<int, int> Grafo::buscar_vertice(int id){
    
    return pair<int, int>(vertices[id].longitud, vertices[id].latitud);
}


