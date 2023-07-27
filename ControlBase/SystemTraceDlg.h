#pragma once
#include "Component/XPGroupBox/XPGroupBox.h"
// CSystemTraceDlg ��ܤ��
#define  TRACE_MESSAGE_MAX_NUM 1000

class CSystemTraceDlg : public CDialog
{
	DECLARE_DYNAMIC(CSystemTraceDlg)

public:
	CSystemTraceDlg(CWnd* pParent = NULL);   // �зǫغc�禡
	virtual ~CSystemTraceDlg();

	// ��ܤ�����
	enum { IDD = IDD_DIALOG_SYSTEM_TRACE };

private:
	CListCtrl m_pMessageList;

	CFont m_Font;

	CXPGroupBox m_GroupBox;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �䴩
	virtual BOOL OnInitDialog();
	BOOL PreTranslateMessage( MSG* pMsg );
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg long OnMessageUpdateTrace( WPARAM wparam, LPARAM lparam );
	afx_msg void OnBnClickedCancel();
};
