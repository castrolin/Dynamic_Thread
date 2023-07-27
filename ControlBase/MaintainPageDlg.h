#pragma once
#include "SystemParams.h"
#include "MaintainPageLevelCheckDlg.h"

// CMaintainPageDlg ��ܤ��

class CMaintainPageDlg : public CDialog
{
	DECLARE_DYNAMIC(CMaintainPageDlg)

public:
	CMaintainPageDlg(CSystemParams *SystemParams, CWnd* pParent = NULL);   // �зǫغc�禡
	virtual ~CMaintainPageDlg();

// ��ܤ�����
	enum { IDD = IDD_DIALOG_OPTION_MAINTAIN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �䴩
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
