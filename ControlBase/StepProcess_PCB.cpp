
#include "stdafx.h"
#include "StepProcess.h"


CStepProcess_PCB::CStepProcess_PCB()
{
	m_bManualClickResultCompelete = FALSE;
	m_PLC_LastMode = 0;
	//pCounterPoint_Class = new CCounterPoint_Class();
}

CStepProcess_PCB::~CStepProcess_PCB()
{
}

BOOL CStepProcess_PCB::Do_MarkSearch(CString PatternName, double &Pos_Xpixel, double &Pos_Ypixel, double &Score, BOOL bSavePic,  FOV_ORG_TYPE nORG_Type)
{
	try
	{
		CDiskObject DiskObject;
		CTime cur_tm = CTime::GetCurrentTime();
		CString csDate, OrgLable, RetLable, FileDirectory;
		CString FolderPath = SystemParams->GetSystemParamData()->ImageFilePath;


		UINT CCD_FOV_Width;
		UINT CCD_FOV_Height;

		PATTERN_FIND_RESULT PatternFindResult;

		csDate = cur_tm.Format("%Y-%m-%d");
		OrgLable = cur_tm.Format("FlatEdge_ORG_%Y-%m-%d-%H-%M-%S");
		RetLable = cur_tm.Format("FlatEdge_RET_%Y-%m-%d-%H-%M-%S");

		ImageProc_PatternFind_MIL->SetPatternName(PatternName);

		FileDirectory = FormatString("%s%s", FolderPath, csDate);

		CCD_FOV_Width = ImageGraber_Hikvision->m_Info.nImageWidth;
		CCD_FOV_Height = ImageGraber_Hikvision->m_Info.nImageHeight;

		if(ImageGraber_Hikvision->IsCameraOpen() == false)
		{
			ImageGraber_Hikvision->CheckConnection();
			return FALSE;
		}

		m_FilePath_Org = FormatString("%s\\%s.bmp", FileDirectory, OrgLable);

		m_FilePath_Ret = FormatString("%s\\%s.bmp", FileDirectory, RetLable);

		if(DiskObject.DirectoryExists(FileDirectory) == FALSE)
			DiskObject.CreateDirectoryA(FileDirectory);

		int nThreshold = ProcessRecipe->Recipe_Data.st_RecipeData.nThreshold;
		int nBlur = ProcessRecipe->Recipe_Data.st_RecipeData.nBlur;

		/*
		if(ImageGraber_Hikvision->SaveOriginalImage(FilePath_Org, nThreshold, nBlur) == false)
			return FALSE;
		*/
		UINT8 *pImagePtr = NULL;
		int ImageWidth, ImageHeight, ImageDepth;
		pImagePtr = ImageGraber_Hikvision->GrabSigleImageBuffer(ImageWidth, ImageHeight, ImageDepth, nThreshold, nBlur);

		if(pImagePtr == NULL)
			return FALSE;

		if(ImageProc_PatternFind_MIL->PatternFind(pImagePtr, ImageWidth, ImageHeight, ImageDepth, PatternFindResult, nORG_Type) == TRUE)
		{
			double Offset_X = PatternFindResult.pos_X;
			double Offset_Y = PatternFindResult.pos_Y;
			Score = PatternFindResult.Score;

			switch(nORG_Type)
			{
			case FOV_ORG_TYPE_LEFTTOP:
				m_nImagePos_X = (int)PatternFindResult.pos_X;
				m_nImagePos_Y = -(int)PatternFindResult.pos_Y;
				break;
			case FOV_ORG_TYPE_LEFTBOTTOM:
				m_nImagePos_X = PatternFindResult.pos_X;////強轉刪除  (int)PatternFindResult.pos_X
				m_nImagePos_Y = ImageGraber_Hikvision->GetImageHeight() - PatternFindResult.pos_Y;////(int)PatternFindResult.pos_Y
				break;
			case FOV_ORG_TYPE_RIGHTTOP:
				m_nImagePos_X = (int)PatternFindResult.pos_X + ImageGraber_Hikvision->GetImageWidth();
				m_nImagePos_Y = -(int)PatternFindResult.pos_Y;
				break;
			case FOV_ORG_TYPE_RIGHTBOTTOM:
				m_nImagePos_X = (int)PatternFindResult.pos_X + ImageGraber_Hikvision->GetImageWidth();
				m_nImagePos_Y = ImageGraber_Hikvision->GetImageHeight() - (int)PatternFindResult.pos_Y;
				break;
			case FOV_ORG_TYPE_CENTER:
				m_nImagePos_X = (int)PatternFindResult.pos_X + ImageGraber_Hikvision->GetImageWidth() / 2;
				m_nImagePos_Y = ImageGraber_Hikvision->GetImageHeight() / 2 - (int)PatternFindResult.pos_Y;
				break;
			case FOV_ORG_TYPE_ORG:
				m_nImagePos_X = (int)PatternFindResult.pos_X;
				m_nImagePos_Y = (int)PatternFindResult.pos_Y;
				break;
			}


			Pos_Xpixel = Offset_X;
			Pos_Ypixel = Offset_Y;

			if(bSavePic == TRUE)
			{
				ImageGraber_Hikvision->SaveGrabSigleImageBuffer(m_FilePath_Org);

				ImageGraber_Hikvision->SaveGrabSigleImageBufferWithLabel(m_FilePath_Ret, FormatString("Pos_X = %.3lf, Pos_Y = %.3lf,Score=%.3lf", PatternFindResult.pos_X, PatternFindResult.pos_Y,PatternFindResult.Score), (UINT)m_nImagePos_X, (UINT)m_nImagePos_Y);

			}
			

			return TRUE;
		}
		else
		{
			if(bSavePic == TRUE)
			{
				ImageGraber_Hikvision->SaveGrabSigleImageBuffer(m_FilePath_Org);
			}

			Score = PatternFindResult.Score;
			return FALSE;
		}
	}
	catch(SYSTEM_ERROR &e)
	{
		e.SetLocation("Do_MarkSearch");
		throw;

		return FALSE;
	}

	return TRUE;
}

BOOL CStepProcess_PCB::Do_MarkSearch( CString PatternName_L, CString PatternName_R, POINT_DATA_2F &Pos_L, POINT_DATA_2F &Pos_R, BOOL bSavePic, FOV_ORG_TYPE nORG_Type )
{
	try
	{
		CDiskObject DiskObject;
		CTime cur_tm = CTime::GetCurrentTime();
		CString csDate, OrgLable, RetLable, FileDirectory;

		UINT CCD_FOV_Width;
		UINT CCD_FOV_Height;

		PATTERN_FIND_RESULT PatternFindResult_L;
		PATTERN_FIND_RESULT PatternFindResult_R;
		CString FolderPath = SystemParams->GetSystemParamData()->ImageFilePath;


		csDate = cur_tm.Format("%Y-%m-%d");
		OrgLable = cur_tm.Format("FlatEdge_ORG_%Y-%m-%d-%H-%M-%S");
		RetLable = cur_tm.Format("FlatEdge_RET_%Y-%m-%d-%H-%M-%S");

		FileDirectory = FormatString("%s%s", FolderPath, csDate);

		CCD_FOV_Width = ImageGraber_Hikvision->m_Info.nImageWidth;
		CCD_FOV_Height = ImageGraber_Hikvision->m_Info.nImageHeight;

		if(ImageGraber_Hikvision->IsCameraOpen() == false)
		{
			ImageGraber_Hikvision->CheckConnection();
			return FALSE;
		}

		m_FilePath_Org = FormatString("%s\\%s.bmp", FileDirectory, OrgLable);

		m_FilePath_Ret = FormatString("%s\\%s.bmp", FileDirectory, RetLable);

		if(DiskObject.DirectoryExists(FileDirectory) == FALSE)
			DiskObject.CreateDirectoryA(FileDirectory);

		int nThreshold = ProcessRecipe->Recipe_Data.st_RecipeData.nThreshold;
		int nBlur = ProcessRecipe->Recipe_Data.st_RecipeData.nBlur;

		UINT8 *pImagePtr = NULL;
		int ImageWidth, ImageHeight, ImageDepth;
		pImagePtr = ImageGraber_Hikvision->GrabSigleImageBuffer(ImageWidth, ImageHeight, ImageDepth, nThreshold, nBlur);

		if(pImagePtr == NULL)
			return FALSE;

		if(ImageProc_PatternFind_MIL->PatternFind(pImagePtr, ImageWidth, ImageHeight, ImageDepth, PatternName_L, PatternName_R, PatternFindResult_L, PatternFindResult_R, nORG_Type) == TRUE)
		{
			double OffsetL_X = PatternFindResult_L.pos_X;
			double OffsetL_Y = PatternFindResult_L.pos_Y;
			double OffsetR_X = PatternFindResult_R.pos_X;
			double OffsetR_Y = PatternFindResult_R.pos_Y;

			switch(nORG_Type)
			{
			case FOV_ORG_TYPE_LEFTTOP:
				m_nImagePosL_X = (int)PatternFindResult_L.pos_X;
				m_nImagePosL_Y = -(int)PatternFindResult_L.pos_Y;
				m_nImagePosR_X = (int)PatternFindResult_R.pos_X;
				m_nImagePosR_Y = -(int)PatternFindResult_R.pos_Y;
				break;
			case FOV_ORG_TYPE_LEFTBOTTOM:
				m_nImagePosL_X = PatternFindResult_L.pos_X;////強轉刪除  (int)PatternFindResult.pos_X
				m_nImagePosL_Y = ImageGraber_Hikvision->GetImageHeight() - PatternFindResult_L.pos_Y;////(int)PatternFindResult.pos_Y
				m_nImagePosR_X = PatternFindResult_R.pos_X;////強轉刪除  (int)PatternFindResult.pos_X
				m_nImagePosR_Y = ImageGraber_Hikvision->GetImageHeight() - PatternFindResult_R.pos_Y;////(int)PatternFindResult.pos_Y
				break;
			case FOV_ORG_TYPE_RIGHTTOP:
				m_nImagePosL_X = (int)PatternFindResult_L.pos_X + ImageGraber_Hikvision->GetImageWidth();
				m_nImagePosL_Y = -(int)PatternFindResult_L.pos_Y;
				m_nImagePosR_X = (int)PatternFindResult_R.pos_X + ImageGraber_Hikvision->GetImageWidth();
				m_nImagePosR_Y = -(int)PatternFindResult_R.pos_Y;
				break;
			case FOV_ORG_TYPE_RIGHTBOTTOM:
				m_nImagePosL_X = (int)PatternFindResult_L.pos_X + ImageGraber_Hikvision->GetImageWidth();
				m_nImagePosL_Y = ImageGraber_Hikvision->GetImageHeight() - (int)PatternFindResult_L.pos_Y;
				m_nImagePosR_X = (int)PatternFindResult_R.pos_X + ImageGraber_Hikvision->GetImageWidth();
				m_nImagePosR_Y = ImageGraber_Hikvision->GetImageHeight() - (int)PatternFindResult_R.pos_Y;
				break;
			case FOV_ORG_TYPE_CENTER:
				m_nImagePosL_X = (int)PatternFindResult_L.pos_X + ImageGraber_Hikvision->GetImageWidth() / 2;
				m_nImagePosL_Y = ImageGraber_Hikvision->GetImageHeight() / 2 - (int)PatternFindResult_L.pos_Y;
				m_nImagePosR_X = (int)PatternFindResult_R.pos_X + ImageGraber_Hikvision->GetImageWidth() / 2;
				m_nImagePosR_Y = ImageGraber_Hikvision->GetImageHeight() / 2 - (int)PatternFindResult_R.pos_Y;
				break;
			case FOV_ORG_TYPE_ORG:
				m_nImagePosL_X = (int)PatternFindResult_L.pos_X;
				m_nImagePosL_Y = (int)PatternFindResult_L.pos_Y;
				m_nImagePosR_X = (int)PatternFindResult_R.pos_X;
				m_nImagePosR_Y = (int)PatternFindResult_R.pos_Y;
				break;
			}


			Pos_L.Point_X = OffsetL_X;
			Pos_L.Point_Y = OffsetL_Y;

			Pos_R.Point_X = OffsetR_X;
			Pos_R.Point_Y = OffsetR_Y;

			if(bSavePic == TRUE)
			{
				ImageGraber_Hikvision->SaveGrabSigleImageBuffer(m_FilePath_Org);

				ImageGraber_Hikvision->SaveGrabSigleImageBufferWithLabel(m_FilePath_Ret, (UINT)m_nImagePosL_X, (UINT)m_nImagePosL_Y, (UINT)m_nImagePosR_X, (UINT)m_nImagePosR_Y);
			}

			return TRUE;
		}
		else
		{
			if(bSavePic == TRUE)
			{
				ImageGraber_Hikvision->SaveGrabSigleImageBuffer(m_FilePath_Org);
			}

			return FALSE;
		}
	
	}
	catch(SYSTEM_ERROR &e)
	{
		e.SetLocation("Do_MarkSearch");
		throw;

		return FALSE;
	}

	return TRUE;
}

BOOL CStepProcess_PCB::Do_CCDAlign(POINT_DATA_2F &RetPoint_L, POINT_DATA_2F &RetPoint_R, double &Offset_X, double &Offset_Y, double &Offset_T, BOOL bSavePic)
{
	try
	{
		CP_ALIGNMENT_DATA AlignmentData;

		int RecipeIndex = ProcessRecipe->Recipe_Data.st_RecipeInfo.nRcipeID;
		CString PatternFileName_L, PatternFileName_R, RecipeName;

		AlignmentData.O_dX1 = ProcessRecipe->Recipe_Data.st_RecipeData.nOrgPosPixel_LX;
		AlignmentData.O_dY1 = ProcessRecipe->Recipe_Data.st_RecipeData.nOrgPosPixel_LY;

		AlignmentData.O_dX2 = ProcessRecipe->Recipe_Data.st_RecipeData.nOrgPosPixel_RX;
		AlignmentData.O_dY2 = ProcessRecipe->Recipe_Data.st_RecipeData.nOrgPosPixel_RY;

		POINT_DATA_2F Point_L, Point_R;

		PatternFileName_L = FormatString("Work%03d_L.ptn", RecipeIndex);
		PatternFileName_R = FormatString("Work%03d_R.ptn", RecipeIndex);
		RecipeName = FormatString("Work%03d", RecipeIndex);

		if(Do_MarkSearch(PatternFileName_L, PatternFileName_R, Point_L, Point_R, bSavePic, FOV_ORG_TYPE_LEFTBOTTOM) == FALSE)
		{
			Offset_X = 0;
			Offset_Y = 0;
			Offset_T = 0;

ManualSelectCheck:

			if(SystemParams->GetSystemParamData()->bManualClickResult == TRUE)
			{

				SystemStatusDlg->SetResultStatus(FALSE, Point_L, Point_R, 0, 0, 0);
				StepFuncDlg->SetResultStatus(Point_L, Point_R, 0, 0, 0);
				RobotStepFuncDlg->SetResultStatus_Tape(Point_L, Point_R, 0, 0, 0);

				Delay(500);

				if(ShowSystemQestionBox("System", "是否執行手動點選結果？") == IDCANCEL)
					return FALSE;

				SystemStatusDlg->ShowClickPos(CImageProc_PictureShowUnit::SHOW_CLICK_POS_DOWN);
				StepFuncDlg->ShowClickPos(CImageProc_PictureShowUnit::SHOW_CLICK_POS_DOWN);
				RobotStepFuncDlg->ShowClickPos(CImageProc_PictureShowUnit::SHOW_CLICK_POS_DOWN);

				SystemStatusDlg->ShowResultPos(FALSE);
				StepFuncDlg->ShowResultPos(FALSE);
				RobotStepFuncDlg->ShowResultPos(FALSE);

				ShowSystemMessageBox("System", "請手動於圖片中選擇位置並按下\"Manual Check\"，完成後流程會繼續執行", TRUE);

				SystemStatusDlg->ShowManualClickResultShowButton(TRUE);
				StepFuncDlg->ShowManualClickResultShowButton(TRUE);
				RobotStepFuncDlg->ShowManualClickResultShowButton(TRUE);

				m_bManualClickResultCompelete = FALSE;

				do 
				{
					Delay(100);
				} while (m_bManualClickResultCompelete == FALSE);

				m_bManualClickResultCompelete = FALSE;

				SystemStatusDlg->ShowManualClickResultShowButton(FALSE);
				StepFuncDlg->ShowManualClickResultShowButton(FALSE);
				RobotStepFuncDlg->ShowManualClickResultShowButton(FALSE);

				CPoint Man_Point_R, Man_Point_L;

				if(SystemStatusDlg->IsWindowVisible() == TRUE)
					SystemStatusDlg->GetManualClickResult(Man_Point_R, Man_Point_L);

				if(StepFuncDlg->IsWindowVisible() == TRUE)
					StepFuncDlg->GetManualClickResult(Man_Point_R, Man_Point_L);

				if(RobotStepFuncDlg->IsWindowVisible() == TRUE)
					RobotStepFuncDlg->GetManualClickResult(Man_Point_R, Man_Point_L);

				Point_R.Point_X = Man_Point_R.x;
				Point_R.Point_Y = Man_Point_R.y;

				Point_L.Point_X = Man_Point_L.x;
				Point_L.Point_Y = Man_Point_L.y;

				SystemStatusDlg->ShowClickPos(CImageProc_PictureShowUnit::SHOW_CLICK_POS_NONE);
				StepFuncDlg->ShowClickPos(CImageProc_PictureShowUnit::SHOW_CLICK_POS_NONE);
				RobotStepFuncDlg->ShowClickPos(CImageProc_PictureShowUnit::SHOW_CLICK_POS_NONE);

				SystemStatusDlg->ShowResultPos(TRUE);
				StepFuncDlg->ShowResultPos(TRUE);
				RobotStepFuncDlg->ShowResultPos(TRUE);

				SystemStatusDlg->SetResultStatus(FALSE, Point_L, Point_R, 0, 0, 0);
				StepFuncDlg->SetResultStatus(Point_L, Point_R, 0, 0, 0);
				RobotStepFuncDlg->SetResultStatus_Tape(Point_L, Point_R, 0, 0, 0);

			}
			else
				return FALSE;

		}


		RetPoint_L = Point_L;
	
		RetPoint_R = Point_R;

		AlignmentData.N_dX1 = Point_L.Point_X;
		AlignmentData.N_dY1 = Point_L.Point_Y;

		AlignmentData.N_dX2 = Point_R.Point_X;
		AlignmentData.N_dY2 = Point_R.Point_Y;


		if(AlignmentProcess->Alignment(RecipeName, AlignmentData, Offset_X, Offset_Y, Offset_T) == false)
		{
			Offset_X = 0;
			Offset_Y = 0;
			Offset_T = 0;

			return FALSE;
		}

		double fPixelSize;

		AlignmentProcess->GetPixelSize(RecipeName, fPixelSize);


		Offset_X *= fPixelSize;
		Offset_Y *= fPixelSize;

		Offset_X = -Offset_X;
		Offset_Y = -Offset_Y;

		/*double Temp;
		Temp = Offset_X;
		Offset_X = Offset_Y;
		Offset_Y = Temp;*/

		if(fabs(Offset_X) > SystemParams->GetSystemParamData()->OverRange_mm_X && SystemParams->GetSystemParamData()->OverRange_mm_X != 0)
		{
			LOG->Message_Error(Log_Main, "X 超過範圍, 請確認!");

			if(SystemParams->GetSystemParamData()->bManualClickResult == TRUE)
				goto ManualSelectCheck;

			return FALSE;
		}

		if(fabs(Offset_Y) > SystemParams->GetSystemParamData()->OverRange_mm_Y && SystemParams->GetSystemParamData()->OverRange_mm_Y != 0)
		{
			LOG->Message_Error(Log_Main, "Y 超過範圍, 請確認!");

			if(SystemParams->GetSystemParamData()->bManualClickResult == TRUE)
				goto ManualSelectCheck;

			return FALSE;
		}

		if(fabs(Offset_T) > SystemParams->GetSystemParamData()->OverRange_mm_T && SystemParams->GetSystemParamData()->OverRange_mm_T != 0)
		{
			LOG->Message_Error(Log_Main, "T 超過範圍, 請確認!");

			if(SystemParams->GetSystemParamData()->bManualClickResult == TRUE)
				goto ManualSelectCheck;

			return FALSE;
		}

	}
	catch(SYSTEM_ERROR &e)
	{
		e.SetLocation("Do_MarkSearch");

		SystemStatusDlg->ShowClickPos(CImageProc_PictureShowUnit::SHOW_CLICK_POS_NONE);
		StepFuncDlg->ShowClickPos(CImageProc_PictureShowUnit::SHOW_CLICK_POS_NONE);

		SystemStatusDlg->ShowResultPos(TRUE);
		StepFuncDlg->ShowResultPos(TRUE);

		throw;

		return FALSE;
	}

	return TRUE;
}

BOOL CStepProcess_PCB::Do_WaitForRobotCalibrateSignal_ORG( DWORD Timeout )
{
	try
	{
	
		DWORD EndTime = GetTickCount() + Timeout;
		int nValue = 0;
		do 
		{
			Delay(100);

			EpsonRC_TCPIP_Ctrl->GetProgramValue("O_REQ_CAL_ORG", nValue);

		} while (nValue == 0 && GetTickCount() <= EndTime);

		if(GetTickCount() > EndTime)
			return FALSE;
	}
	catch(SYSTEM_ERROR &e)
	{
		e.SetLocation("Do_WaitForRobotCalibrateSignal_ORG");
		throw;

		return FALSE;
	}

	return TRUE;
}

BOOL CStepProcess_PCB::Do_WaitForRobotCalibrateSignal_DIS( DWORD Timeout )
{
	try
	{
		DWORD EndTime = GetTickCount() + Timeout;
		int nValue = 0;
		do 
		{
			Delay(100);

			EpsonRC_TCPIP_Ctrl->GetProgramValue("O_REQ_CAL_DISY", nValue);

		} while (nValue == 0 && GetTickCount() <= EndTime);

		if(GetTickCount() > EndTime)
			return FALSE;

	}
	catch(SYSTEM_ERROR &e)
	{
		e.SetLocation("Do_WaitForRobotCalibrateSignal_DIS");
		throw;

		return FALSE;
	}

	return TRUE;
}

BOOL CStepProcess_PCB::Do_WaitForRobotCalibrateSignal_ANGLE( DWORD Timeout )
{
	try
	{
		DWORD EndTime = GetTickCount() + Timeout;
		int nValue = 0;
		do 
		{
			Delay(100);

			EpsonRC_TCPIP_Ctrl->GetProgramValue("O_REQ_CAL_ANGLE", nValue);

		} while (nValue == 0 && GetTickCount() <= EndTime);

		if(GetTickCount() > EndTime)
			return FALSE;
	}
	catch(SYSTEM_ERROR &e)
	{
		e.SetLocation("Do_WaitForRobotCalibrateSignal_ANGLE");
		throw;

		return FALSE;
	}

	return TRUE;
}

BOOL CStepProcess_PCB::Proc_CCD_Calibrate()
{
	

	try
	{
		CP_CALIBRATE_DATA CalibrateData;
		double Score_L=0.0,Score_R=0.0;

		CString PatternFileName;
		int RecipeIndex = ProcessRecipe->Recipe_Data.st_RecipeInfo.nRcipeID;

		CString Pattern_Left = "Calibrate_L.ptn";
		CString Pattern_Right = "Calibrate_R.ptn";

		CString RecipeName = FormatString("Work%03d", RecipeIndex);

		POINT_DATA_2F Point_ORG_L;
		POINT_DATA_2F Point_ORG_R;

		POINT_DATA_2F Point_MOVE_L;
		POINT_DATA_2F Point_MOVE_R;

		POINT_DATA_2F Point_ROTATE_L;
		POINT_DATA_2F Point_ROTATE_R;

		DWORD nTimeout = 30000;
		DWORD nErrorCode = 0;
		int nRB_SigaleInput = 1;
		BOOL bRet = TRUE;

		
		EpsonRC_TCPIP_Ctrl->SetProgramValue("g_RecipeIndex", int(ProcessRecipe->Recipe_Data.st_RecipeInfo.nRcipeID));

		EpsonRC_TCPIP_Ctrl->SetProgramValue("g_RobotSpeed", SystemParams->GetSystemParamData()->RobotSpeed_Manual);
		EpsonRC_TCPIP_Ctrl->SetProgramValue("g_CheckTimeout_Signal", SystemParams->GetSystemParamData()->Robot_Handshake_Timeout);

		EpsonRC_TCPIP_Ctrl->SetProgramValue("g_CalDis", SystemParams->GetSystemParamData()->CCD_Calibrate_Distance);
		EpsonRC_TCPIP_Ctrl->SetProgramValue("g_CalAngle", SystemParams->GetSystemParamData()->CCD_Calibrate_Degree);

		//Execute Epson Job
		if(SystemParams->GetSystemParamData()->bPuttingMode == 1)
			EpsonRC_TCPIP_Ctrl->ExecuteControllerFunc(14);
		else
			EpsonRC_TCPIP_Ctrl->ExecuteControllerFunc(15);

		//Wait for Input signal
		if(Do_WaitForRobotCalibrateSignal_ORG(nTimeout) == FALSE)
		{
			nErrorCode = _ALARM_PROC_STEPPROCESS_PCB_RB_SIGNAL_ORG_TIMEOUT;
			throw SYSTEM_ERROR("Do_WaitForRobotCalibrateSignal_ORG", _MODULE_ERROR_PROCESS, &nErrorCode);
			return FALSE;
		}

		//In Org Position--------------
		if(SystemParams->m_SystemParamData.bDummyCamera == FALSE)
		{
			if(Do_MarkSearch(Pattern_Left, Pattern_Right, Point_ORG_L, Point_ORG_R, TRUE, FOV_ORG_TYPE_LEFTBOTTOM) == FALSE)
			{
				bRet = FALSE;
				nErrorCode = _ALARM_PROC_STEPPROCESS_PCB_PATTERN_FIND_FAIL;
				LOG->Message_Log(Log_Main, "Mark Search Result = NG");
				SystemStatusDlg->SetResultStatus(bRet, Point_ORG_L, Point_ORG_R, 0.0, 0.0, 0.0);
				StepFuncDlg->SetResultStatus(Point_ORG_L, Point_ORG_R, 0.0, 0.0, 0.0);

				EpsonRC_TCPIP_Ctrl->RobotStop();

				throw SYSTEM_ERROR("Do_MarkSearch", _MODULE_ERROR_PROCESS, &nErrorCode);
				return FALSE;
			}
			else
			{
				LOG->Message_Log(Log_Main, "Mark Search Result = OK");
				SystemStatusDlg->SetResultStatus(bRet, Point_ORG_L, Point_ORG_R, 0.0, 0.0, 0.0);
				StepFuncDlg->SetResultStatus(Point_ORG_L, Point_ORG_R, 0.0, 0.0, 0.0);
			}
		}
		else
		{
			LOG->Message_Log(Log_Main, "Mark Search Result = OK");
		}


		CalibrateData.N_dX1 = Point_ORG_L.Point_X;
		CalibrateData.N_dY1 = Point_ORG_L.Point_Y;
		CalibrateData.N_dX2 = Point_ORG_R.Point_X;
		CalibrateData.N_dY2 = Point_ORG_R.Point_Y;

		CalibrateData.Mst1_dX1 = Point_ORG_L.Point_X;
		CalibrateData.Mst1_dY1 = Point_ORG_L.Point_Y;
		CalibrateData.Mst2_dX1 = Point_ORG_R.Point_X;
		CalibrateData.Mst2_dY1 = Point_ORG_R.Point_Y;

		//EpsonRC_TCPIP_Ctrl->SetProgramValue("I_ACK_CAL_ORG", nRB_SigaleInput);

		//Wait for Input signal
		if(Do_WaitForRobotCalibrateSignal_DIS(nTimeout) == FALSE)
		{
			nErrorCode = _ALARM_PROC_STEPPROCESS_PCB_RB_SIGNAL_DIS_TIMEOUT;
			throw SYSTEM_ERROR("Do_WaitForRobotCalibrateSignal_DIS", _MODULE_ERROR_PROCESS, &nErrorCode);
			return FALSE;
		}


		//In DisY Position--------------
		if(SystemParams->m_SystemParamData.bDummyCamera == FALSE)
		{
			if(Do_MarkSearch(Pattern_Left, Pattern_Right, Point_MOVE_L, Point_MOVE_R, TRUE, FOV_ORG_TYPE_LEFTBOTTOM) == FALSE)
			{
				bRet = FALSE;
				nErrorCode = _ALARM_PROC_STEPPROCESS_PCB_PATTERN_FIND_FAIL;
				LOG->Message_Log(Log_Main, "Mark Search Result = NG");
				SystemStatusDlg->SetResultStatus(bRet, Point_MOVE_L, Point_MOVE_R, 0.0, 0.0, 0.0);
				StepFuncDlg->SetResultStatus(Point_MOVE_L, Point_MOVE_R, 0.0, 0.0, 0.0);

				EpsonRC_TCPIP_Ctrl->RobotStop();

				throw SYSTEM_ERROR("Do_MarkSearch", _MODULE_ERROR_PROCESS, &nErrorCode);
				return FALSE;
			}
			else
			{
				LOG->Message_Log(Log_Main, "Mark Search Result = OK");
				SystemStatusDlg->SetResultStatus(bRet, Point_MOVE_L, Point_MOVE_R, 0.0, 0.0, 0.0);
				StepFuncDlg->SetResultStatus(Point_MOVE_L, Point_MOVE_R, 0.0, 0.0, 0.0);
			}
		}
		else
		{
			LOG->Message_Log(Log_Main, "Mark Search Result = OK");
		}

		CalibrateData.Mst1_dX2 = Point_MOVE_L.Point_X;
		CalibrateData.Mst1_dY2 = Point_MOVE_L.Point_Y;
		CalibrateData.Mst2_dX2 = Point_MOVE_R.Point_X;
		CalibrateData.Mst2_dY2 = Point_MOVE_R.Point_Y;

		//EpsonRC_TCPIP_Ctrl->SetProgramValue("I_ACK_CAL_DISY", nRB_SigaleInput);

		//Wait for Input signal
		if(Do_WaitForRobotCalibrateSignal_ANGLE(nTimeout) == FALSE)
		{
			nErrorCode = _ALARM_PROC_STEPPROCESS_PCB_RB_SIGNAL_ANGLE_TIMEOUT;
			throw SYSTEM_ERROR("Do_WaitForRobotCalibrateSignal_ANGLE", _MODULE_ERROR_PROCESS, &nErrorCode);
			return FALSE;
		}

		if(SystemParams->m_SystemParamData.bDummyCamera == FALSE)
		{
			//In Angle Position--------------
			if(Do_MarkSearch(Pattern_Left, Pattern_Right, Point_ROTATE_L, Point_ROTATE_R, TRUE, FOV_ORG_TYPE_LEFTBOTTOM) == FALSE)
			{
				bRet = FALSE;
				nErrorCode = _ALARM_PROC_STEPPROCESS_PCB_PATTERN_FIND_FAIL;
				LOG->Message_Log(Log_Main, "Mark Search Result = NG");
				SystemStatusDlg->SetResultStatus(bRet, Point_ROTATE_L, Point_ROTATE_R, 0.0, 0.0, 0.0);
				StepFuncDlg->SetResultStatus(Point_ROTATE_L, Point_ROTATE_R, 0.0, 0.0, 0.0);

				EpsonRC_TCPIP_Ctrl->RobotStop();

				throw SYSTEM_ERROR("Do_MarkSearch", _MODULE_ERROR_PROCESS, &nErrorCode);
				return FALSE;
			}
			else
			{
				LOG->Message_Log(Log_Main, "Mark Search Result = OK");
				SystemStatusDlg->SetResultStatus(bRet, Point_ROTATE_L, Point_ROTATE_R, 0.0, 0.0, 0.0);
				StepFuncDlg->SetResultStatus(Point_ROTATE_L, Point_ROTATE_R, 0.0, 0.0, 0.0);
			}
		}
		else
		{
			LOG->Message_Log(Log_Main, "Mark Search Result = OK");
		}

		CalibrateData.TN_dX1 = Point_ROTATE_L.Point_X;
		CalibrateData.TN_dY1 = Point_ROTATE_L.Point_Y;
		CalibrateData.TN_dX2 = Point_ROTATE_R.Point_X;
		CalibrateData.TN_dY2 = Point_ROTATE_R.Point_Y;
		
		//EpsonRC_TCPIP_Ctrl->SetProgramValue("I_ACK_CAL_ANGLE", nRB_SigaleInput);

		if(AlignmentProcess->Calibrate(RecipeName, CalibrateData, SystemParams->m_SystemParamData.CCD_Calibrate_Distance, SystemParams->m_SystemParamData.CCD_Calibrate_Degree) == false)
			bRet = FALSE;
			
		DWORD EndTime = GetTickCount() + 30000;

		bool bProgramError = false;
		bool bError = false;
		bool bReady = false;

		do 
		{
			Delay(500);
			bProgramError = InputControl->GetInput(X030_RB_PRG_ERR);
			bError = InputControl->GetInput(X027_RB_ERROR);
			bReady = InputControl->GetInput(X025_RB_READY);

		} while (bProgramError == false && bError == false && bReady == false && GetTickCount() <= EndTime);

		if(bError == true)
		{
			CString StatusCode, ErrorCode;
			EpsonRC_TCPIP_Ctrl->GetStatus(StatusCode, ErrorCode);
			DWORD nErrorCode = strtol((LPCSTR)ErrorCode, NULL, 16);
			throw SYSTEM_ERROR("CStepProcess_PCB::Proc_CCD_Calibrate", _MODULE_ERROR_EPSON_RC, &nErrorCode);
			return FALSE;
		}
		else if(bProgramError == true)
		{
			int nErrorCode = 0;
			EpsonRC_TCPIP_Ctrl->GetProgramValue("g_ErrorCode", nErrorCode);
			throw SYSTEM_ERROR("CStepProcess_PCB::Proc_CCD_Calibrate", _MODULE_ERROR_EPSON_RC, &nErrorCode);
			return FALSE;
		}
		else if(bReady == false)
		{
			DWORD nErrorCode = _ALARM_PROC_STEPPROCESS_ROBOT_CALI_PCB_TIMEOUT;
			throw SYSTEM_ERROR("CStepProcess_PCB::Proc_CCD_Calibrate", _MODULE_ERROR_PROCESS, &nErrorCode);

			EpsonRC_TCPIP_Ctrl->RobotStop();

			return FALSE;
		}

		LOG->Message_Log(Log_Main, "CCD Calibrate Request End");
		
	}
	catch(SYSTEM_ERROR &e)
	{
		e.SetLocation("Proc_CCD_Calibrate");
		throw;

		return FALSE;
	}

	return TRUE;
}

BOOL CStepProcess_PCB::Proc_CCD_Align(double &dOffset_X, double &dOffset_Y, double &dOffset_T)
{
	DWORD StartTick = ::GetTickCount();
	BOOL bRet = FALSE;

	try
	{
		
		LOG->Message_Log(Log_Main, "CCD Alignment Request Start");

		POINT_DATA_2F Point_L;
		POINT_DATA_2F Point_R;

		BOOL bSave = SystemParams->GetSystemParamData()->bAlwaysSaveImage;

		bRet = Do_CCDAlign(Point_L, Point_R, dOffset_X, dOffset_Y, dOffset_T, bSave);

		LOG->Message_Log(Log_Main, "CCD Alignment Request Complete");

		if(bRet == TRUE)
		{
			LOG->Message_Log(Log_Main, "CCD Alignment Result = OK, Offset_X = %.3lf, Offset_Y = %.3lf", dOffset_X, dOffset_Y, dOffset_T);
			SystemStatusDlg->SetResultStatus(bRet, Point_L, Point_R, dOffset_X, dOffset_Y, dOffset_T);
		}
		else
		{
			LOG->Message_Log(Log_Main, "CCD Alignment Result = NG, Offset_X = %.3lf, Offset_Y = %.3lf", dOffset_X, dOffset_Y, dOffset_T);
			SystemStatusDlg->SetResultStatus(bRet, Point_L, Point_R, dOffset_X, dOffset_Y, dOffset_T);
		}


		if(bRet == FALSE)
			ImageGraber_Hikvision->SaveGrabSigleImageBuffer(m_FilePath_Org);
		else
		{
			if(SystemParams->GetSystemParamData()->bAlwaysSaveImage == TRUE)
			{
				ImageGraber_Hikvision->SaveGrabSigleImageBuffer(m_FilePath_Org);

				ImageGraber_Hikvision->SaveGrabSigleImageBufferWithLabel(m_FilePath_Ret, (UINT)m_nImagePosL_X, (UINT)m_nImagePosL_Y, (UINT)m_nImagePosR_X, (UINT)m_nImagePosR_Y);
			}
		}

		VECTOR_DATA_2 OrgVec;
		VECTOR_DATA_2 RetVec;

		OrgVec.Vector_X = ProcessRecipe->Recipe_Data.st_RecipeData.nOrgPosPixel_RX - ProcessRecipe->Recipe_Data.st_RecipeData.nOrgPosPixel_LX;
		OrgVec.Vector_Y = ProcessRecipe->Recipe_Data.st_RecipeData.nOrgPosPixel_RY - ProcessRecipe->Recipe_Data.st_RecipeData.nOrgPosPixel_LY;

		RetVec.Vector_X = Point_R.Point_X - Point_L.Point_X;
		RetVec.Vector_Y = Point_R.Point_Y - Point_L.Point_Y;

		double Length_Org = Vector_Length(OrgVec);
		double Length_Ret = Vector_Length(RetVec);

		if(Length_Ret > (Length_Org * 1.2) || Length_Ret < (Length_Org * 0.8))
		{
			LOG->Message_Warning(Log_Main, "Length is out of the range");
			return FALSE;
		}

		TRACE("Time = %d", ::GetTickCount() - StartTick);

	}
	catch(SYSTEM_ERROR &e)
	{
		e.SetLocation("Do_ProductPosDetectProces");
		throw;

		return FALSE;
	}

	return bRet;
}

BOOL CStepProcess_PCB::Do_ManualClickResultComplete()
{
	m_bManualClickResultCompelete = TRUE;

	return TRUE;
}