/*
 * MainWindow.cpp
 *
 *  Created on: Nov 6, 2013
 *      Author: pablo
 */

#include "MainWindow.h"

namespace UI {

MainWindow::MainWindow() :
		m_VBox_Main(Gtk::ORIENTATION_VERTICAL), m_Frame_Title(), m_Frame_Algorithm(
				"Algorithm Selector"), m_Frame_ImgAc("Image Acquisition"), m_Frame_IO(
				"Input & Output"), m_Button_Start("  START  "), m_Box_Algorithm(), m_Box_IO(), m_Box_ImgAcq(), m_Box_Title() {

	// Basic Configuration.
	set_title("Visual Tracking UI");

	set_border_width(10);

	// Adding main vertical container.
	add(m_VBox_Main);

	//Adding Title Frame.
	m_VBox_Main.pack_start(m_Frame_Title, Gtk::PACK_EXPAND_WIDGET, 10);

	m_Frame_Title.add(m_Box_Title);

	//Adding Title Frame.
	m_VBox_Main.pack_start(m_Frame_Algorithm, Gtk::PACK_EXPAND_WIDGET, 10);

	m_Frame_Algorithm.add(m_Box_Algorithm);

	//Adding Title Frame.
	m_VBox_Main.pack_start(m_Frame_ImgAc, Gtk::PACK_EXPAND_WIDGET, 10);

	m_Frame_ImgAc.add(m_Box_ImgAcq);

	//Adding Title Frame.
	m_VBox_Main.pack_start(m_Frame_IO, Gtk::PACK_EXPAND_WIDGET, 10);

	m_Frame_IO.add(m_Box_IO);

	//Adding start button.
	m_VBox_Main.pack_start(m_Button_Start, Gtk::PACK_EXPAND_WIDGET, 10);

	show_all_children();

}

MainWindow::~MainWindow() {
}

} /* namespace UI */
