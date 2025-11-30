#pragma once

#include "../modelos/producto.h"

class ManagerBase {
public:
    virtual ~ManagerBase() = default;

    // Template method público que demuestra la estructura fija
    bool insertarProducto(const Producto &p) {
        if (!validar(p)) return false;
        antesInsertar(p);
        bool ok = ejecutarInsert(p);
        despuesInsertar(p, ok);
        return ok;
    }

protected:
    // pasos que las subclases deben implementar/pueden sobrecargar
    virtual bool validar(const Producto &p) = 0;
    virtual void antesInsertar(const Producto &p) { /* hook opcional */ }
    virtual bool ejecutarInsert(const Producto &p) = 0;
    virtual void despuesInsertar(const Producto &p, bool exito) { /* hook opcional */ }
};