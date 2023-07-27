
#include "stdafx.h"
#include "SystemControlBase.h"

void CDebugMonitor::OutputWinDebugString(const char *str)
{
	if(SystemTraceDlg->GetSafeHwnd() != NULL)
	{
		::SendMessage(SystemTraceDlg->GetSafeHwnd(), CWM_SYS_UPDATE_TRACE, (WPARAM) str, NULL);

		LOG->Message_Log(Log_Main + 1, str);
	}
}

UINT CControlBase::SystemDetectProc(LPVOID Info)
{
	CControlBase* this_obj = (CControlBase*) Info; 

	BOOL bLoop = TRUE ;

	while (bLoop)
	{
		try
		{
		
			if(WaitForSingleObject(g_hExit, 0) == WAIT_OBJECT_0)
			{
				bLoop = false;
				continue;
			}


			//if(EpsonRC_TCPIP_Ctrl->CheckConnection() == FALSE)
			//	this_obj->SetConnectStatus_PLC(FALSE);
			//else
			//	this_obj->SetConnectStatus_PLC(TRUE);


			CString drive_Log;
			CString drive_Tape;
			CString drive_Sticker;

			bool Req_Delete_Log = false;
			bool Req_Delete_Tape = false;
			bool Req_Delete_Sticker = false;

			ULARGE_INTEGER   bytes_available,   total_bytes,   total_free_bytes;    
			double   free_kilobytes = 0.0;
			double   free_megabytes = 0.0;
			double   free_gigabytes = 0.0;

			//Log Path
			drive_Log = SystemParams->GetSystemParamData()->LogSavePath.Mid(0, 3);

			GetDiskFreeSpaceEx(drive_Log,   &bytes_available,   &total_bytes,   &total_free_bytes);    
			free_kilobytes   =   (double)(__int64)total_free_bytes.QuadPart   /   1024.0;    
			free_megabytes   =   free_kilobytes   /   1024.0;    
			free_gigabytes   =   free_megabytes   /   1024.0;         //得到可用硬盤容量大小(G)   

			if(free_gigabytes < 10)
				Req_Delete_Log = true;

			//ImagePath
			drive_Tape = SystemParams->GetSystemParamData()->ImageFilePath.Mid(0, 3);

			GetDiskFreeSpaceEx(drive_Tape,   &bytes_available,   &total_bytes,   &total_free_bytes);    
			free_kilobytes   =   (double)(__int64)total_free_bytes.QuadPart   /   1024.0;    
			free_megabytes   =   free_kilobytes   /   1024.0;    
			free_gigabytes   =   free_megabytes   /   1024.0;         //得到可用硬盤容量大小(G)   

			if(free_gigabytes < 10)
				Req_Delete_Tape = true;

			//Sticker ImagePath
			drive_Sticker = SystemParams->GetSystemParamData()->ImageFilePath_Sticker.Mid(0, 3);

			GetDiskFreeSpaceEx(drive_Sticker,   &bytes_available,   &total_bytes,   &total_free_bytes);    
			free_kilobytes   =   (double)(__int64)total_free_bytes.QuadPart   /   1024.0;    
			free_megabytes   =   free_kilobytes   /   1024.0;    
			free_gigabytes   =   free_megabytes   /   1024.0;         //得到可用硬盤容量大小(G)   

			if(free_gigabytes < 10)
				Req_Delete_Sticker = true;


			if(Req_Delete_Log == true)
				this_obj->FindDirectoryAndDelete(SystemParams->GetSystemParamData()->LogSavePath);

			if(Req_Delete_Tape == true)
				this_obj->FindDirectoryAndDelete(SystemParams->GetSystemParamData()->ImageFilePath);

			if(Req_Delete_Sticker == true)
				this_obj->FindDirectoryAndDelete(SystemParams->GetSystemParamData()->ImageFilePath_Sticker);
		

			Sleep(60 * 60 * 1000);

		}
		catch(SYSTEM_ERROR &e)
		{
			e.SetLocation("SystemDetectProc");
			LOG->Message_Error(Log_Main, e.GetErrorMessage());
		}
	}

	return 0;
}

UINT CControlBase::SystemInitialProc(LPVOID Info)
{
	CControlBase* this_obj = (CControlBase*) Info; 


	BOOL bLoop = TRUE ;
	try
	{
		while (bLoop)
		{
			if(WaitForSingleObject(g_hExit, 0) == WAIT_OBJECT_0)
			{
				bLoop = false;
				continue;
			}

			if(WaitForSingleObject(g_hInitial, 0) == WAIT_OBJECT_0)	
			{
				//StepProcess->Proc_Robot_Initial(TRUE);

				if(this_obj->InitialSystem() != true)
				{
					SetSystemAlarm();
				}
				ResetEvent(g_hInitial);
			}

			Sleep(500);
		}
		return 0;

	}
	catch(SYSTEM_ERROR &e)
	{
		e.SetLocation("SystemInitialProc");
		LOG->Message_Error(Log_Main, e.GetErrorMessage());
	}

	

	return 0;
}

CControlBase::CControlBase(CWnd* pParent, CWnd* pLogParent, CRect FunctionDlg, CRect LogArea)
{
	//m_DebugMonitor = new CDebugMonitor();

	CWnd_Interface = pParent;

	CWnd_Interface_Log = pLogParent;

	m_FunctionArea = FunctionDlg;

	m_LogArea = LogArea;

	m_nAccessClass = 0;

	bAlarmProcessed = false;

	iEQState = STATUS_DOWN;
	iEQMode = MODE_MANUAL;
	iEQLED = RED_FLASH;
	bCIM_EQ_Remote = false;
	bCIM_BC_Online = false;
	bCIM_EQ_Online = false;

	bConnectPLC = false;
}

CControlBase::~CControlBase()
{
	CloseHandle(g_hExit);
	CloseHandle(g_hBreak);
	CloseHandle(g_hAutoRun);
	CloseHandle(g_hPause);
	CloseHandle(g_hInitial);
}

bool CControlBase::EnableSystem()
{
	try
	{


		SetSystemWarning(_WARNING_SYSTEM_ENABLE);
		
		//參數讀取
		SystemParams->Load();

		PerformanceLog->LoadHistory();

		PerformanceLog->SetMessageTarget(SystemStatusDlg, PerformanceDlg);

		PerformanceLog->SendMessageTarget();

		PostMessage(CWnd_Interface->GetSafeHwnd(), CWM_SYS_UPDATE_SYSTEMID, NULL, NULL);

		//機台帳料, 於Auto時需再次確認帳料是否符合
		Product_Data->DataRestore();

		//參數讀取
		CString LastRecipeName;
		GetPrivateProfileString("LastRecipeName","RecipeName", "", LastRecipeName.GetBuffer(128), 128, Project_Path + "\\CtrlPrms\\MachineSetting.ini");
		if(LastRecipeName != "")
		{
			if(SetSystemRecipe(LastRecipeName))
			{
				PostMessage(CWnd_Interface->GetSafeHwnd(), CWM_SYS_UPDATE_RECIPEID, NULL, NULL);
			}
			else
			{
				ShowSystemQestionBox("系統", "開啟上次參數失敗，請確認參數檔案是否存在");
			}
		}


		Delay(1000);

		CameraLink_Basler_Initial();

		CommunicationLink_RS232();

		CommunicationLink_TCPIP_Client();

		CommunicationLink_TCPIP_Server();

		SetSystemStop(false);

		SetEQState(STATUS_EQ_STOP);

		SetEQLED(RED);

		SetEQMode(MODE_MANUAL);
		
		m_SysDetectThd = AfxBeginThread(SystemDetectProc, (LPVOID)this, THREAD_PRIORITY_NORMAL, 0, CREATE_SUSPENDED);
		m_SysDetectThd->m_bAutoDelete = FALSE;
		m_SysDetectThd->ResumeThread();

		m_SysInitialThd = AfxBeginThread(SystemInitialProc, (LPVOID)this, THREAD_PRIORITY_NORMAL, 0, CREATE_SUSPENDED);
		m_SysInitialThd->m_bAutoDelete = FALSE;
		m_SysInitialThd->ResumeThread();

		AutoTread->ThreadInitial();

		StepProcess->SetProcessStepUpdate_Robot(100);

		StepProcess->SetProcessStepUpdate_CV(200);

		StepProcess->SetProcessStepUpdate_PCB_Press(300);

		LOG->Message_Log( 0 , "ContorlBase : 系統開啟完成 Enable System is Done!!") ;
	}
	catch(SYSTEM_ERROR &e)
	{
		e.SetLocation("EnableSystem");
		LOG->Message_Error(Log_Main, e.GetErrorMessage());
		ShowSystemQestionBox("系統", "系統開啟異常!");
		ShowSystemQestionBox("系統", e.GetErrorMessage());
		SystemForceShutdown();
		return false;
	}

	return true;
}

void CControlBase::SetEQState(EQUIPMENTSTATUS EqStatus)
{
	
	iEQState = EqStatus;

	Sleep(50);

	SendMessage(CWnd_Interface->GetSafeHwnd(), CWM_SYS_CHANGE_STATUS, (WPARAM)EqStatus, NULL);
}

void CControlBase::SetEQMode( EQUIPMENTMODESTATUS EqModeStatus)
{
	
	iEQMode = EqModeStatus;

	Sleep(50);

	SendMessage(CWnd_Interface->GetSafeHwnd(), CWM_SYS_CHANGE_MODE, (WPARAM)EqModeStatus, NULL);

}

void CControlBase::SetEQLED( int EqLEDStatus)
{
	
	try
	{

		iEQLED = EqLEDStatus;

		StepProcess->TurnOffAllLedAndBuzzer();

	
		//if((EqLEDStatus & BUZZER_1) > 0)
		//{
		//	OutputControl->SetLoop(Y003_LED_BUZZER);
		//}

		//if((EqLEDStatus & BUZZER_2) > 0)
		//{
		//	OutputControl->SetLoop(Y003_LED_BUZZER);
		//}

		//if((EqLEDStatus & BUZZER_3) > 0)
		//{
		//	OutputControl->SetLoop(Y003_LED_BUZZER);
		//}

		//if((EqLEDStatus & BUZZER_4) > 0)
		//{
		//	OutputControl->SetLoop(Y003_LED_BUZZER);
		//}

		//if((EqLEDStatus & RED) > 0)
		//{
		//	OutputControl->SetOutput(Y000_LED_RED, true);
		//}

		//if((EqLEDStatus & RED_FLASH) > 0)
		//{
		//	OutputControl->SetLoop(Y000_LED_RED);
		//}

		//if((EqLEDStatus & YELLOW) > 0)
		//{
		//	OutputControl->SetOutput(Y001_LED_YELLOW, true);
		//}

		//if((EqLEDStatus & YELLOW_FLASH) > 0)
		//{
		//	OutputControl->SetLoop(Y001_LED_YELLOW);
		//}

		//if((EqLEDStatus & GREEN) > 0)
		//{
		//	OutputControl->SetOutput(Y002_LED_GREEN, true);
		//}

		//if((EqLEDStatus & GREEN_FLASH) > 0)
		//{
		//	OutputControl->SetLoop(Y002_LED_GREEN);
		//}

		if((EqLEDStatus & BLUE) > 0)
		{

		}

		if((EqLEDStatus & BLUE_FLASH) > 0)
		{

		}
	
		Sleep(10);
	
		SendMessage(CWnd_Interface->GetSafeHwnd(), CWM_SYS_CHANGE_LED, EqLEDStatus, NULL);

		
	}
	catch(SYSTEM_ERROR &e)
	{
		e.SetLocation("SetEQLED");
		LOG->Message_Error(Log_Main, e.GetErrorMessage());
		SetSystemAlarm();
		return ;
	}

}

void CControlBase::SetCIM_EQ_Mode( bool bRemote, bool bCheck)
{
	if(bCheck)
	{
		if(bRemote == bCIM_EQ_Remote)
			return;
	}

	if(bRemote)
	{
		
	}
	else
	{
		
	}

	Sleep(10);

	bCIM_EQ_Remote = bRemote;
}

void CControlBase::SetCIM_BC_Mode( bool bOnLine, bool bCheck)
{
	if(bCheck)
	{
		if(bOnLine == bCIM_BC_Online)
			return;
	}

	if(bOnLine)
	{
		
	}
	else
	{
		
	}

	Sleep(10);

	bCIM_BC_Online = bOnLine;
}

void CControlBase::SetCIM_EQ_Status( bool bOnLine, bool bCheck)
{

	if(bCheck)
	{
		if(bOnLine == bCIM_EQ_Online)
			return;
	}

	if(bOnLine)
	{

	}
	else
	{

	}

	Sleep(10);

	bCIM_EQ_Online = bOnLine;
}

int CControlBase::GetEQState()
{
	return iEQState;
}

BOOL CControlBase::GetConnectStatus_PLC()
{
	return bConnectPLC;
}

int CControlBase::GetEQMode()
{
	return iEQMode;
}

int CControlBase::GetEQLED()
{
	return iEQLED;
}

bool CControlBase::GetCIM_EQ_Mode()
{
	return bCIM_EQ_Remote;
}

bool CControlBase::GetCIM_BC_Mode()
{
	return bCIM_BC_Online;
}

bool CControlBase::GetCIM_EQ_Status()
{
	return bCIM_EQ_Online;
}

void CControlBase::StartInitialSystem()
{
	SetEvent(g_hInitial);
}

bool CControlBase::InitialSystem(long TimeOut)
{

	try
	{
		UINT nType = GetLastLang();

		if (IDYES == ShowSystemQestionBox("系統", "機台即將進行初始化流程，請確認機台內是否無任何異常"))
		{
			bool bRet = true;
			DWORD EndTick = GetTickCount() + TimeOut;
			ControlBase->SetEQState(STATUS_INITIAL);
			ControlBase->SetEQLED(YELLOW_FLASH);
			ResetSystemAlarm();
			/*初始化流程*/
			
			ShowSystemMessageBox("系統", "初始化中...", false);

			StepProcess->Proc_PCB_Release(10000);

			StepProcess->Proc_Robot_Initial(TRUE);

			AutoTread->Initial();

			LOG->Message_Log(Log_Main, "機台初始化完成!!");
			
			SetEQState(STATUS_INITIAL_COMPLETE);
			ControlBase->SetEQLED(GREEN_FLASH);
			SystemMessageBox->ShowWindow(SW_HIDE);
			
		}
	}
	catch(SYSTEM_ERROR &e)
	{
		e.SetLocation("InitialSystem");
		LOG->Message_Error(Log_Main, e.GetErrorMessage());
		SystemMessageBox->ShowWindow(SW_HIDE);

		ControlBase->SetEQState(STATUS_ALARM);
		ControlBase->SetEQLED(BUZZER_2 || RED_FLASH);

		return false;
	}
	return true;
}

UINT CControlBase::EmergencyStopSystem()
{
	SetEvent(g_hBreak);

	//ControlBase->SetEQState(EQUIPMENTSTATUS::STATUS_DOWN);
	return System_NoError;
	
}

UINT CControlBase::ShutDownSystem()
{
	try
	{
		//要注意是否有Thread一直下達軸控指令
		SetSystemStop(false);
	}
	catch(SYSTEM_ERROR &e)
	{
		LOG->Message_Error(Log_Main, e.GetErrorMessage());
		return false;
	}

	return true;

}

bool CControlBase::CommunicationLink_RS232()
{
	try
	{


	}
	catch(SYSTEM_ERROR &e)
	{
		e.SetLocation("CommunicationLink_RS232");
		throw;
		return false;
	}

	return true;
}

bool CControlBase::CommunicationLink_TCPIP_Client()
{

	try
	{

	}
	catch(SYSTEM_ERROR &e)
	{
		e.SetLocation("CommunicationLink_TCPIP_Client");
		throw;
		return false;
	}

	return true;
}

bool CControlBase::CommunicationLink_TCPIP_Server()
{
	try
	{

	}
	catch(SYSTEM_ERROR &e)
	{
		e.SetLocation("CommunicationLink_TCPIP_Server");
		throw;
		return false;
	}

	return true;
}

bool CControlBase::CameraLink_Basler_Initial()
{
	try
	{
		

		//bool PingFlag = true;
		//BOOL bDummyMode = SystemParams->GetSystemParamData()->bDummyCamera;

		//DWORD TimeOut = 120000;

		//if(bDummyMode == FALSE)
		//{
		//	CameraAdaptReboot(FALSE, ImageGraber_Hikvision->GetDeviceName(), ImageGraber_Hikvision->GetDeviceIP());
		//	CameraAdaptReboot(FALSE, ImageGraber_Hikvision_Sticker->GetDeviceName(), ImageGraber_Hikvision_Sticker->GetDeviceIP());

		//	Delay(1000);

		//	CameraAdaptReboot(TRUE, ImageGraber_Hikvision->GetDeviceName(), ImageGraber_Hikvision->GetDeviceIP());
		//	CameraAdaptReboot(TRUE, ImageGraber_Hikvision_Sticker->GetDeviceName(), ImageGraber_Hikvision_Sticker->GetDeviceIP());

		//	DWORD nTickCount = ::GetTickCount();
		//	do 
		//	{
		//		PingFlag = true;

		//		Delay(100);
		//		PingFlag &= Ping("192.168.100.1");
		//		PingFlag &= Ping("192.168.101.1");
		//	} while (PingFlag == false && (::GetTickCount() - nTickCount) < TimeOut);

		//	if((::GetTickCount() - nTickCount) < TimeOut)
		//		Delay(8000);
		//}
		//
		//bool bRet = true;

		//AllUnits_HikvisionGraber.clear();

		//ImageGraber_Hikvision->CameraInitial(bDummyMode, 0, 0);

		//ImageGraber_Hikvision->LoadParameters();

		//ImageGraber_Hikvision->OpenCamera();

		//ImageGraber_Hikvision->GrabImageStart();

		//ImageGraber_Hikvision_Sticker->CameraInitial(bDummyMode, 0, 0);

		//ImageGraber_Hikvision_Sticker->LoadParameters();

		//ImageGraber_Hikvision_Sticker->OpenCamera();

		//ImageGraber_Hikvision_Sticker->GrabImageStart();

		//ImageGraber_Hikvision->SetMeansureMode(false);
		//ImageGraber_Hikvision_Sticker->SetMeansureMode(false);

		//AllUnits_HikvisionGraber.insert(AllUnits_HikvisionGraber.end(), ImageGraber_Hikvision);
		//AllUnits_HikvisionGraber.insert(AllUnits_HikvisionGraber.end(), ImageGraber_Hikvision_Sticker);


		//HikvisionGrabberDlg->CameraInfoInitial(&AllUnits_HikvisionGraber);

	}
	catch(SYSTEM_ERROR &e)
	{
		e.SetLocation("CameraLink_Basler_Initial");
		throw;
		return false;
	}

	return true;
}

bool CControlBase::CameraAdaptReboot(BOOL bEnable, CString sAdaptName, CString sIP)
{
	BOOL bDummyMode = SystemParams->GetSystemParamData()->bDummyCamera;

	if(bDummyMode == FALSE)
	{
		//Restart Camera netCard
		CString sDisableCommand = FormatString("/c netsh interface set interface \"%s\" DISABLE", sAdaptName);
		CString sEnableCommand = FormatString("/c netsh interface set interface \"%s\" ENABLE", sAdaptName);

		if(bEnable)
			ShellExecute(NULL, "open", "cmd", sEnableCommand, "", SW_SHOWMINIMIZED);
		else
			ShellExecute(NULL, "open", "cmd", sDisableCommand, "", SW_SHOWMINIMIZED);
	}

	return true;
}

void CControlBase::SetOperatorID( CString ID )
{
	m_OperatorID = ID;
}

void CControlBase::SetOperatorName( CString ID )
{
	m_OperatorName = ID;
}

void CControlBase::SetAccessClass(UINT nClass)
{
	m_nAccessClass = nClass;
}

UINT CControlBase::GetAccessClass()
{
	return m_nAccessClass;
}

CString CControlBase::GetOperatorID()
{
	return m_OperatorID;
}

CString CControlBase::GetOperatorName()
{
	return m_OperatorName;
}

bool CControlBase::GetAlarmProcessStatus()
{
	return bAlarmProcessed;
}

void CControlBase::SetAlarmProcessStatus( bool bProcessed )
{
	bAlarmProcessed = bProcessed;
}

void CControlBase::SetCurrentLang( UINT nType )
{
	CString MachineSetting_Path;

	m_nLanguage = nType;

	
	MachineSetting_Path.Format("%sCtrlPrms\\MachineSetting.ini", Project_Path);

	WritePrivateProfileString("LastLanguage", "Language", FormatString("%d", m_nLanguage), MachineSetting_Path);
	
	::SendMessage(CWnd_Interface->GetSafeHwnd(), CWM_SYS_UPDATE_LANG, (WPARAM)m_nLanguage, NULL);
	
	::SendMessage(UserAccountDlg->GetSafeHwnd(), CWM_SYS_UPDATE_LANG, (WPARAM)m_nLanguage, NULL);
	::SendMessage(OptionDlg->GetSafeHwnd(), CWM_SYS_UPDATE_LANG, (WPARAM)m_nLanguage, NULL);

	::SendMessage(OptionManualSelDlg->GetSafeHwnd(), CWM_SYS_UPDATE_LANG, (WPARAM)m_nLanguage, NULL);
	::SendMessage(SystemParamsDlg->GetSafeHwnd(), CWM_SYS_UPDATE_LANG, (WPARAM)m_nLanguage, NULL);
	::SendMessage(RecipeSettingDlg->GetSafeHwnd(), CWM_SYS_UPDATE_LANG, (WPARAM)m_nLanguage, NULL);
	::SendMessage(RecipeSettingCurrentDlg->GetSafeHwnd(), CWM_SYS_UPDATE_LANG, (WPARAM)m_nLanguage, NULL);
	::SendMessage(RecipeListDlg->GetSafeHwnd(), CWM_SYS_UPDATE_LANG, (WPARAM)m_nLanguage, NULL);
	::SendMessage(SystemStatusDlg->GetSafeHwnd(), CWM_SYS_UPDATE_LANG, (WPARAM)m_nLanguage, NULL);
	::SendMessage(StepFuncDlg->GetSafeHwnd(), CWM_SYS_UPDATE_LANG, (WPARAM)m_nLanguage, NULL);
	//::SendMessage(StepFuncDlg_Sticker->GetSafeHwnd(), CWM_SYS_UPDATE_LANG, (WPARAM)m_nLanguage, NULL);
	//::SendMessage(RobotStepFuncDlg->GetSafeHwnd(), CWM_SYS_UPDATE_LANG, (WPARAM)m_nLanguage, NULL);


	//::SendMessage(ImageProc_PatternFimd_MIL_DLG->GetSafeHwnd(), CWM_SYS_UPDATE_LANG, (WPARAM)m_nLanguage, NULL);
	//::SendMessage(ImageProc_PatternFimd_MIL_DLG_Sticker->GetSafeHwnd(), CWM_SYS_UPDATE_LANG, (WPARAM)m_nLanguage, NULL);

	//::SendMessage(ImageProc_PatternFimd_MIL_Cali_DLG->GetSafeHwnd(), CWM_SYS_UPDATE_LANG, (WPARAM)m_nLanguage, NULL);
	//::SendMessage(ImageProc_PatternFimd_MIL_DLG_Cali_Sticker->GetSafeHwnd(), CWM_SYS_UPDATE_LANG, (WPARAM)m_nLanguage, NULL);

	::SendMessage(InputTestDlg->GetSafeHwnd(), CWM_SYS_UPDATE_LANG, (WPARAM)m_nLanguage, NULL);
	::SendMessage(OutputTestDlg->GetSafeHwnd(), CWM_SYS_UPDATE_LANG, (WPARAM)m_nLanguage, NULL);


	::SendMessage(PerformanceDlg->GetSafeHwnd(), CWM_SYS_UPDATE_LANG, (WPARAM)m_nLanguage, NULL);
	//SetEQState((EQUIPMENTSTATUS)GetEQState(), false);
	//SetEQMode((EQUIPMENTMODESTATUS)GetEQMode(), false);

}

UINT CControlBase::GetLastLang()
{
	CString MachineSetting_Path;

	UINT nType;

	MachineSetting_Path = Project_Path + "CtrlPrms\\MachineSetting.ini";

	nType = GetPrivateProfileInt("LastLanguage", "Language", 0, MachineSetting_Path);

	return nType;
}

CWnd * CControlBase::GetMainDlg()
{
	return CWnd_Interface;
}

CWnd * CControlBase::GetMainLogDlg()
{
	return CWnd_Interface_Log;
}

BOOL CControlBase::SystemDoorOpenStatus()
{
	return false;
}

BOOL CControlBase::EmergencyStopStatus()
{
	return true;
}

void CControlBase::FindDirectoryAndDelete(CString csFind)
{

	CDiskObject DiskObject;

	CStringArray DirArray;
	DiskObject.EnumAllDirectories(csFind, DirArray);

	if(DirArray.GetSize() == 0)
		return;

	CTime CreateTime = DiskObject.GetDirectoryCreateTime(DirArray.GetAt(0));
	CTime NowTime = CTime::GetCurrentTime () ;
		
	DiskObject.RemoveDirectories(DirArray.GetAt(0));

	LOG->Message_Log( 0 , "Delete Directories = %s Complete", DirArray.GetAt(0)) ;
}

void CControlBase::SetConnectStatus_PLC( BOOL bConnect )
{
	if(bConnectPLC != bConnect)
	{
		bConnectPLC = bConnect;

		Sleep(50);

		SendMessage(CWnd_Interface->GetSafeHwnd(), CWM_SYS_CHANGE_PLC_STAUS, (WPARAM)bConnectPLC, NULL);

		if(bConnectPLC == FALSE)
			LOG->Message_Error(Log_Main, "Robot 已離線, 請確認控制器網路線材是否正常連接!");
	}
}

BOOL CControlBase::PatternOrgSaveCallBack(int nThreshold, int nBlur )
{


	AFX_MANAGE_STATE(AfxGetStaticModuleState( ));

	CMessageBoxYC MessageBoxYC;

	CString Message;
	Message.Format("Threshold = %d, Blur = %d", nThreshold, nBlur);

	INT_PTR nRet = MessageBoxYC.ShowMessageBox("Image Parameters", Message);

	if(nRet == IDYES)
	{
		ProcessRecipe->Recipe_Data.st_RecipeData.nThreshold = nThreshold;
		ProcessRecipe->Recipe_Data.st_RecipeData.nBlur = nBlur;

		ProcessRecipe->SaveRecipe();
		ProcessRecipe->ReloadRecipe();
	}

	return TRUE;
}


BOOL CControlBase::PatternParameterLoadCallBack( int &nThreshold, int &nBlur )
{
	
	nThreshold = ProcessRecipe->Recipe_Data.st_RecipeData.nThreshold;
	nBlur = ProcessRecipe->Recipe_Data.st_RecipeData.nBlur;

	return TRUE;
}

BOOL CControlBase::PatternOrgSaveCallBack_Sticker(int nThreshold, int nBlur )
{

	AFX_MANAGE_STATE(AfxGetStaticModuleState( ));

	CMessageBoxYC MessageBoxYC;

	CString Message;
	Message.Format("Threshold = %d, Blur = %d", nThreshold, nBlur);

	INT_PTR nRet = MessageBoxYC.ShowMessageBox("Image Parameters", Message);

	if(nRet == IDYES)
	{
		ProcessRecipe->Recipe_Data.st_RecipeData.nThreshold_Sticker = nThreshold;
		ProcessRecipe->Recipe_Data.st_RecipeData.nBlur_Sticker = nBlur;

		ProcessRecipe->SaveRecipe();
		ProcessRecipe->ReloadRecipe();
	}

	return TRUE;
}


BOOL CControlBase::PatternParameterLoadCallBack_Sticker( int &nThreshold, int &nBlur )
{
	
	nThreshold = ProcessRecipe->Recipe_Data.st_RecipeData.nThreshold_Sticker;
	nBlur = ProcessRecipe->Recipe_Data.st_RecipeData.nBlur_Sticker;

	return TRUE;
}