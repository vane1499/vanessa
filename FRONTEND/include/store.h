#pragma once
#include "product.h"
#include <vector>
#include <QString>

class Store {
public:
    Store() = default;
    bool loadFromFile(const QString& path);   // carga productos.txt
    bool saveToFile(const QString& path) const;
    void addProduct(const Product& p);
    void removeProductAt(int index);
    const std::vector<Product>& products() const;
    std::vector<Product> filteredByType(const QString& type) const; // "Todos" devuelve todo

private:
    std::vector<Product> m_products;
};
