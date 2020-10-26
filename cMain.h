#pragma once
#include "wx/wx.h"

class cMain : public wxFrame
{
public:
	cMain();
	~cMain();

	const int kFieldWidth = 10;
	const int kFieldHeight = 10;
	wxButton** btn;
	int *nField = nullptr;
	const int kNumMines = 30;
	bool bFirstClick = true;

	void OnButtonClicked(wxCommandEvent& evt);

	wxDECLARE_EVENT_TABLE();
};

