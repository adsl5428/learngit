// SmartDBDemo.h : main header file for the SMARTDBDEMO application
//

#if !defined(AFX_SMARTDBDEMO_H__066DABCF_BEA4_4D64_9DE4_A84B6C0F5283__INCLUDED_)
#define AFX_SMARTDBDEMO_H__066DABCF_BEA4_4D64_9DE4_A84B6C0F5283__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CSmartDBDemoApp:
// See SmartDBDemo.cpp for the implementation of this class
//

class CSmartDBDemoApp : public CWinApp
{
public:
	CSmartDBDemoApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSmartDBDemoApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CSmartDBDemoApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SMARTDBDEMO_H__066DABCF_BEA4_4D64_9DE4_A84B6C0F5283__INCLUDED_)
