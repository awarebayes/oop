#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <optional>
#include "renderer.h"
#include "controller.h"

QT_BEGIN_NAMESPACE
namespace Ui
{
	class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
Q_OBJECT

public:
	explicit MainWindow(QWidget *parent);

	~MainWindow() override;

	void connect_controller(Controller &controller);

	void connect_model(Model &model);

	void rerender();

	void transform_changed(Transformations transforms);

	void object_changed(const Mesh3D &object);

private slots:

	void on_TransX_valueChanged(double arg1);

	void on_TransY_valueChanged(double arg1);

	void on_TransZ_valueChanged(double arg1);

	void on_RotX_valueChanged(double arg1);

	void on_RotY_valueChanged(double arg1);

	void on_RotZ_valueChanged(double arg1);

	void on_ScaleX_valueChanged(double arg1);

	void on_ScaleY_valueChanged(double arg1);

	void on_ScaleZ_valueChanged(double arg1);

	void on_actionOpen_triggered();

	void on_actionExit_triggered();

	void on_actionDefault_Scale_triggered();

	void on_actionSave_triggered();

private:
	Ui::MainWindow *ui;
	std::optional<Renderer> renderer_;
	std::optional<std::reference_wrapper<struct Controller>> controller_;
};

#endif // MAINWINDOW_H
