/*
 * BoxTitle.h
 *
 *  Created on: Nov 6, 2013
 *      Author: pablo
 */

#ifndef BOXTITLE_H_
#define BOXTITLE_H_

#include <gtkmm.h>
#include <gtkmm/box.h>

namespace UI {

class BoxTitle: Gtk::Box {
public:
	BoxTitle();
	virtual ~BoxTitle();

protected:
	Gtk::Label m_Label_Title, m_label_Author, m_Label_Version;
};

} /* namespace UI */

#endif /* BOXTITLE_H_ */
