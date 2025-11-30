#pragma once
#include "ipersistencia.h"
#include <QString>
#include <memory>

// Usa Qt SQL (QSqlDatabase, QSqlQuery)
class PersistSQLite : public IPersistencia {
public:
    explicit PersistSQLite(const QString &dbPath = QStringLiteral("database.db"));
    ~PersistSQLite() override;

    bool init() override;
    bool insertar(const Producto &p) override;
    bool actualizar(const Producto &p) override;
    bool eliminar(int id) override;
    std::vector<Producto> listar() override;
    bool cerrar() override;

private:
    QString m_dbPath;
    bool m_open{false};
};