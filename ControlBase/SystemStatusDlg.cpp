#include "SystemStatusDlg.h"
// SystemStatus.cpp : 實作檔
//

#include "stdafx.h"
#include "ControlBase.h"
#include "SystemStatusDlg.h"


// CSystemStatus 對話方塊

IMPLEMENT_DYNAMIC(CSystemStatusDlg, CDialog)

	CSystemStatusDlg::CSystemStatusDlg(CWnd* pParent)
	: CDialog(CSystemStatusDlg::IDD, pParent)
{

	HINSTANCE ORG = AfxGetResourceHandle();
#ifdef _DEBUG
	HINSTANCE ControlBaseInstanceHandle = GetModuleHandle("..\\Debug\\ControlBase.dll");
#elif
	HINSTANCE ControlBaseInstanceHandle = GetModuleHandle("..\\Release\\ControlBase.dll");
#endif
	AfxSetResourceHandle(ControlBaseInstanceHandle);

	this->Create(IDD_DIALOG_STATUS, pParent);

	AfxSetResourceHandle(ORG);


}

CSystemStatusDlg::~CSystemStatusDlg()
{

}

void CSystemStatusDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_RESULT, m_EditResult);
	DDX_Control(pDX, IDC_EDIT_RESULT_OFFSET_X, m_EditResultOffset_X);
	DDX_Control(pDX, IDC_EDIT_RESULT_OFFSET_Y, m_EditResultOffset_Y);
	DDX_Control(pDX, IDC_EDIT_RESULT_OFFSET_T, m_EditResultOffset_T);
	DDX_Control(pDX, IDC_EDIT_RESULT_SCORE, m_EditResultScore);

	DDX_Control(pDX, IDC_EDIT_RESULT_STICKER, m_EditResultSticker);
	DDX_Control(pDX, IDC_EDIT_RESULT_STICKER_OFFSET_X, m_EditResultStickerOffset_X);
	DDX_Control(pDX, IDC_EDIT_RESULT_STICKER_OFFSET_Y, m_EditResultStickerOffset_Y);
	DDX_Control(pDX, IDC_EDIT_RESULT_STICKER_OFFSET_T, m_EditResultStickerOffset_T);

	DDX_Control(pDX, IDC_CHECK_CV_STATUS_IN, m_Btn_CV_In);
	DDX_Control(pDX, IDC_CHECK_CV_STATUS_OUT, m_Btn_CV_Out);
	DDX_Control(pDX, IDC_CHECK_CV_STATUS_RUNNING, m_Btn_CV_Running);

	DDX_Control(pDX, IDC_BUTTON_STATUS_CV, m_Status_CV);
	DDX_Control(pDX, IDC_BUTTON_STATUS_ROBOT, m_Status_Robot);
	DDX_Control(pDX, IDC_BUTTON_STATUS_STICKER, m_Status_Sticker);
	
	DDX_Control(pDX, IDC_BUTTON_DEMO_STATUS_1, m_Status_Demo_1);
	DDX_Control(pDX, IDC_BUTTON_DEMO_STATUS_2, m_Status_Demo_2);
	DDX_Control(pDX, IDC_BUTTON_DEMO_STATUS_3, m_Status_Demo_3);

	DDX_Control(pDX, IDC_CHECK_CV_CLEAR, m_CV_Clear);

	

}


BEGIN_MESSAGE_MAP(CSystemStatusDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_TIMER()
	ON_WM_SHOWWINDOW()
	ON_MESSAGE(CWM_SYS_UPDATE_LANG, OnMessageChangeLang)

	ON_MESSAGE(CWM_SYS_UPDATE_PRODUCT_COUNT, OnMessageUpdateProductCount)

	ON_MESSAGE(CWM_SYS_UPDATE_PRCESS_STATUS_ROBOT, OnMessageUpdateProcessStepRobot)
	ON_MESSAGE(CWM_SYS_UPDATE_PRCESS_STATUS_CV, OnMessageUpdateProcessStepCV)
	ON_MESSAGE(CWM_SYS_UPDATE_PRCESS_STATUS_PCB_PRESS, OnMessageUpdateProcessStepPCB_Press)

	ON_MESSAGE(CWM_SYS_UPDATE_PRCESS_STATUS_EXIST_ROBOT, OnMessageUpdateExistRobot)
	ON_MESSAGE(CWM_SYS_UPDATE_PRCESS_STATUS_EXIST_CV, OnMessageUpdateExistCV)
	ON_MESSAGE(CWM_SYS_UPDATE_PRCESS_STATUS_EXIST_STICKER, OnMessageUpdateExistSticker)

	ON_MESSAGE(CWM_SYS_UPDATE_PRCESS_STATUS_CV_IN, OnMessageUpdateCV_IN)

	ON_BN_CLICKED(IDC_BUTTON_STATUS_MANUAL_CHECK, &CSystemStatusDlg::OnBnClickedButtonStatusManualCheck)
	ON_BN_CLICKED(IDC_BUTTON_STATUS_STICKER_MANUAL_CHECK, &CSystemStatusDlg::OnBnClickedButtonStatusManualCheck_Sticker)
	ON_BN_CLICKED(IDC_BUTTON_STATUS_CV, &CSystemStatusDlg::OnBnClickedButtonStatusCv)
	ON_BN_CLICKED(IDC_CHECK_CV_CLEAR, &CSystemStatusDlg::OnBnClickedCheckCvClear)
END_MESSAGE_MAP()


// CSystemStatus 訊息處理常式
BOOL CSystemStatusDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	CFont * pFont = GetFont();
	LOGFONT lf;
	pFont->GetLogFont( &lf );
	lf.lfWeight = FW_BOLD;
	m_Font.CreateFontIndirect( &lf );

	SendMessageToDescendants( WM_SETFONT, (WPARAM) m_Font.m_hObject );

	m_bShowResultPos = TRUE;

	m_EditResult.SetWindowText("XX");
	m_EditResult.SetTextFont(250, "Times New Roman");
	m_EditResult.SetForeColor(RGB(255, 0, 0));


	m_EditResultOffset_X.SetWindowText("OffsetX:XXXmm");
	m_EditResultOffset_X.SetTextFont(150, "Times New Roman");
	m_EditResultOffset_X.SetForeColor(RGB(0, 0, 255));

	m_EditResultOffset_Y.SetWindowText("OffsetY:XXXmm");
	m_EditResultOffset_Y.SetTextFont(150, "Times New Roman");
	m_EditResultOffset_Y.SetForeColor(RGB(0, 0, 255));

	m_EditResultOffset_T.SetWindowText("OffsetT:XXXDeg");
	m_EditResultOffset_T.SetTextFont(150, "Times New Roman");
	m_EditResultOffset_T.SetForeColor(RGB(0, 0, 255));

	m_EditResultScore.SetWindowText("");
	m_EditResultScore.SetTextFont(400, "Times New Roman");
	m_EditResultScore.SetForeColor(RGB(0, 0, 255));


	m_EditResultSticker.SetWindowText("XX");
	m_EditResultSticker.SetTextFont(250, "Times New Roman");
	m_EditResultSticker.SetForeColor(RGB(255, 0, 0));


	m_EditResultStickerOffset_X.SetWindowText("OffsetX:XXXmm");
	m_EditResultStickerOffset_X.SetTextFont(150, "Times New Roman");
	m_EditResultStickerOffset_X.SetForeColor(RGB(0, 0, 255));

	m_EditResultStickerOffset_Y.SetWindowText("OffsetY:XXXmm");
	m_EditResultStickerOffset_Y.SetTextFont(150, "Times New Roman");
	m_EditResultStickerOffset_Y.SetForeColor(RGB(0, 0, 255));

	m_EditResultStickerOffset_T.SetWindowText("OffsetT:XXXDeg");
	m_EditResultStickerOffset_T.SetTextFont(150, "Times New Roman");
	m_EditResultStickerOffset_T.SetForeColor(RGB(0, 0, 255));


	
	m_Btn_CV_In.SetIcon(IDI_ICON_MIN_LED_GREEN,IDI_ICON_MIN_LED_NONE);
	m_Btn_CV_In.OffsetColor(CButtonST::BTNST_COLOR_BK_IN, 30);
	m_Btn_CV_In.SetColor(CButtonST::BTNST_COLOR_FG_IN, RGB(0, 0, 255));
	m_Btn_CV_In.SetFont(&m_Font);
	m_Btn_CV_In.SetAlwaysTrack(FALSE);

	m_Btn_CV_Out.SetIcon(IDI_ICON_MIN_LED_GREEN,IDI_ICON_MIN_LED_NONE);
	m_Btn_CV_Out.OffsetColor(CButtonST::BTNST_COLOR_BK_IN, 30);
	m_Btn_CV_Out.SetColor(CButtonST::BTNST_COLOR_FG_IN, RGB(0, 0, 255));
	m_Btn_CV_Out.SetFont(&m_Font);
	m_Btn_CV_Out.SetAlwaysTrack(FALSE);

	m_Btn_CV_Running.SetIcon(IDI_ICON_MIN_LED_GREEN,IDI_ICON_MIN_LED_NONE);
	m_Btn_CV_Running.OffsetColor(CButtonST::BTNST_COLOR_BK_IN, 30);
	m_Btn_CV_Running.SetColor(CButtonST::BTNST_COLOR_FG_IN, RGB(0, 0, 255));
	m_Btn_CV_Running.SetFont(&m_Font);
	m_Btn_CV_Running.SetAlwaysTrack(FALSE);

	m_Status_CV.m_bTransparent=FALSE;
	m_Status_CV.m_bDontUseWinXPTheme=TRUE;

	m_Status_Robot.m_bTransparent=FALSE;
	m_Status_Robot.m_bDontUseWinXPTheme=TRUE;

	m_Status_Sticker.m_bTransparent=FALSE;
	m_Status_Sticker.m_bDontUseWinXPTheme=TRUE;

	m_Status_Demo_1.m_bTransparent=FALSE;
	m_Status_Demo_1.m_bDontUseWinXPTheme=TRUE;

	m_Status_Demo_2.m_bTransparent=FALSE;
	m_Status_Demo_2.m_bDontUseWinXPTheme=TRUE;

	m_Status_Demo_3.m_bTransparent=FALSE;
	m_Status_Demo_3.m_bDontUseWinXPTheme=TRUE;

	m_CV_Clear.m_bTransparent=FALSE;
	m_CV_Clear.m_bDontUseWinXPTheme=TRUE;
	

	m_Status_CV.SetFaceColor(RGB(255,0,0));
	m_Status_Robot.SetFaceColor(RGB(255,0,0));
	m_Status_Sticker.SetFaceColor(RGB(255,0,0));

	m_Status_Demo_1.SetFaceColor(RGB(0, 255, 0));
	m_Status_Demo_2.SetFaceColor(RGB(255, 255, 0));
	m_Status_Demo_3.SetFaceColor(RGB(255, 0, 0));

	m_CV_Clear.SetFaceColor(RGB(255, 0, 0));

	return TRUE;
}

void CSystemStatusDlg::OnPaint()
{
	CDialog::OnPaint();
}

void CSystemStatusDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此加入您的訊息處理常式程式碼和 (或) 呼叫預設值

	CDialog::OnTimer(nIDEvent);

}

void CSystemStatusDlg::OnShowWindow( BOOL bShow, UINT nStatus )
{
	CDialog::OnShowWindow(bShow, nStatus);

	if(bShow)
	{
		//ImageGraber_Hikvision->GrabImageStart();
	}
	else
	{

	}
}

long CSystemStatusDlg::OnMessageChangeLang( WPARAM wparam, LPARAM lparam )
{
	CString DlgName = "SystemStatusDlg";

	

	m_ButtonList = LanguageCtrl->GetInterfaceButtonNameList(DlgName, (UINT)wparam);
	m_StaticList = LanguageCtrl->GetInterfaceStaticNameList(DlgName, (UINT)wparam);


	GetDlgItem(IDC_STATIC_HINT)->SetWindowText(m_StaticList[0]);


	return 0;
}

void CSystemStatusDlg::OnBnClickedButtonStatusManualCheck()
{
//	StepProcess_PCB->Do_ManualClickResultComplete();
}

void CSystemStatusDlg::OnBnClickedButtonStatusManualCheck_Sticker()
{
//	StepProcess_Sticker->Do_ManualClickResultComplete();
}


long CSystemStatusDlg::OnMessageUpdateProductCount( WPARAM wparam, LPARAM lparam )
{
	ULONGLONG nNum = PerformanceLog->GetAllProductNum();
	CTime CurrentTime = CTime::GetCurrentTime();

	
		DWORD nProductNum = 0;
		DWORD nPerformanceTT = 0;
		ULONGLONG nAllProductNum = 0;
		PerformanceLog->GetLastPerformace(PerformanceLog->CheckShift_AM(), nProductNum);
		nAllProductNum = PerformanceLog->GetAllProductNum();
		PerformanceLog->GetLastTackTime(nPerformanceTT);

		GetDlgItem(IDC_EDIT_STATUS_PRODUCT_NUM_SHIFT)->SetWindowText(FormatString("%d", nProductNum));
	
		GetDlgItem(IDC_EDIT_STATUS_PRODUCT_NUM_DAY)->SetWindowText(FormatString("%llu", nAllProductNum));

		GetDlgItem(IDC_EDIT_STATUS_PRODUCT_PERFORMANCE_TT)->SetWindowText(FormatString("%d ms", nPerformanceTT));


		
	return 0;
}

long CSystemStatusDlg::OnMessageUpdateProcessStepRobot( WPARAM wparam, LPARAM lparam )
{
	int nStep = (int)wparam;

	GetDlgItem(IDC_STATIC_SYSTEM_STATUS_PROCESS_STEP_ROBOT)->SetWindowText(FormatString("Robot 步數 = %03d", nStep));

	return 0;
}

long CSystemStatusDlg::OnMessageUpdateProcessStepCV( WPARAM wparam, LPARAM lparam )
{
	int nStep = (int)wparam;

	GetDlgItem(IDC_STATIC_SYSTEM_STATUS_PROCESS_STEP_CV)->SetWindowText(FormatString("CV 步數 = %03d", nStep));

	return 0;
}

long CSystemStatusDlg::OnMessageUpdateProcessStepPCB_Press( WPARAM wparam, LPARAM lparam )
{
	int nStep = (int)wparam;

	GetDlgItem(IDC_STATIC_SYSTEM_STATUS_PROCESS_STEP_PCB_PRESS)->SetWindowText(FormatString("氣壓缸 步數 = %03d", nStep));

	return 0;
}

long CSystemStatusDlg::OnMessageUpdateExistRobot( WPARAM wparam, LPARAM lparam )
{
	BOOL bExist = (BOOL)wparam;

	
	if(bExist == FALSE)
		m_Status_Robot.SetFaceColor(RGB(255,0,0));
	else
		m_Status_Robot.SetFaceColor(RGB(0,255,0));

	return 0;
}

long CSystemStatusDlg::OnMessageUpdateExistCV( WPARAM wparam, LPARAM lparam )
{
	BOOL bExist = (BOOL)wparam;
	PRODUCT_PRODUCT_STATUS eStatus = Product_Data->GetProductProcStatus();


	if(bExist == FALSE)
	{
		m_Status_CV.SetFaceColor(RGB(255,0,0));
	}
	else
	{
		if(eStatus == EXP_PRODUCT_STATUS_DONE)
		{
			m_Status_CV.SetFaceColor(RGB(0,255,0));
		}
		else if(eStatus == EXP_PRODUCT_STATUS_IDLE)
		{
			m_Status_CV.SetFaceColor(RGB(255,255,0));
		}
	}

	return 0;
}
 long CSystemStatusDlg::OnMessageUpdateCV_IN( WPARAM wparam, LPARAM lparam )
 {
	 BOOL bCV_Empty = (BOOL)wparam;
	 
	 if(bCV_Empty == TRUE)
		 m_Btn_CV_In.SetCheck(true);
	 else
		 m_Btn_CV_In.SetCheck(false);

	 return 0;
 }
long CSystemStatusDlg::OnMessageUpdateExistSticker( WPARAM wparam, LPARAM lparam )
{

	BOOL bExist = (BOOL)wparam;

	
	if(bExist == FALSE)
		m_Status_Sticker.SetFaceColor(RGB(255,0,0));
	else
		m_Status_Sticker.SetFaceColor(RGB(0,255,0));

	return 0;
}

void CSystemStatusDlg::OnBnClickedButtonStatusCv()
{
	if(GetSystemMode() == MODE_AUTO)
		return;
	

	if(Product_Data->GetProductProcStatus() == EXP_PRODUCT_STATUS_DONE)
	{
		if(ShowSystemQestionBox("系統", "請問是否將Panel設定為未貼貼紙狀態?\n注意，若玻璃已移除，則無效果!") == IDYES)
		{
			Product_Data->SetProductProcStatus(EXP_PRODUCT_STATUS_IDLE);
		}
	}
	else if(Product_Data->GetProductProcStatus() == EXP_PRODUCT_STATUS_IDLE)
	{
		if(ShowSystemQestionBox("系統", "請問是否將Panel設定為已貼貼紙狀態?\n注意，若玻璃已移除，則無效果!") == IDYES)
		{
			Product_Data->SetProductProcStatus(EXP_PRODUCT_STATUS_DONE);
		}
	}
}


void CSystemStatusDlg::OnBnClickedCheckCvClear()
{
	try
	{
		int iRobotPos = 0;

//		EpsonRC_TCPIP_Ctrl->GetProgramValue("g_RobotPos", iRobotPos);

		if(iRobotPos != PORT_TAPE && iRobotPos != PORT_TAPE_CCD)
		{
			ShowSystemMessageBox("系統", "Robot 不在安全位", true);
			return;
		}


		if(GetSystemMode() != MODE_MANUAL)
		{
			m_CV_Clear.SetCheck(BST_UNCHECKED);
			return;
		}

		if(m_CV_Clear.GetCheck() == BST_CHECKED)
		{
			if(ShowSystemQestionBox("系統", "請問是否流片?") == IDYES)
			{
				StepProcess->Proc_PCB_Release(10000);

				m_CV_Clear.SetFaceColor(RGB(0, 255, 0));
//				OutputControl->SetOutput(Y021_REQ_CV_STOP, false);
			}
			else
				m_CV_Clear.SetCheck(BST_UNCHECKED);
		}
		else
		{
			if(ShowSystemQestionBox("系統", "請問是否取消流片?") == IDYES)
			{
				m_CV_Clear.SetFaceColor(RGB(255, 0, 0));
//				OutputControl->SetOutput(Y021_REQ_CV_STOP, true);
			}
			else
				m_CV_Clear.SetCheck(BST_CHECKED);
		}
	}
	catch(SYSTEM_ERROR &e)
	{
		e.SetLocation("OnBnClickedCheckCvClear");
		LOG->Message_Error(Log_Main, e.GetErrorMessage());
		SetSystemAlarm();
		return ;
	}

}
