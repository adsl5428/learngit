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

// Dialog Data
	//{{AFX_DATA(CXinyong)
	enum { IDD = IDD_CREATE_XINYONG };
	CComboBox	m_qixiandanwei;
	CComboBox	m_jixiriqi;
	CComboBox	m_huankuanfangshi;
	CComboBox	m_fenlei;
	CComboBox	m_danwei;
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
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_XINYONG_H__EEAC00A8_3D46_4F71_BE24_B5AC27126E99__INCLUDED_)