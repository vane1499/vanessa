#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QDate>
#include <QPixmap>
#include <QTableWidgetItem>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Ruta de datos
    m_dataFilePath = QStringLiteral("data/productos.txt");

    // Conectar botones
    connect(ui->btnAdd, &QPushButton::clicked, this, &MainWindow::onAddProduct);
    connect(ui->btnRemove, &QPushButton::clicked, this, &MainWindow::onRemoveProduct);
    connect(ui->btnSelectImage, &QPushButton::clicked, this, &MainWindow::onSelectImage);
    connect(ui->comboFilter, &QComboBox::currentTextChanged, this, &MainWindow::onFilterChanged);
    connect(ui->tableProducts->selectionModel(), &QItemSelectionModel::selectionChanged, this, &MainWindow::onTableSelectionChanged);

    // Config tabla
    ui->tableProducts->setColumnCount(5);
    QStringList headers;
    headers << "Nombre" << "Precio" << "Tipo" << "Caducidad" << "Imagen";
    ui->tableProducts->setHorizontalHeaderLabels(headers);
    ui->tableProducts->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableProducts->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableProducts->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableProducts->horizontalHeader()->setStretchLastSection(true);

    loadStore();
    populateTypeFilter();
    refreshTable();

    ui->lblPreview->setText("Vista previa");
}

MainWindow::~MainWindow() {
    saveStore();
    delete ui;
}

void MainWindow::loadStore() {
    m_store.loadFromFile(m_dataFilePath);
}

void MainWindow::saveStore() {
    m_store.saveToFile(m_dataFilePath);
}

void MainWindow::populateTypeFilter() {
    QSet<QString> types;
    types.insert("Todos");
    for (const auto& p : m_store.products()) types.insert(p.type());
    ui->comboFilter->clear();
    for (const auto& t : types) ui->comboFilter->addItem(t);
}

void MainWindow::refreshTable() {
    QString selectedType = ui->comboFilter->currentText();
    auto list = m_store.filteredByType(selectedType);
    ui->tableProducts->setRowCount(static_cast<int>(list.size()));
    for (int r = 0; r < static_cast<int>(list.size()); ++r) {
        const auto& p = list.at(r);
        ui->tableProducts->setItem(r, 0, new QTableWidgetItem(p.name()));
        ui->tableProducts->setItem(r, 1, new QTableWidgetItem(QString::number(p.price(), 'f', 2)));
        ui->tableProducts->setItem(r, 2, new QTableWidgetItem(p.type()));
        ui->tableProducts->setItem(r, 3, new QTableWidgetItem(p.expiry().toString(Qt::ISODate)));
        ui->tableProducts->setItem(r, 4, new QTableWidgetItem(p.imagePath()));
    }
    ui->tableProducts->resizeColumnsToContents();
    ui->btnRemove->setEnabled(false);
    ui->lblPreview->clear();
}

void MainWindow::onAddProduct() {
    QString name = ui->lineName->text().trimmed();
    double price = ui->spinPrice->value();
    QString type = ui->lineType->text().trimmed();
    QDate expiry = ui->dateExpiry->date();
    QString imagePath = ui->lineImage->text().trimmed();

    if (name.isEmpty() || type.isEmpty()) {
        QMessageBox::warning(this, "Campos incompletos", "Por favor, complete el nombre y el tipo del producto.");
        return;
    }

    Product p(name, price, type, expiry, imagePath);
    m_store.addProduct(p);
    saveStore();
    populateTypeFilter();
    refreshTable();

    // Limpiar formulario
    ui->lineName->clear();
    ui->spinPrice->setValue(0.0);
    ui->lineType->clear();
    ui->dateExpiry->setDate(QDate::currentDate());
    ui->lineImage->clear();
}

void MainWindow::onRemoveProduct() {
    // Remueve el producto seleccionado en la tabla (índice relativo al filtro)
    QModelIndexList sel = ui->tableProducts->selectionModel()->selectedRows();
    if (sel.isEmpty()) return;
    int row = sel.first().row();

    // obtener lista filtrada y hallar el índice real en store
    QString filter = ui->comboFilter->currentText();
    auto filtered = m_store.filteredByType(filter);

    if (row < 0 || row >= static_cast<int>(filtered.size())) return;
    Product toRemove = filtered.at(row);

    // Buscar producto en la lista real (comparando nombre+tipo+expiry+price)
    const auto& all = m_store.products();
    for (int i = 0; i < static_cast<int>(all.size()); ++i) {
        const auto& p = all.at(i);
        if (p.name() == toRemove.name()
            && p.type() == toRemove.type()
            && qFuzzyCompare(p.price() + 1.0, toRemove.price() + 1.0)
            && p.expiry() == toRemove.expiry()) {
            m_store.removeProductAt(i);
            break;
        }
    }

    saveStore();
    populateTypeFilter();
    refreshTable();
}

void MainWindow::onFilterChanged(const QString& /*type*/) {
    refreshTable();
}

void MainWindow::onSelectImage() {
    QString path = QFileDialog::getOpenFileName(this, "Seleccionar imagen", QString(), "Imágenes (*.png *.jpg *.jpeg *.bmp)");
    if (!path.isEmpty()) {
        ui->lineImage->setText(path);
        QPixmap pix(path);
        if (!pix.isNull()) {
            ui->lblPreview->setPixmap(pix.scaled(ui->lblPreview->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
        }
    }
}

void MainWindow::onTableSelectionChanged() {
    QModelIndexList sel = ui->tableProducts->selectionModel()->selectedRows();
    if (sel.isEmpty()) {
        ui->btnRemove->setEnabled(false);
        ui->lblPreview->clear();
        return;
    }
    int row = sel.first().row();
    QString filter = ui->comboFilter->currentText();
    auto filtered = m_store.filteredByType(filter);
    if (row < 0 || row >= static_cast<int>(filtered.size())) return;
    const auto& p = filtered.at(row);
    ui->btnRemove->setEnabled(true);
    if (!p.imagePath().isEmpty()) {
        QPixmap pix(p.imagePath());
        if (!pix.isNull()) {
            ui->lblPreview->setPixmap(pix.scaled(ui->lblPreview->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
        } else {
            ui->lblPreview->setText("No se pudo cargar la imagen");
        }
    } else {
        ui->lblPreview->setText("Sin imagen");
    }
}
