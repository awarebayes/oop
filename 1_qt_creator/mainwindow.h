#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "renderer.h"
#include "state.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent);
    ~MainWindow() override;

	void rerender();
	void updateState();
	void updateSliders();

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

private:
    Ui::MainWindow *ui;
	State state;
	Renderer renderer;
	;
};
#endif // MAINWINDOW_H
