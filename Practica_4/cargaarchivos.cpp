#include "cargaarchivos.h"
#include "router.h"
#include "red.h"
#include <fstream>
#include <sstream>
#include <iostream>
using namespace std;

Cargaarchivos::Cargaarchivos() {}

void Cargaarchivos::cargarDesdeArchivo(const string& archivo, RED& red) {

    ifstream file(archivo);
    if (!file.is_open()) {
        cout << "Error: no se pudo abrir " << archivo << "\n";
        return;
    }
    string linea;
    while (getline(file, linea)) {
        if (linea.empty() || linea[0] == '#') continue;
        istringstream ss(linea);
        string id1, id2, enlace;

        getline(ss,id1,';');
        getline(ss, id2, ';');
        getline(ss, enlace, ';');
        int costo=stoi(enlace) ;
        red.agregarEnlace(id1, id2, costo);
    }
    file.close();
    cout << "Topología cargada desde " << archivo << "\n";
}
