// SmartDBDemoDlg.cpp : implementation file
// SMall Application Relational daTabase
//

#include "stdafx.h"
#include "SmartDBDemo.h"
#include "SmartDBDemoDlg.h"

#include <cderr.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//CSmartDB dbMain;

CSmartDB connMain;
CSmartDBRecordSet rsMain;

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSmartDBDemoDlg dialog

CSmartDBDemoDlg::CSmartDBDemoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSmartDBDemoDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSmartDBDemoDlg)
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSmartDBDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSmartDBDemoDlg)
	DDX_Control(pDX, IDC_BTN_LOAD, m_btnLoad);
	DDX_Control(pDX, IDC_STATIC_SQL, m_statSQL);
	DDX_Control(pDX, IDC_BTN_EXECUTE, m_btnExecute);
	DDX_Control(pDX, IDC_EDIT_QUERY, m_edtQuery);
	DDX_Control(pDX, IDC_LIST_TABLES, m_listTables);
	DDX_Control(pDX, IDC_LIST_DATA, m_listData);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CSmartDBDemoDlg, CDialog)
	//{{AFX_MSG_MAP(CSmartDBDemoDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_LOAD, OnBtnLoad)
	ON_LBN_SELCHANGE(IDC_LIST_TABLES, OnSelchangeListTables)
	ON_BN_CLICKED(IDC_BTN_UNLOAD, OnBtnUnload)
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_BTN_EXECUTE, OnBtnExecute)
	ON_EN_SETFOCUS(IDC_EDIT_QUERY, OnSetfocusEditQuery)
	ON_EN_KILLFOCUS(IDC_EDIT_QUERY, OnKillfocusEditQuery)
	ON_COMMAND(ID_FILE_OPEN, OnFileOpen)
	ON_COMMAND(ID_HELP_ABOUTSMARTSB, OnHelpAboutsmartsb)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSmartDBDemoDlg message handlers

BOOL CSmartDBDemoDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	SetDlgItemText (IDC_EDIT_DBNAME, "demo.db");

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CSmartDBDemoDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CSmartDBDemoDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CSmartDBDemoDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CSmartDBDemoDlg::OnBtnLoad() 
{
	// TODO: Add your control notification handler code here

	// Try to open connection to the database
	CString m_strDBName;
	GetDlgItemText(IDC_EDIT_DBNAME, m_strDBName);
	if (m_strDBName.GetLength() <= 0)
	{
		MessageBox (_T("No database name entered..."));
		return;
	}

	if (connMain.IsConnected())
		connMain.Close();

	OnBtnUnload();

	if (connMain.Connect (m_strDBName) == TRUE)
	{
		// Open SQLITE_MASTER table
		rsMain.Open ("SELECT * FROM SQLITE_MASTER WHERE Type='table'", &connMain);

		// Add table Name found in SQLITE_MASTER into list box
		INT nRecNum=0;
		while (!rsMain.IsEOF())
		{
			m_listTables.AddString((LPTSTR)rsMain.GetColumnString(1));

			rsMain.MoveNext();
			nRecNum++;
		}
		rsMain.Close();

	}
}

void CSmartDBDemoDlg::OnSelchangeListTables() 
{
	char strTable[128];
	CString strQuery;

	int nIndex=-1;

	// return if there is no selection for the list box
	nIndex = m_listTables.GetCurSel();
	if (nIndex < 0)
		return;

	m_listTables.GetText(nIndex, strTable);
	strQuery.Format("SELECT * FROM %s", strTable);

	ExecuteQueryAndShow (strQuery);
}

void CSmartDBDemoDlg::OnBtnUnload() 
{
	// TODO: Add your control notification handler code here
	if (connMain.IsConnected())
		connMain.Close();

	m_listTables.ResetContent();
	m_listData.DeleteAllItems();
	int nCols = m_listData.GetHeaderCtrl()->GetItemCount();
	for (int i = nCols; i > 0; i--)
		m_listData.DeleteColumn(i-1);
}

void CSmartDBDemoDlg::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);

	// TODO: Add your message handler code here
	m_listTables.MoveWindow(10, 68, 130, cy-118);
	m_listData.MoveWindow(150, 68, cx-160, cy-118);
	m_edtQuery.MoveWindow(10, cy-34, cx-110, 20);
	m_btnExecute.MoveWindow(cx-90, cy-34, 80, 25);
	m_statSQL.MoveWindow(10, cy-48, 80, 14);
}

void CSmartDBDemoDlg::OnBtnExecute() 
{
	// TODO: Add your control notification handler code here
	CString strSQL;
	GetDlgItemText (IDC_EDIT_QUERY, strSQL);

	strSQL.TrimLeft();
	strSQL.TrimRight();
	if (strSQL.GetLength() <= 0)
		return;

	if (connMain.IsConnected())
	{
		if (strSQL.Left(7).CompareNoCase ("SELECT ") == 0)
		{
			if (ExecuteQueryAndShow (strSQL) == -1)
				MessageBox(_T("Error while executing select query"));
		}
		else if (connMain.Execute (strSQL) == NULL)
			MessageBox (_T("Query Executed Succesfuly..."));
		else
			MessageBox (_T("Error while Query Execution..."));
	}
}

void CSmartDBDemoDlg::OnSetfocusEditQuery() 
{
	// TODO: Add your control notification handler code here
//	m_btnLoad.SetButtonStyle(BS_PUSHBUTTON);
//	m_btnExecute.SetButtonStyle(BS_DEFPUSHBUTTON);
}

void CSmartDBDemoDlg::OnKillfocusEditQuery() 
{
	// TODO: Add your control notification handler code here
//	m_btnExecute.SetButtonStyle(BS_PUSHBUTTON);
//	m_btnLoad.SetButtonStyle(BS_DEFPUSHBUTTON);
}

UINT CSmartDBDemoDlg::ExecuteQueryAndShow(LPCTSTR strSelectQuery)
{
	int nType;
	char * strTypeNames[] = {"Unknown", "INT", "FLOAT", "TEXT", "BLOB", "NULL"};
	CString strQuery;
	UINT i;
	UINT nRetVal = -1;

	int nIndex=-1;

	// Clear all previous results
	m_listData.DeleteAllItems();
	int nCols = m_listData.GetHeaderCtrl()->GetItemCount();
	for (i = nCols; i > 0; i--)
		m_listData.DeleteColumn(i-1);

	strQuery = strSelectQuery;
	strQuery.TrimLeft();
	strQuery.TrimRight();
	// continue only if it is a select query
	if (strQuery.Left(7).CompareNoCase ("SELECT ") != 0)
		return nRetVal;

	// Try to open a table with SELECT statment
	if (rsMain.Open (strQuery, &connMain) != RSOPEN_SUCCESS)
		return nRetVal;

	// Add list of fields from table into list box
	for (i=0; i < rsMain.FieldsCount(); i++)
	{
		CString strBuffer;
		nType = rsMain.GetFieldType(i);
		strBuffer.Format("%s (%s)", rsMain.GetFieldName(i), strTypeNames[nType]);
		m_listData.InsertColumn(i, strBuffer, LVCFMT_LEFT, 100);
	}

	LVITEM lvItem;

	INT nRecNum=0;
	while (!rsMain.IsEOF())
	{
		for (i=0; i < rsMain.FieldsCount(); i++)
		{
			lvItem.mask = LVIF_TEXT;
			lvItem.iItem = nRecNum;
			lvItem.iSubItem = i;
			lvItem.pszText = (LPTSTR)rsMain.GetColumnString(i);

			if (i == 0)
				m_listData.InsertItem(&lvItem);
			else
				m_listData.SetItem(&lvItem);
		}
		rsMain.MoveNext();
		nRecNum++;
	}
	nRetVal = rsMain.RecordCount();
	rsMain.Close();

	return nRetVal;
}

void CSmartDBDemoDlg::OnFileOpen() 
{
	// TODO: Add your command handler code here
	char strFileName[128] = {0, 0};
	OPENFILENAME opFName;	// = new OPENFILENAME;

	ZeroMemory (&opFName, sizeof (OPENFILENAME));
	opFName.lpstrDefExt = "*.db";
	opFName.lStructSize = sizeof (opFName);
	opFName.hwndOwner = NULL;
	opFName.lpstrFilter = "*.db\0\0";
	opFName.lpstrFile = strFileName;
	opFName.Flags = OFN_EXPLORER;
	GetOpenFileName (&opFName);

	switch (CommDlgExtendedError ())
	{
		case CDERR_DIALOGFAILURE:
			MessageBox ("CDERR_DIALOGFAILURE");
			break;
		case CDERR_FINDRESFAILURE:
			MessageBox ("CDERR_FINDRESFAILURE");
			break;
		case CDERR_NOHINSTANCE:
			MessageBox ("CDERR_NOHINSTANCE");
			break;
		case CDERR_INITIALIZATION:
			MessageBox ("CDERR_INITIALIZATION");
			break;
		case CDERR_NOHOOK:
			MessageBox ("CDERR_NOHOOK");
			break;
		case CDERR_LOCKRESFAILURE:
			MessageBox ("CDERR_LOCKRESFAILURE");
			break;
		case CDERR_NOTEMPLATE:
			MessageBox ("CDERR_NOTEMPLATE");
			break;
		case CDERR_LOADRESFAILURE:
			MessageBox ("CDERR_LOADRESFAILURE");
			break;
		case CDERR_STRUCTSIZE:
			MessageBox ("CDERR_STRUCTSIZE");
			break;
		case CDERR_LOADSTRFAILURE:
			MessageBox ("CDERR_LOADSTRFAILURE");
			break;
		case FNERR_BUFFERTOOSMALL:
			MessageBox ("FNERR_BUFFERTOOSMALL");
			break;
		case CDERR_MEMALLOCFAILURE:
			MessageBox ("CDERR_MEMALLOCFAILURE");
			break;
		case FNERR_INVALIDFILENAME:
			MessageBox ("FNERR_INVALIDFILENAME");
			break;
		case CDERR_MEMLOCKFAILURE:
			MessageBox ("CDERR_MEMLOCKFAILURE");
			break;
		case FNERR_SUBCLASSFAILURE:
			MessageBox ("FNERR_SUBCLASSFAILURE");
			break;
	}

//	delete opFName;
}

void CSmartDBDemoDlg::OnHelpAboutsmartsb() 
{
	// TODO: Add your command handler code here
	CAboutDlg dlgAbout;
	dlgAbout.DoModal();
}
