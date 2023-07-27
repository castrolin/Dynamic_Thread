#pragma once
#include "XPGroupBox.h"
// CMessageBox ��ܤ��

class CMessageBox : public CDialog
{
	DECLARE_DYNAMIC(CMessageBox)

public:
	CMessageBox(CWnd* pParent = NULL);   // �зǫغc�禡
	virtual ~CMessageBox();
	virtual BOOL OnInitDialog();

// ��ܤ�����
	enum { IDD = IDD_DIALOG_MESSAGE_BOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �䴩

	DECLARE_MESSAGE_MAP()
public:

	CFont m_Font;
	CXPGroupBox m_GroupBox;
	void ShowMessage(CString CaptureText, CString Message, bool ShowButton, bool AutoClose = false, DWORD WaitTime = 5000);
	void CloseMessage();
	
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};
