#pragma once
#include "ShadeButtonST.h"

// COptionDlg ��ܤ��
#define _OPTION_PAGE_NUM 30

class COptionDlg : public CDialog
{
	DECLARE_DYNAMIC(COptionDlg)

public:
	COptionDlg(CWnd* pParent = NULL);   // �зǫغc�禡
	virtual ~COptionDlg();

// ��ܤ�����
	enum { IDD = IDD_DIALOG_OPTION };

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
	afx_msg void OnBnClickedButtonOptionPage8();
	afx_msg void OnBnClickedButtonOptionPage9();
	afx_msg void OnBnClickedButtonOptionPage10();
	afx_msg void OnBnClickedButtonOptionPage11();
	afx_msg void OnBnClickedButtonOptionPage12();
	afx_msg void OnBnClickedButtonOptionPage13();
	afx_msg void OnBnClickedButtonOptionPage14();
	afx_msg void OnBnClickedButtonOptionPage15();
	afx_msg void OnBnClickedButtonOptionPage16();
	afx_msg void OnBnClickedButtonOptionPage17();
	afx_msg void OnBnClickedButtonOptionPage18();
	afx_msg void OnBnClickedButtonOptionPage19();
	afx_msg void OnBnClickedButtonOptionPage20();
	afx_msg void OnBnClickedButtonOptionPage21();
	afx_msg void OnBnClickedButtonOptionPage22();
	afx_msg void OnBnClickedButtonOptionPage23();
	afx_msg void OnBnClickedButtonOptionPage24();
	afx_msg void OnBnClickedButtonOptionPage25();
	afx_msg void OnBnClickedButtonOptionPage26();
	afx_msg void OnBnClickedButtonOptionPage27();
	afx_msg void OnBnClickedButtonOptionPage28();
	afx_msg void OnBnClickedButtonOptionPage29();
	afx_msg long OnMessageChangeLang( WPARAM wparam, LPARAM lparam );
	void SetOptionClass( UINT nClass );



};
