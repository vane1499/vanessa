#include <iostream>
#include <memory>
#include "../managers/producto_manager.h"
#include "../persistencia/persist_sqlite.h"

int main() {
    auto repo = std::make_shared<PersistSQLite>(QStringLiteral("database.db"));
    ProductoManager mgr(repo);
    if (!mgr.init()) {
        std::cerr << "No se pudo inicializar la persistencia SQLite.\n";
        return 1;
    }

    int opt = 0;
    do {
        std::cout << "\n=== TIENDA (Consola) ===\n";
        std::cout << "1) Insertar\n2) Listar\n3) Actualizar por ID\n4) Eliminar por ID\n5) Salir\n> ";
        std::cin >> opt;
        if (opt == 1) {
            Producto p;
            std::cin.ignore();
            std::cout << "Nombre: "; std::getline(std::cin, p.nombre);
            std::cout << "Precio: "; std::cin >> p.precio;
            std::cout << "Stock: "; std::cin >> p.stock;
            if (mgr.insertar(p)) std::cout << "Insertado OK\n";
            else std::cout << "Error insertando (validacion o BD)\n";
        } else if (opt == 2) {
            auto lista = mgr.listar();
            std::cout << "---- Productos ----\n";
            for (const auto &it : lista) {
                std::cout << it.id << " | " << it.nombre << " | " << it.precio << " | " << it.stock << "\n";
            }
        } else if (opt == 3) {
            Producto p;
            std::cout << "ID a actualizar: "; std::cin >> p.id;
            std::cin.ignore();
            std::cout << "Nombre: "; std::getline(std::cin, p.nombre);
            std::cout << "Precio: "; std::cin >> p.precio;
            std::cout << "Stock: "; std::cin >> p.stock;
            if (mgr.actualizar(p)) std::cout << "Actualizado OK\n"; else std::cout << "Error al actualizar\n";
        } else if (opt == 4) {
            int id; std::cout << "ID a eliminar: "; std::cin >> id;
            if (mgr.eliminar(id)) std::cout << "Eliminado OK\n"; else std::cout << "No encontrado o error\n";
        }
    } while (opt != 5);

    mgr.cerrar();
    std::cout << "Saliendo...\n";
    return 0;
}