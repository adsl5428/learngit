// SmartDBDemoDlg.h : header file
//

#if !defined(AFX_SMARTDBDEMODLG_H__BA115F57_C4F3_4BB8_BC04_E63FDE1A37E8__INCLUDED_)
#define AFX_SMARTDBDEMODLG_H__BA115F57_C4F3_4BB8_BC04_E63FDE1A37E8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CSmartDBDemoDlg dialog

//#include "SmartDBRecordSet.h"
#include "SmartDB.h"

class CSmartDBDemoDlg : public CDialog
{
// Construction
public:
	UINT ExecuteQueryAndShow (LPCTSTR strSelectQuery);
	CSmartDBDemoDlg(CWnd* pParent = NULL);	// standard constructor
	bool m_login;
	
// Dialog Data
	//{{AFX_DATA(CSmartDBDemoDlg)
	enum { IDD = IDD_SMARTDBDEMO_DIALOG };

	CEdit	m_password;
	CButton	m_btnLoad;
	CStatic	m_statSQL;
	CButton	m_btnExecute;
	CEdit	m_edtQuery;
	CListBox	m_listTables;
	CListCtrl	m_listData;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSmartDBDemoDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CSmartDBDemoDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBtnLoad();
	afx_msg void OnSelchangeListTables();
	afx_msg void OnBtnUnload();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnBtnExecute();
	afx_msg void OnSetfocusEditQuery();
	afx_msg void OnKillfocusEditQuery();
	afx_msg void OnFileOpen();
	afx_msg void OnHelpAboutsmartsb();
	afx_msg void OnAdd();
	afx_msg void OnButton1();
	afx_msg void OnButton2();
	afx_msg void OnDblclkListData(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SMARTDBDEMODLG_H__BA115F57_C4F3_4BB8_BC04_E63FDE1A37E8__INCLUDED_)
