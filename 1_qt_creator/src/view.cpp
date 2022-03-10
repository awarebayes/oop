#include "inc/view.h"
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

	renderer_ = std::optional<Renderer>{{ SCREEN_WIDTH, SCREEN_HEIGHT, *this }};
	ui->graphicsView->setScene(renderer_.value().scene.get());
}

MainWindow::~MainWindow()
{
	delete ui;
}


void MainWindow::on_TransX_valueChanged(double arg1)
{
	auto controller = controller_.value().get();
	TransformMutation mut = {TransformType::Translate, Axis::X, arg1};
	ControllerCommand command = {
			.args = {.transform_mutation=mut},
			.type = ControllerCommandType::mutate_transformations,
	};
	entry_point(controller, command);
}

void MainWindow::on_TransY_valueChanged(double arg1)
{
	auto controller = controller_.value().get();

	TransformMutation mut = {TransformType::Translate, Axis::Y, arg1};
	ControllerCommand command = {
			.args = {.transform_mutation=mut},
			.type = ControllerCommandType::mutate_transformations,
	};
	entry_point(controller, command);
}


void MainWindow::on_TransZ_valueChanged(double arg1)
{
	auto controller = controller_.value().get();

	TransformMutation mut = {TransformType::Translate, Axis::Z, arg1};
	ControllerCommand command = {
			.args = {.transform_mutation=mut},
			.type = ControllerCommandType::mutate_transformations,
	};
	entry_point(controller, command);
}


void MainWindow::on_RotX_valueChanged(double arg1)
{
	auto controller = controller_.value().get();

	TransformMutation mut = {TransformType::Rotate, Axis::X, arg1};
	ControllerCommand command = {
			.args = {.transform_mutation=mut},
			.type = ControllerCommandType::mutate_transformations,
	};
	entry_point(controller, command);
}


void MainWindow::on_RotY_valueChanged(double arg1)
{
	auto controller = controller_.value().get();
	TransformMutation mut = {TransformType::Rotate, Axis::Y, arg1};
	ControllerCommand command = {
			.args = {.transform_mutation=mut},
			.type = ControllerCommandType::mutate_transformations,
	};
	entry_point(controller, command);
}


void MainWindow::on_RotZ_valueChanged(double arg1)
{
	auto controller = controller_.value().get();
	TransformMutation mut = {TransformType::Rotate, Axis::Z, arg1};
	ControllerCommand command = {
			.args = {.transform_mutation=mut},
			.type = ControllerCommandType::mutate_transformations,
	};
	entry_point(controller, command);
}


void MainWindow::on_ScaleX_valueChanged(double arg1)
{
	auto controller = controller_.value().get();

	TransformMutation mut = {TransformType::Scale, Axis::X, arg1};
	ControllerCommand command = {
			.args = {.transform_mutation=mut},
			.type = ControllerCommandType::mutate_transformations,
	};
	entry_point(controller, command);
}


void MainWindow::on_ScaleY_valueChanged(double arg1)
{
	auto controller = controller_.value().get();

	TransformMutation mut = {TransformType::Scale, Axis::Y, arg1};
	ControllerCommand command = {
			.args = {.transform_mutation=mut},
			.type = ControllerCommandType::mutate_transformations,
	};
	entry_point(controller, command);
}


void MainWindow::on_ScaleZ_valueChanged(double arg1)
{
	auto controller = controller_.value().get();

	TransformMutation mut = {TransformType::Scale, Axis::Z, arg1};
	ControllerCommand command = {
			.args = {.transform_mutation=mut},
			.type = ControllerCommandType::mutate_transformations,
	};
	entry_point(controller, command);
}

void MainWindow::on_actionOpen_triggered()
{
	auto controller = controller_.value().get();

	ControllerCommand command = {
			.type = ControllerCommandType::load_object,
	};
	entry_point(controller, command);
}


void MainWindow::on_actionExit_triggered()
{
	auto controller = controller_.value().get();
	ControllerCommand command = {
			.type = ControllerCommandType::exit,
	};
	entry_point(controller, command);
}


void MainWindow::on_actionDefault_Scale_triggered()
{
	auto controller = controller_.value().get();
	ControllerCommand command = {
			.type = ControllerCommandType::default_view,
	};
	entry_point(controller, command);
}

void MainWindow::on_actionSave_triggered()
{
	auto controller = controller_.value().get();
	ControllerCommand command = {
			.type = ControllerCommandType::save_object,
	};
	entry_point(controller, command);
}

void MainWindow::connect_controller(Controller &controller)
{
	this->controller_ = std::optional<std::reference_wrapper<Controller>>{ controller };
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

void MainWindow::object_changed(const Mesh3D &object)
{
	rerender();
}

void MainWindow::rerender()
{
	auto controller = controller_.value().get();
	const Mesh3D &object = controller.get_current_object();
	const Transformations &transform = controller.get_transformations();

	auto maybe_error = renderer_.value().draw_object(object, transform);
	if (maybe_error.has_error())
		Controller::show_error_dialog(maybe_error.error());
}

void MainWindow::connect_model(Model &model)
{
	model.transform.connect(
			[this](const Transformations &new_transform) { this->transform_changed(new_transform); }
	);
	model.current_object.connect(
			[this](const Mesh3D &object) { this->object_changed(object); }
	);
}


