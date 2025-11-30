#pragma once

#include <vector>
#include "../modelos/producto.h"

class IPersistencia {
public:
    virtual ~IPersistencia() = default;

    virtual bool init() = 0; // crear tablas, abrir DB, etc.
    virtual bool insertar(const Producto &p) = 0;
    virtual bool actualizar(const Producto &p) = 0;
    virtual bool eliminar(int id) = 0;
    virtual std::vector<Producto> listar() = 0;
    virtual bool cerrar() = 0;
};