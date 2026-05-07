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

};

#endif // RED_H
