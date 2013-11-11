/*
 * BoxTitle.cpp
 *
 *  Created on: Nov 6, 2013
 *      Author: pablo
 */

#include "BoxTitle.h"

namespace UI {

BoxTitle::BoxTitle() :
		m_Label_Title("Color Objects Tracking UI"), m_label_Author(
				"Author: Pablo Ramón Soria"), m_Label_Version("Version 2.0") {

	// Setting text charasteristic
	m_Label_Title.set_justify(Gtk::JUSTIFY_CENTER);
	m_label_Author.set_justify(Gtk::JUSTIFY_RIGHT);
	m_Label_Version.set_justify(Gtk::JUSTIFY_RIGHT);

	this->pack_start(m_Label_Title, Gtk::PACK_EXPAND_WIDGET, 10);
	this->pack_start(m_label_Author, Gtk::PACK_EXPAND_WIDGET, 10);
	this->pack_start(m_Label_Version, Gtk::PACK_EXPAND_WIDGET, 10);

	show_all_children();

}

BoxTitle::~BoxTitle() {
	// TODO Auto-generated destructor stub
}

} /* namespace UI */
