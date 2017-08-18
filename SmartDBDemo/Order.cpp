// Order.cpp : implementation file
//

#include "stdafx.h"
#include "SmartDBDemo.h"
#include "Order.h"
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
// COrder dialog



COrder::COrder(CWnd* pParent /*=NULL*/)
	: CDialog(COrder::IDD, pParent)
{
	//{{AFX_DATA_INIT(COrder)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void COrder::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(COrder)
	DDX_Control(pDX, IDC_LIST_HUANGKUAN, m_listhuankuan);
	DDX_Control(pDX, IDC_LIST_TUPIAN, m_listtupian);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(COrder, CDialog)
	//{{AFX_MSG_MAP(COrder)
	ON_EN_KILLFOCUS(IDC_EDIT_QIXIAN, OnKillfocusEditQixian)
	ON_EN_SETFOCUS(IDC_EDIT_QIXIAN, OnSetfocusEditQixian)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_TUPIAN, OnDblclkListTupian)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COrder message handlers

void COrder::OnKillfocusEditQixian() 
{
	// TODO: Add your control notification handler code here

}

void COrder::OnSetfocusEditQixian() 
{
	// TODO: Add your control notification handler code here
	
}

BOOL COrder::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	DWORD dwStyle = m_listtupian.SendMessage(LVM_GETEXTENDEDLISTVIEWSTYLE,0,0);
	dwStyle |= LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_HEADERDRAGDROP;
	m_listtupian.SendMessage(LVM_SETEXTENDEDLISTVIEWSTYLE, 0, (LPARAM)dwStyle);
	
	DWORD dwEx = m_listtupian.GetExtendedStyle();
	m_listtupian.SetExtendedStyle(dwEx|LVS_EX_FLATSB);
	
	m_listtupian.InsertColumn( 0, _T("id"), LVCFMT_LEFT, 1);
	m_listtupian.InsertColumn( 1, _T("����id"), LVCFMT_LEFT, 1);
	m_listtupian.InsertColumn( 2, _T("ͼƬ��ַ"), LVCFMT_LEFT, 240);
	
	m_listhuankuan.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);      // ����ѡ��������  
	m_listhuankuan.InsertColumn(0, _T("id"), LVCFMT_CENTER, 1);        // �����2�е����� 
	m_listhuankuan.InsertColumn(1, _T("����"), LVCFMT_CENTER, 50);        // �����2�е�����  
	m_listhuankuan.InsertColumn(2, _T("������"), LVCFMT_CENTER, 110);        // �����3�е�����         // �����4�е�����  
	m_listhuankuan.InsertColumn(3, _T("������"), LVCFMT_CENTER, 80);        // �����3�е�����         // �����4�е����� 
	m_listhuankuan.InsertColumn(4, _T("״̬"), LVCFMT_CENTER, 60);        // �����3�е�����         // �����4�е�����  
	m_listhuankuan.InsertColumn(5, _T("��ע"), LVCFMT_CENTER, 295);        // �����3�е�����         // �����4�е�����  
	
	
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
	LVITEM lvItem;
	INT nRecNum=0;
	for (i=0; i < rsMain.FieldsCount(); i++)
	{
		lvItem.mask = LVIF_TEXT;
		lvItem.iItem = nRecNum;
		lvItem.iSubItem = i;
		lvItem.pszText = (LPTSTR)rsMain.GetColumnString(i);
		
		if (i == 0)
			m_listtupian.InsertItem(&lvItem);
		else
			m_listtupian.SetItem(&lvItem);
	}
	rsMain.MoveNext();
	nRecNum++;
	rsMain.Close();
	
	if (rsMain.Open (strsqlhuankuan, &connMain) != RSOPEN_SUCCESS)
		return nRetVal;
	
	rsMain.Close();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void COrder::OnDblclkListTupian(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	// TODO: Add your control notification handler code here
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: Add your control notification handler code here
	NM_LISTVIEW *pNMListView=(NM_LISTVIEW *)pNMHDR;
	int nItem=pNMListView->iItem;
	if(nItem>=0 && nItem<m_listtupian.GetItemCount())    //�ж�˫��λ���Ƿ��������ݵ��б�������
	{
		POSITION Pos = m_listtupian.GetFirstSelectedItemPosition();
		int nSelect = -1;
		
		while ( Pos )
		{
			
			nSelect = m_listtupian.GetNextSelectedItem(Pos);    //nSelect�ܻ�õڼ���
			CString s=m_listtupian.GetItemText(nSelect,2);
			s="imgs\\"+s;
			ShellExecute(NULL, "open", s, NULL, NULL, SW_SHOW);
		}
	}
	*pResult = 0;
}
