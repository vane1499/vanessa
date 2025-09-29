#include "store.h"
#include <QFile>
#include <QTextStream>

bool Store::loadFromFile(const QString& path) {
    m_products.clear();
    QFile f(path);
    if (!f.exists()) return false;
    if (!f.open(QIODevice::ReadOnly | QIODevice::Text)) return false;
    QTextStream in(&f);
    while (!in.atEnd()) {
        QString line = in.readLine().trimmed();
        if (line.isEmpty()) continue;
        m_products.push_back(Product::deserialize(line));
    }
    f.close();
    return true;
}

bool Store::saveToFile(const QString& path) const {
    QFile f(path);
    if (!f.open(QIODevice::WriteOnly | QIODevice::Text)) return false;
    QTextStream out(&f);
    for (const auto& p : m_products) {
        out << p.serialize() << '\n';
    }
    f.close();
    return true;
}

void Store::addProduct(const Product& p) {
    m_products.push_back(p);
}

void Store::removeProductAt(int index) {
    if (index >= 0 && index < static_cast<int>(m_products.size())) {
        m_products.erase(m_products.begin() + index);
    }
}

const std::vector<Product>& Store::products() const {
    return m_products;
}

std::vector<Product> Store::filteredByType(const QString& type) const {
    if (type.isEmpty() || type == "Todos") {
        return m_products;
    }
    std::vector<Product> out;
    for (const auto& p : m_products) {
        if (p.type().compare(type, Qt::CaseInsensitive) == 0) out.push_back(p);
    }
    return out;
}
