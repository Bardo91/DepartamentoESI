/*
 * BoxAlgorithm.h
 *
 *  Created on: Nov 6, 2013
 *      Author: pablo
 */

#ifndef _VISIONTRACKINGUI_BOXALGORITHM_H_
#define _VISIONTRACKINGUI_BOXALGORITHM_H_

#include <gtkmm.h>
#include <gtkmm/box.h>

namespace UI {

class BoxAlgorithm: public Gtk::Box {
public:
	BoxAlgorithm();
	virtual ~BoxAlgorithm();
};

} /* namespace UI */

#endif /* _VISIONTRACKINGUI_BOXALGORITHM_H_ */
