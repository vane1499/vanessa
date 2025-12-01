#include <curses.h>
#include <string>
#include "tui_curses.h"

TuiCurses::TuiCurses(ProductoManager &mgr) : m_mgr(mgr) {}

void TuiCurses::run() {
    initscr();
    noecho();
    cbreak();
    curs_set(0);

    int opcion = 0;

    while (true) {
        clear();
        mvprintw(1, 2, "=== TIENDA TUI ===");
        mvprintw(3, 2, "1. Listar productos");
        mvprintw(4, 2, "2. Agregar producto");
        mvprintw(5, 2, "3. Editar producto");
        mvprintw(6, 2, "4. Eliminar producto");
        mvprintw(7, 2, "5. Salir");
        mvprintw(9, 2, "Seleccione: ");
        opcion = getch() - '0';

        switch (opcion) {
            case 1: listProducts(); break;
            case 2: addProduct(); break;
            case 3: editProduct(); break;
            case 4: deleteProduct(); break;
            case 5: endwin(); return;
        }
    }
}

void TuiCurses::listProducts() {
    clear();
    auto productos = m_mgr.listar();

    mvprintw(1, 2, "=== LISTA DE PRODUCTOS ===");

    int y = 3;
    for (auto &p : productos) {
        mvprintw(y++, 2, "ID: %d | %s | %.2f Bs | Stock: %d",
                 p.id, p.nombre.c_str(), p.precio, p.stock);
    }

    mvprintw(y + 1, 2, "Presione una tecla para continuar...");
    getch();
}

void TuiCurses::addProduct() {
    clear();
    mvprintw(1, 2, "=== AGREGAR PRODUCTO ===");

    std::string nombre = promptString("Nombre: ");
    double precio = promptDouble("Precio: ");
    int stock = promptNumber("Stock: ");

    Producto p;
    p.nombre = nombre;
    p.precio = precio;
    p.stock = stock;

    m_mgr.insertarProducto(p);

    mvprintw(10, 2, "Producto agregado. Presione una tecla...");
    getch();
}

void TuiCurses::editProduct() {
    clear();
    mvprintw(1, 2, "=== EDITAR PRODUCTO ===");

    int id = promptNumber("ID a editar: ");

    auto lista = m_mgr.listar();
    bool existe = false;
    Producto current;

    for (auto &p : lista)
        if (p.id == id) { current = p; existe = true; }

    if (!existe) {
        mvprintw(10, 2, "ID no encontrado. Tecla para volver...");
        getch();
        return;
    }

    std::string nombre = promptStringAllowEmpty("Nuevo nombre (enter = igual): ");
    double precio = promptDoubleAllowEmpty("Nuevo precio (enter = igual): ", current.precio);
    int stock = promptNumberAllowEmpty("Nuevo stock (enter = igual): ", current.stock);

    if (!nombre.empty()) current.nombre = nombre;
    current.precio = precio;
    current.stock = stock;

    m_mgr.actualizar(current);

    mvprintw(15, 2, "Producto editado. Presione una tecla...");
    getch();
}

void TuiCurses::deleteProduct() {
    clear();
    mvprintw(1, 2, "=== ELIMINAR PRODUCTO ===");

    int id = promptNumber("ID a eliminar: ");

    m_mgr.eliminar(id);

    mvprintw(10, 2, "Producto eliminado. Presione una tecla...");
    getch();
}

// =========================
// INPUT HELPERS
// =========================

std::string TuiCurses::promptString(const char *label) {
    echo();
    nocbreak();
    curs_set(1);

    mvprintw(12, 2, "%s", label);

    char buffer[256];
    getnstr(buffer, 255);

    noecho();
    cbreak();
    curs_set(0);

    return std::string(buffer);
}

std::string TuiCurses::promptStringAllowEmpty(const char *label) {
    echo();
    nocbreak();
    curs_set(1);

    mvprintw(12, 2, "%s", label);

    char buffer[256];
    getnstr(buffer, 255);

    noecho();
    cbreak();
    curs_set(0);

    return std::string(buffer);
}

int TuiCurses::promptNumber(const char *label) {
    while (true) {
        std::string txt = promptString(label);
        try {
            return std::stoi(txt);
        } catch (...) {
            mvprintw(20, 2, "❌ Debe ser un número.");
        }
    }
}

int TuiCurses::promptNumberAllowEmpty(const char *label, int defaultVal) {
    std::string txt = promptStringAllowEmpty(label);
    if (txt.empty()) return defaultVal;
    return std::stoi(txt);
}

double TuiCurses::promptDouble(const char *label) {
    while (true) {
        std::string txt = promptString(label);
        try {
            return std::stod(txt);
        } catch (...) {
            mvprintw(20, 2, "❌ Debe ser decimal.");
        }
    }
}

double TuiCurses::promptDoubleAllowEmpty(const char *label, double defaultVal) {
    std::string txt = promptStringAllowEmpty(label);
    if (txt.empty()) return defaultVal;
    return std::stod(txt);
}
