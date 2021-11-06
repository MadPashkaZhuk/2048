#include "mainwindow.h"
#include <QApplication>
#include "board.h"
#include <QIcon>

int main(int argc, char *argv[])
{
    srand(time(NULL));
    QApplication a(argc, argv);
    MainWindow window;
    window.show();
    return a.exec();
}
