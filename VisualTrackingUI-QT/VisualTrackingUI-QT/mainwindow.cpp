////////////////////////////////////////////////////////////////////////////////
//	Visual Tracking UI
//		Author: Pablo Ramón Soria
//		Date: 2013/10/31
////////////////////////////////////////////////////////////////////////////////
// MainWindow


#include "mainwindow.h"
#include "ThreadManager.h"

#include <qmessagebox.h>

using namespace vision;
using namespace std;
//----------------------------------------------------------------------------
MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	threadManager = new ThreadManager(this);
}
//----------------------------------------------------------------------------
MainWindow::~MainWindow()
{
	delete threadManager;

}

//----------------------------------------------------------------------------
void MainWindow::setUpThread(MainWindow mainWindow){

}

//----------------------------------------------------------------------------
//----------------------Acquire mainwindow widgets information----------------

int MainWindow::getImgAcqMethod(){
	return ui.imgAcqMethodSelector->currentIndex();
}

//----------------------------------------------------------------------------
int MainWindow::getNumberDevices(){
	return ui.rB1Device->isChecked() ? 1 : 2;
}

//----------------------------------------------------------------------------
int MainWindow::getIdDevice1(){
	return ui.spin1Device->value();
}

//----------------------------------------------------------------------------
int MainWindow::getIdDevice2(){
	return ui.spin2Devices->value();
}

//----------------------------------------------------------------------------
string MainWindow::getImagesPath(){
	return ui.imgAcqMethodPathEditText->toPlainText().toStdString();
}

//----------------------------------------------------------------------------
string MainWindow::getImageNameFormat(){
	return ui.imgAcqMethodFileNameEditText->toPlainText().toStdString();
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
//	threadManager->setUpThread();

	threadManager->startThread();
}

//----------------------------------------------------------------------------
void MainWindow::on_testDevicesButton_clicked(){
	QMessageBox::information(this, "TestDevices", "testing");
}

//----------------------------------------------------------------------------
//--------------------INTERNAL FUNCTIONS--------------------------------------
void MainWindow::toggleImageAcquisitionLayout(bool show){
	ui.imgAcqMethodPathEditText->setEnabled(!show);
	ui.imgAcqMethodFileNameEditText->setEnabled(!show);
	ui.rB1Device->setEnabled(show);
	ui.rB2Devices->setEnabled(show);
	ui.label1Device->setEnabled(show);
	ui.label2Devices->setEnabled(show);
	ui.spin1Device->setEnabled(show);
	ui.spin2Devices->setEnabled(show);
}
//----------------------------------------------------------------------------