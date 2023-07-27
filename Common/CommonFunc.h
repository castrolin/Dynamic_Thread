#pragma once

#include <afxsock.h>		// MFC 通訊端擴充功能
#include "Icmpapi.h"
#include "Psapi.h"
#include "TlHelp32.h"
#include <vector>
#include <deque>

#pragma comment( lib, "iphlpapi.lib")
#pragma comment( lib, "Psapi.lib")


#define PI 3.14159265359

struct Point2f
{
	float x;
	float y;
};

struct LinePara
{
	float k;
	float b;

};

struct BYTE_DATA
{
	UINT8 nBit_1 : 1;
	UINT8 nBit_2 : 1;
	UINT8 nBit_3 : 1;
	UINT8 nBit_4 : 1;
	UINT8 nBit_5 : 1;
	UINT8 nBit_6 : 1;
	UINT8 nBit_7 : 1;
	UINT8 nBit_8 : 1;

	BYTE_DATA()
	{
		memset(this, 0, sizeof(BYTE_DATA));
	}

};

struct WORD_DATA
{
	UINT8 nBit_01 : 1;
	UINT8 nBit_02 : 1;
	UINT8 nBit_03 : 1;
	UINT8 nBit_04 : 1;
	UINT8 nBit_05 : 1;
	UINT8 nBit_06 : 1;
	UINT8 nBit_07 : 1;
	UINT8 nBit_08 : 1;
	UINT8 nBit_09 : 1;
	UINT8 nBit_10 : 1;
	UINT8 nBit_11 : 1;
	UINT8 nBit_12 : 1;
	UINT8 nBit_13 : 1;
	UINT8 nBit_14 : 1;
	UINT8 nBit_15 : 1;
	UINT8 nBit_16 : 1;

	WORD_DATA()
	{
		memset(this, 0, sizeof(WORD_DATA));
	}

};

struct VECTOR_DATA_2
{
	double Vector_X;
	double Vector_Y;

	VECTOR_DATA_2()
	{
		Vector_X = 0.0;
		Vector_Y = 0.0;
	}

	VECTOR_DATA_2 operator = (VECTOR_DATA_2 &p)
	{
		Vector_X = p.Vector_X;
		Vector_Y = p.Vector_Y;
		return *this;
	}
};

struct POINT_DATA_2T
{
	INT32 Point_X;
	INT32 Point_Y;
	double Theta;

	POINT_DATA_2T()
	{
		Point_X = 0;
		Point_Y = 0;
		Theta = 0.0;
	}

	POINT_DATA_2T operator = (POINT_DATA_2T &p)
	{
		Point_X = p.Point_X;
		Point_Y = p.Point_Y;
		Theta = p.Theta;
		return *this;
	}
};

struct POINT_DATA_2T_F
{
	double Point_X;
	double Point_Y;
	double Theta;

	POINT_DATA_2T_F()
	{
		Point_X = 0.0;
		Point_Y = 0.0;
		Theta = 0.0;
	}

	POINT_DATA_2T_F operator = (POINT_DATA_2T_F &p)
	{
		Point_X = p.Point_X;
		Point_Y = p.Point_Y;
		Theta = p.Theta;
		return *this;
	}
};

struct POINT_DATA_3
{
	INT32 Point_X;
	INT32 Point_Y;
	INT32 Point_Z;

	POINT_DATA_3()
	{
		Point_X = 0;
		Point_Y = 0;
		Point_Z = 0;
	}

	POINT_DATA_3 operator=(POINT_DATA_3 Point)
	{
		Point_X=Point.Point_X;
		Point_Y=Point.Point_Y;
		Point_Z=Point.Point_Z;
		return *this;
	}

	POINT_DATA_3 operator+(POINT_DATA_3 Point)
	{
		POINT_DATA_3 Ret; 
		Ret.Point_X = Point_X + Point.Point_X;
		Ret.Point_Y = Point_Y + Point.Point_Y;
		Ret.Point_Z = Point_Z + Point.Point_Z;
		return Ret;
	}

	POINT_DATA_3 operator-(POINT_DATA_3 Point)
	{
		POINT_DATA_3 Ret; 
		Ret.Point_X = Point_X - Point.Point_X;
		Ret.Point_Y = Point_Y - Point.Point_Y;
		Ret.Point_Z = Point_Z - Point.Point_Z;
		return Ret;
	}

	POINT_DATA_3 operator+=(POINT_DATA_3 Point)
	{
		Point_X+=Point.Point_X;
		Point_Y+=Point.Point_Y;
		Point_Z+=Point.Point_Z;
		return *this;
	}

};

struct POINT_DATA_3_F
{
	double Point_X;
	double Point_Y;
	double Point_Z;

	POINT_DATA_3_F()
	{
		Point_X = 0;
		Point_Y = 0;
		Point_Z = 0;
	}

	POINT_DATA_3_F operator=(POINT_DATA_3_F Point)
	{
		Point_X=Point.Point_X;
		Point_Y=Point.Point_Y;
		Point_Z=Point.Point_Z;
		return *this;
	}

	POINT_DATA_3_F operator+(POINT_DATA_3_F Point)
	{
		POINT_DATA_3_F Ret; 
		Ret.Point_X = Point_X + Point.Point_X;
		Ret.Point_Y = Point_Y + Point.Point_Y;
		Ret.Point_Z = Point_Z + Point.Point_Z;
		return Ret;
	}

	POINT_DATA_3_F operator-(POINT_DATA_3_F Point)
	{
		POINT_DATA_3_F Ret; 
		Ret.Point_X = Point_X - Point.Point_X;
		Ret.Point_Y = Point_Y - Point.Point_Y;
		Ret.Point_Z = Point_Z - Point.Point_Z;
		return Ret;
	}

	POINT_DATA_3_F operator+=(POINT_DATA_3_F Point)
	{
		Point_X+=Point.Point_X;
		Point_Y+=Point.Point_Y;
		Point_Z+=Point.Point_Z;
		return *this;
	}

};


struct POINT_DATA_3T
{
	INT32 Point_X;
	INT32 Point_Y;
	INT32 Point_Z;
	INT32 Point_T;

	POINT_DATA_3T()
	{
		Point_X = 0;
		Point_Y = 0;
		Point_Z = 0;
		Point_T = 0;
	}

	POINT_DATA_3T operator=(POINT_DATA_3T Point)
	{
		Point_X=Point.Point_X;
		Point_Y=Point.Point_Y;
		Point_Z=Point.Point_Z;
		Point_T=Point.Point_T;
		return *this;
	}

	POINT_DATA_3T operator+(POINT_DATA_3T Point)
	{
		POINT_DATA_3T Ret; 
		Ret.Point_X = Point_X + Point.Point_X;
		Ret.Point_Y = Point_Y + Point.Point_Y;
		Ret.Point_Z = Point_Z + Point.Point_Z;
		Ret.Point_T = Point_T + Point.Point_T;
		return Ret;
	}

	POINT_DATA_3T operator-(POINT_DATA_3T Point)
	{
		POINT_DATA_3T Ret; 
		Ret.Point_X = Point_X - Point.Point_X;
		Ret.Point_Y = Point_Y - Point.Point_Y;
		Ret.Point_Z = Point_Z - Point.Point_Z;
		Ret.Point_T = Point_T - Point.Point_T;
		return Ret;
	}

	POINT_DATA_3T operator+=(POINT_DATA_3T Point)
	{
		Point_X+=Point.Point_X;
		Point_Y+=Point.Point_Y;
		Point_Z+=Point.Point_Z;
		Point_T+=Point.Point_T;
		return *this;
	}
};

struct POINT_DATA_3T_F
{
	double Point_X;
	double Point_Y;
	double Point_Z;
	double Point_T;

	POINT_DATA_3T_F()
	{
		Point_X = 0;
		Point_Y = 0;
		Point_Z = 0;
		Point_T = 0;
	}

	POINT_DATA_3T_F operator=(POINT_DATA_3T_F Point)
	{
		Point_X=Point.Point_X;
		Point_Y=Point.Point_Y;
		Point_Z=Point.Point_Z;
		Point_T=Point.Point_T;
		return *this;
	}

	POINT_DATA_3T_F operator+(POINT_DATA_3T_F Point)
	{
		POINT_DATA_3T_F Ret; 
		Ret.Point_X = Point_X + Point.Point_X;
		Ret.Point_Y = Point_Y + Point.Point_Y;
		Ret.Point_Z = Point_Z + Point.Point_Z;
		Ret.Point_T = Point_T + Point.Point_T;
		return Ret;
	}

	POINT_DATA_3T_F operator-(POINT_DATA_3T_F Point)
	{
		POINT_DATA_3T_F Ret; 
		Ret.Point_X = Point_X - Point.Point_X;
		Ret.Point_Y = Point_Y - Point.Point_Y;
		Ret.Point_Z = Point_Z - Point.Point_Z;
		Ret.Point_T = Point_T - Point.Point_T;
		return Ret;
	}

	POINT_DATA_3T_F operator+=(POINT_DATA_3T_F Point)
	{
		Point_X+=Point.Point_X;
		Point_Y+=Point.Point_Y;
		Point_Z+=Point.Point_Z;
		Point_T+=Point.Point_T;
		return *this;
	}
};

struct LAYOUT_DATA_3_F
{
	double Point_X;
	double Point_Y;
	double Point_Z;
	double Point_T;
	UINT RelIndex;

	LAYOUT_DATA_3_F()
	{
		Point_X = 0;
		Point_Y = 0;
		Point_Z = 0;
		Point_T = 0;
		RelIndex = 0;

	}

	LAYOUT_DATA_3_F operator = (LAYOUT_DATA_3_F &p)
	{
		Point_X = p.Point_X;
		Point_Y = p.Point_Y;
		Point_Z = p.Point_Z;
		Point_T = p.Point_T;
		RelIndex = p.RelIndex;
		return *this;
	}
};


struct POINT_DATA_2F
{
	double Point_X;
	double Point_Y;

	POINT_DATA_2F()
	{
		Point_X = 0;
		Point_Y = 0;
	}

	POINT_DATA_2F operator = (POINT_DATA_2F p)
	{
		Point_X = p.Point_X;
		Point_Y = p.Point_Y;
		return *this;
	}

	POINT_DATA_2F operator = (POINT_DATA_3 p)
	{
		Point_X = p.Point_X;
		Point_Y = p.Point_Y;
		return *this;
	}

	POINT_DATA_2F operator+=(POINT_DATA_3 Point)
	{
		Point_X+=Point.Point_X;
		Point_Y+=Point.Point_Y;
		return *this;
	}
};

struct POINT_DATA_2
{
	INT32 Point_X;
	INT32 Point_Y;

	POINT_DATA_2()
	{
		Point_X = 0;
		Point_Y = 0;
	}

	POINT_DATA_2 operator = (POINT_DATA_2 p)
	{
		Point_X = p.Point_X;
		Point_Y = p.Point_Y;
		return *this;
	}

	POINT_DATA_2 operator = (POINT_DATA_3 p)
	{
		Point_X = p.Point_X;
		Point_Y = p.Point_Y;
		return *this;
	}

	POINT_DATA_2 operator+=(POINT_DATA_3 Point)
	{
		Point_X+=Point.Point_X;
		Point_Y+=Point.Point_Y;
		return *this;
	}
};

struct POINT_DATA_3V
{
	INT32 Point_X;
	INT32 Point_Y;
	INT32 Point_Z;
	INT32 Valve;

	POINT_DATA_3V()
	{
		Point_X = 0;
		Point_Y = 0;
		Point_Z = 0;
		Valve = 0;
	}
};

class EventLock
{
public:
	HANDLE    _hHandle;            // used to lock/unlock object
	bool bInitialed;
	EventLock() : _hHandle(NULL)
	{ 
		bInitialed = true;
		_hHandle = ::CreateEvent(NULL, TRUE, FALSE, NULL);
		SetEvent(_hHandle);
	}

	~EventLock()
	{ 
		if(_hHandle != NULL && bInitialed == true)
		{
			::CloseHandle( _hHandle ); 
			_hHandle = NULL;
		}

	}

	void lock ()
	{
		_ASSERT_EXPR(_hHandle != NULL, L"EventLock Lock Fail! Event is NULL");

		WaitForSingleObject( _hHandle, INFINITE );
		
		ResetEvent(_hHandle);
	}

	void unlock () 
	{ 
		_ASSERT_EXPR(_hHandle != NULL, L"EventLock Unlock Fail! Event is NULL");

		SetEvent(_hHandle);
	}

};

class Lock
{
public:
	HANDLE    _hMutex;            // used to lock/unlock object
	bool bInitialed;
	Lock() : _hMutex(NULL)
	{ 
		bInitialed = true;
		_hMutex = ::CreateMutex( NULL, false, NULL) ; 
	}

	~Lock()
	{ 
		if(_hMutex != NULL && bInitialed == true)
		{
			::CloseHandle( _hMutex ); 
			_hMutex = NULL;
		}

	}

	void lock ()
	{
		_ASSERT_EXPR(_hMutex != NULL, L"LockContainer Lock Fail! Mutex is NULL");

		WaitForSingleObject( _hMutex, INFINITE );
	}

	void unlock () 
	{ 
		_ASSERT_EXPR(_hMutex != NULL, L"LockContainer Unlock Fail! Mutex is NULL");

		ReleaseMutex(_hMutex);      
	}

};

template <class Type>
class LockContainer : public std::deque<Type>, Lock
{
public:
	LockContainer () : deque<Type>(), Lock()
	{



	}

	~LockContainer ()
	{



	}

	void safe_clear ( )
	{
		lock();

		deque<Type>::clear ();

		unlock();
	}

	UINT safe_size()
	{
		lock();

		UINT nSize = deque<Type>::size();

		unlock();

		return nSize;
	}

	UINT safe_maxsize()
	{
		lock();

		UINT nMaxSize = deque<Type>::max_size();

		unlock();

		return nMaxSize;
	}

	reference safe_at ( size_type _Pos )
	{
		lock();
		if (this->_Mysize <= _Pos)
			_Xran();
		reference DATA=(*(begin() + _Pos));
		unlock();
		return  DATA;
	}

	void safe_pushback ( Type & obj )
	{
		lock();

		deque<Type>::push_back (obj);

		unlock();
	}

	void safe_popback ()
	{
		lock();

		deque<Type>::pop_back ();

		unlock();
	}

	void safe_pushfront ( Type & obj )
	{
		lock();

		deque<Type>::push_front() (obj);

		unlock();
	}

	void safe_popfront ( )
	{
		lock();

		deque<Type>::pop_front();

		unlock();
	}

	Type safe_front ( )
	{
		lock();

		Type Object = deque<Type>::front();

		unlock();

		return Object;
	}

	LockContainer& operator=(const LockContainer& other)
	{
		//_ASSERT_EXPR(NULL, L"LockContainer can't use Copy Operator!");
		return *this;
	}



};

#define _TIG_TYPE_R 0
#define _TIG_TYPE_F 1
#define _TIG_TYPE_A 2

class TriggerDetect
{
public:
	TriggerDetect(LPVOID Object, bool *bStatus);
	~TriggerDetect();

private:
	UINT m_Type;

	bool *m_Status;

	bool m_LastStatus;

	LPVOID m_Object;
	void (*pTriggered)(LPVOID pObject);

	HANDLE m_Close;
	HANDLE m_Detect;
	CWinThread *m_DetectThd;
	static UINT DetectProc(LPVOID Info);		// RealTime 偵測
public:
	void RegTriggeredProc(void (*pFunc)(LPVOID pObject));
	void SetTriggerType(UINT nType);
	void DetectStart();
	void DetectStop();
	void Reset();
};

extern void getLinePara(float x1, float y1, float x2, float y2, LinePara & LP);
extern bool getLinCross(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4,  Point2f & pt);

extern float getOverLinePoint_X(float X, POINT_DATA_2F Point_1, POINT_DATA_2F Point_2);
extern float getOverLinePoint_Y(float Y, POINT_DATA_2F Point_1, POINT_DATA_2F Point_2);

extern CString FormatString(CString Format, ...);


BOOL DoEvents();
extern void Delay(DWORD Msecs);

extern double GetDlgItem2Double(HWND hWnd, UINT nID, bool bSigned = true);
extern float GetDlgItem2Float(HWND hWnd, UINT nID, bool bSigned = true);
extern int GetDlgItem2Int(HWND hWnd, UINT nID, bool bSigned = true);
extern CString GetDlgItemString(HWND hWnd, UINT nID);

extern float GetPrivateProfileFloat( LPCTSTR lpAppName, LPCTSTR lpKeyName, float dDefaultValue, LPCTSTR lpFileName );
extern double GetPrivateProfileDouble( LPCTSTR lpAppName, LPCTSTR lpKeyName, double dDefaultValue, LPCTSTR lpFileName );
extern CString GetPrivateProfileString( LPCTSTR lpAppName, LPCTSTR lpKeyName, CString sDefaultValue, LPCTSTR lpFileName );

extern bool Ping(CString sAddr);

extern bool HexToDec( LPCTSTR shex,int& idec );						//16進制轉10進制

extern POINT_DATA_2F Rotate_Point(POINT_DATA_2F Point, POINT_DATA_2F Centor, double dAngle_Deg);

extern BOOL FindCenter(POINT_DATA_2F P_Start, POINT_DATA_2F P_Positive, POINT_DATA_2F P_Nagative, POINT_DATA_2F &P_Result);

extern double Vector_Dot(VECTOR_DATA_2 Vector_1, VECTOR_DATA_2 Vector_2);
extern double Vector_Cross(VECTOR_DATA_2 Vector_1, VECTOR_DATA_2 Vector_2);
extern double Vector_Length(VECTOR_DATA_2 Vector);
extern double Vector_Deg(VECTOR_DATA_2 Vector_1, VECTOR_DATA_2 Vector_2);
int CALLBACK SortFunc_ASC(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort);
int CALLBACK SortFunc_DEC(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort);
int CharacterCount( CString csString_i, char sChar_i );

extern int get_cpu_usage();  

extern int get_memory_usage(UINT64* mem, UINT64* vmem);  

extern int get_io_bytes(UINT64* read_bytes, UINT64* write_bytes);  

extern int get_GDI_usage(DWORD *nCount);  


//System Message-----------------------------------------------------------------

//Normal Message
#define _MESSAGE_SYSTEM_ENABLE_DONE		0x0000

//Warning Message
#define _WARNING_SYSTEM_ENABLE			0x0000


//Error Message 
#include "SystemCodeCtrl.h"

#ifdef USE_PCI_1203

#include "AdvMotDrv.h"
#include "AdvMotApi.h"
#include "AdvMotErr.h"

#endif

#ifdef USE_BASLER_GIGE
#include <pylon/PylonIncludes.h>
#endif

#define _MODULE_ERROR_PROCESS			0x0001
#define _MODULE_ERROR_PCI_1203			0x0002
#define _MODULE_ERROR_BASLER_GIGE		0x0003
#define _MODULE_ERROR_LASER_MARKING		0x0004
#define _MODULE_MX_COMPONENT_ERROR		0x0005
#define _MODULE_OPENCV_PROCESS			0x0006
#define _MODULE_ERROR_ADVANTECH_DAQ     0x0007
#define _MODULE_ERROR_HIKVISION_GIGE	0x0008
#define _MODULE_ERROR_EPSON_RC			0x0009


//--------------------------------------PROCESS ERROR List-------------------------------------
	//Process IO Error 0x1000~0x1fff
	#define _ALARM_PROC_ADVANTECH_DAQ_DATABASE_FAIL					0x1000
	#define _ALARM_PROC_ADVANTECH_DAQ_NOT_FOUND						0x1001

	#define _ALARM_PROC_STEPPROCESS_PCB_RB_SIGNAL_ORG_TIMEOUT		0x1200	
	#define _ALARM_PROC_STEPPROCESS_PCB_RB_SIGNAL_DIS_TIMEOUT		0x1201	
	#define _ALARM_PROC_STEPPROCESS_PCB_RB_SIGNAL_ANGLE_TIMEOUT		0x1202

	#define _ALARM_PROC_STEPPROCESS_PCB_PATTERN_FIND_FAIL			0x1210

	#define _ALARM_PROC_STEPPROCESS_TAPE_RB_SIGNAL_ORG_TIMEOUT		0x1300	
	#define _ALARM_PROC_STEPPROCESS_TAPE_RB_SIGNAL_DIS_TIMEOUT		0x1301	
	#define _ALARM_PROC_STEPPROCESS_TAPE_RB_SIGNAL_ANGLE_TIMEOUT	0x1302

	#define _ALARM_PROC_STEPPROCESS_TAPE_PATTERN_FIND_FAIL			0x1310

	#define _ALARM_PROC_STEPPROCESS_PCB_UP_TIMEOUT					0x1400
	#define _ALARM_PROC_STEPPROCESS_PCB_DOWN_TIMEOUT				0x1401
	#define _ALARM_PROC_STEPPROCESS_PCB_FORWARD_TIMEOUT				0x1402
	#define _ALARM_PROC_STEPPROCESS_PCB_BACKWARD_TIMEOUT			0x1403

	#define _ALARM_PROC_STEPPROCESS_ROBOT_INITIAL_TIMEOUT			0x1500
	#define _ALARM_PROC_STEPPROCESS_ROBOT_MOVE_PORT_TIMEOUT			0x1501
	#define _ALARM_PROC_STEPPROCESS_ROBOT_GET_TAPE_TIMEOUT			0x1502
	#define _ALARM_PROC_STEPPROCESS_ROBOT_PUT_TAPE_TIMEOUT			0x1503
	#define _ALARM_PROC_STEPPROCESS_ROBOT_CALI_TAPE_TIMEOUT			0x1504
	#define _ALARM_PROC_STEPPROCESS_ROBOT_CALI_PCB_TIMEOUT			0x1505

	#define _ALARM_PROC_STEPPROCESS_CV_IN_TIMEOUT					0x1600
	#define _ALARM_PROC_STEPPROCESS_CV_OUT_TIMEOUT					0x1601

	#define _ALARM_THREAD_RB_TIMEOUT								0x1700
	#define _ALARM_THREAD_CV_TIMEOUT								0x1701
	#define _ALARM_THREAD_PCB_TIMEOUT								0x1702

	#define _ALARM_PROC_TAPE_COMEOUT_TIMEOUT						0x1800

	//Process Axis Error 0x2000~0x3fff
	#define _ALARM_PROC_MOVE_X_MOTOR_ALARM 0X2000

	//Camera
	#define _ALARM_PROC_CAMERA_NONE					0x4000
	#define _ALARM_PROC_CAMERA_MISSING				0x4001

	//OpenCV
	#define  _ALARM_PROC_OPENCV_EXCEPTION			0x5000

	//Product Data 0x7000~0x7fff

//----------------------------------------------------------------------------------------------

union MODULE_ERROR_CODE
{
	LONGLONG            llVal;
	LONG                lVal;
	BYTE                bVal;
	SHORT               iVal;
	FLOAT               fltVal;
	DOUBLE              dblVal;
	VARIANT_BOOL        boolVal;
	_VARIANT_BOOL       bool;
	SCODE               scode;
	CY                  cyVal;
	DATE                date;
	BSTR                bstrVal;
	IUnknown            *punkVal;
	IDispatch           *pdispVal;
	SAFEARRAY           *parray;
	BYTE                *pbVal;
	SHORT               *piVal;
	LONG                *plVal;
	LONGLONG            *pllVal;
	FLOAT               *pfltVal;
	DOUBLE              *pdblVal;
	VARIANT_BOOL        *pboolVal;
	_VARIANT_BOOL       *pbool;
	SCODE               *pscode;
	CY                  *pcyVal;
	DATE                *pdate;
	BSTR                *pbstrVal;
	IUnknown            **ppunkVal;
	IDispatch           **ppdispVal;
	SAFEARRAY           **pparray;
	VARIANT             *pvarVal;
	PVOID               byref;
	CHAR                cVal;
	USHORT              uiVal;
	ULONG               ulVal;
	ULONGLONG           ullVal;
	INT                 intVal;
	UINT                uintVal;
	DECIMAL             *pdecVal;
	CHAR                *pcVal;
	USHORT              *puiVal;
	ULONG               *pulVal;
	ULONGLONG           *pullVal;
	INT                 *pintVal;
	UINT                *puintVal;

	MODULE_ERROR_CODE()
	{
		memset(this, 0, sizeof(MODULE_ERROR_CODE));
	}
};

class SYSTEM_ERROR : public std::exception, CSystemCodeCtrl
{
public:
	SYSTEM_ERROR();
	SYSTEM_ERROR(CString ErrorFunction, unsigned long ErrModule, void* ErrorCode);


	CString ERROR_LOCATION[10];

	int nErrorLocationIndex;;

	unsigned long ErrorModule;

	MODULE_ERROR_CODE ModuleErrCode;

	CString ModuleErrDescription;

	void SetLocation(CString Location);
	CString GetErrorMessage();
	CString DAQErrorDescription(ULONG ErrorCode);
};