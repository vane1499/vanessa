#pragma once
#include "manager_base.h"
#include "../persistencia/ipersistencia.h"
#include <memory>
#include <vector>

class ProductoManager : public ManagerBase {
public:
    explicit ProductoManager(std::shared_ptr<IPersistencia> repo);
    ~ProductoManager();

    // Carga/guardar se exponen para control desde la UI
    bool init();
    void cerrar();

    // CRUD desde managers
    bool insertar(const Producto &p); // wrapper que usa Template Method
    bool actualizar(const Producto &p);
    bool eliminar(int id);
    std::vector<Producto> listar() const;

protected:
    bool validar(const Producto &p) override;
    bool ejecutarInsert(const Producto &p) override;

private:
    std::shared_ptr<IPersistencia> m_repo;
};