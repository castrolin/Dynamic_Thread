#pragma once

#include "WorkThread.h"
#include "LogMainWindow.h"


class AFX_EXT_CLASS LogServer
{
public:
	//�إ�Log Server
	//ServerName = �����ѧO���W��
	//LogPath = Log path
	//LogWndNum = �`�@���X��Log Window
	bool Create(IN CString csServerName, IN CString csLogPath, IN int nLogWndNum);

	//�ҰʪA��
	void Start();

	//�����A��
	void Stop();

	//�Ȱ��A��
	void Pause();

	//�]�w������,Log�����������m
	void SetParent(IN CWnd *pParent);

	//�s�WLog����
	//Name = Log�ɮצW��(Path+Name_�y����.txt)
	//Title = Log�������D
	bool AddLogWindow(IN CString csName, IN CString csTitle);

	//��ܩ�����Log����
	void ShowLogWindow(IN bool bShow);

	//�]�wLog������m
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