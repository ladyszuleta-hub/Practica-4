#include "red.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <climits>
#include <queue>
#include <algorithm>
using namespace std;

RED::RED() {}
RED::~RED() {
    for (auto& par : routers) {
        delete par.second;
    }
    routers.clear();
}
void RED::agregarRouter(const string& id) {
    if (routers.find(id) == routers.end()) {
              routers[id] = new Router(id);
        cout << "Router " << id << " agregado.\n";
    } else {
        cout << "Router " << id << " ya existe.\n";
    }
}
void RED::eliminarRouter(const string& id) {
    if (!existeRouter(id)) {
        cout << "Router " << id << " no existe.\n";
        return;
    }
    // Eliminar enlaces hacia este router en todos los demás
    for (auto& par : routers) {
        if (par.first != id) {
           par.second->eliminarVecino(id);
        }
    }
    delete routers[id];
    routers.erase(id);
    cout << "Router " << id << " eliminado.\n";
    actualizarTablas();
}
Router* RED::getRouter(const string& id) const {
    auto it = routers.find(id);
    if (it != routers.end()) return it->second;
    return nullptr;
}

bool RED::existeRouter(const string& id) const {
    return routers.find(id) != routers.end();
}

void RED::actualizarTablas() {
    for (auto& par : routers) {
        string origen = par.first;
        Router* r = par.second;
        r->resetTablaCostos();

        auto resultados = dijkstra(origen);
        for (auto& [dest, info] : resultados) {
            if (dest == origen) continue;
            r->actualizarCosto(dest, info.first);
            r->actualizarRuta(dest, info.second);
        }
    }
}

void RED::agregarEnlace(const string& a, const string& b, int costo) {
    if (!existeRouter(a)) agregarRouter(a);
    if (!existeRouter(b)) agregarRouter(b);
    // Enlace bidireccional
    routers[a]->agregarVecino(b, costo);
    routers[b]->agregarVecino(a, costo);
    cout << "Enlace " << a << " <-> " << b << " (costo " << costo << ") agregado.\n";
    actualizarTablas();
}

void RED::eliminarEnlace(const string& a, const string& b) {
    if (!existeRouter(a) || !existeRouter(b)) {
        cout << "Uno o ambos routers no existen.\n";
        return;
    }
    routers[a]->eliminarVecino(b);
    routers[b]->eliminarVecino(a);
    cout << "Enlace " << a << " <-> " << b << " eliminado.\n";
    actualizarTablas();
}
// ─── Dijkstra ──────────────────────────────────────────
// Retorna para cada destino: {costo mínimo, camino completo}

map<string, pair<int, vector<string>>>
RED::dijkstra(const string& origen) const {

    // distancia mínima conocida a cada nodo
    map<string, int> dist;
    // predecesor en el camino más corto
    map<string, string> prev;
    // {costo, id} — min-heap
    priority_queue<pair<int,string>,vector<pair<int,string>>,greater<pair<int,string>>> pq;

    // Inicializar todas las distancias en infinito
    for (auto& par : routers) {
        dist[par.first] = INT_MAX;
        prev[par.first] = "";
    }
    dist[origen] = 0;
    pq.push({0, origen});

    while (!pq.empty()) {
        auto [costoActual, u] = pq.top();
        pq.pop();

        if (costoActual > dist[u]) continue; // ya procesado

        Router* ru = routers.at(u);
        for (auto& [vecId, costoEnlace] : ru->getVecinos()) {
            if (routers.find(vecId) == routers.end()) continue;
            int nuevoDist = dist[u] + costoEnlace;
            if (nuevoDist < dist[vecId]) {
                dist[vecId] = nuevoDist;
                prev[vecId] = u;
                pq.push({nuevoDist, vecId});
            }
        }
    }

    // Reconstruir caminos
    map<string, pair<int, vector<string>>> resultado;
    for (auto& par : routers) {
        string dest = par.first;
        vector<string> path;
        if (dist[dest] == INT_MAX) {
            resultado[dest] = {INT_MAX, {}};
            continue;
        }
        // Reconstruir desde dest hacia origen
        string actual = dest;
        while (actual != "") {
            path.insert(path.begin(), actual);
            actual = prev[actual];
        }
        resultado[dest] = {dist[dest], path};
    }
    return resultado;
}
vector<string> RED::camino(const string& origen, const string& destino) const {
    if (!existeRouter(origen) || !existeRouter(destino)) return {};
    auto res = dijkstra(origen);
    return res[destino].second;
}

int RED::costoCamino(const string& origen, const string& destino) const {
    if (!existeRouter(origen) || !existeRouter(destino)) return INT_MAX;
    auto res = dijkstra(origen);
    return res[destino].first;
}

void RED::mostrarTopologia() const {
    cout << "\n===== TOPOLOGÍA DE LA RED =====\n";
    cout << "Routers: ";
    for (auto& par : routers) cout << par.first << " ";
    cout << "\n\nEnlaces:\n";
    // Para no repetir A<->B y B<->A
    vector<pair<string,string>> vistos;
    for (auto& par : routers) {
        for (auto& vec : par.second->getVecinos()) {
            string a = par.first, b = vec.first;
            if (a > b) swap(a, b);
            if (find(vistos.begin(), vistos.end(), make_pair(a,b)) == vistos.end()) {
                cout << "  " << a << " <-> " << b << "  costo: " << vec.second << "\n";
                vistos.push_back({a, b});
            }
        }
    }
    cout << "================================\n";
}

void RED::mostrarTablas() const {
    cout << "\n===== TABLAS DE ENRUTAMIENTO =====\n";
    for (auto& par : routers) {
        par.second->mostrarTablaCostos();
        cout << "\n";
    }
}
