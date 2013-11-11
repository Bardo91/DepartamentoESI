/*
 * BoxImgAcq.h
 *
 *  Created on: Nov 6, 2013
 *      Author: pablo
 */

#ifndef _VISIONTRACKINGUI_BOXIMGACQ_H_
#define _VISIONTRACKINGUI_BOXIMGACQ_H_

#include <gtkmm.h>
#include <gtkmm/box.h>

namespace UI {

class BoxImgAcq: public Gtk::Box {
public:
	BoxImgAcq();
	virtual ~BoxImgAcq();

protected:
	// Signals

	// Members
	Gtk::Entry m_Entry_ImgPath;
	Gtk::RadioButton m_rb_Devices, m_rb_Images;
	Gtk::Box m_Box_rb;
};

} /* namespace UI */

#endif /* _VISIONTRACKINGUI_BOXIMGACQ_H_ */
