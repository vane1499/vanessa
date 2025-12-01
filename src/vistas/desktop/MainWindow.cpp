#include "MainWindow.h"
#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    auto repo = std::make_shared<PersistSQLite>("data/tienda.db");
    m_mgr = ProductoManager(repo);
    m_mgr.init();
    QWidget* central = new QWidget(this);
    QVBoxLayout* layout = new QVBoxLayout(central);
    QLabel* label = new QLabel("Tienda Belleza - Desktop (Qt)", central);
    layout->addWidget(label);
    central->setLayout(layout);
    setCentralWidget(central);
    setWindowTitle("Tienda Belleza");
    resize(800, 600);
}

MainWindow::~MainWindow() {}
