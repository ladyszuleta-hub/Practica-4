#ifndef ROUTER_H
#define ROUTER_H

#include <iostream>
#include <map>
#include <string>
#include <vector>
using namespace std;

using namespace std;

class Router {

private:
    string nombre;
    map<string, int> vecinos;
    map<string, int> tablaCostos;
    map<string, vector<string>> rutas;

public:

    Router();

    Router(string nombre);

    void agregarVecino(string vecino,int costo);

    void eliminarVecino(string vecino);
    void mostrarVecinos();
    void mostrarTablaCostos();
    string getNombre();
    map<string, int>& getVecinos();
    map<string, int>& getTablaCostos();
    void actualizarCosto(string destino, int costo);
    void actualizarRuta(string destino, vector<string> camino);
    int getCosto(const string& destino) const;
    void resetTablaCostos();

};

#endif
