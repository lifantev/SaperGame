#include "cMain.h"

wxBEGIN_EVENT_TABLE(cMain, wxFrame)
wxEND_EVENT_TABLE()

cMain::cMain() : wxFrame(nullptr, wxID_ANY, "SAPER", wxPoint(20, 20), wxSize(800, 600))
{
	btn = new wxButton * [kFieldWidth * kFieldHeight];
	wxGridSizer* grid = new wxGridSizer(kFieldWidth, kFieldHeight, 0, 0);

	nField = new int[kFieldWidth * kFieldHeight];

	wxFont font(15, wxFONTFAMILY_MODERN, wxFONTSTYLE_SLANT, wxFONTWEIGHT_BOLD, false);

	for (int x = 0; x < kFieldWidth; ++x)
	{
		for (int y = 0; y < kFieldWidth; ++y)
		{
			btn[y * kFieldWidth + x] = new wxButton(this, (10000 + y * kFieldWidth + x));
			btn[y * kFieldWidth + x]->SetFont(font);
			grid->Add(btn[y * kFieldWidth + x], 1, wxEXPAND | wxALL);
			btn[y * kFieldWidth + x]->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &cMain::OnButtonClicked, this);
			nField[y * kFieldWidth + x] = 0;
		}
	}

	this->SetSizer(grid);
	grid->Layout();

}

cMain::~cMain()
{ 
	delete[] btn;
}

void cMain::OnButtonClicked(wxCommandEvent& evt)
{
	int x = (evt.GetId() - 10000) % kFieldHeight;
	int y = (evt.GetId() - 10000) / kFieldWidth;

	wxColor default_color;
	wxColor blue_color(0, 0, 170);
	wxColor red_color(170, 0, 0);


	if (bFirstClick)
	{
		int mines = kNumMines;

		while (mines)
		{
			int rx = rand() % kFieldWidth;
			int ry = rand() % kFieldHeight;

			if (nField[ry * kFieldWidth + rx] == 0 && rx != x && ry != y)
			{
				nField[ry * kFieldWidth + rx] = -1;
				--mines;
			}
		}

		bFirstClick = false;
	}

	btn[y * kFieldWidth + x]->Enable(false);

	if (nField[y * kFieldWidth + x] == -1)
	{
		wxMessageBox("### BOOOOOOOOOM ###");

		bFirstClick = true;

		for (int x = 0; x < kFieldWidth; ++x)
		{
			for (int y = 0; y < kFieldWidth; ++y)
			{
				nField[y * kFieldWidth + x] = 0;
				btn[y * kFieldWidth + x]->SetLabel("");
				btn[y * kFieldWidth + x]->Enable(true);
				btn[y * kFieldWidth + x]->SetBackgroundColour(default_color);
			}
		}
	}
	else
	{
		int mines_arround = 0;

		for (int i = -1; i < 2; ++i)
		{
			for (int j = -1; j < 2; ++j)
			{
				if (x + i >= 0 && x + i < kFieldWidth && y + j >= 0 && y + j < kFieldHeight)
				{
					if (nField[(y + j) * kFieldWidth + (x + i)] == -1)
						++mines_arround;
				}
			}

		}

		if (mines_arround > 0)
		{
			btn[y * kFieldWidth + x]->SetBackgroundColour(red_color);
			btn[y * kFieldWidth + x]->SetLabel(std::to_string(mines_arround));
		}
		else
		{
			btn[y * kFieldWidth + x]->SetBackgroundColour(blue_color);
		}
	}
	
	evt.Skip();  
}
