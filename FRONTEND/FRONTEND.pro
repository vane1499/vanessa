QT += core gui

CONFIG += c++17 console
CONFIG -= app_bundle

TEMPLATE = app

# Carpeta de código fuente
SOURCES += \
    src/main.cpp \
    src/console.cpp \
    src/mainwindow.cpp \
    src/product.cpp \
    src/store.cpp \
    src/utils.cpp

# Carpeta de headers
HEADERS += \
    include/mainwindow.h \
    include/product.h \
    include/store.h \
    include/utils.h

# Interfaz
FORMS += \
    ui/mainwindow.ui

# Especificar rutas de include adicionales
INCLUDEPATH += include
