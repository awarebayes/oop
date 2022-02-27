#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "config.h"
#include "obj_reader.h"
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
	ui = new Ui::MainWindow;
	ui->setupUi(this);

	ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	ui->graphicsView->setFixedSize(SCREEN_WIDTH, SCREEN_HEIGHT);

	renderer = { SCREEN_WIDTH, SCREEN_HEIGHT, *this};
	ui->graphicsView->setScene(renderer.scene);
	state.transform = state.current_object.get_appropriate_transformations();
	updateSliders();
	rerender();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_TransX_valueChanged(double arg1)
{
	state.transform.translate.x = arg1;
	rerender();
}

void MainWindow::on_TransY_valueChanged(double arg1)
{
	state.transform.translate.y = arg1;
	rerender();
}


void MainWindow::on_TransZ_valueChanged(double arg1)
{
	state.transform.translate.z = arg1;
	rerender();
}


void MainWindow::on_RotX_valueChanged(double arg1)
{
	state.transform.rotate.x = arg1;
	rerender();
}


void MainWindow::on_RotY_valueChanged(double arg1)
{
	state.transform.rotate.y = arg1;
	rerender();
}


void MainWindow::on_RotZ_valueChanged(double arg1)
{
	state.transform.rotate.z = arg1;
	rerender();
}


void MainWindow::on_ScaleX_valueChanged(double arg1)
{
	state.transform.scale.x = arg1;
	rerender();
}


void MainWindow::on_ScaleY_valueChanged(double arg1)
{
	state.transform.scale.y = arg1;
	rerender();
}


void MainWindow::on_ScaleZ_valueChanged(double arg1)
{
	state.transform.scale.z = arg1;
	rerender();
}

void MainWindow::rerender()
{
	renderer.draw_object(state.current_object, state.get_transformation_matrix());
}

void MainWindow::updateSliders()
{
	ui->TransX->setValue(state.transform.translate.x);
	ui->TransY->setValue(state.transform.translate.y);
	ui->TransZ->setValue(state.transform.translate.z);

	ui->ScaleX->setValue(state.transform.scale.x);
	ui->ScaleY->setValue(state.transform.scale.y);
	ui->ScaleZ->setValue(state.transform.scale.z);

	ui->RotX->setValue(state.transform.rotate.x);
	ui->RotY->setValue(state.transform.rotate.y);
	ui->RotZ->setValue(state.transform.rotate.z);
}

void MainWindow::on_actionOpen_triggered()
{
	QString filename = QFileDialog::getOpenFileName(this, "Open .obj file", "./", "Obj file (*.obj)");
	Mesh3D new_mesh = read_obj_file(filename.toStdString());
	state.current_object = new_mesh;
	state.transform = state.current_object.get_appropriate_transformations();
	updateSliders();
	rerender();
}


void MainWindow::on_actionExit_triggered()
{
}


void MainWindow::on_actionDefault_Scale_triggered()
{
	state.transform = state.current_object.get_appropriate_transformations();
	updateSliders();
	rerender();
}

