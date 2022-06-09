#pragma once
#include "wx/wx.h"

// Minesweeper game - you click on the buttons and it reveals
// how many mines are in the surrounding cells 
// use logic to deduce which button is safe to press and which ones aren't  

class WidgetsWindow : public wxFrame //inherit from wxFrame (which is a wimdow in wxWidget) in order for the window/frame to show
{
public:
	WidgetsWindow();

	~WidgetsWindow();
	 
	// There is a parent child relationship btw components and windows
public:

	int fieldWidth = 10;
	int fieldHeight = 10;
	wxButton** btn; // array of pointers to button

	// create another array of integers to store the status of the mines
	int* mineCounter = nullptr; // represent whether the min exists or not
	bool firstClick = true; // if first is being pressed, populate minefield to give user a chance 
							// otherwise it's game over after they click it

	// Add components to the windows (button,text box and a list box)
	/*wxButton* button1 = nullptr;
	wxTextCtrl* text1 = nullptr;
	wxListBox* list1 = nullptr;*/

	// Add events so that when we click on the button after we add items in the Yext box,
	// the item then shows in the liste box
	// we need to handle events that will be sensitive when the button is clicked

	// All events that are not customed have a type: wxCommand Event ( do something event)

	void OnButtonClicked(wxCommandEvent& event); // function that takes wxCommand Event as an argument

	// wxWidgets provides tools to handle events for us: 
	// include the macro declare event table below
	wxDECLARE_EVENT_TABLE(); // implement at the top of .cpp file 
};

