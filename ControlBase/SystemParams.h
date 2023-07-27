#pragma once
#include "GlobalObject.h"

struct SYSTEM_PARAM_DATA
{
	//[SYSTEM]
	CString __m_MachineID;
	CString __m_MaintenanceEG_Name;
	CString __m_MaintenanceEG_Phone;
	CString __m_SystemPassword;

	BOOL __m_InterlockCheck;

	DWORD IdleTime;

	DWORD nAutoLogoutTime;

	CString LogSavePath;

	BOOL bDummyHardware;
	BOOL bDummyCamera;
	BOOL bAlwaysSaveImage;

	CString EpsonRC_Address;
	int EpsonRC_Port;

	int RobotSpeed_Auto;
	int RobotSpeed_Manual;

	float Robot_ForkCheck_Timeout;
	float Robot_Handshake_Timeout;

	float CCD_Calibrate_Distance;
	float CCD_Calibrate_Degree;

	float CCD_Calibrate_Sticker_Distance;
	float CCD_Calibrate_Sticker_Degree;
	
	CString ImageFilePath;
	CString ImageFilePath_Sticker;

	double OverRange_mm_X; // The offset threshold
	double OverRange_mm_Y;
	double OverRange_mm_T;

	double OverRange_Sticker_mm_X; // The offset threshold
	double OverRange_Sticker_mm_Y;
	double OverRange_Sticker_mm_T;

	BOOL bManualClickResult; // manual check 

	DWORD IN_CV_Delay;
	DWORD OUT_CV_Delay;

	DWORD IN_CV_Timeout;
	DWORD OUT_CV_Timeout;

	BOOL bPuttingMode;
	BOOL bByPassMode;
	

	
	SYSTEM_PARAM_DATA()
	{
		__m_InterlockCheck = TRUE;

		IdleTime = 0;

		nAutoLogoutTime = 180000;

		bDummyCamera = FALSE;

		EpsonRC_Address = "192.168.0.1";
		EpsonRC_Port = 5000;

		RobotSpeed_Auto = 10;
		RobotSpeed_Manual = 10;

		Robot_ForkCheck_Timeout = 10.0;
		Robot_Handshake_Timeout = 30.0;

		CCD_Calibrate_Distance = 0;
		CCD_Calibrate_Degree = 0;

		CCD_Calibrate_Sticker_Distance = 0;
		CCD_Calibrate_Sticker_Degree = 0;

		OverRange_mm_X = 0; 
		OverRange_mm_Y = 0;
		OverRange_mm_T = 0;

		OverRange_Sticker_mm_X = 0; // The offset threshold
		OverRange_Sticker_mm_Y = 0;
		OverRange_Sticker_mm_T = 0;

		IN_CV_Delay = 0;
		OUT_CV_Delay = 0;

		IN_CV_Delay = 0;
		OUT_CV_Timeout = 0;

		bPuttingMode = FALSE;
		bByPassMode = FALSE;

	}
};

class CSystemParams
{


public:
	CSystemParams(CString FileName);
	~CSystemParams(void);

	bool Load();
	bool Save();
	CString GetMachineID();
	void SetMachineID(CString csMachineID);
	CString GetMaintenanceEG_Name();
	void SetMaintenanceEG_Name(CString csMaintenanceEG_Name);
	CString GetMaintenanceEG_Phone();
	void SetMaintenanceEG_Phone(CString csMaintenanceEG_Phone);
	BOOL GetInterLockCheck();
	void SetInterLockCheck(BOOL bCheck);
	CString GetSystemPassword();

	SYSTEM_PARAM_DATA* GetSystemParamData();

	CString m_SystemFileName;
	CString m_FilePathName;


	SYSTEM_PARAM_DATA m_SystemParamData;
	
private:
};

