#pragma once
#include <afxbutton.h>
#include "ColorEdit.h"
#include "BtnST.h"
#include "ShadeButtonST.h"
//#include "ImageProc_PictureShowUnit.h"

// CSystemStatus 對話方塊

class CSystemStatusDlg : public CDialog
{
	DECLARE_DYNAMIC(CSystemStatusDlg)

public:
	CSystemStatusDlg(CWnd* pParent);   // 標準建構函式
	virtual ~CSystemStatusDlg();

// 對話方塊資料
	enum { IDD = IDD_DIALOG_STATUS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支援
	virtual BOOL OnInitDialog();

	afx_msg void OnPaint();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg long OnMessageChangeLang( WPARAM wparam, LPARAM lparam );
	afx_msg long OnMessageUpdateProductCount( WPARAM wparam, LPARAM lparam );
	afx_msg long OnMessageUpdateProcessStepRobot( WPARAM wparam, LPARAM lparam );
	afx_msg long OnMessageUpdateProcessStepCV( WPARAM wparam, LPARAM lparam );
	afx_msg long OnMessageUpdateProcessStepPCB_Press( WPARAM wparam, LPARAM lparam );
	afx_msg long OnMessageUpdateExistRobot( WPARAM wparam, LPARAM lparam );
	afx_msg long OnMessageUpdateExistCV( WPARAM wparam, LPARAM lparam );
	afx_msg long OnMessageUpdateExistSticker( WPARAM wparam, LPARAM lparam );
	afx_msg long OnMessageUpdateCV_IN( WPARAM wparam, LPARAM lparam );
	afx_msg void OnBnClickedButtonStatusManualCheck();
	afx_msg void OnBnClickedButtonStatusManualCheck_Sticker();
	afx_msg void OnBnClickedButtonStatusCv();
	afx_msg void OnBnClickedCheckCvClear();
	DECLARE_MESSAGE_MAP()

private:

	CFont m_Font;

	CMFCButton m_Status_CV;
	CMFCButton m_Status_Robot;
	CMFCButton m_Status_Sticker;

	CMFCButton m_Status_Demo_1;
	CMFCButton m_Status_Demo_2;
	CMFCButton m_Status_Demo_3;

	CMFCButton m_CV_Clear;

	std::vector<CString>m_ButtonList;
	std::vector<CString>m_StaticList;

	CColorEdit m_EditResult;
	CColorEdit m_EditResultOffset_X;
	CColorEdit m_EditResultOffset_Y;
	CColorEdit m_EditResultOffset_T;
	CColorEdit m_EditResultScore;

	CColorEdit m_EditResultSticker;
	CColorEdit m_EditResultStickerOffset_X;
	CColorEdit m_EditResultStickerOffset_Y;
	CColorEdit m_EditResultStickerOffset_T;

	CShadeButtonST m_Btn_CV_In;
	CShadeButtonST m_Btn_CV_Out;
	CShadeButtonST m_Btn_CV_Running;


	CString m_PicturePath;
	CString m_PicturePath_Sticker;

	double m_RetOffset_X;
	double m_RetOffset_Y;
	double m_RetOffset_T;

	double m_RetStickerOffset_X;
	double m_RetStickerOffset_Y;
	double m_RetStickerOffset_T;

	POINT_DATA_2F m_Point_L;
	POINT_DATA_2F m_Point_R;

	POINT_DATA_2F m_StickerPoint_L;
	POINT_DATA_2F m_StickerPoint_R;

	BOOL m_bShowResultPos;
	BOOL m_bShowStickerResultPos;

public:


};
