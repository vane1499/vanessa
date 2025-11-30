#include "tui_curses.h"
#include <curses.h>
#include <string>
#include <sstream>
#include <limits>
#include <iomanip>
#include <cstring>

TuiCurses::TuiCurses(ProductoManager &mgr) : m_mgr(mgr) {
    // nothing
}

TuiCurses::~TuiCurses() {
    // nothing
}

void TuiCurses::run() {
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    if (has_colors()) {
        start_color();
        use_default_colors();
        init_pair(1, COLOR_WHITE, COLOR_BLUE); // header
        init_pair(2, COLOR_YELLOW, -1); // highlight
    }

    int ch = 0;
    while (true) {
        clear();
        drawMain();
        mvprintw(LINES - 2, 2, "Seleccione opcion (1-5): ");
        refresh();
        ch = getch();
        if (ch == '1') listProducts();
        else if (ch == '2') addProduct();
        else if (ch == '3') editProduct();
        else if (ch == '4') deleteProduct();
        else if (ch == '5' || ch == 'q' || ch == 'Q') break;
    }

    endwin();
}

void TuiCurses::drawMain() {
    int w = COLS;
    attron(COLOR_PAIR(1));
    mvhline(0, 0, ' ', w);
    mvprintw(0, 2, " TIENDA BELLEZA - TUI (PDCurses) ");
    attroff(COLOR_PAIR(1));

    mvprintw(2, 4, "1) Listar productos");
    mvprintw(3, 4, "2) Agregar producto");
    mvprintw(4, 4, "3) Editar producto (por ID)");
    mvprintw(5, 4, "4) Eliminar producto (por ID)");
    mvprintw(6, 4, "5) Salir (o 'q')");
    mvprintw(8, 4, "Base de datos: database.db (raiz del proyecto)");
}

void TuiCurses::listProducts() {
    clear();
    auto lista = m_mgr.listar();
    mvprintw(0, 2, "Listado de productos (presione Up/Down para navegar, 'b' para volver)");

    int start = 0;
    int cursor = 0;
    int pageSize = LINES - 4;
    int total = (int)lista.size();

    bool running = true;
    while (running) {
        clear();
        mvprintw(0, 2, "Listado de productos (Total: %d)", total);
        for (int i = 0; i < pageSize && start + i < total; ++i) {
            int idx = start + i;
            if (idx == cursor) attron(A_REVERSE);
            mvprintw(2 + i, 2, "%3d | %-30.30s | %8.2f | %4d",
                     lista[idx].id,
                     lista[idx].nombre.c_str(),
                     lista[idx].precio,
                     lista[idx].stock);
            if (idx == cursor) attroff(A_REVERSE);
        }
        mvprintw(LINES - 1, 2, "Up/Down: navegar  PgUp/PgDn: paginas  'b' volver");
        refresh();

        int ch = getch();
        switch (ch) {
            case KEY_UP:
                if (cursor > 0) cursor--;
                if (cursor < start) start = cursor;
                break;
            case KEY_DOWN:
                if (cursor < total - 1) {
                    cursor++;
                    if (cursor >= start + pageSize) start = cursor - pageSize + 1;
                }
                break;
            case KEY_NPAGE: // Page Down
                cursor = std::min(total - 1, cursor + pageSize);
                start = std::min(std::max(0, cursor - pageSize + 1), std::max(0, total - pageSize));
                break;
            case KEY_PPAGE: // Page Up
                cursor = std::max(0, cursor - pageSize);
                start = std::max(0, std::min(cursor, total - pageSize));
                break;
            case 'b':
            case 'B':
            case 27: // ESC
                running = false;
                break;
            default:
                break;
        }
        if (total == 0) {
            mvprintw(3, 2, "(No hay productos)");
            getch();
            running = false;
        }
    }
}

void TuiCurses::addProduct() {
    echo();
    curs_set(1);
    clear();
    mvprintw(1, 2, "AGREGAR PRODUCTO (enter para confirmar)");
    std::string nombre = promptString("Nombre: ");
    double precio = promptDouble("Precio: ");
    int stock = promptNumber("Stock: ");
    Producto p;
    p.nombre = nombre;
    p.precio = precio;
    p.stock = stock;
    if (m_mgr.insertar(p)) {
        mvprintw(LINES - 3, 2, "Producto insertado correctamente. Presione tecla.");
    } else {
        mvprintw(LINES - 3, 2, "Error insertando producto (validacion/DB). Presione tecla.");
    }
    noecho();
    curs_set(0);
    getch();
}

void TuiCurses::editProduct() {
    echo();
    curs_set(1);
    clear();
    mvprintw(1, 2, "EDITAR PRODUCTO");
    int id = promptNumber("ID a editar: ");
    // pedimos nuevos campos
    std::string nombre = promptString("Nuevo nombre: ");
    double precio = promptDouble("Nuevo precio: ");
    int stock = promptNumber("Nuevo stock: ");
    Producto p;
    p.id = id;
    p.nombre = nombre;
    p.precio = precio;
    p.stock = stock;
    if (m_mgr.actualizar(p)) {
        mvprintw(LINES - 3, 2, "Producto actualizado. Presione tecla.");
    } else {
        mvprintw(LINES - 3, 2, "Error al actualizar. Presione tecla.");
    }
    noecho();
    curs_set(0);
    getch();
}

void TuiCurses::deleteProduct() {
    echo();
    curs_set(1);
    clear();
    mvprintw(1, 2, "ELIMINAR PRODUCTO");
    int id = promptNumber("ID a eliminar: ");
    if (m_mgr.eliminar(id)) {
        mvprintw(LINES - 3, 2, "Producto eliminado. Presione tecla.");
    } else {
        mvprintw(LINES - 3, 2, "No encontrado o error. Presione tecla.");
    }
    noecho();
    curs_set(0);
    getch();
}

int TuiCurses::promptNumber(const char *label, int minVal, int maxVal) {
    char buf[128];
    while (true) {
        mvprintw(3, 2, "%s", label);
        echo();
        curs_set(1);
        mvgetnstr(3, (int)strlen(label) + 3, buf, sizeof(buf) - 1);
        noecho();
        curs_set(0);
        std::istringstream ss(buf);
        long long val;
        if ((ss >> val) && val >= minVal && val <= maxVal) return (int)val;
        mvprintw(5, 2, "Entrada invalida. Intente de nuevo.");
    }
}

double TuiCurses::promptDouble(const char *label, double minVal, double maxVal) {
    char buf[256];
    while (true) {
        mvprintw(3, 2, "%s", label);
        echo();
        curs_set(1);
        mvgetnstr(3, (int)strlen(label) + 3, buf, sizeof(buf) - 1);
        noecho();
        curs_set(0);
        std::istringstream ss(buf);
        double val;
        if ((ss >> val) && val >= minVal && val <= maxVal) return val;
        mvprintw(5, 2, "Entrada invalida. Intente de nuevo.");
    }
}

std::string TuiCurses::promptString(const char *label) {
    char buf[512];
    mvprintw(3, 2, "%s", label);
    echo();
    curs_set(1);
    mvgetnstr(3, (int)strlen(label) + 3, buf, sizeof(buf) - 1);
    noecho();
    curs_set(0);
    return std::string(buf);
}
