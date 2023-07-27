// CLogListDlg.cpp : 實作檔
//

#include "stdafx.h"
#include "ControlBase.h"
#include "PerformanceDlg.h"
#include "afxdialogex.h"


// CCLogListDlg 對話方塊

IMPLEMENT_DYNAMIC(CPerformanceDlg, CDialog)

	CPerformanceDlg::CPerformanceDlg(CPerformanceLog *pPerformanceLog, CWnd* pParent /*=NULL*/)
	: CDialog(CPerformanceDlg::IDD, pParent)
{
	HINSTANCE ORG = AfxGetResourceHandle();
#ifdef _DEBUG
	HINSTANCE ControlBaseInstanceHandle = GetModuleHandle("..\\Debug\\ControlBase.dll");
#elif
	HINSTANCE ControlBaseInstanceHandle = GetModuleHandle("..\\Release\\ControlBase.dll");
#endif
	AfxSetResourceHandle(ControlBaseInstanceHandle);

	this->Create(IDD_DIALOG_OPTION_PERFORMANCE, pParent);

	m_pPerformanceLog = pPerformanceLog;

	AfxSetResourceHandle(ORG);

}

CPerformanceDlg::~CPerformanceDlg()
{

}

void CPerformanceDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_LIST_PERFORMANCE, m_ListPerformance);
	DDX_Control(pDX, IDC_LIST_TACKTIME, m_ListTackTime);

	DDX_Control(pDX, IDC_EDIT_PERFORMANCE, m_EditPerformance);
	DDX_Control(pDX, IDC_EDIT_TACKTIME, m_EditTackTime);

}


BEGIN_MESSAGE_MAP(CPerformanceDlg, CDialog)
	
	ON_MESSAGE(CWM_SYS_UPDATE_PRODUCT_COUNT, OnMessageUpdateProductCount)
	ON_MESSAGE(CWM_SYS_UPDATE_LANG, OnMessageChangeLang)
	ON_BN_CLICKED(IDC_BUTTON_PERFORMANCE_TEST, &CPerformanceDlg::OnBnClickedButtonPerformanceTest)
END_MESSAGE_MAP()



BOOL CPerformanceDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_ListPerformance.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES |LVS_EX_FLATSB);
	m_ListPerformance.InsertColumn(0,	_T("No."),	LVCFMT_CENTER, 60, 2);
	m_ListPerformance.InsertColumn(1,	_T("Date"),	LVCFMT_LEFT, 180, 2);
	m_ListPerformance.InsertColumn(2,	_T("AM Shift"),	LVCFMT_LEFT, 140, 2);
	m_ListPerformance.InsertColumn(3,	_T("PM Shift"),	LVCFMT_LEFT, 140, 2);

	m_ListTackTime.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES |LVS_EX_FLATSB);
	m_ListTackTime.InsertColumn(0,	_T("No."),	LVCFMT_CENTER, 60, 2);
	m_ListTackTime.InsertColumn(1,	_T("Date"),	LVCFMT_LEFT, 180, 2);
	m_ListTackTime.InsertColumn(2,	_T("TackTime"),	LVCFMT_LEFT, 140, 2);


	m_EditPerformance.SetWindowText("Performance");
	m_EditPerformance.SetTextFont(220, "Times New Roman");
	m_EditPerformance.SetForeColor(RGB(0, 0, 0));

	m_EditTackTime.SetWindowText("Tack Time");
	m_EditTackTime.SetTextFont(220, "Times New Roman");
	m_EditTackTime.SetForeColor(RGB(0, 0, 0));


	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX 屬性頁應傳回 FALSE
}

long CPerformanceDlg::OnMessageChangeLang( WPARAM wparam, LPARAM lparam )
{
	CString DlgName = "PerformanceDlg";

	std::vector<CString>ButtonList;
	std::vector<CString>StaticList;

	ButtonList = LanguageCtrl->GetInterfaceButtonNameList(DlgName, (UINT)wparam);
	StaticList = LanguageCtrl->GetInterfaceStaticNameList(DlgName, (UINT)wparam);

	GetDlgItem(IDC_EDIT_PERFORMANCE)->SetWindowText(ButtonList.at(0));
	GetDlgItem(IDC_EDIT_TACKTIME)->SetWindowText(ButtonList.at(1));

	LVCOLUMN lvCol;



	for(int x = 1; x < 4; x ++)
	{
		m_ListPerformance.GetColumn(x,&lvCol);
		lvCol.pszText = StaticList.at(x - 1).GetBuffer(0);
		m_ListPerformance.SetColumn(x,&lvCol);

		::ZeroMemory((void *)&lvCol, sizeof(LVCOLUMN));
		lvCol.mask=LVCF_TEXT;
	}

	for(int x = 1; x < 3; x ++)
	{
		m_ListTackTime.GetColumn(x,&lvCol);
		lvCol.pszText = StaticList.at(x - 1 + 3).GetBuffer(0);
		m_ListTackTime.SetColumn(x,&lvCol);

		::ZeroMemory((void *)&lvCol, sizeof(LVCOLUMN));
		lvCol.mask=LVCF_TEXT;
	}

	return 0;

}

long CPerformanceDlg::OnMessageUpdateProductCount( WPARAM wparam, LPARAM lparam )
{

	m_ListPerformance.DeleteAllItems();
	m_ListTackTime.DeleteAllItems();
	
	std::deque<STUC_PERFORMANCE>* pPerformanceData = NULL;
	std::deque<STUC_TACKTIME>* pTackTimeData = NULL;

	pPerformanceData = m_pPerformanceLog->GetPerformanceData();
	pTackTimeData = m_pPerformanceLog->GetTackTimeData();

	for(UINT x = 0; x < pPerformanceData->size(); x++)
	{
		m_ListPerformance.InsertItem(x, FormatString("No.%03d", x + 1));
		m_ListPerformance.SetItemText(x, 1, pPerformanceData->at(x).LogTime.Format("%Y-%m-%d %H:%M:%S"));
		m_ListPerformance.SetItemText(x, 2, FormatString("%d", pPerformanceData->at(x).AM_Shift));
		m_ListPerformance.SetItemText(x, 3, FormatString("%d", pPerformanceData->at(x).PM_Shift));
	}

	for(UINT x = 0; x < pTackTimeData->size(); x++)
	{
		m_ListTackTime.InsertItem(x, FormatString("No.%03d", x + 1));
		m_ListTackTime.SetItemText(x, 1, pTackTimeData->at(x).LogTime.Format("%Y-%m-%d %H:%M:%S"));
		m_ListTackTime.SetItemText(x, 2, FormatString("%d", pTackTimeData->at(x).TackTime));
	}


	return 0;
}

// CCLogListDlg 訊息處理常式

void CPerformanceDlg::OnBnClickedButtonPerformanceTest()
{
	m_pPerformanceLog->AddLastPerformace(1);
	m_pPerformanceLog->SetLastTackTime(1000);
}
