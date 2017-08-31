#if !defined(AFX_XINYONG_H__EEAC00A8_3D46_4F71_BE24_B5AC27126E99__INCLUDED_)
#define AFX_XINYONG_H__EEAC00A8_3D46_4F71_BE24_B5AC27126E99__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Xinyong.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CXinyong dialog

class CXinyong : public CDialog
{
// Construction
public:
	CXinyong(CWnd* pParent = NULL);   // standard constructor
	void conut();
	void liandong();
	void countendtime();
// Dialog Data
	//{{AFX_DATA(CXinyong)
	enum { IDD = IDD_CREATE_XINYONG };
	CComboBox	m_qixiandanwei;
	CComboBox	m_jixiriqi;
	CComboBox	m_huankuanfangshi;
	CComboBox	m_fenlei;
	CComboBox	m_danwei;
	CListCtrl	m_list_huankuan;
	CMonthCalCtrl	m_CtrlDate;
	CListCtrl	m_list1;
	CString	m_starttime;
	CString	m_endtime;
	CString	m_qixian;
	CString	m_money;
	CString	m_lilv;
	CString	m_beizhu;
	CString	m_fuwufei;
	CString	m_idcard;
	CString	m_chuziren;
	CString	m_jingbanren;
	CString	m_name;
	CString	m_xuhuankuan;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CXinyong)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CXinyong)
	virtual BOOL OnInitDialog();
	afx_msg void OnChangeEditQixian();
	afx_msg void OnEditchangeComboJixiriqi();
	afx_msg void OnSelchangeComboJixiriqi();
	afx_msg void OnSelchangeComboHuankuan();
	afx_msg void OnChangeEditLilv();
	afx_msg void OnChangeEditMoney();
	afx_msg void OnChangeEditStarttime();
	afx_msg void OnSetfocusEditStarttime();
	afx_msg void OnKillfocusEditStarttime();
	afx_msg void OnSelchangeMonthcalendar1(NMHDR* pNMHDR, LRESULT* pResult);
	virtual void OnOK();
	afx_msg void OnButton1();
	afx_msg void OnDblclkList1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnChangeEditXuhuankuan();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_XINYONG_H__EEAC00A8_3D46_4F71_BE24_B5AC27126E99__INCLUDED_)
