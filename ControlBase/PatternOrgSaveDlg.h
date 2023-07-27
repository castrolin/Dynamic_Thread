#pragma once
#include "XPGroupBox.h"
// CPatternOrgSaveDlg 對話方塊

class CPatternOrgSaveDlg : public CDialog
{
	DECLARE_DYNAMIC(CPatternOrgSaveDlg)

public:
	CPatternOrgSaveDlg(CString PatternName, double Org_X, double Org_Y, CWnd* pParent = NULL );   // 標準建構函式
	virtual ~CPatternOrgSaveDlg();
	virtual BOOL OnInitDialog();

	// 對話方塊資料
	enum { IDD = IDD_DIALOG_PATTERN_ORG_SAVE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支援
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	DECLARE_MESSAGE_MAP()
public:

	CFont m_Font;
	CXPGroupBox m_GroupBox;
	CString m_PattternName;
	CStringArray m_FileArray;
	CStringArray m_FindArray;
	CListCtrl m_RecipeList;
	double m_NewOrg_X, m_NewOrg_Y;

	afx_msg void OnBnClickedOk();
};
