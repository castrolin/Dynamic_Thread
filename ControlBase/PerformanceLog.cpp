#include "stdafx.h"
#include "PerformanceLog.h"

CPerformanceLog::CPerformanceLog(int Shift_Hour, int Shift_Min)
{
	TCHAR tcPath[MAX_PATH];
	TCHAR tcDriver[MAX_PATH];
	TCHAR tcDir[MAX_PATH];

	::GetModuleFileName(AfxGetInstanceHandle(), tcPath, MAX_PATH);
	_tsplitpath(tcPath, tcDriver, tcDir, NULL, NULL);
	m_Project_Path.Format("%s%s", tcDriver, tcDir);

	m_Shift_Hour = Shift_Hour;
	m_Shift_Min = Shift_Min;

	m_CWnd_1 = NULL;
	m_CWnd_2 = NULL;

	m_EQ_AllProductNum = 0;
}

CPerformanceLog::~CPerformanceLog()
{

}


BOOL CPerformanceLog::SaveTackTimeLog()
{
	m_Lock.lock();

	CString MainKey;
	CString SubKey;
	CString FileName = FormatString("%s\\CtrlPrms\\PerformanceLog.ini", m_Project_Path);

	for(UINT x = 0; x < m_TackTimeArray.size(); x ++)
	{
		MainKey = FormatString("TackTime_%03d", x + 1);

		CString TimeString = m_TackTimeArray.at(x).LogTime.Format("%Y-%m-%d %H:%M:%S");

		WritePrivateProfileString(MainKey, "Time", TimeString, FileName);
		WritePrivateProfileString(MainKey, "TackTime", FormatString("%d", m_TackTimeArray.at(x).TackTime), FileName);

	}

	m_Lock.unlock();

	return TRUE;
}

BOOL CPerformanceLog::SavePerformance()
{
	m_Lock.lock();

	CString MainKey;
	CString SubKey;
	CString FileName = FormatString("%s\\CtrlPrms\\PerformanceLog.ini", m_Project_Path);

	MainKey = "Total";
	WritePrivateProfileString(MainKey, "ProductNum", FormatString("%lld", m_EQ_AllProductNum), FileName);

	for(UINT x = 0; x < m_PerformanceArray.size(); x ++)
	{
		MainKey = FormatString("Performance_%03d", x + 1);

		CString TimeString = m_PerformanceArray.at(x).LogTime.Format("%Y-%m-%d %H:%M:%S");

		WritePrivateProfileString(MainKey, "Time", TimeString, FileName);
		WritePrivateProfileString(MainKey, "AM_Shift", FormatString("%d", m_PerformanceArray.at(x).AM_Shift), FileName);
		WritePrivateProfileString(MainKey, "PM_Shift", FormatString("%d", m_PerformanceArray.at(x).PM_Shift), FileName);

	}

	m_Lock.unlock();

	return TRUE;
}

void CPerformanceLog::SetMessageTarget( CWnd *DlgCWnd_1, CWnd *DlgCWnd_2 )
{
	m_CWnd_1 = DlgCWnd_1;
	m_CWnd_2 = DlgCWnd_2;
}

void CPerformanceLog::SendMessageTarget()
{
	if(m_CWnd_1 != NULL)
		::SendMessage(m_CWnd_1->GetSafeHwnd(), CWM_SYS_UPDATE_PRODUCT_COUNT, NULL, NULL);//::PostMessageA(m_CWnd_1->GetSafeHwnd(), CWM_SYS_UPDATE_PRODUCT_COUNT, NULL, NULL);

	if(m_CWnd_2 != NULL)
		::SendMessage(m_CWnd_2->GetSafeHwnd(), CWM_SYS_UPDATE_PRODUCT_COUNT, NULL, NULL);//::PostMessageA(m_CWnd_1->GetSafeHwnd(), CWM_SYS_UPDATE_PRODUCT_COUNT, NULL, NULL);//
}

BOOL CPerformanceLog::LoadHistory()
{
	CString MainKey;
	CString SubKey;
	CString FileName = FormatString("%s\\CtrlPrms\\PerformanceLog.ini", m_Project_Path);

	//Load All Product Num
	MainKey = "Total";
	double dNum = GetPrivateProfileDouble(MainKey, "ProductNum", 0.0, FileName);
	m_EQ_AllProductNum = ULONGLONG(dNum);

	//Load Tack Time
	m_TackTimeArray.clear();

	for(int x = 0; x < TACKTIME_LOG_NUM; x ++)
	{
		MainKey = FormatString("TackTime_%03d", x + 1);

		STUC_TACKTIME Temp;
		int nYear = 0;
		int nMonth = 0;
		int nDate = 0;
		int nHour = 0;
		int nMin = 0;
		int nSec = 0;

		CString sTimeString = GetPrivateProfileString(MainKey, "Time", "1980-01-01 00:00:00", FileName);
		Temp.TackTime = GetPrivateProfileInt(MainKey, "TackTime", 0, FileName);


		sscanf_s(sTimeString,"%4d-%2d-%2d %2d:%2d:%2d",&nYear, &nMonth, &nDate, &nHour, &nMin, &nSec);

		Temp.LogTime = CTime(nYear, nMonth, nDate, nHour, nMin, nSec);

		m_TackTimeArray.push_back(Temp);
	}


	//Load Performance Log

	for(int x = 0; x < PERFORMANCE_LOG_NUM; x ++)
	{

		MainKey = FormatString("Performance_%03d", x + 1);

		STUC_PERFORMANCE Temp;
		int nYear = 0;
		int nMonth = 0;
		int nDate = 0;
		int nHour = 0;
		int nMin = 0;
		int nSec = 0;

		CString sTimeString = GetPrivateProfileString(MainKey, "Time", "1980-01-01 00:00:00", FileName);
		Temp.AM_Shift = GetPrivateProfileInt(MainKey, "AM_Shift", 0, FileName);
		Temp.PM_Shift = GetPrivateProfileInt(MainKey, "PM_Shift", 0, FileName);


		sscanf_s(sTimeString,"%4d-%2d-%2d %2d:%2d:%2d",&nYear, &nMonth, &nDate, &nHour, &nMin, &nSec);

		Temp.LogTime = CTime(nYear, nMonth, nDate, nHour, nMin, nSec);

		m_PerformanceArray.push_back(Temp);
	}

	return TRUE;
	
}

BOOL CPerformanceLog::SetLastTackTime( DWORD TackTime )
{
	m_Lock.lock();

	if(m_TackTimeArray.size() >= TACKTIME_LOG_NUM)
	{
		m_TackTimeArray.pop_back();
	}

	STUC_TACKTIME Temp;
	Temp.LogTime = CTime::GetCurrentTime();
	Temp.TackTime = TackTime;

	m_TackTimeArray.push_front(Temp);

	SaveTackTimeLog();

	m_Lock.unlock();

	SendMessageTarget();

	return TRUE;
}

BOOL CPerformanceLog::SetLastPerformace( DWORD nNUM )
{
	m_Lock.lock();

	STUC_PERFORMANCE FirstObj;

	if(m_PerformanceArray.at(0).LogTime.GetDay() != CTime::GetCurrentTime().GetDay())
	{
		if(m_PerformanceArray.size() >= PERFORMANCE_LOG_NUM)
		{
			m_PerformanceArray.pop_back();
		}

		STUC_PERFORMANCE Temp;
		Temp.LogTime = CTime::GetCurrentTime();

		if(CheckShift_AM())
			Temp.AM_Shift = nNUM;
		else
			Temp.PM_Shift = nNUM;

		m_PerformanceArray.push_front(Temp);
	}
	else
	{
		if(CheckShift_AM())
			m_PerformanceArray.at(0).AM_Shift = nNUM;
		else
			m_PerformanceArray.at(0).PM_Shift = nNUM;
	}

	m_Lock.unlock();

	SendMessageTarget();

	SavePerformance();

	

	return TRUE;
}

BOOL CPerformanceLog::AddLastPerformace(DWORD nNUM)
{
	m_Lock.lock();

	STUC_PERFORMANCE FirstObj;

	m_EQ_AllProductNum += nNUM;

	if(m_PerformanceArray.at(0).LogTime.GetDay() != CTime::GetCurrentTime().GetDay())
	{
		if(m_PerformanceArray.size() >= PERFORMANCE_LOG_NUM)
		{
			m_PerformanceArray.pop_back();
		}

		STUC_PERFORMANCE Temp;
		Temp.LogTime = CTime::GetCurrentTime();

		if(CheckShift_AM())
			Temp.AM_Shift += nNUM;
		else
			Temp.PM_Shift += nNUM;

		m_PerformanceArray.push_front(Temp);
	}
	else
	{
		if(CheckShift_AM())
			m_PerformanceArray.at(0).AM_Shift += nNUM;
		else
			m_PerformanceArray.at(0).PM_Shift += nNUM;
	}

	m_Lock.unlock();

	SendMessageTarget();

	SavePerformance();

	return TRUE;
}

BOOL CPerformanceLog::GetLastTackTime(DWORD &TackTime)
{
	m_Lock.lock();

	if(m_TackTimeArray.size() == 0)
	{
		TackTime = 0;
		m_Lock.unlock();
		return FALSE;
	}

	TackTime = m_TackTimeArray.at(0).TackTime;

	m_Lock.unlock();
	return TRUE;
}

BOOL CPerformanceLog::GetLastPerformace( BOOL bAM_Shift , DWORD &ProductNum)
{
	m_Lock.lock();

	if(m_PerformanceArray.size() == 0)
	{
		ProductNum = 0;
		m_Lock.unlock();
		return FALSE;
	}

	if(bAM_Shift)
		ProductNum = m_PerformanceArray.at(0).AM_Shift;
	else
		ProductNum = m_PerformanceArray.at(0).PM_Shift;

	m_Lock.unlock();

	return TRUE;
}

ULONGLONG CPerformanceLog::GetAllProductNum()
{
	return m_EQ_AllProductNum;
}

BOOL CPerformanceLog::CheckShift_AM()
{
	CTime CurrentTime = CTime::GetCurrentTime();

	if(CurrentTime.GetHour() < m_Shift_Hour )
	{
		return TRUE;

	}
	else if(CurrentTime.GetHour() == m_Shift_Hour && CurrentTime.GetMinute() < m_Shift_Min )
	{
		return TRUE;

	}
	else if(CurrentTime.GetHour() == m_Shift_Hour && CurrentTime.GetMinute() >= m_Shift_Min )
	{
		return FALSE;
	}
	

	return FALSE;
}

std::deque<STUC_TACKTIME>* CPerformanceLog::GetTackTimeData()
{
	return &m_TackTimeArray;
}

std::deque<STUC_PERFORMANCE>* CPerformanceLog::GetPerformanceData()
{
	return &m_PerformanceArray;
}


