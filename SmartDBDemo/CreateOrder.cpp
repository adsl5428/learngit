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
SetDlgItemText (IDC_STATUS, "正在存入数据...");

	if (connMain.IsConnected())
	{
		if (connMain.Execute (strSQL) == NULL)
		{	
			SetDlgItemText (IDC_STATUS, "正在存入照片...");
			strSQL.Format("select id from orders where idcard = '%s'",stridcard);
			/*MessageBox(strSQL);*/
			if (rsMain.Open (strSQL, &connMain) != RSOPEN_SUCCESS)
			/*if (connMain.Execute (strSQL) != NULL)*/
			{ SetDlgItemText (IDC_STATUS, "数据存入成功,照片存入失败");	return;}
			
			LPTSTR idd = (LPTSTR)rsMain.GetColumnString(0);
			rsMain.Close();
			int len=m_list1.GetItemCount();//取行数
			CString sourpath; 
			CString newpath; 
			
			strSQL="insert into pictures (order_id,path) ";

// 			insert into pictures (order_id,path)   select '1','周宏'  union all  select '1','周宏2'  union all
// 			insert into pictures (order_id,path) VALUES ('1','周宏'),VALUES ('1','周宏1'),VALUES ('1','周宏3')

			for(int row=0;row<len;row++)
			{
				newpath   = m_list1.GetItemText(row,1);
				if (CopyFile(m_list1.GetItemText(row,0),m_list1.GetItemText(row,1),false))
				{
					m_list1.SetItemText(row, 2, "成功"); 
					if (one)
					{	strSQL.Format("%s select '%s' ,'%s' ",strSQL,idd,  newpath.Right( newpath.GetLength()-(newpath.ReverseFind('\\')+1) )); one=false;}
					else
						strSQL.Format("%s union all select '%s' ,'%s' ",strSQL,idd, newpath.Right( newpath.GetLength()-(newpath.ReverseFind('\\')+1) ) );
					
				}
				else
					m_list1.SetItemText(row, 2, "失败");

			}

			if (connMain.Execute (strSQL) == NULL)
				SetDlgItemText (IDC_STATUS, "存入已全完成...");
			else
				SetDlgItemText (IDC_STATUS, "存入图片失败...");
		}
		else
			SetDlgItemText (IDC_STATUS, "存入数据失败...");

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
	CString szFilters=L"图片 (*.jpg; *.png; *.bmp)|*.jpg;*.png;*.bmp||";      //定义文件过滤器  
	//创建打开文件对话框对象，默认的文件扩展名为 
	CFileDialog fileDlg (TRUE, "", "",OFN_FILEMUSTEXIST|OFN_ALLOWMULTISELECT, szFilters, this);  
	//调用DoModal()函数显示打开文件对话框  
	if( fileDlg.DoModal ()==IDOK )  
	{    

		POSITION pos;  
		pos=fileDlg.GetStartPosition();//开始遍历用户选择文件列表  
		while (pos!=NULL)  
		{  
			//m_list1.ResetContent();//清空列表框 m_ctlList为列表控件  
			CString filename=fileDlg.GetNextPathName(pos);  
			CString houzui = filename.Right(4);
			m_time=CTime::GetCurrentTime();             //获取当前时间日期  
			newpath.Format("%s%s%s-%d%s",tt,"\\imgs\\",m_time.Format(_T("%Y-%m-%d-%H_%M_%S")),rand(),houzui);
			int i = m_list1.InsertItem(999, _T(""));
			m_list1.SetItemText(i, 0, filename);                     // 设置第2列(姓名)  
			m_list1.SetItemText(i, 1, newpath);                      // 设置第3列(年龄)  
			m_list1.SetItemText(i, 2, _T("待入库"));                      // 设置第4列(性别)  
// 			if (!CopyFile(filename,newpath,false))
// 			{
// 				MessageBox(filename,_T("复制失败"),0);
// 			
// 			}
			//m_list1.AddString(filename);//将文件名添加到列表框 
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
        nSelect = m_list1.GetNextSelectedItem(Pos);    //nSelect能获得第几行
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
	m_list1.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);      // 整行选择、网格线  
	m_list1.InsertColumn(0, _T("源文件(点击查看)"), LVCFMT_LEFT, 330);        // 插入第2列的列名  
	m_list1.InsertColumn(1, _T("目标文件"), LVCFMT_LEFT, 190);        // 插入第3列的列名         // 插入第4列的列名  
	m_list1.InsertColumn(2, _T("状态"), LVCFMT_LEFT, 70);        // 插入第3列的列名         // 插入第4列的列名  
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
