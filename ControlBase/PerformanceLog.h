#pragma once
#include <deque>
#include "CommonFunc.h"


#define TACKTIME_LOG_NUM 100
#define PERFORMANCE_LOG_NUM 30

struct STUC_TACKTIME
{
	CTime LogTime;
	DWORD TackTime;

	STUC_TACKTIME()
	{
		TackTime = 0;
	}
};

struct STUC_PERFORMANCE
{
	CTime LogTime;
	DWORD AM_Shift;
	DWORD PM_Shift;

	STUC_PERFORMANCE()
	{
		AM_Shift = 0;
		PM_Shift = 0;
	}
};

class AFX_EXT_CLASS CPerformanceLog
{
public:
	CPerformanceLog(int Shift_Hour, int Shift_Min);
	~CPerformanceLog();

private:
	Lock m_Lock; 

	int m_Shift_Hour;
	int m_Shift_Min;

	CWnd *m_CWnd_1;
	CWnd *m_CWnd_2;

	CString m_Project_Path;

	ULONGLONG m_EQ_AllProductNum;

	std::deque<STUC_TACKTIME> m_TackTimeArray;
	std::deque<STUC_PERFORMANCE> m_PerformanceArray;

	BOOL SaveTackTimeLog();
	BOOL SavePerformance();
public:

	BOOL CheckShift_AM();

	void SetMessageTarget(CWnd *DlgCWnd_1, CWnd *DlgCWnd_2);
	void SendMessageTarget();

	BOOL LoadHistory();

	BOOL SetLastTackTime(DWORD TackTime);

	BOOL SetLastPerformace(DWORD nNUM );
	BOOL AddLastPerformace(DWORD nNUM);

	BOOL GetLastTackTime(DWORD &TackTime);
	BOOL GetLastPerformace( BOOL bAM_Shift , DWORD &ProductNum);

	std::deque<STUC_TACKTIME>* GetTackTimeData();
	std::deque<STUC_PERFORMANCE>* GetPerformanceData();

	ULONGLONG GetAllProductNum();
	
};