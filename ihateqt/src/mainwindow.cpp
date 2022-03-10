#include "inc/mainwindow.h"
#include "./ui_mainwindow.h"
#include "inc/config.h"
#include "inc/domain.h"
#include "inc/state.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

	ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	ui->graphicsView->setFixedSize(SCREEN_WIDTH, SCREEN_HEIGHT);

	scene = new QGraphicsScene(0, 0, SCREEN_WIDTH-2, SCREEN_HEIGHT-2, parent);
	scene->addRect(scene->sceneRect());
	ui->graphicsView->setScene(scene);
}

MainWindow::~MainWindow()
{
    delete ui;
}

transformations MainWindow::get_transformations()
{
	transformations res;
	res.translate = {
				.x = ui->TransX->value(),
				.y = ui->TransY->value(),
				.z = ui->TransZ->value(),
		};
	res.scale = {
				.x = ui->ScaleX->value(),
				.y = ui->ScaleY->value(),
				.z = ui->ScaleZ->value(),
		};
	res.rotate = {
				.x = ui->RotX->value(),
				.y = ui->RotY->value(),
				.z = ui->RotZ->value(),
		};
	return res;
}

void MainWindow::rerender()
{
	state s = {};
	s.obj_path = "none";
    s.transforms = get_transformations();
	s.object = object;
	s.scene = scene;
	s.just_initialized = just_initialized;
	entry_point(command_type::draw_object, s);
}



void MainWindow::on_TransX_valueChanged(double arg1)
{
	rerender();
}


void MainWindow::on_TransY_valueChanged(double arg1)
{

	rerender();
}


void MainWindow::on_TransZ_valueChanged(double arg1)
{

	rerender();
}


void MainWindow::on_RotX_valueChanged(double arg1)
{

	rerender();
}


void MainWindow::on_RotY_valueChanged(double arg1)
{

	rerender();
}


void MainWindow::on_RotZ_valueChanged(double arg1)
{

	rerender();
}


void MainWindow::on_ScaleX_valueChanged(double arg1)
{

	rerender();
}


void MainWindow::on_ScaleY_valueChanged(double arg1)
{

	rerender();
}


void MainWindow::on_ScaleZ_valueChanged(double arg1)
{

	rerender();
}

