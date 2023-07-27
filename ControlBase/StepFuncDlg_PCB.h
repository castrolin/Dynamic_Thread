#pragma once
#include "BtnST.h"

//#include "ImageProc_PictureShowUnit.h"

// CStepFuncDlg 對話方塊

class CStepFuncDlg_PCB : public CDialog
{
	DECLARE_DYNAMIC(CStepFuncDlg_PCB)

public:
	CStepFuncDlg_PCB(CWnd* pParent = NULL);   // 標準建構函式
	virtual ~CStepFuncDlg_PCB();

// 對話方塊資料
	enum { IDD = IDD_DIALOG_OPTION_STEP_FUNC };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支援
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()

private:
	BOOL m_bRB_NeedIntial;

	//CImageProc_PictureShowUnit *m_PictureShowUnit;

	CFont m_Font, mBtnFont;

	CString m_PicturePath;

	double m_RetOffset_X;
	double m_RetOffset_Y;
	double m_RetOffset_T;

	POINT_DATA_2F m_Point_L;
	POINT_DATA_2F m_Point_R;


	POINT_DATA_2F m_Point_ORG_L;
	POINT_DATA_2F m_Point_ORG_R;

	POINT_DATA_2F m_Point_MOVE_L;
	POINT_DATA_2F m_Point_MOVE_R;

	POINT_DATA_2F m_Point_ROTATE_L;
	POINT_DATA_2F m_Point_ROTATE_R;

	std::vector<CString>m_ButtonList;
	std::vector<CString>m_StaticList;

	BOOL m_bShowResultPos;

public:
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg long OnMessageChangeLang( WPARAM wparam, LPARAM lparam );

	afx_msg void OnPaint();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnCbnDropDownPatternRecipe();
	afx_msg void OnBnClickedButtonStepProcPatternFindProc();
	afx_msg void OnBnClickedButtonStepProcPatternFindProc_Org();
	afx_msg void OnBnClickedButtonStepProcSavePositionRecipe();
	afx_msg void OnBnClickedButtonStepProcCalibrate_CALIBRATE();
	afx_msg void OnBnClickedButtonStepProcPatternFindManualCheck();
	afx_msg void OnBnClickedButtonStepProcBack();
	afx_msg void OnBnClickedButtonStepProcPatternFindRobotInitial();	
};
