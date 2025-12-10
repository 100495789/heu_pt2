#include <vector>
#include <string>

#include <iostream> // Para cout
using namespace std;

#include "cerrada.hpp"

ListaCerrada::ListaCerrada() = default;

void ListaCerrada::añadir_nodo(Nodo nodo){
    lista.push_back(nodo);
}

vector<Nodo>::iterator ListaCerrada::buscar_nodo_en_vector(int id_a_buscar) {
    for (auto it = lista.begin(); it != lista.end(); ++it) {
        if (it->id == id_a_buscar) {
            return it; // Encontrado
        }
    }
    return lista.end(); // No encontrado
}