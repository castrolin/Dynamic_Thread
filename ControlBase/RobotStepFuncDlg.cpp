#include "RobotStepFuncDlg.h"
// StepFuncDlg.cpp : 實作檔
//

#include "stdafx.h"
#include "ControlBase.h"
#include "RobotStepFuncDlg.h"
#include "math.h"

// CStepFuncDlg 對話方塊

IMPLEMENT_DYNAMIC(CRobotStepFuncDlg, CDialog)

CRobotStepFuncDlg::CRobotStepFuncDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CRobotStepFuncDlg::IDD, pParent)
{
	HINSTANCE ORG = AfxGetResourceHandle();
#ifdef _DEBUG
	HINSTANCE ControlBaseInstanceHandle = GetModuleHandle("..\\Debug\\ControlBase.dll");
#elif
	HINSTANCE ControlBaseInstanceHandle = GetModuleHandle("..\\Release\\ControlBase.dll");
#endif
	AfxSetResourceHandle(ControlBaseInstanceHandle);

	this->Create(IDD_DIALOG_OPTION_STEP_FUNC_1, pParent);

	AfxSetResourceHandle(ORG);
}

CRobotStepFuncDlg::~CRobotStepFuncDlg()
{
}

void CRobotStepFuncDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CHECK_ROBOT_STEP_PROC_CV_STATUS_RUNNING, m_Btn_CV_Running);
	DDX_Control(pDX, IDC_CHECK_ROBOT_STEP_PROC_CV_STATUS_PANEL, m_Btn_CV_Panel);
	DDX_Control(pDX, IDC_CHECK_ROBOT_STEP_PROC_PCB_STATUS_UP, m_Btn_PCB_Up);
	DDX_Control(pDX, IDC_CHECK_ROBOT_STEP_PROC_PCB_STATUS_DOWN, m_Btn_PCB_Down);
	DDX_Control(pDX, IDC_CHECK_ROBOT_STEP_PROC_PCB_STATUS_FORWARD, m_Btn_PCB_Forward);
	DDX_Control(pDX, IDC_CHECK_ROBOT_STEP_PROC_PCB_STATUS_BACKWARD, m_Btn_PCB_Backward);


	

}


BEGIN_MESSAGE_MAP(CRobotStepFuncDlg, CDialog)
	ON_WM_SHOWWINDOW()
	ON_MESSAGE(CWM_SYS_UPDATE_LANG, OnMessageChangeLang)
	ON_WM_TIMER()
	
	ON_BN_CLICKED(IDC_BUTTON_STEP_PROC_CORRECT_PCB, &CRobotStepFuncDlg::OnBnClickedButtonStepProcCorrectPcb)
	ON_BN_CLICKED(IDC_BUTTON_STEP_PROC_CORRECT_TAPE, &CRobotStepFuncDlg::OnBnClickedButtonStepProcCorrectTape)
	ON_BN_CLICKED(IDC_BUTTON_ROBOT_STEP_PROC_PATTERN_FIND_MANUAL_CHECK, &CRobotStepFuncDlg::OnBnClickedButtonRobotStepProcPatternFindManualCheck)
	ON_BN_CLICKED(IDC_BUTTON_ROBOT_STEP_PROC_BACK, &CRobotStepFuncDlg::OnBnClickedButtonRobotStepProcBack)
	ON_BN_CLICKED(IDC_BUTTON_STEP_PROC_MOVE_TAPE, &CRobotStepFuncDlg::OnBnClickedButtonStepProcMoveTape)
	ON_BN_CLICKED(IDC_BUTTON_STEP_PROC_GET_TAPE, &CRobotStepFuncDlg::OnBnClickedButtonStepProcGetTape)
	ON_BN_CLICKED(IDC_BUTTON_STEP_PROC_ROBOT_INITIAL, &CRobotStepFuncDlg::OnBnClickedButtonStepProcRobotInitial)
	ON_BN_CLICKED(IDC_BUTTON_STEP_PROC_MOVE_CCD, &CRobotStepFuncDlg::OnBnClickedButtonStepProcMoveCcd)
	ON_BN_CLICKED(IDC_BUTTON_STEP_PROC_MOVE_PCB, &CRobotStepFuncDlg::OnBnClickedButtonStepProcMovePcb)
	ON_BN_CLICKED(IDC_BUTTON_STEP_PROC_ROBOT_STOP, &CRobotStepFuncDlg::OnBnClickedButtonStepProcRobotStop)
	ON_BN_CLICKED(IDC_BUTTON_STEP_PROC_PUT_TAPE, &CRobotStepFuncDlg::OnBnClickedButtonStepProcPutTape)
	ON_BN_CLICKED(IDC_BUTTON_ROBOT_STEP_PROC_PCB_DOWN, &CRobotStepFuncDlg::OnBnClickedButtonRobotStepProcPcbDown)
	ON_BN_CLICKED(IDC_BUTTON_ROBOT_STEP_PROC_PCB_UP, &CRobotStepFuncDlg::OnBnClickedButtonRobotStepProcPcbUp)
	ON_BN_CLICKED(IDC_BUTTON_ROBOT_STEP_PROC_CV_IN_PROCESS, &CRobotStepFuncDlg::OnBnClickedButtonRobotStepProcCvInProcess)
	ON_BN_CLICKED(IDC_BUTTON_ROBOT_STEP_PROC_CV_OUT_PROCESS, &CRobotStepFuncDlg::OnBnClickedButtonRobotStepProcCvOutProcess)
	ON_BN_CLICKED(IDC_BUTTON_ROBOT_STEP_PROC_PCB_FORWARD, &CRobotStepFuncDlg::OnBnClickedButtonRobotStepProcPcbForward)
	ON_BN_CLICKED(IDC_BUTTON_ROBOT_STEP_PROC_PCB_BACKWARD, &CRobotStepFuncDlg::OnBnClickedButtonRobotStepProcPcbBackward)
	ON_BN_CLICKED(IDC_BUTTON_ROBOT_STEP_PROC_PCB_CLAMP, &CRobotStepFuncDlg::OnBnClickedButtonRobotStepProcPcbClamp)
	ON_BN_CLICKED(IDC_BUTTON_ROBOT_STEP_PROC_PCB_RELEASE, &CRobotStepFuncDlg::OnBnClickedButtonRobotStepProcPcbRelease)
	ON_BN_CLICKED(IDC_BUTTON_STEP_PROC_CORRECT_TAPE_RESET, &CRobotStepFuncDlg::OnBnClickedButtonStepProcCorrectTapeReset)
	ON_BN_CLICKED(IDC_BUTTON_STEP_PROC_CORRECT_PCB_RESET, &CRobotStepFuncDlg::OnBnClickedButtonStepProcCorrectPcbReset)
END_MESSAGE_MAP()



// CStepFuncDlg 訊息處理常式
BOOL CRobotStepFuncDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_bRB_NeedIntial = TRUE;

	CFont * pFont = GetFont();
	LOGFONT lf;
	pFont->GetLogFont( &lf );
	lf.lfWeight = FW_BOLD;
	m_Font.CreateFontIndirect( &lf );

	SendMessageToDescendants( WM_SETFONT, (WPARAM) m_Font.m_hObject );

	mBtnFont.CreateFont(30,  20, 0, 0, FW_BOLD, FALSE, FALSE, 0, 0, 0, 0, 0, 0, "微軟正黑體");

	m_PCBRetOffset_X = 0;
	m_PCBRetOffset_Y = 0;
	m_PCBRetOffset_T = 0;

	m_TapeRetOffset_X = 0;
	m_TapeRetOffset_Y = 0;
	m_TapeRetOffset_T = 0;

	m_PictureShowUnit = new CImageProc_PictureShowUnit(LOG, "RobotStepProcImageWindow", GetDlgItem(IDC_STATIC_PICTURE));

	m_PictureShowUnit->RegDrawCallBack(DrawCallBack, this);

	m_Btn_CV_Running.m_bTransparent=FALSE;
	m_Btn_CV_Running.m_bDontUseWinXPTheme=TRUE;

	m_Btn_CV_Panel.m_bTransparent=FALSE;
	m_Btn_CV_Panel.m_bDontUseWinXPTheme=TRUE;

	m_Btn_PCB_Up.m_bTransparent=FALSE;
	m_Btn_PCB_Up.m_bDontUseWinXPTheme=TRUE;

	m_Btn_PCB_Down.m_bTransparent=FALSE;
	m_Btn_PCB_Down.m_bDontUseWinXPTheme=TRUE;

	m_Btn_PCB_Forward.m_bTransparent=FALSE;
	m_Btn_PCB_Forward.m_bDontUseWinXPTheme=TRUE;

	m_Btn_PCB_Backward.m_bTransparent=FALSE;
	m_Btn_PCB_Backward.m_bDontUseWinXPTheme=TRUE;


	return TRUE;
}

void CRobotStepFuncDlg::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialog::OnShowWindow(bShow, nStatus);

	if(bShow == TRUE)
	{

		GetDlgItem(IDC_STATIC_ROBOT_STEP_PROC_RESULT_PCB)->SetWindowText(FormatString("Offset_X: %.3lf, Offset_Y: %.3lf, , Offset_T: %.3lf", m_PCBRetOffset_X, m_PCBRetOffset_Y, m_PCBRetOffset_T));

		GetDlgItem(IDC_STATIC_ROBOT_STEP_PROC_RESULT_TAPE)->SetWindowText(FormatString("Offset_X: %.3lf, Offset_Y: %.3lf, , Offset_T: %.3lf", m_TapeRetOffset_X, m_TapeRetOffset_Y, m_TapeRetOffset_T));

		SetTimer(0, 500, NULL);
	}
	else
	{
		m_bRB_NeedIntial = TRUE;
	}
}

long CRobotStepFuncDlg::OnMessageChangeLang( WPARAM wparam, LPARAM lparam )
{
	CString DlgName = "RobotStepFuncDlg";

	m_ButtonList = LanguageCtrl->GetInterfaceButtonNameList(DlgName, (UINT)wparam);
	m_StaticList = LanguageCtrl->GetInterfaceStaticNameList(DlgName, (UINT)wparam);

	GetDlgItem(IDC_BUTTON_ROBOT_STEP_PROC_PATTERN_FIND_MANUAL_CHECK)->SetWindowText(m_ButtonList[0]);

	GetDlgItem(IDC_BUTTON_STEP_PROC_MOVE_TAPE)->SetWindowText(m_ButtonList[1]);
	GetDlgItem(IDC_BUTTON_STEP_PROC_GET_TAPE)->SetWindowText(m_ButtonList[2]);
	GetDlgItem(IDC_BUTTON_STEP_PROC_MOVE_CCD)->SetWindowText(m_ButtonList[3]);
	GetDlgItem(IDC_BUTTON_STEP_PROC_CORRECT_TAPE)->SetWindowText(m_ButtonList[4]);
	GetDlgItem(IDC_BUTTON_STEP_PROC_MOVE_PCB)->SetWindowText(m_ButtonList[5]);
	GetDlgItem(IDC_BUTTON_STEP_PROC_CORRECT_PCB)->SetWindowText(m_ButtonList[6]);
	GetDlgItem(IDC_BUTTON_STEP_PROC_PUT_TAPE)->SetWindowText(m_ButtonList[7]);
	GetDlgItem(IDC_BUTTON_STEP_PROC_ROBOT_INITIAL)->SetWindowText(m_ButtonList[8]);

	GetDlgItem(IDC_BUTTON_STEP_PROC_ROBOT_STOP)->SetWindowText(m_ButtonList[9]);

	
	GetDlgItem(IDC_BUTTON_ROBOT_STEP_PROC_CV_IN_PROCESS)->SetWindowText(m_ButtonList[10]);
	GetDlgItem(IDC_BUTTON_ROBOT_STEP_PROC_CV_OUT_PROCESS)->SetWindowText(m_ButtonList[11]);

	GetDlgItem(IDC_CHECK_ROBOT_STEP_PROC_CV_STATUS_RUNNING)->SetWindowText(m_ButtonList[12]);
	GetDlgItem(IDC_CHECK_ROBOT_STEP_PROC_CV_STATUS_PANEL)->SetWindowText(m_ButtonList[13]);

	GetDlgItem(IDC_CHECK_ROBOT_STEP_PROC_PCB_STATUS_DOWN)->SetWindowText(m_ButtonList[14]);
	GetDlgItem(IDC_CHECK_ROBOT_STEP_PROC_PCB_STATUS_UP)->SetWindowText(m_ButtonList[15]);
	GetDlgItem(IDC_CHECK_ROBOT_STEP_PROC_PCB_STATUS_FORWARD)->SetWindowText(m_ButtonList[16]);
	GetDlgItem(IDC_CHECK_ROBOT_STEP_PROC_PCB_STATUS_BACKWARD)->SetWindowText(m_ButtonList[17]);

	GetDlgItem(IDC_BUTTON_ROBOT_STEP_PROC_PCB_DOWN)->SetWindowText(m_ButtonList[18]);
	GetDlgItem(IDC_BUTTON_ROBOT_STEP_PROC_PCB_UP)->SetWindowText(m_ButtonList[19]);
	GetDlgItem(IDC_BUTTON_ROBOT_STEP_PROC_PCB_FORWARD)->SetWindowText(m_ButtonList[20]);
	GetDlgItem(IDC_BUTTON_ROBOT_STEP_PROC_PCB_BACKWARD)->SetWindowText(m_ButtonList[21]);
	GetDlgItem(IDC_BUTTON_ROBOT_STEP_PROC_PCB_CLAMP)->SetWindowText(m_ButtonList[22]);
	GetDlgItem(IDC_BUTTON_ROBOT_STEP_PROC_PCB_RELEASE)->SetWindowText(m_ButtonList[23]);
	
	GetDlgItem(IDC_BUTTON_STEP_PROC_CORRECT_TAPE_RESET)->SetWindowText(m_ButtonList[24]);
	GetDlgItem(IDC_BUTTON_STEP_PROC_CORRECT_PCB_RESET)->SetWindowText(m_ButtonList[25]);

	GetDlgItem(IDC_BUTTON_ROBOT_STEP_PROC_BACK)->SetWindowText(m_ButtonList[26]);

	return 0;
}

void CRobotStepFuncDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此加入您的訊息處理常式程式碼和 (或) 呼叫預設值

	CDialog::OnTimer(nIDEvent);

	try
	{

		if(InputControl->GetInput(X021_CV_EMPTY) == FALSE)
			m_Btn_CV_Panel.SetFaceColor(RGB(0,0,255));
		else
			m_Btn_CV_Panel.SetFaceColor(RGB(255,0,0));

		if(InputControl->GetInput(X012_PCB_FORWAARD) == TRUE)
			m_Btn_PCB_Forward.SetFaceColor(RGB(0,0,255));
		else
			m_Btn_PCB_Forward.SetFaceColor(RGB(255,0,0));

		if(InputControl->GetInput(X013_PCB_BACKWARD) == TRUE)
			m_Btn_PCB_Backward.SetFaceColor(RGB(0,0,255));
		else
			m_Btn_PCB_Backward.SetFaceColor(RGB(255,0,0));

		if(InputControl->GetInput(X014_PCB_DOWN) == TRUE)
			m_Btn_PCB_Down.SetFaceColor(RGB(0,0,255));
		else
			m_Btn_PCB_Down.SetFaceColor(RGB(255,0,0));

		if(InputControl->GetInput(X015_PCB_UP) == TRUE)
			m_Btn_PCB_Up.SetFaceColor(RGB(0,0,255));
		else
			m_Btn_PCB_Up.SetFaceColor(RGB(255,0,0));
	}
	catch(SYSTEM_ERROR &e)
	{
		LOG->Message_Error(Log_Main, e.GetErrorMessage());
		KillTimer(0);
	}
	
}

void CRobotStepFuncDlg::OnBnClickedButtonStepProcCorrectPcb()
{
	try
	{
		DWORD StartTick = ::GetTickCount();

		double Offsetmm_X, Offsetmm_Y, Offsetmm_T;

		POINT_DATA_2F Point_L, Point_R;

		m_nOrgPosPixel_LX = ProcessRecipe->Recipe_Data.st_RecipeData.nOrgPosPixel_LX;
		m_nOrgPosPixel_LY = ProcessRecipe->Recipe_Data.st_RecipeData.nOrgPosPixel_LY;
		m_nOrgPosPixel_RX = ProcessRecipe->Recipe_Data.st_RecipeData.nOrgPosPixel_RX;
		m_nOrgPosPixel_RY = ProcessRecipe->Recipe_Data.st_RecipeData.nOrgPosPixel_RY;


		BOOL bRet = StepProcess_PCB->Do_CCDAlign(Point_L, Point_R, Offsetmm_X, Offsetmm_Y, Offsetmm_T, TRUE);


		if(bRet == FALSE)
		{
			ShowSystemMessageBox("系統", "Do_CCDAlign 失敗", true);
		}

		GetDlgItem(IDC_STATIC_ROBOT_STEP_PROC_RESULT_PCB)->SetWindowText(FormatString("Offset_X: %.3lf, Offset_Y: %.3lf, , Offset_T: %.3lf", Offsetmm_X, Offsetmm_Y, Offsetmm_T));

		if(bRet == TRUE)
		{
			SetResultStatus_PCB(Point_L, Point_R, Offsetmm_X, Offsetmm_Y, Offsetmm_T);
		}
		else
		{
			SetResultStatus_PCB(Point_L, Point_R, Offsetmm_X, Offsetmm_Y, Offsetmm_T);
		}

		SystemStatusDlg->SetResultStatus(bRet, Point_L, Point_R, Offsetmm_X, Offsetmm_Y, Offsetmm_T);

		if(bRet == FALSE)
			ShowSystemMessageBox("系統", "基礎圖像搜尋失敗", true);
		else
			ShowSystemMessageBox("系統", "基礎圖像搜尋完成", true);

		TRACE("Time = %d", ::GetTickCount() - StartTick);
	}
	catch(SYSTEM_ERROR &e)
	{
		ShowSystemMessageBox("系統", "基礎圖像搜尋失敗", true);
		e.SetLocation("OnBnClickedButtonStepProcCorrectPcb");
		LOG->Message_Error(Log_Main, e.GetErrorMessage());

		SetSystemAlarm();

		return;
	}
}

void CRobotStepFuncDlg::OnBnClickedButtonStepProcCorrectTape()
{
	try
	{
		DWORD StartTick = ::GetTickCount();

		double Offsetmm_X, Offsetmm_Y, Offsetmm_T;

		POINT_DATA_2F Point_L, Point_R;

		m_nOrgPosPixel_LX = ProcessRecipe->Recipe_Data.st_RecipeData.nOrgPosPixel_Sticker_LX;
		m_nOrgPosPixel_LY = ProcessRecipe->Recipe_Data.st_RecipeData.nOrgPosPixel_Sticker_LY;
		m_nOrgPosPixel_RX = ProcessRecipe->Recipe_Data.st_RecipeData.nOrgPosPixel_Sticker_RX;
		m_nOrgPosPixel_RY = ProcessRecipe->Recipe_Data.st_RecipeData.nOrgPosPixel_Sticker_RY;

		BOOL bRet = StepProcess_Sticker->Do_CCDAlign(Point_L, Point_R, Offsetmm_X, Offsetmm_Y, Offsetmm_T, TRUE);


		GetDlgItem(IDC_STATIC_ROBOT_STEP_PROC_RESULT_TAPE)->SetWindowText(FormatString("Offset_X: %.3lf, Offset_Y: %.3lf, , Offset_T: %.3lf", Offsetmm_X, Offsetmm_Y, Offsetmm_T));

		if(bRet == TRUE)
		{
			SetResultStatus_Tape(Point_L, Point_R, Offsetmm_X, Offsetmm_Y, Offsetmm_T);
		}
		else
		{
			SetResultStatus_Tape(Point_L, Point_R, Offsetmm_X, Offsetmm_Y, Offsetmm_T);
		}

		SystemStatusDlg->SetResultStatus_Sticker(bRet, Point_L, Point_R, Offsetmm_X, Offsetmm_Y, Offsetmm_T);

		if(bRet == FALSE)
			ShowSystemMessageBox("系統", "基礎圖像搜尋失敗", true);
		else
			ShowSystemMessageBox("系統", "基礎圖像搜尋完成", true);

		TRACE("Time = %d", ::GetTickCount() - StartTick);
	}
	catch(SYSTEM_ERROR &e)
	{
		ShowSystemMessageBox("系統", "基礎圖像搜尋失敗", true);
		e.SetLocation("OnBnClickedButtonStepProcCorrectTape");
		LOG->Message_Error(Log_Main, e.GetErrorMessage());

		SetSystemAlarm();

		return;
	}
}

void CRobotStepFuncDlg::SetResultStatus_Tape(POINT_DATA_2F Point_L, POINT_DATA_2F Point_R, double Offset_X, double Offset_Y, double Offset_T, BOOL CALIMODE /*= FALSE*/ )
{

	m_TapeRetOffset_X = Offset_X;
	m_TapeRetOffset_Y = Offset_Y;
	m_TapeRetOffset_T = Offset_T;

	m_Point_L = Point_L;
	m_Point_R = Point_R;


	m_ImageBuffer.release();

	ImageGraber_Hikvision_Sticker->GetSingleImageBuffer().copyTo(m_ImageBuffer);

	m_PictureShowUnit->ShowImage(m_ImageBuffer);
}

void CRobotStepFuncDlg::SetResultStatus_PCB( POINT_DATA_2F Point_L, POINT_DATA_2F Point_R, double Offset_X, double Offset_Y, double Offset_T, BOOL CALIMODE /*= FALSE*/ )
{

	m_PCBRetOffset_X = Offset_X;
	m_PCBRetOffset_Y = Offset_Y;
	m_PCBRetOffset_T = Offset_T;

	m_Point_L = Point_L;
	m_Point_R = Point_R;


	m_ImageBuffer.release();

	ImageGraber_Hikvision->GetSingleImageBuffer().copyTo(m_ImageBuffer);

	m_PictureShowUnit->ShowImage(m_ImageBuffer);
}

BOOL CRobotStepFuncDlg::DrawCallBack( cv::Mat *pImage, LPVOID pObject )
{
	CRobotStepFuncDlg *this_obj = (CRobotStepFuncDlg *)pObject;

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
		cv_DrawCrossLine_P1.x = int(this_obj->m_nOrgPosPixel_LX) - OrgCrossLength;
		cv_DrawCrossLine_P1.y = pImage->rows - int(this_obj->m_nOrgPosPixel_LY);

		cv_DrawCrossLine_P2.x = int(this_obj->m_nOrgPosPixel_LX) + OrgCrossLength;
		cv_DrawCrossLine_P2.y = pImage->rows - int(this_obj->m_nOrgPosPixel_LY);

		cv_DrawCrossLine_P3.x = int(this_obj->m_nOrgPosPixel_LX);
		cv_DrawCrossLine_P3.y = pImage->rows - int(this_obj->m_nOrgPosPixel_LY) - OrgCrossLength;

		cv_DrawCrossLine_P4.x = int(this_obj->m_nOrgPosPixel_LX);
		cv_DrawCrossLine_P4.y = pImage->rows - int(this_obj->m_nOrgPosPixel_LY) + OrgCrossLength;

		cv::line(*pImage, cv_DrawCrossLine_P1, cv_DrawCrossLine_P2, cv::Scalar(0, 180, 180), CrossLineWidth);
		cv::line(*pImage, cv_DrawCrossLine_P3, cv_DrawCrossLine_P4, cv::Scalar(0, 180, 180), CrossLineWidth);

		//Org Point Right / Right Bottom

		cv_DrawCrossLine_P1.x = int(this_obj->m_nOrgPosPixel_RX) - OrgCrossLength;
		cv_DrawCrossLine_P1.y = pImage->rows - int(this_obj->m_nOrgPosPixel_RY);

		cv_DrawCrossLine_P2.x = int(this_obj->m_nOrgPosPixel_RX) + OrgCrossLength;
		cv_DrawCrossLine_P2.y = pImage->rows - int(this_obj->m_nOrgPosPixel_RY);

		cv_DrawCrossLine_P3.x = int(this_obj->m_nOrgPosPixel_RX);
		cv_DrawCrossLine_P3.y = pImage->rows - int(this_obj->m_nOrgPosPixel_RY) - OrgCrossLength;

		cv_DrawCrossLine_P4.x = int(this_obj->m_nOrgPosPixel_RX);
		cv_DrawCrossLine_P4.y = pImage->rows - int(this_obj->m_nOrgPosPixel_RY) + OrgCrossLength;

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
		throw SYSTEM_ERROR(FormatString("CStepFuncDlg::DrawCallBack CV Exception = %s", e.what()), _MODULE_OPENCV_PROCESS, &nRet);
		return FALSE;
	}

	return TRUE;
}

void CRobotStepFuncDlg::OnBnClickedButtonStepProcPatternFindManualCheck()
{
	StepProcess_PCB->Do_ManualClickResultComplete();
	StepProcess_Sticker->Do_ManualClickResultComplete();
}

void CRobotStepFuncDlg::GetManualClickResult( CPoint &Point_R, CPoint &Point_L )
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

void CRobotStepFuncDlg::ShowClickPos( CImageProc_PictureShowUnit::SHOW_CLICKPOS_TYPE nType )
{
	m_PictureShowUnit->ShowClickPos(nType);
}

void CRobotStepFuncDlg::ShowResultPos( BOOL bShow )
{
	m_bShowResultPos = bShow;
}

void CRobotStepFuncDlg::ShowManualClickResultShowButton( BOOL bShow )
{
	if(bShow)
		GetDlgItem(IDC_BUTTON_ROBOT_STEP_PROC_PATTERN_FIND_MANUAL_CHECK)->ShowWindow(SW_SHOW);
	else
		GetDlgItem(IDC_BUTTON_ROBOT_STEP_PROC_PATTERN_FIND_MANUAL_CHECK)->ShowWindow(SW_HIDE);
}

void CRobotStepFuncDlg::OnBnClickedButtonRobotStepProcPatternFindManualCheck()
{
	StepProcess_PCB->Do_ManualClickResultComplete();
	StepProcess_Sticker->Do_ManualClickResultComplete();
}

void CRobotStepFuncDlg::OnBnClickedButtonRobotStepProcBack()
{
	ShowOptionManualSelDlg();
}

void CRobotStepFuncDlg::OnBnClickedButtonStepProcMoveTape()
{
	if(m_bRB_NeedIntial == TRUE)
	{
		ShowSystemMessageBox("系統", "請先進行Robot 初始化再進行操作", TRUE);
		return;
	}

	if(ShowSystemQestionBox("系統", "移動Robot至貼標機，請問是否進行?") == IDCANCEL)
		return;

	ShowSystemMessageBox("系統", "移動中...請勿點選其他功能", false);

	try
	{
		StepProcess->Proc_Robot_Move_Port(PORT_TAPE);
	}
	catch(SYSTEM_ERROR &e)
	{
		ShowSystemMessageBox("系統", "移動失敗", true);
		LOG->Message_Error(Log_Main, e.GetErrorMessage());
		SetSystemAlarm();
		return;
	}

	ShowSystemMessageBox("系統", "移動完成", true);
}

void CRobotStepFuncDlg::OnBnClickedButtonStepProcMoveCcd()
{
	if(m_bRB_NeedIntial == TRUE)
	{
		ShowSystemMessageBox("系統", "請先進行Robot 初始化再進行操作", TRUE);
		return;
	}

	if(ShowSystemQestionBox("系統", "移動Robot至貼紙CCD處，請問是否進行?") == IDCANCEL)
		return;

	ShowSystemMessageBox("系統", "移動中...請勿點選其他功能", false);

	try
	{
		StepProcess->Proc_Robot_Move_Port(PORT_TAPE_CCD);
	}
	catch(SYSTEM_ERROR &e)
	{
		ShowSystemMessageBox("系統", "移動失敗", true);
		LOG->Message_Error(Log_Main, e.GetErrorMessage());
		SetSystemAlarm();
		return;
	}

	ShowSystemMessageBox("系統", "移動完成", true);
}

void CRobotStepFuncDlg::OnBnClickedButtonStepProcMovePcb()
{
	if(m_bRB_NeedIntial == TRUE)
	{
		ShowSystemMessageBox("系統", "請先進行Robot 初始化再進行操作", TRUE);
		return;
	}

	if(ShowSystemQestionBox("系統", "移動Robot至PCB，請問是否進行?") == IDCANCEL)
		return;

	ShowSystemMessageBox("系統", "移動中...請勿點選其他功能", false);

	try
	{
		if(SystemParams->m_SystemParamData.bPuttingMode == 1)
			StepProcess->Proc_Robot_Move_Port(PORT_PCB_0_Deg);
		else
			StepProcess->Proc_Robot_Move_Port(PORT_PCB_180_Deg);
	}
	catch(SYSTEM_ERROR &e)
	{
		ShowSystemMessageBox("系統", "移動失敗", true);
		LOG->Message_Error(Log_Main, e.GetErrorMessage());
		SetSystemAlarm();
		return;
	}

	ShowSystemMessageBox("系統", "移動完成", true);
}

void CRobotStepFuncDlg::OnBnClickedButtonStepProcGetTape()
{
	if(m_bRB_NeedIntial == TRUE)
	{
		ShowSystemMessageBox("系統", "請先進行Robot 初始化再進行操作", TRUE);
		return;
	}

	if(ShowSystemQestionBox("系統", "Robot取標，請問是否進行?") == IDCANCEL)
		return;

	ShowSystemMessageBox("系統", "取標中...請勿點選其他功能", false);

	try
	{
			StepProcess->Proc_Robot_Get_Tape();
	}
	catch(SYSTEM_ERROR &e)
	{
		ShowSystemMessageBox("系統", "取標失敗", true);
		LOG->Message_Error(Log_Main, e.GetErrorMessage());
		SetSystemAlarm();
		return;
	}

	ShowSystemMessageBox("系統", "取標完成", true);
}

void CRobotStepFuncDlg::OnBnClickedButtonStepProcPutTape()
{
	if(m_bRB_NeedIntial == TRUE)
	{
		ShowSystemMessageBox("系統", "請先進行Robot 初始化再進行操作", TRUE);
		return;
	}

	if(ShowSystemQestionBox("系統", "Robot放標，請問是否進行?") == IDCANCEL)
		return;

	ShowSystemMessageBox("系統", "放標中...請勿點選其他功能", false);

	try
	{
		double dAll_Offset_X = 0;
		double dAll_Offset_Y = 0;
		double dAll_Offset_T = 0;

		if(SystemParams->GetSystemParamData()->bPuttingMode == 1)
		{
			dAll_Offset_X = m_PCBRetOffset_X - m_TapeRetOffset_Y + ProcessRecipe->Recipe_Data.st_RecipeData.Offset_mm_X;
			dAll_Offset_Y = m_PCBRetOffset_Y + m_TapeRetOffset_X + ProcessRecipe->Recipe_Data.st_RecipeData.Offset_mm_Y;
			dAll_Offset_T = -m_PCBRetOffset_T + m_TapeRetOffset_T + ProcessRecipe->Recipe_Data.st_RecipeData.Offset_mm_T;
		}
		else
		{
			dAll_Offset_X = m_PCBRetOffset_X + m_TapeRetOffset_Y + ProcessRecipe->Recipe_Data.st_RecipeData.Offset_mm_X;
			dAll_Offset_Y = m_PCBRetOffset_Y - m_TapeRetOffset_X + ProcessRecipe->Recipe_Data.st_RecipeData.Offset_mm_Y;
			dAll_Offset_T = -m_PCBRetOffset_T + m_TapeRetOffset_T + ProcessRecipe->Recipe_Data.st_RecipeData.Offset_mm_T;
		}

		StepProcess->Proc_Robot_Put_Tape(dAll_Offset_X, dAll_Offset_Y, dAll_Offset_T);
	}
	catch(SYSTEM_ERROR &e)
	{
		ShowSystemMessageBox("系統", "放標失敗", true);
		LOG->Message_Error(Log_Main, e.GetErrorMessage());
		SetSystemAlarm();
		return;
	}

	ShowSystemMessageBox("系統", "放標完成", true);
}

void CRobotStepFuncDlg::OnBnClickedButtonStepProcRobotInitial()
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

void CRobotStepFuncDlg::OnBnClickedButtonStepProcRobotStop()
{
	
	try
	{
		EpsonRC_TCPIP_Ctrl->RobotStop();
	}
	catch(SYSTEM_ERROR &e)
	{
		ShowSystemMessageBox("系統", "停止失敗", true);
		LOG->Message_Error(Log_Main, e.GetErrorMessage());
		SetSystemAlarm();
		return;
	}

	ShowSystemMessageBox("系統", "停止完成", true);
}

void CRobotStepFuncDlg::OnBnClickedButtonRobotStepProcPcbDown()
{
	if(ShowSystemQestionBox("系統", "PCB夾持氣壓缸即將下降，請問是否進行?") == IDCANCEL)
		return;

	ShowSystemMessageBox("系統", "動作中...請勿點選其他功能", false);

	try
	{
		StepProcess->Proc_PCB_Down(30000);
	}
	catch(SYSTEM_ERROR &e)
	{
		ShowSystemMessageBox("系統", "PCB夾持氣壓缸下降失敗", true);
		LOG->Message_Error(Log_Main, e.GetErrorMessage());
		SetSystemAlarm();
		return;
	}

	ShowSystemMessageBox("系統", "PCB夾持氣壓缸下降完成", true);
}

void CRobotStepFuncDlg::OnBnClickedButtonRobotStepProcPcbUp()
{
	if(ShowSystemQestionBox("系統", "PCB夾持氣壓缸即將上升，請問是否進行?") == IDCANCEL)
		return;

	ShowSystemMessageBox("系統", "動作中...請勿點選其他功能", false);

	try
	{
		StepProcess->Proc_PCB_Up(30000);
	}
	catch(SYSTEM_ERROR &e)
	{
		ShowSystemMessageBox("系統", "PCB夾持氣壓缸上升失敗", true);
		LOG->Message_Error(Log_Main, e.GetErrorMessage());
		SetSystemAlarm();
		return;
	}

	ShowSystemMessageBox("系統", "PCB夾持氣壓缸上升完成", true);
}

void CRobotStepFuncDlg::OnBnClickedButtonRobotStepProcPcbForward()
{
	if(ShowSystemQestionBox("系統", "PCB夾持氣壓缸即將前進，請問是否進行?") == IDCANCEL)
		return;

	ShowSystemMessageBox("系統", "動作中...請勿點選其他功能", false);

	try
	{
		StepProcess->Proc_PCB_Forward(30000);
	}
	catch(SYSTEM_ERROR &e)
	{
		ShowSystemMessageBox("系統", "PCB夾持氣壓缸前進失敗", true);
		LOG->Message_Error(Log_Main, e.GetErrorMessage());
		SetSystemAlarm();
		return;
	}

	ShowSystemMessageBox("系統", "PCB夾持氣壓缸前進完成", true);
}

void CRobotStepFuncDlg::OnBnClickedButtonRobotStepProcPcbBackward()
{
	if(ShowSystemQestionBox("系統", "PCB夾持氣壓缸即將後退，請問是否進行?") == IDCANCEL)
		return;

	ShowSystemMessageBox("系統", "動作中...請勿點選其他功能", false);

	try
	{
		StepProcess->Proc_PCB_Backward(30000);
	}
	catch(SYSTEM_ERROR &e)
	{
		ShowSystemMessageBox("系統", "PCB氣壓缸後退失敗", true);
		LOG->Message_Error(Log_Main, e.GetErrorMessage());
		SetSystemAlarm();
		return;
	}

	ShowSystemMessageBox("系統", "PCB夾持氣壓缸後退完成", true);
}

void CRobotStepFuncDlg::OnBnClickedButtonRobotStepProcPcbClamp()
{
	if(ShowSystemQestionBox("系統", "PCB夾持，請問是否進行?") == IDCANCEL)
		return;

	ShowSystemMessageBox("系統", "動作中...請勿點選其他功能", false);

	try
	{
		StepProcess->Proc_PCB_Clamp(30000);
	}
	catch(SYSTEM_ERROR &e)
	{
		ShowSystemMessageBox("系統", "PCB氣壓缸夾持失敗", true);
		LOG->Message_Error(Log_Main, e.GetErrorMessage());
		SetSystemAlarm();
		return;
	}

	ShowSystemMessageBox("系統", "PCB夾持氣壓缸夾持完成", true);
}

void CRobotStepFuncDlg::OnBnClickedButtonRobotStepProcPcbRelease()
{
	if(ShowSystemQestionBox("系統", "PCB釋放，請問是否進行?") == IDCANCEL)
		return;

	ShowSystemMessageBox("系統", "動作中...請勿點選其他功能", false);

	try
	{
		StepProcess->Proc_PCB_Release(30000);
	}
	catch(SYSTEM_ERROR &e)
	{
		ShowSystemMessageBox("系統", "PCB氣壓缸釋放失敗", true);
		LOG->Message_Error(Log_Main, e.GetErrorMessage());
		SetSystemAlarm();
		return;
	}

	ShowSystemMessageBox("系統", "PCB夾持氣壓缸釋放完成", true);
}

void CRobotStepFuncDlg::OnBnClickedButtonRobotStepProcCvInProcess()
{
	if(ShowSystemQestionBox("系統", "CV入料流程，請問是否進行?") == IDCANCEL)
		return;

	ShowSystemMessageBox("系統", "動作中...請勿點選其他功能", false);

	try
	{
		StepProcess->Proc_CV_In(30000);
	}
	catch(SYSTEM_ERROR &e)
	{
		ShowSystemMessageBox("系統", "CV入料流程失敗", true);
		LOG->Message_Error(Log_Main, e.GetErrorMessage());
		SetSystemAlarm();
		return;
	}

	ShowSystemMessageBox("系統", "CV入料流程完成", true);
}

void CRobotStepFuncDlg::OnBnClickedButtonRobotStepProcCvOutProcess()
{
	if(ShowSystemQestionBox("系統", "CV出料流程，請問是否進行?") == IDCANCEL)
		return;

	ShowSystemMessageBox("系統", "動作中...請勿點選其他功能", false);

	try
	{
		StepProcess->Proc_CV_Out(30000);
	}
	catch(SYSTEM_ERROR &e)
	{
		ShowSystemMessageBox("系統", "CV出料流程失敗", true);
		LOG->Message_Error(Log_Main, e.GetErrorMessage());
		SetSystemAlarm();
		return;
	}

	ShowSystemMessageBox("系統", "CV出料流程完成", true);
}

void CRobotStepFuncDlg::OnBnClickedButtonStepProcCorrectTapeReset()
{
	m_TapeRetOffset_X = 0;
	m_TapeRetOffset_Y = 0;
	m_TapeRetOffset_T = 0;

	GetDlgItem(IDC_STATIC_ROBOT_STEP_PROC_RESULT_TAPE)->SetWindowText(FormatString("Offset_X: %.3lf, Offset_Y: %.3lf, , Offset_T: %.3lf", m_TapeRetOffset_X, m_TapeRetOffset_Y, m_TapeRetOffset_T));

}


void CRobotStepFuncDlg::OnBnClickedButtonStepProcCorrectPcbReset()
{

	m_PCBRetOffset_X = 0;
	m_PCBRetOffset_Y = 0;
	m_PCBRetOffset_T = 0;

	GetDlgItem(IDC_STATIC_ROBOT_STEP_PROC_RESULT_PCB)->SetWindowText(FormatString("Offset_X: %.3lf, Offset_Y: %.3lf, , Offset_T: %.3lf", m_PCBRetOffset_X, m_PCBRetOffset_Y, m_PCBRetOffset_T));

}
