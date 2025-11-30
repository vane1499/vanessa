#pragma once
#include <vector>
#include "../managers/producto_manager.h"

class TuiCurses {
public:
    explicit TuiCurses(ProductoManager &mgr);
    ~TuiCurses();

    void run();

private:
    ProductoManager &m_mgr;

    void drawMain();
    void listProducts();
    void addProduct();
    void editProduct();
    void deleteProduct();

    // helpers
    int promptNumber(const char *label, int minVal = INT_MIN, int maxVal = INT_MAX);
    std::string promptString(const char *label);
    double promptDouble(const char *label, double minVal = -1e300, double maxVal = 1e300);
};
