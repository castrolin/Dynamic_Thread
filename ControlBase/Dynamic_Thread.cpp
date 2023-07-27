#include "stdafx.h"
#include "Dynamic_Thread.h"

BOOL Test_Function();
BOOL Test_Function_second();
BOOL Test_Function_third();

CDynamic_Thread::CDynamic_Thread()
{
	m_FirstThread = AfxBeginThread(FirstThread, (LPVOID)this, THREAD_PRIORITY_NORMAL,0, CREATE_SUSPENDED);
	m_FirstThread->ResumeThread();
	
	m_SceondThread = AfxBeginThread(SecondThread, (LPVOID)this, THREAD_PRIORITY_NORMAL,0, CREATE_SUSPENDED);
	m_SceondThread->ResumeThread();

	m_ThirdThread = AfxBeginThread(ThirdThread, (LPVOID)this, THREAD_PRIORITY_NORMAL,0, CREATE_SUSPENDED);
	m_ThirdThread->ResumeThread();


	
}

CDynamic_Thread::~CDynamic_Thread()
{
	LOG->Message_Error(Log_Main, "Thread is stopping now!");
}

UINT CDynamic_Thread::FirstThread(LPVOID Info)
{
	CDynamic_Thread* this_obj = (CDynamic_Thread*) Info;

	CThread_Object* TT = new CThread_Object(Test_Function);
	CThread_Object* TTwo = new CThread_Object(Test_Function_second);
	CThread_Object* TThird = new CThread_Object(Test_Function_third);

	TT->Create_Thread();
	TTwo->Create_Thread();
	TThird->Create_Thread();

	bool bLoop = true;
	while(bLoop)
	{
		if(this_obj->bThreadStart == TRUE)
		{
			TT->Start_Thread();
			TTwo->Start_Thread();
			TThird->Start_Thread();
			this_obj->bThreadStart = FALSE;
			//bLoop = FALSE;
			Sleep(5000);
		}
		if(this_obj->bThreadStart == FALSE)
		{
			TT->Create_Thread();
			TTwo->Create_Thread();
			TThird->Create_Thread();
		}

		
	}
	return 0;
}

UINT CDynamic_Thread::SecondThread(LPVOID Info)
{
	CDynamic_Thread* this_obj = (CDynamic_Thread*) Info;
	
	return 0;
}

UINT CDynamic_Thread::ThirdThread(LPVOID Info)
{
	CDynamic_Thread* this_obj = (CDynamic_Thread*) Info;
	return 0;
}

CThread_Object::CThread_Object(BOOL(*pFunc)())
{
	m_ThreadFunction = pFunc;
	bStart = FALSE;
	bStop = FALSE;
	bEnd = FALSE;
}

CThread_Object::~CThread_Object()
{

}

UINT CThread_Object::Create_Thread()
{
	CWinThread* mSubThread;
	mSubThread = AfxBeginThread(Obj_Thread, (LPVOID)this, THREAD_PRIORITY_NORMAL,0, CREATE_SUSPENDED);
	m_Thread = *&mSubThread;
	return 0;
}

UINT CThread_Object::Obj_Thread(LPVOID info)
{
	CThread_Object* this_obj = (CThread_Object*) info;
	DWORD exit_code= NULL;
	bool bLoop = true;
	while(bLoop)
	{
		if(this_obj->bStart == TRUE)
		{
			//Function
			TRACE("The Obj_Thread For TT is doing_Now \n");
			if(this_obj->m_ThreadFunction() == TRUE)
			{
				this_obj->End_Thread();
				continue;
			}
		}

		if(this_obj->bEnd == TRUE)
			bLoop = false;

	}
	return 0;
}


BOOL CThread_Object::Start_Thread()
{	
	
	bStart = TRUE;
	bStop = FALSE;
	bEnd = FALSE;

	m_Thread->ResumeThread();

	return FALSE;
}

BOOL CThread_Object::Stop_Thread()
{
	bStop = TRUE;
	bStart = FALSE;
	bEnd = FALSE;

	m_Thread->SuspendThread();

	return FALSE;
}

BOOL CThread_Object::End_Thread()
{
	bStart = FALSE;
	bStop = FALSE;
	bEnd = TRUE;

	if(bEnd = TRUE)
		return TRUE;

	return FALSE;
}

/********************TEST FUNCTION************************/
BOOL Test_Function()
{
	TRACE("The Test_Function Is executing \n");
	return TRUE;

}
BOOL Test_Function_second()
{
	TRACE("The Test_Function_second Is executing \n");
	return TRUE;

}
BOOL Test_Function_third()
{
	TRACE("The Test_Function_third Is executing \n");
	return TRUE;

}