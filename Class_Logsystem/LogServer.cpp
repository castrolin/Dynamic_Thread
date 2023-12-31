#include "StdAfx.h"
#include ".\logserver.h"
#include "LogWindow.h"


LogServer::LogServer(CWnd *pParent)
{
	m_pQueue = NULL;
	m_pThread = NULL;
	m_nIndex = 0;
	m_nTotalCount = 0;
	m_pMainWindow = NULL;
	m_pParentWindow = pParent;
	m_LogArray.RemoveAll();
}

LogServer::~LogServer(void)
{
	Stop();
	if(m_pQueue)
	{
		m_pQueue->Close();
		delete m_pQueue;
		m_pQueue = NULL;
	}
	//給MAIN_Tab去解構
	//for(int i=0; i<m_LogArray.GetCount(); i++)
	//{
	//	CLogWindow *pLogWindow = DYNAMIC_DOWNCAST(CLogWindow, m_LogArray.GetAt(i));
	//	if(pLogWindow)
	//	{
	//		pLogWindow->DestroyWindow();
	//		delete pLogWindow;
	//		pLogWindow = NULL;
	//	}
	//}
	m_LogArray.RemoveAll();
	if(m_pMainWindow)
	{
		m_pMainWindow->DestroyWindow();
		delete m_pMainWindow;
		m_pMainWindow = NULL;
	}
	m_pParentWindow = NULL;
}

bool LogServer::Create(IN CString csServerName, IN CString csLogPath, IN int nLogWndNum)
{
	m_nTotalCount = nLogWndNum;
	m_csLogPath = csLogPath;
	m_pQueue = new CXQueue();
	LONG lRet = m_pQueue->Create(csServerName, 1024, 1024);
	return (lRet == XQUEUE_ERROR_SUCCESS) ? true:false;
}

void LogServer::Start()
{
	if(m_pThread)
	{
		Stop();
		return;
	}
	//啟動Thread
	m_pThread = new CTimerWorkThread();
	m_pThread->Start(this, &LogServer::MonitorThread, 10);
}

void LogServer::Stop()
{
	if(m_pThread)
	{
		delete m_pThread;
		m_pThread = NULL;
	}
}

void LogServer::Pause()
{
	m_pThread->Pause();
}

void LogServer::MonitorThread()
{
	TCHAR buf[BUFFER_SIZE] = { _T('\0') };
	LONG lRet;
	size_t nSize = 0;
	size_t nMessageId = 0;
	DWORD nThreadID = 0;
	XQUEUE_VARIABLE_BLOCK *pVB = m_pQueue->GetVariableBlock();
	ASSERT(pVB);

	if (pVB->UsedDataBlocks == 0)
	{
		lRet = m_pQueue->WaitForQueueWrite(100);
	}
	//取得Message size
	lRet = m_pQueue->Read(NULL, &nSize, 10);
	if (lRet == XQUEUE_ERROR_SUCCESS)
	{
		ASSERT(nSize < (BUFFER_SIZE * sizeof(TCHAR)));
		nSize = sizeof(buf) - 2;
		lRet = m_pQueue->Read((LPBYTE)buf, &nSize, &nMessageId, &nThreadID, 10);
		if (lRet == XQUEUE_ERROR_SUCCESS)
		{
			LogMsg logmsg;

			logmsg.SetMessageID(static_cast<int>(nMessageId));
			if(logmsg.GetMessageID()+1 > m_nTotalCount)
			{
				return;
			}
			CLogWindow *pLogWindow = DYNAMIC_DOWNCAST(CLogWindow, m_LogArray[logmsg.GetMessageID()]);
			if(pLogWindow)
			{
				logmsg.SetMessage(buf);
				CSingleLock slock(&pLogWindow->m_CollectionLock);
				slock.Lock();
				pLogWindow->m_LogList.AddTail(logmsg);
				slock.Unlock();
				pLogWindow->PostMessage(WM_COMMAND, WM_UPDATE_LOG, 0);

				if(logmsg.IsError() || logmsg.IsWarning())
				{
					int Index = logmsg.GetMessageID();
					SetLogWindowPage(logmsg.GetMessageID());
				}
			}
		}
	}
}

bool LogServer::CreateMainWindow()
{
	m_pMainWindow = new CLogMainWindow();
	if(m_pMainWindow->Create(IDD_DIALOG_CONTAINER, m_pParentWindow))
	{
 		//m_pMainWindow->ShowWindow(SW_HIDE);
		return TRUE;
	}

	return false;
}

bool LogServer::AddLogWindow(IN CString csName, IN CString csTitle)
{
	CLogWindow *pLogWnd = NULL;

	if(m_nIndex >= m_nTotalCount)
	{
		return false;
	}
	if(m_nIndex == 0)
	{
		if(!CreateMainWindow())
		{
			return false;
		}
	}
	pLogWnd = new CLogWindow(csName, m_csLogPath);
	m_LogArray.Add(pLogWnd);
	m_pMainWindow->m_Tab.InsertItem(m_nIndex, csTitle);
	m_nIndex++;
	if(m_nIndex == m_nTotalCount)
	{
		m_pMainWindow->m_Tab.SetTabPage(&m_LogArray, IDD_DIALOG_LOG, m_nTotalCount);
	}

	return true;
}

void LogServer::SetLogWindowPage(UINT Index)
{
	m_pMainWindow->m_Tab.SetTabSelect(Index);
}

void LogServer::ClearLogWindowPage( UINT Index )
{
	CLogWindow *pLogWindow = DYNAMIC_DOWNCAST(CLogWindow, m_LogArray[Index]);
	if(pLogWindow)
	{
		pLogWindow->m_pList->ResetContent();
	}
}

void LogServer::SetParent(IN CWnd *pParent)
{
	if(pParent)
	{
		m_pParentWindow = pParent;
 		m_pMainWindow->ModifyStyle(WS_CAPTION, 0, SWP_FRAMECHANGED);
		m_pMainWindow->SetParent(m_pParentWindow);
	}
	else
	{
		m_pMainWindow->ModifyStyle(0, WS_CAPTION, SWP_FRAMECHANGED);
		m_pMainWindow->SetParent(NULL);
	}
}

void LogServer::ShowLogWindow(IN bool bShow)
{
	if(bShow)
	{
		m_pMainWindow->ShowWindow(SW_SHOW);
	}
	else
	{
		m_pMainWindow->ShowWindow(SW_HIDE);
	}
}

void LogServer::SetLogWindowPos(IN int nX, IN int nY, IN int nWidth, IN int nHeight)
{
	m_pMainWindow->ShowWindow(SW_HIDE);
	m_pMainWindow->SetWindowPos(&CWnd::wndTop, nX, nY, nWidth, nHeight, SWP_HIDEWINDOW);
	m_pMainWindow->m_Tab.SetWindowPos(&CWnd::wndTop, 0, 0, nWidth-10, nHeight-10, SWP_SHOWWINDOW);
	m_pMainWindow->m_Tab.SetRectangle();
	m_pMainWindow->ShowWindow(SW_SHOW);
}

