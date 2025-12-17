#include "grafo.hpp"
#include "abierta.hpp"
#include "cerrada.hpp"

#include <algorithm>
#include "algoritmo.hpp"

#include <limits>

#include <iostream> // Para cout
using namespace std;

A_star::A_star() = default;

bool A_star::a_star(int v_origen, int v_destino, string mapa_path, string output){
    // 1. Leemos el grafo para saber cuántos vértices hay
    grafo.leer_fichero_coordenadas(mapa_path);
    grafo.leer_fichero_grafico(mapa_path);
    
    // 2. Inicializamos el vector auxiliar de la lista cerrada con el tamaño exacto (num_vertices + 1)
    //vector<int> visitados_en_cerrada(grafo.num_vertices + 1, -1);
    cerrada.visitados.resize(grafo.num_vertices + 1, -1);
    // constantes del destino
   // pair<double, double> atributosFinal = grafo.buscar_vertice(v_destino);
    longitud_destino = grafo.vertices[v_destino].longitud;
    latitud_destino = grafo.vertices[v_destino].latitud;
    id_destino = v_destino;

    // 3. Crear el nodo inicial y añadirlo a la lista abierta
    id_origen = v_origen;
    int longitud_inicial = grafo.vertices[v_origen].longitud;
    int latitud_inicial = grafo.vertices[v_origen].latitud;
    //pair<int, int> atributosInicial = grafo.buscar_vertice(v_origen);
    float h_inicial = funcion_heuristica(longitud_inicial, latitud_inicial);
    Nodo estadoInicial = crear_nodo(v_origen,  longitud_inicial, latitud_inicial, 0, h_inicial, -1);

    abierta.insertar_nodo(estadoInicial);


    while (!abierta.lista.empty() && !exito){
        //Quitar el primer nodo de ABIERTA, N y meterlo en CERRADA

        Nodo nodo_actual = abierta.pop();
        cerrada.añadir_nodo(nodo_actual);
        cerrada.visitados[nodo_actual.id] = nodo_actual.g;
        // SI N es Estado-final ENTONCES EXITO=Verdadero
        if (nodo_actual.id == v_destino) {
            exito = true;
            coste_final = nodo_actual.g;
        }

        else{
            
            //cout << "Nodos en ABIERTA: " << abierta.lista.size() << " | Nodos en CERRADA: " << cerrada.lista.size() << "\r";
            num_expansiones++;

            // Para cada sucesor S de N hacer
            for(int j = 0; j < grafo.lista_adjaciencia[nodo_actual.id].size(); j++){
                // los sucesores son los arcos que están adyacentes al nodo actual
                Arco s = grafo.lista_adjaciencia[nodo_actual.id][j];
                num_nodos_expandidos++;

                // Crear el nodo sucesor con sus respectivos atributos
                //pair<int, int> atributos = grafo.buscar_vertice(s.idDestino);
                int longitud_sucesor = grafo.vertices[s.idDestino].longitud;
                int latitud_sucesor = grafo.vertices[s.idDestino].latitud;
                float h_nodo = funcion_heuristica(longitud_sucesor, latitud_sucesor);
                Nodo sucesor = crear_nodo(s.idDestino, longitud_sucesor, latitud_sucesor, nodo_actual.g + s.coste, h_nodo, nodo_actual.id);
                
                // Si S está en CERRADA con un coste menor o igual que el coste de S ENTONCES no le metemos en ABIERTA
                if (cerrada.visitados[sucesor.id] != -1 && cerrada.visitados[sucesor.id] <= sucesor.g) {
                    
                    continue; // Si ya está en cerrada, no hacemos nada
                }
                // si no está en cerrada o tiene un coste mayor, lo añadimos a abierta para ser examinado
                cerrada.visitados[sucesor.id] = sucesor.g;
                abierta.insertar_nodo(sucesor); 
            }
        
        }
    }
    if (exito){
        // Si EXITO Entonces Solución=camino desde I a N a través de los punteros de G

        // Si no Solución=Fracaso

        //declaraciones para iniciar la reconstrucción del camino
        vector<Nodo> solucion;
        int id = id_destino;
        // reconstrucción del camino desde el destino al origen
        while (id != -1) { 
                // reconstruimos el camino hacia atrás con id_padre y agregamos los nodos a la solución
                auto it = cerrada.buscar_nodo_en_vector(id); 
                Nodo nodo_actual = *it;
                solucion.push_back(nodo_actual);
                id = nodo_actual.id_padre; 
            }
        // invertimos el camino para que vaya del origen al destino y escribimos la solución en el fichero
        reverse(solucion.begin(), solucion.end());
        escribir_solucion(output, solucion);
        return true;
    }
    else {
        return false;
    }
}


double A_star::funcion_heuristica(double nodo_longitud, double nodo_latitud){
    // distancia euclidiana 
    double diffX = nodo_longitud - longitud_destino;
    double diffY = nodo_latitud - latitud_destino;
    return sqrt(diffX * diffX + diffY * diffY)*0.1;
}



Nodo A_star::crear_nodo(int id, double longitud, double latitud, int g, double h, int nodoPadre){
    // asignamos los valores al nuevo nodo
    Nodo nuevo_nodo;
    nuevo_nodo.id = id;
    nuevo_nodo.latitud =latitud;
    nuevo_nodo.longitud = longitud;
    nuevo_nodo.g = g;
    nuevo_nodo.h = h;
    nuevo_nodo.f = g + h;
    nuevo_nodo.id_padre = nodoPadre;
    return nuevo_nodo;
}

void A_star::escribir_solucion(const string& file_path, const vector<Nodo>& camino){
    // Abrir el archivo para escribir la solución
    ofstream fichero(file_path);
    if (!fichero.is_open())
    {
        cout << "Error al abrir " << file_path << "\n";
        exit(EXIT_FAILURE);
    }
    int id = id_destino;

    
    // Imprimir cada nodo
    for (size_t i = 0; i < camino.size() -1 ; ++i) {
        const Nodo& n = camino[i];
        
        fichero << n.id << " - ("<< camino[i+1].g - camino[i].g << ") - ";
        
    }
    // imprimos el último nodo sin flecha
    const Nodo& n = camino.back();
    fichero << n.id;
    fichero << endl;
}   

Dijkstra::Dijkstra() = default;

void Dijkstra::dijkstra(int v_origen, int v_destino, string mapa_path, string output){
    // 1. Leemos el grafo para saber cuántos vértices hay
    grafo.leer_fichero_coordenadas(mapa_path);
    grafo.leer_fichero_grafico(mapa_path);
    //grafo.encontrarExtremos();
    // asginamos los ids de origen y destino
    id_destino = v_destino;
    id_origen = v_origen;
    /*
    Dijkstra(Grafo G, Nodo origen s):
        1. Para cada nodo v en G:
                dist[v] = infinito
                prev[v] = NULL
        3. Crear una cola de prioridad Q, con todos
        los nodos de G ordenados por dist[v]*/

    // Inicializamos los vectores Dist y Prev
    //vector<int> Dist(grafo.num_vertices +1, oo); 
    // La distancia hacia todos los vertices. Inicialmente para cada vertice su valor es infinito.
	//vector<int> Prev(grafo.num_vertices +1, -1); 
    // Este arreglo nos permitira determinar los nodos procesados.
    distancias.resize(grafo.num_vertices +1, oo);
    padres.resize(grafo.num_vertices +1, -1);


    distancias[v_origen] = 0; // Valor inicial del vertice de partida.
    
    // 2. dist[origen] = 0
    // metemos el nodo origen en la cola de prioridad
    Nodo origen;
    origen.id = v_origen;
    origen.g = 0;
    origen.id_padre = -1;
    cola_prioridad.push(origen);
    
    //  4. Mientras Q no este vacıa:
    while (!cola_prioridad.empty()){
        /*1. tomamos el nodo con menor g que es el primero en la cola*/
        Nodo nodo_actual = cola_prioridad.top();
        int id_nodo_actual = nodo_actual.id;
        int distancia = nodo_actual.g;
        // 2. Eliminar u de Q
        cola_prioridad.pop();
        num_nodos_expandidos++;
        if (distancia > distancias[id_nodo_actual]) {
            continue; // Ya hemos encontrado una mejor distancia para 'u'
        }

        if (nodo_actual.id == v_destino){
            // Hemos llegado al destino
            coste_final = distancias[v_destino];
            imprimir_camino(output);
            return;
        }
        // 3. Para cada vecino v de u:        
		for (const Arco & s : grafo.lista_adjaciencia[id_nodo_actual]) {
            
            int nodo_vecino = s.idDestino;
            int peso = s.coste;
            num_expansiones++;
            //  Si encontramos un camino más corto al nodo vecino desde el nodo actual
            if (distancias[id_nodo_actual] != oo && distancias[id_nodo_actual] + peso < distancias[nodo_vecino]) {
                 // Actualizar distancia
                distancias[nodo_vecino] = distancias[id_nodo_actual] + peso;
                // Almacenar el predecesor para reconstruir el camino
                padres[nodo_vecino] = id_nodo_actual; 
                
                // Insertar el vecino con la nueva distancia en la cola
                Nodo nuevo_nodo;
                nuevo_nodo.id = nodo_vecino;
                nuevo_nodo.g = distancias[nodo_vecino];
                nuevo_nodo.id_padre = id_nodo_actual;
                cola_prioridad.push(nuevo_nodo);
            }
        }
}
// Si la cola se vacía y no llegamos al destino
    if (distancias[v_destino] == oo) {
        cout << "El destino no es alcanzable desde el origen." << endl;
    }
}


void Dijkstra::imprimir_camino(string output_path) {
    ofstream fichero(output_path, ios_base::app);
    if (!fichero.is_open())
    {
        cout << "Error al abrir " << output_path << "\n";
        exit(EXIT_FAILURE);
    }
    
    // 1. Trazar el camino hacia atrás
    vector<int> camino;
    int current = id_destino;
    

    
    while (current != -1) {
        camino.push_back(current);
        current = padres[current];
    }
    
    // El camino se construye al revés, lo invertimos para ir de origen a destino
    reverse(camino.begin(), camino.end());

    
    for (size_t i = 0; i < camino.size(); ++i) {
        int vertice_actual = camino[i];
        
        fichero << vertice_actual;

        if (i < camino.size() - 1) {
            int vertice_siguiente = camino[i+1];
            
            // Buscar el peso de la arista (u, v)
            int coste = -1;
            for (const Arco& s : grafo.lista_adjaciencia[vertice_actual]) {
                if (s.idDestino == vertice_siguiente) {
                    coste = s.coste;
                    break;
                }
            }
            
            // Imprimir el coste de la arista y la flecha al siguiente nodo
            fichero << " - (" << coste << ") - ";
        }
    }
    fichero << endl;
}