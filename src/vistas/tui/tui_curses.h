#ifndef TUI_CURSES_H
#define TUI_CURSES_H

#include <string>
#include "../../managers/producto_manager.h"

class TuiCurses {
private:
    ProductoManager &m_mgr;

public:
    TuiCurses(ProductoManager &mgr);

    void run();
    void addProduct();
    void editProduct();
    void deleteProduct();
    void listProducts();

    // === INPUTS ===
    int promptNumber(const char *label);
    int promptNumberAllowEmpty(const char *label, int defaultVal);

    double promptDouble(const char *label);
    double promptDoubleAllowEmpty(const char *label, double defaultVal);

    std::string promptString(const char *label);
    std::string promptStringAllowEmpty(const char *label);
};

#endif
