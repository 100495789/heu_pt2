#include <vector>
#include <string>
#include <unordered_map>
#include <iostream> // Para cout
using namespace std;

#include "abierta.hpp"

class ListaCerrada {
    public:
        unordered_map<int, int> lista; //id & f
        void añadir_nodo(Nodo nodoN);
};

