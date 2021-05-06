// DrawPath.h : main header file for the DRAWPATH application
//

#if !defined(AFX_DRAWPATH_H__AA5174B2_AA18_41C8_8A2E_C453941FEBEE__INCLUDED_)
#define AFX_DRAWPATH_H__AA5174B2_AA18_41C8_8A2E_C453941FEBEE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CDrawPathApp:
// See DrawPath.cpp for the implementation of this class
//

class CDrawPathApp : public CWinApp
{
public:
	CDrawPathApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDrawPathApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CDrawPathApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DRAWPATH_H__AA5174B2_AA18_41C8_8A2E_C453941FEBEE__INCLUDED_)
