// PatternOrgSaveDlg.cpp : 實作檔
//

#include "stdafx.h"
#include "PatternOrgSaveDlg.h"

// CPatternOrgSaveDlg 對話方塊

IMPLEMENT_DYNAMIC(CPatternOrgSaveDlg, CDialog)

CPatternOrgSaveDlg::CPatternOrgSaveDlg(CString PatternName, double Org_X, double Org_Y, CWnd* pParent)
	: CDialog(CPatternOrgSaveDlg::IDD, pParent)
{
	m_PattternName = PatternName;
	m_NewOrg_X = Org_X;
	m_NewOrg_Y = Org_Y;
}

CPatternOrgSaveDlg::~CPatternOrgSaveDlg()
{
}

void CPatternOrgSaveDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_PATTERN_ORG_SAVE_GROUP, m_GroupBox);
	DDX_Control(pDX , IDC_LIST_PATTERN_ORG_SAVE, m_RecipeList);
}


BEGIN_MESSAGE_MAP(CPatternOrgSaveDlg, CDialog)
	ON_WM_SHOWWINDOW()
	ON_BN_CLICKED(IDOK, &CPatternOrgSaveDlg::OnBnClickedOk)
END_MESSAGE_MAP()

BOOL CPatternOrgSaveDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	CFont * pFont = GetFont();
	LOGFONT lf;
	pFont->GetLogFont( &lf );
	lf.lfWeight = FW_BOLD;
	m_Font.CreateFontIndirect( &lf );

	SendMessageToDescendants( WM_SETFONT,
		(WPARAM) m_Font.m_hObject );

	//GetDlgItem(IDC_STATIC_MESSAGE)->SetParent(m_GroupBox.FromHandle(m_GroupBox.GetSafeHwnd()));

	m_GroupBox.SetXPGroupStyle(CXPGroupBox::XPGB_FRAME);
	m_GroupBox.SetBackgroundColor(RGB(180, 230, 30), ::GetSysColor(COLOR_BTNFACE));
	m_GroupBox.SetBorderColor(RGB(180, 230, 30));
	m_GroupBox.SetBorderWidth(5);

	m_GroupBox.SetFontBold(TRUE);
	m_GroupBox.SetAlignment(SS_CENTER);

	m_RecipeList.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES | LVS_EX_FLATSB | LVS_EX_CHECKBOXES);
	m_RecipeList.InsertColumn(0,	_T(""),	LVCFMT_CENTER, 22, 2);
	m_RecipeList.InsertColumn(1,	_T("No."),	LVCFMT_CENTER, 40, 2);
	m_RecipeList.InsertColumn(2,	_T("RecipeName"),	LVCFMT_LEFT, 150, 2);
	m_RecipeList.InsertColumn(3,	_T("Org_X"),	LVCFMT_LEFT, 100, 2);
	m_RecipeList.InsertColumn(4,	_T("Org_Y"),	LVCFMT_LEFT, 100, 2);

	return TRUE;
}

// CMessageBox 訊息處理常式


void CPatternOrgSaveDlg::OnShowWindow( BOOL bShow, UINT nStatus )
{
	CDialog::OnShowWindow(bShow, nStatus);

	if(bShow == TRUE)
	{
		CDiskObject DiskObject;
		m_FileArray.RemoveAll();
		m_FindArray.RemoveAll();
		m_RecipeList.DeleteAllItems();


		DiskObject.EnumFilesInDirectory(Project_Path + "/Recipe", m_FileArray, 1);
		int nIndex = 0;

		for(int x = 0; x < m_FileArray.GetCount(); x ++)
		{
			

			CString RecipeFilePath = m_FileArray.GetAt(x);
			int XXX= RecipeFilePath.ReverseFind('\\');

			CString RecipeName = RecipeFilePath.Mid(XXX + 1, RecipeFilePath.GetLength() - XXX);

			CString sPattern = GetPrivateProfileString("RecipeData","PatternName", "", RecipeFilePath);
			if(sPattern.Compare(m_PattternName) == 0)
			{
				int OldOrg_X = GetPrivateProfileInt("RecipeData","nOrgPosPixel_X", 0, RecipeFilePath) ;
				int OldOrg_Y = GetPrivateProfileInt("RecipeData","nOrgPosPixel_Y", 0, RecipeFilePath) ;

				m_FindArray.Add(RecipeName);
				m_RecipeList.InsertItem(nIndex, "");
				m_RecipeList.SetItemText(nIndex, 1, FormatString("%02d", nIndex + 1));
				m_RecipeList.SetItemText(nIndex, 2, RecipeName);
				m_RecipeList.SetItemText(nIndex, 3, FormatString("%d", OldOrg_X));
				m_RecipeList.SetItemText(nIndex, 4, FormatString("%d", OldOrg_Y));

				nIndex ++;
			}
		}

	}
	else
	{
	}
}

void CPatternOrgSaveDlg::OnBnClickedOk()
{
	for(int x = 0; x < m_RecipeList.GetItemCount(); x ++)
	{
		if(m_RecipeList.GetCheck(x) == BST_CHECKED)
		{
			CString sRecipeName = m_RecipeList.GetItemText(x, 2);
			CString sRecipeFilePath = Project_Path + "\\Recipe\\" + sRecipeName;

			WritePrivateProfileString("RecipeData","nOrgPosPixel_X" , FormatString("%d", (int)m_NewOrg_X) , sRecipeFilePath );
			WritePrivateProfileString("RecipeData","nOrgPosPixel_Y" , FormatString("%d", (int)m_NewOrg_Y) , sRecipeFilePath );
		}
	}


	ProcessRecipe->ReloadRecipe();

	CDialog::OnOK();
}
