// LoginDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SmartDBDemo.h"
#include "LoginDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLoginDlg dialog


CLoginDlg::CLoginDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CLoginDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CLoginDlg)
	m_password = _T("");
	m_msg = _T("");
	//}}AFX_DATA_INIT
}


void CLoginDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLoginDlg)
	DDX_Text(pDX, IDC_EDIT1, m_password);
	DDX_Text(pDX, IDC_MSG, m_msg);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CLoginDlg, CDialog)
	//{{AFX_MSG_MAP(CLoginDlg)
	ON_WM_CLOSE()
	ON_WM_DESTROY()
	ON_EN_SETFOCUS(IDC_EDIT1, OnSetfocusEdit1)
	ON_WM_CANCELMODE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLoginDlg message handlers

void CLoginDlg::OnOK() 
{
	// TODO: Add extra validation here
// 	CString ac=	"C:\\Users\\Adminis21trator\\learngit\\Smar21tDBDemo\\Release\\imgs\\2017-2-01_12_59-11793.png";
// 
// 	ac = ac.Right( ac.GetLength()-(ac.ReverseFind('\\')+1) );
// 
// 	MessageBox(ac);
// 	int i = ac.Find( '\\' );
// 	CString f;
// 	f.Format("%d",i);
// 	MessageBox(f);
// 	MessageBox(ac.Right(i)) ;

	UpdateData(TRUE);
	if (m_password== "1")
	{
		CDialog::OnCancel();
	}
	else
	{
		m_msg="√‹¬Î¥ÌŒÛ";
		UpdateData(FALSE);
	}
	
}

void CLoginDlg::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	CDialog::OnClose();
}


void CLoginDlg::OnDestroy() 
{
	CDialog::OnDestroy();
	
	// TODO: Add your message handler code here

}

void CLoginDlg::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	exit(0);
}

void CLoginDlg::OnSetfocusEdit1() 
{
	// TODO: Add your control notification handler code here
	m_msg="";
	m_password="";
	UpdateData(FALSE);
}

BOOL CLoginDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
