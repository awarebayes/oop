#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <command/facade.h>
#include <QGraphicsScene>
#include <QKeyEvent>
#include "scene_meta.h"
#include "vim.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
	std::unique_ptr<Vim> vim;
    Ui::MainWindow *ui;
	QGraphicsScene *scene;
	void set_status(const std::string &status);

protected:
	void keyPressEvent(QKeyEvent *event) override;

public slots:
	void on_actionLoadModel_triggered();
	void on_actionSelect_triggered();
	void on_actionView_Objects_triggered();
	void on_line_edit_returnPressed();
};
#endif // MAINWINDOW_H
