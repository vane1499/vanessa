#include <iostream>
#include <memory>
#include <limits>
#include "producto_manager.h"
#include "persist_sqlite.h"

using namespace std;

void limpiarBuffer() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

int pedirEntero(const string& mensaje) {
    int valor;
    while (true) {
        cout << mensaje;
        if (cin >> valor) break;

        cout << " Entrada invalida. Debe ingresar un numero.\n";
        limpiarBuffer();
    }
    limpiarBuffer();
    return valor;
}

double pedirDouble(const string& mensaje) {
    double valor;
    while (true) {
        cout << mensaje;
        if (cin >> valor) break;

        cout << " Entrada invalida. Debe ingresar un numero.\n";
        limpiarBuffer();
    }
    limpiarBuffer();
    return valor;
}

string pedirString(const string& mensaje) {
    string s;
    cout << mensaje;
    getline(cin, s);
    return s;
}

void mostrarProductos(const vector<Producto>& lista) {
    cout << "\n LISTA DE PRODUCTOS\n";
    for (const auto& p : lista) {
        cout << "---------------------------------------\n";
        cout << "ID:     " << p.id << "\n";
        cout << "Nombre: " << p.nombre << "\n";
        cout << "Precio: " << p.precio << "\n";
        cout << "Stock:  " << p.stock << "\n";
    }
}

int main() {
    
    auto repo = make_shared<PersistSQLite>("data/tienda.db");
    ProductoManager manager(repo);

    if (!manager.init()) {
        cout << " Error al inicializar la base de datos.\n";
        return 1;
    }

    while (true) {
        cout << R"(
======= TIENDA (TUI) =======
1. Listar productos
2. Agregar producto
3. Editar producto
4. Eliminar producto
5. Salir
Opcion: )";

        int opcion = pedirEntero("");

        switch (opcion) {

        case 2: {
            Producto p;
            p.nombre = pedirString("Nombre: ");
            p.precio = pedirDouble("Precio: ");
            p.stock  = pedirEntero("Stock: ");

            if (manager.insertar(p))
                cout << "✔ Producto agregado.\n";
            else
                cout << " No se pudo agregar.\n";
            break;
        }

        case 3: {
            int id = pedirEntero("ID del producto a editar: ");

            auto lista = manager.listar();
            Producto encontrado;
            bool existe = false;

            for (auto& p : lista)
                if (p.id == id) { encontrado = p; existe = true; }

            if (!existe) {
                cout << " No existe ese ID.\n";
                break;
            }

            cout << "\n--- Deja vacio para no modificar ---\n";

            string nombre = pedirString("Nuevo nombre (" + encontrado.nombre + "): ");
            string precioS = pedirString("Nuevo precio (" + to_string(encontrado.precio) + "): ");
            string stockS  = pedirString("Nuevo stock (" + to_string(encontrado.stock) + "): ");

            if (!nombre.empty()) encontrado.nombre = nombre;
            if (!precioS.empty()) encontrado.precio = stod(precioS);
            if (!stockS.empty())  encontrado.stock  = stoi(stockS);

            if (manager.actualizar(encontrado))
                cout << "✔ Producto actualizado.\n";
            else
                cout << " No se pudo actualizar.\n";

            break;
        }

        case 4: {
            int id = pedirEntero("ID a eliminar: ");
            if (manager.eliminar(id))
                cout << "✔ Eliminado.\n";
            else
                cout << " No se pudo eliminar.\n";
            break;
        }

        case 1: {
            auto lista = manager.listar();
            mostrarProductos(lista);
            break;
        }

        case 5:
            manager.cerrar();
            return 0;

        default:
            cout << " Opción invalida.\n";
        }
    }
}
