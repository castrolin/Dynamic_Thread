#include "StdAfx.h"
#include "systemparams.h"

CSystemParams::CSystemParams(CString FileName)
{
	m_SystemFileName = FileName;
}

CSystemParams::~CSystemParams(void)
{
}

bool CSystemParams::Load()
{
	m_FilePathName = Project_Path + "CtrlPrms\\" + m_SystemFileName;

	CString cstrPath("") , cstrDef("") ;
	char chData[MAX_PATH] = {0};
	cstrDef.Format("NODATA");
	cstrPath.Format("%s" , m_FilePathName) ;
	cstrPath.Trim();
	if (cstrPath.IsEmpty())
	{
		return (false) ;
	}
	
//[SYSTEM]
	::GetPrivateProfileString("SYSTEM" , "MachineID" , cstrDef , chData , MAX_PATH , cstrPath) ;
	if (0 == cstrDef.CollateNoCase(chData))
	{
		return (false) ;
	}
	else
	{	
		m_SystemParamData.__m_MachineID.Format("%s" , chData) ;
	}

	::GetPrivateProfileString("SYSTEM" , "EngineerName" , cstrDef , chData , MAX_PATH , cstrPath) ;
	if (0 == cstrDef.CollateNoCase(chData))
	{
		return (false) ;
	}
	else
	{	
		m_SystemParamData.__m_MaintenanceEG_Name.Format("%s" , chData) ;
	}

	::GetPrivateProfileString("SYSTEM" , "EngineerPhone" , cstrDef , chData , MAX_PATH , cstrPath) ;
	if (0 == cstrDef.CollateNoCase(chData))
	{
		return (false) ;
	}
	else
	{	
		m_SystemParamData.__m_MaintenanceEG_Phone.Format("%s" , chData) ;
	}

	::GetPrivateProfileString("SYSTEM" , "Password" , cstrDef , chData , MAX_PATH , cstrPath) ;
	if (0 == cstrDef.CollateNoCase(chData))
	{
		return (false) ;
	}
	else
	{	
		m_SystemParamData.__m_SystemPassword.Format("%s" , chData) ;
	}

	m_SystemParamData.__m_InterlockCheck = GetPrivateProfileInt("SYSTEM" , "InterLock" , 0 , cstrPath) ;

	//[EQ Machine Data]

	m_SystemParamData.IdleTime = GetPrivateProfileInt("SYSTEM", "IdleTime", 0, cstrPath);

	m_SystemParamData.bDummyHardware = GetPrivateProfileInt("SystemParam", "bDummyHardware", 0, cstrPath);

	m_SystemParamData.nAutoLogoutTime = GetPrivateProfileInt("SystemParam", "nAutoLogoutTime", 0, cstrPath);

	m_SystemParamData.LogSavePath = GetPrivateProfileString("SystemParam", "LogSavePath", "C:\\Log", cstrPath);

	m_SystemParamData.ImageFilePath = GetPrivateProfileString("SystemParam", "ImageFilePath", "C:\\Image", cstrPath);

	m_SystemParamData.ImageFilePath_Sticker = GetPrivateProfileString("SystemParam", "ImageFilePath_Sticker", "C:\\Image_Sticker", cstrPath);

	m_SystemParamData.bDummyCamera = GetPrivateProfileInt("SystemParam", "DummyCamera", 0, cstrPath);
	m_SystemParamData.bAlwaysSaveImage = GetPrivateProfileInt("SystemParam", "AlwaysSaveImage", 0, cstrPath);
	
	m_SystemParamData.EpsonRC_Address = GetPrivateProfileString("SystemParam", "EpsonRC_Address", "127.0.0.1", cstrPath);
	m_SystemParamData.EpsonRC_Port = GetPrivateProfileInt("SystemParam", "EpsonRC_Port", 20000, cstrPath);

	m_SystemParamData.RobotSpeed_Auto = GetPrivateProfileInt("SystemParam", "RobotSpeed_Auto", 10, cstrPath);
	m_SystemParamData.RobotSpeed_Manual = GetPrivateProfileInt("SystemParam", "RobotSpeed_Manual", 10, cstrPath);

	m_SystemParamData.Robot_ForkCheck_Timeout = GetPrivateProfileFloat("SystemParam", "Robot_ForkCheck_Timeout", 10.0, cstrPath);
	m_SystemParamData.Robot_Handshake_Timeout = GetPrivateProfileFloat("SystemParam", "Robot_Handshake_Timeout", 30.0, cstrPath);

	m_SystemParamData.CCD_Calibrate_Distance = GetPrivateProfileFloat("SystemParam", "CCD_Calibrate_Distance", 0, cstrPath);
	m_SystemParamData.CCD_Calibrate_Degree = GetPrivateProfileFloat("SystemParam", "CCD_Calibrate_Degree", 0, cstrPath);

	m_SystemParamData.CCD_Calibrate_Sticker_Distance = GetPrivateProfileFloat("SystemParam", "CCD_Calibrate_Sticker_Distance", 0, cstrPath);
	m_SystemParamData.CCD_Calibrate_Sticker_Degree = GetPrivateProfileFloat("SystemParam", "CCD_Calibrate_Sticker_Degree", 0, cstrPath);

	m_SystemParamData.OverRange_mm_X = GetPrivateProfileDouble("SystemParam", "OverRange_mm_X", 0, cstrPath);
	m_SystemParamData.OverRange_mm_Y = GetPrivateProfileDouble("SystemParam", "OverRange_mm_Y", 0, cstrPath);
	m_SystemParamData.OverRange_mm_T = GetPrivateProfileDouble("SystemParam", "OverRange_mm_T", 0, cstrPath);

	m_SystemParamData.OverRange_Sticker_mm_X = GetPrivateProfileDouble("SystemParam", "OverRange_Sticker_mm_X", 0, cstrPath);
	m_SystemParamData.OverRange_Sticker_mm_Y = GetPrivateProfileDouble("SystemParam", "OverRange_Sticker_mm_Y", 0, cstrPath);
	m_SystemParamData.OverRange_Sticker_mm_T = GetPrivateProfileDouble("SystemParam", "OverRange_Sticker_mm_T", 0, cstrPath);

	m_SystemParamData.bManualClickResult = GetPrivateProfileInt("SystemParam", "bManualClickResult", 0, cstrPath);

	m_SystemParamData.IN_CV_Delay = GetPrivateProfileInt("SystemParam", "IN_CV_Delay", 0, cstrPath);
	m_SystemParamData.OUT_CV_Delay = GetPrivateProfileInt("SystemParam", "OUT_CV_Delay", 0, cstrPath);

	m_SystemParamData.IN_CV_Timeout = GetPrivateProfileInt("SystemParam", "IN_CV_Timeout", 0, cstrPath);
	m_SystemParamData.OUT_CV_Timeout = GetPrivateProfileInt("SystemParam", "OUT_CV_Timeout", 0, cstrPath);

	m_SystemParamData.bPuttingMode = GetPrivateProfileInt("SystemParam", "bPuttingMode", 0, cstrPath);
	m_SystemParamData.bByPassMode = GetPrivateProfileInt("SystemParam", "bByPassMode", 0, cstrPath);

	return true;
}

bool CSystemParams::Save()
{
	CString cstrPath("") , cstrDef("") ;
	char chData[MAX_PATH] = {0};
	cstrDef.Format("NODATA");
	cstrPath.Format("%s" , m_FilePathName) ;
	cstrPath.Trim();
	if (cstrPath.IsEmpty())
	{
		return (false) ;
	}

	//[SYSTEM]
	::WritePrivateProfileString("SYSTEM" , "MachineID" , m_SystemParamData.__m_MachineID, cstrPath) ;

	::WritePrivateProfileString("SYSTEM" , "EngineerName" , m_SystemParamData.__m_MaintenanceEG_Name, cstrPath) ;

	::WritePrivateProfileString("SYSTEM" , "EngineerPhone" , m_SystemParamData.__m_MaintenanceEG_Phone, cstrPath) ;

	::WritePrivateProfileString("SYSTEM" , "Password" , m_SystemParamData.__m_SystemPassword, cstrPath) ;

	::WritePrivateProfileString("SYSTEM" , "InterLock" , FormatString("%d", m_SystemParamData.__m_InterlockCheck), cstrPath) ;

	//[EQ Machine Data]

	::WritePrivateProfileString("SYSTEM" , "IdleTime" , FormatString("%d", m_SystemParamData.IdleTime), cstrPath) ;

	::WritePrivateProfileString("SYSTEM" , "bDummyHardware" , FormatString("%d", m_SystemParamData.bDummyHardware), cstrPath) ;

	::WritePrivateProfileString("SystemParam" , "nAutoLogoutTime" , FormatString("%d", m_SystemParamData.nAutoLogoutTime), cstrPath) ;

	::WritePrivateProfileString("SystemParam" , "LogSavePath" , m_SystemParamData.LogSavePath, cstrPath) ;

	::WritePrivateProfileString("SystemParam" , "ImageFilePath" , m_SystemParamData.ImageFilePath, cstrPath) ;

	::WritePrivateProfileString("SystemParam" , "ImageFilePath_Sticker" , m_SystemParamData.ImageFilePath_Sticker, cstrPath) ;

	::WritePrivateProfileString("SystemParam" , "DummyCamera" , FormatString("%d", m_SystemParamData.bDummyCamera), cstrPath) ;
	::WritePrivateProfileString("SystemParam" , "AlwaysSaveImage" , FormatString("%d", m_SystemParamData.bAlwaysSaveImage), cstrPath) ;

	::WritePrivateProfileString("SystemParam" , "EpsonRC_Address" , m_SystemParamData.EpsonRC_Address, cstrPath) ;
	::WritePrivateProfileString("SystemParam" , "EpsonRC_Port" , FormatString("%d", m_SystemParamData.EpsonRC_Port), cstrPath) ;

	::WritePrivateProfileString("SystemParam" , "RobotSpeed_Auto" , FormatString("%d", m_SystemParamData.RobotSpeed_Auto), cstrPath) ;
	::WritePrivateProfileString("SystemParam" , "RobotSpeed_Manual" , FormatString("%d", m_SystemParamData.RobotSpeed_Manual), cstrPath) ;

	::WritePrivateProfileString("SystemParam" , "Robot_ForkCheck_Timeout" , FormatString("%.3f", m_SystemParamData.Robot_ForkCheck_Timeout), cstrPath) ;
	::WritePrivateProfileString("SystemParam" , "Robot_Handshake_Timeout" , FormatString("%.3f", m_SystemParamData.Robot_Handshake_Timeout), cstrPath) ;

	::WritePrivateProfileString("SystemParam" , "CCD_Calibrate_Distance" , FormatString("%.3f", m_SystemParamData.CCD_Calibrate_Distance), cstrPath) ;
	::WritePrivateProfileString("SystemParam" , "CCD_Calibrate_Degree" , FormatString("%.3f", m_SystemParamData.CCD_Calibrate_Degree), cstrPath) ;

	::WritePrivateProfileString("SystemParam" , "CCD_Calibrate_Sticker_Distance" , FormatString("%.3f", m_SystemParamData.CCD_Calibrate_Sticker_Distance), cstrPath) ;
	::WritePrivateProfileString("SystemParam" , "CCD_Calibrate_Sticker_Degree" , FormatString("%.3f", m_SystemParamData.CCD_Calibrate_Sticker_Degree), cstrPath) ;

	::WritePrivateProfileString("SystemParam", "OverRange_mm_X", FormatString("%.31f" , m_SystemParamData.OverRange_mm_X), cstrPath);
	::WritePrivateProfileString("SystemParam", "OverRange_mm_Y", FormatString("%.31f" , m_SystemParamData.OverRange_mm_Y), cstrPath);
	::WritePrivateProfileString("SystemParam", "OverRange_mm_T", FormatString("%.31f" , m_SystemParamData.OverRange_mm_T), cstrPath);

	::WritePrivateProfileString("SystemParam", "OverRange_Sticker_mm_X", FormatString("%.31f" , m_SystemParamData.OverRange_Sticker_mm_X), cstrPath);
	::WritePrivateProfileString("SystemParam", "OverRange_Sticker_mm_Y", FormatString("%.31f" , m_SystemParamData.OverRange_Sticker_mm_Y), cstrPath);
	::WritePrivateProfileString("SystemParam", "OverRange_Sticker_mm_T", FormatString("%.31f" , m_SystemParamData.OverRange_Sticker_mm_T), cstrPath);

	::WritePrivateProfileString("SystemParam", "bManualClickResult", FormatString("%d", m_SystemParamData.bManualClickResult), cstrPath);

	::WritePrivateProfileString("SystemParam", "IN_CV_Delay", FormatString("%d", m_SystemParamData.IN_CV_Delay), cstrPath);
	::WritePrivateProfileString("SystemParam", "OUT_CV_Delay", FormatString("%d", m_SystemParamData.OUT_CV_Delay), cstrPath);

	::WritePrivateProfileString("SystemParam", "IN_CV_Timeout", FormatString("%d", m_SystemParamData.IN_CV_Timeout), cstrPath);
	::WritePrivateProfileString("SystemParam", "OUT_CV_Timeout", FormatString("%d", m_SystemParamData.OUT_CV_Timeout), cstrPath);

	::WritePrivateProfileString("SystemParam", "bPuttingMode", FormatString("%d", m_SystemParamData.bPuttingMode), cstrPath);
	::WritePrivateProfileString("SystemParam", "bByPassMode", FormatString("%d", m_SystemParamData.bByPassMode), cstrPath);

	return true;
}

CString CSystemParams::GetMachineID()
{
	return m_SystemParamData.__m_MachineID;
}

void CSystemParams::SetMachineID( CString csMachineID )
{
	m_SystemParamData.__m_MachineID = csMachineID;
}

CString CSystemParams::GetMaintenanceEG_Name()
{
	return m_SystemParamData.__m_MaintenanceEG_Name;
}

void CSystemParams::SetMaintenanceEG_Name( CString csMaintenanceEG_Name )
{
	m_SystemParamData.__m_MaintenanceEG_Name = csMaintenanceEG_Name;
}

CString CSystemParams::GetMaintenanceEG_Phone()
{
	return m_SystemParamData.__m_MaintenanceEG_Phone;
}

void CSystemParams::SetMaintenanceEG_Phone( CString csMaintenanceEG_Phone )
{
	m_SystemParamData.__m_MaintenanceEG_Phone = csMaintenanceEG_Phone;
}

CString CSystemParams::GetSystemPassword()
{
	return m_SystemParamData.__m_SystemPassword;
}

SYSTEM_PARAM_DATA* CSystemParams::GetSystemParamData()
{
	return &m_SystemParamData;
}

BOOL CSystemParams::GetInterLockCheck()
{
	return m_SystemParamData.__m_InterlockCheck;
}

void CSystemParams::SetInterLockCheck( BOOL bCheck )
{
	m_SystemParamData.__m_InterlockCheck = bCheck;
}
