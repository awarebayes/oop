#include "inc/mainwindow.h"

#include <QApplication>
#include "inc/domain.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
