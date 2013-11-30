////////////////////////////////////////////////////////////////////////////////
//	Visual Tracking UI
//		Author: Pablo Ram�n Soria
//		Date: 2013/10/31
////////////////////////////////////////////////////////////////////////////////
// MainWindow


#ifndef _VISUAL_TRACKING_UI_MAINWINDOW_H
#define _VISUAL_TRACKING_UI_MAINWINDOW_H

#include <QtWidgets/QMainWindow>
#include "ui_mainwindow.h"

#include "ThreadManager.h"

#include <string>

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = 0);
	~MainWindow();

public: // Functions assiciated to ThreadManager class.
	void setUpThread(MainWindow mainWindow);

public: // Functions to adquire mainwindow widgets information.
	// Functions related to Image acquisitior method
	int getImgAcqMethod();
	int getNumberDevices();
	int getWidth();
	int getHeight();	
	int getIdDevice1();
	int getIdDevice2();
	std::string getImagesPath();
	std::string getImageNameFormat1();
	std::string getImageNameFormat2();

	// Functions related to Segmentation algorithm
	int getSegmentationAlgorithm();
	int getThreshold(); // 666 TODO: add threshold to segmentation algorithms and change UI putting edittext next to segmentation algorthm selector

	// Functions related to Position acquisition
	int getPositionAcquisitionMethod();
	std::string getCameraInfoPath();
	std::string getCameraPositionPath();
	bool getIsFixedCameras();

	// Functions related to Tracking filters
	int getTrackingAlgorithm();


private slots:
	// Combo Box Slots
	void on_imgAcqMethodSelector_currentIndexChanged(int index);
	void on_segMethodSelector_currentIndexChanged(int index);
	void on_posAcqMethodSelector_currentIndexChanged(int index);
	void on_posReconAlgorithmSelector_currentIndexChanged(int index);

	// Button Slots:
	void on_testDevicesButton_clicked();
	void on_startButton_clicked();
	void on_stopButton_clicked();

private: // private actions to control UI
	void toggleImageAcquisitionLayout(bool enable); // if true device else path.

private:
	Ui::MainWindowClass ui;

	vision::ThreadManager threadManager;

	vision::InfoCollector *infoCollector;
};



#endif // _VISUAL_TRACKING_UI_MAINWINDOW_H
