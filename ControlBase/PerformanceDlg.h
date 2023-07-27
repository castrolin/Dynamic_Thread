#pragma once
#include "PerformanceLog.h"
#include "ColorEdit.h"

// CCLogListDlg ��ܤ��

class CPerformanceDlg : public CDialog
{
	DECLARE_DYNAMIC(CPerformanceDlg)

public:
	CPerformanceDlg(CPerformanceLog *pPerformanceLog, CWnd* pParent = NULL);   // �зǫغc�禡
	virtual ~CPerformanceDlg();

	// ��ܤ�����
	enum { IDD = IDD_DIALOG_OPTION_PERFORMANCE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �䴩
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
