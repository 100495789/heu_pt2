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
    
    // 2. Inicializamos los vectores con el tamaño exacto (num_vertices + 1)
    vector<int> visitados_en_cerrada(grafo.num_vertices + 1, -1);

    pair<double, double> atributosFinal = grafo.buscar_vertice(v_destino);
    longitud_destino = atributosFinal.first;
    latitud_destino = atributosFinal.second;
    id_destino = v_destino;
    id_origen = v_origen;

    pair<int, int> atributosInicial = grafo.buscar_vertice(v_origen);
    
    float h_inicial = funcion_heuristica(atributosInicial.first, atributosInicial.second);
    Nodo estadoInicial = crear_nodo(v_origen,  atributosInicial.first, atributosInicial.second, 0, h_inicial, -1);

    abierta.insertar_nodo(estadoInicial);


    while (!abierta.lista.empty() && !exito){
        //Quitar el primer nodo de ABIERTA, N y meterlo en CERRADA

        Nodo nodo_actual = abierta.pop();
        cerrada.añadir_nodo(nodo_actual);
        visitados_en_cerrada[nodo_actual.id] = nodo_actual.g;
        // SI N es Estado-final ENTONCES EXITO=Verdadero
        if (nodo_actual.id == v_destino) {
            exito = true;
            coste_final = nodo_actual.g;
        }

        else{
            
            cout << "Nodos en ABIERTA: " << abierta.lista.size() << " | Nodos en CERRADA: " << cerrada.lista.size() << "\r";
            num_expansiones++;
            for(int j = 0; j < grafo.lista_adjaciencia[nodo_actual.id].size(); j++){
                Arco s = grafo.lista_adjaciencia[nodo_actual.id][j];
                num_nodos_expandidos++;
                pair<int, int> atributos = grafo.buscar_vertice(s.idDestino);

                float h_nodo = funcion_heuristica(atributos.first, atributos.second);
                Nodo sucesor = crear_nodo(s.idDestino, atributos.first, atributos.second, nodo_actual.g + s.coste, h_nodo, nodo_actual.id);
                
                if (visitados_en_cerrada[sucesor.id] != -1 && visitados_en_cerrada[sucesor.id] <= sucesor.g) {
                    
                    continue; // Si ya está en cerrada, no hacemos nada
                }
                visitados_en_cerrada[sucesor.id] = sucesor.g;
                abierta.insertar_nodo(sucesor); 
            }
        
        }
    }
    if (exito){
        // Si EXITO Entonces Solución=camino desde I a N a través de los punteros de G

        // Si no Solución=Fracaso
        vector<Nodo> solucion;
        int id = id_destino;
        
        while (id != -1) { 
                
                auto it = cerrada.buscar_nodo_en_vector(id); 

                Nodo nodo_actual = *it;
                solucion.push_back(nodo_actual);
                //cout << nodo_actual.id << " - (" << nodo_actual.coste << ") - " ;
                id = nodo_actual.id_padre; 
            }
        //cout << endl;
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
    return sqrt(diffX * diffX + diffY * diffY)*0.9;
}

vector<Arco> A_star::expandir_nodo(Nodo nodo){
    //grafo.lista_adjaciencia.find
    vector<Arco> sucesores;
    for(int j = 0; j < grafo.lista_adjaciencia[nodo.id].size(); j++){
        Arco s = grafo.lista_adjaciencia[nodo.id][j];
        // el strucut arco tiene v_destino = id y coste = g
        sucesores.push_back(s);
    }
    return sucesores;  
}

Nodo A_star::crear_nodo(int id, double longitud, double latitud, int g, double h, int nodoPadre){
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
    //const Nodo& = camino[camino.size()];
    const Nodo& n = camino.back();
    fichero << n.id;
    fichero << endl;
}   

Dijkstra::Dijkstra() = default;

void Dijkstra::dijkstra(int v_origen, int v_destino, string mapa_path, string output){
    grafo.leer_fichero_coordenadas(mapa_path);
    grafo.leer_fichero_grafico(mapa_path);


    id_destino = v_destino;
    id_origen = v_origen;
    /*
    Dijkstra(Grafo G, Nodo origen s):
        1. Para cada nodo v en G:
                dist[v] = infinito
                prev[v] = NULL
        3. Crear una cola de prioridad Q, con todos
        los nodos de G ordenados por dist[v]*/
    vector<int> Dist(grafo.num_vertices +1, oo); // La distancia hacia todos los vertices. Inicialmente para cada vertice su valor es infinito.
	vector<int> Prev(grafo.num_vertices +1, -1); // Este arreglo nos permitira determinar los nodos procesados.

    Dist[v_origen] = 0; // Valor inicial del vertice de partida.
    //inicializar_nodos(grafo.vertices);
    
    // 2. dist[origen] = 0
    Nodo origen;
    origen.id = v_origen;
    origen.g = 0;
    origen.id_padre = -1;
    cola_prioridad.push(origen);
    
    //  4. Mientras Q no este vacıa:

    while (!cola_prioridad.empty()){
        /*1. u = Nodo con la distancia m´as peque~na en Q*/
        Nodo nodo_actual = cola_prioridad.top();
        int u = nodo_actual.id;
        int d = nodo_actual.g;
        // 2. Eliminar u de Q
        cola_prioridad.pop();
        if (d > Dist[u]) {
            continue; // Ya hemos encontrado una mejor distancia para 'u'
        }

        if (nodo_actual.id == v_destino){
            // Hemos llegado al destino
            coste_final = Dist[v_destino];
            imprimir_camino(Dist, Prev, output);
            return;
        }
        // 3. Para cada vecino v de u:
        //vector<Nodo> vecinos = buscar_vecinos(nodo_actual);
        
		for (const Arco & s : grafo.lista_adjaciencia[u]) {
            int v = s.idDestino;
            int peso = s.coste;
            
            // Relajación: Si encontramos un camino más corto a 'v' a través de 'u'
            if (Dist[u] != oo && Dist[u] + peso < Dist[v]) {
                
                Dist[v] = Dist[u] + peso; // Actualizar distancia
                Prev[v] = u; // **Almacenar el predecesor para reconstruir el camino**
                
                // Insertar 'v' con la nueva distancia en la cola
                Nodo nuevo_nodo;
                nuevo_nodo.id = v;
                nuevo_nodo.g = Dist[v];
                nuevo_nodo.id_padre = u;
                cola_prioridad.push(nuevo_nodo);
            }
        }

    /*   
        1. Si v est´a en Q:
            2. Si dist[u] + peso(u, v) < dist[v]:
        dist[v] = dist[u] + peso(u, v)
        prev[v] = u
        Actualizar la posici´on de v en Q
        5. Retornar dist[] y prev[] (distancias
        m´ınimas y el camino m´as corto
        desde s a todos los nodos)*/



}
// Si la cola se vacía y no llegamos al destino
    if (Dist[v_destino] == oo) {
        cout << "El destino no es alcanzable desde el origen." << endl;
    }
}


void Dijkstra::imprimir_camino(vector<int> Dist, vector<int> Prev, string output_path) {
    ofstream fichero(output_path, ios_base::app);
    if (!fichero.is_open())
    {
        cout << "Error al abrir " << output_path << "\n";
        exit(EXIT_FAILURE);
    }
    
    // 1. Trazar el camino hacia atrás
    vector<int> path;
    int current = id_destino;
    

    
    while (current != -1) {
        path.push_back(current);
        current = Prev[current];
    }
    
    // El camino se construye al revés, lo invertimos para ir de origen a destino
    reverse(path.begin(), path.end());

    
    for (size_t i = 0; i < path.size(); ++i) {
        int u = path[i];
        
        fichero << u;

        if (i < path.size() - 1) {
            int v = path[i+1];
            
            // Buscar el peso de la arista (u, v)
            int weight = -1;
            for (const Arco& s : grafo.lista_adjaciencia[u]) {
                if (s.idDestino == v) {
                    weight = s.coste;
                    break;
                }
            }
            
            // Imprimir el coste de la arista y la flecha al siguiente nodo
            fichero << " - (" << weight << ") - ";
        }
    }
    fichero << endl;
}