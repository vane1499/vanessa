#include <QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[]) {
    if (argc > 1 && std::string(argv[1]) == "--console") {
        runConsole();  // función en console.cpp
        return 0;
    }

    QApplication app(argc, argv);
    MainWindow w;
    w.show();
    return app.exec();
}
