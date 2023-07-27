
#pragma once

class CScenario
{

public:
	CScenario();
	~CScenario();

private:
	void RobotStatus();
	void CVStatus();
	void PCBStatus();

public:

	double m_dPCB_Offset_X;
	double m_dPCB_Offset_Y;
	double m_dPCB_Offset_T;

	double m_dSticker_Offset_X;
	double m_dSticker_Offset_Y;
	double m_dSticker_Offset_T;

	double m_dManual_Offset_X;
	double m_dManual_Offset_Y;
	double m_dManual_Offset_T;

	double m_dTotal_Offset_X;
	double m_dTotal_Offset_Y;
	double m_dTotal_Offset_T;
	
	HANDLE m_CloseThreadEvent;

	BOOL RBExecute;
	BOOL RBAbnormal;
	UINT RBStep;
	HANDLE m_RBStatus;
	CWinThread *m_RBThread;
	static UINT RBProc(LPVOID Info);

	BOOL CVExecute;
	BOOL CVAbnormal;
	UINT CVStep;
	HANDLE m_CVStatus;
	CWinThread *m_CVThread;
	static UINT CVProc(LPVOID Info);

	BOOL PCBExecute;
	BOOL PCBAbnormal;
	UINT PCBStep;
	HANDLE m_PCBStatus;
	CWinThread *m_PCBThread;
	static UINT PCBProc(LPVOID Info);



};