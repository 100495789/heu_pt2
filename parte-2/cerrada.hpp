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
        vector<Nodo> lista; //id & f
        void añadir_nodo(Nodo nodo);
        vector<Nodo>::iterator buscar_nodo_en_vector(int id_a_buscar);

};

#endif // ABIERTA_HPP