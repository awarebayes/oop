#include "mainwindow.h"

#include <QApplication>
#include <gtest/gtest.h>
#include "tests/main_test.h"

 int main(int argc, char **argv)
 {
 	testing::InitGoogleTest(&argc, argv);
 	return RUN_ALL_TESTS();
 }

// int main(int argc, char *argv[])
// {
// 	QApplication a(argc, argv);
// 	MainWindow w;
// 	w.show();
// 	return a.exec();
// }