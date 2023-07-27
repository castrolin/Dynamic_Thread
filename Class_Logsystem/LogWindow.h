#pragma once

#include "afxwin.h"
#include "LogFile.h"
#include "WorkThread.h"


// CLogWindow 對話方塊

class CLogWindow : public CDialog
{
	DECLARE_DYNAMIC(CLogWindow)

public:
	CString GetName() { return _m_LogName; }
	CXListBox *m_pList;
	LogMsgList m_LogList;
	CCriticalSection m_CollectionLock;
	int _m_FileDay;

private:
	CLogFile _m_File;
	CString _m_LogName;
	CString _m_LogPath;
	CFont m_Font;
	bool m_bNoLog;
	void UpdateLog();

public:
	CLogWindow(IN CString csLogName, IN CString csLogPath, CWnd* pParent = NULL);   // 標準建構函式
	virtual ~CLogWindow();

// 對話方塊資料
	//enum { IDD = IDD_DIALOG_LOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支援

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnDestroy();
protected:
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
