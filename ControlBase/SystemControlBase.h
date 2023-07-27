#pragma once
#include "Resource.h"

#include "DiskObject.h"
#include "ShadeButtonST.h"
#include "AnimateIcon.h"
#include "PatternOrgSaveDlg.h"
#include "Component/WinDebugMonitor/WinDebugMonitor.h"

class CDebugMonitor : public CWinDebugMonitor
{
public:

	void OutputWinDebugString(const char *str);

};

class AFX_EXT_CLASS CControlBase 
{

public:
	CDebugMonitor *m_DebugMonitor;

	CWnd *CWnd_Interface;
	CWnd *CWnd_Interface_Log;
	CRect m_FunctionArea;
	CRect m_LogArea;
	CControlBase(CWnd* pParent, CWnd* pLogParent, CRect FunctionDlg, CRect LogArea);
	~CControlBase();

	UINT m_nLanguage;

	bool EnableSystem();
	void StartInitialSystem();
	void CalibratePosition();
	bool InitialSystem(long TimeOut = 60000);

	UINT EmergencyStopSystem();
	UINT ShutDownSystem();

	//RS232 �q�T��l��
	bool CommunicationLink_RS232();

	//TCPIP �q�T��l��
	bool CommunicationLink_TCPIP_Client();
	bool CommunicationLink_TCPIP_Server();

	//CCD ��l��
	bool CameraLink_Basler_Initial();
	bool CameraAdaptReboot(BOOL bEnable, CString sAdaptName, CString sIP);

	//���x���p
	void SetEQState(EQUIPMENTSTATUS EqStatus);
	void SetConnectStatus_PLC( BOOL bConnect );
	void SetEQMode(EQUIPMENTMODESTATUS EqModeStatus);
	void SetEQLED( int EqLEDStatus);

	void SetCIM_EQ_Mode( bool bRemote, bool bCheck = TRUE);
	void SetCIM_BC_Mode( bool bOnLine, bool bCheck = TRUE);
	void SetCIM_EQ_Status( bool bOnLine, bool bCheck = TRUE);

	int GetEQState();
	BOOL GetConnectStatus_PLC();
	int GetEQMode();
	int GetEQLED();

	bool GetCIM_EQ_Mode();
	bool GetCIM_BC_Mode();
	bool GetCIM_EQ_Status();

	int iEQState;
	BOOL bConnectPLC;
	int iEQMode;
	int iEQLED;
	
	bool bCIM_EQ_Remote;
	bool bCIM_BC_Online;
	bool bCIM_EQ_Online;

	//���q��s


	void SetOperatorID(CString ID);
	void SetOperatorName(CString Name);
	void SetAccessClass(UINT nClass);
	
	CString GetOperatorID();
	CString GetOperatorName();
	UINT GetAccessClass();

	bool GetAlarmProcessStatus();
	void SetAlarmProcessStatus(bool bProcessed);

	void SetCurrentLang(UINT nType);
	UINT GetLastLang();

	CWnd *GetMainDlg();

	CWnd *GetMainLogDlg();

	void FindDirectoryAndDelete(CString csFind);

	static BOOL PatternOrgSaveCallBack(int nThreshold, int nBlur );

	static BOOL PatternParameterLoadCallBack(int &nThreshold, int &nBlur );


	static BOOL PatternOrgSaveCallBack_Sticker(int nThreshold, int nBlur );

	static BOOL PatternParameterLoadCallBack_Sticker(int &nThreshold, int &nBlur );
private:

	CWinThread *m_SysDetectThd;
	static UINT SystemDetectProc(LPVOID Info);		// RealTime ����

	CWinThread *m_SysInitialThd;
	static UINT SystemInitialProc(LPVOID Info);		// RealTime ����

	CString m_OperatorID;
	CString m_OperatorName;
	UINT m_nAccessClass;

	bool bAlarmProcessed;

	static BOOL SystemDoorOpenStatus();

	static BOOL EmergencyStopStatus();

	


};