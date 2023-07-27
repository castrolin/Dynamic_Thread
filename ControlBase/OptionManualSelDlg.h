#pragma once
#include "ShadeButtonST.h"

// COptionDlg ��ܤ��
#define _OPTION_MANUAL_SEL_PAGE_NUM 8

class COptionManualSelDlg : public CDialog
{
	DECLARE_DYNAMIC(COptionManualSelDlg)

public:
	COptionManualSelDlg(CWnd* pParent = NULL);   // �зǫغc�禡
	virtual ~COptionManualSelDlg();

	// ��ܤ�����
	enum { IDD = IDD_DIALOG_OPTION_MANUAL_SEL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �䴩
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
