#pragma once

#include "WorkThread.h"
#include "LogMsg.h"


class AFX_EXT_CLASS LogClient
{
public:
	//�s�u��Log Server
	//ServerName�����MLog Server���ۦP
	bool Connect(IN CString csServerName);

	//��XLog, Log��ܤ@��T��, Error/Warning��ܿ��~/ĵ�i�ɵo���T��
	//LogIndex�Ψӫ��w��X������,��0�}�l��
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
