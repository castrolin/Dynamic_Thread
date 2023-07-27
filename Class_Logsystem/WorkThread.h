//===================================================================
//  FILE:       WorkThread.h
//  DATE:       2008/10/27
//  COMMENTS:   需用new的方式產生thread
//  Modification History:
//  DATE         LEVEL NAME           COMMENT
//  -----------  ----  -------------  ---------------------------------------
//  2008/10/21   0.01  Ray Lin        Initial Release
//  2008/10/24   0.02  Ray Lin        實作基底類別(CWorkThread)與衍生類別(CTimerWorkThread)
//  2008/10/27   0.03  Ray Lin        實作衍生類別(CEventWorkThread)
//  2009/07/29   0.04  Rookers        實作衍生類別(CStaticTimerWorkThread)
//===================================================================

#if !defined(WORKTHREAD_H__A2E1B9A3_FA87_4091_A37E_6C0AAFDB255A)
#define WORKTHREAD_H__A2E1B9A3_FA87_4091_A37E_6C0AAFDB255A

#pragma once

/* 基底類別 :繼承需實作Start與Thread function */
class CWorkThread
{
public:
	//建立Thread並執行
	void Start();
	//暫停Thread
	void Pause()
	{
		if(_m_pThread)
		{
			_m_pThread->SuspendThread();
		}
	}
	//回復執行Thread
	void Resume()
	{
		if(_m_pThread)
		{
			while(_m_pThread->ResumeThread())
			{
				;
			}
		}
	}
	//結束Thread
	void Stop()
	{
		if(_m_pThread)
		{
			DWORD uExCode;

			::SetEvent(_m_hDeadEvent);
			while(_m_pThread->ResumeThread())
			{
				;
			}
			do 
			{
				::GetExitCodeThread(_m_pThread->m_hThread ,&uExCode);
				Sleep(100);
			}while(uExCode == STILL_ACTIVE);
			delete _m_pThread;
			_m_pThread = NULL;
			::CloseHandle(_m_hDeadEvent);
		}
	}

//JoeChou:
//protected:
public:
	CWinThread *_m_pThread;
	HANDLE _m_hDeadEvent;

public:
	CWorkThread() : _m_pThread(NULL), _m_hDeadEvent(NULL)
	{
	}
	~CWorkThread()
	{
		Stop();
	}
};

/* Timer功能用Thread來實現 */
class CTimerWorkThread : public CWorkThread
{
public:
	//建立Thread並執行
	//參數1:第2參數所在class
	//參數2:所要執行的函數
	//參數3:呼叫函數的間隔時間(ms)
	template <class T> void Start(T* ptr, void (T::*func)(), DWORD nInterval = 1000)
	{
		ThreadData<T> threaddata;

		if(_m_pThread)
		{
			return;
		}
		threaddata.pThreadObject = ptr;
		threaddata.pThreadFunc = func;
		threaddata.nInterval = nInterval;
		threaddata.hDeadEvent = ::CreateEvent(NULL, TRUE, FALSE, NULL);
		threaddata.hArchiveEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
		_m_hDeadEvent = threaddata.hDeadEvent;
		_m_pThread = ::AfxBeginThread((AFX_THREADPROC)ThreadData<T>::_ThreadFunc, &threaddata, THREAD_PRIORITY_NORMAL, 0, CREATE_SUSPENDED);
		_m_pThread->m_bAutoDelete = FALSE;
		_m_pThread->ResumeThread();
		WaitForSingleObject(threaddata.hArchiveEvent,INFINITE);
		::CloseHandle(threaddata.hArchiveEvent);
		return;
	}

private:
	template <class T> struct ThreadData
	{
		typedef void (T::*TFunc)();
		T* pThreadObject;
		TFunc pThreadFunc;
		DWORD nInterval;
		HANDLE hArchiveEvent;
		HANDLE hDeadEvent;
		static UINT _ThreadFunc(ThreadData<T>* pThis)
		{
			//保存資料
			ThreadData<T> threaddata = *pThis;
			SetEvent(threaddata.hArchiveEvent);
			while(!WaitForSingleObject(threaddata.hDeadEvent, threaddata.nInterval) == WAIT_OBJECT_0)
			{
				((*(threaddata.pThreadObject)).*(threaddata.pThreadFunc))();
			}
			TRACE1("Thread [%s] Exit!\n", __FUNCTION__);

			return 0;
		}
	};
};

/* 靜態函示Thread 功能用Timer Thread來實現， */
class CStaticTimerWorkThread : public CWorkThread
{
public:
	//建立Thread並執行
	//參數1:第2參數所在class
	//參數2:所要執行的函數
	//參數3:呼叫函數的間隔時間(ms)
	void Start( void (*func)(), DWORD nInterval = 1000)
	{
		ThreadData threaddata;

		if(_m_pThread)
		{
			return;
		}
		threaddata.pThreadFunc = func;
		threaddata.nInterval = nInterval;
		threaddata.hDeadEvent = ::CreateEvent(NULL, TRUE, FALSE, NULL);
		threaddata.hArchiveEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
		_m_hDeadEvent = threaddata.hDeadEvent;
		_m_pThread = ::AfxBeginThread((AFX_THREADPROC)ThreadData::_ThreadFunc, &threaddata, THREAD_PRIORITY_NORMAL, 0, CREATE_SUSPENDED);
		_m_pThread->m_bAutoDelete = FALSE;
		_m_pThread->ResumeThread();
		WaitForSingleObject(threaddata.hArchiveEvent,INFINITE);
		::CloseHandle(threaddata.hArchiveEvent);
		return;
	}

private:
	struct ThreadData
	{
		typedef void (*TFunc)();
		TFunc pThreadFunc;
		DWORD nInterval;
		HANDLE hArchiveEvent;
		HANDLE hDeadEvent;
		static UINT _ThreadFunc(ThreadData* pThis)
		{
			//保存資料
			ThreadData threaddata = *pThis;
			SetEvent(threaddata.hArchiveEvent);
			while(!WaitForSingleObject(threaddata.hDeadEvent, threaddata.nInterval) == WAIT_OBJECT_0)
			{
				(*threaddata.pThreadFunc)();
			}
			TRACE1("Thread [%s] Exit!\n", __FUNCTION__);

			return 0;
		}
	};
};

/* 多個函數用Thread來實現,一次只能執行1個函數 */
class CEventWorkThread : public CWorkThread
{
public:
	//建立Thread並執行
	//參數1:第2參數所在class
	//參數2:所要執行的函數
	//參數3:Event數量
	template <class T> void Start(T* ptr, void (T::*func)(), int nEventCount)
	{
		ThreadData<T> threaddata;

		if(_m_pThread || nEventCount <=0)
		{
			return;
		}
		if(nEventCount >= MAXIMUM_WAIT_OBJECTS)
		{
			TRACE("Too many events!!\n");
			return;
		}
		_m_nEventCount = nEventCount;
		threaddata.pThreadObject = ptr;
		threaddata.pThreadFunc = func;
		threaddata.nEventCount = nEventCount;
		threaddata.pHandleArray = new HANDLE[nEventCount];
		::ZeroMemory(threaddata.pHandleArray, sizeof(threaddata.pHandleArray));
		_m_pHandleArray = new HANDLE[nEventCount];
		::ZeroMemory(_m_pHandleArray, sizeof(_m_pHandleArray));
		for(int i=0; i<nEventCount; i++)
		{
			threaddata.pHandleArray[i] = ::CreateEvent(NULL, TRUE, FALSE, NULL);
			_m_pHandleArray[i] = threaddata.pHandleArray[i];
		}
		threaddata.hDeadEvent = ::CreateEvent(NULL, TRUE, FALSE, NULL);
		threaddata.hArchiveEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
		_m_hDeadEvent = threaddata.hDeadEvent;
		_m_pThread = ::AfxBeginThread((AFX_THREADPROC)ThreadData<T>::_ThreadFunc, &threaddata, THREAD_PRIORITY_NORMAL, 0, CREATE_SUSPENDED);
		_m_pThread->m_bAutoDelete = FALSE;
		_m_pThread->ResumeThread();
		WaitForSingleObject(threaddata.hArchiveEvent,INFINITE);
		::CloseHandle(threaddata.hArchiveEvent);
		return;
	}
	//觸發事件
	void Trigger(int nEvent)
	{
		if(_m_pThread)
		{
			if(nEvent < _m_nEventCount)
			{
				::SetEvent(_m_pHandleArray[nEvent]);
			}
		}
	}
	//等待事件發生
	int WaitEvent()
	{
		DWORD ret = WaitForMultipleObjects(_m_nEventCount, _m_pHandleArray, FALSE, 0);
		for(int i=0; i<_m_nEventCount; i++)
		{
			::ResetEvent(_m_pHandleArray[i]);
		}
		return ret -= WAIT_OBJECT_0;
	}
	void Stop()
	{
		CWorkThread::Stop();
		if(_m_pHandleArray)
		{
			for(int i=0; i<_m_nEventCount; i++)
			{
				::CloseHandle(_m_pHandleArray[i]);
				_m_pHandleArray[i] = NULL;
			}
			delete [] _m_pHandleArray;
			_m_pHandleArray = NULL;
		}
	}

private:
	template <class T> struct ThreadData
	{
		typedef void (T::*TFunc)();
		T* pThreadObject;
		TFunc pThreadFunc;
		HANDLE* pHandleArray;
		int nEventCount;
		HANDLE hArchiveEvent;
		HANDLE hDeadEvent;
		static UINT _ThreadFunc(ThreadData<T>* pThis)
		{
			ThreadData<T> threaddata = *pThis;
			int ret = 0;
			HANDLE* pHandle = NULL;
			int nEventCount = 0;

			nEventCount = threaddata.nEventCount+1;
			pHandle = new HANDLE[nEventCount];
			::ZeroMemory(pHandle, sizeof(pHandle));
			pHandle[0] = threaddata.hDeadEvent;
			for(int i=1; i<nEventCount; i++)
			{
				pHandle[i] = threaddata.pHandleArray[i-1];
			}
			SetEvent(threaddata.hArchiveEvent);
			while(true)
			{
				ret = WaitForMultipleObjects(nEventCount, pHandle, FALSE, INFINITE);
				ret -= WAIT_OBJECT_0;
				if(ret >=0 && ret<nEventCount)
				{
					//有Event發生
					if(ret == 0)
					{
						break;
					}
					((*(threaddata.pThreadObject)).*(threaddata.pThreadFunc))();
				}
			}
			delete [] pHandle;
			delete [] threaddata.pHandleArray;
			TRACE1("Thread [%s] Exit!\n", __FUNCTION__);

			return 0;
		}
		ThreadData()
		{
			pThreadObject = NULL;
			pThreadFunc = NULL;
			pHandleArray = NULL;
			hArchiveEvent = NULL;
			hDeadEvent = NULL;
		}
	};

private:
	int _m_nEventCount;
	HANDLE* _m_pHandleArray;

public:
	CEventWorkThread()
	{
		_m_nEventCount = 0;
		_m_pHandleArray = NULL;
	}
	~CEventWorkThread()
	{
		if(_m_pHandleArray)
		{
			for(int i=0; i<_m_nEventCount; i++)
			{
				::CloseHandle(_m_pHandleArray[i]);
				_m_pHandleArray[i] = NULL;
			}
			delete [] _m_pHandleArray;
			_m_pHandleArray = NULL;
		}
	}
};

#endif // WORKTHREAD_H__A2E1B9A3_FA87_4091_A37E_6C0AAFDB255A
