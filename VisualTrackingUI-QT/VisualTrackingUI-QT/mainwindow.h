#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets/QMainWindow>
#include "ui_mainwindow.h"

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = 0);
	~MainWindow();

private slots:
	// Combo Box Slots
	void on_imgAcqMethodSelector_currentIndexChanged(int index);
	void on_segMethodSelector_currentIndexChanged(int index);
	void on_posAcqMethodSelector_currentIndexChanged(int index);
	void on_posReconAlgorithmSelector_currentIndexChanged(int index);

	// Button Slots:
	void on_testDevicesButton_clicked();
	void on_startButton_clicked();


private: // private actions to control UI
	void toggleImageAcquisitionLayout(bool enable); // if true device else path.

private:
	Ui::MainWindowClass ui;
};

#endif // MAINWINDOW_H
