#include "inc/mainwindow.h"

#include <QApplication>
#include <inc/controller.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

	MainWindow view(nullptr);
	Model model;
	Controller controller(model, view);

	model.connect_view(view);
	view.connect_controller(controller);

    view.show();
    return a.exec();
}
