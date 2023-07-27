#pragma once

class LogMsg
{
public:
	void SetMessageID(int nID) { _m_nMsgID = nID; }
	void SetMessage(CString msg) { _m_Message = msg; }
	bool IsError();
	bool IsWarning();
	CString GetMessage() { return _m_Message; }
	int GetMessageID();

private:
	int _m_nMsgID;
	CString _m_Message;

public:
	LogMsg();
	~LogMsg();
};

typedef CList<LogMsg, LogMsg&> LogMsgList;
