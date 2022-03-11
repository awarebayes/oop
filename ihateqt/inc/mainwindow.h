#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include "transformations.h"
#include "obj3d.h"

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
	MainWindow(QWidget *parent = nullptr);

	~MainWindow();

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

private:
	Ui::MainWindow *ui;
	QGraphicsScene *scene;
	transformations get_transformations();
	void rerender();
	void set_transforms(const transformations &transforms);
	bool just_initialized = true;
	obj3d object;
};

#endif // MAINWINDOW_H
