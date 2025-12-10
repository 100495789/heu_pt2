#include <iostream> // Para cout
#include <vector>
#include <string>

using namespace std;

#include "abierta.hpp"

Comparacion::Comparacion() = default;


bool Comparacion::operator() (const Nodo& nodo_max, const Nodo& nodo_nuevo) const{
    if (nodo_max.f != nodo_nuevo.f) {
            return nodo_max.f < nodo_nuevo.f;
        }
        return nodo_max.id < nodo_nuevo.id;
}

bool Comparacion::operator() (const int& id_a, const Nodo& nodo_b) const {
        return id_a < nodo_b.id;
    }

bool Comparacion::operator() (const Nodo& nodo_a, const int& id_b) const {
    return nodo_a.id < id_b;
}

ListaAbierta::ListaAbierta() = default;


/*void ListaAbierta::insertar_nodo(int id, int g, int h, Nodo nodoPadre){


    Nodo nuevo_nodo;
    nuevo_nodo.id = id;
    nuevo_nodo.g = g;
    nuevo_nodo.h = h;
    nuevo_nodo.f = g + h;
    nuevo_nodo.id_padre = &nodoPadre;
    lista.push(nuevo_nodo);
    
}*/



void ListaAbierta::insertar_nodo(Nodo nodo){

    // creamos del estado el nuevo nodo y asignamos sus parámetros
    /*Nodo nuevo_nodo;
    nuevo_nodo.id = id;
    nuevo_nodo.g = g;
    nuevo_nodo.h = h;
    nuevo_nodo.f = g + h;
    nuevo_nodo.id_padre = &nodoPadre;*/

    // insertamos en el set
    lista.insert(nodo);
    
}
    
Nodo ListaAbierta::pop(){
    return move(lista.extract(lista.begin()).value());
}



//Nodo ListaAbierta::pop(){
    /*if (lista.empty()) {
        cout << "Error: Lista Abierta vacía al intentar pop()" << endl;
        //return Nodo nodo;
        exit;
    }
    
    int mejor_f;
    int mejor_id;*/
    //Nodo nodo_elegido = lista.top();
    //lista.pop();
    //return nodo_elegido;

    /*for (int i=0; i<lista.size();i++){
        if (mejor_f > lista[i].f){
            mejor_f = lista[i].f;
            mejor_id = lista[i].id;
        }
    }*/

    //nodo_pop = find(lista, lista.begin(), lista.end(), mejor_f, mejor_id);
    //lista.erase(lista.begin() + id);


//}


void ListaAbierta::imprimir_nodos(){
    //while(!lista.empty()) {
       // cout << lista.top().id << ", ";
        //lista.pop();
        
        //cout << lista
    //}
    //cout << endl;
    for (Nodo it: lista){
        cout << it.id << ", ";
    }
    cout << endl;
}

std::set<Nodo, Comparacion>::iterator ListaAbierta::buscar_nodo(int id){
    // falta cosas
    auto nodo = lista.find(id);
    return nodo;
}

/*void ListaAbierta::lista_prioridad(int g, int h){
    // en esta función debemos organizar los nodos de la lista para que el primero sea el mejor
}

int main(){
    ListaAbierta abierta;
    Nodo nodo;
    nodo.id = 0;
    nodo.g = 0;
    nodo.h = 0;
    nodo.id_padre = &nodo;
    abierta.insertar_nodo(1, 0, 0, nodo);

    return 0;
}*/