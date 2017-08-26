#if !defined(AFX_ORDER_H__7619EC62_F40D_48ED_A00C_0B80C79006F0__INCLUDED_)
#define AFX_ORDER_H__7619EC62_F40D_48ED_A00C_0B80C79006F0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Order.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// COrder dialog

class COrder : public CDialog
{
// Construction
public:
	COrder(CWnd* pParent = NULL);   // standard constructor
	int m_Col;
	int m_Row;
	void countallhuan();
// Dialog Data
	//{{AFX_DATA(COrder)
	enum { IDD = IDD_DIALOG_ORDER };
	CEdit	m_listedit;
	CListCtrl	m_listhuankuan;
	CListCtrl	m_listtupian;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COrder)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(COrder)
	afx_msg void OnKillfocusEditQixian();
	afx_msg void OnSetfocusEditQixian();
	virtual BOOL OnInitDialog();
	afx_msg void OnDblclkListTupian(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDblclkListHuangkuan(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnKillfocusEditList();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ORDER_H__7619EC62_F40D_48ED_A00C_0B80C79006F0__INCLUDED_)
