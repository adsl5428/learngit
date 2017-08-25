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
	m_money = _T("");
	m_lilv = _T("");
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
	DDX_Control(pDX, IDC_LIST_HUANGKUAN, m_list_huankuan);
	DDX_Control(pDX, IDC_MONTHCALENDAR1, m_CtrlDate);
	DDX_Control(pDX, IDC_LIST1, m_list1);
	DDX_Text(pDX, IDC_EDIT_STARTTIME, m_starttime);
	DDX_Text(pDX, IDC_EDIT_ENDTIME, m_endtime);
	DDX_Text(pDX, IDC_EDIT_QIXIAN, m_qixian);
	DDX_Text(pDX, IDC_EDIT_MONEY, m_money);
	DDX_Text(pDX, IDC_EDIT_LILV, m_lilv);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CXinyong, CDialog)
	//{{AFX_MSG_MAP(CXinyong)
	ON_EN_CHANGE(IDC_EDIT_QIXIAN, OnChangeEditQixian)
	ON_CBN_EDITCHANGE(IDC_COMBO_JIXIRIQI, OnEditchangeComboJixiriqi)
	ON_CBN_SELCHANGE(IDC_COMBO_JIXIRIQI, OnSelchangeComboJixiriqi)
	ON_CBN_SELCHANGE(IDC_COMBO_HUANKUAN, OnSelchangeComboHuankuan)
	ON_EN_CHANGE(IDC_EDIT_LILV, OnChangeEditLilv)
	ON_EN_CHANGE(IDC_EDIT_MONEY, OnChangeEditMoney)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CXinyong message handlers
void msgint(int a)
{
	CString f;
	f.Format("%d",a);
	MessageBox(NULL,f,f,0);
}
BOOL CXinyong::OnInitDialog() 
{
	CDialog::OnInitDialog();
	// TODO: Add extra initialization here
	m_fenlei.SetCurSel(0);
	m_huankuanfangshi.SetCurSel(0);
	m_jixiriqi.SetCurSel(1);
	CString strtemp;
	m_jixiriqi.GetLBText(m_jixiriqi.GetCurSel(), strtemp);
	if (strtemp == "日息")
	{
		m_qixiandanwei.SetCurSel(1);
		m_danwei.SetCurSel(1);
	}
	else if(strtemp == "月息")
	{
		m_qixiandanwei.SetCurSel(0);
		m_danwei.SetCurSel(0);
	}

	CString str; //获取系统时间 　　	
	CTime tm;
	tm=CTime::GetCurrentTime();		
	str=tm.Format("%Y-%m-%d 12:00:00");
	
	m_list1.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);      // 整行选择、网格线  
	m_list1.InsertColumn(0, _T("源文件(点击查看)"), LVCFMT_LEFT, 330);        // 插入第2列的列名  
	m_list1.InsertColumn(1, _T("目标文件"), LVCFMT_LEFT, 190);        // 插入第3列的列名         // 插入第4列的列名  
	m_list1.InsertColumn(2, _T("状态"), LVCFMT_LEFT, 70);        // 插入第3列的列名         // 插入第4列的列名  
	
	m_list_huankuan.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);      // 整行选择、网格线  
	m_list_huankuan.InsertColumn(0, _T("期数"), LVCFMT_CENTER, 40);        // 插入第2列的列名  
	m_list_huankuan.InsertColumn(1, _T("还款日"), LVCFMT_CENTER, 110);        // 插入第3列的列名         // 插入第4列的列名  
	m_list_huankuan.InsertColumn(2, _T("计划还款"), LVCFMT_CENTER, 80);        // 插入第3列的列名         // 插入第4列的列名 
	m_list_huankuan.InsertColumn(3, _T("实际还款"), LVCFMT_CENTER, 80);        // 插入第3列的列名         // 插入第4列的列名  
	m_list_huankuan.InsertColumn(4, _T("备注"), LVCFMT_CENTER, 287);        // 插入第3列的列名         // 插入第4列的列名  

	SetDlgItemText(IDC_EDIT_IDCARD,"6666");
	SetDlgItemText(IDC_EDIT_MONEY,"100000");
	SetDlgItemText(IDC_EDIT_LILV,"5");
	SetDlgItemText(IDC_EDIT_STARTTIME,str);
	SetDlgItemText(IDC_EDIT_QIXIAN,"16");
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
int DateNum(int year,int month)
{
	int days[]={31,28,31,30,31,30,31,31,30,31,30,31};
	if((year%4==0&&year%100!=0)||year%400==0)
		days[1]=29;
	return days[month];
}
void CXinyong::liandong()
{
	CString strtemp;
	m_jixiriqi.GetLBText(m_jixiriqi.GetCurSel(), strtemp);
	if (strtemp == "日息")
	{
		m_qixiandanwei.SetCurSel(1);
		m_danwei.SetCurSel(1);
	}
	else if(strtemp == "月息")
	{
		m_qixiandanwei.SetCurSel(0);
		m_danwei.SetCurSel(0);
	}

}
void CXinyong::conut()
{
	float fzhouqililv;
	int imoney,itianshu,idanwei,izhouqidanwei,iqishu;
	CString strtemp;
	bool xianxihouben=false;


	UpdateData(TRUE);   //控件更新到变量

// 	GetDlgItemText(IDC_EDIT_MONEY,strmoney);
// 	GetDlgItemText(IDC_EDIT_LILV,strlilv);
// 	GetDlgItemText(IDC_EDIT_QIXIAN,strqixian);
// 	GetDlgItemText(IDC_EDIT_STARTTIME,strstart);
	if (m_money.IsEmpty() || m_lilv.IsEmpty() || m_qixian.IsEmpty() || m_starttime.IsEmpty())
		return ;
	m_jixiriqi.GetLBText(m_jixiriqi.GetCurSel(), strtemp);
	if (strtemp == "日息")
	{
		
	}
	else if(strtemp == "月息")
	{

	}


	m_danwei.GetLBText(m_danwei.GetCurSel(), strtemp);
	if (strtemp=="百分")
		idanwei=100;
	else if (strtemp=="千分")
		idanwei=1000;


	m_list_huankuan.DeleteAllItems();					// 全部清空
	imoney = _ttoi(m_money);
	itianshu = _ttoi(m_qixian)*izhouqidanwei;

	m_qixiandanwei.GetLBText(m_qixiandanwei.GetCurSel(), strtemp);
	if (strtemp=="周")	
	{	
		izhouqidanwei=7;
		fzhouqililv = (float)atof(m_lilv)/idanwei*7;
	}
	else if (strtemp=="月")
	{	
		izhouqidanwei=30;
		fzhouqililv = (float)atof(m_lilv)/idanwei;
	}
//	msgint((int)fzhouqililv);
	

	iqishu=_ttoi(m_qixian);


	float qihuankuan;

	

	m_huankuanfangshi.GetLBText(m_huankuanfangshi.GetCurSel(), strtemp);
	if (strtemp=="等额本息")
	{
		qihuankuan = ((imoney*fzhouqililv*iqishu)+imoney)/iqishu;
//		msgint((int)qihuankuan);
	}
	else if (strtemp=="先息后本")
	{
		qihuankuan = imoney*fzhouqililv;
		iqishu--;
		xianxihouben = true;
	}
		
	int i=1;
	for (;i<=iqishu;i++)
	{
		int x = m_list_huankuan.InsertItem(999, _T(""));
		strtemp.Format("%d",i);
		m_list_huankuan.SetItemText(x, 0, strtemp);      //期数
		
		int    nYear,    nMonth,    nDate,    nHour,    nMin,    nSec;   
		sscanf(m_starttime,    "%d-%d-%d    %d:%d:%d",    &nYear,    &nMonth,    &nDate,    &nHour,    &nMin,    &nSec);   
		CTime   s(nYear,    nMonth,    nDate,    nHour,    nMin,    nSec);


		CTimeSpan m_timespan(izhouqidanwei*(i-1),0,0,0); // 3天，4小时，5分，6秒
		s=s+m_timespan;

		strtemp = s.Format("%Y-%m-%d");
		m_list_huankuan.SetItemText(x, 1, strtemp);               //还款日
		
		strtemp.Format("%0.0f",qihuankuan);
		m_list_huankuan.SetItemText(x, 2, strtemp);              //计划还款金额
	}

	if (xianxihouben)
	{
		int x = m_list_huankuan.InsertItem(999, _T(""));
		strtemp.Format("%d",iqishu+1);
		m_list_huankuan.SetItemText(x, 0, strtemp);      //期数
		
		CTimeSpan m_timespan(izhouqidanwei*(i-1),0,0,0); // 3天，4小时，5分，6秒
		int    nYear,    nMonth,    nDate,    nHour,    nMin,    nSec;   
		sscanf(m_starttime,    "%d-%d-%d    %d:%d:%d",    &nYear,    &nMonth,    &nDate,    &nHour,    &nMin,    &nSec);   
		CTime   s(nYear,    nMonth,    nDate,    nHour,    nMin,    nSec);
		s=s+m_timespan;
		strtemp = s.Format("%Y-%m-%d");
		m_list_huankuan.SetItemText(x, 1, strtemp);               //还款日
		
		strtemp.Format("%0.0f",qihuankuan+imoney);
		m_list_huankuan.SetItemText(x, 2, strtemp);              //计划还款金额
	}
} 

void CXinyong::OnChangeEditQixian() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	conut();
}


void CXinyong::OnEditchangeComboJixiriqi() 
{
	// TODO: Add your control notification handler code here
conut();
}

void CXinyong::OnSelchangeComboJixiriqi() 
{
	// TODO: Add your control notification handler code here
	liandong();
	conut();
}

void CXinyong::OnSelchangeComboHuankuan() 
{
	// TODO: Add your control notification handler code here
	conut();
}

void CXinyong::OnChangeEditLilv() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	conut();
}

void CXinyong::OnChangeEditMoney() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	conut(); 
}
