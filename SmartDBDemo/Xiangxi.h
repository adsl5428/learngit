#if !defined(AFX_XIANGXI_H__B280B400_956C_427D_A401_3D57C6E67A89__INCLUDED_)
#define AFX_XIANGXI_H__B280B400_956C_427D_A401_3D57C6E67A89__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Xiangxi.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CXiangxi dialog

class CXiangxi : public CDialog
{
// Construction
public:
	CXiangxi(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CXiangxi)
	enum { IDD = IDD_DIALOG_XIANGXI };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CXiangxi)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CXiangxi)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_XIANGXI_H__B280B400_956C_427D_A401_3D57C6E67A89__INCLUDED_)
