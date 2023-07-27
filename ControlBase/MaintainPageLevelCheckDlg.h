#pragma once
#include "XPGroupBox.h"
#include "CommonFunc.h"


// CMaintainPageLevelCheckDlg 對話方塊

class CMaintainPageLevelCheckDlg : public CDialog
{
	DECLARE_DYNAMIC(CMaintainPageLevelCheckDlg)

public:
	CMaintainPageLevelCheckDlg(CWnd* pParent = NULL);   // 標準建構函式
	virtual ~CMaintainPageLevelCheckDlg();

// 對話方塊資料
	enum { IDD = IDD_DIALOG_OPTION_MAINTAIN_USER_INFO };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支援
	virtual BOOL OnInitDialog();
	BOOL PreTranslateMessage(MSG* pMsg);
	DECLARE_MESSAGE_MAP()

private:
	CString m_PassWord, m_OperatorID, m_OperatorName;
	UINT m_AccessClass;

	CString m_Project_Path;
	CFont m_Font;

	CComboBox m_UserSel;

	CXPGroupBox m_GroupBox;
public:

	afx_msg void OnBnClickedButtonOptionMaintainUserInfoYes();
	afx_msg void OnBnClickedButtonOptionMaintainUserInfoCancel();

	UINT GetAccessRet();
	CString GetOperatorID();
	CString GetOperatorName();
	UINT GetAccessClass();
	afx_msg void OnCbnSetfocusComboOptionMaintainUserInfoUserId();
};
