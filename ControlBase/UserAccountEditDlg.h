#pragma once
#include "XPGroupBox.h"

// CUserAccountEditDlg ��ܤ��

class AFX_EXT_CLASS CUserAccountEditDlg : public CDialog
{
	DECLARE_DYNAMIC(CUserAccountEditDlg)

public:
	CUserAccountEditDlg(CWnd* pParent = NULL);   // �зǫغc�禡
	virtual ~CUserAccountEditDlg();

// ��ܤ�����
	enum { IDD = IDD_DIALOG_OPTION_ACCOUNT_MODIFY };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �䴩
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
