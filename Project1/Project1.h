/**
 * \file Project1.h
 *
 * \author Team - Summer banana
 *
 * main header file for the Project1 application
 * 
 * Tower Defense Game
 */

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


 /**
  * Application class for Project1 Tower Defense Game
  */
class CProject1App : public CWinApp
{
public:
	CProject1App() noexcept;


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation

public:
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()

private:
	/// GDI+ support variable
	Gdiplus::GdiplusStartupInput gdiplusStartupInput;

	/// GDI+ token
	ULONG_PTR gdiplusToken = 0;
};

extern CProject1App theApp;
