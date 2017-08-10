#if !defined(AFX_CREATEORDER_H__F465FDC1_51AB_48AB_9E4A_D06951915921__INCLUDED_)
#define AFX_CREATEORDER_H__F465FDC1_51AB_48AB_9E4A_D06951915921__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CreateOrder.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCreateOrder dialog

class CCreateOrder : public CDialog
{
// Construction
public:
	CCreateOrder(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CCreateOrder)
	enum { IDD = IDD_CREATE_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCreateOrder)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CCreateOrder)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CREATEORDER_H__F465FDC1_51AB_48AB_9E4A_D06951915921__INCLUDED_)
