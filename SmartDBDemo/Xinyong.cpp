// Xinyong.cpp : implementation file
//

#include "stdafx.h"
#include "SmartDBDemo.h"
#include "Xinyong.h"
#include "SmartDB.h"

extern CSmartDB connMain;
extern CSmartDBRecordSet rsMain;
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
	m_beizhu = _T("");
	m_fuwufei = _T("");
	m_idcard = _T("");
	m_chuziren = _T("");
	m_jingbanren = _T("");
	m_name = _T("");
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
	DDX_Text(pDX, IDC_EDIT_BEIZHU, m_beizhu);
	DDX_Text(pDX, IDC_EDIT_FUWUFEI, m_fuwufei);
	DDX_Text(pDX, IDC_EDIT_IDCARD, m_idcard);
	DDX_Text(pDX, IDC_EDIT_CHUZIREN, m_chuziren);
	DDX_Text(pDX, IDC_EDIT_JINGBANREN, m_jingbanren);
	DDX_Text(pDX, IDC_EDIT_NAME, m_name);
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
	ON_EN_CHANGE(IDC_EDIT_STARTTIME, OnChangeEditStarttime)
	ON_EN_SETFOCUS(IDC_EDIT_STARTTIME, OnSetfocusEditStarttime)
	ON_EN_KILLFOCUS(IDC_EDIT_STARTTIME, OnKillfocusEditStarttime)
	ON_NOTIFY(MCN_SELCHANGE, IDC_MONTHCALENDAR1, OnSelchangeMonthcalendar1)
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST1, OnDblclkList1)
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
	if (strtemp == "��Ϣ")
	{
		m_qixiandanwei.SetCurSel(1);
		m_danwei.SetCurSel(1);
	}
	else if(strtemp == "��Ϣ")
	{
		m_qixiandanwei.SetCurSel(0);
		m_danwei.SetCurSel(0);
	}

	CString str; //��ȡϵͳʱ�� ����	
	CTime tm;
	tm=CTime::GetCurrentTime();		
	str=tm.Format("%Y-%m-%d 12:00:00");
	
	m_list1.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);      // ����ѡ��������  
	m_list1.InsertColumn(0, _T("Դ�ļ�(����鿴)"), LVCFMT_LEFT, 330);        // �����2�е�����  
	m_list1.InsertColumn(1, _T("Ŀ���ļ�"), LVCFMT_LEFT, 190);        // �����3�е�����         // �����4�е�����  
	m_list1.InsertColumn(2, _T("״̬"), LVCFMT_LEFT, 70);        // �����3�е�����         // �����4�е�����  
	
	m_list_huankuan.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);      // ����ѡ��������  
	m_list_huankuan.InsertColumn(0, _T("����"), LVCFMT_CENTER, 40);        // �����2�е�����  
	m_list_huankuan.InsertColumn(1, _T("������"), LVCFMT_CENTER, 110);        // �����3�е�����         // �����4�е�����  
	m_list_huankuan.InsertColumn(2, _T("�ƻ�����"), LVCFMT_CENTER, 80);        // �����3�е�����         // �����4�е����� 
	m_list_huankuan.InsertColumn(3, _T("ʵ�ʻ���"), LVCFMT_CENTER, 80);        // �����3�е�����         // �����4�е�����  
	m_list_huankuan.InsertColumn(4, _T("��ע"), LVCFMT_CENTER, 287);        // �����3�е�����         // �����4�е�����  

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
	if (strtemp == "��Ϣ")
	{
		m_qixiandanwei.SetCurSel(1);
		m_danwei.SetCurSel(1);
	}
	else if(strtemp == "��Ϣ")
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


	UpdateData(TRUE);   //�ؼ����µ�����


	if (m_money.IsEmpty() || m_lilv.IsEmpty() || m_qixian.IsEmpty() || m_starttime.IsEmpty())
		return ;
	m_jixiriqi.GetLBText(m_jixiriqi.GetCurSel(), strtemp);



	m_danwei.GetLBText(m_danwei.GetCurSel(), strtemp);
	if (strtemp=="�ٷ�")
		idanwei=100;
	else if (strtemp=="ǧ��")
		idanwei=1000;


	m_list_huankuan.DeleteAllItems();					// ȫ�����
	imoney = _ttoi(m_money);
	itianshu = _ttoi(m_qixian)*izhouqidanwei;

	m_qixiandanwei.GetLBText(m_qixiandanwei.GetCurSel(), strtemp);
	if (strtemp=="��")	
	{	
		izhouqidanwei=7;
		fzhouqililv = (float)atof(m_lilv)/idanwei*7;
	}
	else if (strtemp=="��")
	{	
		izhouqidanwei=30;
		fzhouqililv = (float)atof(m_lilv)/idanwei;
	}
//	msgint((int)fzhouqililv);
	

	iqishu=_ttoi(m_qixian);


	float qihuankuan;

	

	m_huankuanfangshi.GetLBText(m_huankuanfangshi.GetCurSel(), strtemp);
	if (strtemp=="�ȶϢ")
	{
		qihuankuan = ((imoney*fzhouqililv*iqishu)+imoney)/iqishu;
//		msgint((int)qihuankuan);
	}
	else if (strtemp=="��Ϣ��")
	{
		qihuankuan = imoney*fzhouqililv;
		iqishu--;
		xianxihouben = true;
	}
		

	if (iqishu==1)    //ֻ��һ�ڵĵ����
	{
	}

	else{
	int i=1;
	for (;i<=iqishu;i++)
	{
		int x = m_list_huankuan.InsertItem(999, _T(""));
		strtemp.Format("%d",i);
		m_list_huankuan.SetItemText(x, 0, strtemp);      //����
		
		int    nYear,    nMonth,    nDate,    nHour,    nMin,    nSec;   
		sscanf(m_starttime,    "%d-%d-%d    %d:%d:%d",    &nYear,    &nMonth,    &nDate,    &nHour,    &nMin,    &nSec);   
		CTime   s(nYear,    nMonth,    nDate,    nHour,    nMin,    nSec);


		CTimeSpan m_timespan(izhouqidanwei*(i-1),0,0,0); // 3�죬4Сʱ��5�֣�6��
		s=s+m_timespan;

		strtemp = s.Format("%Y-%m-%d");
		m_list_huankuan.SetItemText(x, 1, strtemp);               //������
		
		strtemp.Format("%0.0f",qihuankuan);
		m_list_huankuan.SetItemText(x, 2, strtemp);              //�ƻ�������
	}

	if (xianxihouben)
	{
		int x = m_list_huankuan.InsertItem(999, _T(""));
		strtemp.Format("%d",iqishu+1);
		m_list_huankuan.SetItemText(x, 0, strtemp);      //����
		
		CTimeSpan m_timespan(izhouqidanwei*(i-1),0,0,0); // 3�죬4Сʱ��5�֣�6��
		int    nYear,    nMonth,    nDate,    nHour,    nMin,    nSec;   
		sscanf(m_starttime,    "%d-%d-%d    %d:%d:%d",    &nYear,    &nMonth,    &nDate,    &nHour,    &nMin,    &nSec);   
		CTime   s(nYear,    nMonth,    nDate,    nHour,    nMin,    nSec);
		s=s+m_timespan;
		strtemp = s.Format("%Y-%m-%d");
		m_list_huankuan.SetItemText(x, 1, strtemp);               //������
		
		strtemp.Format("%0.0f",qihuankuan+imoney);
		m_list_huankuan.SetItemText(x, 2, strtemp);              //�ƻ�������
	}
	}

} 

void CXinyong::OnChangeEditQixian() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	countendtime();
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
void CXinyong::countendtime() 
{
	UpdateData(true);
	if (m_starttime.IsEmpty() || m_qixian.IsEmpty())
	{
		return ;
	}
	CString strtemp;
	float	fzhouqidanwei;
	m_qixiandanwei.GetLBText(m_qixiandanwei.GetCurSel(), strtemp);
	if (strtemp=="��")	
	{	
		fzhouqidanwei=7;
	}
	else if (strtemp=="��")
	{	
		fzhouqidanwei=30.5;
	}
	int    nYear,    nMonth,    nDate,    nHour,    nMin,    nSec;   
	sscanf(m_starttime,    "%d-%d-%d    %d:%d:%d",    &nYear,    &nMonth,    &nDate,    &nHour,    &nMin,    &nSec);   
	CTime   s(nYear,    nMonth,    nDate,    nHour,    nMin,    nSec);
	
	
	// 	int    nYear1,    nMonth1,    nDate1,    nHour1,    nMin1,    nSec1;   
	// 	sscanf(m_endtime,    "%d-%d-%d %d:%d:%d",    &nYear1,    &nMonth1,    &nDate1,    &nHour1,    &nMin1,    &nSec1);   
	CTime   e;
	CTimeSpan qixian(_ttoi(m_qixian)*fzhouqidanwei,0,0,0);
	e = s+qixian;
	m_endtime = e.Format("%Y-%m-%d %H:%M:%S");
	 	
	// 	m_qixian.Format("%d",qixian.GetDays());
	UpdateData(FALSE);
}

void CXinyong::OnChangeEditStarttime() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	countendtime();
}

void CXinyong::OnSetfocusEditStarttime() 
{
	// TODO: Add your control notification handler code here
	m_CtrlDate.ShowWindow(SW_SHOW);
	GetDlgItem(IDC_EDIT_BEIZHU)->ShowWindow(SW_HIDE);
}

void CXinyong::OnKillfocusEditStarttime() 
{
	// TODO: Add your control notification handler code here
		m_CtrlDate.ShowWindow(SW_HIDE);
	GetDlgItem(IDC_EDIT_BEIZHU)->ShowWindow(SW_SHOW);
}


void CXinyong::OnSelchangeMonthcalendar1(NMHDR* pNMHDR, LRESULT* pResult) 
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
	
	m_starttime=szStr+" "+str;
//	m_endtime=szStr+" "+str;
	
	UpdateData(false);
	
	m_CtrlDate.ShowWindow(SW_HIDE);
	GetDlgItem(IDC_EDIT_BEIZHU)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_EDIT_QIXIAN)->SetFocus();
	*pResult = 0;
}

void CXinyong::OnOK() 
{
	// TODO: Add extra validation here
		// TODO: Add extra validation here
	bool one=true;
	CString strSQL;
	CString strdanwei;
	CString strfenlei;
	CString strhuankuangfangshi;
	CString strjixiriqi;
	CString strqixiandanwei;

m_danwei.GetLBText(m_danwei.GetCurSel(),strdanwei );  //ǧ��/�ٷ�
m_fenlei.GetLBText(m_fenlei.GetCurSel(),strfenlei );  
m_huankuanfangshi.GetLBText(m_huankuanfangshi.GetCurSel(),strhuankuangfangshi );  
m_jixiriqi.GetLBText(m_jixiriqi.GetCurSel(), strjixiriqi);  // ��Ϣ/��Ϣ
m_qixiandanwei.GetLBText(m_qixiandanwei.GetCurSel(),strqixiandanwei ); // �� / ��
	LPTSTR idd;
	UpdateData(TRUE);
// 	GetDlgItemText (IDC_EDIT_BEIZHU, strbeizhu);
// 	GetDlgItemText (IDC_EDIT_FUWUFEI, strfuwufei);
// 	GetDlgItemText (IDC_EDIT_IDCARD, stridcard);
// 	GetDlgItemText (IDC_EDIT_LILV,strlilv );
// 	GetDlgItemText (IDC_EDIT_MONEY,strmoney );
// 	GetDlgItemText (IDC_EDIT_NAME,strname );
// 	GetDlgItemText (IDC_EDIT_QIXIAN,strqixian );
// 	GetDlgItemText (IDC_EDIT_STARTTIME, strstarttime);
// 	GetDlgItemText (IDC_EDIT_ENDTIME, strendtime);


strSQL.Format("INSERT INTO orders (name,type1, money,huankuanfangshi ,qixian ,qixiandanwei,jixizhouqi,zhanbi,lixi ,fuwufei, beizhu , starttime, endtime,jingbanren,chuziren,idcard) 	  VALUES  ('%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s','%s', '%s', '%s', '%s', '%s', '%s', '%s')", m_name,strfenlei,m_money,strhuankuangfangshi,m_qixian,strqixiandanwei,strjixiriqi,strdanwei, m_lilv,m_fuwufei,	  m_beizhu,m_starttime ,m_endtime,m_jingbanren,m_chuziren,m_idcard);

SetDlgItemText (IDC_STATUS, "���ڴ�������...");

	if (connMain.IsConnected())
	{
		int len=m_list1.GetItemCount();//ȡ����
		if (connMain.Execute (strSQL) == NULL && len>0)
		{	
			SetDlgItemText (IDC_STATUS, "���ڴ�����Ƭ...");
			strSQL.Format("select id from orders where idcard = '%s'",m_idcard);
			/*MessageBox(strSQL);*/
			if (rsMain.Open (strSQL, &connMain) != RSOPEN_SUCCESS)
			/*if (connMain.Execute (strSQL) != NULL)*/
			{ SetDlgItemText (IDC_STATUS, "���ݴ���ɹ�,��Ƭ����ʧ��");	return;}
			
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
		
		one=true;
		len=m_list_huankuan.GetItemCount();//ȡ����
		if ( len>0)
		{	
			strSQL.Format("select id from orders where idcard = '%s'",m_idcard);
			if (rsMain.Open (strSQL, &connMain) != RSOPEN_SUCCESS)
			{ 	return;}			
			idd = (LPTSTR)rsMain.GetColumnString(0);
			rsMain.Close();		

			CString temp = idd;
			SetDlgItemText (IDC_STATUS, "���ڴ��뻹��ƻ�...");
		
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
			SetDlgItemText (IDC_STATUS, "����ƻ���ȫ���...");
		else
				SetDlgItemText (IDC_STATUS, "����ƻ�ʧ��...");	
	}
//	CDialog::OnOK();
}

void CXinyong::OnButton1() 
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
			//			m_list1.AddString(filename);//���ļ�����ӵ��б�� 
		}  
	} 
}

void CXinyong::OnDblclkList1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	// TODO: Add your control notification handler code here
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: Add your control notification handler code here
	NM_LISTVIEW *pNMListView=(NM_LISTVIEW *)pNMHDR;
	int nItem=pNMListView->iItem;
	if(nItem>=0 && nItem<m_list1.GetItemCount())    //�ж�˫��λ���Ƿ��������ݵ��б�������
	{
		POSITION Pos = m_list1.GetFirstSelectedItemPosition();
		int nSelect = -1;
		
		while ( Pos )
		{
			nSelect = m_list1.GetNextSelectedItem(Pos);    //nSelect�ܻ�õڼ���
			CString s=m_list1.GetItemText(nSelect,0);
			ShellExecute(NULL, "open", s, NULL, NULL, SW_SHOW);
		}
	}
	*pResult = 0;
}
