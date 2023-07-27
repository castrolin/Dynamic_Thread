#pragma once
#include <deque>
#include "UserAccountEditDlg.h"

// CUserAccountDlg 對話方塊

class CUserAccountDlg : public CDialog
{
	DECLARE_DYNAMIC(CUserAccountDlg)

public:
	CUserAccountDlg(CWnd* pParent = NULL);   // 標準建構函式
	virtual ~CUserAccountDlg();

// 對話方塊資料
	enum { IDD = IDD_DIALOG_OPTION_ACCOUNT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支援
	virtual BOOL OnInitDialog();
	BOOL PreTranslateMessage( MSG* pMsg );
	DECLARE_MESSAGE_MAP()

private:
	CListCtrl m_AccountList;

	CEdit m_Base_EditItem;
	CComboBox m_Base_ComboBoxItem;

	int m_Base_Row, m_Base_Col;

	CFont m_Font;

	bool LoadAccountData();
	bool CheckAccountData();

	std::deque<CString> m_UserPasswordList;
public:
	CUserAccountEditDlg UserAccountEditDlg;

	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnBnClickedButtonAccountAdd();
	afx_msg void OnBnClickedButtonAccountDelete();
	afx_msg void OnBnClickedButtonAccountReset();
	afx_msg void OnBnClickedButtonAccountSet();
	afx_msg void OnPointListCtrlClick(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnPointListCtrlDbClick(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg long OnMessageChangeLang( WPARAM wparam, LPARAM lparam );
};
