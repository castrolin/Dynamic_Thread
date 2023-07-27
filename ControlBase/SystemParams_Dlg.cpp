// SystemParamsDlg.cpp : 實作檔
//

#include "stdafx.h"
#include "SystemParams_Dlg.h"


// CSystemParamsDlg 對話方塊

IMPLEMENT_DYNAMIC(CSystemParamsDlg, CDialog)
	CSystemParamsDlg::CSystemParamsDlg(CSystemParams *SystemParams, CWnd* pParent /*=NULL*/)
	: CDialog(CSystemParamsDlg::IDD, pParent)
{
	HINSTANCE ORG = AfxGetResourceHandle();
#ifdef _DEBUG
	HINSTANCE ControlBaseInstanceHandle = GetModuleHandle("..\\Debug\\ControlBase.dll");
#elif
	HINSTANCE ControlBaseInstanceHandle = GetModuleHandle("..\\Release\\ControlBase.dll");
#endif
	AfxSetResourceHandle(ControlBaseInstanceHandle);

	this->Create(IDD_DIALOG_SYSPARAMSET, pParent);

	m_SystemParams = SystemParams;

	TCHAR tcPath[MAX_PATH];
	TCHAR tcDriver[MAX_PATH];
	TCHAR tcDir[MAX_PATH];

	::GetModuleFileName(AfxGetInstanceHandle(), tcPath, MAX_PATH);
	_tsplitpath(tcPath, tcDriver, tcDir, NULL, NULL);

	Project_Path.Format("%s%s", tcDriver, tcDir);

	m_Base_Row = 0;
	m_Base_Col = 0;

	AfxSetResourceHandle(ORG);

}

CSystemParamsDlg::~CSystemParamsDlg()
{
	m_Font.DeleteObject();
}

void CSystemParamsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_LIST_SYSTEM_MACHINE_PROC, m_ParamList);

	DDX_Control(pDX, IDC_CHECK_SYSTEMPARAM_INTERLOCK_CHECK, m_InterLockCheck);

}


BEGIN_MESSAGE_MAP(CSystemParamsDlg, CDialog)

	ON_NOTIFY(NM_CLICK, IDC_LIST_SYSTEM_MACHINE_PROC, OnNMClickGrid)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_SYSTEM_MACHINE_PROC, OnNMDbClickGrid)

	ON_MESSAGE(CWM_SYS_UPDATE_LANG, OnMessageChangeLang)
	ON_BN_CLICKED(IDC_BTN_SAVESETTING,   OnBnClickedButtonSave)
	ON_WM_SHOWWINDOW()
	ON_BN_CLICKED(IDC_BUTTON_TODAY_PRODUCTS_CLEAR, &CSystemParamsDlg::OnBnClickedButtonTodayProductsClear)
	ON_BN_CLICKED(IDC_BUTTON_TOTAL_PRODUCTS_CLEAR, &CSystemParamsDlg::OnBnClickedButtonTotalProductsClear)
	ON_BN_CLICKED(IDC_BTN_RESET_SETTING, &CSystemParamsDlg::OnBnClickedBtnResetSetting)

	ON_BN_CLICKED(IDC_CHECK_SYSTEMPARAM_INTERLOCK_CHECK, &CSystemParamsDlg::OnBnClickedCheckSystemparamInterlockCheck)
END_MESSAGE_MAP()


// CSystemParamsDlg 訊息處理常式

BOOL CSystemParamsDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	CFont * pFont = GetFont();
	LOGFONT lf;
	pFont->GetLogFont( &lf );
	lf.lfWeight = FW_BOLD;
	m_Font.CreateFontIndirect( &lf );

	SendMessageToDescendants( WM_SETFONT, (WPARAM) m_Font.m_hObject );

	m_ParamList.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES |LVS_EX_FLATSB);
	m_ParamList.InsertColumn(0,	_T("No."),	LVCFMT_CENTER, 45, 2);
	m_ParamList.InsertColumn(1,	_T("Parameters"),	LVCFMT_LEFT, 300, 2);
	m_ParamList.InsertColumn(2,	_T("Value"),	LVCFMT_LEFT, 440, 2);

	for(int x = 0; x < 30; x ++)
		m_ParamList.InsertItem(x, FormatString("%02d", x + 1));

	
	m_ParamList.SetItemText(0, 1, "AutoLogoutTime");
	m_ParamList.SetItemText(1, 1, "DummyHardware");
	m_ParamList.SetItemText(2, 1, "DummyCamera");
	m_ParamList.SetItemText(3, 1, "AlwaysSaveImage");
	m_ParamList.SetItemText(4, 1, "LogFilePath");
	m_ParamList.SetItemText(5, 1, "ImageFilePath");
	m_ParamList.SetItemText(6, 1, "ImageFilePath_Sticker");
	m_ParamList.SetItemText(7, 1, "EpsonRC_Address");
	m_ParamList.SetItemText(8, 1, "EpsonRC_Port");
	m_ParamList.SetItemText(9, 1, "EpsonRC_Speed_Auto(%)");
	m_ParamList.SetItemText(10, 1, "EpsonRC_Speed_Manual(%)");
	m_ParamList.SetItemText(11, 1, "EpsonRC_CheckTimeout_Fork(sec)");
	m_ParamList.SetItemText(12, 1, "EpsonRC_CheckTimeout_Handshake(sec)");
	m_ParamList.SetItemText(13, 1, "CCD_Calibrate_Distance(mm)");
	m_ParamList.SetItemText(14, 1, "CCD_Calibrate_Degree(Deg)");
	m_ParamList.SetItemText(15, 1, "CCD_Calibrate_Sticker_Distance(mm)");
	m_ParamList.SetItemText(16, 1, "CCD_Calibrate_Sticker_Degree(Deg)");
	m_ParamList.SetItemText(17, 1, "OverRange_X(mm)");
	m_ParamList.SetItemText(18, 1, "OverRange_Y(mm)");
	m_ParamList.SetItemText(19, 1, "OverRange_T(Deg)");
	m_ParamList.SetItemText(20, 1, "OverRange_Sticker_X(mm)");
	m_ParamList.SetItemText(21, 1, "OverRange_Sticker_Y(mm)");
	m_ParamList.SetItemText(22, 1, "OverRange_Sticker_T(Deg)");
	m_ParamList.SetItemText(23, 1, "b_ManualCheckList");
	m_ParamList.SetItemText(24, 1, "IN_CV_Timeout");
	m_ParamList.SetItemText(25, 1, "OUT_CV_Timeout");
	m_ParamList.SetItemText(26, 1, "IN_CV_Delay");
	m_ParamList.SetItemText(27, 1, "OUT_CV_Delay");
	m_ParamList.SetItemText(28, 1, "PuttingMode 0=180 Deg, 1=0 Deg");
	m_ParamList.SetItemText(29, 1, "ByPassMode");


	RECT rect;
	rect.left = 0;
	rect.top = 0;
	rect.bottom = 15;
	rect.right = 200;

	m_Base_EditItem.Create(WS_CHILD | ES_LEFT | WS_BORDER | ES_AUTOHSCROLL | ES_WANTRETURN | ES_MULTILINE, rect, GetDlgItem(IDC_LIST_SYSTEM_MACHINE_PROC), IDC_MY_LIST_EDITBOX);
	m_Base_EditItem.SetFont(&m_Font);

	m_Base_ComboBoxItem.Create(WS_CHILD| CBS_DROPDOWN | CBS_HASSTRINGS | WS_VSCROLL, rect, GetDlgItem(IDC_LIST_SYSTEM_MACHINE_PROC), IDC_MY_LIST_COMBOBOX);
	m_Base_ComboBoxItem.SetFont(&m_Font);

	m_InterLockCheck.SetIcon(IDI_ICON_MIN_LED_GREEN,IDI_ICON_MIN_LED_NONE);
	m_InterLockCheck.OffsetColor(CButtonST::BTNST_COLOR_BK_IN, 30);
	m_InterLockCheck.SetColor(CButtonST::BTNST_COLOR_FG_IN, RGB(0, 0, 255));
	m_InterLockCheck.SetFont(&m_Font);
	m_InterLockCheck.SetAlwaysTrack(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX 屬性頁應傳回 FALSE
}

long CSystemParamsDlg::OnMessageChangeLang( WPARAM wparam, LPARAM lparam )
{
	CString DlgName = "SystemParamsDlg";

	std::vector<CString>ButtonList;
	std::vector<CString>StaticList;

	ButtonList = LanguageCtrl->GetInterfaceButtonNameList(DlgName, (UINT)wparam);
	StaticList = LanguageCtrl->GetInterfaceStaticNameList(DlgName, (UINT)wparam);

	GetDlgItem(IDC_STATIC_SYSTEM_PARAM_CTRL)->SetWindowText(StaticList.at(0));
	GetDlgItem(IDC_GROUP_STARTMETHOD2)->SetWindowText(StaticList.at(1));
	GetDlgItem(IDC_GROUP_STARTMETHOD3)->SetWindowText(StaticList.at(2));
	GetDlgItem(IDC_GROUP_STARTMETHOD4)->SetWindowText(StaticList.at(3));

	GetDlgItem(IDC_STATIC_ENGINEER_NAME)->SetWindowText(StaticList.at(5));
	GetDlgItem(IDC_STATIC_PHONE)->SetWindowText(StaticList.at(6));

	GetDlgItem(IDC_BTN_SAVESETTING)->SetWindowText(ButtonList.at(0));
	GetDlgItem(IDC_BUTTON_TODAY_PRODUCTS_CLEAR)->SetWindowText(ButtonList.at(9));
	GetDlgItem(IDC_BUTTON_TOTAL_PRODUCTS_CLEAR)->SetWindowText(ButtonList.at(10));
	GetDlgItem(IDC_BTN_RESET_SETTING)->SetWindowText(ButtonList.at(11));

	switch((UINT)wparam)
	{
	case SYSTEM_LANGUAGE_EN:
		m_ParamList.SetItemText(0, 1, "AutoLogoutTime");
		m_ParamList.SetItemText(1, 1, "DummyHardware");
		m_ParamList.SetItemText(2, 1, "DummyCamera");
		m_ParamList.SetItemText(3, 1, "AlwaysSaveImage");
		m_ParamList.SetItemText(4, 1, "LogFilePath");
		m_ParamList.SetItemText(5, 1, "ImageFilePath");
		m_ParamList.SetItemText(6, 1, "ImageFilePath_Sticker");
		m_ParamList.SetItemText(7, 1, "EpsonRC_Address");
		m_ParamList.SetItemText(8, 1, "EpsonRC_Port");
		m_ParamList.SetItemText(9, 1, "EpsonRC_Speed_Auto(%)");
		m_ParamList.SetItemText(10, 1, "EpsonRC_Speed_Manual(%)");
		m_ParamList.SetItemText(11, 1, "EpsonRC_CheckTimeout_Fork(sec)");
		m_ParamList.SetItemText(12, 1, "EpsonRC_CheckTimeout_Handshake(sec)");
		m_ParamList.SetItemText(13, 1, "CCD_Calibrate_Distance(mm)");
		m_ParamList.SetItemText(14, 1, "CCD_Calibrate_Degree(Deg)");
		m_ParamList.SetItemText(15, 1, "CCD_Calibrate_Sticker_Distance(mm)");
		m_ParamList.SetItemText(16, 1, "CCD_Calibrate_Sticker_Degree(Deg)");
		m_ParamList.SetItemText(17, 1, "OverRange_X(mm)");
		m_ParamList.SetItemText(18, 1, "OverRange_Y(mm)");
		m_ParamList.SetItemText(19, 1, "OverRange_T(Deg)");
		m_ParamList.SetItemText(20, 1, "OverRange_Sticker_X(mm)");
		m_ParamList.SetItemText(21, 1, "OverRange_Sticker_Y(mm)");
		m_ParamList.SetItemText(22, 1, "OverRange_Sticker_T(Deg)");
		m_ParamList.SetItemText(23, 1, "b_ManualCheckList");
		m_ParamList.SetItemText(24, 1, "IN_CV_Timeout");
		m_ParamList.SetItemText(25, 1, "OUT_CV_Timeout");
		m_ParamList.SetItemText(26, 1, "IN_CV_Delay");
		m_ParamList.SetItemText(27, 1, "OUT_CV_Delay");
		m_ParamList.SetItemText(28, 1, "PuttingMode 0=180 Deg, 1=0 Deg");
		m_ParamList.SetItemText(29, 1, "ByPassMode");
		break;

	case SYSTEM_LANGUAGE_CN:
		m_ParamList.SetItemText(0, 1, "自動登出時間");
		m_ParamList.SetItemText(1, 1, "虛擬硬體");
		m_ParamList.SetItemText(2, 1, "虛擬攝影機");
		m_ParamList.SetItemText(3, 1, "常態儲存圖檔");
		m_ParamList.SetItemText(4, 1, "記錄儲存路徑");
		m_ParamList.SetItemText(5, 1, "圖片儲存路徑");
		m_ParamList.SetItemText(6, 1, "貼紙圖片儲存路徑");
		m_ParamList.SetItemText(7, 1, "Epson_IP位置");
		m_ParamList.SetItemText(8, 1, "Epson_Port");
		m_ParamList.SetItemText(9, 1, "Epson 速度 自動(%)");
		m_ParamList.SetItemText(10, 1, "Epson 速度 手動(%)");
		m_ParamList.SetItemText(11, 1, "Epson 真空 超時(Sec)");
		m_ParamList.SetItemText(12, 1, "Epson 訊號 超時(Sec)");
		m_ParamList.SetItemText(13, 1, "CCD 校正距離(mm)");
		m_ParamList.SetItemText(14, 1, "CCD 校正角度(Deg)");
		m_ParamList.SetItemText(15, 1, "貼紙CCD 校正距離(mm)");
		m_ParamList.SetItemText(16, 1, "貼紙CCD 校正角度(Deg)");
		m_ParamList.SetItemText(17, 1, "X_補正值超出(mm)");
		m_ParamList.SetItemText(18, 1, "Y_補正值超出(mm)");
		m_ParamList.SetItemText(19, 1, "T_補正值超出(Deg)");
		m_ParamList.SetItemText(20, 1, "貼紙X_補正值超出(mm)");
		m_ParamList.SetItemText(21, 1, "貼紙Y_補正值超出(mm)");
		m_ParamList.SetItemText(22, 1, "貼紙T_補正值超出(Deg)");
		m_ParamList.SetItemText(23, 1, "手動操作");
		m_ParamList.SetItemText(24, 1, "IN_CV_超時");
		m_ParamList.SetItemText(25, 1, "OUT_CV_超時");
		m_ParamList.SetItemText(26, 1, "IN_CV_延時");
		m_ParamList.SetItemText(27, 1, "OUT_CV_延時");
		m_ParamList.SetItemText(28, 1, "貼標模式 0=180度, 1=0度");
		m_ParamList.SetItemText(29, 1, "過片模式");
		break;
	}

	

	return 0;

}

void CSystemParamsDlg::OnNMClickGrid(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);

	LVHITTESTINFO info;
	info.pt = pNMItemActivate->ptAction;

	int sel = m_ParamList.GetSelectionMark();

	if(m_Base_EditItem.IsWindowVisible())
	{
		m_Base_EditItem.ShowWindow(SW_HIDE);
		if(m_Base_Row != -1)
		{
			int Row = m_Base_Row;
			CString ItemText;
			m_Base_EditItem.GetWindowText(ItemText);
			m_ParamList.SetItemText(Row, m_Base_Col, ItemText);

		}
	}

	if(m_Base_ComboBoxItem.IsWindowVisible())
	{
		m_Base_ComboBoxItem.ShowWindow(SW_HIDE);
		if(m_Base_Row != -1)
		{
			int Row = m_Base_Row;
			CString ItemText;
			m_Base_ComboBoxItem.GetLBText(m_Base_ComboBoxItem.GetCurSel(), ItemText);
			m_ParamList.SetItemText(Row, m_Base_Col, ItemText);

		}
	}

	if(sel  == -1 )
		return ;
	else
	{
		//UpdateUIParameter(sel);
	}

	*pResult = 0;
}

void CSystemParamsDlg::OnNMDbClickGrid( NMHDR* pNMHDR, LRESULT* pResult )
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);

	LVHITTESTINFO info;
	info.pt = pNMItemActivate->ptAction;

	if(m_ParamList.SubItemHitTest(&info) != -1)
	{
		m_Base_Row = info.iItem;
		m_Base_Col = info.iSubItem;
		CRect rect;
		CString Temp;


		switch(m_Base_Col)
		{
		case 2:
			if(m_Base_Row == 4 || m_Base_Row == 5 || m_Base_Row == 6 )
			{
				CFolderPickerDialog fd("D:\\", 0 , this, 0);

				if(fd.DoModal() == IDOK)
				{
					CString ItemText = fd.GetPathName();
					m_ParamList.SetItemText(m_Base_Row, m_Base_Col, ItemText + "\\");

				}
				
			}
			else
			{
				m_ParamList.GetSubItemRect(info.iItem, info.iSubItem, LVIR_LABEL, rect);
				Temp = m_ParamList.GetItemText(info.iItem, info.iSubItem);
				m_Base_EditItem.SetWindowText(Temp);
				m_Base_EditItem.MoveWindow(&rect, TRUE);
				m_Base_EditItem.ShowWindow(SW_SHOW);
				m_Base_EditItem.SetFocus();
			}
			
			break;

		}
	}
}

void CSystemParamsDlg::UpdateUI()
{

	if(ReloadSystemParams() == false)
	{
		AfxMessageBox("讀取系統參數失敗\nLoad System Parameters is Fail!!");
		return;
	}

	GetDlgItem(IDC_EDIT_SYSPARAM_EQ_NAME)->SetWindowText(SystemParams->GetMachineID());
	GetDlgItem(IDC_EDIT_SYSPARAM_M_E_NAME)->SetWindowText(SystemParams->GetMaintenanceEG_Name());
	GetDlgItem(IDC_EDIT_SYSPARAM_M_E_PHONE)->SetWindowText(SystemParams->GetMaintenanceEG_Phone());

	if(SystemParams->GetInterLockCheck())
		m_InterLockCheck.SetCheck(BST_CHECKED);
	else
		m_InterLockCheck.SetCheck(BST_UNCHECKED);

	m_ParamList.SetItemText(0, 2, FormatString("%d", SystemParams->GetSystemParamData()->nAutoLogoutTime));
	m_ParamList.SetItemText(1, 2, FormatString("%d", SystemParams->GetSystemParamData()->bDummyHardware));
	m_ParamList.SetItemText(2, 2, FormatString("%d", SystemParams->GetSystemParamData()->bDummyCamera));
	m_ParamList.SetItemText(3, 2, FormatString("%d", SystemParams->GetSystemParamData()->bAlwaysSaveImage));
	m_ParamList.SetItemText(4, 2, SystemParams->GetSystemParamData()->LogSavePath);
	m_ParamList.SetItemText(5, 2, SystemParams->GetSystemParamData()->ImageFilePath);
	m_ParamList.SetItemText(6, 2, SystemParams->GetSystemParamData()->ImageFilePath_Sticker);
	m_ParamList.SetItemText(7, 2, SystemParams->GetSystemParamData()->EpsonRC_Address);
	m_ParamList.SetItemText(8, 2, FormatString("%d", SystemParams->GetSystemParamData()->EpsonRC_Port));

	m_ParamList.SetItemText(9, 2, FormatString("%d", SystemParams->GetSystemParamData()->RobotSpeed_Auto));
	m_ParamList.SetItemText(10, 2, FormatString("%d", SystemParams->GetSystemParamData()->RobotSpeed_Manual));

	m_ParamList.SetItemText(11, 2, FormatString("%.3lf", SystemParams->GetSystemParamData()->Robot_ForkCheck_Timeout));
	m_ParamList.SetItemText(12, 2, FormatString("%.3lf", SystemParams->GetSystemParamData()->Robot_Handshake_Timeout));

	m_ParamList.SetItemText(13, 2, FormatString("%.3f", SystemParams->GetSystemParamData()->CCD_Calibrate_Distance));
	m_ParamList.SetItemText(14, 2, FormatString("%.3f", SystemParams->GetSystemParamData()->CCD_Calibrate_Degree));
	m_ParamList.SetItemText(15, 2, FormatString("%.3f", SystemParams->GetSystemParamData()->CCD_Calibrate_Sticker_Distance));
	m_ParamList.SetItemText(16, 2, FormatString("%.3f", SystemParams->GetSystemParamData()->CCD_Calibrate_Sticker_Degree));

	m_ParamList.SetItemText(17, 2,  FormatString("%.3lf", SystemParams->GetSystemParamData()->OverRange_mm_X));
	m_ParamList.SetItemText(18, 2,  FormatString("%.3lf", SystemParams->GetSystemParamData()->OverRange_mm_Y));
	m_ParamList.SetItemText(19, 2,  FormatString("%.3lf", SystemParams->GetSystemParamData()->OverRange_mm_T));

	m_ParamList.SetItemText(20, 2,  FormatString("%.3lf", SystemParams->GetSystemParamData()->OverRange_Sticker_mm_X));
	m_ParamList.SetItemText(21, 2,  FormatString("%.3lf", SystemParams->GetSystemParamData()->OverRange_Sticker_mm_Y));
	m_ParamList.SetItemText(22, 2,  FormatString("%.3lf", SystemParams->GetSystemParamData()->OverRange_Sticker_mm_T));

	m_ParamList.SetItemText(23, 2,  FormatString("%d", SystemParams->GetSystemParamData()->bManualClickResult));

	m_ParamList.SetItemText(24, 2,  FormatString("%d", SystemParams->GetSystemParamData()->IN_CV_Timeout));
	m_ParamList.SetItemText(25, 2,  FormatString("%d", SystemParams->GetSystemParamData()->OUT_CV_Timeout));

	m_ParamList.SetItemText(26, 2,  FormatString("%d", SystemParams->GetSystemParamData()->IN_CV_Delay));
	m_ParamList.SetItemText(27, 2,  FormatString("%d", SystemParams->GetSystemParamData()->OUT_CV_Delay));
	m_ParamList.SetItemText(28, 2,  FormatString("%d", SystemParams->GetSystemParamData()->bPuttingMode));
	m_ParamList.SetItemText(29, 2,  FormatString("%d", SystemParams->GetSystemParamData()->bByPassMode));
}

void CSystemParamsDlg::OnBnClickedButtonSave()
{
	try
	{
		if(m_Base_EditItem.IsWindowVisible())
		{
			m_Base_EditItem.ShowWindow(SW_HIDE);
			if(m_Base_Row != -1)
			{
				int Row = m_Base_Row;
				CString ItemText;
				m_Base_EditItem.GetWindowText(ItemText);
				m_ParamList.SetItemText(Row, m_Base_Col, ItemText);

			}
		}

		if(m_Base_ComboBoxItem.IsWindowVisible())
		{
			m_Base_ComboBoxItem.ShowWindow(SW_HIDE);
			if(m_Base_Row != -1)
			{
				int Row = m_Base_Row;
				CString ItemText;
				m_Base_ComboBoxItem.GetLBText(m_Base_ComboBoxItem.GetCurSel(), ItemText);
				m_ParamList.SetItemText(Row, m_Base_Col, ItemText);

			}
		}

		CString csPath;

		csPath.Format("%s\\CtrlPrms\\MachineSetting.ini" , Project_Path);

		SystemParams->SetMachineID(GetDlgItemString(this->GetSafeHwnd(), IDC_EDIT_SYSPARAM_EQ_NAME));

		SystemParams->SetMaintenanceEG_Name(GetDlgItemString(this->GetSafeHwnd(), IDC_EDIT_SYSPARAM_M_E_NAME));

		SystemParams->SetMaintenanceEG_Phone(GetDlgItemString(this->GetSafeHwnd(), IDC_EDIT_SYSPARAM_M_E_PHONE));

		SystemParams->SetInterLockCheck(m_InterLockCheck.GetCheck());
		
		SystemParams->GetSystemParamData()->IdleTime = GetDlgItemInt(IDC_EDIT_SYSPARAM_EQ_CLEAN_TIME);

		SystemParams->GetSystemParamData()->nAutoLogoutTime = atoi(m_ParamList.GetItemText(0, 2));
		SystemParams->GetSystemParamData()->bDummyHardware = atoi(m_ParamList.GetItemText(1, 2));
		SystemParams->GetSystemParamData()->bDummyCamera = atoi(m_ParamList.GetItemText(2, 2));
		SystemParams->GetSystemParamData()->bAlwaysSaveImage = atoi(m_ParamList.GetItemText(3, 2));
		SystemParams->GetSystemParamData()->LogSavePath = m_ParamList.GetItemText(4, 2);
		SystemParams->GetSystemParamData()->ImageFilePath = m_ParamList.GetItemText(5, 2);
		SystemParams->GetSystemParamData()->ImageFilePath_Sticker = m_ParamList.GetItemText(6, 2);
		SystemParams->GetSystemParamData()->EpsonRC_Address = m_ParamList.GetItemText(7, 2);
		SystemParams->GetSystemParamData()->EpsonRC_Port = atoi(m_ParamList.GetItemText(8, 2));

		SystemParams->GetSystemParamData()->RobotSpeed_Auto = atoi(m_ParamList.GetItemText(9, 2));
		SystemParams->GetSystemParamData()->RobotSpeed_Manual = atoi(m_ParamList.GetItemText(10, 2));

		SystemParams->GetSystemParamData()->Robot_ForkCheck_Timeout = float(atof(m_ParamList.GetItemText(11, 2)));
		SystemParams->GetSystemParamData()->Robot_Handshake_Timeout = float(atof(m_ParamList.GetItemText(12, 2)));

		SystemParams->GetSystemParamData()->CCD_Calibrate_Distance = float(atof(m_ParamList.GetItemText(13, 2)));
		SystemParams->GetSystemParamData()->CCD_Calibrate_Degree = float(atof(m_ParamList.GetItemText(14, 2)));

		SystemParams->GetSystemParamData()->CCD_Calibrate_Sticker_Distance = float(atof(m_ParamList.GetItemText(15, 2)));
		SystemParams->GetSystemParamData()->CCD_Calibrate_Sticker_Degree = float(atof(m_ParamList.GetItemText(16, 2)));

		SystemParams->GetSystemParamData()->OverRange_mm_X = atof(m_ParamList.GetItemText(17, 2));
		SystemParams->GetSystemParamData()->OverRange_mm_Y = atof(m_ParamList.GetItemText(18, 2));
		SystemParams->GetSystemParamData()->OverRange_mm_T = atof(m_ParamList.GetItemText(19, 2));

		SystemParams->GetSystemParamData()->OverRange_Sticker_mm_X = atof(m_ParamList.GetItemText(20, 2));
		SystemParams->GetSystemParamData()->OverRange_Sticker_mm_Y = atof(m_ParamList.GetItemText(21, 2));
		SystemParams->GetSystemParamData()->OverRange_Sticker_mm_T = atof(m_ParamList.GetItemText(22, 2));

		SystemParams->GetSystemParamData()->bManualClickResult = atoi(m_ParamList.GetItemText(23, 2));

		SystemParams->GetSystemParamData()->IN_CV_Timeout = atoi(m_ParamList.GetItemText(24, 2));
		SystemParams->GetSystemParamData()->OUT_CV_Timeout = atoi(m_ParamList.GetItemText(25, 2));

		SystemParams->GetSystemParamData()->IN_CV_Delay = atoi(m_ParamList.GetItemText(26, 2));
		SystemParams->GetSystemParamData()->OUT_CV_Timeout = atoi(m_ParamList.GetItemText(27, 2));
		SystemParams->GetSystemParamData()->bPuttingMode = atoi(m_ParamList.GetItemText(28, 2));
		SystemParams->GetSystemParamData()->bByPassMode = atoi(m_ParamList.GetItemText(29, 2));

		SystemParams->Save();

		ProcessRecipe->SaveRecipe();

		ProcessRecipe->ReloadRecipe();

		UpdateUI();

		BOOL NowSetting;

		if(GetPrivateProfileIntA("StartSetting", "Enable", -1, (LPCTSTR)csPath) == 0)
			NowSetting = FALSE;
		else
			NowSetting = TRUE;

		::AfxMessageBox("請重新開啟程式套用此參數\nPlease Re-execute Program to Enable Reload Parameters!!");
	}
	catch(SYSTEM_ERROR &e)
	{
		e.SetLocation("OnBnClickedButtonSave");
		LOG->Message_Error(Log_Main, e.GetErrorMessage());
		return;
	}
}

void CSystemParamsDlg::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialog::OnShowWindow(bShow, nStatus);

	if(bShow)
	{
		try
		{

			UpdateUI();
		}
		catch(SYSTEM_ERROR &e)
		{
			e.SetLocation("CSystemParamsDlg::OnShowWindow");
			LOG->Message_Error(Log_Main, e.GetErrorMessage());
			return;
		}
	}
}

bool CSystemParamsDlg::ReloadSystemParams()
{

	if(m_SystemParams->Load() == false)
		return false;

	return true;
}

void CSystemParamsDlg::OnBnClickedButtonTodayProductsClear()
{
	
}


void CSystemParamsDlg::OnBnClickedButtonTotalProductsClear()
{
	
}

void CSystemParamsDlg::OnBnClickedBtnResetSetting()
{
	ReloadSystemParams();
	try
	{
		UpdateUI();
	}
	catch(SYSTEM_ERROR &e)
	{
		e.SetLocation(" CSystemParamsDlg::OnBnClickedBtnResetSetting");
		LOG->Message_Error(Log_Main, e.GetErrorMessage());
		return;
	}
}

void CSystemParamsDlg::OnBnClickedCheckSystemparamInterlockCheck()
{
	if(m_InterLockCheck.GetCheck() == BST_CHECKED)
		m_InterLockCheck.SetCheck(BST_UNCHECKED);
	else
		m_InterLockCheck.SetCheck(BST_CHECKED);
}
