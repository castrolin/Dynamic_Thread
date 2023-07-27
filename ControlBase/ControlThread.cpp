#include "stdafx.h"
#include "ControlThread.h"

IMPLEMENT_DYNCREATE(ControlThread, CWinThread)

ControlThread::ControlThread()
{	
	ThreadDead	= CreateEvent( NULL, TRUE, FALSE, NULL );	//Manual-reset, non-signaled.
	m_bAutoDelete	= FALSE;	
	m_Running = false;

}

ControlThread::~ControlThread()
{
	DWORD uExCode;
	while(ResumeThread())
	{
		;
	}

	SetEvent(ThreadDead);
	
	do 
	{
		GetExitCodeThread(m_hThread ,&uExCode);
		Sleep(20);

	}while(uExCode == STILL_ACTIVE);

	CloseHandle( ThreadDead );	

}

BOOL ControlThread::InitInstance()
{	
	DWORD result;
	bool looping = true;
	while( looping == true )
	{
		result = WaitForSingleObject( ThreadDead, 200 );
		if( result == WAIT_OBJECT_0 )
			break;
		
		ExecuteInside();		
	}
	SetEvent( ThreadDead );
	return FALSE;
}

void ControlThread::Start()
{
	if( m_Running == true )
		return;
	
	ResetEvent(ThreadDead);
	CreateThread( CREATE_SUSPENDED );
	SetThreadPriority( THREAD_PRIORITY_NORMAL );
	ResumeThread();	
	
	m_Running = true;
}

void ControlThread::Stop()
{
	ResetEvent(ThreadDead ) ;
	Sleep(20) ;
	SetEvent( ThreadDead );
}

bool ControlThread::SetName(LPCTSTR str)
{
	m_Name.Format("%s" , str) ;
	m_Name.Trim();
	if (m_Name.IsEmpty())
	{
		return false ;
	}
	else
	{
		return true ;
	}
}

LPCTSTR ControlThread::GetName()const
{
	return static_cast<LPCTSTR>(m_Name) ;
}

//¤l¥NOverride¤§Method
void ControlThread::ExecuteInside()
{
    Sleep(100);
	return;
}

BEGIN_MESSAGE_MAP(ControlThread, CWinThread)
END_MESSAGE_MAP()