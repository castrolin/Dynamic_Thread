#pragma once
#include "BtnST.h"
#include "ImageProc_PictureShowUnit.h"

// CStepFuncDlg 對話方塊

class CStepFuncDlg_Sticker : public CDialog
{
	DECLARE_DYNAMIC(CStepFuncDlg_Sticker)

public:
	CStepFuncDlg_Sticker(CWnd* pParent = NULL);   // 標準建構函式
	virtual ~CStepFuncDlg_Sticker();

	// 對話方塊資料
	enum { IDD = IDD_DIALOG_OPTION_STEP_FUNC };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支援
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()

private:
	BOOL m_bRB_NeedIntial;

	CImageProc_PictureShowUnit *m_PictureShowUnit;

	CFont m_Font, mBtnFont;

	cv::Mat m_ImageBuffer;

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

	void ShowManualClickResultShowButton(BOOL bShow);

	void SetResultStatus( POINT_DATA_2F Point_L, POINT_DATA_2F Point_R, double Offset_X, double Offset_Y, double Offset_T, BOOL CALIMODE = FALSE);

	static BOOL DrawCallBack(cv::Mat *pImage, LPVOID pObject);

	void GetManualClickResult(CPoint &Point_R, CPoint &Point_L);

	void ShowClickPos(CImageProc_PictureShowUnit::SHOW_CLICKPOS_TYPE nType);
	void ShowResultPos( BOOL bShow );
	
	
};
