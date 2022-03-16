#include <QFileDialog>
#include "inc/mainwindow.h"
#include "./ui_mainwindow.h"
#include "inc/config.h"
#include "inc/domain.h"

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

	reset_view();
	rerender();
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
				.type = transform_type::Translate,
		};
	res.scale = {
				.x = ui->ScaleX->value(),
				.y = ui->ScaleY->value(),
				.z = ui->ScaleZ->value(),
				.type = transform_type::Scale,
	};
	res.rotate = {
				.x = ui->RotX->value(),
				.y = ui->RotY->value(),
				.z = ui->RotZ->value(),
				.type = transform_type::Rotate,
	};
	return res;
}

void MainWindow::rerender()
{
	command com{};
	strcpy(com.obj_path.buf, "NONE");
	com.scene = scene;
	com.type = command_type::draw_object;
	com.transforms = get_transformations();
	entry_point(com);
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

void MainWindow::set_transforms(const transformations &transforms)
{
	ui->RotX->setValue(transforms.rotate.x);
	ui->RotY->setValue(transforms.rotate.y);
	ui->RotZ->setValue(transforms.rotate.z);

	ui->TransX->setValue(transforms.translate.x);
	ui->TransY->setValue(transforms.translate.y);
	ui->TransZ->setValue(transforms.translate.z);

	ui->ScaleX->setValue(transforms.scale.x);
	ui->ScaleY->setValue(transforms.scale.y);
	ui->ScaleZ->setValue(transforms.scale.z);
}

void MainWindow::on_actionOpen_triggered()
{
	QString filename = QFileDialog::getOpenFileName(nullptr, "Open .obj file", "./", "Obj file (*.obj)");
	if (filename.isEmpty())
		return;
	load_object(filename.toStdString());
	reset_view();
	rerender();
}


void MainWindow::on_actionExit_triggered() {}


void MainWindow::on_actionDefault_Scale_triggered()
{
	reset_view();
	rerender();
}

void MainWindow::on_actionSave_triggered()
{
	QString filename = QFileDialog::getSaveFileName(nullptr, "Open .obj file", "./", "Obj file (*.obj)");
	if (filename.isEmpty())
		return;

	load_object(filename.toStdString());
	rerender();
}

void MainWindow::reset_view()
{
	command com = {.type = command_type::default_view};
	entry_point(com);
	transformations transforms;
	reset_transforms(transforms);
	this->set_transforms(transforms);
}

void MainWindow::load_object(const std::string &path)
{
	command com = {};
	strcpy(com.obj_path.buf, path.c_str());
	com.scene = scene;
	com.type = command_type::load_object;
	entry_point(com);
}

void MainWindow::save_object(const std::string& filename)
{
	command com = {.scene=scene, .type = command_type::save_object};
	strcpy(com.obj_path.buf, filename.c_str());
	entry_point(com);
}
