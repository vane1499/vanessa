// TUI simple: mismo flujo que la consola pero con una pequeña interfaz de menu mejorada.
#include <iostream>
#include <memory>
#include "../managers/producto_manager.h"
#include "../persistencia/persist_sqlite.h"
#include "tui_curses.h"
#include <filesystem>

static void mostrarEncabezado() {
    std::cout << "+--------------------------------+\n";
    std::cout << "|   TIENDA - TUI (Terminal)     |\n";
    std::cout << "+--------------------------------+\n";
}

int main() {
    std::filesystem::create_directories("data");

    auto repo = std::make_shared<PersistSQLite>("data/tienda.db");
    ProductoManager mgr(repo);
    if (!mgr.init()) {
        // si falla inicializar la BD mostramos mensaje sin curses
        puts("Error inicializando DB (persist_sqlite). Asegurate de tener Qt SQL instalado.");
        return 1;
    }

    TuiCurses tui(mgr);
    tui.run();

    mgr.cerrar();
    return 0;
}

int main_tui() {
    std::filesystem::create_directories("data");
    auto repo = std::make_shared<PersistSQLite>("data/tienda.db");
    ProductoManager mgr(repo);
    if (!mgr.init()) {
        std::cerr << "Error inicializando DB\n";
        return 1;
    }

    int opt = 0;
    while (opt != 5) {
        mostrarEncabezado();
        std::cout << "1) Añadir producto\n2) Listar\n3) Editar\n4) Borrar\n5) Salir\n> ";
        std::cin >> opt;
        if (opt == 1) {
            Producto p; std::cin.ignore();
            std::cout << "Nombre: "; std::getline(std::cin, p.nombre);
            std::cout << "Precio: "; std::cin >> p.precio;
            std::cout << "Stock: "; std::cin >> p.stock;
            mgr.insertar(p);
        } else if (opt == 2) {
            auto lista = mgr.listar();
            for (auto &it : lista) std::cout << it.id << " | " << it.nombre << " | " << it.precio << " | " << it.stock << "\n";
            std::cout << "Presione Enter para continuar..."; std::cin.ignore(); std::cin.get();
        } else if (opt == 3) {
            Producto p; std::cout << "ID: "; std::cin >> p.id; std::cin.ignore();
            std::cout << "Nombre: "; std::getline(std::cin, p.nombre);
            std::cout << "Precio: "; std::cin >> p.precio;
            std::cout << "Stock: "; std::cin >> p.stock;
            mgr.actualizar(p);
        } else if (opt == 4) {
            int id; std::cout << "ID: "; std::cin >> id; mgr.eliminar(id);
        }
    }

    mgr.cerrar();
    return 0;
}