#pragma once


// CRecipeSettingDlg ��ܤ��

class CRecipeSettingCurrentDlg : public CDialog
{
	DECLARE_DYNAMIC(CRecipeSettingCurrentDlg)

public:
	CRecipeSettingCurrentDlg(CWnd* pParent, CString RecipePATH, CGetRecipe *pSystemRecipe);   // �зǫغc�禡
	virtual ~CRecipeSettingCurrentDlg();

	// ��ܤ�����
	enum { IDD = IDD_DIALOG_OPTION_RECIPE_CURRENT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �䴩
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()

private:

	CString m_RecipePATH;

	CFont m_Font, m_ComboxFont;

	CStringList cListrecipedata ;

	CListCtrl m_ParamList;

	CGetRecipe *m_pSystemRecipe;

	CGetRecipe m_pRecipe;

	int m_Base_Row, m_Base_Col;

	int m_Recipe_Row, m_Recipe_Col;

	CComboBox m_Base_ComboBoxItem;

	CEdit m_Base_EditItem;

	CString m_PatternRecipePath;

public:

	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);

	afx_msg long OnMessageChangeLang( WPARAM wparam, LPARAM lparam );

	afx_msg void OnNMClickGrid(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMDbClickGrid(NMHDR* pNMHDR, LRESULT* pResult);

	void ShowRecipeData();

	void CopyPatternOnForAll(CString SourcePattern);

	afx_msg void OnBnClickedButtonSystemRecipeReload();
	afx_msg void OnBnClickedButtonSystemRecipeSave();
	afx_msg void OnCbnDropDownPatternRecipe();
};
