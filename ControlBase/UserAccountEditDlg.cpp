// UserAccountEditDlg.cpp : 實作檔
//

#include "stdafx.h"
#include "UserAccountEditDlg.h"
#include "afxdialogex.h"


// CUserAccountEditDlg 對話方塊

IMPLEMENT_DYNAMIC(CUserAccountEditDlg, CDialog)

CUserAccountEditDlg::CUserAccountEditDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CUserAccountEditDlg::IDD, pParent)
{
	m_LanguageType = 0;
}

CUserAccountEditDlg::~CUserAccountEditDlg()
{
}

void CUserAccountEditDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_USER_LEVEL, m_UserLevelSel);
	DDX_Control(pDX, IDC_STATIC_OPTION_ACCOUNT_MODIFY_GROUP, m_GroupBox);
}


BEGIN_MESSAGE_MAP(CUserAccountEditDlg, CDialog)
	ON_WM_SHOWWINDOW()
	ON_BN_CLICKED(IDOK, &CUserAccountEditDlg::OnBnClickedOk)
	ON_MESSAGE(CWM_SYS_UPDATE_LANG, OnMessageChangeLang)
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// CUserAccountEditDlg 訊息處理常式
BOOL CUserAccountEditDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_UserLevelSel.AddString("RD");
	m_UserLevelSel.AddString("EG");
	m_UserLevelSel.AddString("OP");

	m_GroupBox.SetXPGroupStyle(CXPGroupBox::XPGB_FRAME);
	m_GroupBox.SetBackgroundColor(RGB(180, 230, 30), ::GetSysColor(COLOR_BTNFACE));
	m_GroupBox.SetBorderColor(RGB(180, 230, 30));
	m_GroupBox.SetBorderWidth(5);

	m_GroupBox.SetFontBold(TRUE);
	m_GroupBox.SetAlignment(SS_CENTER);

	return TRUE;
}

BOOL CUserAccountEditDlg::PreTranslateMessage( MSG* pMsg )
{
	if(pMsg->message==WM_KEYDOWN && pMsg->wParam==VK_ESCAPE) 
	{ 
		pMsg->wParam=NULL;                                  
	} 

	if(pMsg->message == WM_LBUTTONDOWN && pMsg->hwnd == this->GetSafeHwnd())
	{
		this->SendMessage(WM_NCLBUTTONDOWN,HTCAPTION);

		return 1;
	}

	return CDialog::PreTranslateMessage(pMsg);
}

void CUserAccountEditDlg::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialog::OnShowWindow(bShow, nStatus);

	if(bShow)
	{
		CString DlgName = "UserAccountEditDlg";

		std::vector<CString>ButtonList;
		std::vector<CString>StaticList;

		ButtonList = LanguageCtrl->GetInterfaceButtonNameList(DlgName, (UINT)m_LanguageType);
		StaticList = LanguageCtrl->GetInterfaceStaticNameList(DlgName, (UINT)m_LanguageType);

		this->GetDlgItem(IDOK)->SetWindowText(ButtonList.at(0));
		this->GetDlgItem(IDCANCEL)->SetWindowText(ButtonList.at(1));

		//更換顯示
		this->GetDlgItem(IDC_STATIC_ACCOUNT_NAME)->SetWindowText(StaticList.at(0));
		this->GetDlgItem(IDC_STATIC_ACCOUNT_ID)->SetWindowText(StaticList.at(1));
		this->GetDlgItem(IDC_STATIC_ACCOUNT_PASSWORD)->SetWindowText(StaticList.at(2));
		this->GetDlgItem(IDC_STATIC_ACCOUNT_PASSWORD2)->SetWindowText(StaticList.at(3));
		this->GetDlgItem(IDC_STATIC_ACCOUNT_LEVEL)->SetWindowText(StaticList.at(4));

		GetDlgItem(IDC_EDIT_USER_NAME)->SetWindowText("");
		GetDlgItem(IDC_EDIT_USER_ACCOUNT)->SetWindowText("");
		GetDlgItem(IDC_EDIT_USER_PASSWORD)->SetWindowText("");
		GetDlgItem(IDC_EDIT_USER_PASSWORD_CHECK)->SetWindowText("");
		m_UserLevelSel.SetCurSel(2);
	}

	
}

void CUserAccountEditDlg::OnBnClickedOk()
{
	m_sUserName = GetDlgItemString(this->GetSafeHwnd(), IDC_EDIT_USER_NAME);
	m_sUserID = GetDlgItemString(this->GetSafeHwnd(), IDC_EDIT_USER_ACCOUNT);
	m_sUserPassword = GetDlgItemString(this->GetSafeHwnd(), IDC_EDIT_USER_PASSWORD);
	CString sUserPasswordCheck = GetDlgItemString(this->GetSafeHwnd(), IDC_EDIT_USER_PASSWORD_CHECK);


	if(m_sUserID.GetLength() > 8)
	{
		AfxMessageBox("使用者ID超過範圍!\nUser ID Out of Range!");
		m_sUserName = "";
		m_sUserID = "";
		m_sUserPassword = "";
		return;
	}

	if(m_sUserPassword != sUserPasswordCheck)
	{
		AfxMessageBox("比對密碼錯誤\nCheck Password Fail");
		m_sUserName = "";
		m_sUserID = "";
		m_sUserPassword = "";
		return ;
	}

	switch(m_UserLevelSel.GetCurSel())
	{
	case 0:
		m_nUserLevel = 3;
		break;
	case 1:
		m_nUserLevel = 2;
		break;
	case 2:
		m_nUserLevel = 1;
		break;
	default:
		AfxMessageBox("請選擇安全及別\nPlease Select Level");
		m_sUserName = "";
		m_sUserID = "";
		m_sUserPassword = "";
		return;
		break;
	}

	CDialog::OnOK();
}

CString CUserAccountEditDlg::GetUserID()
{
	return m_sUserID;
}

CString CUserAccountEditDlg::GetUserPassword()
{
	return m_sUserPassword;
}

int CUserAccountEditDlg::GetUserLevel()
{
	return m_nUserLevel;
}

CString CUserAccountEditDlg::GetUserName()
{
	return m_sUserName;
}

long CUserAccountEditDlg::OnMessageChangeLang( WPARAM wparam, LPARAM lparam )
{

	CString DlgName = "UserAccountEditDlg";

	std::vector<CString>ButtonList;
	std::vector<CString>StaticList;

	ButtonList = LanguageCtrl->GetInterfaceButtonNameList(DlgName, (UINT)wparam);
	StaticList = LanguageCtrl->GetInterfaceStaticNameList(DlgName, (UINT)wparam);

	this->GetDlgItem(IDOK)->SetWindowText(ButtonList.at(0));
	this->GetDlgItem(IDCANCEL)->SetWindowText(ButtonList.at(1));

	//更換顯示
	this->GetDlgItem(IDC_STATIC_ACCOUNT_NAME)->SetWindowText(StaticList.at(0));
	this->GetDlgItem(IDC_STATIC_ACCOUNT_ID)->SetWindowText(StaticList.at(1));
	this->GetDlgItem(IDC_STATIC_ACCOUNT_PASSWORD)->SetWindowText(StaticList.at(2));
	this->GetDlgItem(IDC_STATIC_ACCOUNT_PASSWORD2)->SetWindowText(StaticList.at(3));
	this->GetDlgItem(IDC_STATIC_ACCOUNT_LEVEL)->SetWindowText(StaticList.at(4));


	return 0;
}

void CUserAccountEditDlg::SetLanguage( UINT nType )
{
	m_LanguageType = nType;
}


void CUserAccountEditDlg::OnDestroy()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState( ));
	CDialog::OnDestroy();

	// TODO: 在此加入您的訊息處理常式程式碼
}
