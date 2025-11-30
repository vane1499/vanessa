#include "persist_sqlite.h"
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QVariant>
#include <iostream>

PersistSQLite::PersistSQLite(const QString &dbPath)
    : m_dbPath(dbPath) {}

PersistSQLite::~PersistSQLite() {
    cerrar();
}

bool PersistSQLite::init() {
    if (m_open) return true;
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(m_dbPath);
    if (!db.open()) {
        std::cerr << "Error abriendo DB: " << db.lastError().text().toStdString() << '\n';
        return false;
    }
    QSqlQuery q;
    // Crear tabla si no existe
    const QString create = R"(
        CREATE TABLE IF NOT EXISTS productos (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            nombre TEXT NOT NULL,
            precio REAL NOT NULL,
            stock INTEGER NOT NULL
        )
    )";
    if (!q.exec(create)) {
        std::cerr << "Error creando tabla: " << q.lastError().text().toStdString() << '\n';
        return false;
    }
    m_open = true;
    return true;
}

bool PersistSQLite::insertar(const Producto &p) {
    if (!m_open) if (!init()) return false;
    QSqlQuery q;
    q.prepare("INSERT INTO productos (nombre, precio, stock) VALUES (:n, :pr, :st)");
    q.bindValue(":n", QString::fromStdString(p.nombre));
    q.bindValue(":pr", p.precio);
    q.bindValue(":st", p.stock);
    if (!q.exec()) {
        std::cerr << "Insert error: " << q.lastError().text().toStdString() << '\n';
        return false;
    }
    return true;
}

bool PersistSQLite::actualizar(const Producto &p) {
    if (!m_open) if (!init()) return false;
    QSqlQuery q;
    q.prepare("UPDATE productos SET nombre = :n, precio = :pr, stock = :st WHERE id = :id");
    q.bindValue(":n", QString::fromStdString(p.nombre));
    q.bindValue(":pr", p.precio);
    q.bindValue(":st", p.stock);
    q.bindValue(":id", p.id);
    if (!q.exec()) {
        std::cerr << "Update error: " << q.lastError().text().toStdString() << '\n';
        return false;
    }
    return true;
}

bool PersistSQLite::eliminar(int id) {
    if (!m_open) if (!init()) return false;
    QSqlQuery q;
    q.prepare("DELETE FROM productos WHERE id = :id");
    q.bindValue(":id", id);
    if (!q.exec()) {
        std::cerr << "Delete error: " << q.lastError().text().toStdString() << '\n';
        return false;
    }
    return true;
}

std::vector<Producto> PersistSQLite::listar() {
    std::vector<Producto> out;
    if (!m_open) if (!init()) return out;
    QSqlQuery q("SELECT id, nombre, precio, stock FROM productos ORDER BY id");
    while (q.next()) {
        Producto p;
        p.id = q.value(0).toInt();
        p.nombre = q.value(1).toString().toStdString();
        p.precio = q.value(2).toDouble();
        p.stock = q.value(3).toInt();
        out.push_back(p);
    }
    return out;
}

bool PersistSQLite::cerrar() {
    if (!m_open) return true;
    QSqlDatabase db = QSqlDatabase::database();
    db.close();
    QSqlDatabase::removeDatabase(QSqlDatabase::defaultConnection);
    m_open = false;
    return true;
}