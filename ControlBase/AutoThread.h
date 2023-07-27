
#pragma once


class CAutoThread
{

public:
	CAutoThread();          
	~CAutoThread();

private:

	CString ErrorDescription;
	UINT m_uReturnTool;
	UINT m_Step;

	UINT m_CurrentRBStep;
	UINT m_CurrentCVStep;
	UINT m_CurrentPCBStep;

	UINT m_CurrentStep;


	BOOL m_Exist_CV;
	BOOL m_Exist_RB;
	BOOL m_Exist_Sticker;
	BOOL m_REQ_CV_STOP;

	PRODUCT_PRODUCT_STATUS m_ProductStatus_CV;

public:
	

	BOOL Initial();

	void ThreadInitial();

	BOOL bReAuto;
	//Main Thread
	CWinThread *m_ProcessThread;
	static UINT MainProc(LPVOID Info);

	CWinThread *m_DetectThread;
	static UINT DetectProc(LPVOID Info);

	// Main Controll Process and Detection
	CWinThread *m_MainTread;
	static UINT MainThread(LPVOID Info);


	UINT CheckProcessing();
	UINT CheckError();

	BOOL EndProcess();

	//Add the wait thread in order to judge the action (does it continue)
	BOOL ToolThreadExecute(UINT Step, UINT ToolName, BOOL bWait = TRUE, DWORD Timeout = 30000);

};
