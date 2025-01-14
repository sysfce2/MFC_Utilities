
// SeguroMedico.h : main header file for the SeguroMedico application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CSeguroMedicoApp:
// See SeguroMedico.cpp for the implementation of this class
//

class CSeguroMedicoApp : public CWinAppEx
{
public:
	CSeguroMedicoApp() noexcept;


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	UINT  m_nAppLook;
	BOOL  m_bHiColorIcons;

	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();

	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
	afx_msg void OnFileOpendialog();
};

extern CSeguroMedicoApp theApp;
