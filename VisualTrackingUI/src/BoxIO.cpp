/*
 * BoxIO.cpp
 *
 *  Created on: Nov 6, 2013
 *      Author: pablo
 */

#include "BoxIO.h"

namespace UI {

BoxIO::BoxIO() :
		m_Box_rb(Gtk::ORIENTATION_HORIZONTAL, 5), m_Label_PosAcMet(
				"Method of cam position acquisition"), m_Label_OutPath(
				"Output path for cam position"), m_rb_FixedPos("From File"), m_rb_Vicon(
				"Stream with Vicon"), m_InPos_Path(), m_OutPos_Path() {

	this->set_orientation(Gtk::ORIENTATION_VERTICAL);

	// Creating the group of radio buttons
	Gtk::RadioButton::Group group = m_rb_FixedPos.get_group();
	m_rb_Vicon.set_group(group);

	// Adding widgets to the box
	this->pack_start(m_Label_PosAcMet);

	this->pack_start(m_Box_rb);
	m_Box_rb.pack_start(m_rb_FixedPos);
	m_Box_rb.pack_start(m_rb_Vicon);

	m_rb_FixedPos.set_active();

	this->pack_start(m_InPos_Path);
	this->pack_start(m_Label_OutPath);
	this->pack_start(m_OutPos_Path);

	show_all_children();

}

BoxIO::~BoxIO() {
	// TODO Auto-generated destructor stub
}

} /* namespace UI */
