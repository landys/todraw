// ToDraw.h : main header file for the TODRAW application
//

#if !defined(AFX_TODRAW_H__790BC29F_9867_4C2E_A98F_E0490DF1871C__INCLUDED_)
#define AFX_TODRAW_H__790BC29F_9867_4C2E_A98F_E0490DF1871C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CToDrawApp:
// See ToDraw.cpp for the implementation of this class
//

class CToDrawApp : public CWinApp
{
public:
	CToDrawApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CToDrawApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CToDrawApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TODRAW_H__790BC29F_9867_4C2E_A98F_E0490DF1871C__INCLUDED_)
