// CreateOrder.cpp : implementation file
//

#include "stdafx.h"
#include "SmartDBDemo.h"
#include "CreateOrder.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCreateOrder dialog


CCreateOrder::CCreateOrder(CWnd* pParent /*=NULL*/)
	: CDialog(CCreateOrder::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCreateOrder)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CCreateOrder::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCreateOrder)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCreateOrder, CDialog)
	//{{AFX_MSG_MAP(CCreateOrder)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCreateOrder message handlers
