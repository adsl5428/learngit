// Xinyong.cpp : implementation file
//

#include "stdafx.h"
#include "SmartDBDemo.h"
#include "Xinyong.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CXinyong dialog


CXinyong::CXinyong(CWnd* pParent /*=NULL*/)
	: CDialog(CXinyong::IDD, pParent)
{
	//{{AFX_DATA_INIT(CXinyong)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CXinyong::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CXinyong)
	DDX_Control(pDX, IDC_COMBO_QIXIANDANWEI, m_qixiandanwei);
	DDX_Control(pDX, IDC_COMBO_JIXIRIQI, m_jixiriqi);
	DDX_Control(pDX, IDC_COMBO_HUANKUAN, m_huankuanfangshi);
	DDX_Control(pDX, IDC_COMBO_FENLEI, m_fenlei);
	DDX_Control(pDX, IDC_COMBO_DANWEI, m_danwei);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CXinyong, CDialog)
	//{{AFX_MSG_MAP(CXinyong)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CXinyong message handlers

BOOL CXinyong::OnInitDialog() 
{
	CDialog::OnInitDialog();
	// TODO: Add extra initialization here
	m_danwei.SetCurSel(0);
	m_fenlei.SetCurSel(0);
	m_huankuanfangshi.SetCurSel(0);
	m_jixiriqi.SetCurSel(0);
	m_qixiandanwei.SetCurSel(0);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
