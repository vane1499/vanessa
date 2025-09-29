#pragma once
#include <QString>
#include <QDate>

class Product {
public:
    Product() = default;
    Product(const QString& name, double price, const QString& type, const QDate& expiry, const QString& imagePath = QString());

    QString name() const;
    double price() const;
    QString type() const;
    QDate expiry() const;
    QString imagePath() const;

    QString serialize() const;            // formato para guardar en txt
    static Product deserialize(const QString& line); // parsea una línea

private:
    QString m_name;
    double m_price = 0.0;
    QString m_type;
    QDate m_expiry;
    QString m_imagePath;
};
