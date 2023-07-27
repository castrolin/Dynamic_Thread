#include "stdAfx.h"
#include "CommonFunc.h"

 
void getLinePara(float x1, float y1, float x2, float y2, LinePara & LP)
{
	double m = 0;

	m = x2 - x1;

	if (0 == m)
	{
		LP.k = 10000.0;
		LP.b = y1 - LP.k * x1;
	}
	else
	{
		LP.k = (y2 - y1) / (x2 - x1);
		LP.b = y1 - LP.k * x1;
	}


}

bool getLinCross(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4,  Point2f & pt)
{

	LinePara para1, para2;
	getLinePara(x1, y1, x2, y2, para1);
	getLinePara(x3, y3, x4, y4, para2);
  
	if (abs(para1.k - para2.k) > 0.5)
	{
		pt.x = (para2.b - para1.b) / (para1.k - para2.k);
		pt.y = para1.k * pt.x + para1.b;

		return true;

	}
	else
	{
		return false;
	}

}

extern float getOverLinePoint_Y( float X, POINT_DATA_2F Point_1, POINT_DATA_2F Point_2 )
{
	LinePara LineParam;

	getLinePara(float(Point_1.Point_X), float(Point_1.Point_Y), float(Point_2.Point_X), float(Point_2.Point_Y), LineParam);

	return LineParam.k * X + LineParam.b;

}

extern float getOverLinePoint_X(float Y, POINT_DATA_2F Point_1, POINT_DATA_2F Point_2 )
{
	LinePara LineParam;

	getLinePara(float(Point_1.Point_X), float(Point_1.Point_Y), float(Point_2.Point_X), float(Point_2.Point_Y), LineParam);

	return (Y - LineParam.b) / LineParam.k;
}

CString FormatString( CString Format, ... )
{
	CString ReturnMsg;
	char vbuf[4096];

	va_list marker;

	va_start(marker, Format);
	ZeroMemory(vbuf, sizeof(vbuf));
	vsprintf(vbuf, Format, marker);
	va_end(marker);

	ReturnMsg.Format("%s", vbuf);

	return ReturnMsg;
}

BOOL DoEvents()
{ 
	MSG msg;

	while(::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
	{
		if(msg.message==WM_QUIT)
			return FALSE;
		::TranslateMessage(&msg);
		::DispatchMessage(&msg);

	}

	return TRUE;
}

void Delay(DWORD Msecs)	/* delay Miniseconds */
{
	DWORD dwBeginTime = ::GetTickCount();
	do{
		DoEvents();
		Sleep(1);
	} while ((::GetTickCount() - dwBeginTime) < Msecs);
}

double GetDlgItem2Double(HWND hWnd, UINT nID, bool bSigned)
{
	CString nText;
	CWnd::FromHandle(GetDlgItem(hWnd, nID))->GetWindowText(nText);

	return atof(nText);
}

float GetDlgItem2Float(HWND hWnd, UINT nID, bool bSigned)
{
	CString nText;
	float fRet;
	CWnd::FromHandle(GetDlgItem(hWnd, nID))->GetWindowText(nText);
	fRet = (float)atof(nText);
	return fRet;
}

int GetDlgItem2Int(HWND hWnd, UINT nID, bool bSigned)
{
	CString nText;
	CWnd::FromHandle(GetDlgItem(hWnd, nID))->GetWindowText(nText);
	return atoi(nText);
}

CString GetDlgItemString(HWND hWnd, UINT nID)
{
	CString nText;
	CWnd::FromHandle(GetDlgItem(hWnd, nID))->GetWindowText(nText);
	return nText;
}

float GetPrivateProfileFloat( LPCTSTR lpAppName, LPCTSTR lpKeyName, float dDefaultValue, LPCTSTR lpFileName )
{
	int		nTokenIndex = 0;
	CString strRetStr, strBuf;
	char	chBuf[MAX_PATH]={};
	DWORD	dRet = 0;

	dRet = GetPrivateProfileString(lpAppName, lpKeyName, "", chBuf, MAX_PATH, lpFileName);

	if (dRet == 0)
		return 0;

	strRetStr.Format("%s", chBuf);
	float ReturnValue = (float)atof(strRetStr);

	return ReturnValue;
}

double GetPrivateProfileDouble( LPCTSTR lpAppName, LPCTSTR lpKeyName, double dDefaultValue, LPCTSTR lpFileName )
{
	int		nTokenIndex = 0;
	CString strRetStr, strBuf;
	char	chBuf[MAX_PATH]={};
	DWORD	dRet = 0;

	dRet = GetPrivateProfileString(lpAppName, lpKeyName, "", chBuf, MAX_PATH, lpFileName);

	if (dRet == 0)
		return 0;

	strRetStr.Format("%s", chBuf);
	return atof(strRetStr);
}

CString GetPrivateProfileString( LPCTSTR lpAppName, LPCTSTR lpKeyName, CString sDefaultValue, LPCTSTR lpFileName )
{
	int		nTokenIndex = 0;
	CString strRetStr, strBuf;
	char	chBuf[256]={};
	DWORD	dRet = 0;

	dRet = GetPrivateProfileString(lpAppName, lpKeyName, "", chBuf, 256, lpFileName);

	if (dRet == 0)
		return sDefaultValue;

	strRetStr.Format("%s", chBuf);
	return strRetStr;
}

bool Ping(CString sAddr)
{
	char *pIPAddr = sAddr.GetBuffer(0);

	bool Status;

	HANDLE iHwnd;
	iHwnd=IcmpCreateFile();
	IPAddr pAddr;
	pAddr=(IPAddr)inet_addr (pIPAddr);
	icmp_echo_reply pData;

	IcmpSendEcho(iHwnd,pAddr,NULL,0,NULL,(LPVOID)&pData,sizeof(icmp_echo_reply),1000);

	if (pData.Status==0)
		Status = TRUE;
	else
		Status = FALSE;

	IcmpCloseHandle(iHwnd);

	return Status;

}

double Vector_Dot(VECTOR_DATA_2 Vector_1, VECTOR_DATA_2 Vector_2)
{	
	return Vector_1.Vector_X * Vector_2.Vector_X + Vector_1.Vector_Y * Vector_2.Vector_Y;
}

double Vector_Cross(VECTOR_DATA_2 Vector_1, VECTOR_DATA_2 Vector_2)	//Vector1 -> Vector2
{

	return Vector_1.Vector_X * Vector_2.Vector_Y - Vector_1.Vector_Y * Vector_2.Vector_X;
}

double Vector_Length(VECTOR_DATA_2 Vector)
{
	return sqrt(Vector.Vector_X * Vector.Vector_X + Vector.Vector_Y * Vector.Vector_Y);
}

double Vector_Deg(VECTOR_DATA_2 Vector_1, VECTOR_DATA_2 Vector_2)//Vector1 -> Vector2
{

	
	double Length_1 = Vector_Length(Vector_1);
	double Length_2 = Vector_Length(Vector_2);

	double cosθ =  Vector_Dot(Vector_1, Vector_2) / (Length_1 * Length_2);
	//bool bCCW = (Vector_Cross(Vector_1, Vector_2) >= 0) ? true : false;

	double θ1;
	if(cosθ <= 1)
		θ1 = acos(cosθ);  // [0, π]
	else
		θ1 = 0.0;

	double degree = θ1 * (180 / PI) ;

	/*if(bCCW)
		degree = fabs(degree);
	else
		degree = -fabs(degree);*/

	return degree;
}

bool HexToDec( LPCTSTR shex,int& idec )
{
	int i,mid;
	int len = lstrlen( shex );
	if( len>8 ) return FALSE;
	mid = 0; idec = 0;
	for( i=0;i<len;i++ )
	{
		if( shex[i]>='0'&&shex[i]<='9' ) mid = shex[i]-'0';
		else if( shex[i]>='a'&&shex[i]<='f' ) mid = shex[i] -'a' +10;
		else if( shex[i]>='A'&&shex[i]<='F' ) mid = shex[i] -'A' +10;
		else return FALSE;
		mid <<= ((len-i-1)<<2);
		idec |= mid;
	}
	return TRUE;
}

extern POINT_DATA_2F Rotate_Point( POINT_DATA_2F Point, POINT_DATA_2F Centor, double dAngle_Deg )
{
	POINT_DATA_2F Temp, Result;
	double dAngle_Rad;

	Temp.Point_X = Point.Point_X - Centor.Point_X;
	Temp.Point_Y = Point.Point_Y - Centor.Point_Y;

	dAngle_Rad = dAngle_Deg / 180 * 3.14159;


	Result.Point_X = Temp.Point_X * cos(dAngle_Rad) - Temp.Point_Y * sin(dAngle_Rad);
	Result.Point_Y = Temp.Point_X * sin(dAngle_Rad) + Temp.Point_Y * cos(dAngle_Rad);

	Result.Point_X = Result.Point_X + Centor.Point_X;
	Result.Point_Y = Result.Point_Y + Centor.Point_Y;

	return Result;
}

extern BOOL FindCenter( POINT_DATA_2F P_Start, POINT_DATA_2F P_Positive, POINT_DATA_2F P_Nagative, POINT_DATA_2F &P_Result )
{

	POINT_DATA_2F P_Positive_C, P_Nagative_C;

	//Centor between two point 
	//P_C.Point_X = (P2.Point_X - P1.Point_X) / 2 + P1.Point_X;
	//P_C.Point_Y = (P2.Point_Y - P1.Point_Y) / 2 + P1.Point_Y;

	//Centor between  P_Positive and P_Start
	P_Positive_C.Point_X = (P_Start.Point_X - P_Positive.Point_X) / 2 + P_Positive.Point_X;
	P_Positive_C.Point_Y = (P_Start.Point_Y - P_Positive.Point_Y) / 2 + P_Positive.Point_Y;

	//Centor between  P_Start and P_Nagative
	P_Nagative_C.Point_X = (P_Nagative.Point_X - P_Start.Point_X) / 2 + P_Start.Point_X;
	P_Nagative_C.Point_Y = (P_Nagative.Point_Y - P_Start.Point_Y) / 2 + P_Start.Point_Y;


	POINT_DATA_2F P1_2, P1_3;
	POINT_DATA_2F P2_2, P2_3;

	//P_Positive Rotate 90 Deg using P_Positive_C as Centor
	P1_2 = Rotate_Point(P_Positive, P_Positive_C, 90);

	//P_Start Rotate 90 Deg using P_Positive_C as Centor
	P1_3 = Rotate_Point(P_Start, P_Positive_C, 90);

	//P_Start Rotate 90 Deg using P_Nagative_C as Centor
	P2_2 = Rotate_Point(P_Start, P_Nagative_C, 90);

	//P_Nagative Rotate 90 Deg using P_Nagative_C as Centor
	P2_3 = Rotate_Point(P_Nagative, P_Nagative_C, 90);

	Point2f Centor;

	if(getLinCross(float(P1_2.Point_X), float(P1_2.Point_Y), float(P1_3.Point_X), float(P1_3.Point_Y), float(P2_2.Point_X), float(P2_2.Point_Y), float(P2_3.Point_X), float(P2_3.Point_Y), Centor) == false)
		return false;

	POINT_DATA_2F Result;

	P_Result.Point_X = double(Centor.x);
	P_Result.Point_Y = double(Centor.y);

	return true;
}

int CALLBACK SortFunc_ASC(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort)
{
	int nRetVal=1;

	CListCtrl *m_Tmp = (CListCtrl *)lParamSort;

	CString    strItem1 = m_Tmp->GetItemText(lParam1, 0);	// 取得該行的某一個元素的字串
	CString    strItem2 = m_Tmp->GetItemText(lParam2, 0);	// 取得該行的某一個元素的字串

	nRetVal = strcmp(strItem1, strItem2);

	return nRetVal;
}

int CALLBACK SortFunc_DEC(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort)
{
	int nRetVal=1;

	CListCtrl *m_Tmp = (CListCtrl *)lParamSort;

	CString    strItem1 = m_Tmp->GetItemText(lParam1, 0);	// 取得該行的某一個元素的字串
	CString    strItem2 = m_Tmp->GetItemText(lParam2, 0);	// 取得該行的某一個元素的字串

	nRetVal = strcmp(strItem1, strItem2);

	if(nRetVal>0)
		nRetVal = -1;
	else if(nRetVal<0)
		nRetVal = 1;

	return nRetVal;
}

int CharacterCount( CString csString_i, char sChar_i )
{
	if( csString_i.IsEmpty() || sChar_i == 0 )
	{
		return 0;
	}

	int nFind = -1;
	int nCount = 0;
	while( -1 != ( nFind = csString_i.Find( sChar_i, nFind + 1 )))
	{
		nCount++;
	}
	return nCount;
}

static UINT64 file_time_2_utc(const FILETIME* ftime)  
{  
	LARGE_INTEGER li;  

	ASSERT(ftime);  
	li.LowPart = ftime->dwLowDateTime;  
	li.HighPart = ftime->dwHighDateTime;  
	return li.QuadPart;  
}  

static int get_processor_number()  
{  
	SYSTEM_INFO info;  
	GetSystemInfo(&info);  
	return (int)info.dwNumberOfProcessors;  
}  

int get_cpu_usage()
{
	static int processor_count_ = -1;  

	static INT64 last_time_ = 0;  
	static INT64 last_system_time_ = 0;  


	FILETIME now;  
	FILETIME creation_time;  
	FILETIME exit_time;  
	FILETIME kernel_time;  
	FILETIME user_time;  
	INT64 system_time;  
	INT64 time;  
	INT64 system_time_delta;  
	INT64 time_delta;  

	int cpu = -1;  


	if(processor_count_ == -1)  
	{  
		processor_count_ = get_processor_number();  
	}  

	GetSystemTimeAsFileTime(&now);  

	if (!GetProcessTimes(GetCurrentProcess(), &creation_time, &exit_time,  
		&kernel_time, &user_time))  
	{  
		// We don't assert here because in some cases (such as in the Task Manager)  
			// we may call this function on a process that has just exited but we have  
			// not yet received the notification.  
			return -1;  
	}  
	system_time = (file_time_2_utc(&kernel_time) + file_time_2_utc(&user_time))   

		/  
		processor_count_;  
	time = file_time_2_utc(&now);  

	if ((last_system_time_ == 0) || (last_time_ == 0))  
	{  
		// First call, just set the last values.  
		last_system_time_ = system_time;  
		last_time_ = time;  
		return -1;  
	}  

	system_time_delta = system_time - last_system_time_;  
	time_delta = time - last_time_;  

	ASSERT(time_delta != 0);  

	if (time_delta == 0)  
		return -1;  

	// We add time_delta / 2 so the result is rounded.  
	cpu = (int)((system_time_delta * 100 + time_delta / 2) / time_delta);  
	last_system_time_ = system_time;  
	last_time_ = time;  
	return cpu;  
}

int get_memory_usage(UINT64* mem, UINT64* vmem)
{
	PROCESS_MEMORY_COUNTERS pmc;  
	if(GetProcessMemoryInfo(GetCurrentProcess(), &pmc, sizeof(pmc)))  
	{  
		if(mem) *mem = pmc.WorkingSetSize;  
		if(vmem) *vmem = pmc.PagefileUsage;  
		return 0;  
	}  
	return -1;  
}

int get_io_bytes(UINT64* read_bytes, UINT64* write_bytes)
{
	IO_COUNTERS io_counter;  
	if(GetProcessIoCounters(GetCurrentProcess(), &io_counter))  
	{  
		if(read_bytes) *read_bytes = io_counter.ReadTransferCount;  
		if(write_bytes) *write_bytes = io_counter.WriteTransferCount;  
		return 0;  
	}  
	return -1;  
}

int get_GDI_usage( DWORD *nCount )
{
	*nCount = GetGuiResources(GetCurrentProcess(), GR_GDIOBJECTS);

	if(*nCount == 0)
		return -1;

	return 0;
}

//Class TriggerDetect_R 

UINT TriggerDetect::DetectProc( LPVOID Info )
{
	TriggerDetect* this_obj = (TriggerDetect*)Info;

	bool bLoop = true;

	HANDLE h[2];

	h[0] = this_obj->m_Close;
	h[1] = this_obj->m_Detect;

	while(bLoop)
	{
		DWORD nEvent = WaitForMultipleObjects(2, h, FALSE, INFINITE) - WAIT_OBJECT_0;

		switch(nEvent)
		{
		case 0:
			bLoop = false;
			break;

		case 1:
			switch(this_obj->m_Type)
			{
			case _TIG_TYPE_R:
				if((*this_obj->m_Status) != this_obj->m_LastStatus)
				{
					if(this_obj->m_LastStatus == false)
						this_obj->pTriggered(this_obj->m_Object);

					this_obj->m_LastStatus = (*this_obj->m_Status);

				}
				break;
			case _TIG_TYPE_F:
				if((*this_obj->m_Status) != this_obj->m_LastStatus)
				{
					if(this_obj->m_LastStatus == true)
						this_obj->pTriggered(this_obj->m_Object);

					this_obj->m_LastStatus = (*this_obj->m_Status);

				}
				break;
			case _TIG_TYPE_A:
				if((*this_obj->m_Status) != this_obj->m_LastStatus)
				{
					this_obj->pTriggered(this_obj->m_Object);

					this_obj->m_LastStatus = (*this_obj->m_Status);
				}
				break;

			}

			break;
		}

		Sleep(10);
	}

	return 0;
}

TriggerDetect::TriggerDetect(LPVOID Object, bool *bStatus)
{
	m_Type = _TIG_TYPE_R;
	m_Status = bStatus;
	m_Object = Object;

	m_Close = CreateEvent(NULL, TRUE, FALSE, NULL);
	m_Detect = CreateEvent(NULL, TRUE, FALSE, NULL);

	m_DetectThd = AfxBeginThread(DetectProc, (LPVOID)this, THREAD_PRIORITY_NORMAL, 0, CREATE_SUSPENDED);
	m_DetectThd->m_bAutoDelete = FALSE;
	m_DetectThd->ResumeThread();
}

TriggerDetect::~TriggerDetect()
{
	ResetEvent(m_Detect);
	Sleep(10);
	SetEvent(m_Close);

	WaitForSingleObject(m_DetectThd->m_hThread, 100);

}

void TriggerDetect::RegTriggeredProc( void (*pFunc)(LPVOID pObject) )
{
	pTriggered = pFunc;
}

void TriggerDetect::SetTriggerType( UINT nType )
{
	m_Type = nType;

	if(m_Type == _TIG_TYPE_R)
		m_LastStatus = false;
	else if(m_Type == _TIG_TYPE_F)
		m_LastStatus = true;
}

void TriggerDetect::DetectStart()
{
	m_LastStatus = *m_Status;
	SetEvent(m_Detect);
}

void TriggerDetect::DetectStop()
{
	ResetEvent(m_Detect);
}

void TriggerDetect::Reset()
{
	if(m_Type == _TIG_TYPE_R)
		m_LastStatus = false;
	else if(m_Type == _TIG_TYPE_F)
		m_LastStatus = true;
}


#ifdef USE_LASER_MARKING

CString LaserErr2String( unsigned long nErrorID )
{
	CString FilePath;
	FilePath.Format("..\\Debug\\CtrlPrms\\LaserErrorList.ini");

	CString sErrorID, sErrorMsg;

	sErrorID.Format("02d", nErrorID);

	sErrorMsg = GetPrivateProfileString("ErrorList", sErrorID, "NA", FilePath);

	return sErrorMsg;
}

#endif

//System Message-----------------------------------------------------------------


SYSTEM_ERROR::SYSTEM_ERROR()
{

}

SYSTEM_ERROR::SYSTEM_ERROR( CString ErrorFunction, unsigned long ErrModule, void* ErrorCode )
{

	ERROR_LOCATION[0] = ErrorFunction;

	nErrorLocationIndex = 1;

	ErrorModule = ErrModule;

	switch(ErrorModule)
	{

	case _MODULE_ERROR_PROCESS:
		ModuleErrCode.ulVal = *(ULONG*)ErrorCode;
		ModuleErrDescription = GetCode(_CODE_ALARM_, ModuleErrCode.ulVal);


		break;

#ifdef USE_PCI_1203
	case _MODULE_ERROR_PCI_1203:
		ModuleErrCode.ulVal = *(ULONG*)ErrorCode;
		Acm_GetErrorMessage(ModuleErrCode.ulVal, ModuleErrDescription.GetBuffer(256), 256);

		break;
#endif

#ifdef USE_BASLER_GIGE
	case _MODULE_ERROR_BASLER_GIGE:
		ModuleErrCode.ulVal = 0;
		ModuleErrDescription = CString((char *)ErrorCode);

		break;
#endif

#ifdef USE_LASER_MARKING
	case _MODULE_ERROR_LASER_MARKING:
		ModuleErrCode.ulVal = *(ULONG*)ErrorCode;
		ModuleErrDescription = LaserErr2String(ModuleErrCode.ulVal);

		break;
#endif

#ifdef USE_ADVANTECH_DAQ
	case _MODULE_ERROR_ADVANTECH_DAQ:
		ModuleErrCode.ulVal = *(ULONG*)ErrorCode;
		//Acm_GetErrorMessage(ModuleErrCode.ulVal, ModuleErrDescription.GetBuffer(256), 256);
		//ModuleErrDescription.Format("%d", ModuleErrCode.ullVal);
		ModuleErrDescription = DAQErrorDescription(ModuleErrCode.ulVal);

		break;
#endif

#ifdef USE_MX_COMPONENT
	case _MODULE_MX_COMPONENT_ERROR:
		ModuleErrCode.ulVal = *(ULONG*)ErrorCode;
		ModuleErrDescription = "Please Read MX Component Manual for Error Code Information";

		break;
#endif

#ifdef USE_HIKVISION_GIGE
	case _MODULE_ERROR_HIKVISION_GIGE:
		ModuleErrCode.ulVal = *(ULONG*)ErrorCode;
		ModuleErrDescription = CString((char *)ErrorCode);

		break;
#endif

#ifdef USE_EPSON_RC
	case _MODULE_ERROR_EPSON_RC:
		ModuleErrCode.ulVal = *(ULONG*)ErrorCode;

		switch(ModuleErrCode.ulVal)
		{
		case 0:
			ModuleErrDescription = "No Error";
			break;
		case 10:
			ModuleErrDescription = "No Header";
			break;
		case 11:
			ModuleErrDescription = "No Login";
			break;
		case 12:
			ModuleErrDescription = "Format Error";
			break;
		case 13:
			ModuleErrDescription = "Password Error";
			break;
		case 14:
			ModuleErrDescription = "Value Over Range";
			break;
		case 15:
			ModuleErrDescription = "Variable not Exist";
			break;
		case 19:
			ModuleErrDescription = "Timeout";
			break;
		case 20:
			ModuleErrDescription = "Controller not Ready";
			break;
		case 21:
			ModuleErrDescription = "Executing Command";
			break;
		case 98:
			ModuleErrDescription = "Need Password";
			break;
		case 99:
			ModuleErrDescription = "Communication Error";
			break;
		case 900:
			ModuleErrDescription = "Request Command Decode Error";
			break;
		case 901:
			ModuleErrDescription = "Request and Response Commands Compare Error";
			break;
		case 902:
			ModuleErrDescription = "Response Command Decode Error";
			break;
		case 903:
			ModuleErrDescription = "Response Command not Numeric";
			break;
		case 950:
			ModuleErrDescription = "Variable Parser Error";
			break;
		case 999:
			ModuleErrDescription = "Communication Timeout";
			break;
		case 20000:
			ModuleErrDescription = "Vac ACK On is Check Timeout";
			break;
		case 20001:
			ModuleErrDescription = "Vac ACK Off is Check Timeout";
			break;
		case 20002:
			ModuleErrDescription = "Vac On is Check Timeout";
			break;
		case 20010:
			ModuleErrDescription = "Air ACK On is Check Timeout";
			break;
		case 20011:
			ModuleErrDescription = "Air ACK Off is Check Timeout";
			break;
		case 20012:
			ModuleErrDescription = "Air On is Check Timeout";
			break;
		case 20015:
			ModuleErrDescription = "OPS ON VAC ERR";
			break;
		case 20016:
			ModuleErrDescription = "VAC ON OPS ERR";
			break;
		case 20017:
			ModuleErrDescription = "VAC ERR OPS ERR";
			break;
		case 20020:
			ModuleErrDescription = "Target Port is not Set Target Port is not Set";
			break;
		case 20021:
			ModuleErrDescription = "Target Layer is not Set";
			break;
		case 20022:
			ModuleErrDescription = "Recipe Index is not Set";
			break;
		case 20023:
			ModuleErrDescription = "Speed is not Set";
			break;
		case 20030:
			ModuleErrDescription = "Calibrate Angle not Set";
			break;
		case 20031:
			ModuleErrDescription = "Calibrate Angle Over Range";
			break;
		case 20040:
			ModuleErrDescription = "Calibrate Distance not Set";
			break;
		case 20041:
			ModuleErrDescription = "Calibrate Distance Over Range";
			break;
		case 20050:
			ModuleErrDescription = "I_ACK_CAL_ORG Timeout";
			break;
		case 20051:
			ModuleErrDescription = "I_ACK_CAL_Angle Timeout";
			break;
		case 20052:
			ModuleErrDescription = "I_ACK_CAL_DISX Timeout";
			break;
		case 20053:
			ModuleErrDescription = "I_ACK_CAL_DISY Timeout";
			break;
		case 20060:
			ModuleErrDescription = "I_ACK_ALI Timeout";
			break;
		case 20070:
			ModuleErrDescription = "g_ForkMappingOffset not Defined";
			break;
		case 20071:
			ModuleErrDescription = "g_MappingCSTGap Defined";
			break;
		case 20072:
			ModuleErrDescription = "I_RecipeIndex not Defined";
			break;
		case 20100:
			ModuleErrDescription = "CCLink Remote not Ready";
			break;
		case 20101:
			ModuleErrDescription = "Robot Not in Safe Position";
			break;
		case 20102:
			ModuleErrDescription = "Point Not Defined";
			break;
		case 20103:
			ModuleErrDescription = "Record Point Not Defined after Recording";
			break;
		case 20104:
			ModuleErrDescription = "Record Point Type Not Defined after Recording";
			break;
		case 20105:
			ModuleErrDescription = "Record Point Number out of Range";
			break;
		case 29000:
			ModuleErrDescription = "RFunction not Defined";
			break;
		case 29999:
			ModuleErrDescription = "Over Torque";
			break;
		}

		break;
#endif

	}
}

void SYSTEM_ERROR::SetLocation( CString Location )
{
	if(nErrorLocationIndex <= 9)
	{
		ERROR_LOCATION[nErrorLocationIndex] = Location;

		nErrorLocationIndex ++;
	}
}

CString SYSTEM_ERROR::GetErrorMessage()
{
	
	CString ErrorMessage;

	if(ModuleErrDescription.IsEmpty())
		ModuleErrDescription = "Description not Defined";

	switch(ErrorModule)
	{
	case _MODULE_ERROR_PROCESS:
		
		ErrorMessage.Append("Error Module = Process Error, ");
		ErrorMessage.Append(FormatString("Error Code = %#X, ", ModuleErrCode.ulVal));
		ErrorMessage.Append(FormatString("Error Description = %s, ", ModuleErrDescription));

		break;

#ifdef USE_PCI_1203
	case _MODULE_ERROR_PCI_1203:
		ErrorMessage.Append("Error Module = PCI_1203, ");
		ErrorMessage.Append(FormatString("Error Code = %#X, ", ModuleErrCode.ulVal));
		ErrorMessage.Append(FormatString("Error Description = %s, ", ModuleErrDescription));
		break;
#endif

#ifdef USE_BASLER_GIGE
	case _MODULE_ERROR_BASLER_GIGE:
		ErrorMessage.Append("Error Module = Basler Camera, ");
		ErrorMessage.Append(FormatString("Error Code = %#X, ", ModuleErrCode.ulVal));
		ErrorMessage.Append(FormatString("Error Description = %s, ", ModuleErrDescription));

		break;
#endif

#ifdef USE_LASER_MARKING
	case _MODULE_ERROR_LASER_MARKING:
		ErrorMessage.Append("Error Module = Laser Marking, ");
		ErrorMessage.Append(FormatString("Error Code = %#X, ", ModuleErrCode.ulVal));
		ErrorMessage.Append(FormatString("Error Description = %s, ", ModuleErrDescription));

		break;
#endif

#ifdef USE_MX_COMPONENT
	case _MODULE_MX_COMPONENT_ERROR:
		ErrorMessage.Append("Error Module = MX Component, ");
		ErrorMessage.Append(FormatString("Error Code = %#X, ", ModuleErrCode.ulVal));
		ErrorMessage.Append(FormatString("Error Description = %s, ", ModuleErrDescription));
		break;
#endif

#ifdef USE_ADVANTECH_DAQ
	case _MODULE_ERROR_ADVANTECH_DAQ:
		ErrorMessage.Append("Error Module = PCI_1730, ");
		ErrorMessage.Append(FormatString("Error Code = %#X, ", ModuleErrCode.ulVal));
		ErrorMessage.Append(FormatString("Error Description = %s, ", ModuleErrDescription));
		break;
#endif

#ifdef USE_HIKVISION_GIGE
	case _MODULE_ERROR_HIKVISION_GIGE:
		ErrorMessage.Append("Error Module = HIKVISION GIGE, ");
		ErrorMessage.Append(FormatString("Error Code = %#X, ", ModuleErrCode.ulVal));
		ErrorMessage.Append(FormatString("Error Description = %s, ", ModuleErrDescription));
		break;
#endif

#ifdef USE_EPSON_RC
	case _MODULE_ERROR_EPSON_RC:
		ErrorMessage.Append("Error Module = EPSON RC, ");
		ErrorMessage.Append(FormatString("Error Code = %#X, ", ModuleErrCode.ulVal));
		ErrorMessage.Append(FormatString("Error Description = %s, ", ModuleErrDescription));
		break;
#endif

	}

	for(int x = 0; x < nErrorLocationIndex; x ++)
	{
		ErrorMessage.Append(FormatString("Error Location %d = %s, ", nErrorLocationIndex - 1 - x, ERROR_LOCATION[nErrorLocationIndex - 1 - x]));
	}

	return ErrorMessage;
}


CString SYSTEM_ERROR::DAQErrorDescription(ULONG ErrorCode)
{
	CString Errdescription;
	switch(ErrorCode)
	{
	case 0xA0000000:
		Errdescription = "WarningIntrNotAvailable";
		return Errdescription;
	case 0xa0000001:
		Errdescription = "WarningParamOutOfRange";
		return Errdescription;
	case 0xA0000002:
		Errdescription = "WarningPropValueOutOfRange";
		return Errdescription;
	case 0xA0000003:
		Errdescription = "WarningParamOutOfRange";
		return Errdescription;
	case 0xA0000004:
		Errdescription = "WarningPropValueConflict";
		return Errdescription;
	case 0xA0000005:
		Errdescription = "WarningVrgOfGroupNotSame";
		return Errdescription;
	case 0xA0000006:
		Errdescription = "WarningPropPartialFailed";
		return Errdescription;
	case 0xA0000007:
		Errdescription = "WarningFuncStopped";
		return Errdescription;
	case 0xA0000008:
		Errdescription = "WarningFuncTimeout";
		return Errdescription;
	case 0xA0000009:
		Errdescription = "WarningCacheOverflow";
		return Errdescription;
	case 0xA000000A:
		Errdescription = "WarningBurnout";
		return Errdescription;
	case 0xA000000B:
		Errdescription = "WarningRecordEnd";
		return Errdescription;
	case 0xA000000C:
		Errdescription = "WarningProfileNotValid";
		return Errdescription;
	case 0xa000000D:
		Errdescription = "WarningFileMismatch";
		return Errdescription;
	case 0xE0000000:
		Errdescription = "ErrorHandleNotValid";
		return Errdescription;
	case 0xE0000001:
		Errdescription = "ErrorParamOutOfRange";
		return Errdescription;

	case 0xE0000002:
		Errdescription = "ErrorParamNotSpted ";
		return Errdescription;
	case 0xE0000003:
		Errdescription = "ErrorParamFmtUnexpted";
		return Errdescription;

	case 0xE0000004:
		Errdescription = "ErrorMemoryNotEnough";
		return Errdescription;
	case 0xE0000005:
		Errdescription = "ErrorBufferIsNull";
		return Errdescription;

	case 0xE0000006:
		Errdescription = "ErrorBufferTooSmall";
		return Errdescription;
	case 0xE0000007:
		Errdescription = "ErrorDataLenExceedLimit";
		return Errdescription;

	case 0xE0000008:
		Errdescription = "ErrorFuncNotSpted";
		return Errdescription;
	case 0xE0000009:
		Errdescription = "ErrorEventNotSpted";
		return Errdescription;

	case 0xE000000A:
		Errdescription = "ErrorPropNotSpted";
		return Errdescription;
	case 0xE000000B:
		Errdescription = "ErrorPropReadOnly";
		return Errdescription;

	case 0xE000000C:
		Errdescription = "ErrorPropValueConflict";
		return Errdescription;
	case 0xE000000D:
		Errdescription = "ErrorPropValueOutOfRange";
		return Errdescription;

	case 0xE000000E:
		Errdescription = "ErrorPropValueNotSpted";
		return Errdescription;
	case 0xE000000F:
		Errdescription = "ErrorPrivilegeNotHeld";
		return Errdescription;


	case 0xE0000010:
		Errdescription = " ErrorPrivilegeNotAvailable";
		return Errdescription;
	case 0xE0000011:
		Errdescription = "ErrorDriverNotFound";
		return Errdescription;

	case 0xE0000012:
		Errdescription = "ErrorDriverVerMismatch ";
		return Errdescription;
	case 0xE0000013:
		Errdescription = "ErrorDriverCountExceedLimit";
		return Errdescription;

	case 0xE0000014:
		Errdescription = "ErrorDeviceNotOpened";
		return Errdescription;
	case 0xE0000015:
		Errdescription = "ErrorDeviceNotExist";
		return Errdescription;

	case 0xE0000016:
		Errdescription = "ErrorDeviceUnrecognized";
		return Errdescription;
	case 0xE0000017:
		Errdescription = "ErrorConfigDataLost";
		return Errdescription;

	case 0xE0000018:
		Errdescription = "ErrorFuncNotInited";
		return Errdescription;
	case 0xE0000019:
		Errdescription = "ErrorFuncBusy";
		return Errdescription;

	case 0xE000001A:
		Errdescription = "ErrorIntrNotAvailable";
		return Errdescription;
	case 0xE000001B:
		Errdescription = "ErrorDmaNotAvailable";
		return Errdescription;

	case 0xE000001C:
		Errdescription = "ErrorDeviceIoTimeOut";
		return Errdescription;
	case 0xE000001D:
		Errdescription = "ErrorSignatureNotMatch";
		return Errdescription;

	case 0xE000001E:
		Errdescription = "ErrorFuncConflictWithBfdAi";
		return Errdescription;
	case 0xE000001F:
		Errdescription = "ErrorVrgNotAvailableInSeMode";
		return Errdescription;


	case 0xE0000020:
		Errdescription = "ErrorCouplingNotAvailableInIEPEMode";
		return Errdescription;
	case 0xE0000021:
		Errdescription = "ErrorCouplingNotAvailableIn50ohmMode";
		return Errdescription;

	case 0xE0000022:
		Errdescription = "ErrorCouplingNotAvailableInIEPEMode ";
		return Errdescription;
	case 0xE0000023:
		Errdescription = "ErrorDeviceCommunicationFailed";
		return Errdescription;

	case 0xE0000024:
		Errdescription = "ErrorFixNumberConflict";
		return Errdescription;
	case 0xE0000025:
		Errdescription = "ErrorTrigSrcConflict";
		return Errdescription;

	case 0xE0000026:
		Errdescription = "ErrorPropAllFailed";
		return Errdescription;
	case 0xE0000027:
		Errdescription = "ErrorDeviceNotFusionable";
		return Errdescription;

	case 0xE0000028:
		Errdescription = "ErrorFileOpenFailed";
		return Errdescription;
	case 0xE0000029:
		Errdescription = "ErrorNotCompatible ";
		return Errdescription;

	case 0xE000FFFF:
		Errdescription = "ErrorUndefined";
		return Errdescription;
	}
	return Errdescription;



}
