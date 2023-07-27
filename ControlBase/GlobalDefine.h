#pragma once

//前期Inlude項目
#include "Icmpapi.h"
#include "ProductDataDef.h"
#include <afxsock.h>		// MFC 通訊端擴充功能
#include <vector>
#include <deque>


#include <windows.h>
#include <imagehlp.h>
#include <stdlib.h>

#pragma comment(lib, "dbghelp.lib")


//Access Type
#define _OPERATOR_			0
#define _ENGINEER_			1

//PDMS_ChangingMode
#define _PDMS_CHANGE_NONE			0
#define _PDMS_CHANGE_CYCLE_DONE		1
#define _PDMS_CHANGE_IMMEDIATELY	2

enum _LAMPHOUSE_FILTER
{
	LAMP_HOUSE_FILTER_1,
	LAMP_HOUSE_FILTER_2,
	LAMP_HOUSE_FILTER_3,
	LAMP_HOUSE_FILTER_4
};

//Log Page
#define Log_Main			0
#define Log_Trace			1

//System Error Code
#define System_Max_Error_Save			500
#define System_NoError					0x0000
#define System_InitialError				0x0001
#define System_Break					0x0002
#define System_Param_Load_Err			0x0003

#define IDC_MY_LIST_EDITBOX		20001
#define IDC_MY_LIST_COMBOBOX	20002

#define _IMPRINTER_MAX_PROC	50


//EQ Buzzer Type
#define EQ_Buzzer_Non		0
#define EQ_Buzzer_Type1		1
#define EQ_Buzzer_Type2		2

#define LOG_SERVER_NAME "MainFrameLogServer"
#define DateTimerUpdate 0

enum PORT_INDEX
{
	PORT_TAPE			= 1,
	PORT_PCB_0_Deg		= 2,
	PORT_PCB_180_Deg	= 3,
	PORT_TAPE_CCD		= 4,
};

enum EQUIPMENTSTATUS
{
	STATUS_DOWN,
	STATUS_INITIAL,
	STATUS_RUN,
	STATUS_BC_STOP,
	STATUS_EQ_STOP,
	STATUS_IDLE,
	STATUS_ALARM,
	STATUS_WARNING,
	STATUS_INITIAL_COMPLETE,
	STATUS_MANUAL
};

enum PLCSTATUS
{
	PLC_STATUS_DOWN,
	PLC_STATUS_ONLINE,
	PLC_STATUS_OFFLINE
};

enum EQUIPMENTMODESTATUS
{
	MODE_OFFLINE,
	MODE_MANUAL,
	MODE_INITIAL,
	MODE_AUTO,
	MODE_PAUSE
};

enum EQUIPMENTLEDSTATUS
{
	BUZZER_1 = 0x0001 << 0,
	BUZZER_2 = 0x0001 << 1,
	BUZZER_3 = 0x0001 << 2,
	BUZZER_4 = 0x0001 << 3,
	BUZZER_5 = 0x0001 << 4,
	BUZZER_6 = 0x0001 << 5,
	BUZZER_7 = 0x0001 << 6,
	BUZZER_8 = 0x0001 << 7,

	RED				= 0x0001 << 8,
	RED_FLASH		= 0x0001 << 9,
	YELLOW			= 0x0001 << 10,
	YELLOW_FLASH	= 0x0001 << 11,
	GREEN			= 0x0001 << 12,
	GREEN_FLASH		= 0x0001 << 13,
	BLUE			= 0x0001 << 14,
	BLUE_FLASH		= 0x0001 << 15

};

AFX_EXT_API bool SetSystemInitial(CWnd* pParent, CWnd* pLogParent, CRect SubArea, CRect LogArea);
AFX_EXT_API void SetSystemMotionInitial();
AFX_EXT_API bool SetSystemEnable();
AFX_EXT_API bool SetSystemAutoRun(bool bCheck = true);
AFX_EXT_API bool SetSystemAuto(bool bCheck=true);
AFX_EXT_API bool SetSystemManual(bool bCheck=true);
AFX_EXT_API bool SetSystemStop(bool bAsk);
AFX_EXT_API bool SetSystemPause(bool bAsk);
AFX_EXT_API bool SetSystemAlarm();
AFX_EXT_API bool SetSystemWarning(UINT nWarningCode);
AFX_EXT_API bool SetSystemTerminate();
AFX_EXT_API void SetSystemLanguage(UINT nType);

AFX_EXT_API void SetSystemInterlock(BOOL bOpen);
AFX_EXT_API BOOL GetSystemInterlockOpen();
AFX_EXT_API BOOL GetSystemInterlockCommand();

AFX_EXT_API void SetLogMessage_Normal(CString Message);
AFX_EXT_API void SetLogMessage_Warning(CString Message);
AFX_EXT_API void SetLogMessage_Error(CString Message);

AFX_EXT_API bool SystemLogin(CString sID, CString sName, UINT nLevel);
AFX_EXT_API bool SystemLogout();
AFX_EXT_API bool ResetSystemBuzzer();
AFX_EXT_API bool ResetSystemAlarm();

AFX_EXT_API UINT GetSystemLanguage();
AFX_EXT_API UINT GetSystemMode();
AFX_EXT_API UINT GetSystemStatus();

AFX_EXT_API CString GetSystemID();

AFX_EXT_API DWORD GetSystemAutoLogoutTime();

AFX_EXT_API CString GetSystemLastRecipeName();

AFX_EXT_API CString GetSystemRecipeFileName();

AFX_EXT_API CString GetSystemCaliFileName();

AFX_EXT_API void GetSystemRecipeList(std::vector<CString> &RecipeList);

AFX_EXT_API bool SetSystemRecipe(CString sFileName);

AFX_EXT_API void ShowSystemMessageBox(CString CaptureText, CString Message, bool ShowButton, bool AutoClose = false, DWORD WaitTime = 5000);
AFX_EXT_API INT_PTR ShowSystemQestionBox(CString CaptureText, CString Message);
AFX_EXT_API void HideSystemMessageBox();

AFX_EXT_API void ShowOptionDlg();

AFX_EXT_API void ShowOptionManualSelDlg();

AFX_EXT_API void ShowSystemStatusDlg();

AFX_EXT_API void HideAllDlg();

AFX_EXT_API void ForceKillProgram();

AFX_EXT_API bool CheckPauseStop(void);//!<return false 表示有事件發生，流程停止,true 表示正常，流程繼續
AFX_EXT_API CString GetOperatorName();

AFX_EXT_API CString GetCameraPicture(int nThreshold, int nBlur);

AFX_EXT_API CString GetCameraPicture_Sticker(int nThreshold, int nBlur);

AFX_EXT_API void GetSystemRecipeFileList(std::vector<CString> &RecipeFileList);

AFX_EXT_API void SystemForceShutdown();

inline BOOL IsDataSectionNeeded(const WCHAR* pModuleName);

inline BOOL CALLBACK MiniDumpCallback(PVOID pParam, const PMINIDUMP_CALLBACK_INPUT pInput, PMINIDUMP_CALLBACK_OUTPUT pOutput);

inline void CreateMiniDump(EXCEPTION_POINTERS* pep, LPCTSTR strFileName);


AFX_EXT_API LONG WINAPI GPTUnhandledExceptionFilter(PEXCEPTION_POINTERS pExceptionInfo);

AFX_EXT_API CString GetLastErrorAsString();

AFX_EXT_API bool GetSwitchKey_Auto();