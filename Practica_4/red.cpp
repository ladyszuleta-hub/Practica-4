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
        //      routers[id] = new Router(id);
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
            //       par.second->eliminarVecino(id);
        }
    }
    delete routers[id];
    routers.erase(id);
    cout << "Router " << id << " eliminado.\n";
    //actualizarTablas();
}
Router* RED::getRouter(const string& id) const {
    auto it = routers.find(id);
    if (it != routers.end()) return it->second;
    return nullptr;
}

bool RED::existeRouter(const string& id) const {
    return routers.find(id) != routers.end();
}
