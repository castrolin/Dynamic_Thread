#pragma once
#include "ShadeButtonST.h"

// COptionDlg 對話方塊
#define _OPTION_MANUAL_SEL_PAGE_NUM 8

class COptionManualSelDlg : public CDialog
{
	DECLARE_DYNAMIC(COptionManualSelDlg)

public:
	COptionManualSelDlg(CWnd* pParent = NULL);   // 標準建構函式
	virtual ~COptionManualSelDlg();

	// 對話方塊資料
	enum { IDD = IDD_DIALOG_OPTION_MANUAL_SEL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支援
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:

	CShadeButtonST m_Btn_Option_Page[30];
	CFont m_ControlFont;
	CRect FunctionArea;

	afx_msg void OnBnClickedButtonOptionPage0();
	afx_msg void OnBnClickedButtonOptionPage1();
	afx_msg void OnBnClickedButtonOptionPage2();
	afx_msg void OnBnClickedButtonOptionPage3();
	afx_msg void OnBnClickedButtonOptionPage4();
	afx_msg void OnBnClickedButtonOptionPage5();
	afx_msg void OnBnClickedButtonOptionPage6();
	afx_msg void OnBnClickedButtonOptionPage7();
	
	afx_msg long OnMessageChangeLang( WPARAM wparam, LPARAM lparam );



};
