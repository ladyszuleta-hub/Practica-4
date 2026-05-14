#include <iostream>
#include <fstream>
#include <sstream>
#include "red.h"
#include "cargaarchivos.h"

using namespace std;

int main() {

    RED red;
    Cargaarchivos ca;

    int opcion;

    do {

        cout << "\n========== MENU RED ==========\n";
        cout << "1. Agregar topologia desde archivo\n";
        cout << "2. Agregar router\n";
        cout << "3. Eliminar router\n";
        cout << "4. Agregar enlace\n";
        cout << "5. Eliminar enlace\n";
        cout << "6. Mostrar topologia\n";
        cout << "7. Mostrar tablas\n";
        cout << "8. Buscar camino\n";
        cout << "9. Salir\n";
        cout << "Seleccione una opcion: ";

        cin >> opcion;
        switch(opcion) {

        case 1: {

            ca.cargarDesdeArchivo("topologia.txt", red);

            break;
        }
        case 2: {

            string id;
            cout << "\nNombre del router: ";
            cin >> id;
            red.agregarRouter(id);

            break;
        }

        case 3: {

            string id;

            cout << "\nIngrese el router a eliminar: ";
            cin >> id;
            red.eliminarRouter(id);
            cout << "\nRouter eliminado.\n";

            break;
        }

        case 4:{
            string a, b;
            int costo;
            cout << "Router origen: "<<endl;
            cin >> a;
            cout <<"Router destino: "<<endl;
            cin >> b;
            cout << "costo: "<<endl;
            cin>> costo;
            red.agregarEnlace(a,b,costo);

            break;
        }

        case 5:{
            string a, b;
            cout << "Router 1:"<<endl;
            cin >> a;
            cout <<"Router 2: "<<endl;
            cin >> b;
            red.eliminarEnlace(a,b);
            break;
        }
        case 6:{
            red.mostrarTopologia();
            break;
        }
        case 7:{
            red.mostrarTablas();
            break;
        }
        case 8:{
            string origen, destino;
            cout<<"Origen: ";
            cin>> origen;
            cout<<"Destino: ";
            cin>>destino;
            vector <string> ruta=
                red.camino(origen,destino);
            if (ruta.empty())
                cout << "No existe camino.\n";
            else {
                cout <<"camino: ";
                for (size_t i=0; i<ruta.size();i++){
                    cout <<ruta[i];
                    if (i!= ruta.size()-1)
                        cout<<"->";
                }
                cout<<endl;
                cout << "Costo total: "<<red.costoCamino(origen,destino)<<endl;
            }
            break;
        }
        case 9:{
        cout << "Saliendo...\n";
        break;
        }
    default:
        cout << "\nOpcion invalida.\n";
    }

    } while(opcion != 9);

    return 0;
}
