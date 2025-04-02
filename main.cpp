#include <QApplication>
#include "src/graphics/MainWindow.h"
#include <QDebug>




int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    MainWindow mainWindow;
    mainWindow.show();

    return app.exec();
}