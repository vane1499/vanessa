#pragma once
#include <string>

class Producto {
public:
    int id;
    std::string nombre;
    double precio;
    int stock;

    Producto() : id(0), nombre(""), precio(0.0), stock(0) {}
    Producto(int id_, const std::string &n, double p, int s)
        : id(id_), nombre(n), precio(p), stock(s) {}
};