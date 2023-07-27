#include "StdAfx.h"
#include "LogMsg.h"


LogMsg::LogMsg()
{
	_m_nMsgID = -1;
	_m_Message.Empty();
}

LogMsg::~LogMsg()
{
}

bool LogMsg::IsError()
{
	if(_m_nMsgID & ERROR_FLAG)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool LogMsg::IsWarning()
{
	if(_m_nMsgID & WARNING_FLAG)
	{
		return true;
	}
	else
	{
		return false;
	}
}

int LogMsg::GetMessageID()
{
	return _m_nMsgID & 0xff;
}
