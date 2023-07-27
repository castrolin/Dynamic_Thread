#pragma once
#include "SystemParams.h"
#include "MaintainPageLevelCheckDlg.h"

// CMaintainPageDlg 對話方塊

class CMaintainPageDlg : public CDialog
{
	DECLARE_DYNAMIC(CMaintainPageDlg)

public:
	CMaintainPageDlg(CSystemParams *SystemParams, CWnd* pParent = NULL);   // 標準建構函式
	virtual ~CMaintainPageDlg();

// 對話方塊資料
	enum { IDD = IDD_DIALOG_OPTION_MAINTAIN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支援
	virtual BOOL OnInitDialog();
	BOOL PreTranslateMessage( MSG* pMsg );
	DECLARE_MESSAGE_MAP()

	CString m_sTimeStr;
	CSystemParams *m_SystemParams;

	
	CMaintainPageLevelCheckDlg m_MaintainPageLevelCheckDlg;

public:
	afx_msg void OnPaint();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnBnClickedButtonExitOptionDlg();
};
