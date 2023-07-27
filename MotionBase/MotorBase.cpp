#include "stdafx.h"
#include "MotorBase.h"
UINT CMotorBase::MotorProc( LPVOID pObj )
{
	CMotorBase *pObject = (CMotorBase*)pObj;

	HANDLE h[2];
	h[0] = pObject->m_hDead;
	h[1] = pObject->m_hBreak;

	bool bLoop = true;

	while(bLoop)
	{
		DWORD nEvent = WaitForMultipleObjects(2, h, FALSE, INFINITE) - WAIT_OBJECT_0;

		switch(nEvent)
		{
		case 0:
			bLoop = false;
			ResetEvent(pObject->m_hDead);
			break;

		case 1:
			try
			{
				if(pObject->IsMotorDataLoaded() == true)
				{
					if(pObject->IsMotorBusy() == true)
						pObject->MotorStop();
				}
			}
			catch(...)
			{
				return false;
			}
			

			break;
		}

		Sleep(50);
	}

	return 0;
}

CMotorBase::CMotorBase()
{
	_ASSERT_EXPR(FALSE, L"Don't Use Default Contractor");
}

CMotorBase::CMotorBase(HANDLE hBreak, BOOL bSelfStop)
{
	m_bDataLoaded = FALSE;
	m_bInitialed = FALSE;

	m_hDead = CreateEvent(NULL, TRUE, FALSE, NULL);
	m_hBreak = hBreak;

	m_MotorThd = AfxBeginThread(MotorProc, (LPVOID)this, THREAD_PRIORITY_NORMAL, 0, CREATE_SUSPENDED);
	m_MotorThd->m_bAutoDelete = FALSE;

	if(bSelfStop)
		m_MotorThd->ResumeThread();
	else
		m_MotorThd->SuspendThread();
}

CMotorBase::~CMotorBase()
{

}

bool CMotorBase::IsMotorDataLoaded()
{
	if(m_bDataLoaded == TRUE)
		return true;
	
	return false;
}

BOOL CMotorBase::DoEvents()
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

void CMotorBase::Delay(DWORD Msecs)
{
	DWORD dwBeginTime = ::GetTickCount();
	do{
		DoEvents();
		Sleep(1);
	} while ((::GetTickCount() - dwBeginTime) < Msecs);
}

