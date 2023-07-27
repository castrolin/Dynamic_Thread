#pragma once
#include "PictureViewerDlg.h"

// CPattenPage 對話方塊

class CPattenPage : public CDialog
{
	DECLARE_DYNAMIC(CPattenPage)

public:
	CPattenPage(CWnd* pParent = NULL);   // 標準建構函式
	virtual ~CPattenPage();

// 對話方塊資料
	enum { IDD = IDD_DIALOG_OPTION_STEP_PATTEN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支援
	virtual BOOL OnInitDialog();
	BOOL PreTranslateMessage(MSG* pMsg);
	DECLARE_MESSAGE_MAP()
private:
	CPictureViewerDlg *PictureViewerDlg_Mark1_CCDL;
	CPictureViewerDlg *PictureViewerDlg_Mark2_CCDL;
	
	CPictureViewerDlg *PictureViewerDlg_Mark1_CCDR;
	CPictureViewerDlg *PictureViewerDlg_Mark2_CCDR;
	
public:
	afx_msg void OnBnClickedButtonStepFuncCalculateClosepage();
	afx_msg void OnBnClickedButtonStepFuncGetMarkCcdL1();
	afx_msg void OnBnClickedButtonStepFuncViewMarkCcdL1();
	afx_msg void OnBnClickedButtonStepFuncViewMarkCcdL2();
	afx_msg void OnBnClickedButtonStepFuncViewMarkCcdR1();
	afx_msg void OnBnClickedButtonStepFuncViewMarkCcdR2();
	afx_msg void OnBnClickedButtonStepFuncGetMarkCcdL2();
	afx_msg void OnBnClickedButtonStepFuncGetMarkCcdR1();
	afx_msg void OnBnClickedButtonStepFuncGetMarkCcdR2();
	afx_msg void OnBnClickedButtonStepFuncCalculateResultCcdL();
	afx_msg void OnBnClickedButtonStepFuncCalculateResultCcdR();
};
