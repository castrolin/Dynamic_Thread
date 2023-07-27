#pragma once
#include "ShadeButtonST.h"
#include "OutputBase.h"

// COutputTestDlg 對話方塊
#define _OUTPUT_REPEAT_TIMER	0

class COutputTestDlg : public CDialog
{
	DECLARE_DYNAMIC(COutputTestDlg)

public:
	COutputTestDlg(CWnd* pParent = NULL);   // 標準建構函式
	virtual ~COutputTestDlg();

// 對話方塊資料
	enum { IDD = IDD_DIALOG_OPTION_OUTPUT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支援
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
	
private:

	CFont m_Font;

	CShadeButtonST m_OutputChEnable_1, m_OutputChEnable_2;
	CShadeButtonST m_OutputOn, m_OutputOff;
	CShadeButtonST m_OutputRepeat, m_OutputStop;

	CListCtrl m_OutputInfoList;

	std::vector<COutputBase*> *m_OutputArray;

	CComboBox m_OutputCh1, m_OutputCh2;

	CWinThread *m_OutputThd;
	static UINT OutputProc(LPVOID pObj);

	HANDLE m_hDead;
	HANDLE m_hOutputUpdate;

public:

	
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg long OnMessageChangeLang( WPARAM wparam, LPARAM lparam );
	afx_msg void OnBnClickedButtonOptionInputOn();
	afx_msg void OnBnClickedButtonOptionInputOff();
	afx_msg void OnBnClickedButtonOptionOutputRepeat();
	afx_msg void OnCbnSetfocusComboOptionOutputCh1();
	afx_msg void OnCbnSetfocusComboOptionOutputCh2();
	afx_msg void OnBnClickedButtonOptionOutputStop();
	afx_msg void OnBnClickedCheckOptionOutputCh1();
	afx_msg void OnBnClickedCheckOptionOutputCh2();

	void InitialOutputInfo(std::vector<COutputBase*> *Array);

	UINT GetRepeatTimeSetting();
	
};
