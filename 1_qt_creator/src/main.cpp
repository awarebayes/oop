#include "inc/view.h"

#include <QApplication>
#include <inc/controller.h>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	MainWindow view(nullptr);
	Model model;
	Controller controller(model);

	view.connect_controller(controller);
	view.connect_model(model);
	controller.load_default_cube();

	view.show();
	view.rerender();
	return a.exec();
}
