#include "router.h"

Router::Router() {

    nombre = "";
}

Router::Router(string nombre) {

    this->nombre = nombre;

    tablaCostos[nombre] = 0;
}

void Router::agregarVecino(string vecino,int costo) {

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
void Router::actualizarRuta(string destino, vector<string> camino) {

    rutas[destino] = camino;
}

int Router::getCosto(const string& destino) const {
    auto it = tablaCostos.find(destino);
    if (it != tablaCostos.end()) return it->second;
    return INT_MAX;
}

void Router::resetTablaCostos() {

    tablaCostos.clear();

    rutas.clear();

    // costo hacia sí mismo
    tablaCostos[nombre] = 0;
    rutas[nombre] = { nombre };

    // vecinos directos
    for (auto v : vecinos) {

        tablaCostos[v.first] = v.second;

        rutas[v.first] = { nombre, v.first };
    }
}

