; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=COrder
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "SmartDBDemo.h"

ClassCount=8
Class1=CSmartDBDemoApp
Class2=CSmartDBDemoDlg
Class3=CAboutDlg

ResourceCount=8
Resource1=IDD_CREATE_DIALOG
Resource2=IDR_MAINFRAME
Resource3=IDD_ABOUTBOX
Resource4=IDD_DIALOG_ORDER
Resource5=IDD_LOGIN_DIALOG
Resource6=IDD_SMARTDBDEMO_DIALOG
Class4=Login
Resource7=IDD_SMARTDBDEMO_DIALOG (English (U.S.))
Class5=CLoginDlg
Class6=CCreateOrder
Class7=CXiangxi
Class8=COrder
Resource8=IDR_MENU_MAIN

[CLS:CSmartDBDemoApp]
Type=0
HeaderFile=SmartDBDemo.h
ImplementationFile=SmartDBDemo.cpp
Filter=N
LastObject=CSmartDBDemoApp

[CLS:CSmartDBDemoDlg]
Type=0
HeaderFile=SmartDBDemoDlg.h
ImplementationFile=SmartDBDemoDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=CSmartDBDemoDlg

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
ControlCount=17
Control1=IDC_STATIC,static,1073872896
Control2=IDC_EDIT_DBNAME,edit,1073807488
Control3=IDC_BTN_LOAD,button,1073807360
Control4=IDC_BTN_UNLOAD,button,1073807360
Control5=IDCANCEL,button,1342242816
Control6=IDC_STATIC,static,1073872896
Control7=IDC_LIST_TABLES,listbox,1344340225
Control8=IDC_STATIC,static,1073872896
Control9=IDC_LIST_DATA,SysListView32,1342242825
Control10=IDC_STATIC_SQL,static,1342308353
Control11=IDC_EDIT_QUERY,edit,1342242944
Control12=IDC_BTN_EXECUTE,button,1342242817
Control13=IDC_ADD,button,1342242816
Control14=IDC_EDIT_FIND_NAME,edit,1350631552
Control15=IDC_BUTTON1,button,1342242816
Control16=IDC_BUTTON2,button,1342242816
Control17=IDC_BUTTON3,button,1073807360

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

[DLG:IDD_SMARTDBDEMO_DIALOG (English (U.S.))]
Type=1
Class=CSmartDBDemoDlg
ControlCount=13
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
Control13=IDC_ADD,button,1342242816

[CLS:Login]
Type=0
HeaderFile=Login.h
ImplementationFile=Login.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC

[CLS:CLoginDlg]
Type=0
HeaderFile=LoginDlg.h
ImplementationFile=LoginDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CLoginDlg

[DLG:IDD_CREATE_DIALOG]
Type=1
Class=CCreateOrder
ControlCount=28
Control1=IDC_EDIT_NAME,edit,1342242944
Control2=IDC_EDIT_IDCARD,edit,1342242944
Control3=IDC_EDIT_MONEY,edit,1342242944
Control4=IDC_EDIT_LILV,edit,1342242944
Control5=IDC_EDIT_FUWUFEI,edit,1342242944
Control6=IDC_EDIT_STARTTIME,edit,1342242944
Control7=IDC_EDIT_QIXIAN,edit,1342242944
Control8=IDC_EDIT_BEIZHU,edit,1344344132
Control9=IDC_EDIT_ENDTIME,edit,1476460672
Control10=IDC_EDIT_HUANKUAN,edit,1073807488
Control11=IDC_MONTHCALENDAR1,SysMonthCal32,1073807376
Control12=IDOK,button,1342242817
Control13=IDCANCEL,button,1342242816
Control14=IDC_STATIC,static,1342308352
Control15=IDC_STATIC,static,1342308352
Control16=IDC_STATIC,static,1342308352
Control17=IDC_STATIC,static,1342308352
Control18=IDC_STATIC,static,1073872896
Control19=IDC_STATIC,static,1342308352
Control20=IDC_STATIC,static,1342308352
Control21=IDC_STATIC,static,1342308352
Control22=IDC_STATIC,static,1342308352
Control23=IDC_BUTTON1,button,1342242816
Control24=IDC_LIST1,SysListView32,1342242825
Control25=IDC_STATUS,static,1342308353
Control26=IDC_LIST_HUANGKUAN,SysListView32,1350631425
Control27=IDC_STATIC,static,1342308352
Control28=IDC_STATIC,static,1342308352

[CLS:CCreateOrder]
Type=0
HeaderFile=CreateOrder.h
ImplementationFile=CreateOrder.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=IDC_EDIT_LILV

[DLG:IDD_LOGIN_DIALOG]
Type=1
Class=CLoginDlg
ControlCount=4
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_EDIT1,edit,1350631585
Control4=IDC_MSG,static,1342308353

[CLS:CXiangxi]
Type=0
HeaderFile=Xiangxi.h
ImplementationFile=Xiangxi.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=IDC_LIST_TUPIAN

[DLG:IDD_DIALOG_ORDER]
Type=1
Class=COrder
ControlCount=28
Control1=IDC_EDIT_NAME,edit,1342242944
Control2=IDC_EDIT_IDCARD,edit,1342242944
Control3=IDC_EDIT_MONEY,edit,1342242944
Control4=IDC_EDIT_LILV,edit,1342242944
Control5=IDC_EDIT_FUWUFEI,edit,1342242944
Control6=IDC_EDIT_STARTTIME,edit,1342242944
Control7=IDC_EDIT_ENDTIME,edit,1476460672
Control8=IDC_EDIT_QIXIAN,edit,1342242944
Control9=IDC_EDIT_BEIZHU,edit,1344344132
Control10=IDC_EDIT_HUANKUAN,edit,1073807488
Control11=IDOK,button,1073807361
Control12=IDCANCEL,button,1342242816
Control13=IDC_STATIC,static,1342308352
Control14=IDC_STATIC,static,1342308352
Control15=IDC_STATIC,static,1342308352
Control16=IDC_STATIC,static,1342308352
Control17=IDC_STATIC,static,1073872896
Control18=IDC_STATIC,static,1342308352
Control19=IDC_STATIC,static,1342308352
Control20=IDC_STATIC,static,1342308352
Control21=IDC_STATIC,static,1342308352
Control22=IDC_BUTTON1,button,1342242816
Control23=IDC_LIST_TUPIAN,SysListView32,1342242825
Control24=IDC_STATUS,static,1342308353
Control25=IDC_LIST_HUANGKUAN,SysListView32,1350631425
Control26=IDC_STATIC,static,1342308352
Control27=IDC_STATIC,static,1342308352
Control28=IDC_EDIT_LIST,edit,1082196096

[CLS:COrder]
Type=0
HeaderFile=Order.h
ImplementationFile=Order.cpp
BaseClass=CDialog
Filter=D
LastObject=COrder
VirtualFilter=dWC

