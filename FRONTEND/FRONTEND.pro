TEMPLATE = app
TARGET = FRONTEND

CONFIG += console c++17
QT += core

# Carpeta con headers y fuentes
INCLUDEPATH += src

HEADERS += \
    src/mainwindow.h \
    src/product.h \
    src/store.h \
    src/utils.h

SOURCES += \
    src/main.cpp \
    src/console.cpp \
    src/mainwindow.cpp \
    src/product.cpp \
    src/store.cpp \
    src/utils.cpp
