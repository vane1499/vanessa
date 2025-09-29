#pragma once
#include <QMainWindow>
#include "store.h"

namespace Ui { class MainWindow; }

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

private slots:
    void onAddProduct();
    void onRemoveProduct();
    void onFilterChanged(const QString& type);
    void onSelectImage();
    void onTableSelectionChanged();
    void refreshTable();

private:
    Ui::MainWindow* ui;
    Store m_store;
    QString m_dataFilePath;
    void loadStore();
    void saveStore();
    void populateTypeFilter();
};