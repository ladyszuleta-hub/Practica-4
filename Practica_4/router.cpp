#include "Router.h"

Router::Router() {

    nombre = "";
}

Router::Router(string nombre) {

    this->nombre = nombre;

    tablaCostos[nombre] = 0;
}

void Router::agregarVecino(string vecino,
                           int costo) {

    vecinos[vecino] = costo;

    tablaCostos[vecino] = costo;
}

void Router::eliminarVecino(string vecino) {

    vecinos.erase(vecino);

    tablaCostos.erase(vecino);
}

void Router::mostrarVecinos() {

    cout << "Vecinos del router "
         << nombre << endl;

    for (auto v : vecinos) {

        cout << v.first
             << " -> "
             << v.second
             << endl;
    }
}

void Router::mostrarTablaCostos() {

    cout << "Tabla de costos de "
         << nombre << endl;

    for (auto t : tablaCostos) {

        cout << t.first
             << " : "
             << t.second
             << endl;
    }
}

string Router::getNombre() {

    return nombre;
}

map<string, int>& Router::getVecinos() {

    return vecinos;
}

map<string, int>& Router::getTablaCostos() {

    return tablaCostos;
}
void Router::actualizarCosto(string destino, int costo) {

    tablaCostos[destino] = costo;
}
