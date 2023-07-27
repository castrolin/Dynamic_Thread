#pragma once

#include <Gdiplus.h>
#include "DiskObject.h"


class AFX_EXT_CLASS CStepProcess
{
private:

public:
	CStepProcess();
	~CStepProcess();

private:
	

public:
	BOOL TurnOffAllLedAndBuzzer();

	BOOL CheckSystemInterlockOpen();
	BOOL CheckSystemInterlockCommand();
	BOOL LockSystemInterLock(bool bOpen);

	//Process Step Update
	void SetProcessStepUpdate_Robot(int nStep);
	void SetProcessStepUpdate_CV(int nStep);
	void SetProcessStepUpdate_PCB_Press(int nStep);


	//Robot Step Process
	BOOL Proc_Robot_Initial(bool bAuto, DWORD Timeout = 30000);
	BOOL Proc_Robot_Move_Port(PORT_INDEX nPortIndex, DWORD Timeout = 30000);

	BOOL Proc_Robot_Get_Tape(DWORD Timeout = 30000);
	BOOL Proc_Robot_Put_Tape(double dOffset_X, double dOffset_Y, double dOffset_T, DWORD Timeout = 30000);


	//PCB
	BOOL Proc_PCB_Up(DWORD Timeout);
	BOOL Proc_PCB_Down(DWORD Timeout);
	BOOL Proc_PCB_Forward(DWORD Timeout);
	BOOL Proc_PCB_Backward(DWORD Timeout);

	BOOL Proc_PCB_Clamp(DWORD Timeout);
	BOOL Proc_PCB_Release(DWORD Timeout);

	//CV
	BOOL Proc_CV_In(DWORD Timeout);
	BOOL Proc_CV_Out(DWORD Timeout);
};
