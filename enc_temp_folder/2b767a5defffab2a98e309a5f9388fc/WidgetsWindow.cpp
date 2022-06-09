#include "WidgetsWindow.h"

// implement Event Table
wxBEGIN_EVENT_TABLE(WidgetsWindow, wxFrame) // takes name of the class for the event and the base class)
	EVT_BUTTON(10001, OnButtonClicked) // macroe event button that takes in the button's windows ID, and link any button eith the ID being clicked
									  // to the function we want to call 
wxEND_EVENT_TABLE()

// WidgetWindow is A type wxFrame - it requires some information in order to initialize it (parameters: parent, ID, name, location point, size)
// overriding wxFrame to nullptr since the window does not have a parent, it's the base
// wxID_ANY: each graphical obj gets an ID 
// Title for the window
// Location is where we want the window to appear ( a point)x,y))
// Size of the window (width, height)
WidgetsWindow::WidgetsWindow(): wxFrame(nullptr, wxID_ANY, "Widgets!", wxPoint(400,200), wxSize(500,400))
{
	// Create and populate the new array of buttons (line 13)
	// which will be 10 x 10 = 100 buttons
	btn = new wxButton*[fieldWidth * fieldHeight];

	// Sizer is a structure (not a component) that describe the relationship btwn a parent and its children
	// as the parent is being resized the sizer updates the size of its children 
	// A gridSizer ensures all of the columns and rows of the children's components are equally spaced
	wxGridSizer* grid = new wxGridSizer(fieldWidth, fieldHeight, 0, 0); // (rows, columns, padding/gaps inside the rows and columns )
	
	// nested for loop to create buttons and add them to the parent window
	for (int x = 0; x < fieldWidth; x++)
	{
		for (int y = 0; y < fieldHeight; y++)
		{
			// y * width of x turns 2D coord sys into a 1D system for the array of buttons
			btn[y * fieldWidth + x] = new wxButton(this, 10000 + (y * fieldWidth + x));
			                          // create a new button(parent frame, unique ID based on its position within the array)
			// Add the new button to the grid sizer
			grid->Add(btn[y * fieldWidth + x], 1, wxEXPAND | wxALL); 
												// wxEXPAND | wxALL = occupy the entire space of the cell in the grid
												// and expand as necessary to follow the dimensions (gride sizer)
		}	
	}
	
	// Tell the parent window which sizer to use (gridsizer)
	this->SetSizer(grid);
	
	// Also to restrict itself dependinng on 
	// the information contained in the grid (buttons with 10 rows and 10 columns)
	grid->Layout();

	// for the button,text box and list box we created in WidgetsWindow.h (line 18)
	//button1 = new wxButton(this, 10001, "Click Me", wxPoint(10, 10), wxSize(150, 50));
	//text1 = new wxTextCtrl(this, wxID_ANY, "", wxPoint(10, 70), wxSize(300, 30));
	//list1 = new wxListBox(this, wxID_ANY, wxPoint(10, 110), wxSize(300, 300));
}

WidgetsWindow::~WidgetsWindow()
{
	// delete the array of buttons to prevent a memory leak
	delete[] btn;
}

void WidgetsWindow::OnButtonClicked(wxCommandEvent &event)
{
	//// Event handler for the components we created in WidgetsWindow.h (line 18)
	//// Add the contents of the text box to the list box 
	//list1->AppendString(text1->GetValue()); // AppendString adds a string to the list box
	//					// We get the string from the text box
	//event.Skip(); // tells the system the event has been handled
}

