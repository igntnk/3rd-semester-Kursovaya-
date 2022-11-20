#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    PixWork window;
    window.setWindowTitle("Saturation checker");
    window.show();
    return a.exec();
}
