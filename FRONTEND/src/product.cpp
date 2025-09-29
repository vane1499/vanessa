#include "product.h"
#include <QStringList>

Product::Product(const QString& name, double price, const QString& type, const QDate& expiry, const QString& imagePath)
    : m_name(name), m_price(price), m_type(type), m_expiry(expiry), m_imagePath(imagePath)
{}

QString Product::name() const { return m_name; }
double Product::price() const { return m_price; }
QString Product::type() const { return m_type; }
QDate Product::expiry() const { return m_expiry; }
QString Product::imagePath() const { return m_imagePath; }

// Serializamos como: nombre|precio|tipo|YYYY-MM-DD|imagePath
QString Product::serialize() const {
    QStringList parts;
    parts << m_name
          << QString::number(m_price, 'f', 2)
          << m_type
          << m_expiry.toString(Qt::ISODate)
          << m_imagePath;
    return parts.join('|');
}

Product Product::deserialize(const QString& line) {
    QStringList parts = line.split('|');
    QString name = parts.value(0);
    double price = parts.value(1).toDouble();
    QString type = parts.value(2);
    QDate expiry = QDate::fromString(parts.value(3), Qt::ISODate);
    QString imagePath = parts.value(4);
    return Product(name, price, type, expiry, imagePath);
}
