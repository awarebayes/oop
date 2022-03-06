#include "inc/mainwindow.h"
#include "./ui_mainwindow.h"
#include "inc/config.h"
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
	rerender();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_TransX_valueChanged(double arg1)
{
	controller_->mutate_transformations(TransformType::Translate, Axis::X, arg1);
}

void MainWindow::on_TransY_valueChanged(double arg1)
{
	controller_->mutate_transformations(TransformType::Translate, Axis::Y, arg1);
}


void MainWindow::on_TransZ_valueChanged(double arg1)
{
	controller_->mutate_transformations(TransformType::Translate, Axis::Z, arg1);
}


void MainWindow::on_RotX_valueChanged(double arg1)
{
	controller_->mutate_transformations(TransformType::Rotate, Axis::X, arg1);
}


void MainWindow::on_RotY_valueChanged(double arg1)
{
	controller_->mutate_transformations(TransformType::Rotate, Axis::Y, arg1);
}


void MainWindow::on_RotZ_valueChanged(double arg1)
{
	controller_->mutate_transformations(TransformType::Rotate, Axis::Z, arg1);
}


void MainWindow::on_ScaleX_valueChanged(double arg1)
{
	controller_->mutate_transformations(TransformType::Scale, Axis::X, arg1);
}


void MainWindow::on_ScaleY_valueChanged(double arg1)
{
	controller_->mutate_transformations(TransformType::Scale, Axis::Y, arg1);
}


void MainWindow::on_ScaleZ_valueChanged(double arg1)
{
	controller_->mutate_transformations(TransformType::Scale, Axis::Z, arg1);
}

void MainWindow::on_actionOpen_triggered()
{
	controller_->load_object();
}


void MainWindow::on_actionExit_triggered()
{
	exit(0);
}


void MainWindow::on_actionDefault_Scale_triggered()
{
	controller_->apply_appropriate_transformations();
}

void MainWindow::connect_controller(Controller &controller)
{
	this->controller_ = &controller;
}

void MainWindow::transform_changed(Transformations transforms)
{
	ui->TransX->setValue(transforms.translate.x);
	ui->TransY->setValue(transforms.translate.y);
	ui->TransZ->setValue(transforms.translate.z);

	ui->ScaleX->setValue(transforms.scale.x);
	ui->ScaleY->setValue(transforms.scale.y);
	ui->ScaleZ->setValue(transforms.scale.z);

	ui->RotX->setValue(transforms.rotate.x);
	ui->RotY->setValue(transforms.rotate.y);
	ui->RotZ->setValue(transforms.rotate.z);
	rerender();
}

void MainWindow::rerender()
{
	const Mesh3D &object = controller_->get_current_object();
	const Mat4x4 trans_matrix = controller_->get_transformation_matrix();
	renderer.draw_object(object, trans_matrix);
}

void MainWindow::object_changed(const Mesh3D &object)
{
	rerender();
}



