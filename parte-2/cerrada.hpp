#ifndef CERRADA_HPP
#define CERRADA_HPP

#include <vector>
#include <string>
#include <unordered_map>
#include <iostream> // Para cout
using namespace std;

#include "abierta.hpp"

class ListaCerrada {
    public:
        ListaCerrada();
        vector<Nodo> lista; 
        vector<int> visitados; // en cada posicion guardamos el coste g del nodo visitado

        void añadir_nodo(Nodo nodo);
        vector<Nodo>::iterator buscar_nodo_en_vector(int id_a_buscar);

};

#endif // CERRADA_HPP