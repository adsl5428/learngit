// CreateOrder.cpp : implementation file
//

#include "stdafx.h"
#include "SmartDBDemo.h"
#include "CreateOrder.h"
#include "SmartDB.h"

extern CSmartDB connMain;
extern CSmartDBRecordSet rsMain;

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
	m_starttime = _T("");
	//}}AFX_DATA_INIT
}


void CCreateOrder::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCreateOrder)
	DDX_Control(pDX, IDC_MONTHCALENDAR1, m_CtrlDate);
	DDX_Control(pDX, IDC_LIST1, m_list1);
	DDX_Text(pDX, IDC_EDIT_STARTTIME, m_starttime);
	//}}AFX_DATA_MAP

}


BEGIN_MESSAGE_MAP(CCreateOrder, CDialog)
	//{{AFX_MSG_MAP(CCreateOrder)
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_NOTIFY(NM_CLICK, IDC_LIST1, OnClickList1)
	ON_BN_DOUBLECLICKED(IDC_BUTTON1, OnDoubleclickedButton1)
	ON_NOTIFY(MCN_GETDAYSTATE, IDC_MONTHCALENDAR1, OnGetdaystateMonthcalendar1)
	ON_NOTIFY(MCN_SELECT, IDC_MONTHCALENDAR1, OnSelectMonthcalendar1)
	ON_EN_SETFOCUS(IDC_EDIT_STARTTIME, OnSetfocusEditStarttime)
	ON_EN_KILLFOCUS(IDC_EDIT_STARTTIME, OnKillfocusEditStarttime)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCreateOrder message handlers
void msgint(int a)
{
	CString f;
	f.Format("%d",a);
	MessageBox(NULL,f,f,0);
}
void CCreateOrder::OnOK() 
{
	// TODO: Add extra validation here
	bool one=true;
	CString strSQL;
	CString strbeizhu;
	CString strfuwufei;
	CString strhuankuan;
	CString stridcard;
	CString strlilv;
	CString strmoney;
	CString strname;
	CString strqixian;
	CString strstarttime;
	
GetDlgItemText (IDC_EDIT_BEIZHU, strbeizhu);
GetDlgItemText (IDC_EDIT_FUWUFEI, strfuwufei);
GetDlgItemText (IDC_EDIT_HUANKUAN,strhuankuan );
GetDlgItemText (IDC_EDIT_IDCARD, stridcard);
GetDlgItemText (IDC_EDIT_LILV,strlilv );
GetDlgItemText (IDC_EDIT_MONEY,strmoney );
GetDlgItemText (IDC_EDIT_NAME,strname );
GetDlgItemText (IDC_EDIT_QIXIAN,strqixian );
GetDlgItemText (IDC_EDIT_STARTTIME, strstarttime);

strSQL.Format("INSERT INTO orders (name,idcard, money ,qixian ,zhouhuankuan ,lixi, fuwufei, beizhu , starttime )  VALUES  ('%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s')",
			  strname,stridcard,strmoney,strqixian,strhuankuan,
			  strlilv,strfuwufei,strbeizhu,strstarttime);
SetDlgItemText (IDC_STATUS, "���ڴ�������...");

	if (connMain.IsConnected())
	{
		if (connMain.Execute (strSQL) == NULL)
		{	
			SetDlgItemText (IDC_STATUS, "���ڴ�����Ƭ...");
			strSQL.Format("select id from orders where idcard = '%s'",stridcard);
			/*MessageBox(strSQL);*/
			if (rsMain.Open (strSQL, &connMain) != RSOPEN_SUCCESS)
			/*if (connMain.Execute (strSQL) != NULL)*/
			{ SetDlgItemText (IDC_STATUS, "���ݴ���ɹ�,��Ƭ����ʧ��");	return;}
			
			LPTSTR idd = (LPTSTR)rsMain.GetColumnString(0);
			rsMain.Close();
			int len=m_list1.GetItemCount();//ȡ����
			CString sourpath; 
			CString newpath; 
			
			strSQL="insert into pictures (order_id,path) ";

// 			insert into pictures (order_id,path)   select '1','�ܺ�'  union all  select '1','�ܺ�2'  union all
// 			insert into pictures (order_id,path) VALUES ('1','�ܺ�'),VALUES ('1','�ܺ�1'),VALUES ('1','�ܺ�3')

			for(int row=0;row<len;row++)
			{
				newpath   = m_list1.GetItemText(row,1);
				if (CopyFile(m_list1.GetItemText(row,0),m_list1.GetItemText(row,1),false))
				{
					m_list1.SetItemText(row, 2, "�ɹ�"); 
					if (one)
					{	strSQL.Format("%s select '%s' ,'%s' ",strSQL,idd,  newpath.Right( newpath.GetLength()-(newpath.ReverseFind('\\')+1) )); one=false;}
					else
						strSQL.Format("%s union all select '%s' ,'%s' ",strSQL,idd, newpath.Right( newpath.GetLength()-(newpath.ReverseFind('\\')+1) ) );
					
				}
				else
					m_list1.SetItemText(row, 2, "ʧ��");

			}

			if (connMain.Execute (strSQL) == NULL)
				SetDlgItemText (IDC_STATUS, "������ȫ���...");
			else
				SetDlgItemText (IDC_STATUS, "����ͼƬʧ��...");
		}
		else
			SetDlgItemText (IDC_STATUS, "��������ʧ��...");

	}
	
//	CDialog::OnOK();
}

void CCreateOrder::OnButton1() 
{
	// TODO: Add your control notification handler code here
	srand((unsigned)time(NULL)); 
	CTime m_time;  
	CString newpath;
	char pFileName[MAX_PATH];   
	int nPos = GetCurrentDirectory( MAX_PATH, pFileName);    
	CString tt=pFileName;
	CString szFilters=L"ͼƬ (*.jpg; *.png; *.bmp)|*.jpg;*.png;*.bmp||";      //�����ļ�������  
	//�������ļ��Ի������Ĭ�ϵ��ļ���չ��Ϊ 
	CFileDialog fileDlg (TRUE, "", "",OFN_FILEMUSTEXIST|OFN_ALLOWMULTISELECT, szFilters, this);  
	//����DoModal()������ʾ���ļ��Ի���  
	if( fileDlg.DoModal ()==IDOK )  
	{    

		POSITION pos;  
		pos=fileDlg.GetStartPosition();//��ʼ�����û�ѡ���ļ��б�  
		while (pos!=NULL)  
		{  
			//m_list1.ResetContent();//����б�� m_ctlListΪ�б�ؼ�  
			CString filename=fileDlg.GetNextPathName(pos);  
			CString houzui = filename.Right(4);
			m_time=CTime::GetCurrentTime();             //��ȡ��ǰʱ������  
			newpath.Format("%s%s%s-%d%s",tt,"\\imgs\\",m_time.Format(_T("%Y-%m-%d-%H_%M_%S")),rand(),houzui);
			int i = m_list1.InsertItem(999, _T(""));
			m_list1.SetItemText(i, 0, filename);                     // ���õ�2��(����)  
			m_list1.SetItemText(i, 1, newpath);                      // ���õ�3��(����)  
			m_list1.SetItemText(i, 2, _T("�����"));                      // ���õ�4��(�Ա�)  
// 			if (!CopyFile(filename,newpath,false))
// 			{
// 				MessageBox(filename,_T("����ʧ��"),0);
// 			
// 			}
			//m_list1.AddString(filename);//���ļ�����ӵ��б�� 
		}  
	} 

}

void CCreateOrder::OnClickList1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	POSITION Pos = m_list1.GetFirstSelectedItemPosition();
    int nSelect = -1;
	
    while ( Pos )
    {
        nSelect = m_list1.GetNextSelectedItem(Pos);    //nSelect�ܻ�õڼ���
		CString s=m_list1.GetItemText(nSelect,0);
		ShellExecute(NULL, "open", s, NULL, NULL, SW_SHOW);
    }

	*pResult = 0;
}

void CCreateOrder::OnDoubleclickedButton1() 
{
	// TODO: Add your control notification handler code here

}

void CCreateOrder::OnGetdaystateMonthcalendar1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	*pResult = 0;
}

void CCreateOrder::OnSelectMonthcalendar1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	CTime refDateTime;
	m_CtrlDate.GetCurSel(refDateTime);
	m_starttime =refDateTime.Format(_T("%Y-%m-%d")); 
	UpdateData(false);
	m_CtrlDate.ShowWindow(SW_HIDE);
	GetDlgItem(IDC_EDIT_BEIZHU)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_EDIT_QIXIAN)->SetFocus();
	*pResult = 0;
}

void CCreateOrder::OnSetfocusEditStarttime() 
{
	// TODO: Add your control notification handler code here
	m_CtrlDate.ShowWindow(SW_SHOW);
	GetDlgItem(IDC_EDIT_BEIZHU)->ShowWindow(SW_HIDE);
}

void CCreateOrder::OnKillfocusEditStarttime() 
{
	m_CtrlDate.ShowWindow(SW_HIDE);
	GetDlgItem(IDC_EDIT_BEIZHU)->ShowWindow(SW_SHOW);	
}

BOOL CCreateOrder::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	return CDialog::Create(IDD, pParentWnd);
}

BOOL CCreateOrder::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_list1.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);      // ����ѡ��������  
	m_list1.InsertColumn(0, _T("Դ�ļ�(����鿴)"), LVCFMT_LEFT, 330);        // �����2�е�����  
	m_list1.InsertColumn(1, _T("Ŀ���ļ�"), LVCFMT_LEFT, 190);        // �����3�е�����         // �����4�е�����  
	m_list1.InsertColumn(2, _T("״̬"), LVCFMT_LEFT, 70);        // �����3�е�����         // �����4�е�����  
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
