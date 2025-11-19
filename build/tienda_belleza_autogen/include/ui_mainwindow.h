/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.5.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QDate>
#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout;
    QFrame *frameForm;
    QVBoxLayout *verticalLayoutForm;
    QLabel *labelTitle;
    QFormLayout *formLayout;
    QLabel *labelName;
    QLineEdit *lineName;
    QLabel *labelPrice;
    QDoubleSpinBox *spinPrice;
    QLabel *labelType;
    QLineEdit *lineType;
    QLabel *labelExpiry;
    QDateEdit *dateExpiry;
    QLabel *labelImage;
    QHBoxLayout *hLayoutImage;
    QLineEdit *lineImage;
    QPushButton *btnSelectImage;
    QHBoxLayout *hButtons;
    QPushButton *btnAdd;
    QPushButton *btnRemove;
    QLabel *lblPreview;
    QVBoxLayout *verticalLayoutRight;
    QHBoxLayout *hFilter;
    QLabel *labelFilter;
    QComboBox *comboFilter;
    QTableWidget *tableProducts;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(920, 560);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        horizontalLayout = new QHBoxLayout(centralwidget);
        horizontalLayout->setObjectName("horizontalLayout");
        frameForm = new QFrame(centralwidget);
        frameForm->setObjectName("frameForm");
        frameForm->setMinimumWidth(320);
        verticalLayoutForm = new QVBoxLayout(frameForm);
        verticalLayoutForm->setObjectName("verticalLayoutForm");
        labelTitle = new QLabel(frameForm);
        labelTitle->setObjectName("labelTitle");
        labelTitle->setAlignment(Qt::AlignCenter);

        verticalLayoutForm->addWidget(labelTitle);

        formLayout = new QFormLayout();
        formLayout->setObjectName("formLayout");
        formLayout->setLabelAlignment(Qt::AlignRight);
        labelName = new QLabel(frameForm);
        labelName->setObjectName("labelName");

        formLayout->setWidget(0, QFormLayout::LabelRole, labelName);

        lineName = new QLineEdit(frameForm);
        lineName->setObjectName("lineName");

        formLayout->setWidget(0, QFormLayout::FieldRole, lineName);

        labelPrice = new QLabel(frameForm);
        labelPrice->setObjectName("labelPrice");

        formLayout->setWidget(1, QFormLayout::LabelRole, labelPrice);

        spinPrice = new QDoubleSpinBox(frameForm);
        spinPrice->setObjectName("spinPrice");
        spinPrice->setMaximum(1000000.000000000000000);
        spinPrice->setDecimals(2);

        formLayout->setWidget(1, QFormLayout::FieldRole, spinPrice);

        labelType = new QLabel(frameForm);
        labelType->setObjectName("labelType");

        formLayout->setWidget(2, QFormLayout::LabelRole, labelType);

        lineType = new QLineEdit(frameForm);
        lineType->setObjectName("lineType");

        formLayout->setWidget(2, QFormLayout::FieldRole, lineType);

        labelExpiry = new QLabel(frameForm);
        labelExpiry->setObjectName("labelExpiry");

        formLayout->setWidget(3, QFormLayout::LabelRole, labelExpiry);

        dateExpiry = new QDateEdit(frameForm);
        dateExpiry->setObjectName("dateExpiry");
        dateExpiry->setCalendarPopup(true);
        dateExpiry->setDate(QDate(0, 0, 0));

        formLayout->setWidget(3, QFormLayout::FieldRole, dateExpiry);

        labelImage = new QLabel(frameForm);
        labelImage->setObjectName("labelImage");

        formLayout->setWidget(4, QFormLayout::LabelRole, labelImage);

        hLayoutImage = new QHBoxLayout();
        hLayoutImage->setObjectName("hLayoutImage");
        lineImage = new QLineEdit(frameForm);
        lineImage->setObjectName("lineImage");

        hLayoutImage->addWidget(lineImage);

        btnSelectImage = new QPushButton(frameForm);
        btnSelectImage->setObjectName("btnSelectImage");

        hLayoutImage->addWidget(btnSelectImage);


        formLayout->setLayout(4, QFormLayout::FieldRole, hLayoutImage);


        verticalLayoutForm->addLayout(formLayout);

        hButtons = new QHBoxLayout();
        hButtons->setObjectName("hButtons");
        btnAdd = new QPushButton(frameForm);
        btnAdd->setObjectName("btnAdd");

        hButtons->addWidget(btnAdd);

        btnRemove = new QPushButton(frameForm);
        btnRemove->setObjectName("btnRemove");
        btnRemove->setEnabled(false);

        hButtons->addWidget(btnRemove);


        verticalLayoutForm->addLayout(hButtons);

        lblPreview = new QLabel(frameForm);
        lblPreview->setObjectName("lblPreview");
        lblPreview->setMinimumHeight(120);
        lblPreview->setFrameShape(QFrame::Box);
        lblPreview->setAlignment(Qt::AlignCenter);

        verticalLayoutForm->addWidget(lblPreview);


        horizontalLayout->addWidget(frameForm);

        verticalLayoutRight = new QVBoxLayout();
        verticalLayoutRight->setObjectName("verticalLayoutRight");
        hFilter = new QHBoxLayout();
        hFilter->setObjectName("hFilter");
        labelFilter = new QLabel(centralwidget);
        labelFilter->setObjectName("labelFilter");

        hFilter->addWidget(labelFilter);

        comboFilter = new QComboBox(centralwidget);
        comboFilter->setObjectName("comboFilter");

        hFilter->addWidget(comboFilter);


        verticalLayoutRight->addLayout(hFilter);

        tableProducts = new QTableWidget(centralwidget);
        tableProducts->setObjectName("tableProducts");

        verticalLayoutRight->addWidget(tableProducts);


        horizontalLayout->addLayout(verticalLayoutRight);

        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Tienda Belleza", nullptr));
        labelTitle->setText(QCoreApplication::translate("MainWindow", "Agregar producto", nullptr));
        labelName->setText(QCoreApplication::translate("MainWindow", "Nombre:", nullptr));
        labelPrice->setText(QCoreApplication::translate("MainWindow", "Precio:", nullptr));
        spinPrice->setPrefix(QCoreApplication::translate("MainWindow", "$", nullptr));
        labelType->setText(QCoreApplication::translate("MainWindow", "Tipo:", nullptr));
        labelExpiry->setText(QCoreApplication::translate("MainWindow", "Caducidad:", nullptr));
        labelImage->setText(QCoreApplication::translate("MainWindow", "Imagen:", nullptr));
        btnSelectImage->setText(QCoreApplication::translate("MainWindow", "...", nullptr));
        btnAdd->setText(QCoreApplication::translate("MainWindow", "Agregar", nullptr));
        btnRemove->setText(QCoreApplication::translate("MainWindow", "Eliminar", nullptr));
        labelFilter->setText(QCoreApplication::translate("MainWindow", "Filtrar por tipo:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
