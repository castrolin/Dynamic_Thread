#pragma once

#include "WorkThread.h"
#include "LogMainWindow.h"


class AFX_EXT_CLASS LogServer
{
public:
	//建立Log Server
	//ServerName = 雙方識別的名稱
	//LogPath = Log path
	//LogWndNum = 總共有幾個Log Window
	bool Create(IN CString csServerName, IN CString csLogPath, IN int nLogWndNum);

	//啟動服務
	void Start();

	//關閉服務
	void Stop();

	//暫停服務
	void Pause();

	//設定父視窗,Log視窗的停佇位置
	void SetParent(IN CWnd *pParent);

	//新增Log視窗
	//Name = Log檔案名稱(Path+Name_流水號.txt)
	//Title = Log視窗標題
	bool AddLogWindow(IN CString csName, IN CString csTitle);

	//顯示或隱藏Log視窗
	void ShowLogWindow(IN bool bShow);

	//設定Log視窗位置
	void SetLogWindowPos(IN int nX, IN int nY, IN int nWidth, IN int nHeight);

	void SetLogWindowPage(UINT Index);

	void ClearLogWindowPage(UINT Index);
	

private:
	static const int BUFFER_SIZE = 100*1024;
	bool CreateMainWindow();
	CXQueue *m_pQueue;
	CLogMainWindow *m_pMainWindow;
	CObArray m_LogArray;
	CString m_csLogPath;
	int m_nIndex;
	int m_nTotalCount;
	CWnd *m_pParentWindow;
	//thread
	CTimerWorkThread *m_pThread;
	void MonitorThread();

public:
	LogServer(CWnd *pParent);
	~LogServer(void);
};
