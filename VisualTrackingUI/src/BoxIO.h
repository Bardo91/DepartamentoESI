/*
 * BoxIO.h
 *
 *  Created on: Nov 6, 2013
 *      Author: pablo
 */

#ifndef _VISIONTRACKINGUI_BOXIO_H_
#define _VISIONTRACKINGUI_BOXIO_H_

#include <gtkmm.h>
#include <gtkmm/box.h>

namespace UI {

class BoxIO: public Gtk::Box {
public:
	BoxIO();
	virtual ~BoxIO();

protected:
	// Signals

	// Members
	Gtk::Box m_Box_rb;
	Gtk::Label m_Label_PosAcMet, m_Label_OutPath;
	Gtk::RadioButton m_rb_FixedPos, m_rb_Vicon;
	Gtk::Entry m_InPos_Path, m_OutPos_Path;
};

} /* namespace UI */

#endif /* _VISIONTRACKINGUI_BOXIO_H_ */
