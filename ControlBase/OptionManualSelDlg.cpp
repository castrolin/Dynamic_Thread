// OptionDlg.cpp : 實作檔
//

#include "stdafx.h"
#include "OptionManualSelDlg.h"


// COptionDlg 對話方塊

IMPLEMENT_DYNAMIC(COptionManualSelDlg, CDialog)

	COptionManualSelDlg::COptionManualSelDlg(CWnd* pParent /*=NULL*/)
	: CDialog(COptionManualSelDlg::IDD, pParent)
{
	HINSTANCE ORG = AfxGetResourceHandle();
#ifdef _DEBUG
	HINSTANCE ControlBaseInstanceHandle = GetModuleHandle("..\\Debug\\ControlBase.dll");
#elif
	HINSTANCE ControlBaseInstanceHandle = GetModuleHandle("..\\Release\\ControlBase.dll");
#endif
	AfxSetResourceHandle(ControlBaseInstanceHandle);

	this->Create(IDD_DIALOG_OPTION_MANUAL_SEL, pParent);

	AfxSetResourceHandle(ORG);
}

COptionManualSelDlg::~COptionManualSelDlg()
{
}

void COptionManualSelDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	for(int x = 0; x < _OPTION_MANUAL_SEL_PAGE_NUM; x++)
	{
		DDX_Control(pDX, IDC_BUTTON_OPTION_MANUAL_SEL_PAGE_0 + x, m_Btn_Option_Page[x]);
	}
}


BEGIN_MESSAGE_MAP(COptionManualSelDlg, CDialog)
	ON_MESSAGE(CWM_SYS_UPDATE_LANG, OnMessageChangeLang)
	ON_BN_CLICKED(IDC_BUTTON_OPTION_MANUAL_SEL_PAGE_0, &COptionManualSelDlg::OnBnClickedButtonOptionPage0)
	ON_BN_CLICKED(IDC_BUTTON_OPTION_MANUAL_SEL_PAGE_1, &COptionManualSelDlg::OnBnClickedButtonOptionPage1)
	ON_BN_CLICKED(IDC_BUTTON_OPTION_MANUAL_SEL_PAGE_2, &COptionManualSelDlg::OnBnClickedButtonOptionPage2)
	ON_BN_CLICKED(IDC_BUTTON_OPTION_MANUAL_SEL_PAGE_3, &COptionManualSelDlg::OnBnClickedButtonOptionPage3)
	ON_BN_CLICKED(IDC_BUTTON_OPTION_MANUAL_SEL_PAGE_4, &COptionManualSelDlg::OnBnClickedButtonOptionPage4)
	ON_BN_CLICKED(IDC_BUTTON_OPTION_MANUAL_SEL_PAGE_5, &COptionManualSelDlg::OnBnClickedButtonOptionPage5)
	ON_BN_CLICKED(IDC_BUTTON_OPTION_MANUAL_SEL_PAGE_6, &COptionManualSelDlg::OnBnClickedButtonOptionPage6)
	ON_BN_CLICKED(IDC_BUTTON_OPTION_MANUAL_SEL_PAGE_7, &COptionManualSelDlg::OnBnClickedButtonOptionPage7)
END_MESSAGE_MAP()


// COptionDlg 訊息處理常式
BOOL COptionManualSelDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	CFont * pFont = GetFont();
	LOGFONT lf;
	pFont->GetLogFont( &lf );
	lf.lfWeight = FW_BOLD;
	m_ControlFont.CreateFontIndirect( &lf );

	SendMessageToDescendants( WM_SETFONT, (WPARAM) m_ControlFont.m_hObject );

	for(int x = 0; x < _OPTION_MANUAL_SEL_PAGE_NUM; x++)
	{
		m_Btn_Option_Page[x].SetFlat(FALSE);
		m_Btn_Option_Page[x].SetShade(CShadeButtonST::SHS_NOISE, 8, 20, 5, RGB(55,55,255));		
		m_Btn_Option_Page[x].SetColor(CButtonST::BTNST_COLOR_FG_IN, RGB(0, 0, 255));
		m_Btn_Option_Page[x].SetFont(&m_ControlFont);
	}


	return TRUE;
}

void COptionManualSelDlg::OnBnClickedButtonOptionPage0()
{
	ShowOptionDlg();
}

void COptionManualSelDlg::OnBnClickedButtonOptionPage1()
{

	HideAllDlg();

	CRect ClientRect;
	StepFuncDlg->GetClientRect(&ClientRect);
	StepFuncDlg->MoveWindow(	ControlBase->m_FunctionArea.left + 5, 
								ControlBase->m_FunctionArea.top + 5,
								ClientRect.Width(), 
								ClientRect.Height());

	StepFuncDlg->ShowWindow(SW_SHOW);

}

void COptionManualSelDlg::OnBnClickedButtonOptionPage2()
{	

	HideAllDlg();

}

void COptionManualSelDlg::OnBnClickedButtonOptionPage3()
{

	HideAllDlg();

}

void COptionManualSelDlg::OnBnClickedButtonOptionPage4()
{
	HideAllDlg();
}

void COptionManualSelDlg::OnBnClickedButtonOptionPage5()
{
	HideAllDlg();

	CRect ClientRect;
	//RobotStepFuncDlg->GetClientRect(&ClientRect);
	//RobotStepFuncDlg->MoveWindow(	ControlBase->m_FunctionArea.left + 5, 
	//								ControlBase->m_FunctionArea.top + 5,
	//								ClientRect.Width(), 
	//								ClientRect.Height());

	//RobotStepFuncDlg->ShowWindow(SW_SHOW);
}

void COptionManualSelDlg::OnBnClickedButtonOptionPage6()
{
	HideAllDlg();

}

void COptionManualSelDlg::OnBnClickedButtonOptionPage7()
{
	HideAllDlg();
}

long COptionManualSelDlg::OnMessageChangeLang( WPARAM wparam, LPARAM lparam )
{
	CString DlgName = "OptionManualSelDlg";

	std::vector<CString>ButtonList;

	ButtonList = LanguageCtrl->GetInterfaceButtonNameList(DlgName, (UINT)wparam);

	//更換按鈕
	for(int x = 0; x < _OPTION_MANUAL_SEL_PAGE_NUM; x ++)
		this->GetDlgItem(IDC_BUTTON_OPTION_MANUAL_SEL_PAGE_0 + x)->SetWindowText(ButtonList.at(x));

	return 0;

}
