#include "producto_manager.h"
#include <iostream>

ProductoManager::ProductoManager(std::shared_ptr<IPersistencia> repo)
    : m_repo(std::move(repo)) {}

ProductoManager::~ProductoManager() {
    if (m_repo) m_repo->cerrar();
}

bool ProductoManager::init() {
    if (!m_repo) return false;
    return m_repo->init();
}

void ProductoManager::cerrar() {
    if (m_repo) m_repo->cerrar();
}

bool ProductoManager::insertar(const Producto &p) {
    // usa el Template Method definido en ManagerBase
    return insertarProducto(p);
}

bool ProductoManager::actualizar(const Producto &p) {
    if (!m_repo) return false;
    return m_repo->actualizar(p);
}

bool ProductoManager::eliminar(int id) {
    if (!m_repo) return false;
    return m_repo->eliminar(id);
}

std::vector<Producto> ProductoManager::listar() const {
    if (!m_repo) return {};
    return m_repo->listar();
}

bool ProductoManager::validar(const Producto &p) {
    if (p.nombre.empty()) return false;
    if (p.precio < 0.0) return false;
    if (p.stock < 0) return false;
    return true;
}

bool ProductoManager::ejecutarInsert(const Producto &p) {
    if (!m_repo) return false;
    return m_repo->insertar(p);
}