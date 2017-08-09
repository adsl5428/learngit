; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CSmartDBDemoDlg
LastTemplate=CWinThread
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "SmartDBDemo.h"

ClassCount=3
Class1=CSmartDBDemoApp
Class2=CSmartDBDemoDlg
Class3=CAboutDlg

ResourceCount=7
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Resource3=IDD_SMARTDBDEMO_DIALOG
Resource4=IDR_MENU_MAIN
Resource5=IDD_ABOUTBOX (English (U.S.))
Resource6=IDD_SMARTDBDEMO_DIALOG (English (U.S.))
Resource7=IDR_MENU_MAIN (English (U.S.))

[CLS:CSmartDBDemoApp]
Type=0
HeaderFile=SmartDBDemo.h
ImplementationFile=SmartDBDemo.cpp
Filter=N

[CLS:CSmartDBDemoDlg]
Type=0
HeaderFile=SmartDBDemoDlg.h
ImplementationFile=SmartDBDemoDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=ID_HELP_ABOUTSMARTSB

[CLS:CAboutDlg]
Type=0
HeaderFile=SmartDBDemoDlg.h
ImplementationFile=SmartDBDemoDlg.cpp
Filter=D
LastObject=CAboutDlg

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=5
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889
Control5=IDC_STATIC,static,1342308352

[DLG:IDD_SMARTDBDEMO_DIALOG]
Type=1
Class=CSmartDBDemoDlg
ControlCount=12
Control1=IDC_STATIC,static,1342308352
Control2=IDC_EDIT_DBNAME,edit,1342242944
Control3=IDC_BTN_LOAD,button,1342242816
Control4=IDC_BTN_UNLOAD,button,1342242816
Control5=IDCANCEL,button,1342242816
Control6=IDC_STATIC,static,1342308352
Control7=IDC_LIST_TABLES,listbox,1344340225
Control8=IDC_STATIC,static,1342308352
Control9=IDC_LIST_DATA,SysListView32,1342242821
Control10=IDC_STATIC_SQL,static,1342308352
Control11=IDC_EDIT_QUERY,edit,1342242944
Control12=IDC_BTN_EXECUTE,button,1342242817

[MNU:IDR_MENU_MAIN]
Type=1
Class=?
Command1=ID_FILE_OPEN
Command2=ID_FILE_CLOSE
Command3=ID_FILE_EXIT
Command4=ID_OPTIONS_COMPACTDATABASE
Command5=ID_OPTIONS_REPAIRDATABASE
Command6=ID_OPTIONS_SETTINGS
Command7=ID_HELP_ABOUTSMARTSB
CommandCount=7

[DLG:IDD_ABOUTBOX (English (U.S.))]
Type=1
Class=?
ControlCount=5
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889
Control5=IDC_STATIC,static,1342308352

[DLG:IDD_SMARTDBDEMO_DIALOG (English (U.S.))]
Type=1
Class=?
ControlCount=12
Control1=IDC_STATIC,static,1342308352
Control2=IDC_EDIT_DBNAME,edit,1342242944
Control3=IDC_BTN_LOAD,button,1342242816
Control4=IDC_BTN_UNLOAD,button,1342242816
Control5=IDCANCEL,button,1342242816
Control6=IDC_STATIC,static,1342308352
Control7=IDC_LIST_TABLES,listbox,1344340225
Control8=IDC_STATIC,static,1342308352
Control9=IDC_LIST_DATA,SysListView32,1342242821
Control10=IDC_STATIC_SQL,static,1342308352
Control11=IDC_EDIT_QUERY,edit,1342242944
Control12=IDC_BTN_EXECUTE,button,1342242817

[MNU:IDR_MENU_MAIN (English (U.S.))]
Type=1
Class=?
Command1=ID_FILE_OPEN
Command2=ID_FILE_CLOSE
Command3=ID_FILE_EXIT
Command4=ID_OPTIONS_COMPACTDATABASE
Command5=ID_OPTIONS_REPAIRDATABASE
Command6=ID_OPTIONS_SETTINGS
Command7=ID_HELP_ABOUTSMARTSB
CommandCount=7

