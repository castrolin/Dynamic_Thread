#ifndef _CONTROLTHREAD_H_
#define _CONTROLTHREAD_H_
#pragma once

class ControlThread : public CWinThread{
	
	DECLARE_DYNCREATE(ControlThread)

public://Override "protected constructor used by dynamic creation" by public keyword.
	
	ControlThread();           
	virtual ~ControlThread();

public:

	virtual BOOL InitInstance();
	virtual void ExecuteInside();///¤l¥NOverride¤§Method
	void	Start();
	void	Stop();
    void SetObj(void* aObj){m_Obj=aObj;};
	HANDLE GetDeadHandle() const{return  ThreadDead;};
    bool SetName(LPCTSTR str);
    LPCSTR GetName() const ;

protected:
	void* m_Obj;
	HANDLE	ThreadDead;			//This is singleton just before termination of thread.		
	bool	m_Running;
    CString m_Name ;

protected:	
	DECLARE_MESSAGE_MAP()
};

#endif
