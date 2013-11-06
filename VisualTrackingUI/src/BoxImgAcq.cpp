/*
 * BoxImgAcq.cpp
 *
 *  Created on: Nov 6, 2013
 *      Author: pablo
 */

#include "BoxImgAcq.h"

namespace UI {

BoxImgAcq::BoxImgAcq() : m_Entry_ImgPath(), m_rb_Devices(
				"Device/s"), m_rb_Images("Images"), m_Box_rb(
				Gtk::ORIENTATION_HORIZONTAL, 5) {

	this->set_orientation(Gtk::ORIENTATION_VERTICAL);

	// Creating the group of radio buttons
	Gtk::RadioButton::Group group = m_rb_Devices.get_group();
	m_rb_Images.set_group(group);

	// Adding widgets

	this->pack_start(m_Box_rb);
	m_Box_rb.pack_start(m_rb_Devices);
	m_Box_rb.pack_start(m_rb_Images);

	m_rb_Devices.set_active();

	this->pack_start(m_Entry_ImgPath);

	show_all_children();

}

BoxImgAcq::~BoxImgAcq() {
	// TODO Auto-generated destructor stub
}

} /* namespace UI */
