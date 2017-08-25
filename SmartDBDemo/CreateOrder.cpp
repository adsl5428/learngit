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
	m_endtime = _T("");
	m_qixian = _T("");
	//}}AFX_DATA_INIT
}


void CCreateOrder::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCreateOrder)
	DDX_Control(pDX, IDC_LIST_HUANGKUAN, m_list_huankuan);
	DDX_Control(pDX, IDC_MONTHCALENDAR1, m_CtrlDate);
	DDX_Control(pDX, IDC_LIST1, m_list1);
	DDX_Text(pDX, IDC_EDIT_STARTTIME, m_starttime);
	DDX_Text(pDX, IDC_EDIT_ENDTIME, m_endtime);
	DDX_Text(pDX, IDC_EDIT_QIXIAN, m_qixian);
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
	ON_NOTIFY(NM_DBLCLK, IDC_LIST1, OnDblclkList1)
	ON_EN_SETFOCUS(IDC_EDIT_ENDTIME, OnSetfocusEditEndtime)
	ON_EN_KILLFOCUS(IDC_EDIT_ENDTIME, OnKillfocusEditEndtime)
	ON_EN_KILLFOCUS(IDC_EDIT_MONEY, OnKillfocusEditMoney)
	ON_EN_CHANGE(IDC_EDIT_LILV, OnChangeEditLilv)
	ON_EN_KILLFOCUS(IDC_EDIT_LILV, OnKillfocusEditLilv)
	ON_EN_CHANGE(IDC_EDIT_QIXIAN, OnChangeEditQixian)
	ON_EN_KILLFOCUS(IDC_EDIT_QIXIAN, OnKillfocusEditQixian)
	ON_EN_SETFOCUS(IDC_EDIT_QIXIAN, OnSetfocusEditQixian)
	ON_EN_CHANGE(IDC_EDIT_MONEY, OnChangeEditMoney)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCreateOrder message handlers
// void msgint(int a)
// {
// 	CString f;
// 	f.Format("%d",a);
// 	MessageBox(NULL,f,f,0);
// }
void CCreateOrder::OnOK() 
{
	// TODO: Add extra validation here
	bool one=true;
	CString strSQL;
	CString strbeizhu;
	CString strfuwufei;
	CString stridcard;
	CString strlilv;
	CString strmoney;
	CString strname;
	CString strqixian;
	CString strstarttime;
	CString strendtime;
	LPTSTR idd;
	GetDlgItemText (IDC_EDIT_BEIZHU, strbeizhu);
	GetDlgItemText (IDC_EDIT_FUWUFEI, strfuwufei);
	GetDlgItemText (IDC_EDIT_IDCARD, stridcard);
	GetDlgItemText (IDC_EDIT_LILV,strlilv );
	GetDlgItemText (IDC_EDIT_MONEY,strmoney );
	GetDlgItemText (IDC_EDIT_NAME,strname );
	GetDlgItemText (IDC_EDIT_QIXIAN,strqixian );
	GetDlgItemText (IDC_EDIT_STARTTIME, strstarttime);
	GetDlgItemText (IDC_EDIT_ENDTIME, strendtime);


strSQL.Format("INSERT INTO orders (name,idcard, money ,qixian  ,lixi, fuwufei, beizhu , starttime, endtime)  VALUES  ('%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s')",
			  strname,stridcard,strmoney,strqixian,
			  strlilv,strfuwufei,strbeizhu,strstarttime ,strendtime);
SetDlgItemText (IDC_STATUS, "正在存入数据...");


	if (connMain.IsConnected())
	{
		int len=m_list1.GetItemCount();//取行数
		if (connMain.Execute (strSQL) == NULL && len>0)
		{	
			SetDlgItemText (IDC_STATUS, "正在存入照片...");
			strSQL.Format("select id from orders where idcard = '%s'",stridcard);
			/*MessageBox(strSQL);*/
			if (rsMain.Open (strSQL, &connMain) != RSOPEN_SUCCESS)
			/*if (connMain.Execute (strSQL) != NULL)*/
			{ SetDlgItemText (IDC_STATUS, "数据存入成功,照片存入失败");	return;}
			
			idd = (LPTSTR)rsMain.GetColumnString(0);

			rsMain.Close();

			CString sourpath; 
			CString newpath; 
			
			strSQL="insert into pictures (order_id,path) ";

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
		
		one=true;
		len=m_list_huankuan.GetItemCount();//取行数
		if ( len>0)
		{	
			strSQL.Format("select id from orders where idcard = '%s'",stridcard);
			if (rsMain.Open (strSQL, &connMain) != RSOPEN_SUCCESS)
			{ 	return;}			
			idd = (LPTSTR)rsMain.GetColumnString(0);
			rsMain.Close();		

			CString temp = idd;
			SetDlgItemText (IDC_STATUS, "正在存入还款计划...");
		
			strSQL="insert into huankuans (qishu , time, money ,  order_id) select ";
			
			for(int row=0;row<len;row++)
			{
				if (one)
				{			
					for (int lie=0;lie<3;lie++)
					{
						CString vaule = m_list_huankuan.GetItemText(row,lie);
//						strSQL = strSQL+" "+vaule;	
						strSQL.Format("%s '%s', ",strSQL,vaule);
					}
					strSQL.Format("%s '%s' ",strSQL,temp);
					one = false;
				}
				else 
				{	
					strSQL.Format("%s union all select ",strSQL);
					for (int lie=0;lie<3;lie++)
					{
						CString vaule = m_list_huankuan.GetItemText(row,lie);
//						strSQL = strSQL+" "+vaule;	
						strSQL.Format("%s '%s', ",strSQL,vaule);
					}
					strSQL.Format("%s '%s' ",strSQL,temp);
				}
			
			}
			}
		if (connMain.Execute (strSQL) == NULL)
			SetDlgItemText (IDC_STATUS, "还款计划已全完成...");
		else
				SetDlgItemText (IDC_STATUS, "还款计划失败...");	
	}

//	SetDlgItemText (IDC_STATUS, "存储完成...");
	
//	CDialog::OnOK();
}

void CCreateOrder::OnButton1() 
{
	// TODO: Add your control notification handler code here
	srand((unsigned)time(NULL)); 
	CTime m_time;  
	CString newpath;

	CString path; 
	CString pFileName;
    GetModuleFileName(NULL,path.GetBufferSetLength(MAX_PATH+1),MAX_PATH); 
    path.ReleaseBuffer(); 
    int pos = path.ReverseFind('\\'); 
    CString tt = path.Left(pos); 

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
//			m_list1.AddString(filename);//将文件名添加到列表框 
		}  
	} 

}

void CCreateOrder::OnClickList1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here


// 	POSITION Pos = m_list1.GetFirstSelectedItemPosition();
//     int nSelect = -1;
// 	
//     while ( Pos )
//     {
//         nSelect = m_list1.GetNextSelectedItem(Pos);    //nSelect能获得第几行
// 		CString s=m_list1.GetItemText(nSelect,0);
// 		ShellExecute(NULL, "open", s, NULL, NULL, SW_SHOW);
//     }

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
	UpdateData(true);
	CString str;  
	CTime tm;  
	tm=CTime::GetCurrentTime();
//	str=tm.Format("%H:%M:%S");  
	str=tm.Format("12:00:00");  

	CString szStr;
	COleDateTime m_dSelRq  ;
	m_dSelRq = COleDateTime(((NMSELCHANGE*)pNMHDR)->stSelStart);  
	UINT nYear,nMonth,nDay;
	nYear   =  m_dSelRq.GetYear();
	nMonth  =  m_dSelRq.GetMonth();
	nDay    =  m_dSelRq.GetDay(); 
	szStr.Format(_T("%d-%d-%d"),nYear,nMonth,nDay);

	if (m_startorend==1)
	{
		m_starttime=szStr+" "+str;
	}
	if (m_startorend==2)
	{
		m_endtime=szStr+" "+str;
	}
	UpdateData(false);

	m_CtrlDate.ShowWindow(SW_HIDE);
	GetDlgItem(IDC_EDIT_BEIZHU)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_EDIT_QIXIAN)->SetFocus();
// 	if (m_startorend==1)
// 	{
// 		GetDlgItem(IDC_EDIT_ENDTIME)->SetFocus();
// 	}
// 	else if (m_startorend==2)
// 	{
// 		GetDlgItem(IDC_EDIT_QIXIAN)->SetFocus();
// 	}
	*pResult = 0;
}

void CCreateOrder::OnSetfocusEditStarttime() 
{
	// TODO: Add your control notification handler code here
	m_startorend=1;
	m_CtrlDate.ShowWindow(SW_SHOW);
	GetDlgItem(IDC_EDIT_BEIZHU)->ShowWindow(SW_HIDE);
}

void CCreateOrder::OnKillfocusEditStarttime() 
{
	m_CtrlDate.ShowWindow(SW_HIDE);
	GetDlgItem(IDC_EDIT_BEIZHU)->ShowWindow(SW_SHOW);
	qixian();
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

	m_list_huankuan.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);      // 整行选择、网格线  
	m_list_huankuan.InsertColumn(0, _T("期数"), LVCFMT_CENTER, 40);        // 插入第2列的列名  
	m_list_huankuan.InsertColumn(1, _T("还款日"), LVCFMT_CENTER, 110);        // 插入第3列的列名         // 插入第4列的列名  
	m_list_huankuan.InsertColumn(2, _T("还款金额"), LVCFMT_CENTER, 80);        // 插入第3列的列名         // 插入第4列的列名 
	m_list_huankuan.InsertColumn(3, _T("状态"), LVCFMT_CENTER, 60);        // 插入第3列的列名         // 插入第4列的列名  
	m_list_huankuan.InsertColumn(4, _T("备注"), LVCFMT_CENTER, 287);        // 插入第3列的列名         // 插入第4列的列名  

	CString str; //获取系统时间 　　	
	CTime tm;
	tm=CTime::GetCurrentTime();		
	str=tm.Format("%Y-%m-%d 12:00:00");

	SetDlgItemText(IDC_EDIT_IDCARD,"6666");
	SetDlgItemText(IDC_EDIT_MONEY,"100000");
	SetDlgItemText(IDC_EDIT_LILV,"5");
	SetDlgItemText(IDC_EDIT_STARTTIME,str);
//	SetDlgItemText(IDC_EDIT_ENDTIME,"2017-8-26 12:00:00");
	SetDlgItemText(IDC_EDIT_QIXIAN,"16");
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CCreateOrder::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN)  
	{  
		CWnd *mwnd = GetNextDlgTabItem (GetFocus());        //取得当前焦点控件的下一个控件的句柄  
		if (mwnd)  
		{  
			mwnd->SetFocus();        //设置下一件控件得到输入焦点  
			return TRUE;  
		}  
     }  
	return CDialog::PreTranslateMessage(pMsg);
}

void CCreateOrder::OnDblclkList1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: Add your control notification handler code here
	NM_LISTVIEW *pNMListView=(NM_LISTVIEW *)pNMHDR;
	int nItem=pNMListView->iItem;
	if(nItem>=0 && nItem<m_list1.GetItemCount())    //判断双击位置是否在有数据的列表项上面
	{
			POSITION Pos = m_list1.GetFirstSelectedItemPosition();
			int nSelect = -1;
			
			while ( Pos )
			{
				nSelect = m_list1.GetNextSelectedItem(Pos);    //nSelect能获得第几行
				CString s=m_list1.GetItemText(nSelect,0);
				ShellExecute(NULL, "open", s, NULL, NULL, SW_SHOW);
	   }
	}
	*pResult = 0;
}

void CCreateOrder::count()
{
	float ililv;
	int imoney,itianshu;
	CString strmoney,strlilv,strqixian,strtemp,strstart;
	GetDlgItemText(IDC_EDIT_MONEY,strmoney);
	GetDlgItemText(IDC_EDIT_LILV,strlilv);
	GetDlgItemText(IDC_EDIT_QIXIAN,strqixian);
	GetDlgItemText(IDC_EDIT_STARTTIME,strstart);
	if (strmoney.IsEmpty() || strlilv.IsEmpty() || strqixian.IsEmpty() || strstart.IsEmpty())
		return;

	m_list_huankuan.DeleteAllItems(); // 全部清空  
	imoney = _ttoi(strmoney);
	itianshu = _ttoi(strqixian)*7;
	ililv = (float)atof(strlilv)/10000;

	int qishu=itianshu/7;
	float zhouhuankuan = ((imoney*ililv*itianshu)+imoney)/qishu;
//	int zhouhuankuan = zonghuankua;
	

	
	int i=1;
	for (;i<=qishu;i++)
	{
		int x = m_list_huankuan.InsertItem(999, _T(""));
		strtemp.Format("%d",i);
		m_list_huankuan.SetItemText(x, 0, strtemp); 
		
		CTimeSpan m_timespan(7*(i-1),0,0,0); // 3天，4小时，5分，6秒
		int    nYear,    nMonth,    nDate,    nHour,    nMin,    nSec;   
		sscanf(strstart,    "%d-%d-%d    %d:%d:%d",    &nYear,    &nMonth,    &nDate,    &nHour,    &nMin,    &nSec);   
		CTime   s(nYear,    nMonth,    nDate,    nHour,    nMin,    nSec);
		s=s+m_timespan;
		strtemp = s.Format("%Y-%m-%d");
		m_list_huankuan.SetItemText(x, 1, strtemp);               

		strtemp.Format("%0.0f",zhouhuankuan);
		m_list_huankuan.SetItemText(x, 2, strtemp);              
	}

// 	int x = m_list_huankuan.InsertItem(999, _T(""));
// 	CTimeSpan m_timespan;	
// 
// 	strtemp.Format("%d",i+1);
// 	m_list_huankuan.SetItemText(x, 0, strtemp); 
// 	if (qishu == 1)
// 	{ CTimeSpan tp(zuihouyiqi,0,0,0);	m_timespan=tp; }// 3天，4小时，5分，6秒
// 	else 
// 	{CTimeSpan tp(7*(i-1)+zuihouyiqi,0,0,0);	m_timespan=tp;} // 3天，4小时，5分，6秒
// 	int    nYear,    nMonth,    nDate,    nHour,    nMin,    nSec;   
// 	sscanf(strstart,    "%d-%d-%d    %d:%d:%d",    &nYear,    &nMonth,    &nDate,    &nHour,    &nMin,    &nSec);   
// 	CTime   s(nYear,    nMonth,    nDate,    nHour,    nMin,    nSec);
// 	s=s+m_timespan;
// 	strtemp = s.Format("%Y-%m-%d");
// 	m_list_huankuan.SetItemText(x, 1, strtemp);               
// 	
// 	strtemp.Format("%d",rihuankuan*zuihouyiqi);
// 	m_list_huankuan.SetItemText(x, 2, strtemp);  

}

void CCreateOrder::OnSetfocusEditEndtime() 
{
	// TODO: Add your control notification handler code here
	m_startorend=2;
	m_CtrlDate.ShowWindow(SW_SHOW);
	GetDlgItem(IDC_EDIT_BEIZHU)->ShowWindow(SW_HIDE);
}

void CCreateOrder::OnKillfocusEditEndtime() 
{
	m_CtrlDate.ShowWindow(SW_HIDE);
	GetDlgItem(IDC_EDIT_BEIZHU)->ShowWindow(SW_SHOW);
	qixian();
}



void CCreateOrder::qixian()
{
	UpdateData(true);
// 	CString start,strqixian;
// 	GetDlgItemText(IDC_EDIT_STARTTIME,start);
// 	GetDlgItemText(IDC_EDIT_QIXIAN,strqixian);
	if (m_starttime.IsEmpty() || m_qixian.IsEmpty())
	{
		return ;
	}

	int    nYear,    nMonth,    nDate,    nHour,    nMin,    nSec;   
	sscanf(m_starttime,    "%d-%d-%d    %d:%d:%d",    &nYear,    &nMonth,    &nDate,    &nHour,    &nMin,    &nSec);   
	CTime   s(nYear,    nMonth,    nDate,    nHour,    nMin,    nSec);


// 	int    nYear1,    nMonth1,    nDate1,    nHour1,    nMin1,    nSec1;   
// 	sscanf(m_endtime,    "%d-%d-%d %d:%d:%d",    &nYear1,    &nMonth1,    &nDate1,    &nHour1,    &nMin1,    &nSec1);   
 	CTime   e;
 	CTimeSpan qixian(_ttoi(m_qixian)*7,0,0,0);
	e = s+qixian;
	m_endtime = e.Format("%Y-%m-%d %H:%M:%S");
// 	
// 	m_qixian.Format("%d",qixian.GetDays());
	UpdateData(FALSE);
}

void CCreateOrder::OnKillfocusEditMoney() 
{
	// TODO: Add your control notification handler code here
	count();
}

void CCreateOrder::OnChangeEditLilv() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	count();
}

void CCreateOrder::OnKillfocusEditLilv() 
{
	// TODO: Add your control notification handler code here
	count();
}

void CCreateOrder::OnChangeEditQixian() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	CString start;
	CString strqixian;
	CString strend;
	GetDlgItemText(IDC_EDIT_STARTTIME,start);
	GetDlgItemText(IDC_EDIT_QIXIAN,strqixian);
	int iqixian = _ttoi(strqixian)*7;
	int    nYear,    nMonth,    nDate,    nHour,    nMin,    nSec;   
	sscanf(start,    "%d-%d-%d    %d:%d:%d",    &nYear,    &nMonth,    &nDate,    &nHour,    &nMin,    &nSec);   
	CTime   s(nYear,    nMonth,    nDate,    nHour,    nMin,    nSec);
	CTimeSpan tian(iqixian,0,0,0);
	s=s+tian;
	strend = s.Format("%Y-%m-%d %H:%M:%S");
	SetDlgItemText(IDC_EDIT_ENDTIME,strend);
	count();
}

void CCreateOrder::OnKillfocusEditQixian() 
{
	// TODO: Add your control notification handler code here
	count();
}

void CCreateOrder::OnSetfocusEditQixian() 
{
	// TODO: Add your control notification handler code here
	count();
}

void CCreateOrder::OnChangeEditMoney() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	count();
}
