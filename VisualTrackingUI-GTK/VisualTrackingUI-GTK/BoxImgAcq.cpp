/*
 * BoxImgAcq.cpp
 *
 *  Created on: Nov 6, 2013
 *      Author: pablo
 */

#include "BoxImgAcq.h"

namespace UI {

BoxImgAcq::BoxImgAcq() :
		m_Label_Img("Image Acquisition"),
		m_Entry_ImgPath(),
		m_rb_Devices("Device/s"),
		m_rb_Images("Images"),
		m_Box_rb(Gtk::ORIENTATION_VERTICAL, 5) {

	this->pack_start(m_Label_Img);

	this->pack_start(m_Box_rb);
	m_Box_rb.pack_start(m_rb_Devices);
	m_Box_rb.pack_start(m_rb_Images);

	this->pack_start(m_Entry_ImgPath);

	show_all_children();

}

BoxImgAcq::~BoxImgAcq() {
	// TODO Auto-generated destructor stub
}

} /* namespace UI */
