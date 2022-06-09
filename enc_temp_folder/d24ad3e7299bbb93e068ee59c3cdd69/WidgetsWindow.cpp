#include "WidgetsWindow.h"

// WidgetWindow is A type wxFrame - it requires some information in order to initialize it (parameters: parent, ID, name, location point, size)
// overriding wxFrame to nullptr since the window does not have a parent, it's the base
// wxID_ANY: each graphical obj gets an ID 
WidgetsWindow::WidgetsWindow(): wxFrame(nullptr, wxID_ANY, "Widgets!", wxPoint(400,200), wxSize(500,500))
{
}

WidgetsWindow::~WidgetsWindow()
{
}
