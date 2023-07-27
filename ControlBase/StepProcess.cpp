
#include "stdafx.h"
#include "StepProcess.h"


CStepProcess::CStepProcess()
{

}

CStepProcess::~CStepProcess()
{

}

BOOL CStepProcess::TurnOffAllLedAndBuzzer()
{
	
	try
	{

		//OutputControl->SetOutput(Y000_LED_RED, false);
		//OutputControl->SetOutput(Y001_LED_YELLOW, false);
		//OutputControl->SetOutput(Y002_LED_GREEN, false);
		//OutputControl->SetOutput(Y003_LED_BUZZER, false);

	}
	catch(SYSTEM_ERROR &e)
	{
		e.SetLocation("TurnOffAllLedAndBuzzer");
		throw;

		return FALSE;
	}

	return TRUE;
}

BOOL CStepProcess::CheckSystemInterlockOpen()
{
	
	try
	{

		//if(	
		//	InputControl->GetInput(X004_INTERLOCK_1) == FALSE ||
		//	InputControl->GetInput(X005_INTERLOCK_2) == FALSE ||
		//	InputControl->GetInput(X006_INTERLOCK_3) == FALSE ||
		//	InputControl->GetInput(X007_INTERLOCK_4) == FALSE)
		//	return TRUE;

	}
	catch(SYSTEM_ERROR &e)
	{
		e.SetLocation("CheckSystemInterlockOpen");
		throw;

		return TRUE;
	}

	return FALSE;
}

BOOL CStepProcess::CheckSystemInterlockCommand()
{
	try
	{

		//if(	
		//	OutputControl->GetOutput(Y004_INTERLOCK_1) == FALSE &&
		//	OutputControl->GetOutput(Y005_INTERLOCK_2) == FALSE &&
		//	OutputControl->GetOutput(Y006_INTERLOCK_3) == FALSE &&
		//	OutputControl->GetOutput(Y007_INTERLOCK_4) == FALSE )
		//	return TRUE;

	}
	catch(SYSTEM_ERROR &e)
	{
		e.SetLocation("CheckSystemInterlockOpen");
		throw;

		return FALSE;
	}

	return FALSE;
}

BOOL CStepProcess::LockSystemInterLock(bool bOpen)
{
	try
	{

		//OutputControl->SetOutput(Y004_INTERLOCK_1, bOpen);
		//OutputControl->SetOutput(Y005_INTERLOCK_2, bOpen);
		//OutputControl->SetOutput(Y006_INTERLOCK_3, bOpen);
		//OutputControl->SetOutput(Y007_INTERLOCK_4, bOpen);

	}
	catch(SYSTEM_ERROR &e)
	{
		e.SetLocation("LockSystemInterLock");
		throw;

		return FALSE;
	}

	return TRUE;
}

void CStepProcess::SetProcessStepUpdate_Robot( int nStep )
{
	::SendMessage(SystemStatusDlg->GetSafeHwnd(), CWM_SYS_UPDATE_PRCESS_STATUS_ROBOT, (WPARAM)nStep, NULL);
}

void CStepProcess::SetProcessStepUpdate_CV( int nStep )
{
	::SendMessage(SystemStatusDlg->GetSafeHwnd(), CWM_SYS_UPDATE_PRCESS_STATUS_CV, (WPARAM)nStep, NULL);
}

void CStepProcess::SetProcessStepUpdate_PCB_Press( int nStep )
{
	::SendMessage(SystemStatusDlg->GetSafeHwnd(), CWM_SYS_UPDATE_PRCESS_STATUS_PCB_PRESS, (WPARAM)nStep, NULL);
}

BOOL CStepProcess::Proc_Robot_Initial(bool bAuto, DWORD Timeout)
{
	try
	{
		//Set Robot Parameters 
		//EpsonRC_TCPIP_Ctrl->SetProgramValue("g_RecipeIndex", int(ProcessRecipe->Recipe_Data.st_RecipeInfo.nRcipeID));

		//if(bAuto)
		//	EpsonRC_TCPIP_Ctrl->SetProgramValue("g_RobotSpeed", SystemParams->GetSystemParamData()->RobotSpeed_Auto);
		//else
		//	EpsonRC_TCPIP_Ctrl->SetProgramValue("g_RobotSpeed", SystemParams->GetSystemParamData()->RobotSpeed_Manual);

		//EpsonRC_TCPIP_Ctrl->SetProgramValue("g_CheckTimeout_Fork", SystemParams->GetSystemParamData()->Robot_ForkCheck_Timeout);
		//EpsonRC_TCPIP_Ctrl->SetProgramValue("g_CheckTimeout_Signal", SystemParams->GetSystemParamData()->Robot_Handshake_Timeout);

		//EpsonRC_TCPIP_Ctrl->SetProgramValue("g_CalDis", SystemParams->GetSystemParamData()->CCD_Calibrate_Distance);
		//EpsonRC_TCPIP_Ctrl->SetProgramValue("g_CalAngle", SystemParams->GetSystemParamData()->CCD_Calibrate_Degree);

		//EpsonRC_TCPIP_Ctrl->ExecuteControllerFunc(10);

		//DWORD EndTime = GetTickCount() + Timeout;

		//bool bProgramError = false;
		//bool bError = false;
		//bool bReady = false;

		//do 
		//{
		//	Delay(500);
		//	bProgramError = InputControl->GetInput(X030_RB_PRG_ERR);
		//	bError = InputControl->GetInput(X027_RB_ERROR);
		//	bReady = InputControl->GetInput(X025_RB_READY);

		//} while (bProgramError == false && bError == false && bReady == false && GetTickCount() <= EndTime);

		//if(bError == true)
		//{
		//	CString StatusCode, ErrorCode;
		//	EpsonRC_TCPIP_Ctrl->GetStatus(StatusCode, ErrorCode);
		//	DWORD nErrorCode = strtol((LPCSTR)ErrorCode, NULL, 16);
		//	throw SYSTEM_ERROR("Proc_Robot_Initial", _MODULE_ERROR_EPSON_RC, &nErrorCode);
		//	return FALSE;
		//}
		//else if(bProgramError == true)
		//{
		//	int nErrorCode = 0;
		//	EpsonRC_TCPIP_Ctrl->GetProgramValue("g_ErrorCode", nErrorCode);
		//	throw SYSTEM_ERROR("Proc_Robot_Initial", _MODULE_ERROR_EPSON_RC, &nErrorCode);
		//	return FALSE;
		//}
		//else if(bReady == false)
		//{
		//	DWORD nErrorCode = _ALARM_PROC_STEPPROCESS_ROBOT_INITIAL_TIMEOUT;
		//	throw SYSTEM_ERROR("Proc_Robot_Initial", _MODULE_ERROR_PROCESS, &nErrorCode);

		//	EpsonRC_TCPIP_Ctrl->RobotStop();

		//	return FALSE;
		//}
	}
	catch(SYSTEM_ERROR &e)
	{
		e.SetLocation("Proc_RobotInitial");
		throw;

		return FALSE;
	}

	return TRUE;
}

BOOL CStepProcess::Proc_Robot_Move_Port( PORT_INDEX nPortIndex, DWORD Timeout)
{
	try
	{
		//Set Robot Parameters 

	/*	switch(nPortIndex)
		{
		case PORT_TAPE:
			EpsonRC_TCPIP_Ctrl->ExecuteControllerFunc(50);
			break;
		case PORT_PCB_0_Deg:
			EpsonRC_TCPIP_Ctrl->ExecuteControllerFunc(51);
			break;
		case PORT_PCB_180_Deg:
			EpsonRC_TCPIP_Ctrl->ExecuteControllerFunc(52);
			break;
		case PORT_TAPE_CCD:
			EpsonRC_TCPIP_Ctrl->ExecuteControllerFunc(53);
			break;
		}
		
		DWORD EndTime = GetTickCount() + Timeout;

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
			throw SYSTEM_ERROR("Proc_Robot_Move_Port", _MODULE_ERROR_EPSON_RC, &nErrorCode);
			return FALSE;
		}
		else if(bProgramError == true)
		{
			int nErrorCode = 0;
			EpsonRC_TCPIP_Ctrl->GetProgramValue("g_ErrorCode", nErrorCode);
			throw SYSTEM_ERROR("Proc_Robot_Move_Port", _MODULE_ERROR_EPSON_RC, &nErrorCode);
			return FALSE;
		}
		else if(bReady == false)
		{
			DWORD nErrorCode = _ALARM_PROC_STEPPROCESS_ROBOT_MOVE_PORT_TIMEOUT;
			throw SYSTEM_ERROR("Proc_Robot_Move_Port", _MODULE_ERROR_PROCESS, &nErrorCode);

			EpsonRC_TCPIP_Ctrl->RobotStop();

			return FALSE;
		}*/
	}
	catch(SYSTEM_ERROR &e)
	{
		e.SetLocation("Proc_Robot_Move_Port");
		throw;

		return FALSE;
	}

	return TRUE;
}

BOOL CStepProcess::Proc_Robot_Get_Tape(DWORD Timeout)
{
	try
	{
		
		//EpsonRC_TCPIP_Ctrl->ExecuteControllerFunc(30);

		//DWORD EndTime = GetTickCount() + Timeout;

		//bool bProgramError = false;
		//bool bError = false;
		//bool bReady = false;

		//do 
		//{
		//	Delay(500);
		//	bProgramError = InputControl->GetInput(X030_RB_PRG_ERR);
		//	bError = InputControl->GetInput(X027_RB_ERROR);
		//	bReady = InputControl->GetInput(X025_RB_READY);

		//} while (bProgramError == false && bError == false && bReady == false && GetTickCount() <= EndTime);

		//if(bError == true)
		//{
		//	CString StatusCode, ErrorCode;
		//	EpsonRC_TCPIP_Ctrl->GetStatus(StatusCode, ErrorCode);
		//	DWORD nErrorCode = strtol((LPCSTR)ErrorCode, NULL, 16);
		//	throw SYSTEM_ERROR("Proc_Robot_Get_Tape", _MODULE_ERROR_EPSON_RC, &nErrorCode);
		//	return FALSE;
		//}
		//else if(bProgramError == true)
		//{
		//	int nErrorCode = 0;
		//	EpsonRC_TCPIP_Ctrl->GetProgramValue("g_ErrorCode", nErrorCode);
		//	throw SYSTEM_ERROR("Proc_Robot_Get_Tape", _MODULE_ERROR_EPSON_RC, &nErrorCode);
		//	return FALSE;
		//}
		//else if(bReady == false)
		//{
		//	DWORD nErrorCode = _ALARM_PROC_STEPPROCESS_ROBOT_GET_TAPE_TIMEOUT;
		//	throw SYSTEM_ERROR("Proc_Robot_Get_Tape", _MODULE_ERROR_PROCESS, &nErrorCode);

		//	EpsonRC_TCPIP_Ctrl->RobotStop();

		//	return FALSE;
		//}
	}
	catch(SYSTEM_ERROR &e)
	{
		e.SetLocation("Proc_Robot_Get_Tape");
		throw;

		return FALSE;
	}

	return TRUE;
}

BOOL CStepProcess::Proc_Robot_Put_Tape(double dOffset_X, double dOffset_Y, double dOffset_T, DWORD Timeout)
{
	try
	{

		//Set Parameters
	/*	EpsonRC_TCPIP_Ctrl->SetProgramValue("g_OffsetX", float(dOffset_X));
		EpsonRC_TCPIP_Ctrl->SetProgramValue("g_OffsetY", float(dOffset_Y));
		EpsonRC_TCPIP_Ctrl->SetProgramValue("g_OffsetT", float(dOffset_T));

		if(SystemParams->GetSystemParamData()->bPuttingMode == 1)
			EpsonRC_TCPIP_Ctrl->ExecuteControllerFunc(41);
		else
			EpsonRC_TCPIP_Ctrl->ExecuteControllerFunc(42);

		DWORD EndTime = GetTickCount() + Timeout;

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
			throw SYSTEM_ERROR("Proc_Robot_Put_Tape", _MODULE_ERROR_EPSON_RC, &nErrorCode);
			return FALSE;
		}
		else if(bProgramError == true)
		{
			int nErrorCode = 0;
			EpsonRC_TCPIP_Ctrl->GetProgramValue("g_ErrorCode", nErrorCode);
			throw SYSTEM_ERROR("Proc_Robot_Put_Tape", _MODULE_ERROR_EPSON_RC, &nErrorCode);
			return FALSE;
		}
		else if(bReady == false)
		{
			DWORD nErrorCode = _ALARM_PROC_STEPPROCESS_ROBOT_PUT_TAPE_TIMEOUT;
			throw SYSTEM_ERROR("Proc_Robot_Put_Tape", _MODULE_ERROR_PROCESS, &nErrorCode);

			EpsonRC_TCPIP_Ctrl->RobotStop();

			return FALSE;*/
		//}
	}
	catch(SYSTEM_ERROR &e)
	{
		e.SetLocation("Proc_Robot_Put_Tape");
		throw;

		return FALSE;
	}

	Delay(500);

	return TRUE;
}

BOOL CStepProcess::Proc_PCB_Up( DWORD Timeout )
{
	try
	{
		//DWORD EndTime = GetTickCount() + Timeout;

		//OutputControl->SetOutput(Y015_PCB_UP, true);
		//OutputControl->SetOutput(Y014_PCB_DOWN, false);

		//do 
		//{
		//	Delay(100);
		//} while (InputControl->GetInput(X015_PCB_UP) == FALSE && GetTickCount() < EndTime);

		//if(GetTickCount() >= EndTime)
		//{
		//	DWORD nErrorCode = _ALARM_PROC_STEPPROCESS_PCB_UP_TIMEOUT;
		//	throw SYSTEM_ERROR("Proc_PCB_Up", _MODULE_ERROR_PROCESS, &nErrorCode);
		//	return FALSE;
		//}
	}
	catch(SYSTEM_ERROR &e)
	{
		e.SetLocation("Proc_PCB_Up");
		throw;

		return FALSE;
	}

	return TRUE;
}

BOOL CStepProcess::Proc_PCB_Down( DWORD Timeout )
{
	try
	{
		//DWORD EndTime = GetTickCount() + Timeout;

		//OutputControl->SetOutput(Y015_PCB_UP, false);
		//OutputControl->SetOutput(Y014_PCB_DOWN, true);

		//do 
		//{
		//	Delay(100);
		//} while (InputControl->GetInput(X014_PCB_DOWN) == FALSE && GetTickCount() < EndTime);

		//if(GetTickCount() >= EndTime)
		//{
		//	DWORD nErrorCode = _ALARM_PROC_STEPPROCESS_PCB_DOWN_TIMEOUT;
		//	throw SYSTEM_ERROR("Proc_PCB_Down", _MODULE_ERROR_PROCESS, &nErrorCode);
		//	return FALSE;
		//}
	}
	catch(SYSTEM_ERROR &e)
	{
		e.SetLocation("Proc_PCB_Down");
		throw;

		return FALSE;
	}

	return TRUE;
}

BOOL CStepProcess::Proc_PCB_Forward( DWORD Timeout )
{
	try
	{
		//DWORD EndTime = GetTickCount() + Timeout;

		//OutputControl->SetOutput(Y012_PCB_FORWAARD, true);
		//OutputControl->SetOutput(Y013_PCB_BACKWARD, false);

		//do 
		//{
		//	Delay(100);
		//} while (InputControl->GetInput(X012_PCB_FORWAARD) == FALSE && GetTickCount() < EndTime);

		//if(GetTickCount() >= EndTime)
		//{
		//	DWORD nErrorCode = _ALARM_PROC_STEPPROCESS_PCB_FORWARD_TIMEOUT;
		//	throw SYSTEM_ERROR("Proc_PCB_Forward", _MODULE_ERROR_PROCESS, &nErrorCode);
		//	return FALSE;
		//}
	}
	catch(SYSTEM_ERROR &e)
	{
		e.SetLocation("Proc_PCB_Forward");
		throw;

		return FALSE;
	}

	return TRUE;
}

BOOL CStepProcess::Proc_PCB_Backward( DWORD Timeout )
{
	try
	{
		//DWORD EndTime = GetTickCount() + Timeout;

		//OutputControl->SetOutput(Y012_PCB_FORWAARD, false);
		//OutputControl->SetOutput(Y013_PCB_BACKWARD, true);

		//do 
		//{
		//	Delay(100);
		//} while (InputControl->GetInput(X013_PCB_BACKWARD) == FALSE && GetTickCount() < EndTime);

		//if(GetTickCount() >= EndTime)
		//{
		//	DWORD nErrorCode = _ALARM_PROC_STEPPROCESS_PCB_BACKWARD_TIMEOUT;
		//	throw SYSTEM_ERROR("Proc_PCB_Backward", _MODULE_ERROR_PROCESS, &nErrorCode);
		//	return FALSE;
		//}
	}
	catch(SYSTEM_ERROR &e)
	{
		e.SetLocation("Proc_PCB_Backward");
		throw;

		return FALSE;
	}

	return TRUE;
}

BOOL CStepProcess::Proc_PCB_Clamp( DWORD Timeout )
{
	try
	{
		//if(InputControl->GetInput(X014_PCB_DOWN) == true)
		//	return TRUE;

		//Proc_PCB_Down(Timeout);

	}
	catch(SYSTEM_ERROR &e)
	{
		e.SetLocation("Proc_PCB_Clamp");
		throw;

		return FALSE;
	}

	return TRUE;
}

BOOL CStepProcess::Proc_PCB_Release( DWORD Timeout )
{
	try
	{
		//if(InputControl->GetInput(X015_PCB_UP) == true)
		//	return TRUE;

		//Proc_PCB_Up(Timeout);
	}
	catch(SYSTEM_ERROR &e)
	{
		e.SetLocation("Proc_PCB_Release");
		throw;

		return FALSE;
	}

	return TRUE;
}

BOOL CStepProcess::Proc_CV_In( DWORD Timeout )
{
	DWORD EndTime = GetTickCount() + Timeout;
	try
	{
	/*	if(InputControl->GetInput(X021_CV_EMPTY) == false)
			return TRUE;

		OutputControl->SetOutput(Y021_REQ_CV_STOP, true);

		bool bPanelExist = false;
		do
		{
			Delay(1);
			bPanelExist = InputControl->GetInput(X021_CV_EMPTY);

		}while(bPanelExist == true && GetTickCount() < EndTime);

		if(GetTickCount() >= EndTime)
		{
			DWORD nErrorCode = _ALARM_PROC_STEPPROCESS_CV_IN_TIMEOUT;
			throw SYSTEM_ERROR("Proc_PCB_Backward", _MODULE_ERROR_PROCESS, &nErrorCode);
			return FALSE;
		}
		else
		{
			Delay(SystemParams->GetSystemParamData()->IN_CV_Delay);
		}*/
	}
	catch(SYSTEM_ERROR &e)
	{
		e.SetLocation("Proc_CV_In");
		throw;

		return FALSE;
	}

	return TRUE;
}

BOOL CStepProcess::Proc_CV_Out( DWORD Timeout )
{
	DWORD EndTime = GetTickCount() + Timeout;
	try
	{
		//if(InputControl->GetInput(X021_CV_EMPTY) == true)
		//	return TRUE;

		//OutputControl->SetOutput(Y021_REQ_CV_STOP, false);

		//bool bPanelExist = false;
		//do
		//{
		//	Delay(1);
		//	bPanelExist = InputControl->GetInput(X021_CV_EMPTY);

		//}while(bPanelExist == false && GetTickCount() < EndTime);

		//if(GetTickCount() >= EndTime)
		//{
		//	OutputControl->SetOutput(Y021_REQ_CV_STOP, false);
		//	DWORD nErrorCode = _ALARM_PROC_STEPPROCESS_CV_OUT_TIMEOUT;
		//	throw SYSTEM_ERROR("Proc_PCB_Backward", _MODULE_ERROR_PROCESS, &nErrorCode);
		//	return FALSE;
		//}
		//else
		//{
		//	Delay(SystemParams->GetSystemParamData()->OUT_CV_Delay);
		//	OutputControl->SetOutput(Y021_REQ_CV_STOP, true);
		//}
	}
	catch(SYSTEM_ERROR &e)
	{
		e.SetLocation("Proc_CV_In");
		throw;

		return FALSE;
	}

//	OutputControl->SetOutput(Y021_REQ_CV_STOP, true);

	return TRUE;
}
