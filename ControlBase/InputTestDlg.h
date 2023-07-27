#pragma once
#include "InputBase.h"

// CInputTest 對話方塊

class CInputTestDlg : public CDialog
{
	DECLARE_DYNAMIC(CInputTestDlg)

public:
	CInputTestDlg(CWnd* pParent = NULL);   // 標準建構函式
	virtual ~CInputTestDlg();

// 對話方塊資料
	enum { IDD = IDD_DIALOG_OPTION_INPUT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支援
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()

private:

	CFont m_Font;

	CListCtrl m_InputInfoList;

	std::vector<CInputBase*> *m_InputArray;

	CWinThread *m_InputThd;
	static UINT InputProc(LPVOID pObj);

	HANDLE m_hDead;
	HANDLE m_hOutputUpdate;

public:

	void InitialInputInfo(std::vector<CInputBase*> *Array);

	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg long OnMessageChangeLang( WPARAM wparam, LPARAM lparam );
};
