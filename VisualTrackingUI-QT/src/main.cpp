////////////////////////////////////////////////////////////////////////////////
//	Visual Tracking UI
//		Author: Pablo Ram�n Soria
//		Date: 2013/10/31
////////////////////////////////////////////////////////////////////////////////
// Main function

#include "mainwindow.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	MainWindow w;
	w.show();
	return a.exec();
}
