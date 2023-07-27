#include "stdafx.h"
#include "SystemCodeCtrl.h"

CSystemCodeCtrl::CSystemCodeCtrl()
{
	

	TCHAR tcPath[MAX_PATH];
	TCHAR tcDriver[MAX_PATH];
	TCHAR tcDir[MAX_PATH];

	::GetModuleFileName(AfxGetInstanceHandle(), tcPath, MAX_PATH);
	_tsplitpath(tcPath, tcDriver, tcDir, NULL, NULL);

	Project_Path.Format("%s%s", tcDriver, tcDir);

	m_nLanguageIndex = _CODE_EN_;

	m_CodeListPath_Alarm.Format("%sCtrlPrms\\SystemCode\\SystemAlarmCode_En.ini", Project_Path);
	m_CodeListPath_Warning.Format("%sCtrlPrms\\SystemCode\\SystemWarningCode_En.ini", Project_Path);
	m_CodeListPath_Normal.Format("%sCtrlPrms\\SystemCode\\SystemNomalCode_En.ini", Project_Path);
}

CSystemCodeCtrl::~CSystemCodeCtrl()
{

}

void CSystemCodeCtrl::SetCodeLanguage( UINT nLanguageIndex )
{
	switch(nLanguageIndex)
	{
	case _CODE_EN_:

		m_CodeListPath_Alarm.Format("%sCtrlPrms\\SystemCode\\SystemAlarmCode_En.ini", Project_Path);
		m_CodeListPath_Warning.Format("%sCtrlPrms\\SystemCode\\SystemWarningCode_En.ini", Project_Path);
		m_CodeListPath_Normal.Format("%sCtrlPrms\\SystemCode\\SystemNomalCode_En.ini", Project_Path);

		break;
	case _CODE_CH_:

		m_CodeListPath_Alarm.Format("%sCtrlPrms\\SystemCode\\SystemAlarmCode_Ch.ini", Project_Path);
		m_CodeListPath_Warning.Format("%sCtrlPrms\\SystemCode\\SystemWarningCode_Ch.ini", Project_Path);
		m_CodeListPath_Normal.Format("%sCtrlPrms\\SystemCode\\SystemNomalCode_Ch.ini", Project_Path);

		break;
	default:

		m_CodeListPath_Alarm.Format("%sCtrlPrms\\SystemCode\\SystemAlarmCode_En.ini", Project_Path);
		m_CodeListPath_Warning.Format("%sCtrlPrms\\SystemCode\\SystemWarningCode_En.ini", Project_Path);
		m_CodeListPath_Normal.Format("%sCtrlPrms\\SystemCode\\SystemNomalCode_En.ini", Project_Path);

		break;
	}
}

CString CSystemCodeCtrl::GetCode( UINT nCodeType, UINT nCodeIndex, ...)
{
	CString FileName;
	switch(nCodeType)
	{
	case _CODE_ALARM_:
		FileName = m_CodeListPath_Alarm;
		break;
	case _CODE_WARNING_:
		FileName = m_CodeListPath_Warning;
		break;
	case _CODE_NORMAL_:
		FileName = m_CodeListPath_Normal;
		break;
	default:
		return "";
	}

	CString sCodeInex;
	sCodeInex.Format("%04X", nCodeIndex);

	CString sSystemCode;

	GetPrivateProfileString("Code", sCodeInex, "", sSystemCode.GetBuffer(256), 256, FileName);

	va_list ap;
	char buffer[1024];

	va_start(ap, nCodeIndex);
	vsprintf_s(buffer, sizeof(buffer), sSystemCode, ap);
	va_end(ap);   

	return buffer;


}
