// UserAccountDlg.cpp : 實作檔
//

#include "stdafx.h"
#include "UserAccountDlg.h"
#include "afxdialogex.h"


// CUserAccountDlg 對話方塊

IMPLEMENT_DYNAMIC(CUserAccountDlg, CDialog)

CUserAccountDlg::CUserAccountDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CUserAccountDlg::IDD, pParent)
{
	HINSTANCE ORG = AfxGetResourceHandle();
#ifdef _DEBUG
	HINSTANCE ControlBaseInstanceHandle = GetModuleHandle("..\\Debug\\ControlBase.dll");
#elif
	HINSTANCE ControlBaseInstanceHandle = GetModuleHandle("..\\Release\\ControlBase.dll");
#endif
	AfxSetResourceHandle(ControlBaseInstanceHandle);

	this->Create(IDD_DIALOG_OPTION_ACCOUNT, pParent);

	AfxSetResourceHandle(ORG);
	
}

CUserAccountDlg::~CUserAccountDlg()
{
}

void CUserAccountDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_OPTION_ACCOUNT, m_AccountList);
}


BEGIN_MESSAGE_MAP(CUserAccountDlg, CDialog)
	ON_WM_SHOWWINDOW()
	ON_MESSAGE(CWM_SYS_UPDATE_LANG, OnMessageChangeLang)

	ON_BN_CLICKED(IDC_BUTTON_ACCOUNT_ADD, &CUserAccountDlg::OnBnClickedButtonAccountAdd)
	ON_BN_CLICKED(IDC_BUTTON_ACCOUNT_DELETE, &CUserAccountDlg::OnBnClickedButtonAccountDelete)
	ON_BN_CLICKED(IDC_BUTTON_ACCOUNT_RESET, &CUserAccountDlg::OnBnClickedButtonAccountReset)
	ON_BN_CLICKED(IDC_BUTTON_ACCOUNT_SET, &CUserAccountDlg::OnBnClickedButtonAccountSet)

	ON_NOTIFY(NM_CLICK, IDC_LIST_OPTION_ACCOUNT, &CUserAccountDlg::OnPointListCtrlClick)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_OPTION_ACCOUNT, &CUserAccountDlg::OnPointListCtrlDbClick)

END_MESSAGE_MAP()

// CUserAccountDlg 訊息處理常式
BOOL CUserAccountDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	CFont * pFont = GetFont();
	LOGFONT lf;
	pFont->GetLogFont( &lf );
	lf.lfWeight = FW_BOLD;
	m_Font.CreateFontIndirect( &lf );

	SendMessageToDescendants( WM_SETFONT, (WPARAM) m_Font.m_hObject );

	m_AccountList.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES |LVS_EX_FLATSB);
	m_AccountList.InsertColumn(0, "No.", LVCFMT_CENTER, 60);
	m_AccountList.InsertColumn(1, "Name", LVCFMT_CENTER, 150);
	m_AccountList.InsertColumn(2, "ID", LVCFMT_CENTER, 150);
	m_AccountList.InsertColumn(3, "Password", LVCFMT_CENTER, 150);
	m_AccountList.InsertColumn(4, "Level", LVCFMT_CENTER, 60);

	RECT rect;
	rect.left = 0;
	rect.top = 0;
	rect.bottom = 15;
	rect.right = 200;

	m_Base_EditItem.Create(WS_CHILD | ES_LEFT | WS_BORDER | ES_AUTOHSCROLL | ES_WANTRETURN | ES_MULTILINE, rect, GetDlgItem(IDC_LIST_OPTION_ACCOUNT), IDC_MY_LIST_EDITBOX);
	m_Base_EditItem.SetFont(&m_Font, TRUE);

	m_Base_ComboBoxItem.Create(WS_CHILD| CBS_DROPDOWN | CBS_HASSTRINGS | CBS_DROPDOWNLIST | WS_VSCROLL, rect, GetDlgItem(IDC_LIST_OPTION_ACCOUNT), IDC_MY_LIST_COMBOBOX);
	m_Base_ComboBoxItem.SetFont(&m_Font);

	return TRUE;
}

BOOL CUserAccountDlg::PreTranslateMessage( MSG* pMsg )
{
	if(pMsg->message==WM_KEYDOWN)
	{ 
		if(pMsg->wParam == VK_RETURN && m_Base_EditItem.GetFocus() != NULL)
		{

			if(m_Base_EditItem.IsWindowVisible())
			{
				m_Base_EditItem.ShowWindow(0);
				if(m_Base_Row != -1)
				{
					int Row = m_Base_Row;
					CString ItemText;
					m_Base_EditItem.GetWindowText(ItemText);
					m_AccountList.SetItemText(Row, m_Base_Col, ItemText);
					//::PostMessage(GetParent()->m_hWnd, MLSM_ITEMCHANGED, (WPARAM)MAKELONG(m_Row, m_Col), (LPARAM)this->m_hWnd);
				}
			}

			m_Base_Row = m_Base_Col = -1;

			pMsg->wParam=NULL;
		}

	} 
	else if(pMsg->wParam==VK_ESCAPE) 
	{
		pMsg->wParam=NULL;
	}

	return CDialog::PreTranslateMessage(pMsg);
}

void CUserAccountDlg::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialog::OnShowWindow(bShow, nStatus);

	if(bShow)
	{
		LoadAccountData();
	}
}

void CUserAccountDlg::OnPointListCtrlClick(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);

	LVHITTESTINFO info;
	info.pt = pNMItemActivate->ptAction;


	if(m_Base_EditItem.IsWindowVisible())
	{
		m_Base_EditItem.ShowWindow(0);
		if(m_Base_Row != -1)
		{
			
			int Row = m_Base_Row;
			CString ItemText;
			m_Base_EditItem.GetWindowText(ItemText);
			m_AccountList.SetItemText(Row, m_Base_Col, ItemText);
			//::PostMessage(GetParent()->m_hWnd, MLSM_ITEMCHANGED, (WPARAM)MAKELONG(m_Row, m_Col), (LPARAM)this->m_hWnd);

		}
	}

	if(m_Base_ComboBoxItem.IsWindowVisible())
	{
		m_Base_ComboBoxItem.ShowWindow(0);
		if(m_Base_Row != -1)
		{
			CString ItemText;
			m_Base_ComboBoxItem.GetLBText(m_Base_ComboBoxItem.GetCurSel(), ItemText);
			m_AccountList.SetItemText(m_Base_Row, m_Base_Col, ItemText);
			//::PostMessage(GetParent()->m_hWnd, MLSM_ITEMCHANGED, (WPARAM)MAKELONG(m_Row, m_Col), (LPARAM)this->m_hWnd);
		}
	}

	m_Base_Row = m_Base_Col = -1;

}

void CUserAccountDlg::OnPointListCtrlDbClick(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);

	LVHITTESTINFO info;
	info.pt = pNMItemActivate->ptAction;


	if(m_AccountList.SubItemHitTest(&info) != -1)
	{
		m_Base_Row = info.iItem;
		m_Base_Col = info.iSubItem;
		CRect rect;
		CString Temp;


		switch(m_Base_Col)
		{
		case 0:
			break;

		case 1:
		case 2:

			/*m_AccountList.GetSubItemRect(info.iItem, info.iSubItem, LVIR_LABEL, rect);
			Temp = m_AccountList.GetItemText(info.iItem, info.iSubItem);
			m_Base_EditItem.SetWindowText(Temp);
			m_Base_EditItem.MoveWindow(&rect, TRUE);
			m_Base_EditItem.ShowWindow(1);
			m_Base_EditItem.SetFocus();*/
			break;

		case 3:
			break;
		case 4:

			m_AccountList.GetSubItemRect(info.iItem, info.iSubItem, LVIR_LABEL, rect);
			Temp = m_AccountList.GetItemText(info.iItem, info.iSubItem);
			rect.bottom = rect.top + 240;
			m_Base_ComboBoxItem.ResetContent();
			m_Base_ComboBoxItem.MoveWindow(rect);
			
			m_Base_ComboBoxItem.AddString("RD");
			m_Base_ComboBoxItem.AddString("EG");
			m_Base_ComboBoxItem.AddString("OP");
			
			if(Temp == "RD")
				m_Base_ComboBoxItem.SetCurSel(0);
			else if(Temp == "EG")
				m_Base_ComboBoxItem.SetCurSel(1);
			else
				m_Base_ComboBoxItem.SetCurSel(2);

			m_Base_ComboBoxItem.ShowWindow(SW_SHOW);
			m_Base_ComboBoxItem.SetFocus();

			break;

		}
		
	}

}

bool CUserAccountDlg::CheckAccountData()
{
	int nCount = m_AccountList.GetItemCount();

	for(int x = 0; x < nCount; x ++)
	{
		if(m_AccountList.GetItemText(x , 1) == "")
			return false;

		if(m_AccountList.GetItemText(x , 2) == "")
			return false;

		if(m_AccountList.GetItemText(x , 3) == "")
			return false;
	}

	return true;
}

long CUserAccountDlg::OnMessageChangeLang( WPARAM wparam, LPARAM lparam )
{
	CString DlgName = "UserAccountDlg";

	std::vector<CString>ButtonList;
	std::vector<CString>StaticList;

	ButtonList = LanguageCtrl->GetInterfaceButtonNameList(DlgName, (UINT)wparam);
	StaticList = LanguageCtrl->GetInterfaceStaticNameList(DlgName, (UINT)wparam);

	//更換按鈕
	this->GetDlgItem(IDC_BUTTON_ACCOUNT_ADD)->SetWindowText(ButtonList.at(0));
	this->GetDlgItem(IDC_BUTTON_ACCOUNT_DELETE)->SetWindowText(ButtonList.at(1));
	this->GetDlgItem(IDC_BUTTON_ACCOUNT_RESET)->SetWindowText(ButtonList.at(2));
	this->GetDlgItem(IDC_BUTTON_ACCOUNT_SET)->SetWindowText(ButtonList.at(3));

	//更換List表頭
	CHeaderCtrl* m_Header=(CHeaderCtrl*)m_AccountList.GetDlgItem(0); 
	int nCount = m_Header->GetItemCount(); 

	for(int x = 0; x < nCount;  x++)
	{
		if(UINT(x + 1) > StaticList.size())
			break;

		LVCOLUMN lvCol;
		::ZeroMemory((void *)&lvCol, sizeof(LVCOLUMN));
		lvCol.mask=LVCF_TEXT;
		m_AccountList.GetColumn(x,&lvCol);

		lvCol.pszText = StaticList.at(x).GetBuffer(StaticList.at(x).GetLength());

		m_AccountList.SetColumn(x,&lvCol);

	}

	//通知子視窗變更語言
	UserAccountEditDlg.SetLanguage((UINT)wparam);

	return 0;

}

void CUserAccountDlg::OnBnClickedButtonAccountAdd()
{
	HINSTANCE ORG = AfxGetResourceHandle();
#ifdef _DEBUG
	HINSTANCE ControlBaseInstanceHandle = GetModuleHandle("..\\Debug\\ControlBase.dll");
#elif
	HINSTANCE ControlBaseInstanceHandle = GetModuleHandle("..\\Release\\ControlBase.dll");
#endif
	AfxSetResourceHandle(ControlBaseInstanceHandle);

	if(UserAccountEditDlg.DoModal() == IDOK)
	{
		int nCount = m_AccountList.GetItemCount();
		m_AccountList.InsertItem(nCount, FormatString("%04d", nCount + 1));
		CString UserName = UserAccountEditDlg.GetUserName();
		CString UserID = UserAccountEditDlg.GetUserID();
		CString UserPassword = UserAccountEditDlg.GetUserPassword();
		int UserLevel = UserAccountEditDlg.GetUserLevel();

		m_AccountList.SetItemText(nCount, 1, UserName);
		m_AccountList.SetItemText(nCount, 2, UserID);
		m_AccountList.SetItemText(nCount, 3, "●●●●●●●●");

		switch(UserLevel)
		{
		case 1:
			m_AccountList.SetItemText(nCount, 4, "OP");
			break;
		case 2:
			m_AccountList.SetItemText(nCount, 4, "EG");
			break;
		case 3:
			m_AccountList.SetItemText(nCount, 4, "RD");
			break;
		}
		
		m_UserPasswordList.push_back(UserPassword);
	}

	AfxSetResourceHandle(ORG);
}

void CUserAccountDlg::OnBnClickedButtonAccountDelete()
{
	int nIndex = m_AccountList.GetSelectionMark();

	if(nIndex == 0)
	{
		AfxMessageBox("預設帳號，無法刪除!\nDefault Account, can't delete!");
		return;
	}

	m_AccountList.DeleteItem(nIndex);
	m_UserPasswordList.erase(m_UserPasswordList.begin() + nIndex);

	int nCount = m_AccountList.GetItemCount();

	for(int x = 0; x < nCount; x ++)
	{
		m_AccountList.SetItemText(x, 0, FormatString("%04d", x + 1));
	}
}

void CUserAccountDlg::OnBnClickedButtonAccountReset()
{
	LoadAccountData();
}

void CUserAccountDlg::OnBnClickedButtonAccountSet()
{
	CString sDataPath = Project_Path + "CtrlPrms\\OperatorID.ini";

	int nAccountNum = m_AccountList.GetItemCount();
	WritePrivateProfileString("OperatorAccount", "UserNum", FormatString("%d", nAccountNum), sDataPath);

	for(int x = 0; x < nAccountNum; x ++)
	{
		CString sUserName = m_AccountList.GetItemText(x, 1);
		CString sUserID = m_AccountList.GetItemText(x, 2);
		CString sUserPassword = m_UserPasswordList.at(x);
		int nUserLevel = 0;

		if(m_AccountList.GetItemText(x, 4) == "RD")
			nUserLevel = 3;
		else if(m_AccountList.GetItemText(x, 4) == "EG")
			nUserLevel = 2;
		else
			nUserLevel = 1;

		WritePrivateProfileString("OperatorAccount", FormatString("UserName_%04d", x), sUserName, sDataPath);
		WritePrivateProfileString("OperatorAccount", FormatString("UserID_%04d", x), sUserID, sDataPath);
		WritePrivateProfileString("OperatorAccount", FormatString("UserPassWord_%04d", x), m_UserPasswordList.at(x), sDataPath);
		WritePrivateProfileString("OperatorAccount", FormatString("UserClass_%04d", x), FormatString("%d", nUserLevel), sDataPath);
	}

	AfxMessageBox("儲存帳號密碼完成\nSave Account and Password Success!");
}

bool CUserAccountDlg::LoadAccountData()
{
	CString sDataPath = Project_Path + "CtrlPrms\\OperatorID.ini";
	int nAccountNum = GetPrivateProfileInt("OperatorAccount", "UserNum", 0, sDataPath);

	m_AccountList.DeleteAllItems();
	m_UserPasswordList.clear();


	for(int x = 0; x < nAccountNum; x ++)
	{
		CString sUserName = GetPrivateProfileString("OperatorAccount", FormatString("UserName_%04d", x), "NA", sDataPath);
		CString sUserID = GetPrivateProfileString("OperatorAccount", FormatString("UserID_%04d", x), "NA", sDataPath);
		CString sUserPassword = GetPrivateProfileString("OperatorAccount", FormatString("UserPassWord_%04d", x), "NA", sDataPath);
		int nUserLevel = GetPrivateProfileInt("OperatorAccount", FormatString("UserClass_%04d", x), 0, sDataPath);

		m_AccountList.InsertItem(x, FormatString("%04d", x + 1));
		m_AccountList.SetItemText(x, 1, sUserName);
		m_AccountList.SetItemText(x, 2, sUserID);
		m_AccountList.SetItemText(x, 3, "●●●●●●●●");
		m_UserPasswordList.push_back(sUserPassword);
		
		switch(nUserLevel)
		{
		case 3:
			m_AccountList.SetItemText(x, 4, "RD");
			break;
		case 2:
			m_AccountList.SetItemText(x, 4, "EG");
			break;
		case 1:
			m_AccountList.SetItemText(x, 4, "OP");
			break;
		}
		
	}

	return true;

}
