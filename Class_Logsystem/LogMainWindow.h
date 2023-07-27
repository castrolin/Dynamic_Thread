#pragma once

#include "afxcmn.h"
#include "MAIN_Tab.h"


// CLogMainWindow 對話方塊

class CLogMainWindow : public CDialog
{
	DECLARE_DYNAMIC(CLogMainWindow)

public:
	CMAIN_Tab m_Tab;

public:
	CLogMainWindow(CWnd* pParent = NULL);   // 標準建構函式
	virtual ~CLogMainWindow();

// 對話方塊資料
// 	enum { IDD = IDD_DIALOG_CONTAINER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支援

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
