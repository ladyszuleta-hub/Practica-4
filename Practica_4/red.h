#ifndef RED_H
#define RED_H
#include "router.h"
#include <map>
#include <vector>
#include <string>
using namespace std;
class RED
{
private:
    map<string, Router*> routers;
    map<string, pair<int, vector<string>>>  dijkstra(const string& origen) const;
public:
    RED();
    ~RED();
    void agregarRouter(const string& id);
    void eliminarRouter(const string& id);
    Router* getRouter(const string& id) const;
    bool existeRouter(const string& id) const;

    void actualizarTablas();

    void agregarEnlace(const string& a, const string& b, int costo);
    void eliminarEnlace(const string& a, const string& b);

    vector<string> camino(const string& origen, const string& destino) const;
    int costoCamino(const string& origen, const string& destino) const;

};

#endif // RED_H
