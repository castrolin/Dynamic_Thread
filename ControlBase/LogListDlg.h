#pragma once


// CCLogListDlg ��ܤ��

struct SYSTEM_LOG_DATA
{
	CString _m_Date;
	CString _m_Time;
	CString _m_Description;

	SYSTEM_LOG_DATA()
	{
		_m_Date = "";
		_m_Time = "";
		_m_Description = "";
	}
};

class CLogListDlg : public CDialog
{
	DECLARE_DYNAMIC(CLogListDlg)

public:
	CLogListDlg(CString FilePath, CWnd* pParent = NULL);   // �зǫغc�禡
	virtual ~CLogListDlg();

// ��ܤ�����
	enum { IDD = IDD_DIALOG_LOGLIST };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �䴩
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
private:

	CListCtrl    m_LogList;
	CDiskObject* m_DiskObj;

	CComboBox m_DateComboBox;
	CComboBox m_TimeComboBox;
	CComboBox m_FileSelector;

	int m_Base_Row, m_Base_Col;
	CEdit m_Base_EditItem;
	int m_Base;

	CString m_path;
	CString m_FileName;
	CString m_ChosenDate;

	bool LogDataLoad();

	CString GetTimeFromString(int nRow);
	std::vector<CString> *TimeRangeVector;

	BOOL TImeFilter(CString InputTime, CString p_filter); // TimeFormate: hr:min:sec

public:
	
	afx_msg void OnBnClickedOpenLog();
	afx_msg void OnBnClickedCleanLog();

	afx_msg void OnCbnSelchangeComboDateSelect();
	afx_msg void OnCbnSelchangeComboTimeSelect();
	afx_msg void OnCbnSelchangeComboFileSelect();

	SYSTEM_LOG_DATA m_SystemLogListData;
};
