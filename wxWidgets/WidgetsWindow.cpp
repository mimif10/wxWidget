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
	// Create and populate the new array of buttons (line 20)
	// which will be 10 x 10 = 100 buttons
	btn = new wxButton*[fieldWidth * fieldHeight];

	// Sizer is a structure (not a component) that describe the relationship btwn a parent and its children
	// as the parent is being resized the sizer updates the size of its children 
	// A gridSizer ensures all of the columns and rows of the children's components are equally spaced
	wxGridSizer* grid = new wxGridSizer(fieldWidth, fieldHeight, 0, 0); // (rows, columns, padding/gaps inside the rows and columns )
	

	// Create and populate the new array of buttons (line 23)
	mineCounter = new int[fieldWidth * fieldHeight];

	// Change the size of the font inside the cell 
	// Create an instance of wxFont and tell it (the size, font, nold/italic)
	wxFont font(14, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false);
	
	// nested for loop to create buttons and add them to the parent window
	for (int x = 0; x < fieldWidth; x++)
	{
		for (int y = 0; y < fieldHeight; y++)
		{
			// y * width of x turns 2D coord sys into a 1D system for the array of buttons
			btn[y * fieldWidth + x] = new wxButton(this, 10000 + (y * fieldWidth + x));
			                          // create a new button(parent frame, unique ID based on its position within the array)

			// For each button, set the font to the font we created
			btn[y * fieldWidth + x]->SetFont(font);

			// Add the new button to the grid sizer
			grid->Add(btn[y * fieldWidth + x], 1, wxEXPAND | wxALL); 
												// wxEXPAND | wxALL = occupy the entire space of the cell in the grid
												// and expand as necessary to follow the dimensions (gride sizer)
			// Handle one of the buttons being pressed on the grid by
			// dinamically associating an event handling function with the button being clicked
			// Take the button and call the binding function (will bind an event handler to the specified event handler)
			// So if the button is being clicked, it will bind that event (event handler) to the "OnButtonClickd"
			btn[y * fieldWidth + x]->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &WidgetsWindow::OnButtonClicked, this);

			// set the default value for each location in the minefield array to 0
			mineCounter[y * fieldWidth + x] = 0;
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
	// Since we specified a specific ID for all of the buttons in the grid
	// We can figure out which particular button was clicked with its x and y coordinates
	int x = (event.GetId() - 10000) % fieldWidth;
	int y = (event.GetId() - 10000) / fieldHeight;
	
	if (firstClick) // One the very 1st click of the game, generate the minefield
	{
		int mines = 30; // for a 10x10 mine, there are 30 mines

		// randomly generate x and y locations within that minefield
		while(mines)
		{
			int rx = rand() % fieldWidth;
			int ry = rand() % fieldHeight;

			// if there is no mine at that location and also check that the randonly selected location
			// is not the same as the location of the button in the array
			// we don't want the 1st button clicked to cause a game over
			if (mineCounter[ry * fieldWidth + rx] == 0 && rx != x && ry != y)
			{
				// then place a mine there
				mineCounter[ry * fieldWidth + rx] = -1; // -1 indicates the	presence of mine after 1st click
				mines--;
			}
		}

		firstClick = false; 
	}

	// Disable the button from being pressed again since we've already tried it
	btn[y * fieldWidth + x]->Enable(false);

	// Check if player hit mine when button is clicked
	if(mineCounter[y*fieldWidth +x] == -1) // if cell contains a -1
	{
		wxMessageBox("BOOOOOOOM !! ** GAME OVER ** :("); // Game over

		// Reset the game
		firstClick = true; // set first click to true
		for (int x = 0; x < fieldWidth; x++) // go through all of the mines and buttons
		{
			for (int y = 0; y < fieldHeight; y++)
			{
				mineCounter[y * fieldWidth + x] = 0; // reset them 
			 // set the label to blank so the label is the text that appears on the button
				btn[y * fieldWidth + x]->SetLabel("");
				btn[y * fieldWidth + x]->Enable(true); // and enable them again
			}
		}
	// use the label to indicate to the player how many mines are surrounding the clicked button
	}
	else // if the player clicked and didn't hit a mine
	{
		// Go through all the neighbors and count the number of mines that exist
		int counter = 0;
		for (int i = 0; i < 2; i++) // iterate around the 8 neighbors of the clicked cell
		{
			for (int j = -1; j < 2; j++)
			{
				if (x + i >= 0 && x + i < fieldWidth && y + j >= 0 && y + j < fieldHeight)
				{
					// if any of the neighbooring cells are equal to -1 
					if (mineCounter[(y + j)*fieldWidth + (x + i)] == -1)
					{
						counter++; // then keep count of how many mines surround that cell
					}
				}
			}
		}


		// Update buttons lable to show mine count 
		if (counter > 0) // if counter/mine count > 0
		{
			// Use the set label function of the button 
			// to display the number of mines in the surrounding cells
			btn[y * fieldWidth + x]->SetLabel(std::to_string(counter));
		}
	}
	
	//// Event handler for the components we created in WidgetsWindow.h (line 18)
	//// Add the contents of the text box to the list box 
	//list1->AppendString(text1->GetValue()); // AppendString adds a string to the list box
	//					// We get the string from the text box
	//
	event.Skip(); // tells the system the event has been handled
}

