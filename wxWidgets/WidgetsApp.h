#pragma once
#include "wx/wx.h"
#include "WidgetsWindow.h"

class WidgetsApp: public wxApp //inherit from base class provided by the framework "wxApp" ~ wxWidgets type framework
{
public:
	WidgetsApp();

	~WidgetsApp();

private:
	WidgetsWindow* windowFrame = nullptr; // private variable for the frame

public:
	virtual bool OnInit(); // to be able to inherit from wxApp
};

