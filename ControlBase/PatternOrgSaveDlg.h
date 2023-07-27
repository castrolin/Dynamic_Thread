#pragma once
#include "XPGroupBox.h"
// CPatternOrgSaveDlg ��ܤ��

class CPatternOrgSaveDlg : public CDialog
{
	DECLARE_DYNAMIC(CPatternOrgSaveDlg)

public:
	CPatternOrgSaveDlg(CString PatternName, double Org_X, double Org_Y, CWnd* pParent = NULL );   // �зǫغc�禡
	virtual ~CPatternOrgSaveDlg();
	virtual BOOL OnInitDialog();

	// ��ܤ�����
	enum { IDD = IDD_DIALOG_PATTERN_ORG_SAVE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �䴩
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
