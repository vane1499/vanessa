#include <iostream>
#include <QString>
#include <QCoreApplication>
#include "store.h"
#include <QTextStream>

void printMenu() {
    std::cout << "=== Tienda Belleza (Consola) ===\n";
    std::cout << "1) Listar productos\n";
    std::cout << "2) Agregar producto\n";
    std::cout << "3) Eliminar producto (por índice)\n";
    std::cout << "4) Guardar y salir\n";
    std::cout << "Elija una opción: ";
}

int main_console(int argc, char** argv) {
    QCoreApplication app(argc, argv);
    Store s;
    QString path = "data/productos.txt";
    s.loadFromFile(path);

    int opt = 0;
    while (true) {
        printMenu();
        std::cin >> opt;
        if (opt == 1) {
            const auto& prods = s.products();
            for (size_t i = 0; i < prods.size(); ++i) {
                const auto& p = prods.at(i);
                std::cout << i << ") " << p.name().toStdString()
                          << " | $" << p.price()
                          << " | " << p.type().toStdString()
                          << " | " << p.expiry().toString(Qt::ISODate).toStdString()
                          << "\n";
            }
        } else if (opt == 2) {
            std::string n, t;
            double price;
            std::string dateStr;
            std::cout << "Nombre: "; std::cin >> std::ws; std::getline(std::cin, n);
            std::cout << "Precio: "; std::cin >> price;
            std::cout << "Tipo: "; std::cin >> std::ws; std::getline(std::cin, t);
            std::cout << "Caducidad (YYYY-MM-DD): "; std::cin >> dateStr;
            QDate date = QDate::fromString(QString::fromStdString(dateStr), Qt::ISODate);
            Product p(QString::fromStdString(n), price, QString::fromStdString(t), date);
            s.addProduct(p);
            std::cout << "Añadido.\n";
        } else if (opt == 3) {
            int idx; std::cout << "Índice a eliminar: "; std::cin >> idx;
            s.removeProductAt(idx);
            std::cout << "Eliminado (si existía).\n";
        } else if (opt == 4) {
            s.saveToFile(path);
            std::cout << "Guardado. Saliendo...\n";
            break;
        } else {
            std::cout << "Opción inválida\n";
        }
    }
    return 0;
}
