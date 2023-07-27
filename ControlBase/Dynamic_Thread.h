#pragma once

class CDynamic_Thread
{
	
public:
	CDynamic_Thread();
	~CDynamic_Thread();


	CWinThread *m_FirstThread;
	static UINT FirstThread(LPVOID Info);

	CWinThread *m_SceondThread;
	static UINT SecondThread(LPVOID Info);

	CWinThread *m_ThirdThread;
	static UINT ThirdThread(LPVOID Info);

	BOOL bThreadStart;
};

class CThread_Object
{
private:
	CWinThread* m_Thread;
	static UINT Obj_Thread(LPVOID info);

	//CallBack Function for the Thread Excute
	BOOL (*m_ThreadFunction)();

	BOOL bStart;
	BOOL bStop;
	BOOL bEnd ;

public:
	CThread_Object(BOOL(*pFunc)());
	~CThread_Object();

	UINT Create_Thread();
	BOOL Start_Thread();
	BOOL Stop_Thread();
	BOOL End_Thread();
};