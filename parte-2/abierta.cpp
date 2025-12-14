#include <iostream> // Para cout
#include <vector>
#include <string>

using namespace std;

#include "abierta.hpp"

Comparacion_A_star::Comparacion_A_star() = default;


bool Comparacion_A_star::operator() (const Nodo& nodo_max, const Nodo& nodo_nuevo) const{
    if (nodo_max.f != nodo_nuevo.f) {
            return nodo_max.f < nodo_nuevo.f;
        }
        return nodo_max.id < nodo_nuevo.id;
}

bool Comparacion_A_star::operator() (const int& id_a, const Nodo& nodo_b) const {
        return id_a < nodo_b.id;
    }

bool Comparacion_A_star::operator() (const Nodo& nodo_a, const int& id_b) const {
    return nodo_a.id < id_b;
}


Comparacion_Dijkstra::Comparacion_Dijkstra() = default;

bool Comparacion_Dijkstra::operator() (const Nodo& nodo_max, const Nodo& nodo_nuevo) const{
    if (nodo_max.g != nodo_nuevo.g) {
            return nodo_max.g > nodo_nuevo.g;
        }
        return nodo_max.id > nodo_nuevo.id;
}


ListaAbierta::ListaAbierta() = default;




void ListaAbierta::insertar_nodo(Nodo nodo){
    // insertamos en el set
    lista.insert(nodo);
    
}
    
Nodo ListaAbierta::pop(){
    return move(lista.extract(lista.begin()).value());
}



void ListaAbierta::imprimir_nodos(){
    
    for (Nodo it: lista){
        cout << it.id << ", ";
    }
    cout << endl;
}

std::set<Nodo, Comparacion_A_star>::iterator ListaAbierta::buscar_nodo(int id){
    
    auto nodo = lista.find(id);
    return nodo;
}
