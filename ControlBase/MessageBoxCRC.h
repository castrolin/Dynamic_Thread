#pragma once
#include "XPGroupBox.h"
// CMessageBoxCRC 對話方塊

class CMessageBoxCRC : public CDialog
{
	DECLARE_DYNAMIC(CMessageBoxCRC)

public:

	enum _SHOW_BST_TYPE
	{
		BST_CANCEL_RETRY_CONTINUE,
		BST_CANCEL_RETRY,
		BST_CANCEL_CONTINUE,
		BST_RETRY_CONTINUE,
	};

	CMessageBoxCRC(CWnd* pParent = NULL);   // 標準建構函式
	virtual ~CMessageBoxCRC();
	virtual BOOL OnInitDialog();

	// 對話方塊資料
	enum { IDD = IDD_DIALOG_MESSAGE_BOX_CRC };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支援

	DECLARE_MESSAGE_MAP()

private:

	CString m_CaptureText;
	CString m_Message;
	_SHOW_BST_TYPE m_ShowType;
	bool m_AutoClose;
	DWORD m_WaitTime;

	CXPGroupBox m_GroupBox;
public:

	CFont m_Font;
	void SetMessage(CString CaptureText, CString Message, _SHOW_BST_TYPE ShowType, bool AutoClose = false, DWORD WaitTime = 5000);
	void CloseMessage();

	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnBnClickedBstMessageCancel();
	afx_msg void OnBnClickedBstMessageRetry();
	afx_msg void OnBnClickedBstMessageContinue();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};
