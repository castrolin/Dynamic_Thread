#pragma once
#include "BtnST.h"
#include "ShadeButtonST.h"
#include "ImageProc_PictureShowUnit.h"

// CStepFuncDlg 對話方塊

class CRobotStepFuncDlg : public CDialog
{
	DECLARE_DYNAMIC(CRobotStepFuncDlg)

public:
	CRobotStepFuncDlg(CWnd* pParent = NULL);   // 標準建構函式
	virtual ~CRobotStepFuncDlg();

	// 對話方塊資料
	enum { IDD = IDD_DIALOG_OPTION_STEP_FUNC_1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支援
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()

private:
	bool m_bRB_NeedIntial;
	CFont m_Font, mBtnFont;

	CImageProc_PictureShowUnit *m_PictureShowUnit;

	std::vector<CString>m_ButtonList;
	std::vector<CString>m_StaticList;

	cv::Mat m_ImageBuffer;

	CString m_PicturePath;

	BOOL m_bShowResultPos;

	double m_RetOffset_X;
	double m_RetOffset_Y;
	double m_RetOffset_T;

	double m_TapeRetOffset_X;
	double m_TapeRetOffset_Y;
	double m_TapeRetOffset_T;

	double m_PCBRetOffset_X;
	double m_PCBRetOffset_Y;
	double m_PCBRetOffset_T;

	POINT_DATA_2F m_Point_L;
	POINT_DATA_2F m_Point_R;


	CMFCButton m_Btn_CV_Running;
	CMFCButton m_Btn_CV_Panel;

	CMFCButton m_Btn_PCB_Up;
	CMFCButton m_Btn_PCB_Down;
	CMFCButton m_Btn_PCB_Forward;
	CMFCButton m_Btn_PCB_Backward;

	double m_nOrgPosPixel_LX;
	double m_nOrgPosPixel_LY;

	double m_nOrgPosPixel_RX;
	double m_nOrgPosPixel_RY;

	
	static BOOL DrawCallBack(cv::Mat *pImage, LPVOID pObject);
public:
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg long OnMessageChangeLang( WPARAM wparam, LPARAM lparam );

	afx_msg void OnTimer(UINT_PTR nIDEvent);
	
	afx_msg void OnBnClickedButtonStepProcCorrectPcb();
	afx_msg void OnBnClickedButtonStepProcCorrectTape();
	void SetResultStatus_Tape(POINT_DATA_2F Point_L, POINT_DATA_2F Point_R, double Offset_X, double Offset_Y, double Offset_T, BOOL CALIMODE = FALSE);
	void SetResultStatus_PCB(POINT_DATA_2F Point_L, POINT_DATA_2F Point_R, double Offset_X, double Offset_Y, double Offset_T, BOOL CALIMODE = FALSE);
	void ShowResultPos( BOOL bShow );
	void ShowClickPos( CImageProc_PictureShowUnit::SHOW_CLICKPOS_TYPE nType );
	void GetManualClickResult( CPoint &Point_R, CPoint &Point_L );
	void OnBnClickedButtonStepProcPatternFindManualCheck();
	void ShowManualClickResultShowButton( BOOL bShow );


	afx_msg void OnBnClickedButtonRobotStepProcPatternFindManualCheck();
	afx_msg void OnBnClickedButtonRobotStepProcBack();
	afx_msg void OnBnClickedButtonStepProcMoveTape();
	afx_msg void OnBnClickedButtonStepProcMoveCcd();
	afx_msg void OnBnClickedButtonStepProcMovePcb();
	afx_msg void OnBnClickedButtonStepProcGetTape();
	afx_msg void OnBnClickedButtonStepProcPutTape();
	afx_msg void OnBnClickedButtonStepProcRobotInitial();
	afx_msg void OnBnClickedButtonStepProcRobotStop();
	
	afx_msg void OnBnClickedButtonRobotStepProcPcbDown();
	afx_msg void OnBnClickedButtonRobotStepProcPcbUp();
	afx_msg void OnBnClickedButtonRobotStepProcPcbForward();
	afx_msg void OnBnClickedButtonRobotStepProcPcbBackward();
	afx_msg void OnBnClickedButtonRobotStepProcPcbClamp();
	afx_msg void OnBnClickedButtonRobotStepProcPcbRelease();

	afx_msg void OnBnClickedButtonRobotStepProcCvInProcess();
	afx_msg void OnBnClickedButtonRobotStepProcCvOutProcess();
	afx_msg void OnBnClickedButtonStepProcCorrectTapeReset();
	afx_msg void OnBnClickedButtonStepProcCorrectPcbReset();
};
