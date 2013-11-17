#include "mainwindow.h"

#include <qmessagebox.h>
//----------------------------------------------------------------------------
MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

}
//----------------------------------------------------------------------------
MainWindow::~MainWindow()
{

}
//----------------------------------------------------------------------------
//-------------------SIGNAL_SLOTS_ACTIONS-------------------------------------
void MainWindow::on_imgAcqMethodSelector_currentIndexChanged(int index){
	if(index == 0){
		toggleImageAcquisitionLayout(true);
	}else if (index == 1 || index == 2){
		toggleImageAcquisitionLayout(false);
	}
}

//---------------------------------------------------------------------------
void MainWindow::on_posAcqMethodSelector_currentIndexChanged(int index){
	if(index == 0){
		ui.posAcqMethodEditText->setEnabled(true);
	}else if (index == 1){
		ui.posAcqMethodEditText->setEnabled(false);
	}
}

//---------------------------------------------------------------------------
void MainWindow::on_posReconAlgorithmSelector_currentIndexChanged(int index){

}

//---------------------------------------------------------------------------
void MainWindow::on_segMethodSelector_currentIndexChanged(int index){

}

//----------------------------------------------------------------------------
void MainWindow::on_startButton_clicked(){
	QMessageBox::information(this, "GOOOOO", "GOOOOO");
}

//----------------------------------------------------------------------------
void MainWindow::on_testDevicesButton_clicked(){
	QMessageBox::information(this, "TestDevices", "testing");
}

//----------------------------------------------------------------------------
//--------------------INTERNAL FUNCTIONS--------------------------------------
void MainWindow::toggleImageAcquisitionLayout(bool show){
	ui.imgAcqMethodEditText->setEnabled(!show);
	ui.rB1Device->setEnabled(show);
	ui.rB2Devices->setEnabled(show);
	ui.label1Device->setEnabled(show);
	ui.label2Devices->setEnabled(show);
	ui.spin1Device->setEnabled(show);
	ui.spin2Devices->setEnabled(show);
}
//----------------------------------------------------------------------------