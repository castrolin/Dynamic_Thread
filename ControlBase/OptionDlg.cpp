// OptionDlg.cpp : 實作檔
//

#include "stdafx.h"
#include "OptionDlg.h"


// COptionDlg 對話方塊

IMPLEMENT_DYNAMIC(COptionDlg, CDialog)

COptionDlg::COptionDlg(CWnd* pParent /*=NULL*/)
	: CDialog(COptionDlg::IDD, pParent)
{
	HINSTANCE ORG = AfxGetResourceHandle();
#ifdef _DEBUG
	HINSTANCE ControlBaseInstanceHandle = GetModuleHandle("..\\Debug\\ControlBase.dll");
#elif
	HINSTANCE ControlBaseInstanceHandle = GetModuleHandle("..\\Release\\ControlBase.dll");
#endif
	AfxSetResourceHandle(ControlBaseInstanceHandle);

	this->Create(IDD_DIALOG_OPTION, pParent);

	AfxSetResourceHandle(ORG);
}

COptionDlg::~COptionDlg()
{
}

void COptionDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	for(int x = 0; x < _OPTION_PAGE_NUM; x++)
	{
		DDX_Control(pDX, IDC_BUTTON_OPTION_PAGE_0 + x, m_Btn_Option_Page[x]);
	}
}


BEGIN_MESSAGE_MAP(COptionDlg, CDialog)
	ON_MESSAGE(CWM_SYS_UPDATE_LANG, OnMessageChangeLang)
	ON_BN_CLICKED(IDC_BUTTON_OPTION_PAGE_0, &COptionDlg::OnBnClickedButtonOptionPage0)
	ON_BN_CLICKED(IDC_BUTTON_OPTION_PAGE_1, &COptionDlg::OnBnClickedButtonOptionPage1)
	ON_BN_CLICKED(IDC_BUTTON_OPTION_PAGE_2, &COptionDlg::OnBnClickedButtonOptionPage2)
	ON_BN_CLICKED(IDC_BUTTON_OPTION_PAGE_3, &COptionDlg::OnBnClickedButtonOptionPage3)
	ON_BN_CLICKED(IDC_BUTTON_OPTION_PAGE_4, &COptionDlg::OnBnClickedButtonOptionPage4)

	ON_BN_CLICKED(IDC_BUTTON_OPTION_PAGE_5, &COptionDlg::OnBnClickedButtonOptionPage5)
	ON_BN_CLICKED(IDC_BUTTON_OPTION_PAGE_6, &COptionDlg::OnBnClickedButtonOptionPage6)
	ON_BN_CLICKED(IDC_BUTTON_OPTION_PAGE_7, &COptionDlg::OnBnClickedButtonOptionPage7)
	ON_BN_CLICKED(IDC_BUTTON_OPTION_PAGE_8, &COptionDlg::OnBnClickedButtonOptionPage8)
	ON_BN_CLICKED(IDC_BUTTON_OPTION_PAGE_9, &COptionDlg::OnBnClickedButtonOptionPage9)

	ON_BN_CLICKED(IDC_BUTTON_OPTION_PAGE_10, &COptionDlg::OnBnClickedButtonOptionPage10)
	ON_BN_CLICKED(IDC_BUTTON_OPTION_PAGE_11, &COptionDlg::OnBnClickedButtonOptionPage11)
	ON_BN_CLICKED(IDC_BUTTON_OPTION_PAGE_12, &COptionDlg::OnBnClickedButtonOptionPage12)
	ON_BN_CLICKED(IDC_BUTTON_OPTION_PAGE_13, &COptionDlg::OnBnClickedButtonOptionPage13)
	ON_BN_CLICKED(IDC_BUTTON_OPTION_PAGE_14, &COptionDlg::OnBnClickedButtonOptionPage14)

	ON_BN_CLICKED(IDC_BUTTON_OPTION_PAGE_15, &COptionDlg::OnBnClickedButtonOptionPage15)
	ON_BN_CLICKED(IDC_BUTTON_OPTION_PAGE_16, &COptionDlg::OnBnClickedButtonOptionPage16)
	ON_BN_CLICKED(IDC_BUTTON_OPTION_PAGE_17, &COptionDlg::OnBnClickedButtonOptionPage17)
	ON_BN_CLICKED(IDC_BUTTON_OPTION_PAGE_18, &COptionDlg::OnBnClickedButtonOptionPage18)
	ON_BN_CLICKED(IDC_BUTTON_OPTION_PAGE_19, &COptionDlg::OnBnClickedButtonOptionPage19)

	ON_BN_CLICKED(IDC_BUTTON_OPTION_PAGE_20, &COptionDlg::OnBnClickedButtonOptionPage20)
	ON_BN_CLICKED(IDC_BUTTON_OPTION_PAGE_21, &COptionDlg::OnBnClickedButtonOptionPage21)
	ON_BN_CLICKED(IDC_BUTTON_OPTION_PAGE_22, &COptionDlg::OnBnClickedButtonOptionPage22)
	ON_BN_CLICKED(IDC_BUTTON_OPTION_PAGE_23, &COptionDlg::OnBnClickedButtonOptionPage23)
	ON_BN_CLICKED(IDC_BUTTON_OPTION_PAGE_24, &COptionDlg::OnBnClickedButtonOptionPage24)

	ON_BN_CLICKED(IDC_BUTTON_OPTION_PAGE_25, &COptionDlg::OnBnClickedButtonOptionPage25)
	ON_BN_CLICKED(IDC_BUTTON_OPTION_PAGE_26, &COptionDlg::OnBnClickedButtonOptionPage26)
	ON_BN_CLICKED(IDC_BUTTON_OPTION_PAGE_27, &COptionDlg::OnBnClickedButtonOptionPage27)
	ON_BN_CLICKED(IDC_BUTTON_OPTION_PAGE_28, &COptionDlg::OnBnClickedButtonOptionPage28)
	ON_BN_CLICKED(IDC_BUTTON_OPTION_PAGE_29, &COptionDlg::OnBnClickedButtonOptionPage29)
END_MESSAGE_MAP()


// COptionDlg 訊息處理常式
BOOL COptionDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	CFont * pFont = GetFont();
	LOGFONT lf;
	pFont->GetLogFont( &lf );
	lf.lfWeight = FW_BOLD;
	m_ControlFont.CreateFontIndirect( &lf );

	SendMessageToDescendants( WM_SETFONT, (WPARAM) m_ControlFont.m_hObject );

	for(int x = 0; x < _OPTION_PAGE_NUM; x++)
	{
		m_Btn_Option_Page[x].SetFlat(FALSE);
		m_Btn_Option_Page[x].SetShade(CShadeButtonST::SHS_NOISE, 8, 20, 5, RGB(55,55,255));		
		m_Btn_Option_Page[x].SetColor(CButtonST::BTNST_COLOR_FG_IN, RGB(0, 0, 255));
		m_Btn_Option_Page[x].SetFont(&m_ControlFont);
	}
	
	SetOptionClass(1);

	return TRUE;
}

void COptionDlg::OnBnClickedButtonOptionPage0()
{
	if(GetSystemMode() == MODE_AUTO)
	{
		return;
	}

	HideAllDlg();

	CRect ClientRect;
	SystemParamsDlg->GetClientRect(&ClientRect);
	SystemParamsDlg->MoveWindow(	ControlBase->m_FunctionArea.left + 5, 
									ControlBase->m_FunctionArea.top + 5,
									ClientRect.Width(), 
									ClientRect.Height());

	SystemParamsDlg->ShowWindow(SW_SHOW);
}

void COptionDlg::OnBnClickedButtonOptionPage1()
{

	if(GetSystemMode() == MODE_AUTO)
	{
		return;
	}

	HideAllDlg();

	CRect ClientRect;
	RecipeSettingDlg->GetClientRect(&ClientRect);
	RecipeSettingDlg->MoveWindow(	ControlBase->m_FunctionArea.left + 5, 
									ControlBase->m_FunctionArea.top + 5,
									ClientRect.Width(), 
									ClientRect.Height());

	RecipeSettingDlg->ShowWindow(SW_SHOW);

}

void COptionDlg::OnBnClickedButtonOptionPage2()
{	
	
	
	
}

void COptionDlg::OnBnClickedButtonOptionPage3()
{
	if(GetSystemMode() == MODE_AUTO)
	{
		return;
	}

	HideAllDlg();
	
	CRect ClientRect;
	RecipeSettingCurrentDlg->GetClientRect(&ClientRect);
	RecipeSettingCurrentDlg->MoveWindow(	ControlBase->m_FunctionArea.left + 5, 
											ControlBase->m_FunctionArea.top + 5,
											ClientRect.Width(), 
											ClientRect.Height());

	RecipeSettingCurrentDlg->ShowWindow(SW_SHOW);
}

void COptionDlg::OnBnClickedButtonOptionPage4()
{
	if(GetSystemMode() == MODE_AUTO)
	{
		return;
	}

	HideAllDlg();

	CRect ClientRect;
	RecipeListDlg->GetClientRect(&ClientRect);
	RecipeListDlg->MoveWindow(	ControlBase->m_FunctionArea.left + 5, 
								ControlBase->m_FunctionArea.top + 5,
								ClientRect.Width(), 
								ClientRect.Height());

	RecipeListDlg->ShowWindow(SW_SHOW);
}

void COptionDlg::OnBnClickedButtonOptionPage5()
{
	if(GetSystemMode() == MODE_AUTO)
	{
		return;
	}

	HideAllDlg();

	CRect ClientRect;
	OptionManualSelDlg->GetClientRect(&ClientRect);
	OptionManualSelDlg->MoveWindow(	ControlBase->m_FunctionArea.left + 5, 
									ControlBase->m_FunctionArea.top + 5,
									ClientRect.Width(), 
									ClientRect.Height());

	OptionManualSelDlg->ShowWindow(SW_SHOW);
	
}

void COptionDlg::OnBnClickedButtonOptionPage6()
{
	HideAllDlg();
}

void COptionDlg::OnBnClickedButtonOptionPage7()
{
	HideAllDlg();
}

void COptionDlg::OnBnClickedButtonOptionPage8()
{
	HideAllDlg();
}

void COptionDlg::OnBnClickedButtonOptionPage9()
{
	HideAllDlg();
}

void COptionDlg::OnBnClickedButtonOptionPage10()
{
	HideAllDlg();
}

void COptionDlg::OnBnClickedButtonOptionPage11()
{
	HideAllDlg();
}

void COptionDlg::OnBnClickedButtonOptionPage12()
{
	HideAllDlg();
}

void COptionDlg::OnBnClickedButtonOptionPage13()
{
	HideAllDlg();
}

void COptionDlg::OnBnClickedButtonOptionPage14()
{
	HideAllDlg();
}

void COptionDlg::OnBnClickedButtonOptionPage15()
{
	
	HideAllDlg();
}

void COptionDlg::OnBnClickedButtonOptionPage16()
{
	HideAllDlg();
}

void COptionDlg::OnBnClickedButtonOptionPage17()
{
	HideAllDlg();
}

void COptionDlg::OnBnClickedButtonOptionPage18()
{
	
	HideAllDlg();
	
}

void COptionDlg::OnBnClickedButtonOptionPage19()
{
	HideAllDlg();
}

void COptionDlg::OnBnClickedButtonOptionPage20()
{
	HideAllDlg();

	Dynamic_Thread->bThreadStart=TRUE;
	CRect ClientRect;
	InputTestDlg->GetClientRect(&ClientRect);
	InputTestDlg->MoveWindow(	ControlBase->m_FunctionArea.left + 5, 
								ControlBase->m_FunctionArea.top + 5,
								ClientRect.Width(), 
								ClientRect.Height());

	InputTestDlg->ShowWindow(SW_SHOW);
}

void COptionDlg::OnBnClickedButtonOptionPage21()
{

	HideAllDlg();

	CRect ClientRect;
	OutputTestDlg->GetClientRect(&ClientRect);
	OutputTestDlg->MoveWindow(	ControlBase->m_FunctionArea.left + 5, 
								ControlBase->m_FunctionArea.top + 5,
								ClientRect.Width(), 
								ClientRect.Height());

	OutputTestDlg->ShowWindow(SW_SHOW);


	InputTestDlg->GetClientRect(&ClientRect);
	InputTestDlg->MoveWindow(	ControlBase->m_FunctionArea.left + 550, 
								ControlBase->m_FunctionArea.top + 5,
								ClientRect.Width(), 
								ClientRect.Height());

	InputTestDlg->ShowWindow(SW_SHOW);
}

void COptionDlg::OnBnClickedButtonOptionPage22()
{

	HideAllDlg();
}

void COptionDlg::OnBnClickedButtonOptionPage23()
{
	HideAllDlg();
	
	CRect ClientRect;
	PerformanceDlg->GetClientRect(&ClientRect);
	PerformanceDlg->MoveWindow(	ControlBase->m_FunctionArea.left + 5, 
								ControlBase->m_FunctionArea.top + 5,
								ClientRect.Width(), 
								ClientRect.Height());

	PerformanceDlg->ShowWindow(SW_SHOW);
}

void COptionDlg::OnBnClickedButtonOptionPage24()
{
	HideAllDlg();

	CRect ClientRect;
	LogListDlg->GetClientRect(&ClientRect);
	LogListDlg->MoveWindow(	ControlBase->m_FunctionArea.left + 5, 
							ControlBase->m_FunctionArea.top + 5,
							ClientRect.Width(), 
							ClientRect.Height());

	LogListDlg->ShowWindow(SW_SHOW);

	
}

void COptionDlg::OnBnClickedButtonOptionPage25()
{
	HideAllDlg();

	CRect ClientRect;
	UserAccountDlg->GetClientRect(&ClientRect);
	UserAccountDlg->MoveWindow(	ControlBase->m_FunctionArea.left + 5, 
								ControlBase->m_FunctionArea.top + 5,
								ClientRect.Width(), 
								ClientRect.Height());

	UserAccountDlg->ShowWindow(SW_SHOW);
}

void COptionDlg::OnBnClickedButtonOptionPage26()
{
	//HideAllDlg();

	SystemTraceDlg->ShowWindow(SW_SHOW);
}

void COptionDlg::OnBnClickedButtonOptionPage27()
{
	ControlBase->SetCurrentLang(SYSTEM_LANGUAGE_CN);
}

void COptionDlg::OnBnClickedButtonOptionPage28()
{
	ControlBase->SetCurrentLang(SYSTEM_LANGUAGE_EN);
}

void COptionDlg::OnBnClickedButtonOptionPage29()
{
	HideAllDlg();

	MaintainPageDlg->ShowWindow(SW_SHOW);
}

long COptionDlg::OnMessageChangeLang( WPARAM wparam, LPARAM lparam )
{
	CString DlgName = "OptionDlg";

	std::vector<CString>ButtonList;

	ButtonList = LanguageCtrl->GetInterfaceButtonNameList(DlgName, (UINT)wparam);

	//更換按鈕
	for(int x = 0; x < 30; x ++)
		this->GetDlgItem(IDC_BUTTON_OPTION_PAGE_0 + x)->SetWindowText(ButtonList.at(x));

	return 0;

}

void COptionDlg::SetOptionClass( UINT nClass )
{
	switch(nClass)
	{
	case 1:
		//OP
		GetDlgItem(IDC_BUTTON_OPTION_PAGE_0)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_OPTION_PAGE_1)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_OPTION_PAGE_2)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_OPTION_PAGE_3)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_OPTION_PAGE_4)->EnableWindow(FALSE);

		GetDlgItem(IDC_BUTTON_OPTION_PAGE_5)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_OPTION_PAGE_6)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_OPTION_PAGE_7)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_OPTION_PAGE_8)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_OPTION_PAGE_9)->EnableWindow(FALSE);

		GetDlgItem(IDC_BUTTON_OPTION_PAGE_10)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_OPTION_PAGE_11)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_OPTION_PAGE_12)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_OPTION_PAGE_13)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_OPTION_PAGE_14)->EnableWindow(FALSE);

		GetDlgItem(IDC_BUTTON_OPTION_PAGE_15)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_OPTION_PAGE_16)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_OPTION_PAGE_17)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_OPTION_PAGE_18)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_OPTION_PAGE_19)->EnableWindow(FALSE);

		GetDlgItem(IDC_BUTTON_OPTION_PAGE_20)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_OPTION_PAGE_21)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_OPTION_PAGE_22)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_OPTION_PAGE_23)->EnableWindow(TRUE);
		GetDlgItem(IDC_BUTTON_OPTION_PAGE_24)->EnableWindow(TRUE);

		GetDlgItem(IDC_BUTTON_OPTION_PAGE_25)->EnableWindow(TRUE);
		GetDlgItem(IDC_BUTTON_OPTION_PAGE_26)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_OPTION_PAGE_27)->EnableWindow(TRUE);
		GetDlgItem(IDC_BUTTON_OPTION_PAGE_28)->EnableWindow(TRUE);
		GetDlgItem(IDC_BUTTON_OPTION_PAGE_29)->EnableWindow(TRUE);
		
		break;
	case 2:
		//EG
		GetDlgItem(IDC_BUTTON_OPTION_PAGE_0)->EnableWindow(TRUE);
		GetDlgItem(IDC_BUTTON_OPTION_PAGE_1)->EnableWindow(TRUE);
		GetDlgItem(IDC_BUTTON_OPTION_PAGE_2)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_OPTION_PAGE_3)->EnableWindow(TRUE);
		GetDlgItem(IDC_BUTTON_OPTION_PAGE_4)->EnableWindow(TRUE);

		GetDlgItem(IDC_BUTTON_OPTION_PAGE_5)->EnableWindow(TRUE);
		GetDlgItem(IDC_BUTTON_OPTION_PAGE_6)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_OPTION_PAGE_7)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_OPTION_PAGE_8)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_OPTION_PAGE_9)->EnableWindow(FALSE);

		GetDlgItem(IDC_BUTTON_OPTION_PAGE_10)->EnableWindow(TRUE);
		GetDlgItem(IDC_BUTTON_OPTION_PAGE_11)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_OPTION_PAGE_12)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_OPTION_PAGE_13)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_OPTION_PAGE_14)->EnableWindow(FALSE);

		GetDlgItem(IDC_BUTTON_OPTION_PAGE_15)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_OPTION_PAGE_16)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_OPTION_PAGE_17)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_OPTION_PAGE_18)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_OPTION_PAGE_19)->EnableWindow(FALSE);

		GetDlgItem(IDC_BUTTON_OPTION_PAGE_20)->EnableWindow(TRUE);
		GetDlgItem(IDC_BUTTON_OPTION_PAGE_21)->EnableWindow(TRUE);
		GetDlgItem(IDC_BUTTON_OPTION_PAGE_22)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_OPTION_PAGE_23)->EnableWindow(TRUE);
		GetDlgItem(IDC_BUTTON_OPTION_PAGE_24)->EnableWindow(TRUE);

		GetDlgItem(IDC_BUTTON_OPTION_PAGE_25)->EnableWindow(TRUE);
		GetDlgItem(IDC_BUTTON_OPTION_PAGE_26)->EnableWindow(TRUE);
		GetDlgItem(IDC_BUTTON_OPTION_PAGE_27)->EnableWindow(TRUE);
		GetDlgItem(IDC_BUTTON_OPTION_PAGE_28)->EnableWindow(TRUE);
		GetDlgItem(IDC_BUTTON_OPTION_PAGE_29)->EnableWindow(TRUE);
		break;
	case 3:
		//RD
		GetDlgItem(IDC_BUTTON_OPTION_PAGE_0)->EnableWindow(TRUE);
		GetDlgItem(IDC_BUTTON_OPTION_PAGE_1)->EnableWindow(TRUE);
		GetDlgItem(IDC_BUTTON_OPTION_PAGE_2)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_OPTION_PAGE_3)->EnableWindow(TRUE);
		GetDlgItem(IDC_BUTTON_OPTION_PAGE_4)->EnableWindow(TRUE);

		GetDlgItem(IDC_BUTTON_OPTION_PAGE_5)->EnableWindow(TRUE);
		GetDlgItem(IDC_BUTTON_OPTION_PAGE_6)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_OPTION_PAGE_7)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_OPTION_PAGE_8)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_OPTION_PAGE_9)->EnableWindow(FALSE);

		GetDlgItem(IDC_BUTTON_OPTION_PAGE_10)->EnableWindow(TRUE);
		GetDlgItem(IDC_BUTTON_OPTION_PAGE_11)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_OPTION_PAGE_12)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_OPTION_PAGE_13)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_OPTION_PAGE_14)->EnableWindow(FALSE);

		GetDlgItem(IDC_BUTTON_OPTION_PAGE_15)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_OPTION_PAGE_16)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_OPTION_PAGE_17)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_OPTION_PAGE_18)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_OPTION_PAGE_19)->EnableWindow(FALSE);

		GetDlgItem(IDC_BUTTON_OPTION_PAGE_20)->EnableWindow(TRUE);
		GetDlgItem(IDC_BUTTON_OPTION_PAGE_21)->EnableWindow(TRUE);
		GetDlgItem(IDC_BUTTON_OPTION_PAGE_22)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_OPTION_PAGE_23)->EnableWindow(TRUE);
		GetDlgItem(IDC_BUTTON_OPTION_PAGE_24)->EnableWindow(TRUE);

		GetDlgItem(IDC_BUTTON_OPTION_PAGE_25)->EnableWindow(TRUE);
		GetDlgItem(IDC_BUTTON_OPTION_PAGE_26)->EnableWindow(TRUE);
		GetDlgItem(IDC_BUTTON_OPTION_PAGE_27)->EnableWindow(TRUE);
		GetDlgItem(IDC_BUTTON_OPTION_PAGE_28)->EnableWindow(TRUE);
		GetDlgItem(IDC_BUTTON_OPTION_PAGE_29)->EnableWindow(TRUE);
		break;
	default:
		break;
	}

}