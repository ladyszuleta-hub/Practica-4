#include "Router.h"

int main() {

    string nombre;

    cout << "Ingrese el nombre del router: ";
    cin >> nombre;

    Router router(nombre);

    int opcion;

    do {

        cout << "\n========== MENU ==========\n";
        cout << "1. Agregar vecino\n";
        cout << "2. Eliminar vecino\n";
        cout << "3. Mostrar vecinos\n";
        cout << "4. Mostrar tabla de costos\n";
        cout << "5. Salir\n";
        cout << "Seleccione una opcion: ";

        cin >> opcion;

        switch(opcion) {

        case 1: {

            string vecino;
            int costo;

            cout << "\nNombre del vecino: ";
            cin >> vecino;
            cout << "Costo del enlace: ";
            cin >> costo;

            while (costo < 0) {

                cout << "Costo invalido. Ingrese nuevamente: ";
                cin >> costo;
            }

            router.agregarVecino(vecino,costo);
            cout << "\nVecino agregado correctamente.\n";

            break;
        }

        case 2: {

            string vecino;

            cout << "\nIngrese el vecino a eliminar: ";
            cin >> vecino;
            router.eliminarVecino(vecino);
            cout << "\nVecino eliminado.\n";

            break;
        }

        case 3:
            cout << "\n===== VECINOS =====\n";
            router.mostrarVecinos();
            break;

        case 4:
            cout << "\n===== TABLA DE COSTOS =====\n";
            router.mostrarTablaCostos();
            break;

        case 5:
            cout << "\nSaliendo del programa...\n";
            break;

        default:
            cout << "\nOpcion invalida.\n";
        }

    } while(opcion != 5);

    return 0;
}
