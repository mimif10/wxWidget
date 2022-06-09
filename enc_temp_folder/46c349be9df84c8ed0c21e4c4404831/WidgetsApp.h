#pragma once
#include "wx/wx.h"
#include "WidgetsWindow.h"

class WidgetsApp: public wxApp //inherit from base class provided by the framework "wxApp" ~ wxWidgets type framework
{
public:
	WidgetsApp();

	~WidgetsApp();

public:
	virtual bool OnInit(); // to be able to inherit from wxApp
};

