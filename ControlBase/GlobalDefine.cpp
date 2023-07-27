#include "stdafx.h"
#include "ShadeButtonST.h"
#include "GlobalDefine.h"

bool SetSystemAutoRun(bool bCheck)
{
	
	if(bCheck)
	{
		/*if( SystemParams->GetInterLockCheck() == TRUE)
		{
			if(StepProcess->CheckSystemInterlockOpen() == TRUE)
			{
				ShowSystemMessageBox("系統", "於執行自動流程前，請關閉安全門...", true);
				return false;
			}
		}*/

		if (ControlBase->GetEQState() == STATUS_DOWN || ControlBase->GetEQState() == STATUS_ALARM)
		{
			AfxMessageBox("機台未進行初始化!!\nEQ is not be initialed!!", MB_OK);
			return false;
		}

		if(WaitForSingleObject(g_hPause, 0) == WAIT_OBJECT_0)
		{
			if (IDYES == AfxMessageBox("請問是否要取消暫停狀態，請確認?\nIt will cancel Pause Statu\nYes or No?" , MB_YESNO | MB_ICONQUESTION ))
			{
				::ResetEvent(g_hPause) ;
			}
		}
		else
		{
			if (IDYES == AfxMessageBox("機台是否安全? 若未進行檢查，可能造成無法預期之結果  請確認!\nIs EQ in safe status? it will be cause unexpected result, please check!" , MB_YESNO | MB_ICONQUESTION ))
			{
				//SystemStatusDlg->SetByPassMode(false);

				//StepProcess->LockSystemInterLock(false);

				AutoTread->Initial();

				::ResetEvent(g_hBreak) ;
				::ResetEvent(g_hPause) ;
				::SetEvent(g_hAutoRun) ;
				ControlBase->SetEQMode(MODE_AUTO);
				ControlBase->SetEQState(STATUS_RUN) ;

				ControlBase->SetEQLED(GREEN);

				return true;
			}
		}
	}
	else
	{
		//SystemStatusDlg->SetByPassMode(false);

		//StepProcess->LockSystemInterLock(false);

		AutoTread->Initial();

		::ResetEvent(g_hBreak) ;
		::ResetEvent(g_hPause) ;
		::SetEvent(g_hAutoRun) ;


		ControlBase->SetEQState(STATUS_RUN) ;

		ControlBase->SetEQLED(GREEN);

		return true;
	}
	
	return false;
}

AFX_EXT_API bool SetSystemAuto( bool bCheck/*=true*/ )
{
	if (IDYES == AfxMessageBox("機台是否切換至自動模式下?" , MB_YESNO | MB_ICONQUESTION ))
	{
		ShowSystemMessageBox("系統", "機台於自動模式下", true);

		
		ControlBase->SetEQMode(MODE_AUTO);

		ControlBase->SetEQState(STATUS_INITIAL) ;

		ControlBase->SetEQLED(GREEN_FLASH);

		return true;
	}

	return false;
}

AFX_EXT_API bool SetSystemManual( bool bCheck/*=true*/ )
{

	if (IDYES == AfxMessageBox("機台是否切換至手動模式下?" , MB_YESNO | MB_ICONQUESTION ))
	{
		::ResetEvent(g_hAutoRun) ;
		::ResetEvent(g_hPause) ;

		ShowSystemMessageBox("系統", "等待停止中...", false);

		do 
		{
			Delay(1000);
		} while (AutoTread->CheckProcessing() == TRUE);

		ShowSystemMessageBox("系統", "機台於手動模式下", true);

		//OutputControl->SetOutput(Y021_REQ_CV_STOP, true);

		if(GetSystemStatus() == STATUS_ALARM || GetSystemStatus() == STATUS_DOWN)
			return true;

		ControlBase->SetEQMode(MODE_MANUAL);

		ControlBase->SetEQState(STATUS_MANUAL) ;

		ControlBase->SetEQLED(YELLOW);

		return true;
	}

	return false;
}

bool SetSystemStop(bool bAsk)
{
	if(bAsk)
	{
		if (IDYES == AfxMessageBox("要停止動作嗎?\nIt will be stop\nYes or No?" , MB_YESNO | MB_ICONQUESTION ))
		{

			::SetEvent(g_hBreak) ;
			::ResetEvent(g_hAutoRun) ;
			::ResetEvent(g_hPause) ;

			ShowSystemMessageBox("系統", "機台停止中，請等待", false);

			do 
			{
				Delay(1000);
			} while (AutoTread->CheckProcessing() == TRUE);

			//OutputControl->SetOutput(Y021_REQ_CV_STOP, true);

			ShowSystemMessageBox("系統", "機台已停止", true);

			ControlBase->SetEQState(STATUS_EQ_STOP) ;

			ControlBase->SetEQLED(RED);

			return true;
		}
		else
			return false;
	}
	else
	{
		
		::SetEvent(g_hBreak) ;

		::ResetEvent(g_hAutoRun) ;
		::ResetEvent(g_hPause) ;

		ShowSystemMessageBox("系統", "機台停止中，請等待", false);

		do 
		{
			Delay(1000);
		} while (AutoTread->CheckProcessing() == TRUE);

		//OutputControl->SetOutput(Y021_REQ_CV_STOP, true);

		ShowSystemMessageBox("系統", "機台已停止", true);

		ControlBase->SetEQState(STATUS_EQ_STOP) ;

		ControlBase->SetEQLED(RED);

		return true;  
	
	}

	return false;
}

bool SetSystemPause(bool bAsk)
{
	if (IDYES == AfxMessageBox("要中途暫停嗎?\nIt will be Pause\nYes or No" , MB_YESNO | MB_ICONQUESTION ))
	{
		::SetEvent(g_hPause) ;
		return true;
	}
	return false;
}

bool SetSystemAlarm()
{

	::ResetEvent(g_hAutoRun) ;
	::ResetEvent(g_hPause) ;

	::SetEvent(g_hBreak) ;

	if(ControlBase != NULL)
	{
		ControlBase->SetEQState(STATUS_ALARM);
		ControlBase->SetEQMode(MODE_MANUAL);

		ControlBase->SetEQLED(RED_FLASH | BUZZER_1);

	}
	

	return true;
}

bool SetSystemWarning(UINT nWarningCode)
{
	CString Msg;
	Msg = SystemCodeCtrl->GetCode(_CODE_WARNING_, nWarningCode);

	LOG->Message_Warning(Log_Main, "警告碼 = %04X; %s", nWarningCode, Msg);

	return false;
}

bool SetSystemTerminate()
{
	//StepProcess->LockSystemInterLock(true);
	ControlBase->ShutDownSystem();

	return true;
}

void SetSystemLanguage(UINT nType)
{
	ControlBase->SetCurrentLang(nType);
}

void SetSystemInterlock( BOOL bOpen )
{
	
	try
	{
		if(bOpen == TRUE)
			StepProcess->LockSystemInterLock(true);
		else
			StepProcess->LockSystemInterLock(false);
	}
	catch(SYSTEM_ERROR &e)
	{
		e.SetLocation("SetSystemInterlock");
		throw;

		return;
	}

	return;
}

BOOL GetSystemInterlockOpen()
{
	BOOL bRet = FALSE;

	try
	{
		bRet = StepProcess->CheckSystemInterlockOpen();
	}
	catch(SYSTEM_ERROR &e)
	{
		e.SetLocation("GetSystemInterlockOpen");
		throw;

		return FALSE;
	}

	return bRet;
}

BOOL GetSystemInterlockCommand()
{
	BOOL bRet = FALSE;

	try
	{
		bRet = StepProcess->CheckSystemInterlockCommand();
	}
	catch(SYSTEM_ERROR &e)
	{
		e.SetLocation("GetSystemInterlockOpen");
		throw;

		return FALSE;
	}

	return bRet;
}

bool CheckPauseStop(void)
{

	//!機台SOTP事件
	if (WaitForSingleObject(g_hBreak , 0) == WAIT_OBJECT_0)
	{
		//if(ControlBase != NULL)
			//ControlBase->SetEQState(EQUIPMENTSTATUS::STATUS_STOP, EQ_Buzzer_Type2);

		ResetEvent(g_hPause) ;		//!<不允許暫停
		return (false) ;
	}

	//!機台暫停事件
	if(WaitForSingleObject(g_hPause, 0) == WAIT_OBJECT_0)
	{
		//if(ControlBase != NULL)
			//ControlBase->SetEQState(EQUIPMENTSTATUS::STATUS_PAUSE, EQ_Buzzer_Type2);

		while(true)
		{
			Sleep(50);

			if(WaitForSingleObject(g_hPause, 0) != WAIT_OBJECT_0)
			{
				break;
			}

			if(WaitForSingleObject(g_hBreak, 0) == WAIT_OBJECT_0)
			{
				ResetEvent(g_hPause);
				return (false) ;
			}
		}
	}

	return (true) ;
}


bool SetSystemInitial( CWnd* pParent, CWnd* pLogParent, CRect FucntionArea, CRect LogArea)
{
	//參數初始化
	TCHAR tcPath[MAX_PATH];
	TCHAR tcDriver[MAX_PATH];
	TCHAR tcDir[MAX_PATH];

	::GetModuleFileName(AfxGetInstanceHandle(), tcPath, MAX_PATH);
	_tsplitpath(tcPath, tcDriver, tcDir, NULL, NULL);
	Project_Path.Format("%s%s", tcDriver, tcDir);

	g_hExit			= CreateEvent(NULL, TRUE, FALSE, NULL);
	g_hBreak		= CreateEvent(NULL, TRUE, FALSE, NULL);
	g_hAutoRun		= CreateEvent(NULL, TRUE, FALSE, NULL);
	g_hPause		= CreateEvent(NULL, TRUE, FALSE, NULL);
	g_hInitial		= CreateEvent(NULL, TRUE, FALSE, NULL);

	SystemCodeCtrl = new CSystemCodeCtrl();

	m_pLogServer = new LogServer(pLogParent);
	
	LOG = new LogClient();

	LanguageCtrl = new CLanguageCtrl();

	SystemParams = new CSystemParams("MachineSetting.ini");

	SystemParams->Load();

	//HikvisionGrabberDlg = new CHikvisionGrabberDlg(pParent);

	//ImageGraber_Hikvision = new CImageGraber_Hikvision("CCD", "CCD", "192.168.100.1", LOG, HikvisionGrabberDlg, "New");

	//ImageGraber_Hikvision_Sticker = new CImageGraber_Hikvision("CCD_S", "CCD_S", "192.168.101.1", LOG, HikvisionGrabberDlg, "New1");

	ControlBase = new CControlBase(pParent, pLogParent, FucntionArea, LogArea);
	
	ProcessRecipe = new CGetRecipe(Project_Path);

	StepProcess = new CStepProcess();

	Dynamic_Thread = new CDynamic_Thread();

	Scenario = new CScenario();

	AutoTread = new CAutoThread();
	
	//ImageProc_PatternFind_MIL = new CImageProc_PatternFind_MIL(Project_Path + "Recipe\\MarkSearchProc", LOG);

	//ImageProc_PatternFind_MIL_Sticker = new CImageProc_PatternFind_MIL(Project_Path + "Recipe\\MarkSearchProc_Sticker", LOG);

	//AlignmentProcess = new CAlignmentProcess("Alignment_PCB", FALSE);

	//AlignmentProcess_Sticker = new CAlignmentProcess("Alignment_Sticker", FALSE);
	//
	//IO_CentralCtrl_DAQ = new CIO_CentraCtrl_DAQ(SystemParams->GetSystemParamData()->bDummyHardware);

	//InputControl = new CInputControl();

	//OutputControl = new COutputControl();

	PerformanceLog = new CPerformanceLog(19, 30);

	//建立視窗
	SystemMessageBox = new CMessageBox();

	OptionDlg = new COptionDlg(pParent);

	OptionManualSelDlg = new COptionManualSelDlg(pParent);

	InputTestDlg = new CInputTestDlg(pParent);

	OutputTestDlg = new COutputTestDlg(pParent);

	UserAccountDlg = new CUserAccountDlg(pParent);

	SystemParamsDlg = new CSystemParamsDlg(SystemParams, pParent);

	RecipeSettingDlg = new CRecipeSettingDlg(pParent, Project_Path, ProcessRecipe);

	RecipeSettingCurrentDlg = new CRecipeSettingCurrentDlg(pParent, Project_Path, ProcessRecipe);

	RecipeListDlg = new CRecipeListDlg(pParent, Project_Path, ProcessRecipe);

	SystemStatusDlg = new CSystemStatusDlg(pParent);

	MaintainPageDlg = new CMaintainPageDlg(SystemParams, pParent);
	
	//StepFuncDlg = new CStepFuncDlg_PCB(pParent);

	//StepFuncDlg_Sticker = new CStepFuncDlg_Sticker(pParent);

	//ImageProc_PatternFimd_MIL_DLG = new CImageProc_PatternFimd_MIL_DLG(pParent, ImageProc_PatternFind_MIL, LOG, GetCameraPicture);

	//ImageProc_PatternFimd_MIL_DLG->RegParameterSaveToCallBack(ControlBase->PatternOrgSaveCallBack);

	//ImageProc_PatternFimd_MIL_DLG->RegGetSystemRecipeFileNameCallBack(GetSystemRecipeFileName);

	//ImageProc_PatternFimd_MIL_DLG->RegParameterLoadCallBack(ControlBase->PatternParameterLoadCallBack);


	//ImageProc_PatternFimd_MIL_DLG_Sticker = new CImageProc_PatternFimd_MIL_DLG(pParent, ImageProc_PatternFind_MIL_Sticker, LOG, GetCameraPicture_Sticker);

	/*ImageProc_PatternFimd_MIL_DLG_Sticker->RegParameterSaveToCallBack(ControlBase->PatternOrgSaveCallBack_Sticker);

	ImageProc_PatternFimd_MIL_DLG_Sticker->RegGetSystemRecipeFileNameCallBack(GetSystemRecipeFileName);

	ImageProc_PatternFimd_MIL_DLG_Sticker->RegParameterLoadCallBack(ControlBase->PatternParameterLoadCallBack_Sticker);


	ImageProc_PatternFimd_MIL_Cali_DLG = new CImageProc_PatternFimd_MIL_DLG(pParent, ImageProc_PatternFind_MIL, LOG, GetCameraPicture);

	ImageProc_PatternFimd_MIL_Cali_DLG->RegParameterSaveToCallBack(ControlBase->PatternOrgSaveCallBack);

	ImageProc_PatternFimd_MIL_Cali_DLG->RegGetSystemRecipeFileNameCallBack(GetSystemCaliFileName);

	ImageProc_PatternFimd_MIL_Cali_DLG->RegParameterLoadCallBack(ControlBase->PatternParameterLoadCallBack);


	ImageProc_PatternFimd_MIL_DLG_Cali_Sticker = new CImageProc_PatternFimd_MIL_DLG(pParent, ImageProc_PatternFind_MIL_Sticker, LOG, GetCameraPicture_Sticker);

	ImageProc_PatternFimd_MIL_DLG_Cali_Sticker->RegParameterSaveToCallBack(ControlBase->PatternOrgSaveCallBack_Sticker);

	ImageProc_PatternFimd_MIL_DLG_Cali_Sticker->RegGetSystemRecipeFileNameCallBack(GetSystemCaliFileName);

	ImageProc_PatternFimd_MIL_DLG_Cali_Sticker->RegParameterLoadCallBack(ControlBase->PatternParameterLoadCallBack_Sticker);*/


	//RobotStepFuncDlg = new CRobotStepFuncDlg(pParent);

	//EpsonRC_TCPIP_Ctrl = new CEpsonRC_TCPIP_Ctrl();

	SystemTraceDlg = new CSystemTraceDlg(pParent);

	LogListDlg = new CLogListDlg(SystemParams->GetSystemParamData()->LogSavePath, pParent);

	PerformanceDlg = new CPerformanceDlg(PerformanceLog, pParent);

	Product_Data = new CProduct_Data("CV");
	
	return false;

}

bool SetSystemEnable()
{
	
	CRect LogServerClient = ControlBase->m_LogArea;

	m_pLogServer->Create(LOG_SERVER_NAME, SystemParams->GetSystemParamData()->LogSavePath, 2);

	m_pLogServer->AddLogWindow("ControlLog", "Log");
	m_pLogServer->AddLogWindow("TraceLog", "Trace");
	
	m_pLogServer->SetParent(ControlBase->GetMainLogDlg());

	m_pLogServer->SetLogWindowPos(LogServerClient.left + 4 , LogServerClient.top + 4, LogServerClient.Width() - 4, LogServerClient.Height() - 4);

	m_pLogServer->Start();

	LOG->Connect(LOG_SERVER_NAME);
	
	if(ControlBase->EnableSystem() != true)
		return false;

	return true;
}

bool SystemLogin( CString sID, CString sName, UINT nLevel )
{
	
	ControlBase->SetOperatorID(sID);
	ControlBase->SetAccessClass(nLevel);
	ControlBase->SetOperatorName(sName);

	OptionDlg->SetOptionClass(nLevel);

	return true;
}

bool SystemLogout()
{

	ControlBase->SetOperatorID("");
	ControlBase->SetAccessClass(1);
	ControlBase->SetOperatorName("");

	OptionDlg->SetOptionClass(1);

	return true;
}

CString GetOperatorName()
{
	return ControlBase->GetOperatorName();
}

UINT GetSystemLanguage()
{
	return ControlBase->GetLastLang();
}

AFX_EXT_API UINT GetSystemMode()
{
	return ControlBase->GetEQMode();
}

AFX_EXT_API UINT GetSystemStatus()
{
	return ControlBase->GetEQState();
}

AFX_EXT_API CString GetSystemID()
{
	return SystemParams->GetMachineID();
}

AFX_EXT_API DWORD GetSystemAutoLogoutTime()
{
	return SystemParams->GetSystemParamData()->nAutoLogoutTime;
}

AFX_EXT_API CString GetSystemLastRecipeName()
{
	return ProcessRecipe->GetRecipeName();
}

AFX_EXT_API CString GetSystemRecipeFileName()
{
	return ProcessRecipe->GetRecipeFileName();
}

AFX_EXT_API CString GetSystemCaliFileName()
{
	return "Calibrate.rcp";
}

AFX_EXT_API void GetSystemRecipeList(std::vector<CString> &RecipeList)
{

	CGetRecipe::RECIPE_INDEX_INFO info ;
	CStringList cListrecipedata ;
	CString RecipeName;
	int recipe_no;
	POSITION pos;

	CGetRecipe getRecipe(Project_Path);

	recipe_no = getRecipe.GetTotalRecipeName(cListrecipedata) ;
	pos = cListrecipedata.GetHeadPosition();

	for(int x = 0; x < recipe_no; x++)
	{
		RecipeName = cListrecipedata.GetNext(pos);
		
		ProcessRecipe->GetRecipeIndexInfo(RecipeName, info);


		RecipeList.push_back(info.csRecipeName);
	}
	
}

AFX_EXT_API void GetSystemRecipeFileList(std::vector<CString> &RecipeFileList)
{

	CGetRecipe::RECIPE_INDEX_INFO info ;
	CStringList cListrecipedata ;
	CString RecipeName;
	int recipe_no;
	POSITION pos;

	CGetRecipe getRecipe(Project_Path);

	recipe_no = getRecipe.GetTotalRecipeName(cListrecipedata) ;
	pos = cListrecipedata.GetHeadPosition();

	for(int x = 0; x < recipe_no; x++)
	{
		RecipeName = cListrecipedata.GetNext(pos);
		
		RecipeFileList.push_back(RecipeName);
	}

}

AFX_EXT_API bool SetSystemRecipe( CString sFileName )
{
	if(ProcessRecipe->LoadRecipe(sFileName) == false)
	{
		LOG->Message_Error(Log_Main, "目標參數載入失敗，請確認參數檔案是否存在");
		return FALSE;
	}

	CPoint Center;
	Center.x = LONG(ProcessRecipe->Recipe_Data.st_RecipeData.nOrgPosPixel_LX);
	Center.y = LONG(ProcessRecipe->Recipe_Data.st_RecipeData.nOrgPosPixel_LY);

	//Save Last Recipe Name
	WritePrivateProfileString("LastRecipeName","RecipeName", sFileName, Project_Path + "\\CtrlPrms\\MachineSetting.ini");

	return true;
}

void ShowSystemMessageBox( CString CaptureText, CString Message, bool ShowButton, bool AutoClose /*= false*/, DWORD WaitTime /*= 5000*/ )
{
	SystemMessageBox->ShowMessage(CaptureText, Message, ShowButton, AutoClose, WaitTime);
}

AFX_EXT_API INT_PTR ShowSystemQestionBox( CString CaptureText, CString Message )
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState( ));

	CMessageBoxYC MessageBoxYC;

	INT_PTR nRet = MessageBoxYC.ShowMessageBox(CaptureText, Message);

	return nRet;
}

void HideSystemMessageBox()
{
	SystemMessageBox->CloseMessage();
}

void ShowOptionDlg()
{
	try
	{
	
		HideAllDlg();

		CRect ClientRect;
		OptionDlg->GetClientRect(&ClientRect);
		OptionDlg->MoveWindow(	ControlBase->m_FunctionArea.left + 5, 
								ControlBase->m_FunctionArea.top + 5,
								ClientRect.Width(), 
								ClientRect.Height());

		OptionDlg->ShowWindow(SW_SHOW);
		
	}
	catch(SYSTEM_ERROR &e)
	{
		e.SetLocation("ShowOptionDlg()");
		LOG->Message_Error(Log_Main, e.GetErrorMessage());

		return;
	}

	return;

}

AFX_EXT_API void ShowOptionManualSelDlg()
{
	try
	{

		HideAllDlg();

		CRect ClientRect;
		OptionManualSelDlg->GetClientRect(&ClientRect);
		OptionManualSelDlg->MoveWindow(	ControlBase->m_FunctionArea.left + 5, 
										ControlBase->m_FunctionArea.top + 5,
										ClientRect.Width(), 
										ClientRect.Height());

		OptionManualSelDlg->ShowWindow(SW_SHOW);

	}
	catch(SYSTEM_ERROR &e)
	{
		e.SetLocation("ShowOptionManualSelDlg()");
		LOG->Message_Error(Log_Main, e.GetErrorMessage());

		return;
	}

	return;
}

void ShowSystemStatusDlg()
{
	
	HideAllDlg();
	CRect ClientRect;
	SystemStatusDlg->GetClientRect(&ClientRect);
	SystemStatusDlg->MoveWindow(	ControlBase->m_FunctionArea.left + 5, 
									ControlBase->m_FunctionArea.top + 5,
									ClientRect.Width(), 
									ClientRect.Height());
	SystemStatusDlg->ShowWindow(SW_SHOW);
}

void HideAllDlg()
{

	OptionDlg->ShowWindow(SW_HIDE);

	OptionManualSelDlg->ShowWindow(SW_HIDE);

	InputTestDlg->ShowWindow(SW_HIDE);

	OutputTestDlg->ShowWindow(SW_HIDE);

	UserAccountDlg->ShowWindow(SW_HIDE);

	SystemParamsDlg->ShowWindow(SW_HIDE);

	RecipeSettingDlg->ShowWindow(SW_HIDE);

	RecipeSettingCurrentDlg->ShowWindow(SW_HIDE);

	RecipeListDlg->ShowWindow(SW_HIDE);

	SystemStatusDlg->ShowWindow(SW_HIDE);

	MaintainPageDlg->ShowWindow(SW_HIDE);

	//StepFuncDlg->ShowWindow(SW_HIDE);

	LogListDlg->ShowWindow(SW_HIDE);

	PerformanceDlg->ShowWindow(SW_HIDE);



}

AFX_EXT_API void ForceKillProgram()
{
	//取得最高權限
	HANDLE              hToken = NULL;
	LUID                Luid = {0};
	TOKEN_PRIVILEGES    tp = {0};

	if (!OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES|TOKEN_QUERY, &hToken))
	{
		CloseHandle(hToken);
		return;
	}
	if (!LookupPrivilegeValue(NULL, SE_DEBUG_NAME, &Luid))
	{
		CloseHandle(hToken);
		return;
	}

	tp.PrivilegeCount = 1;
	tp.Privileges[0].Luid = Luid;
	tp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
	if (!AdjustTokenPrivileges(hToken, FALSE, &tp, sizeof(tp), NULL, NULL))
	{
		CloseHandle(hToken);
		return;
	}

	//關閉目前程序

	PROCESSENTRY32 Entry;
	HANDLE hSnapShot;
	BOOL ret;

	hSnapShot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if(hSnapShot==INVALID_HANDLE_VALUE)
	{
		printf("CreateToolhelp32Snapshot fail.\n");
	}

	Entry.dwSize = sizeof(PROCESSENTRY32);
	ret = Process32First(hSnapShot, &Entry);
	while(ret)
	{
		if(Entry.th32ProcessID == GetCurrentProcessId())
		{
			DWORD ExitCode;

			HANDLE hProcess = NULL;
			hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, Entry.th32ProcessID);

			BOOL FLAG = GetExitCodeProcess(hProcess, &ExitCode);
			if(FLAG)
			{
				TerminateProcess(hProcess, ExitCode);
			}
		}

		ret = Process32Next(hSnapShot, &Entry);
	}
	CloseHandle(hSnapShot);
	CloseHandle(hToken);


}

AFX_EXT_API void SetSystemMotionInitial()
{
	ControlBase->StartInitialSystem();

}

AFX_EXT_API void SetLogMessage_Normal( CString Message )
{
	LOG->Message_Log(Log_Main, Message);
}

AFX_EXT_API void SetLogMessage_Warning( CString Message )
{
	LOG->Message_Warning(Log_Main, Message);
}

AFX_EXT_API void SetLogMessage_Error( CString Message )
{
	LOG->Message_Error(Log_Main, Message);
}

AFX_EXT_API bool ResetSystemBuzzer()
{
	try
	{
		TRACE("The system Buzzer has operated");
	}
	catch(SYSTEM_ERROR &e)
	{
		e.SetLocation("ResetSystemBuzzer");
		LOG->Message_Error(Log_Main, e.GetErrorMessage());
		SystemMessageBox->ShowWindow(SW_HIDE);
		return false;
	}

	return true;
}

AFX_EXT_API bool ResetSystemAlarm()
{
	try
	{
		if(GetSystemMode() == MODE_AUTO)
		{
			ShowSystemMessageBox("系統", "目前機台處於自動模式，請切換至手動模式後再進行錯誤清除", true);
			return false;
		}

		ResetEvent(g_hBreak);

		ShowSystemMessageBox("系統", "清除機台錯誤，請等待...", false);

		ShowSystemMessageBox("系統", "機台錯誤已清除!", true);
		
		ControlBase->SetEQState(STATUS_MANUAL);
		ControlBase->SetEQLED(YELLOW);
	}
	catch(SYSTEM_ERROR &e)
	{
		e.SetLocation("ResetSystemAlarm");
		LOG->Message_Error(Log_Main, e.GetErrorMessage());
		SystemMessageBox->ShowWindow(SW_HIDE);
		return false;
	}

	return true;
}

AFX_EXT_API CString GetCameraPicture(int nThreshold, int nBlur)
{
	CString FilePath_Org;

	try
	{
		CDiskObject DiskObject;
		CTime cur_tm = CTime::GetCurrentTime();
		CString csDate, OrgLable, FileDirectory;

		csDate = cur_tm.Format("%Y-%m-%d");
		OrgLable = cur_tm.Format("FlatEdge_ORG_%Y-%m-%d-%H-%M-%S");
		CString FolderPath = SystemParams->GetSystemParamData()->ImageFilePath;

		FileDirectory = FormatString("%s%s", FolderPath, csDate);

		//if(ImageGraber_Hikvision->IsCameraOpen() == false)
		//	return FALSE;

		FilePath_Org = FormatString("%s\\%s.bmp", FileDirectory, OrgLable);

		if(DiskObject.DirectoryExists(FileDirectory) == FALSE)
			DiskObject.CreateDirectoryA(FileDirectory);

		//if(ImageGraber_Hikvision->SaveOriginalImage(FilePath_Org, nThreshold, nBlur) == false)
		//	FilePath_Org = "";

	}
	catch(SYSTEM_ERROR &e)
	{
		e.SetLocation("GetCameraPicture");
		throw;

		return "";
	}

	return FilePath_Org;
}

AFX_EXT_API CString GetCameraPicture_Sticker(int nThreshold, int nBlur)
{
	CString FilePath_Org;

	try
	{
		CDiskObject DiskObject;
		CTime cur_tm = CTime::GetCurrentTime();
		CString csDate, OrgLable, FileDirectory;

		csDate = cur_tm.Format("%Y-%m-%d");
		OrgLable = cur_tm.Format("FlatEdge_ORG_%Y-%m-%d-%H-%M-%S");
		CString FolderPath = SystemParams->GetSystemParamData()->ImageFilePath_Sticker;

		FileDirectory = FormatString("%s%s", FolderPath, csDate);

		//if(ImageGraber_Hikvision_Sticker->IsCameraOpen() == false)
		//	return FALSE;

		FilePath_Org = FormatString("%s\\%s.bmp", FileDirectory, OrgLable);

		if(DiskObject.DirectoryExists(FileDirectory) == FALSE)
			DiskObject.CreateDirectoryA(FileDirectory);

		//if(ImageGraber_Hikvision_Sticker->SaveOriginalImage(FilePath_Org, nThreshold, nBlur) == false)
		//	FilePath_Org = "";

	}
	catch(SYSTEM_ERROR &e)
	{
		e.SetLocation("GetCameraPicture_Sticker");
		throw;

		return "";
	}

	return FilePath_Org;
}
AFX_EXT_API void SystemForceShutdown()
{
	//取得最高權限
	HANDLE              hToken = NULL;
	LUID                Luid = {0};
	TOKEN_PRIVILEGES    tp = {0};

	if (!OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES|TOKEN_QUERY, &hToken))
	{
		CloseHandle(hToken);
		return;
	}
	if (!LookupPrivilegeValue(NULL, SE_DEBUG_NAME, &Luid))
	{
		CloseHandle(hToken);
		return;
	}

	tp.PrivilegeCount = 1;
	tp.Privileges[0].Luid = Luid;
	tp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
	if (!AdjustTokenPrivileges(hToken, FALSE, &tp, sizeof(tp), NULL, NULL))
	{
		CloseHandle(hToken);
		return;
	}

	//關閉目前程序

	PROCESSENTRY32 Entry;
	HANDLE hSnapShot;
	BOOL ret;

	hSnapShot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if(hSnapShot==INVALID_HANDLE_VALUE)
	{
		printf("CreateToolhelp32Snapshot fail.\n");
	}

	Entry.dwSize = sizeof(PROCESSENTRY32);
	ret = Process32First(hSnapShot, &Entry);
	while(ret)
	{
		if(Entry.th32ProcessID == GetCurrentProcessId())
		{
			DWORD ExitCode;

			HANDLE hProcess = NULL;
			hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, Entry.th32ProcessID);

			BOOL FLAG = GetExitCodeProcess(hProcess, &ExitCode);
			if(FLAG)
			{
				TerminateProcess(hProcess, ExitCode);
			}
		}

		ret = Process32Next(hSnapShot, &Entry);
	}
	CloseHandle(hSnapShot);
	CloseHandle(hToken);
}

inline BOOL IsDataSectionNeeded(const WCHAR* pModuleName)
{
	if(pModuleName == 0)
	{
		return FALSE;
	}

	WCHAR szFileName[_MAX_FNAME] = L"";
	_wsplitpath(pModuleName, NULL, NULL, szFileName, NULL);
	if(wcsicmp(szFileName, L"ntdll") == 0)
		return TRUE;
	return FALSE; 
}

inline BOOL CALLBACK MiniDumpCallback(PVOID pParam, const PMINIDUMP_CALLBACK_INPUT pInput, PMINIDUMP_CALLBACK_OUTPUT pOutput)
{
	if(pInput == 0 || pOutput == 0)
		return FALSE;

	switch(pInput->CallbackType)
	{
	case ModuleCallback: 
		if(pOutput->ModuleWriteFlags & ModuleWriteDataSeg) 
			if(!IsDataSectionNeeded(pInput->Module.FullPath)) 
				pOutput->ModuleWriteFlags &= (~ModuleWriteDataSeg); 
	case IncludeModuleCallback:
	case IncludeThreadCallback:
	case ThreadCallback:
	case ThreadExCallback:
		return TRUE;
	default:;
	}
	return FALSE;
}

inline void CreateMiniDump(EXCEPTION_POINTERS* pep, LPCTSTR strFileName)
{
	HANDLE hFile = CreateFile(strFileName, GENERIC_READ | GENERIC_WRITE,
		0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	if((hFile != NULL) && (hFile != INVALID_HANDLE_VALUE))
	{
		MINIDUMP_EXCEPTION_INFORMATION mdei;
		mdei.ThreadId           = GetCurrentThreadId();
		mdei.ExceptionPointers  = pep;
		mdei.ClientPointers     = FALSE;
		MINIDUMP_CALLBACK_INFORMATION mci;
		mci.CallbackRoutine     = (MINIDUMP_CALLBACK_ROUTINE)MiniDumpCallback;
		mci.CallbackParam       = 0;
		MINIDUMP_TYPE mdt       = (MINIDUMP_TYPE)(MiniDumpWithPrivateReadWriteMemory | 
			MiniDumpWithDataSegs | 
			MiniDumpWithHandleData |
			0x00000800 /*MiniDumpWithFullMemoryInfo*/ | 
			0x00001000 /*MiniDumpWithThreadInfo*/ | 
			MiniDumpWithUnloadedModules);
		MiniDumpWriteDump(GetCurrentProcess(), GetCurrentProcessId(),
			hFile, mdt, (pep != 0) ? &mdei : 0, 0, &mci);
		CloseHandle(hFile); 
	}
}

AFX_EXT_API LONG  WINAPI GPTUnhandledExceptionFilter(PEXCEPTION_POINTERS pExceptionInfo)
{

	SYSTEMTIME st;
	::GetLocalTime(&st);
	TCHAR exeFullPath[256];
	GetModuleFileName(NULL,exeFullPath,256);
	CString strPath;
	DWORD nLoc;
	strPath.Format("%s",exeFullPath);  
	nLoc = strPath.ReverseFind('\\');
	strPath.Delete(nLoc+1,strPath.GetLength()-nLoc); 

	CString szFileName;
	szFileName.Format("%sERLOG_%04d%02d%02d%02d%02d%02d%02d%02d.dmp",strPath, st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond, st.wMilliseconds, rand()%100);
	CreateMiniDump(pExceptionInfo, szFileName);

	exit(pExceptionInfo->ExceptionRecord->ExceptionCode);
	return EXCEPTION_EXECUTE_HANDLER;
}


AFX_EXT_API CString GetLastErrorAsString()
{
	//Get the error message ID, if any.
	DWORD errorMessageID = ::GetLastError();
	if(errorMessageID == 0) {
		return ""; //No error message has been recorded
	}

	LPSTR messageBuffer = nullptr;

	//Ask Win32 to give us the string version of that message ID.
	//The parameters we pass in, tell Win32 to create the buffer that holds the message for us (because we don't yet know how long the message string will be).
	size_t size = FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL, errorMessageID, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPSTR)&messageBuffer, 0, NULL);

	//Copy the error message into a std::string.
	std::string message(messageBuffer, size);

	CString sMessage(message.c_str());

	//Free the Win32's string's buffer.
	LocalFree(messageBuffer);

	return sMessage;
}

AFX_EXT_API bool GetSwitchKey_Auto()
{
	try
	{

	}
	catch(SYSTEM_ERROR &e)
	{
		e.SetLocation("GetSwitchKey_Auto");
		LOG->Message_Error(Log_Main, e.GetErrorMessage());

		return false;
	}

	return false;
}



