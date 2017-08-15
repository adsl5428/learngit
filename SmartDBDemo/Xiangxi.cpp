// Xiangxi.cpp : implementation file
//

#include "stdafx.h"
#include "SmartDBDemo.h"
#include "Xiangxi.h"
#include "SmartDB.h"

extern int orderid;
extern CSmartDBRecordSet rsMain;
extern CSmartDB connMain;


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CXiangxi dialog

CXiangxi::CXiangxi(CWnd* pParent /*=NULL*/)
	: CDialog(CXiangxi::IDD, pParent)
{
	//{{AFX_DATA_INIT(CXiangxi)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CXiangxi::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CXiangxi)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CXiangxi, CDialog)
	//{{AFX_MSG_MAP(CXiangxi)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CXiangxi message handlers

BOOL CXiangxi::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	UINT nRetVal = -1;
	CString strtemp;
	strtemp.Format("%d",orderid);
	CString strsqlorder; 
	CString strsqlpicture;
	CString strsqlhuankuan;
	int i;
	strsqlorder.Format("select * from orders where id = '%d'",orderid);
	strsqlpicture.Format("select * from pictures where order_id = '%d'",orderid);
	strsqlhuankuan.Format("select * from huankuans where order_id = '%d'",orderid);

	if (rsMain.Open (strsqlorder, &connMain) != RSOPEN_SUCCESS)
		return nRetVal;
	while (!rsMain.IsEOF())
	{
		for (i=0; i < rsMain.FieldsCount(); i++)
		{		
			int ikongjian[]={IDC_STATIC_ID,IDC_EDIT_NAME,IDC_EDIT_IDCARD,IDC_EDIT_MONEY,IDC_EDIT_QIXIAN,IDC_EDIT_HUANKUAN,IDC_EDIT_LILV,IDC_EDIT_FUWUFEI,IDC_EDIT_BEIZHU,IDC_EDIT_STARTTIME};
			SetDlgItemText(ikongjian[i],(LPTSTR)rsMain.GetColumnString(i));
		}
		rsMain.MoveNext();
	}
	rsMain.Close();

	if (rsMain.Open (strsqlpicture, &connMain) != RSOPEN_SUCCESS)
		return nRetVal;
	
	rsMain.Close();

	if (rsMain.Open (strsqlhuankuan, &connMain) != RSOPEN_SUCCESS)
		return nRetVal;
	
	rsMain.Close();

// 	MessageBox(strtemp);
// 	SetDlgItemText(IDC_EDIT_NAME,"12345");
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
