
// invaders.h : main header file for the invaders application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CinvadersApp:
// See invaders.cpp for the implementation of this class
//

class CinvadersApp : public CWinApp
{
public:
	CinvadersApp();


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CinvadersApp theApp;
