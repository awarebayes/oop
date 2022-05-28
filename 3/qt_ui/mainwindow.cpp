#include <iostream>
#include <QShortcut>
#include <drawer/inc/qt_canvas_factory.h>
#include <manager/inc/draw_manager.h>
#include <drawer/inc/canvas_solution.h>
#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
	int screen_width = ui->graphicsView->width();
	int screen_height = ui->graphicsView->height();
	scene = std::make_shared<QGraphicsScene>(0, 0, screen_width - 2, screen_height - 2, parent);
	scene->addRect(scene->sceneRect());
	ui->graphicsView->setScene(scene.get());

	std::shared_ptr<ICanvas> canvas =  CanvasSolution::create(CanvasType::QtCanvas, scene);

	auto draw_manager = DrawManagerCreator().get();
	draw_manager->set_canvas(canvas);
	interactor = std::make_unique<Interactor>([this](const std::string &status){this->set_status(status);});;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionLoadModel_triggered()
{
    std::cout << "Hello world" << std::endl;
}

void MainWindow::on_actionSelect_triggered()
{
	std::cout << "Hello world" << std::endl;
}

void MainWindow::on_actionView_Objects_triggered()
{

}

void MainWindow::keyPressEvent(QKeyEvent *e)
{
	int key = e->key();
	interactor->handle_key(key);
}

void MainWindow::set_status(const std::string &status)
{
	ui->feedback_thingy->setText(QString::fromUtf8(status.c_str()));
}

void MainWindow::on_line_edit_returnPressed()
{
	interactor->handle_command(ui->line_edit->text().toStdString());
}

