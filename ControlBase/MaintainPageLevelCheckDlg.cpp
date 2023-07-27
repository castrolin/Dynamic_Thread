// MaintainPageLevelCheckDlg.cpp : 實作檔
//

#include "stdafx.h"
#include "ControlBase.h"
#include "MaintainPageLevelCheckDlg.h"
#include "afxdialogex.h"


// CMaintainPageLevelCheckDlg 對話方塊

IMPLEMENT_DYNAMIC(CMaintainPageLevelCheckDlg, CDialog)

CMaintainPageLevelCheckDlg::CMaintainPageLevelCheckDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMaintainPageLevelCheckDlg::IDD, pParent)
{

}

CMaintainPageLevelCheckDlg::~CMaintainPageLevelCheckDlg()
{
}

void CMaintainPageLevelCheckDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	
	DDX_Control(pDX, IDC_COMBO_OPTION_MAINTAIN_USER_INFO_USER_ID, m_UserSel);
	DDX_Control(pDX, IDC_STATIC_OPTION_MAINTAIN_USER_INFO_GROUP, m_GroupBox);
}


BEGIN_MESSAGE_MAP(CMaintainPageLevelCheckDlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_OPTION_MAINTAIN_USER_INFO_YES, &CMaintainPageLevelCheckDlg::OnBnClickedButtonOptionMaintainUserInfoYes)
	ON_BN_CLICKED(IDC_BUTTON_OPTION_MAINTAIN_USER_INFO_CANCEL, &CMaintainPageLevelCheckDlg::OnBnClickedButtonOptionMaintainUserInfoCancel)
	ON_CBN_SETFOCUS(IDC_COMBO_OPTION_MAINTAIN_USER_INFO_USER_ID, &CMaintainPageLevelCheckDlg::OnCbnSetfocusComboOptionMaintainUserInfoUserId)
END_MESSAGE_MAP()


// CMaintainPageLevelCheckDlg 訊息處理常式
BOOL CMaintainPageLevelCheckDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	TCHAR tcPath[MAX_PATH];
	TCHAR tcDriver[MAX_PATH];
	TCHAR tcDir[MAX_PATH];

	::GetModuleFileName(AfxGetInstanceHandle(), tcPath, MAX_PATH);
	_tsplitpath(tcPath, tcDriver, tcDir, NULL, NULL);
	m_Project_Path.Format("%s%s", tcDriver, tcDir);

	m_GroupBox.SetXPGroupStyle(CXPGroupBox::XPGB_FRAME);
	m_GroupBox.SetBackgroundColor(RGB(180, 230, 30), ::GetSysColor(COLOR_BTNFACE));
	m_GroupBox.SetBorderColor(RGB(180, 230, 30));
	m_GroupBox.SetBorderWidth(5);

	m_GroupBox.SetFontBold(TRUE);
	m_GroupBox.SetAlignment(SS_CENTER);

	return TRUE;
}

BOOL CMaintainPageLevelCheckDlg::PreTranslateMessage( MSG* pMsg )
{
	if(pMsg->message==WM_KEYDOWN && pMsg->wParam==VK_ESCAPE) 
	{ 
		//OnBnClickedButtonProductModifyLevelCheckCancel();                          
	} 
	else if(pMsg->message == WM_LBUTTONDOWN && pMsg->hwnd == this->GetSafeHwnd())
	{
		this->SendMessage(WM_NCLBUTTONDOWN,HTCAPTION);

		return 1;
	}
	else if(pMsg->message==WM_KEYDOWN && pMsg->wParam==VK_RETURN) 
	{
		//OnBnClickedButtonProductModifyLevelCheckYes();
		OnOK();
		return FALSE;
	}

	return CDialog::PreTranslateMessage(pMsg);
}

void CMaintainPageLevelCheckDlg::OnBnClickedButtonOptionMaintainUserInfoYes()
{
	int nIndex = m_UserSel.GetCurSel();

	CString sDataPath = m_Project_Path + "CtrlPrms\\OperatorID.ini";

	m_OperatorID = GetPrivateProfileString("OperatorAccount", FormatString("UserID_%04d", nIndex), "NA", sDataPath);

	m_OperatorName = GetPrivateProfileString("OperatorAccount", FormatString("UserName_%04d", nIndex), "NA", sDataPath);

	GetDlgItem(IDC_EDIT_OPTION_MAINTAIN_USER_INFO_PASSWORD)->GetWindowTextA(m_PassWord);

	GetDlgItem(IDC_EDIT_OPTION_MAINTAIN_USER_INFO_PASSWORD)->SetWindowTextA("");

	if(GetAccessRet() == 0)
	{
		AfxMessageBox("ID或是密碼錯誤\nID or Password Error!");
	}

	OnOK();
}

void CMaintainPageLevelCheckDlg::OnBnClickedButtonOptionMaintainUserInfoCancel()
{
	OnCancel();
}

UINT CMaintainPageLevelCheckDlg::GetAccessRet()
{
	UINT nRet = 0;
	UINT nUserNum;
	CString FileName;

	FileName.Format("%sCtrlPrms\\OperatorID.ini", m_Project_Path);

	nUserNum = GetPrivateProfileInt("OperatorAccount","UserNum", 0, FileName);

	for(UINT x = 0; x < nUserNum;  x++)
	{
		CString sSubKey;
		sSubKey.Format("UserID_%04d", x);

		CString FindedName = GetPrivateProfileString("OperatorAccount", sSubKey, "", FileName);

		if(m_OperatorID == FindedName)
		{
			sSubKey.Format("UserPassWord_%04d", x);
			CString FindedPassWord = GetPrivateProfileString("OperatorAccount", sSubKey, "", FileName);

			if(m_PassWord == FindedPassWord)
			{
				sSubKey.Format("UserClass_%04d", x);
				nRet = GetPrivateProfileInt("OperatorAccount", sSubKey, 0, FileName);
				break;
			}
		}
	}

	m_AccessClass = nRet;

	return nRet;
}

CString CMaintainPageLevelCheckDlg::GetOperatorID()
{
	return m_OperatorID;
}

CString CMaintainPageLevelCheckDlg::GetOperatorName()
{
	return m_OperatorName;
}

UINT CMaintainPageLevelCheckDlg::GetAccessClass()
{
	return m_AccessClass;
}

void CMaintainPageLevelCheckDlg::OnCbnSetfocusComboOptionMaintainUserInfoUserId()
{
	m_UserSel.ResetContent();

	CString sDataPath = m_Project_Path + "CtrlPrms\\OperatorID.ini";
	int nAccountNum = GetPrivateProfileInt("OperatorAccount", "UserNum", 0, sDataPath);

	for(int x = 0; x < nAccountNum; x ++)
	{
		CString sUserName = GetPrivateProfileString("OperatorAccount", FormatString("UserName_%04d", x), "NA", sDataPath);
		m_UserSel.AddString(sUserName);
	}
}
