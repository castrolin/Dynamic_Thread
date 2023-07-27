#pragma once


// CRecipeSettingDlg ��ܤ��

class CRecipeListDlg : public CDialog
{
	DECLARE_DYNAMIC(CRecipeListDlg)

public:
	CRecipeListDlg(CWnd* pParent, CString RecipePATH, CGetRecipe *pProcessRecipe);   // �зǫغc�禡
	virtual ~CRecipeListDlg();

	// ��ܤ�����
	enum { IDD = IDD_DIALOG_OPTION_RECIPE_LIST };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �䴩
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()

private:

	CString m_RecipePATH;

	CFont m_Font, m_ComboxFont;

	CStringList cListrecipedata ;

	CListCtrl m_RecipeList;

	CGetRecipe *m_pProcessRecipe;

	CGetRecipe m_pRecipe_Source, m_pRecipe_Destination;

	CComboBox m_RecipeSourceSel, m_RecipeDestinationSel;

	CString m_PatternRecipePath;

public:

	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);

	afx_msg long OnMessageChangeLang( WPARAM wparam, LPARAM lparam );

	void UpdateList();

	void CopyPatternOnForAll(CString SourcePattern);

	afx_msg void OnBnClickedButtonSystemRecipeReload();
	afx_msg void OnBnClickedButtonSystemRecipeSet();
	afx_msg void OnBnClickedButtonSystemRecipeCopy();
	afx_msg void OnCbnDropdownComboRecipeListCopySource();
	afx_msg void OnCbnDropdownComboRecipeListCopyDestination();
};
