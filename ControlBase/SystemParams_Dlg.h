#pragma once

#include "Resource.h"
#include "BtnST.h"
#include "ShadeButtonST.h"
#include "XPGroupBox.h"
#include "afxwin.h"
#include "SystemParams.h"

// CSystemParamsDlg ��ܤ��

class CSystemParamsDlg : public CDialog
{
	DECLARE_DYNAMIC(CSystemParamsDlg)

public:
	void UpdateUI();
	
private:
	CFont m_Font;

public:
	CSystemParamsDlg(CSystemParams *SystemParams, CWnd* pParent = NULL);   // �зǫغc�禡
	virtual ~CSystemParamsDlg();

// ��ܤ�����
	enum { IDD = IDD_DIALOG_SYSPARAMSET };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �䴩
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()

private:
	CListCtrl m_ParamList;

	int m_Base_Row, m_Base_Col;

	CEdit m_Base_EditItem;

	CComboBox m_Base_ComboBoxItem;

	CSystemParams *m_SystemParams;

	CShadeButtonST m_InterLockCheck;

public:

	afx_msg void OnNMClickGrid(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMDbClickGrid(NMHDR* pNMHDR, LRESULT* pResult);

	afx_msg long OnMessageChangeLang( WPARAM wparam, LPARAM lparam );

	afx_msg void OnBnClickedButtonSave();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnBnClickedButtonTodayProductsClear();
	afx_msg void OnBnClickedButtonTotalProductsClear();

	bool ReloadSystemParams();
	afx_msg void OnBnClickedBtnResetSetting();
	afx_msg void OnBnClickedCheckSystemparamInterlockCheck();
};

