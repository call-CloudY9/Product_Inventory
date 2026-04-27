#include <QApplication>
#include "../include/MainWindow.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    MainWindow window;
    window.setWindowTitle("Учёт инвентаря продуктов");
    window.resize(600, 400);
    window.show();

    return app.exec();
}