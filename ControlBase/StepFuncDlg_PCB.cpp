// StepFuncDlg.cpp : 實作檔
//

#include "stdafx.h"
#include "ControlBase.h"
#include "StepFuncDlg_PCB.h"
#include "math.h"

// CStepFuncDlg 對話方塊

IMPLEMENT_DYNAMIC(CStepFuncDlg_PCB, CDialog)

CStepFuncDlg_PCB::CStepFuncDlg_PCB(CWnd* pParent /*=NULL*/)
	: CDialog(CStepFuncDlg_PCB::IDD, pParent)
{
	HINSTANCE ORG = AfxGetResourceHandle();
#ifdef _DEBUG
	HINSTANCE ControlBaseInstanceHandle = GetModuleHandle("..\\Debug\\ControlBase.dll");
#elif
	HINSTANCE ControlBaseInstanceHandle = GetModuleHandle("..\\Release\\ControlBase.dll");
#endif
	AfxSetResourceHandle(ControlBaseInstanceHandle);

	this->Create(IDD_DIALOG_OPTION_STEP_FUNC, pParent);

	AfxSetResourceHandle(ORG);
}

CStepFuncDlg_PCB::~CStepFuncDlg_PCB()
{
}

void CStepFuncDlg_PCB::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CStepFuncDlg_PCB, CDialog)
	ON_WM_SHOWWINDOW()
	ON_MESSAGE(CWM_SYS_UPDATE_LANG, OnMessageChangeLang)
	ON_WM_TIMER()
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BUTTON_STEP_PROC_PATTERN_FIND_PROC, &CStepFuncDlg_PCB::OnBnClickedButtonStepProcPatternFindProc)
	ON_BN_CLICKED(IDC_BUTTON_STEP_PROC_PATTERN_FIND_SAVE_POS_RECIPE, &CStepFuncDlg_PCB::OnBnClickedButtonStepProcSavePositionRecipe)
	ON_BN_CLICKED(IDC_BUTTON_STEP_PROC_PATTERN_FIND_ORG_PROC, &CStepFuncDlg_PCB::OnBnClickedButtonStepProcPatternFindProc_Org)

	ON_BN_CLICKED(IDC_BUTTON_STEP_PROC_PATTERN_FIND_CALIBRATE, &CStepFuncDlg_PCB::OnBnClickedButtonStepProcCalibrate_CALIBRATE)
	ON_BN_CLICKED(IDC_BUTTON_STEP_PROC_PATTERN_FIND_MANUAL_CHECK, &CStepFuncDlg_PCB::OnBnClickedButtonStepProcPatternFindManualCheck)
	ON_BN_CLICKED(IDC_BUTTON_STEP_PROC_BACK, &CStepFuncDlg_PCB::OnBnClickedButtonStepProcBack)
	ON_BN_CLICKED(IDC_BUTTON_STEP_PROC_PATTERN_FIND_ROBOT_INITIAL, &CStepFuncDlg_PCB::OnBnClickedButtonStepProcPatternFindRobotInitial)
END_MESSAGE_MAP()



// CStepFuncDlg 訊息處理常式
BOOL CStepFuncDlg_PCB::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_bRB_NeedIntial = TRUE;

	m_bShowResultPos = TRUE;

	CFont * pFont = GetFont();
	LOGFONT lf;
	pFont->GetLogFont( &lf );
	lf.lfWeight = FW_BOLD;
	m_Font.CreateFontIndirect( &lf );

	SendMessageToDescendants( WM_SETFONT, (WPARAM) m_Font.m_hObject );

	mBtnFont.CreateFont(30,  20, 0, 0, FW_BOLD, FALSE, FALSE, 0, 0, 0, 0, 0, 0, "微軟正黑體");

	m_PictureShowUnit = new CImageProc_PictureShowUnit(LOG, "StepProcImageWindow", GetDlgItem(IDC_STATIC_PICTURE));

	m_PictureShowUnit->RegDrawCallBack(DrawCallBack, this);

	ShowClickPos(CImageProc_PictureShowUnit::SHOW_CLICK_POS_NONE);

	return TRUE;
}

void CStepFuncDlg_PCB::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialog::OnShowWindow(bShow, nStatus);

	if(bShow == TRUE)
	{
	
	}
	else
	{
		m_bRB_NeedIntial = TRUE;
		ImageGraber_Hikvision->SetShowUint(FALSE);
	}
}

long CStepFuncDlg_PCB::OnMessageChangeLang( WPARAM wparam, LPARAM lparam )
{
	CString DlgName = "StepFuncDlg";

	m_ButtonList = LanguageCtrl->GetInterfaceButtonNameList(DlgName, (UINT)wparam);
	m_StaticList = LanguageCtrl->GetInterfaceStaticNameList(DlgName, (UINT)wparam);


	GetDlgItem(IDC_BUTTON_STEP_PROC_PATTERN_FIND_PROC)->SetWindowText(m_ButtonList[0]);
	GetDlgItem(IDC_BUTTON_STEP_PROC_PATTERN_FIND_ORG_PROC)->SetWindowText(m_ButtonList[1]);
	GetDlgItem(IDC_BUTTON_STEP_PROC_PATTERN_FIND_SAVE_POS_RECIPE)->SetWindowText(m_ButtonList[2]);
	GetDlgItem(IDC_BUTTON_STEP_PROC_PATTERN_FIND_CALIBRATE)->SetWindowText(m_ButtonList[3]);
	GetDlgItem(IDC_BUTTON_STEP_PROC_PATTERN_FIND_ROBOT_INITIAL)->SetWindowText(m_ButtonList[4]);
	GetDlgItem(IDC_BUTTON_STEP_PROC_BACK)->SetWindowText(m_ButtonList[5]);

	GetDlgItem(IDC_STATIC_STEP_HINT)->SetWindowText(m_StaticList[0]);
	return 0;
}

void CStepFuncDlg_PCB::OnPaint()
{
	CDialog::OnPaint();
}

void CStepFuncDlg_PCB::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此加入您的訊息處理常式程式碼和 (或) 呼叫預設值

	CDialog::OnTimer(nIDEvent);
}

void CStepFuncDlg_PCB::OnBnClickedButtonStepProcPatternFindProc()
{
	try
	{
		DWORD StartTick = ::GetTickCount();

		double Offsetmm_X, Offsetmm_Y, Offsetmm_T;

		POINT_DATA_2F Point_L, Point_R;

		BOOL bRet = StepProcess_PCB->Do_CCDAlign(Point_L, Point_R, Offsetmm_X, Offsetmm_Y, Offsetmm_T, TRUE);

		GetDlgItem(IDC_STATIC_STEP_PROC_PATTERN_FIND)->SetWindowText(FormatString("Offset_X: %.3lf, Offset_Y: %.3lf, , Offset_T: %.3lf", Offsetmm_X, Offsetmm_Y, Offsetmm_T));

		if(bRet == TRUE)
		{
			SetResultStatus(Point_L, Point_R, Offsetmm_X, Offsetmm_Y, Offsetmm_T);
		}
		else
		{
			SetResultStatus(Point_L, Point_R, Offsetmm_X, Offsetmm_Y, Offsetmm_T);
		}

		if(bRet == FALSE)
			ShowSystemMessageBox("系統", "基礎圖像搜尋失敗", true);
		else
			ShowSystemMessageBox("系統", "基礎圖像搜尋完成", true);

		TRACE("Time = %d", ::GetTickCount() - StartTick);
	}
	catch(SYSTEM_ERROR &e)
	{
		ShowSystemMessageBox("系統", "基礎圖像搜尋失敗", true);
		e.SetLocation("OnBnClickedButtonStepProcPatternFindProc");
		LOG->Message_Error(Log_Main, e.GetErrorMessage());
		SetSystemAlarm();
		return;
	}
}

void CStepFuncDlg_PCB::OnBnClickedButtonStepProcSavePositionRecipe()
{

	if(AfxMessageBox("系統將目前檢測結果帶入參數檔內，請問是否覆寫參數?!\nSystem will Overwrite recipe parameters?\nYes or No", MB_YESNO) == IDNO)
	{
		return;
	}

	ProcessRecipe->Recipe_Data.st_RecipeData.nOrgPosPixel_LX = (m_Point_L.Point_X);
	ProcessRecipe->Recipe_Data.st_RecipeData.nOrgPosPixel_LY = (m_Point_L.Point_Y);
	ProcessRecipe->Recipe_Data.st_RecipeData.nOrgPosPixel_RX = (m_Point_R.Point_X);
	ProcessRecipe->Recipe_Data.st_RecipeData.nOrgPosPixel_RY = (m_Point_R.Point_Y);

	
	if(ProcessRecipe->SaveRecipe() == false)
	{	
		ShowSystemMessageBox("系統", "儲存參數失敗", true);
		return;
	}

	if(ProcessRecipe->ReloadRecipe() == false)
	{
		ShowSystemMessageBox("系統", "重載參數失敗", true);
		return;
	}

	ShowSystemMessageBox("系統", "參數已完成覆寫!\nRecipe Parameters are overwrited!", true);

}

void CStepFuncDlg_PCB::OnBnClickedButtonStepProcPatternFindProc_Org()
{

	try
	{
	
		DWORD StartTick = ::GetTickCount();

		POINT_DATA_2F Point_L, Point_R;

		int RecipeIndex = ProcessRecipe->Recipe_Data.st_RecipeInfo.nRcipeID;
		CString PatternFileName_L, PatternFileName_R, RecipeName;

		PatternFileName_L = FormatString("Work%03d_L.ptn", RecipeIndex);
		PatternFileName_R = FormatString("Work%03d_R.ptn", RecipeIndex);
		RecipeName = FormatString("Work%03d", RecipeIndex);



		BOOL bRet = StepProcess_PCB->Do_MarkSearch(PatternFileName_L, PatternFileName_R, Point_L, Point_R, TRUE, FOV_ORG_TYPE_LEFTBOTTOM);


		if(bRet == TRUE)
		{
			SetResultStatus(Point_L, Point_R, 0, 0, 0);
		}
		else
		{
			SetResultStatus(Point_L, Point_R, 0, 0, 0);
		}

		if(bRet == FALSE)
			ShowSystemMessageBox("系統", "基礎圖像搜尋失敗", true);
		else
			ShowSystemMessageBox("系統", "基礎圖像搜尋完成", true);

		TRACE("Time = %d", ::GetTickCount() - StartTick);
	}
	catch(SYSTEM_ERROR &e)
	{
		ShowSystemMessageBox("系統", "基礎圖像搜尋失敗", true);
		e.SetLocation("OnBnClickedButtonStepProcPatternFindProc_Org");
		LOG->Message_Error(Log_Main, e.GetErrorMessage());
		SetSystemAlarm();
		return;
	}
}

void CStepFuncDlg_PCB::OnBnClickedButtonStepProcCalibrate_CALIBRATE()
{
	
	

	if(m_bRB_NeedIntial == TRUE)
	{
		ShowSystemMessageBox("系統", "請先進行Robot 初始化再進行操作", TRUE);
		return;
	}

	int RecipeIndex = ProcessRecipe->Recipe_Data.st_RecipeInfo.nRcipeID;
	CString RecipeName = FormatString("Work%03d", RecipeIndex);

	if(ShowSystemQestionBox("系統", FormatString("系統將進行CCD校正，原先Recipte%s校正參數將會被覆蓋請問是否執行?", RecipeName)) == IDCANCEL)
		return;

	ShowSystemMessageBox("系統", "校正中...請勿點選其他功能", false);

	try
	{
		StepProcess_PCB->Proc_CCD_Calibrate();
	}
	catch(SYSTEM_ERROR &e)
	{
		ShowSystemMessageBox("系統", "校正失敗", true);
		LOG->Message_Error(Log_Main, e.GetErrorMessage());
		SetSystemAlarm();
		return;
	}

	ShowSystemMessageBox("系統", FormatString("校正完成, Recipe = %s", RecipeName), true);
	
}


void CStepFuncDlg_PCB::ShowManualClickResultShowButton( BOOL bShow )
{
	if(bShow)
		GetDlgItem(IDC_BUTTON_STEP_PROC_PATTERN_FIND_MANUAL_CHECK)->ShowWindow(SW_SHOW);
	else
		GetDlgItem(IDC_BUTTON_STEP_PROC_PATTERN_FIND_MANUAL_CHECK)->ShowWindow(SW_HIDE);
}

void CStepFuncDlg_PCB::OnBnClickedButtonStepProcPatternFindManualCheck()
{
	StepProcess_PCB->Do_ManualClickResultComplete();
}

void CStepFuncDlg_PCB::OnBnClickedButtonStepProcBack()
{
	ShowOptionManualSelDlg();
}

void CStepFuncDlg_PCB::OnBnClickedButtonStepProcPatternFindRobotInitial()
{
	if(ShowSystemQestionBox("系統", "系統將進行Robot 初始化，請問是否進行?") == IDCANCEL)
		return;

	ShowSystemMessageBox("系統", "初始化中...請勿點選其他功能", false);

	try
	{
		StepProcess->Proc_Robot_Initial(FALSE);
	}
	catch(SYSTEM_ERROR &e)
	{
		ShowSystemMessageBox("系統", "初始化失敗", true);
		LOG->Message_Error(Log_Main, e.GetErrorMessage());
		SetSystemAlarm();
		return;
	}

	ShowSystemMessageBox("系統", "初始化完成", true);
	m_bRB_NeedIntial = FALSE;
}

void CStepFuncDlg_PCB::GetManualClickResult( CPoint &Point_R, CPoint &Point_L )
{
	CPoint Point1, Point2;

	m_PictureShowUnit->GetImageClickPos_Down(0, Point1, CImageProc_PictureShowUnit::FOV_ORG_TYPE_LEFTBOTTOM);
	m_PictureShowUnit->GetImageClickPos_Down(1, Point2, CImageProc_PictureShowUnit::FOV_ORG_TYPE_LEFTBOTTOM);

	if(Point1.x < Point2.x)
	{
		Point_L = Point1;
		Point_R = Point2;
	}
	else
	{
		Point_L = Point2;
		Point_R = Point1;
	}
}