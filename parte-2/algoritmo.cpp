#include "grafo.hpp"
#include "abierta.hpp"
#include "cerrada.hpp"

#include <algorithm>
#include "algoritmo.hpp"

#include <iostream> // Para cout
using namespace std;




/*EL PSEUDO CÓDIGO DE A* ES:
Crear grafo de búsqueda G, con el nodo inicial, I (Estado-inicial)
    llamada a grafo.cpp

    recibimos v_origen y v_destino y path de input
    
    Grafo grafo;
    grafo.leer_ficheros(path);
    // en grafo.vertices y grafo.lista_adjacencia tenemos el grafo

    llamada a abierta.cpp meter estado inicial en abierta
    ListaAbierta abierta;
    
    llamada a funcion heuristica distancia euclidiana o manhatan

    lista.insertarNodo(v_origen, g = 0, h, nodoPadre=null)

    llamada cerrada.cpp

    ListaCerrada cerrada;

    declaracion de exitos
    int exito =1;



Hasta que ABIERTA esté vacía O EXITO

    while (abierta.size() != 0 || exito) 

Quitar el primer nodo de ABIERTA, N y meterlo en CERRADA
   Nodo nodo_actual = abierta.pop()
   cerrada.añadir_nodo(nodo_actual)
   
SI N es Estado-final ENTONCES EXITO=Verdadero
    if nodo_actual.id = v_destino
        exitos = 0;
SI NO Expandir N, generando el conjunto S de sucesores de N, que no son antecesores de N en el grafo
Generar un nodo en G por cada s de S
Establecer un puntero a N desde aquellos s de S que no estuvieran ya en G


    else {
        vector<Nodo> sucesores = expandir_nodo(nodo_actual)
            expandir_nodo() tener en cuenta si son padre o no



        Añadirlos a ABIERTA --> primero comprobamos si el vertice ya está dentro con find or something
        si esta dentro hacemos cambiar_nodo
        si no añadir_nodo
        Para cada s de S que estuviera ya en ABIERTA o CERRADA
        decidir si redirigir o no sus punteros hacia N
        Para cada s de S que estuviera ya en CERRADA
        decidir si redirigir o no los punteros de los nodos en sus subárboles
        
Si EXITO Entonces Solución=camino desde I a N a través de los punteros de G
    Si no Solución=Fracaso
*/
A_star::A_star() = default;

void A_star::a_star(int v_origen, int v_destino, string mapa_path, string output){
    //Crear grafo de búsqueda G, con el nodo inicial, I (Estado-inicial)
    //llamada a grafo.cpp
    //Grafo grafo;
    grafo.leer_fichero_coordenadas(mapa_path);
    grafo.leer_fichero_grafico(mapa_path);
    // en grafo.vertices y grafo.lista_adjacencia tenemos el grafo
    pair<int, int> atributosFinal = grafo.buscar_vertice(v_destino);
    longitud_destino = atributosFinal.first;
    latitud_destino = atributosFinal.second;
    id_destino = v_destino;
    id_origen = v_origen;

    pair<int, int> atributosInicial = grafo.buscar_vertice(v_origen);
    
    float h_inicial = funcion_heuristica(atributosInicial.first, atributosInicial.second);
    Nodo estadoInicial = crear_nodo(v_origen,  atributosInicial.first, atributosInicial.second, 0, h_inicial, -1, 0);

    // como es el estado inical y no podemos asignar NULL en un parametro de la funcion haremos el nodo
   
    //llamada a abierta.cpp meter estado inicial en abierta
    //ListaAbierta abierta;
    abierta.insertar_nodo(estadoInicial);

    // llamada a cerrada.cpp
    //ABIERTA=I, CERRADA=Vacío, EXITO=Falso

    //ListaCerrada cerrada;


    while (!abierta.lista.empty() && !exito){
        //Quitar el primer nodo de ABIERTA, N y meterlo en CERRADA

        Nodo nodo_actual = abierta.pop();
        cerrada.añadir_nodo(nodo_actual);

        // SI N es Estado-final ENTONCES EXITO=Verdadero
        if (nodo_actual.id == v_destino) {
            exito = true;
            coste_final = nodo_actual.g;
        }

        else{
            //SI NO Expandir N, generando el conjunto S de sucesores de N, 
            //que no son antecesores de N en el grafo
            vector<Arco> sucesores;
            sucesores = expandir_nodo(nodo_actual);
            num_expansiones++;
            for (Arco s : sucesores){
                num_nodos_expandidos++;
                pair<int, int> atributos = grafo.buscar_vertice(s.idDestino);
                float h_nodo = funcion_heuristica(atributos.first, atributos.second);
                Nodo sn = crear_nodo(s.idDestino, atributos.first, atributos.second, nodo_actual.g + s.coste, h_nodo, nodo_actual.id, s.coste);
                //Añadirlos a ABIERTA --> primero comprobamos si el vertice ya está dentro con find or something
                //si esta dentro hacemos cambiar_nodo
                auto nodo_buscado = abierta.buscar_nodo(sn.id);
                

               /* if (nodo_buscado != abierta.lista.end()){
                    // ESTA EN ABIERTA

                    Nodo nodo_viejo = *nodo_buscado; // Obtener la copia vieja

                    //  Decidir si redirigir punteros: Comparar el costo g (el real)
                    if (sn.g < nodo_viejo.g) {

                        // El nuevo camino es mejor. Eliminar el viejo.
                        abierta.lista.erase(*nodo_buscado);
                        abierta.insertar_nodo(sn);
                    }

                 }   // Si el nuevo camino no es mejor, no hacemos nada y terminamos.

                else {*///Para cada s de S que estuviera ya en ABIERTA o CERRADA
                    //decidir si redirigir o no sus punteros hacia N
                    auto it_cerrada = find_if(cerrada.lista.begin(), cerrada.lista.end(), 
                                               [&sn](const Nodo& n){ return n.id == sn.id; });

                    if (it_cerrada != cerrada.lista.end()) {
                        // Nodo en CERRADA: comprobar mejora (g)
                        Nodo nodo_viejo_cerrada = *it_cerrada; 
                        
                        if (sn.g < nodo_viejo_cerrada.g) {
                            
                            cerrada.lista.erase(it_cerrada); 
                            abierta.insertar_nodo(sn);       
                        }
                    } 
                    
                    // 3. NODO NUEVO (No está ni en ABIERTA ni en CERRADA)
                    else {
                        abierta.insertar_nodo(sn);
                    }

        
  
                //}        
        
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
        std::reverse(solucion.begin(), solucion.end());
        escribir_solucion(output, solucion);
    }
}


float A_star::funcion_heuristica(int nodo_longitud, int nodo_latitud){
        // h(n)=∣xn​−xd​∣+∣yn​−yd​∣
        //h(n)=∣Longitudn​−Longitudd​∣+∣Latitudn​−Latitudd​∣

        //h(n)=(Longitudn​−Longitudd​)2+(Latitudn​−Latitudd​)2​
    int valor1 = (nodo_longitud - longitud_destino)*(nodo_longitud - longitud_destino);
    int valor2 = (nodo_latitud - latitud_destino)*(nodo_latitud - latitud_destino);

    int a = abs(nodo_longitud - longitud_destino);
    int b = abs(nodo_latitud - latitud_destino);
    //return a +b;
    return sqrt(valor1 + valor2) ;

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

Nodo A_star::crear_nodo(int id, int longitud, int latitud, int g, int h, int nodoPadre, int coste){
    Nodo nuevo_nodo;
    nuevo_nodo.id = id;
    nuevo_nodo.latitud =latitud;
    nuevo_nodo.longitud = longitud;
    nuevo_nodo.g = g;
    nuevo_nodo.h = h;
    nuevo_nodo.f = g + h;
    nuevo_nodo.id_padre = nodoPadre;
    nuevo_nodo.coste= coste;
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
        
        fichero << n.id << " - ("<< camino[i+1].coste << ") - ";
        
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
    inicializar_nodos(grafo.vertices);
    
    // 2. dist[origen] = 0
    Nodo origen;
    origen.g = 0;
    origen.id_padre = -1;
    cola_prioridad.push(origen);
    
    //  4. Mientras Q no este vacıa:

    while (!cola_prioridad.empty()){
        /**/
    }

    /*   
        1. u = Nodo con la distancia m´as peque~na en Q
        2. Eliminar u de Q
        3. Para cada vecino v de u:
        1. Si v est´a en Q:
        2. Si dist[u] + peso(u, v) < dist[v]:
        dist[v] = dist[u] + peso(u, v)
        prev[v] = u
        Actualizar la posici´on de v en Q
        5. Retornar dist[] y prev[] (distancias
        m´ınimas y el camino m´as corto
        desde s a todos los nodos)*/



}


void Dijkstra::inicializar_nodos(vector<Vertice> vertices){
    /*1. Para cada nodo v en G:
                dist[v] = infinito
                prev[v] = NULL
    3. Crear una cola de prioridad Q, con todos
        los nodos de G ordenados por dist[v]*/
    for (int i = 0; i <= vertices.size(); ++i) {
        if (i =! id_origen){
            Nodo nuevo_nodo;
            nuevo_nodo.id = vertices[i].id;
            nuevo_nodo.id_padre = -1;
            nuevo_nodo.g = INFINITY;
            cola_prioridad.push(nuevo_nodo);
        }
       
}