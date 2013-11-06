/*
 ============================================================================
 Name        : VisualTrackingUI-GTK.cpp
 Author      : Pablo Ramón Soria
 Version     :
 Copyright   : DD
 Description : Hello World in gttkmm
 ============================================================================
 */

#include "MainWindow.h"
#include <gtkmm/application.h>

int main(int argc, char *argv[]) {
	Glib::RefPtr<Gtk::Application> app = Gtk::Application::create(argc, argv,
			"org.gtkmm.example");

	MainWindow mainWin;
	return app->run(helloworld);
}
