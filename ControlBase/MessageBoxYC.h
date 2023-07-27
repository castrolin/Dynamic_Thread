#pragma once
#include "XPGroupBox.h"

// CMessageBoxYC ��ܤ��

class AFX_EXT_CLASS CMessageBoxYC : public CDialog
{
	DECLARE_DYNAMIC(CMessageBoxYC)

public:
	CMessageBoxYC(CWnd* pParent = NULL);   // �зǫغc�禡
	virtual ~CMessageBoxYC();

// ��ܤ�����
	enum { IDD = IDD_DIALOG_MESSAGE_BOX_YC };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �䴩
	BOOL OnInitDialog();
	BOOL PreTranslateMessage(MSG* pMsg);
	DECLARE_MESSAGE_MAP()

private:
	CFont m_Font;
	CXPGroupBox m_GroupBox;
	CString m_sShowMsg;
	CString m_ShowTitle;
public:

	INT_PTR ShowMessageBox(CString CaptureText, CString Message);

	afx_msg void OnBnClickedBstMessageYes();
	afx_msg void OnBnClickedBstMessageCancel();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
};
