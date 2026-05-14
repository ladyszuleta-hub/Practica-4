#ifndef CARGAARCHIVOS_H
#define CARGAARCHIVOS_H
#include <string>
#include "router.h"
#include "red.h"
using namespace std;

class Cargaarchivos
{
public:
    Cargaarchivos();

    void cargarDesdeArchivo(const string& archivo, RED& red);
};

#endif // CARGAARCHIVOS_H
