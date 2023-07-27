#pragma once

#include "WorkThread.h"
#include "LogMsg.h"


class AFX_EXT_CLASS LogClient
{
public:
	//連線到Log Server
	//ServerName必須和Log Server的相同
	bool Connect(IN CString csServerName);

	//輸出Log, Log表示一般訊息, Error/Warning表示錯誤/警告時發的訊息
	//LogIndex用來指定輸出的視窗,由0開始算
	void Message_Log(int nLogIndex, LPCTSTR lpszString, ...);
	void Message_Error(int nLogIndex, LPCTSTR lpszString, ...);
	void Message_Warning(int nLogIndex, LPCTSTR lpszString, ...);

private:
	CXQueue *m_pQueue;
	LogMsgList m_LogList;
	CTimerWorkThread *m_pThread;
	void MonitorThread();

public:
	LogClient(void);
	~LogClient(void);
};
