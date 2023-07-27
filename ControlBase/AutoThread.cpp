#include "stdafx.h"
#include "AutoThread.h"
#include "Scenario.h"

#define _DEBUGSIMTIME	50

#define _CV  100
#define _RB	 200
#define _PCB 300


#define	PRO_STEP_1   10	// CV In
#define	PRO_STEP_2   11	// Take sticker and PCB Clamp
#define	PRO_STEP_3   12	// PCB Clamp waiting func
#define	PRO_STEP_4   13	// CCD Align
#define	PRO_STEP_5   14	// PCB Align
#define	PRO_STEP_6   15	// Stick Label
#define	PRO_STEP_7   17	// CV Out and PCB Release
#define	PRO_STEP_999   999	// End

CAutoThread::CAutoThread()
{
	
	
	m_Exist_CV = FALSE;
	m_Exist_RB = FALSE;
	m_Exist_Sticker = FALSE;
	m_REQ_CV_STOP = FALSE; 

	m_ProductStatus_CV = EXP_PRODUCT_STATUS_UNKNOWN;

	bReAuto	 = FALSE;

}

CAutoThread::~CAutoThread()
{
	
}
BOOL CAutoThread::Initial()
{

	try
	{

	}
	catch(SYSTEM_ERROR &e)
	{
		e.SetLocation("CAutoThread::Initial()");
		throw;

		return FALSE;
	}
	

	return TRUE;
}

void CAutoThread::ThreadInitial()
{
	m_ProcessThread = AfxBeginThread(MainProc, (LPVOID)this, THREAD_PRIORITY_NORMAL, 0, CREATE_SUSPENDED);
	m_ProcessThread->m_bAutoDelete = FALSE;
	m_ProcessThread->ResumeThread();

	m_DetectThread = AfxBeginThread(DetectProc, (LPVOID)this, THREAD_PRIORITY_NORMAL, 0, CREATE_SUSPENDED);
	m_DetectThread->m_bAutoDelete = FALSE;
	m_DetectThread->ResumeThread();
}

UINT CAutoThread::DetectProc( LPVOID Info )
{
	CAutoThread* this_obj = (CAutoThread*) Info;

	BOOL bExist_RB = FALSE;
	BOOL bExist_CV = FALSE;
	BOOL bExist_Sticker = FALSE;
	BOOL bREQ_CV_STOP = FALSE; //**For self-start**
	
	PRODUCT_PRODUCT_STATUS eProductStatuus_CV = EXP_PRODUCT_STATUS_UNKNOWN;

	while(WaitForSingleObject(g_hExit, 0) != WAIT_OBJECT_0)
	{
		
		try
		{
		/*
			if(InputControl->GetInput(X026_RB_VAC) == true)
				bExist_RB = TRUE;
			else
				bExist_RB = FALSE;


			if(InputControl->GetInput(X021_CV_EMPTY) == false)
				bExist_CV = TRUE;
			else
				bExist_CV = FALSE;


			if(OutputControl->GetOutput(Y021_REQ_CV_STOP) == true )
				bREQ_CV_STOP = FALSE;
			else
				bREQ_CV_STOP = TRUE;


		   if(InputControl->GetInput(X016_TAPE_EMPTY) == false)
				bExist_Sticker = TRUE;
			else
				bExist_Sticker = FALSE;



			eProductStatuus_CV = Product_Data->GetProductProcStatus();

			if(this_obj->m_Exist_RB != bExist_RB)
			{
				::SendMessage(SystemStatusDlg->GetSafeHwnd(), CWM_SYS_UPDATE_PRCESS_STATUS_EXIST_ROBOT, (WPARAM)bExist_RB, NULL);
				this_obj->m_Exist_RB = bExist_RB;
			}

			if(this_obj->m_Exist_CV != bExist_CV || this_obj->m_ProductStatus_CV != eProductStatuus_CV)
			{
				::SendMessage(SystemStatusDlg->GetSafeHwnd(), CWM_SYS_UPDATE_PRCESS_STATUS_EXIST_CV, (WPARAM)bExist_CV, (LPARAM)eProductStatuus_CV);
				this_obj->m_Exist_CV = bExist_CV;
				this_obj->m_ProductStatus_CV = eProductStatuus_CV;
			}

			if(this_obj->m_Exist_Sticker != bExist_Sticker)
			{
				::SendMessage(SystemStatusDlg->GetSafeHwnd(), CWM_SYS_UPDATE_PRCESS_STATUS_EXIST_STICKER, (WPARAM)bExist_Sticker, NULL);
				this_obj->m_Exist_Sticker = bExist_Sticker;
			}

			if(this_obj->m_REQ_CV_STOP != bREQ_CV_STOP )
			{
				::SendMessage(SystemStatusDlg->GetSafeHwnd(), CWM_SYS_UPDATE_PRCESS_STATUS_CV_IN, (WPARAM)bREQ_CV_STOP, NULL);
				this_obj->m_REQ_CV_STOP = bREQ_CV_STOP;
			}

			Sleep(500);*/
		}
		catch(SYSTEM_ERROR &ex)
		{

			ex.SetLocation("AutoThread  DetectProc");

			LOG->Message_Error(Log_Trace, ex.GetErrorMessage());

			SetSystemAlarm();

			continue;

		}

		Sleep(1000); //g_hexit
	}
	return 0;

}

UINT CAutoThread::MainProc( LPVOID Info )
{
	CAutoThread* this_obj = (CAutoThread*) Info;
	BOOL Sticker_Signal_PAUSE = FALSE; // for sicker signal switch case loop control
	bool bRobotIO = false;
	DWORD nErrorCode = 0;
	DWORD EndTime = 0;
	this_obj->m_Step = PRO_STEP_1;

	DWORD TT_StartTime = 0;
	DWORD TT_EndTime = 0;

	while(WaitForSingleObject(g_hExit, 0) != WAIT_OBJECT_0)
	{
		while(WaitForSingleObject(g_hAutoRun, INFINITE) == WAIT_OBJECT_0)
		{

			Sleep(100); // g_hauto	
		}
		Sleep(1000); //g_hexit
	}
	return 0;

}

UINT CAutoThread::MainThread(LPVOID Info)
{
	CAutoThread* this_obj = (CAutoThread*) Info;
	while(WaitForSingleObject(g_hExit, 0) != WAIT_OBJECT_0)
	{
		while(WaitForSingleObject(g_hAutoRun, INFINITE) == WAIT_OBJECT_0)
		{
			//Start CV, Robot, PCB thread 
			try
			{
				SetEvent(Scenario-> m_CVStatus);
				SetEvent(Scenario->m_RBStatus);
				SetEvent(Scenario->m_PCBStatus);
			}
			catch(SYSTEM_ERROR& ex)
			{
				ex.SetLocation("ToolThreadExecute");
				throw;
				return FALSE;
			}

			

		}
	}
	return TRUE;
}

UINT CAutoThread::CheckProcessing()
{
	if(WaitForSingleObject(Scenario->m_RBStatus, 0) == WAIT_OBJECT_0 ||
		WaitForSingleObject(Scenario->m_CVStatus, 0) == WAIT_OBJECT_0 ||
		WaitForSingleObject(Scenario->m_PCBStatus, 0) == WAIT_OBJECT_0 )
	{
		return TRUE;
	}
	else
		return FALSE;
}

UINT CAutoThread::CheckError()
{
	
	if(Scenario->CVAbnormal == TRUE )
	{
	   m_CurrentCVStep = Scenario->CVStep;
	   return _CV;
	}
	if(Scenario->RBAbnormal == TRUE )
	{
		m_CurrentRBStep = Scenario->RBStep;
		return _RB;
	}
	if(Scenario->PCBAbnormal == TRUE )
	{
		m_CurrentPCBStep = Scenario->PCBStep;
		return _PCB;
	} 

	return FALSE;
}

BOOL CAutoThread::EndProcess()
{
	SetEvent(Scenario->m_CloseThreadEvent);
	return TRUE;
}

BOOL CAutoThread::ToolThreadExecute(UINT Step, UINT ToolName, BOOL bWait, DWORD Timeout)
{
	DWORD nErrorCode = 0;
	try
	{
		if(WaitForSingleObject(g_hPause, 0) == WAIT_OBJECT_0 ||
			WaitForSingleObject(g_hBreak, 0) == WAIT_OBJECT_0 )
		{
			ResetEvent(Scenario->m_CVStatus);
			ResetEvent(Scenario->m_RBStatus);
			ResetEvent(Scenario->m_PCBStatus);

			m_uReturnTool = ToolName;
			switch(ToolName)
			{
			case _CV:
				m_CurrentCVStep = Step;
				break;
			case _RB:
				m_CurrentRBStep = Step;
				break;
			case _PCB:
				m_CurrentPCBStep = Step;
				break;
			}

			bReAuto = TRUE;

			Sleep(1);
			return FALSE;

		}
		else
		{
			switch(ToolName)
			{
			case _RB:

				Scenario->RBStep = Step; 
				SetEvent(Scenario->m_RBStatus);


				if(bWait)
				{
					DWORD EndTime = GetTickCount() + Timeout; //ms
					do 
					{
						Sleep(100);
					} while (WaitForSingleObject(Scenario->m_RBStatus, 0) == WAIT_OBJECT_0 && GetTickCount()<EndTime );

					if(GetTickCount() >EndTime)
					{
						nErrorCode = _ALARM_THREAD_RB_TIMEOUT;
						throw SYSTEM_ERROR("Thread_RB_TimeOut", _MODULE_ERROR_PROCESS, &nErrorCode);
					}
				}

				if(Scenario->RBAbnormal == TRUE)
				{
					nErrorCode = _ALARM_THREAD_RB_TIMEOUT;
					throw SYSTEM_ERROR("Thread_Tool_RB", _MODULE_ERROR_PROCESS, &nErrorCode);
				}

				break;

			case _CV:

				Scenario->CVStep = Step;
				SetEvent(Scenario->m_CVStatus);

				if(bWait)
				{
					DWORD EndTime = GetTickCount() + Timeout; //ms
					do 
					{
						Sleep(100);
					} while (WaitForSingleObject(Scenario->m_CVStatus, 0) == WAIT_OBJECT_0 && GetTickCount()<EndTime );

					if(GetTickCount() >EndTime)
					{
						nErrorCode = _ALARM_THREAD_CV_TIMEOUT;
						throw SYSTEM_ERROR("Thread_CV_TimeOut", _MODULE_ERROR_PROCESS, &nErrorCode);
					}

				}
				if(Scenario->CVAbnormal == TRUE)
				{
					nErrorCode = _ALARM_THREAD_CV_TIMEOUT;
					throw SYSTEM_ERROR("Thread_Tool_CV", _MODULE_ERROR_PROCESS, &nErrorCode);
				}

				break;
			case _PCB:

				Scenario->PCBStep = Step;
				SetEvent(Scenario->m_PCBStatus);

				if(bWait)
				{
					DWORD EndTime = GetTickCount() + Timeout; //ms
					do 
					{
						Sleep(100);
					} while (WaitForSingleObject(Scenario->m_PCBStatus, 0) == WAIT_OBJECT_0 && GetTickCount()<EndTime );

					if(GetTickCount() >EndTime)
					{
						nErrorCode = _ALARM_THREAD_PCB_TIMEOUT;
						throw SYSTEM_ERROR("Thread_PCB_TimeOut", _MODULE_ERROR_PROCESS, &nErrorCode);
					}
				}

				if(Scenario->PCBAbnormal == TRUE)
				{
					nErrorCode = _ALARM_THREAD_PCB_TIMEOUT;
					throw SYSTEM_ERROR("Thread_Tool_PCB", _MODULE_ERROR_PROCESS, &nErrorCode);
				}

				break;

			}

		}
		

	}
	catch(SYSTEM_ERROR &e)
	{
		ResetEvent(Scenario->m_CVStatus);
		ResetEvent(Scenario->m_RBStatus);
		ResetEvent(Scenario->m_PCBStatus);

		TRACE("The abnormal event is triggered \n");
		e.SetLocation("ToolThreadExecute");
		throw;
		return FALSE;
	}
	 

	return TRUE;
}