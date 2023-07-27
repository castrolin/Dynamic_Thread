#include "StdAfx.h"
#include ".\logclient.h"

#pragma warning(disable : 4996)	// disable bogus deprecation warning

CCriticalSection m_critSect ;
LogClient::LogClient(void)
{
	m_pQueue = NULL;
	m_pThread = NULL;
	m_LogList.RemoveAll();
}

LogClient::~LogClient(void)
{
	if(m_pThread)
	{
		delete m_pThread;
		m_pThread = NULL;
	}
	if(m_pQueue)
	{
		delete m_pQueue;
		m_pQueue = NULL;
	}
	m_LogList.RemoveAll();
}

bool LogClient::Connect(IN CString csServerName)
{
	LONG lRet = -1;

	//Init Client Message Queue
	m_pQueue = new CXQueue();
	ASSERT(m_pQueue);
	// try to open server
	for (int i = 0; i < 3; i++)
	{
		lRet = m_pQueue->Open(csServerName);
		if (lRet == XQUEUE_ERROR_SUCCESS)
		{
			break;
		}
	}
	//±Ò°ÊThread
	m_pThread = new CTimerWorkThread();
	m_pThread->Start(this, &LogClient::MonitorThread, 100);

	return (lRet == XQUEUE_ERROR_SUCCESS ? true:false);
}

void LogClient::Message_Log(int nLogIndex, LPCTSTR lpszString, ...)
{
	char vbuf[4096];
	va_list marker;
	CString csMsg;
	CTime ctTime = CTime::GetCurrentTime();
	LogMsg logmsg;

	if(m_pQueue == NULL)
	{
		return;
	}
	if(!m_pQueue->IsOpen())
	{
		return;
	}
	va_start(marker, lpszString);
	ZeroMemory(vbuf, sizeof(vbuf));
	vsprintf(vbuf, lpszString, marker);
	va_end(marker);
	csMsg.Format("%04d/%02d/%02d %02d:%02d:%02d    %s", 
		ctTime.GetYear(), ctTime.GetMonth(), 
		ctTime.GetDay(), ctTime.GetHour(), 
		ctTime.GetMinute(), ctTime.GetSecond(), vbuf);
	logmsg.SetMessageID(nLogIndex);
	logmsg.SetMessage(csMsg);

	{
		CSingleLock singlelock(&m_critSect) ;
		singlelock.Lock() ;

		m_LogList.AddTail(logmsg);

		singlelock.Unlock() ;
	}
	
}

void LogClient::Message_Error(int nLogIndex, LPCTSTR lpszString, ...)
{
	char vbuf[4096];
	va_list marker;
	CString csMsg;
	CTime ctTime = CTime::GetCurrentTime();
	LogMsg logmsg;

	if(m_pQueue == NULL)
	{
		return;
	}
	if(!m_pQueue->IsOpen())
	{
		return;
	}
	va_start(marker, lpszString);
	ZeroMemory(vbuf, sizeof(vbuf));
	vsprintf(vbuf, lpszString, marker);
	va_end(marker);
	csMsg.Format("%04d/%02d/%02d %02d:%02d:%02d    %s", 
		ctTime.GetYear(), ctTime.GetMonth(), 
		ctTime.GetDay(), ctTime.GetHour(), 
		ctTime.GetMinute(), ctTime.GetSecond(), vbuf);
	logmsg.SetMessageID(nLogIndex+ERROR_FLAG);
	logmsg.SetMessage(csMsg);

	{
		CSingleLock singlelock(&m_critSect) ;
		singlelock.Lock() ;

		m_LogList.AddTail(logmsg);

		singlelock.Unlock() ;
	}
}

void LogClient::Message_Warning(int nLogIndex, LPCTSTR lpszString, ...)
{
	char vbuf[4096];
	va_list marker;
	CString csMsg;
	CTime ctTime = CTime::GetCurrentTime();
	LogMsg logmsg;

	if(m_pQueue == NULL)
	{
		return;
	}
	if(!m_pQueue->IsOpen())
	{
		return;
	}
	va_start(marker, lpszString);
	ZeroMemory(vbuf, sizeof(vbuf));
	vsprintf(vbuf, lpszString, marker);
	va_end(marker);
	csMsg.Format("%04d/%02d/%02d %02d:%02d:%02d    %s", 
		ctTime.GetYear(), ctTime.GetMonth(), 
		ctTime.GetDay(), ctTime.GetHour(), 
		ctTime.GetMinute(), ctTime.GetSecond(), vbuf);
	logmsg.SetMessageID(nLogIndex+WARNING_FLAG);
	logmsg.SetMessage(csMsg);
	{
		CSingleLock singlelock(&m_critSect) ;
		singlelock.Lock() ;

		m_LogList.AddTail(logmsg);

		singlelock.Unlock() ;
	}
}

void LogClient::MonitorThread()
{
	if(m_pQueue == NULL)
	{
		return;
	}
	if(!m_pQueue->IsOpen())
	{
		return;
	}
	while(m_LogList.GetCount())
	{
		LogMsg logmsg;

		{
			CSingleLock singlelock(&m_critSect) ;
			singlelock.Lock() ;

			logmsg = m_LogList.RemoveHead();

			singlelock.Unlock() ;
		}

		if(logmsg.IsError())
		{
			m_pQueue->Log(logmsg.GetMessageID()+ERROR_FLAG, logmsg.GetMessage());
		}
		else if(logmsg.IsWarning())
		{
			m_pQueue->Log(logmsg.GetMessageID()+WARNING_FLAG, logmsg.GetMessage());
		}
		else
		{
			m_pQueue->Log(logmsg.GetMessageID(), logmsg.GetMessage());
		}
	}
}
