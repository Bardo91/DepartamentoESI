/*
 * MainWindow.h
 *
 *  Created on: Nov 6, 2013
 *      Author: pablo
 */

#ifndef _VISIONTRACKINGUI_MAINWINDOW_H_
#define _VISIONTRACKINGUI_MAINWINDOW_H_

#include <gtkmm.h>
#include <gtkmm/box.h>

#include "BoxAlgorithm.h"
#include "BoxIO.h"
#include "BoxImgAcq.h"
#include "BoxTitle.h"

namespace UI {

class MainWindow: public Gtk::Window {
public:
	MainWindow();
	virtual ~MainWindow();

protected:
	// Signal Handlers

	// Members & widgets
	Gtk::Box m_VBox_Main;
	Gtk::Frame m_Frame_Title, m_Frame_Algorithm, m_Frame_ImgAc, m_Frame_IO;
	Gtk::Button m_Button_Start;
	BoxAlgorithm m_Box_Algorithm;
	BoxIO m_Box_IO;
	BoxImgAcq m_Box_ImgAcq;
	BoxTitle m_Box_Title;
};

} /* namespace UI */

#endif /* _VISIONTRACKINGUI_MAINWINDOW_H_ */
