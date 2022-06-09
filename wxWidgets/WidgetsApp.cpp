#include "WidgetsApp.h"

wxIMPLEMENT_APP(WidgetsApp); // tells wxWidget to generate a main for the class

WidgetsApp::WidgetsApp()
{
}

WidgetsApp::~WidgetsApp()
{
}

bool WidgetsApp::OnInit() // to be able to inherit from wxApp
{
	// create an instance of the window
	windowFrame = new WidgetsWindow();
	windowFrame->Show();

	return true;
}
