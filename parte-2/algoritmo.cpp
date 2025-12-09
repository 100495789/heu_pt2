#include "grafo.hpp"
#include "abierta.hpp"
#include "cerrada.hpp"

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


void A_star::a_star(int v_origen, int v_destino, string mapa_path, string output){
    //Crear grafo de búsqueda G, con el nodo inicial, I (Estado-inicial)
    //llamada a grafo.cpp
    //Grafo grafo;
    grafo.leer_fichero_coordenadas(mapa_path);
    grafo.leer_fichero_grafico(mapa_path);
    // en grafo.vertices y grafo.lista_adjacencia tenemos el grafo

    //Nodo estadoInicial = crear_nodo(v_origen, 0, funcion_heuristica(), * );

    // como es el estado inical y no podemos asignar NULL en un parametro de la funcion haremos el nodo
    Nodo estadoInicial;
    estadoInicial.id = v_origen;
    estadoInicial.id_padre = NULL;
    estadoInicial.g = 0;
    estadoInicial.h = funcion_heuristica();
    estadoInicial.f = estadoInicial.h;
    
    //llamada a abierta.cpp meter estado inicial en abierta
    //ListaAbierta abierta;
    abierta.insertar_nodo(estadoInicial);

    // llamada a cerrada.cpp
    //ABIERTA=I, CERRADA=Vacío, EXITO=Falso

    //ListaCerrada cerrada;


    while (!abierta.lista.empty() || !exito)
    {
        //Quitar el primer nodo de ABIERTA, N y meterlo en CERRADA

        Nodo nodo_actual = abierta.pop();
        cerrada.añadir_nodo(nodo_actual);

        // SI N es Estado-final ENTONCES EXITO=Verdadero
        if (nodo_actual.id = v_destino) exito = true;

        else{
            //SI NO Expandir N, generando el conjunto S de sucesores de N, 
            //que no son antecesores de N en el grafo
            vector<Arco> sucesores;
            sucesores = expandir_nodo(nodo_actual);
            for (Arco s : sucesores){
                Nodo sn = crear_nodo(s.idDestino, nodo_actual.g + s.coste, funcion_heuristica(), nodo_actual);
                //Añadirlos a ABIERTA --> primero comprobamos si el vertice ya está dentro con find or something
                //si esta dentro hacemos cambiar_nodo
                for (Nodo n : abierta.lista){
                    //Para cada s de S que estuviera ya en ABIERTA o CERRADA
                    //decidir si redirigir o no sus punteros hacia N
                    if (n.id = sn.id && n.f > sn.id){
                        abierta.lista.erase(n);
                        
                    }
                    //Reordenar ABIERTA según f (n)
                    abierta.insertar_nodo(sn);
                }
                
                //Para cada s de S que estuviera ya en ABIERTA o CERRADA
                //decidir si redirigir o no sus punteros hacia N
                if (cerrada.lista.count(sn.id)>0 && cerrada.lista[sn.id] > sn.f){
                    // qé hago aqui cambiar el nodo de cerrada?
            
                }

                   
            }
            cerrada.lista[nodo_actual.id] = nodo_actual.f;
            
        
        }

        if (exito){
            // Si EXITO Entonces Solución=camino desde I a N a través de los punteros de G

            // Si no Solución=Fracaso
        }
    }
    

}

int A_star::funcion_heuristica(){
        // ignorar q no esta hecho
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

Nodo A_star::crear_nodo(int id, int g, int h, Nodo nodoPadre){
    Nodo nuevo_nodo;
    nuevo_nodo.id = id;
    nuevo_nodo.g = g;
    nuevo_nodo.h = h;
    nuevo_nodo.f = g + h;
    nuevo_nodo.id_padre = &nodoPadre;
    return nuevo_nodo;
}