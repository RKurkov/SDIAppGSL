
// SDIAppGSL.h : main header file for the SDIAppGSL application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CSDIAppGSLApp:
// See SDIAppGSL.cpp for the implementation of this class
//

class CSDIAppGSLApp : public CWinApp
{
public:
	CSDIAppGSLApp() noexcept;


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CSDIAppGSLApp theApp;
