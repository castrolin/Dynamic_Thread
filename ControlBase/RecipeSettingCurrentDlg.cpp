// RecipeSettingDlg.cpp : 實作檔
//

#include "stdafx.h"
#include "ControlBase.h"
#include "RecipeSettingCurrentDlg.h"
#include "afxdialogex.h"


// CRecipeSettingDlg 對話方塊

IMPLEMENT_DYNAMIC(CRecipeSettingCurrentDlg, CDialog)

	CRecipeSettingCurrentDlg::CRecipeSettingCurrentDlg(CWnd* pParent, CString RecipePATH, CGetRecipe *pSystemRecipe)
	: CDialog(CRecipeSettingCurrentDlg::IDD, pParent), m_pRecipe(RecipePATH)
{
	HINSTANCE ORG = AfxGetResourceHandle();
#ifdef _DEBUG
	HINSTANCE ControlBaseInstanceHandle = GetModuleHandle("..\\Debug\\ControlBase.dll");
#elif
	HINSTANCE ControlBaseInstanceHandle = GetModuleHandle("..\\Release\\ControlBase.dll");
#endif
	AfxSetResourceHandle(ControlBaseInstanceHandle);

	this->Create(IDD_DIALOG_OPTION_RECIPE_CURRENT, pParent);

	m_pSystemRecipe = pSystemRecipe;

	m_RecipePATH = RecipePATH;

	m_Base_Row = 0;
	m_Base_Col = 0;

	m_Recipe_Row = 0;
	m_Recipe_Col = 0;

	AfxSetResourceHandle(ORG);

}

CRecipeSettingCurrentDlg::~CRecipeSettingCurrentDlg()
{
}

void CRecipeSettingCurrentDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_RECIPE_PARAM, m_ParamList);

}

BEGIN_MESSAGE_MAP(CRecipeSettingCurrentDlg, CDialog)
	ON_WM_SHOWWINDOW()
	ON_MESSAGE(CWM_SYS_UPDATE_LANG, OnMessageChangeLang)

	ON_NOTIFY(NM_CLICK, IDC_LIST_RECIPE_PARAM, OnNMClickGrid)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_RECIPE_PARAM, OnNMDbClickGrid)

	ON_BN_CLICKED(IDC_BUTTON_SYSTEM_RECIPE_RELOAD, &CRecipeSettingCurrentDlg::OnBnClickedButtonSystemRecipeReload)
	ON_BN_CLICKED(IDC_BUTTON_SYSTEM_RECIPE_SAVE, &CRecipeSettingCurrentDlg::OnBnClickedButtonSystemRecipeSave)

END_MESSAGE_MAP()

// CRecipeSettingDlg 訊息處理常式
BOOL CRecipeSettingCurrentDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	CFont * pFont = GetFont();
	LOGFONT lf;
	pFont->GetLogFont( &lf );
	lf.lfWeight = FW_BOLD;
	m_Font.CreateFontIndirect( &lf );

	SendMessageToDescendants( WM_SETFONT, (WPARAM) m_Font.m_hObject );

	m_ParamList.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES |LVS_EX_FLATSB);
	m_ParamList.InsertColumn(0,	_T("No."),	LVCFMT_CENTER, 40, 2);
	m_ParamList.InsertColumn(1,	_T("Parameters"),	LVCFMT_LEFT, 140, 2);
	m_ParamList.InsertColumn(2,	_T("Value"),	LVCFMT_LEFT, 330, 2);

	for(int x = 0; x < 17; x ++)
		m_ParamList.InsertItem(x, FormatString("%02d", x + 1));

	m_ParamList.SetItemText(0, 1, "RecipeName");
	m_ParamList.SetItemText(1, 1, "Comment");
	m_ParamList.SetItemText(2, 1, "nThreshold");
	m_ParamList.SetItemText(3, 1, "nBlur");
	m_ParamList.SetItemText(4, 1, "nOrgPosPixel_LX");
	m_ParamList.SetItemText(5, 1, "nOrgPosPixel_LY");
	m_ParamList.SetItemText(6, 1, "nOrgPosPixel_RX");
	m_ParamList.SetItemText(7, 1, "nOrgPosPixel_RY");
	m_ParamList.SetItemText(8, 1, "nThreshold_Sticker");
	m_ParamList.SetItemText(9, 1, "nBlur_Sticker");
	m_ParamList.SetItemText(10, 1, "nOrgPosPixel_Sticker_LX");
	m_ParamList.SetItemText(11, 1, "nOrgPosPixel_Sticker_LY");
	m_ParamList.SetItemText(12, 1, "nOrgPosPixel_Sticker_RX");
	m_ParamList.SetItemText(13, 1, "nOrgPosPixel_Sticker_RY");
	m_ParamList.SetItemText(14, 1, "Offset_X");
	m_ParamList.SetItemText(15, 1, "Offset_Y");
	m_ParamList.SetItemText(16, 1, "Offset_T");

	RECT rect;
	rect.left = 0;
	rect.top = 0;
	rect.bottom = 5;
	rect.right = 5;

	m_Base_ComboBoxItem.Create(WS_CHILD| CBS_DROPDOWN | CBS_HASSTRINGS | WS_VSCROLL, rect, GetDlgItem(IDC_LIST_RECIPE_PARAM), IDC_MY_LIST_COMBOBOX);
	m_Base_ComboBoxItem.SetFont(&m_Font);

	m_Base_EditItem.Create(WS_CHILD | ES_LEFT | WS_BORDER | ES_AUTOHSCROLL | ES_WANTRETURN | ES_MULTILINE, rect, GetDlgItem(IDC_LIST_RECIPE_PARAM), IDC_MY_LIST_EDITBOX);
	m_Base_EditItem.SetFont(&m_Font);

	return TRUE;
}

void CRecipeSettingCurrentDlg::OnShowWindow( BOOL bShow, UINT nStatus )
{
	CDialog::OnShowWindow(bShow, nStatus);

	if(bShow == TRUE)
	{

		GetDlgItem(IDC_EDIT_SYSTEM_RECIPE_NAME)->SetWindowText(FormatString("Current Rcipe: %s", m_pSystemRecipe->GetRecipeName()));

		//將目前機台Recipe複製到此DLG中的Recipe備用
		m_pRecipe = *m_pSystemRecipe;

		ShowRecipeData();

	}
	else
	{

	}
}

long CRecipeSettingCurrentDlg::OnMessageChangeLang( WPARAM wparam, LPARAM lparam )
{
	CString DlgName = "RecipeSettingCurrentDlg";

	std::vector<CString>ButtonList;
	std::vector<CString>StaticList;

	ButtonList = LanguageCtrl->GetInterfaceButtonNameList(DlgName, (UINT)wparam);
	StaticList = LanguageCtrl->GetInterfaceStaticNameList(DlgName, (UINT)wparam);

	GetDlgItem(IDC_BUTTON_SYSTEM_RECIPE_RELOAD)->SetWindowText(ButtonList.at(0));
	GetDlgItem(IDC_BUTTON_SYSTEM_RECIPE_SAVE)->SetWindowText(ButtonList.at(1));


	switch((UINT)wparam)
	{
	case SYSTEM_LANGUAGE_EN:
		m_ParamList.SetItemText(0, 1, "RecipeName");
		m_ParamList.SetItemText(1, 1, "Comment");
		m_ParamList.SetItemText(2, 1, "nThreshold");
		m_ParamList.SetItemText(3, 1, "nBlur");
		m_ParamList.SetItemText(4, 1, "nOrgPosPixel_LX");
		m_ParamList.SetItemText(5, 1, "nOrgPosPixel_LY");
		m_ParamList.SetItemText(6, 1, "nOrgPosPixel_RX");
		m_ParamList.SetItemText(7, 1, "nOrgPosPixel_RY");
		m_ParamList.SetItemText(8, 1, "nThreshold_Sticker");
		m_ParamList.SetItemText(9, 1, "nBlur_Sticker");
		m_ParamList.SetItemText(10, 1, "nOrgPosPixel_Sticker_LX");
		m_ParamList.SetItemText(11, 1, "nOrgPosPixel_Sticker_LY");
		m_ParamList.SetItemText(12, 1, "nOrgPosPixel_Sticker_RX");
		m_ParamList.SetItemText(13, 1, "nOrgPosPixel_Sticker_RY");
		m_ParamList.SetItemText(14, 1, "Offset_X");
		m_ParamList.SetItemText(15, 1, "Offset_Y");
		m_ParamList.SetItemText(16, 1, "Offset_T");

		break;

	case SYSTEM_LANGUAGE_CN:
		m_ParamList.SetItemText(0, 1, "參數名稱");
		m_ParamList.SetItemText(1, 1, "敘述");
		m_ParamList.SetItemText(2, 1, "二值化閥值");
		m_ParamList.SetItemText(3, 1, "高絲模糊");
		m_ParamList.SetItemText(4, 1, "左原點_座標X");
		m_ParamList.SetItemText(5, 1, "左原點_座標Y");
		m_ParamList.SetItemText(6, 1, "右原點_座標X");
		m_ParamList.SetItemText(7, 1, "右原點_座標Y");

		m_ParamList.SetItemText(8, 1, "二值化閥值_貼紙");
		m_ParamList.SetItemText(9, 1, "高絲模糊_貼紙");
		m_ParamList.SetItemText(10, 1, "左原點_貼紙_座標X");
		m_ParamList.SetItemText(11, 1, "左原點_貼紙_座標Y");
		m_ParamList.SetItemText(12, 1, "右原點_貼紙_座標X");
		m_ParamList.SetItemText(13, 1, "右原點_貼紙_座標Y");

		m_ParamList.SetItemText(14, 1, "Offset_X");
		m_ParamList.SetItemText(15, 1, "Offset_Y");
		m_ParamList.SetItemText(16, 1, "Offset_T");
		break;
	}



	return 0;

}

void CRecipeSettingCurrentDlg::OnNMClickGrid(NMHDR *pNMHDR, LRESULT *pResult)
{

	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);

	LVHITTESTINFO info;
	info.pt = pNMItemActivate->ptAction;

	int sel = m_ParamList.GetSelectionMark();

	if(m_Base_ComboBoxItem.IsWindowVisible())
	{
		m_Base_ComboBoxItem.ShowWindow(SW_HIDE);

		if(m_Base_Row != -1)
		{
			CString ItemText;
			m_Base_ComboBoxItem.GetLBText(m_Base_ComboBoxItem.GetCurSel(), ItemText);
			m_ParamList.SetItemText(m_Base_Row, m_Base_Col, ItemText);
			//::PostMessage(GetParent()->m_hWnd, MLSM_ITEMCHANGED, (WPARAM)MAKELONG(m_Row, m_Col), (LPARAM)this->m_hWnd);
		}

	}
	else if(m_Base_EditItem.IsWindowVisible())
	{
		m_Base_EditItem.ShowWindow(SW_HIDE);
		if(m_Base_Row != -1)
		{
			CString ItemText;
			m_Base_EditItem.GetWindowText(ItemText);
			m_ParamList.SetItemText(m_Base_Row, m_Base_Col, ItemText);

		}
	}

	if(sel  == -1 )
		return ;
	else
	{
		//UpdateUIParameter(sel);
	}

	*pResult = 0;

}

void CRecipeSettingCurrentDlg::OnNMDbClickGrid( NMHDR* pNMHDR, LRESULT* pResult )
{

	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);

	LVHITTESTINFO info;
	info.pt = pNMItemActivate->ptAction;

	if(m_ParamList.SubItemHitTest(&info) != -1)
	{
		m_Base_Row = info.iItem;
		m_Base_Col = info.iSubItem;
		CRect rect;
		CString Temp;

		CDiskObject DiskObject;
		CStringArray RecipeArray;

		CString m_sParamPath;
		CString RecipeName;

		m_ParamList.GetSubItemRect(info.iItem, info.iSubItem, LVIR_LABEL, rect);
		rect.top = rect.top - 1;
		rect.bottom = rect.top + 240;
		m_Base_ComboBoxItem.MoveWindow(rect);
		m_Base_ComboBoxItem.SetItemHeight(-1, 15);

		if (m_Base_Col==2)
		{

			m_ParamList.GetSubItemRect(info.iItem, info.iSubItem, LVIR_LABEL, rect);
			Temp = m_ParamList.GetItemText(info.iItem, info.iSubItem);
			m_Base_EditItem.SetWindowText(Temp);
			m_Base_EditItem.MoveWindow(&rect, TRUE);
			m_Base_EditItem.ShowWindow(SW_SHOW);
			m_Base_EditItem.SetFocus();

		}

	}

}

void CRecipeSettingCurrentDlg::OnBnClickedButtonSystemRecipeReload()
{
	m_pRecipe.ReloadRecipe();

	if(m_pRecipe.Recipe_Data.st_RecipeInfo.nRcipeID == m_pSystemRecipe->Recipe_Data.st_RecipeInfo.nRcipeID)
		m_pSystemRecipe->ReloadRecipe();

	ShowRecipeData();
}

void CRecipeSettingCurrentDlg::OnBnClickedButtonSystemRecipeSave()
{

	ShowSystemMessageBox("系統", "參數儲存中 ...", false);

	if(m_Base_ComboBoxItem.IsWindowVisible())
	{
		m_Base_ComboBoxItem.ShowWindow(SW_HIDE);

		if(m_Base_Row != -1)
		{
			CString ItemText;
			m_Base_ComboBoxItem.GetLBText(m_Base_ComboBoxItem.GetCurSel(), ItemText);
			m_ParamList.SetItemText(m_Base_Row, m_Base_Col, ItemText);
			//::PostMessage(GetParent()->m_hWnd, MLSM_ITEMCHANGED, (WPARAM)MAKELONG(m_Row, m_Col), (LPARAM)this->m_hWnd);
		}

	}
	else if(m_Base_EditItem.IsWindowVisible())
	{
		m_Base_EditItem.ShowWindow(SW_HIDE);
		if(m_Base_Row != -1)
		{
			CString ItemText;
			m_Base_EditItem.GetWindowText(ItemText);
			m_ParamList.SetItemText(m_Base_Row, m_Base_Col, ItemText);

		}
	}

	CTime time = CTime::GetCurrentTime();

	m_pRecipe.Recipe_Data.st_RecipeInfo.csAccessTime.Format("%04d/%02d/%02d/%02d:%02d" ,\
		time.GetYear() , \
		time.GetMonth() ,\
		time.GetDay() ,  \
		time.GetHour() , \
		time.GetMinute());

	if(atoi(m_ParamList.GetItemText(0, 2)) > 256)
	{
		ShowSystemMessageBox("系統", "二值話閥值超過範圍! \n 參數無法儲存!", true);
		return;
	}

	if(atoi(m_ParamList.GetItemText(1, 2)) != 0 && atoi(m_ParamList.GetItemText(1, 2)) % 2 == 0)
	{
		ShowSystemMessageBox("系統", "模糊數值需為奇數! \n 參數無法儲存!", true);
		return;
	}

	m_pRecipe.Recipe_Data.st_RecipeInfo.csRecipeName = m_ParamList.GetItemText(0, 2);
	m_pRecipe.Recipe_Data.st_RecipeInfo.csComment = m_ParamList.GetItemText(1, 2);
	m_pRecipe.Recipe_Data.st_RecipeData.nThreshold = atoi(m_ParamList.GetItemText(2, 2));
	m_pRecipe.Recipe_Data.st_RecipeData.nBlur = atoi(m_ParamList.GetItemText(3, 2));
	m_pRecipe.Recipe_Data.st_RecipeData.nOrgPosPixel_LX = atof(m_ParamList.GetItemText(4, 2));
	m_pRecipe.Recipe_Data.st_RecipeData.nOrgPosPixel_LY = atof(m_ParamList.GetItemText(5, 2));
	m_pRecipe.Recipe_Data.st_RecipeData.nOrgPosPixel_RX = atof(m_ParamList.GetItemText(6, 2));
	m_pRecipe.Recipe_Data.st_RecipeData.nOrgPosPixel_RY = atof(m_ParamList.GetItemText(7, 2));

	m_pRecipe.Recipe_Data.st_RecipeData.nThreshold_Sticker = atoi(m_ParamList.GetItemText(8, 2));
	m_pRecipe.Recipe_Data.st_RecipeData.nBlur_Sticker = atoi(m_ParamList.GetItemText(9, 2));
	m_pRecipe.Recipe_Data.st_RecipeData.nOrgPosPixel_Sticker_LX = atof(m_ParamList.GetItemText(10, 2));
	m_pRecipe.Recipe_Data.st_RecipeData.nOrgPosPixel_Sticker_LY = atof(m_ParamList.GetItemText(11, 2));
	m_pRecipe.Recipe_Data.st_RecipeData.nOrgPosPixel_Sticker_RX = atof(m_ParamList.GetItemText(12, 2));
	m_pRecipe.Recipe_Data.st_RecipeData.nOrgPosPixel_Sticker_RY = atof(m_ParamList.GetItemText(13, 2));

	m_pRecipe.Recipe_Data.st_RecipeData.Offset_mm_X = atof(m_ParamList.GetItemText(14, 2));
	m_pRecipe.Recipe_Data.st_RecipeData.Offset_mm_Y = atof(m_ParamList.GetItemText(15, 2));
	m_pRecipe.Recipe_Data.st_RecipeData.Offset_mm_T = atof(m_ParamList.GetItemText(16, 2));


	m_pRecipe.SaveRecipe();

	if(m_pRecipe.Recipe_Data.st_RecipeInfo.csRecipeName == m_pSystemRecipe->Recipe_Data.st_RecipeInfo.csRecipeName)
		m_pSystemRecipe->ReloadRecipe();

	ShowRecipeData();

	ShowSystemMessageBox("系統", "參數儲存中 ...", true);
}

void CRecipeSettingCurrentDlg::ShowRecipeData()
{

	GetDlgItem(IDC_EDIT_SYSTEM_RECIPE_NAME)->SetWindowText(m_pRecipe.GetRecipeName());

	m_ParamList.SetItemText(0, 2, m_pRecipe.Recipe_Data.st_RecipeInfo.csRecipeName);
	m_ParamList.SetItemText(1, 2, m_pRecipe.Recipe_Data.st_RecipeInfo.csComment);
	m_ParamList.SetItemText(2, 2, FormatString("%d", m_pRecipe.Recipe_Data.st_RecipeData.nThreshold));
	m_ParamList.SetItemText(3, 2, FormatString("%d", m_pRecipe.Recipe_Data.st_RecipeData.nBlur));
	m_ParamList.SetItemText(4, 2, FormatString("%.3lf", m_pRecipe.Recipe_Data.st_RecipeData.nOrgPosPixel_LX));
	m_ParamList.SetItemText(5, 2, FormatString("%.3lf", m_pRecipe.Recipe_Data.st_RecipeData.nOrgPosPixel_LY));
	m_ParamList.SetItemText(6, 2, FormatString("%.3lf", m_pRecipe.Recipe_Data.st_RecipeData.nOrgPosPixel_RX));
	m_ParamList.SetItemText(7, 2, FormatString("%.3lf", m_pRecipe.Recipe_Data.st_RecipeData.nOrgPosPixel_RY));

	m_ParamList.SetItemText(8, 2, FormatString("%d", m_pRecipe.Recipe_Data.st_RecipeData.nThreshold_Sticker));
	m_ParamList.SetItemText(9, 2, FormatString("%d", m_pRecipe.Recipe_Data.st_RecipeData.nBlur_Sticker));
	m_ParamList.SetItemText(10, 2, FormatString("%.3lf", m_pRecipe.Recipe_Data.st_RecipeData.nOrgPosPixel_Sticker_LX));
	m_ParamList.SetItemText(11, 2, FormatString("%.3lf", m_pRecipe.Recipe_Data.st_RecipeData.nOrgPosPixel_Sticker_LY));
	m_ParamList.SetItemText(12, 2, FormatString("%.3lf", m_pRecipe.Recipe_Data.st_RecipeData.nOrgPosPixel_Sticker_RX));
	m_ParamList.SetItemText(13, 2, FormatString("%.3lf", m_pRecipe.Recipe_Data.st_RecipeData.nOrgPosPixel_Sticker_RY));

	m_ParamList.SetItemText(14, 2, FormatString("%.3lf", m_pRecipe.Recipe_Data.st_RecipeData.Offset_mm_X));
	m_ParamList.SetItemText(15, 2, FormatString("%.3lf", m_pRecipe.Recipe_Data.st_RecipeData.Offset_mm_Y));
	m_ParamList.SetItemText(16, 2, FormatString("%.3lf", m_pRecipe.Recipe_Data.st_RecipeData.Offset_mm_T));
}

void CRecipeSettingCurrentDlg::CopyPatternOnForAll( CString SourcePattern)
{
	CDiskObject DiskObject;

	CString TargetPath_RCP = Project_Path + "Recipe\\";
	CString SourcePath_RCP = Project_Path + "Recipe\\" + SourcePattern + ".rcp";

	CString TargetPath_PTN = Project_Path + "Recipe\\MarkSearchProc_Sticker\\";
	CString SourcePath_L_PTN = Project_Path + "Recipe\\MarkSearchProc_Sticker\\" + SourcePattern + "_L.ptn";
	CString SourcePath_L_BMP = Project_Path + "Recipe\\MarkSearchProc_Sticker\\" + SourcePattern + "_L.bmp";
	CString SourcePath_R_PTN = Project_Path + "Recipe\\MarkSearchProc_Sticker\\" + SourcePattern + "_R.ptn";
	CString SourcePath_R_BMP = Project_Path + "Recipe\\MarkSearchProc_Sticker\\" + SourcePattern + "_R.bmp";


	for(int x = 1; x <= 200; x ++)
	{
		CString TargetPath_RCP_Name = FormatString("Work%03d.rcp", x);
		DiskObject.CopyFile(SourcePath_RCP, TargetPath_RCP, TargetPath_RCP_Name);


		CString TargetPath_L_PTN = FormatString("Work%03d_L.ptn", x);
		CString TargetPath_L_BMP = FormatString("Work%03d_L.bmp", x);

		CString TargetPath_R_PTN = FormatString("Work%03d_R.ptn", x);
		CString TargetPath_R_BMP = FormatString("Work%03d_R.bmp", x);

		DiskObject.CopyFile(SourcePath_L_PTN, TargetPath_PTN, TargetPath_L_PTN);
		DiskObject.CopyFile(SourcePath_L_BMP, TargetPath_PTN, TargetPath_L_BMP);

		DiskObject.CopyFile(SourcePath_R_PTN, TargetPath_PTN, TargetPath_R_PTN);
		DiskObject.CopyFile(SourcePath_R_BMP, TargetPath_PTN, TargetPath_R_BMP);

		Delay(100);
		CGetRecipe GetRecipe(Project_Path);

		GetRecipe.LoadRecipe(TargetPath_RCP_Name);

		GetRecipe.Recipe_Data.st_RecipeInfo.csRecipeName = TargetPath_RCP_Name;
		GetRecipe.Recipe_Data.st_RecipeInfo.nRcipeID = x;

		GetRecipe.SaveRecipe();

	}

}
