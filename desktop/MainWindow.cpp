#include "MainWindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QInputDialog>
#include <QMessageBox>
#include <QHeaderView>
#include <QLabel>
#include <filesystem>
#include <QString>

// Constructor
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    // 1) Aseguramos la carpeta data y la BD común
    std::filesystem::create_directories("data");
    auto repo = std::make_shared<PersistSQLite>("data/tienda.db");

    // 2) Creamos el manager (se guarda en unique_ptr para manejo RAII)
    m_mgr = std::make_unique<ProductoManager>(repo);
    if (!m_mgr->init()) {
        QMessageBox::critical(this, "Error", "No se pudo inicializar la base de datos.");
        // no retornamos; igual intentamos mostrar UI para depurar
    }

    setupUI();
    loadData();
    setWindowTitle("Tienda Belleza - Desktop");
    resize(900, 600);
}

// Destructor
MainWindow::~MainWindow() {
    if (m_mgr) m_mgr->cerrar();
}

// Montaje de la UI
void MainWindow::setupUI() {
    QWidget *central = new QWidget(this);
    QVBoxLayout *mainLayout = new QVBoxLayout(central);

    // Label superior
    QLabel* header = new QLabel("Tienda Belleza — Desktop", central);
    header->setStyleSheet("font-weight: bold; font-size: 18px;");
    mainLayout->addWidget(header);

    // Tabla
    table = new QTableWidget(0, 4, central);
    table->setHorizontalHeaderLabels(QStringList() << "ID" << "Nombre" << "Precio" << "Stock");
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    table->setSelectionBehavior(QAbstractItemView::SelectRows);
    table->setSelectionMode(QAbstractItemView::SingleSelection);
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    mainLayout->addWidget(table, /*stretch=*/1);

    // Botones
    QHBoxLayout *hl = new QHBoxLayout();
    btnAdd = new QPushButton("Agregar", central);
    btnEdit = new QPushButton("Editar", central);
    btnDelete = new QPushButton("Eliminar", central);
    btnRefresh = new QPushButton("Refrescar", central);

    hl->addWidget(btnAdd);
    hl->addWidget(btnEdit);
    hl->addWidget(btnDelete);
    hl->addStretch();
    hl->addWidget(btnRefresh);

    mainLayout->addLayout(hl);
    central->setLayout(mainLayout);
    setCentralWidget(central);

    // Conectar señales
    connect(btnAdd, &QPushButton::clicked, this, &MainWindow::onAdd);
    connect(btnEdit, &QPushButton::clicked, this, &MainWindow::onEdit);
    connect(btnDelete, &QPushButton::clicked, this, &MainWindow::onDelete);
    connect(btnRefresh, &QPushButton::clicked, this, &MainWindow::onRefresh);
}

// Cargar datos desde manager -> tabla
void MainWindow::loadData() {
    table->setRowCount(0);
    if (!m_mgr) return;

    auto lista = m_mgr->listar();
    table->setRowCount((int)lista.size());

    for (int i = 0; i < (int)lista.size(); ++i) {
        const auto &p = lista[i];
        QTableWidgetItem *idItem = new QTableWidgetItem(QString::number(p.id));
        QTableWidgetItem *nameItem = new QTableWidgetItem(QString::fromStdString(p.nombre));
        QTableWidgetItem *priceItem = new QTableWidgetItem(QString::number(p.precio, 'f', 2));
        QTableWidgetItem *stockItem = new QTableWidgetItem(QString::number(p.stock));

        // alinear
        idItem->setTextAlignment(Qt::AlignCenter);
        priceItem->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
        stockItem->setTextAlignment(Qt::AlignCenter);

        table->setItem(i, 0, idItem);
        table->setItem(i, 1, nameItem);
        table->setItem(i, 2, priceItem);
        table->setItem(i, 3, stockItem);
    }
}

// Helper: buscar Producto por ID (lanza si no encontrado)
Producto MainWindow::findProductById(int id) {
    Producto notFound;
    auto lista = m_mgr->listar();
    for (const auto &p : lista) {
        if (p.id == id) return p;
    }
    return notFound; // id=0 o default indica no encontrado
}

// ----------------- SLOTS CRUD -----------------

void MainWindow::onAdd() {
    bool ok;
    QString nombre = QInputDialog::getText(this, "Agregar producto", "Nombre:", QLineEdit::Normal, "", &ok);
    if (!ok || nombre.trimmed().isEmpty()) {
        QMessageBox::information(this, "Info", "Nombre vacío. Operación cancelada.");
        return;
    }

    double precio = QInputDialog::getDouble(this, "Agregar producto", "Precio:", 1.0, 0.0, 1e9, 2, &ok);
    if (!ok) return;

    int stock = QInputDialog::getInt(this, "Agregar producto", "Stock:", 1, 0, 1000000, 1, &ok);
    if (!ok) return;

    Producto p;
    p.nombre = nombre.toStdString();
    p.precio = precio;
    p.stock = stock;

    if (!m_mgr->insertar(p)) {
        QMessageBox::warning(this, "Error", "No se pudo insertar el producto. Verifique validaciones o BD.");
    }
    loadData();
}

void MainWindow::onEdit() {
    auto sels = table->selectionModel()->selectedRows();
    if (sels.empty()) {
        QMessageBox::information(this, "Info", "Seleccione una fila para editar.");
        return;
    }

    int row = sels.first().row();
    int id = table->item(row, 0)->text().toInt();

    auto current = findProductById(id);
    if (current.id == 0) {
        QMessageBox::warning(this, "Error", "Producto no encontrado.");
        return;
    }

    bool ok;
    QString nuevoNombre = QInputDialog::getText(this, "Editar producto", "Nombre:", QLineEdit::Normal, QString::fromStdString(current.nombre), &ok);
    if (!ok) return;

    double nuevoPrecio = QInputDialog::getDouble(this, "Editar producto", "Precio:", current.precio, 0.0, 1e9, 2, &ok);
    if (!ok) return;

    int nuevoStock = QInputDialog::getInt(this, "Editar producto", "Stock:", current.stock, 0, 1000000, 1, &ok);
    if (!ok) return;

    Producto p = current;
    p.nombre = nuevoNombre.toStdString();
    p.precio = nuevoPrecio;
    p.stock = nuevoStock;

    if (!m_mgr->actualizar(p)) {
        QMessageBox::warning(this, "Error", "No se pudo actualizar el producto.");
    }
    loadData();
}

void MainWindow::onDelete() {
    auto sels = table->selectionModel()->selectedRows();
    if (sels.empty()) {
        QMessageBox::information(this, "Info", "Seleccione una fila para eliminar.");
        return;
    }

    int row = sels.first().row();
    int id = table->item(row, 0)->text().toInt();

    auto reply = QMessageBox::question(this, "Confirmar", QString("¿Eliminar producto ID %1 ?").arg(id),
                                       QMessageBox::Yes | QMessageBox::No);
    if (reply != QMessageBox::Yes) return;

    if (!m_mgr->eliminar(id)) {
        QMessageBox::warning(this, "Error", "No se pudo eliminar (tal vez no existe).");
    }
    loadData();
}

void MainWindow::onRefresh() {
    loadData();
}
