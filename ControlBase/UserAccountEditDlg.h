#pragma once
#include "XPGroupBox.h"

// CUserAccountEditDlg 對話方塊

class AFX_EXT_CLASS CUserAccountEditDlg : public CDialog
{
	DECLARE_DYNAMIC(CUserAccountEditDlg)

public:
	CUserAccountEditDlg(CWnd* pParent = NULL);   // 標準建構函式
	virtual ~CUserAccountEditDlg();

// 對話方塊資料
	enum { IDD = IDD_DIALOG_OPTION_ACCOUNT_MODIFY };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支援
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()

private:
	CFont m_Font;

	UINT m_LanguageType;

	CString m_sUserName, m_sUserID, m_sUserPassword;
	int m_nUserLevel;

	CComboBox m_UserLevelSel;

	CXPGroupBox m_GroupBox;

public:
	BOOL PreTranslateMessage(MSG* pMsg);

	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg long OnMessageChangeLang( WPARAM wparam, LPARAM lparam );
	afx_msg void OnBnClickedOk();

	CString GetUserName();
	CString GetUserID();
	CString GetUserPassword();
	int GetUserLevel();

	void SetLanguage(UINT nType);
	
	afx_msg void OnDestroy();
};
