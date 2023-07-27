// StepFuncDlg.cpp : 實作檔
//

#include "stdafx.h"
#include "ControlBase.h"
#include "StepFuncDlg_Sticker.h"
#include "math.h"

// CStepFuncDlg 對話方塊

IMPLEMENT_DYNAMIC(CStepFuncDlg_Sticker, CDialog)

CStepFuncDlg_Sticker::CStepFuncDlg_Sticker(CWnd* pParent /*=NULL*/)
	: CDialog(CStepFuncDlg_Sticker::IDD, pParent)
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

CStepFuncDlg_Sticker::~CStepFuncDlg_Sticker()
{
}

void CStepFuncDlg_Sticker::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CStepFuncDlg_Sticker, CDialog)
	ON_WM_SHOWWINDOW()
	ON_MESSAGE(CWM_SYS_UPDATE_LANG, OnMessageChangeLang)
	ON_WM_TIMER()
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BUTTON_STEP_PROC_PATTERN_FIND_PROC, &CStepFuncDlg_Sticker::OnBnClickedButtonStepProcPatternFindProc)
	ON_BN_CLICKED(IDC_BUTTON_STEP_PROC_PATTERN_FIND_ORG_PROC, &CStepFuncDlg_Sticker::OnBnClickedButtonStepProcPatternFindProc_Org)
	ON_BN_CLICKED(IDC_BUTTON_STEP_PROC_PATTERN_FIND_SAVE_POS_RECIPE, &CStepFuncDlg_Sticker::OnBnClickedButtonStepProcSavePositionRecipe)

	ON_BN_CLICKED(IDC_BUTTON_STEP_PROC_PATTERN_FIND_CALIBRATE, &CStepFuncDlg_Sticker::OnBnClickedButtonStepProcCalibrate_CALIBRATE)
	ON_BN_CLICKED(IDC_BUTTON_STEP_PROC_PATTERN_FIND_MANUAL_CHECK, &CStepFuncDlg_Sticker::OnBnClickedButtonStepProcPatternFindManualCheck)
	ON_BN_CLICKED(IDC_BUTTON_STEP_PROC_BACK, &CStepFuncDlg_Sticker::OnBnClickedButtonStepProcBack)
	ON_BN_CLICKED(IDC_BUTTON_STEP_PROC_PATTERN_FIND_ROBOT_INITIAL, &CStepFuncDlg_Sticker::OnBnClickedButtonStepProcPatternFindRobotInitial)
END_MESSAGE_MAP()



// CStepFuncDlg 訊息處理常式
BOOL CStepFuncDlg_Sticker::OnInitDialog()
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

	m_PictureShowUnit = new CImageProc_PictureShowUnit(LOG, "StepProcImageWindow_Sticker", GetDlgItem(IDC_STATIC_PICTURE));

	m_PictureShowUnit->RegDrawCallBack(DrawCallBack, this);

	ShowClickPos(CImageProc_PictureShowUnit::SHOW_CLICK_POS_NONE);

	return TRUE;
}

void CStepFuncDlg_Sticker::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialog::OnShowWindow(bShow, nStatus);

	if(bShow == TRUE)
	{

	}
	else
	{
		m_bRB_NeedIntial = TRUE;
		ImageGraber_Hikvision_Sticker->SetShowUint(FALSE);
	}
}

long CStepFuncDlg_Sticker::OnMessageChangeLang( WPARAM wparam, LPARAM lparam )
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

void CStepFuncDlg_Sticker::OnPaint()
{
	CDialog::OnPaint();
}

void CStepFuncDlg_Sticker::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此加入您的訊息處理常式程式碼和 (或) 呼叫預設值

	CDialog::OnTimer(nIDEvent);
}

void CStepFuncDlg_Sticker::OnBnClickedButtonStepProcPatternFindProc()
{
	try
	{
		DWORD StartTick = ::GetTickCount();

		double Offsetmm_X, Offsetmm_Y, Offsetmm_T;

		POINT_DATA_2F Point_L, Point_R;

		BOOL bRet = StepProcess_Sticker->Do_CCDAlign(Point_L, Point_R, Offsetmm_X, Offsetmm_Y, Offsetmm_T, TRUE);


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

void CStepFuncDlg_Sticker::OnBnClickedButtonStepProcPatternFindProc_Org()
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



		BOOL bRet = StepProcess_Sticker->Do_MarkSearch(PatternFileName_L, PatternFileName_R, Point_L, Point_R, TRUE, FOV_ORG_TYPE_LEFTBOTTOM);


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

void CStepFuncDlg_Sticker::OnBnClickedButtonStepProcSavePositionRecipe()
{

	if(AfxMessageBox("系統將目前檢測結果帶入參數檔內，請問是否覆寫參數?!\nSystem will Overwrite recipe parameters?\nYes or No", MB_YESNO) == IDNO)
	{
		return;
	}

	ProcessRecipe->Recipe_Data.st_RecipeData.nOrgPosPixel_Sticker_LX = (m_Point_L.Point_X);
	ProcessRecipe->Recipe_Data.st_RecipeData.nOrgPosPixel_Sticker_LY = (m_Point_L.Point_Y);
	ProcessRecipe->Recipe_Data.st_RecipeData.nOrgPosPixel_Sticker_RX = (m_Point_R.Point_X);
	ProcessRecipe->Recipe_Data.st_RecipeData.nOrgPosPixel_Sticker_RY = (m_Point_R.Point_Y);

	
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

void CStepFuncDlg_Sticker::OnBnClickedButtonStepProcCalibrate_CALIBRATE()
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
		StepProcess_Sticker->Proc_CCD_Calibrate();
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

void CStepFuncDlg_Sticker::SetResultStatus( POINT_DATA_2F Point_L, POINT_DATA_2F Point_R, double Offset_X, double Offset_Y, double Offset_T, BOOL CALIMODE)
{
	ShowResultPos(true);

	m_RetOffset_X = Offset_X;
	m_RetOffset_Y = Offset_Y;
	m_RetOffset_T = Offset_T;

	m_Point_L = Point_L;
	m_Point_R = Point_R;


	m_ImageBuffer.release();

	ImageGraber_Hikvision_Sticker->GetSingleImageBuffer().copyTo(m_ImageBuffer);

	m_PictureShowUnit->ShowImage(m_ImageBuffer);

}

BOOL CStepFuncDlg_Sticker::DrawCallBack( cv::Mat *pImage, LPVOID pObject )
{
	CStepFuncDlg_Sticker *this_obj = (CStepFuncDlg_Sticker *)pObject;

	try
	{
		if(this_obj->m_bShowResultPos == FALSE)
			return TRUE;

		int OrgCrossLength = 0;
		int ResultCrossLength = 0;
		int CrossLineWidth = 0;


		if(this_obj->m_PictureShowUnit->GetShowMode() == FALSE)
		{
			OrgCrossLength = 40;
			ResultCrossLength = 20;
			CrossLineWidth = 4;
		}
		else
		{
			OrgCrossLength = 80;
			ResultCrossLength = 40;
			CrossLineWidth = 8;
		}

		cv::Point cv_DrawCrossLine_P1, cv_DrawCrossLine_P2, cv_DrawCrossLine_P3, cv_DrawCrossLine_P4;

		//Calibrate 

		//Org Point Left / Left Bottom
		cv_DrawCrossLine_P1.x = int(ProcessRecipe->Recipe_Data.st_RecipeData.nOrgPosPixel_Sticker_LX) - OrgCrossLength;
		cv_DrawCrossLine_P1.y = pImage->rows - int(ProcessRecipe->Recipe_Data.st_RecipeData.nOrgPosPixel_Sticker_LY);

		cv_DrawCrossLine_P2.x = int(ProcessRecipe->Recipe_Data.st_RecipeData.nOrgPosPixel_Sticker_LX) + OrgCrossLength;
		cv_DrawCrossLine_P2.y = pImage->rows - int(ProcessRecipe->Recipe_Data.st_RecipeData.nOrgPosPixel_Sticker_LY);

		cv_DrawCrossLine_P3.x = int(ProcessRecipe->Recipe_Data.st_RecipeData.nOrgPosPixel_Sticker_LX);
		cv_DrawCrossLine_P3.y = pImage->rows - int(ProcessRecipe->Recipe_Data.st_RecipeData.nOrgPosPixel_Sticker_LY) - OrgCrossLength;

		cv_DrawCrossLine_P4.x = int(ProcessRecipe->Recipe_Data.st_RecipeData.nOrgPosPixel_Sticker_LX);
		cv_DrawCrossLine_P4.y = pImage->rows - int(ProcessRecipe->Recipe_Data.st_RecipeData.nOrgPosPixel_Sticker_LY) + OrgCrossLength;

		cv::line(*pImage, cv_DrawCrossLine_P1, cv_DrawCrossLine_P2, cv::Scalar(0, 180, 180), CrossLineWidth);
		cv::line(*pImage, cv_DrawCrossLine_P3, cv_DrawCrossLine_P4, cv::Scalar(0, 180, 180), CrossLineWidth);

		//Org Point Right / Right Bottom

		cv_DrawCrossLine_P1.x = int(ProcessRecipe->Recipe_Data.st_RecipeData.nOrgPosPixel_Sticker_RX) - OrgCrossLength;
		cv_DrawCrossLine_P1.y = pImage->rows - int(ProcessRecipe->Recipe_Data.st_RecipeData.nOrgPosPixel_Sticker_RY);

		cv_DrawCrossLine_P2.x = int(ProcessRecipe->Recipe_Data.st_RecipeData.nOrgPosPixel_Sticker_RX) + OrgCrossLength;
		cv_DrawCrossLine_P2.y = pImage->rows - int(ProcessRecipe->Recipe_Data.st_RecipeData.nOrgPosPixel_Sticker_RY);

		cv_DrawCrossLine_P3.x = int(ProcessRecipe->Recipe_Data.st_RecipeData.nOrgPosPixel_Sticker_RX);
		cv_DrawCrossLine_P3.y = pImage->rows - int(ProcessRecipe->Recipe_Data.st_RecipeData.nOrgPosPixel_Sticker_RY) - OrgCrossLength;

		cv_DrawCrossLine_P4.x = int(ProcessRecipe->Recipe_Data.st_RecipeData.nOrgPosPixel_Sticker_RX);
		cv_DrawCrossLine_P4.y = pImage->rows - int(ProcessRecipe->Recipe_Data.st_RecipeData.nOrgPosPixel_Sticker_RY) + OrgCrossLength;

		cv::line(*pImage, cv_DrawCrossLine_P1, cv_DrawCrossLine_P2, cv::Scalar(0, 180, 180), CrossLineWidth);
		cv::line(*pImage, cv_DrawCrossLine_P3, cv_DrawCrossLine_P4, cv::Scalar(0, 180, 180), CrossLineWidth);

		//Result----------------------------------------------------------------------------------

		//Result Point Left / Left Bottom
		cv_DrawCrossLine_P1.x = int(this_obj->m_Point_L.Point_X) - ResultCrossLength;
		cv_DrawCrossLine_P1.y = pImage->rows - int(this_obj->m_Point_L.Point_Y);

		cv_DrawCrossLine_P2.x = int(this_obj->m_Point_L.Point_X) + ResultCrossLength;
		cv_DrawCrossLine_P2.y = pImage->rows - int(this_obj->m_Point_L.Point_Y);

		cv_DrawCrossLine_P3.x = int(this_obj->m_Point_L.Point_X);
		cv_DrawCrossLine_P3.y = pImage->rows - int(this_obj->m_Point_L.Point_Y) - ResultCrossLength;

		cv_DrawCrossLine_P4.x = int(this_obj->m_Point_L.Point_X);
		cv_DrawCrossLine_P4.y = pImage->rows - int(this_obj->m_Point_L.Point_Y) + ResultCrossLength;

		cv::line(*pImage, cv_DrawCrossLine_P1, cv_DrawCrossLine_P2, cv::Scalar(0, 180, 0), CrossLineWidth);
		cv::line(*pImage, cv_DrawCrossLine_P3, cv_DrawCrossLine_P4, cv::Scalar(0, 180, 0), CrossLineWidth);

		//Result Point Right / Right Bottom
		cv_DrawCrossLine_P1.x = int(this_obj->m_Point_R.Point_X) - ResultCrossLength;
		cv_DrawCrossLine_P1.y = pImage->rows - int(this_obj->m_Point_R.Point_Y);

		cv_DrawCrossLine_P2.x = int(this_obj->m_Point_R.Point_X) + ResultCrossLength;
		cv_DrawCrossLine_P2.y = pImage->rows - int(this_obj->m_Point_R.Point_Y);

		cv_DrawCrossLine_P3.x = int(this_obj->m_Point_R.Point_X);
		cv_DrawCrossLine_P3.y = pImage->rows - int(this_obj->m_Point_R.Point_Y) - ResultCrossLength;

		cv_DrawCrossLine_P4.x = int(this_obj->m_Point_R.Point_X);
		cv_DrawCrossLine_P4.y = pImage->rows - int(this_obj->m_Point_R.Point_Y) + ResultCrossLength;

		cv::line(*pImage, cv_DrawCrossLine_P1, cv_DrawCrossLine_P2, cv::Scalar(0, 180, 0), CrossLineWidth);
		cv::line(*pImage, cv_DrawCrossLine_P3, cv_DrawCrossLine_P4, cv::Scalar(0, 180, 0), CrossLineWidth);

	}
	catch(cv::Exception& e)
	{
		ULONG nRet = _ALARM_PROC_OPENCV_EXCEPTION;
		throw SYSTEM_ERROR(FormatString("CStepFuncDlg_Sticker::DrawCallBack CV Exception = %s", e.what()), _MODULE_OPENCV_PROCESS, &nRet);
		return FALSE;
	}

	return TRUE;
}

void CStepFuncDlg_Sticker::ShowManualClickResultShowButton( BOOL bShow )
{
	if(bShow)
		GetDlgItem(IDC_BUTTON_STEP_PROC_PATTERN_FIND_MANUAL_CHECK)->ShowWindow(SW_SHOW);
	else
		GetDlgItem(IDC_BUTTON_STEP_PROC_PATTERN_FIND_MANUAL_CHECK)->ShowWindow(SW_HIDE);
}

void CStepFuncDlg_Sticker::OnBnClickedButtonStepProcPatternFindManualCheck()
{
	StepProcess_Sticker->Do_ManualClickResultComplete();
}

void CStepFuncDlg_Sticker::OnBnClickedButtonStepProcBack()
{
	ShowOptionManualSelDlg();
}

void CStepFuncDlg_Sticker::OnBnClickedButtonStepProcPatternFindRobotInitial()
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

void CStepFuncDlg_Sticker::GetManualClickResult( CPoint &Point_R, CPoint &Point_L )
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

void CStepFuncDlg_Sticker::ShowClickPos( CImageProc_PictureShowUnit::SHOW_CLICKPOS_TYPE nType )
{
	m_PictureShowUnit->ShowClickPos(nType);
}

void CStepFuncDlg_Sticker::ShowResultPos( BOOL bShow )
{
	m_bShowResultPos = bShow;
}