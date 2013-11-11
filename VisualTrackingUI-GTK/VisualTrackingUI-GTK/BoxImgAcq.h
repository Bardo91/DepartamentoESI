/*
 * BoxImgAcq.h
 *
 *  Created on: Nov 6, 2013
 *      Author: pablo
 */

#ifndef BOXIMGACQ_H_
#define BOXIMGACQ_H_

#include <gtkmm.h>
#include <gtkmm/box.h>

namespace UI {

class BoxImgAcq: Gtk::Box {
public:
	BoxImgAcq();
	virtual ~BoxImgAcq();

protected:
	// Signals

	// Members
	Gtk::Label m_Label_Img;
	Gtk::Entry m_Entry_ImgPath;
	Gtk::RadioButton m_rb_Devices, m_rb_Images;
	Gtk::Box m_Box_rb;
};

} /* namespace UI */

#endif /* BOXIMGACQ_H_ */
