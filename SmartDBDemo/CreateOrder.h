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
	CMonthCalCtrl	m_CtrlDate;
	CListCtrl	m_list1;
	CString	m_starttime;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCreateOrder)
	public:
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CCreateOrder)
	virtual void OnOK();
	afx_msg void OnButton1();
	afx_msg void OnClickList1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDoubleclickedButton1();
	afx_msg void OnGetdaystateMonthcalendar1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSelectMonthcalendar1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSetfocusEditStarttime();
	afx_msg void OnKillfocusEditStarttime();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CREATEORDER_H__F465FDC1_51AB_48AB_9E4A_D06951915921__INCLUDED_)
