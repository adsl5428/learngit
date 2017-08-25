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
SetDlgItemText (IDC_STATUS, "���ڴ�������...");


	if (connMain.IsConnected())
	{
		int len=m_list1.GetItemCount();//ȡ����
		if (connMain.Execute (strSQL) == NULL && len>0)
		{	
			SetDlgItemText (IDC_STATUS, "���ڴ�����Ƭ...");
			strSQL.Format("select id from orders where idcard = '%s'",stridcard);
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
			strSQL.Format("select id from orders where idcard = '%s'",stridcard);
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

//	SetDlgItemText (IDC_STATUS, "�洢���...");
	
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

void CCreateOrder::OnClickList1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here


// 	POSITION Pos = m_list1.GetFirstSelectedItemPosition();
//     int nSelect = -1;
// 	
//     while ( Pos )
//     {
//         nSelect = m_list1.GetNextSelectedItem(Pos);    //nSelect�ܻ�õڼ���
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
	m_list1.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);      // ����ѡ��������  
	m_list1.InsertColumn(0, _T("Դ�ļ�(����鿴)"), LVCFMT_LEFT, 330);        // �����2�е�����  
	m_list1.InsertColumn(1, _T("Ŀ���ļ�"), LVCFMT_LEFT, 190);        // �����3�е�����         // �����4�е�����  
	m_list1.InsertColumn(2, _T("״̬"), LVCFMT_LEFT, 70);        // �����3�е�����         // �����4�е�����  

	m_list_huankuan.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);      // ����ѡ��������  
	m_list_huankuan.InsertColumn(0, _T("����"), LVCFMT_CENTER, 40);        // �����2�е�����  
	m_list_huankuan.InsertColumn(1, _T("������"), LVCFMT_CENTER, 110);        // �����3�е�����         // �����4�е�����  
	m_list_huankuan.InsertColumn(2, _T("������"), LVCFMT_CENTER, 80);        // �����3�е�����         // �����4�е����� 
	m_list_huankuan.InsertColumn(3, _T("״̬"), LVCFMT_CENTER, 60);        // �����3�е�����         // �����4�е�����  
	m_list_huankuan.InsertColumn(4, _T("��ע"), LVCFMT_CENTER, 287);        // �����3�е�����         // �����4�е�����  

	CString str; //��ȡϵͳʱ�� ����	
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
		CWnd *mwnd = GetNextDlgTabItem (GetFocus());        //ȡ�õ�ǰ����ؼ�����һ���ؼ��ľ��  
		if (mwnd)  
		{  
			mwnd->SetFocus();        //������һ���ؼ��õ����뽹��  
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

	m_list_huankuan.DeleteAllItems(); // ȫ�����  
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
		
		CTimeSpan m_timespan(7*(i-1),0,0,0); // 3�죬4Сʱ��5�֣�6��
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
// 	{ CTimeSpan tp(zuihouyiqi,0,0,0);	m_timespan=tp; }// 3�죬4Сʱ��5�֣�6��
// 	else 
// 	{CTimeSpan tp(7*(i-1)+zuihouyiqi,0,0,0);	m_timespan=tp;} // 3�죬4Сʱ��5�֣�6��
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
