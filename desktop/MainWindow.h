#pragma once

#include <QMainWindow>
#include <QTableWidget>
#include <QPushButton>
#include <memory>

#include "../managers/producto_manager.h"
#include "../persistencia/persist_sqlite.h"

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

private slots:
    void onAdd();
    void onEdit();
    void onDelete();
    void onRefresh();

private:
    // UI
    QTableWidget *table;
    QPushButton *btnAdd;
    QPushButton *btnEdit;
    QPushButton *btnDelete;
    QPushButton *btnRefresh;

    // Lógica
    std::unique_ptr<ProductoManager> m_mgr;

    // helpers
    void setupUI();
    void loadData();
    Producto findProductById(int id);
};
