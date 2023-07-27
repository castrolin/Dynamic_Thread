#pragma once
#include "Component/XPGroupBox/XPGroupBox.h"
// CSystemTraceDlg 對話方塊
#define  TRACE_MESSAGE_MAX_NUM 1000

class CSystemTraceDlg : public CDialog
{
	DECLARE_DYNAMIC(CSystemTraceDlg)

public:
	CSystemTraceDlg(CWnd* pParent = NULL);   // 標準建構函式
	virtual ~CSystemTraceDlg();

	// 對話方塊資料
	enum { IDD = IDD_DIALOG_SYSTEM_TRACE };

private:
	CListCtrl m_pMessageList;

	CFont m_Font;

	CXPGroupBox m_GroupBox;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支援
	virtual BOOL OnInitDialog();
	BOOL PreTranslateMessage( MSG* pMsg );
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg long OnMessageUpdateTrace( WPARAM wparam, LPARAM lparam );
	afx_msg void OnBnClickedCancel();
};
