#pragma once
#include "PerformanceLog.h"
#include "ColorEdit.h"

// CCLogListDlg 對話方塊

class CPerformanceDlg : public CDialog
{
	DECLARE_DYNAMIC(CPerformanceDlg)

public:
	CPerformanceDlg(CPerformanceLog *pPerformanceLog, CWnd* pParent = NULL);   // 標準建構函式
	virtual ~CPerformanceDlg();

	// 對話方塊資料
	enum { IDD = IDD_DIALOG_OPTION_PERFORMANCE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支援
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
private:
	CPerformanceLog *m_pPerformanceLog;

	CListCtrl m_ListPerformance;
	CListCtrl m_ListTackTime;

	CColorEdit m_EditPerformance;
	CColorEdit m_EditTackTime;
public:
	afx_msg long OnMessageChangeLang( WPARAM wparam, LPARAM lparam );
	afx_msg long OnMessageUpdateProductCount( WPARAM wparam, LPARAM lparam );
	afx_msg void OnBnClickedButtonPerformanceTest();
};
