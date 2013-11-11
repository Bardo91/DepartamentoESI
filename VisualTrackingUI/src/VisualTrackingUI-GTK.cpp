/*
 ============================================================================
 Name        : VisualTrackingUI-GTK.cpp
 Author      : Pablo Ramón Soria
 Version     :
 Copyright   : DD
 Description : Hello World in gttkmm
 ============================================================================
 */

#include <gtkmm/application.h>

#include "MainWindow.h"

using namespace UI;

int main(int argc, char *argv[]) {
	Glib::RefPtr<Gtk::Application> app = Gtk::Application::create(argc, argv,
			"PabloRamonSoria");

	MainWindow mainWin;

	return app->run(mainWin);
}
