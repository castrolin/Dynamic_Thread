// RecipeSettingDlg.cpp : 龟郎
//

#include "stdafx.h"
#include "ControlBase.h"
#include "RecipeListDlg.h"
#include "afxdialogex.h"


// CRecipeSettingDlg 癸杠よ遏

IMPLEMENT_DYNAMIC(CRecipeListDlg, CDialog)

	CRecipeListDlg::CRecipeListDlg(CWnd* pParent, CString RecipePATH, CGetRecipe *pProcessRecipe)
	: CDialog(CRecipeListDlg::IDD, pParent), m_pRecipe_Source(RecipePATH), m_pRecipe_Destination(RecipePATH)
{
	HINSTANCE ORG = AfxGetResourceHandle();
#ifdef _DEBUG
	HINSTANCE ControlBaseInstanceHandle = GetModuleHandle("..\\Debug\\ControlBase.dll");
#elif
	HINSTANCE ControlBaseInstanceHandle = GetModuleHandle("..\\Release\\ControlBase.dll");
#endif
	AfxSetResourceHandle(ControlBaseInstanceHandle);

	this->Create(IDD_DIALOG_OPTION_RECIPE_LIST, pParent);

	m_pProcessRecipe = pProcessRecipe;
	m_RecipePATH = RecipePATH;

	AfxSetResourceHandle(ORG);

}

CRecipeListDlg::~CRecipeListDlg()
{
}

void CRecipeListDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX , IDC_LIST_RECIPE_INFO, m_RecipeList);
	DDX_Control(pDX, IDC_COMBO_RECIPE_LIST_COPY_SOURCE, m_RecipeSourceSel);
	DDX_Control(pDX, IDC_COMBO_RECIPE_LIST_COPY_DESTINATION, m_RecipeDestinationSel);
}

BEGIN_MESSAGE_MAP(CRecipeListDlg, CDialog)
	ON_WM_SHOWWINDOW()
	ON_MESSAGE(CWM_SYS_UPDATE_LANG, OnMessageChangeLang)

	
	ON_BN_CLICKED(IDC_BUTTON_SYSTEM_RECIPE_RELOAD, &CRecipeListDlg::OnBnClickedButtonSystemRecipeReload)
	ON_BN_CLICKED(IDC_BUTTON_SYSTEM_RECIPE_SET, &CRecipeListDlg::OnBnClickedButtonSystemRecipeSet)

	ON_BN_CLICKED(IDC_BUTTON_SYSTEM_RECIPE_COPY, &CRecipeListDlg::OnBnClickedButtonSystemRecipeCopy)
	ON_CBN_DROPDOWN(IDC_COMBO_RECIPE_LIST_COPY_SOURCE, &CRecipeListDlg::OnCbnDropdownComboRecipeListCopySource)
	ON_CBN_DROPDOWN(IDC_COMBO_RECIPE_LIST_COPY_DESTINATION, &CRecipeListDlg::OnCbnDropdownComboRecipeListCopyDestination)
END_MESSAGE_MAP()

// CRecipeSettingDlg 癟矪瞶盽Α
BOOL CRecipeListDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	CFont * pFont = GetFont();
	LOGFONT lf;
	pFont->GetLogFont( &lf );
	lf.lfWeight = FW_BOLD;
	m_Font.CreateFontIndirect( &lf );

	SendMessageToDescendants( WM_SETFONT, (WPARAM) m_Font.m_hObject );

	m_RecipeList.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES |LVS_EX_FLATSB);
	m_RecipeList.InsertColumn(0,	_T("No."),	LVCFMT_CENTER, 40, 2);
	m_RecipeList.InsertColumn(1,	_T("Date"),	LVCFMT_LEFT, 140, 2);
	m_RecipeList.InsertColumn(2,	_T("RecipeName"),	LVCFMT_LEFT, 250, 2);
	m_RecipeList.InsertColumn(3,	_T("FileName"),	LVCFMT_LEFT, 250, 2);
	m_RecipeList.InsertColumn(4,	_T("Description"),	LVCFMT_LEFT, 480, 2);

	return TRUE;
}

void CRecipeListDlg::OnShowWindow( BOOL bShow, UINT nStatus )
{
	CDialog::OnShowWindow(bShow, nStatus);

	if(bShow == TRUE)
	{
		UpdateList();

		GetDlgItem(IDC_STATIC_SYSTEM_RECIPE_PATH)->SetWindowText(FormatString("Current Rcipe Path: %s", m_RecipePATH));


	}
	else
	{

	}
}

long CRecipeListDlg::OnMessageChangeLang( WPARAM wparam, LPARAM lparam )
{
	CString DlgName = "RecipeListDlg";

	std::vector<CString>ButtonList;
	std::vector<CString>StaticList;

	ButtonList = LanguageCtrl->GetInterfaceButtonNameList(DlgName, (UINT)wparam);
	StaticList = LanguageCtrl->GetInterfaceStaticNameList(DlgName, (UINT)wparam);

	GetDlgItem(IDC_BUTTON_SYSTEM_RECIPE_SET)->SetWindowText(ButtonList.at(0));
	GetDlgItem(IDC_BUTTON_SYSTEM_RECIPE_RELOAD)->SetWindowText(ButtonList.at(1));
	GetDlgItem(IDC_BUTTON_SYSTEM_RECIPE_COPY)->SetWindowText(ButtonList.at(2));

	LVCOLUMN lvCol;
	

	
	for(int x = 1; x < 5; x ++)
	{
		m_RecipeList.GetColumn(x,&lvCol);
		lvCol.pszText = StaticList.at(x - 1).GetBuffer(0);
		m_RecipeList.SetColumn(x,&lvCol);

		::ZeroMemory((void *)&lvCol, sizeof(LVCOLUMN));
		lvCol.mask=LVCF_TEXT;
	}

	return 0;

}

void CRecipeListDlg::UpdateList()
{
	CGetRecipe::RECIPE_INDEX_INFO info ;

	CString RecipeName, sz;
	int recipe_no;
	POSITION pos;

	CGetRecipe getRecipe(Project_Path);

	recipe_no = getRecipe.GetTotalRecipeName(cListrecipedata) ;
	pos = cListrecipedata.GetHeadPosition();

	m_RecipeList.DeleteAllItems();

	UINT nIndex = 0;

	for(int x = 0; x < recipe_no; x++)
	{
		RecipeName = cListrecipedata.GetNext(pos);
		if( !getRecipe.GetRecipeIndexInfo(RecipeName , info ) )
			continue;

		m_RecipeList.InsertItem(nIndex, FormatString("%02d", x + 1));
		m_RecipeList.SetItemText(nIndex, 1, info.csAccessTime);
		m_RecipeList.SetItemText(nIndex, 2, info.csRecipeName);
		m_RecipeList.SetItemText(nIndex, 3, info.csFileName);
		m_RecipeList.SetItemText(nIndex, 4, info.csComment);

		nIndex ++;
	}

}

void CRecipeListDlg::OnBnClickedButtonSystemRecipeReload()
{
	UpdateList();
}

void CRecipeListDlg::OnBnClickedButtonSystemRecipeSet()
{
	
	int nSelect = m_RecipeList.GetSelectionMark();
	CString FileName = m_RecipeList.GetItemText(nSelect, 3);

	if(ShowSystemQestionBox("╰参", FormatString("╰参盢ち传把计叫拜琌ち传把计:%s", FileName)) == IDCANCEL)
		return;

	if(m_pProcessRecipe->LoadRecipe(FileName) == false)
	{
		ShowSystemMessageBox("╰参", "ヘ夹把计更ア毖叫絋粄把计郎琌", true);
		return;
	}

	WritePrivateProfileString("LastRecipeName","RecipeName", FileName, Project_Path + "\\CtrlPrms\\MachineSetting.ini");
	::PostMessage(ControlBase->CWnd_Interface->GetSafeHwnd(), CWM_SYS_UPDATE_RECIPEID, NULL, NULL);

	ShowSystemMessageBox("╰参", FormatString("╰参ち传%s", FileName), true);

}

void CRecipeListDlg::CopyPatternOnForAll( CString SourcePattern)
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

void CRecipeListDlg::OnBnClickedButtonSystemRecipeCopy()
{
	CDiskObject DiskObject;

	CString RecipeName_Source, RecipeName_Destination;

	int nSourceSel = m_RecipeSourceSel.GetCurSel();
	int nDestinationSel = m_RecipeDestinationSel.GetCurSel();

	if(nSourceSel < 0)
	{
		ShowSystemMessageBox("╰参", "ㄓ方把计ゼ匡拒", true);
		return;
	}

	if(nDestinationSel < 0)
	{
		ShowSystemMessageBox("╰参", "ヘ夹把计ゼ匡拒", true);
		return;
	}

	m_RecipeSourceSel.GetLBText(nSourceSel, RecipeName_Source);

	m_RecipeDestinationSel.GetLBText(nDestinationSel, RecipeName_Destination);


	if(ShowSystemQestionBox("╰参", FormatString("╰参盢盢把计%s狡籹把计%sい叫拜琌膥尿", RecipeName_Source, RecipeName_Destination)) == IDCANCEL)
		return;

	if(m_pRecipe_Source.LoadRecipe(RecipeName_Source) == false)
	{
		ShowSystemMessageBox("╰参", "ㄓ方把计更ア毖叫絋粄郎琌", true);
		return;
	}

	if(m_pRecipe_Destination.LoadRecipe(RecipeName_Destination) == false)
	{
		ShowSystemMessageBox("╰参", "ヘ夹把计更ア毖叫絋粄郎琌", true);
		return;
	}

	m_pRecipe_Destination.Recipe_Data.st_RecipeData = m_pRecipe_Source.Recipe_Data.st_RecipeData;

	m_pRecipe_Destination.Recipe_Data.st_RecipeInfo.csComment = m_pRecipe_Source.Recipe_Data.st_RecipeInfo.csComment;
	m_pRecipe_Destination.Recipe_Data.st_RecipeInfo.csRecipeName = m_pRecipe_Destination.Recipe_Data.st_RecipeInfo.csFileName;


	m_pRecipe_Destination.SaveRecipe();

	//PatternFind郎狡籹
	CString PatternFileName_Source, PatternFilePath_Source, PatternFileName_Destination, PatternFilePath_Destination;

	PatternFileName_Source = FormatString("Work%03d_L.bmp", m_pRecipe_Source.Recipe_Data.st_RecipeInfo.nRcipeID);
	//PatternFilePath_Source  = FormatString("%s\\%s", ImageProc_PatternFind_MIL->GetPatternFolderPath(), PatternFileName_Source);

	PatternFileName_Destination = FormatString("Work%03d_L.bmp", m_pRecipe_Destination.Recipe_Data.st_RecipeInfo.nRcipeID);
	//PatternFilePath_Destination = FormatString("%s\\", ImageProc_PatternFind_MIL->GetPatternFolderPath());

	DiskObject.CopyFile(PatternFilePath_Source, PatternFilePath_Destination, PatternFileName_Destination);


	PatternFileName_Source = FormatString("Work%03d_R.bmp", m_pRecipe_Source.Recipe_Data.st_RecipeInfo.nRcipeID);
	//PatternFilePath_Source  = FormatString("%s\\%s", ImageProc_PatternFind_MIL->GetPatternFolderPath(), PatternFileName_Source);

	PatternFileName_Destination = FormatString("Work%03d_R.bmp", m_pRecipe_Destination.Recipe_Data.st_RecipeInfo.nRcipeID);
	//PatternFilePath_Destination = FormatString("%s\\", ImageProc_PatternFind_MIL->GetPatternFolderPath());

	DiskObject.CopyFile(PatternFilePath_Source, PatternFilePath_Destination, PatternFileName_Destination);

	PatternFileName_Source = FormatString("Work%03d_L.ptn", m_pRecipe_Source.Recipe_Data.st_RecipeInfo.nRcipeID);
	//PatternFilePath_Source  = FormatString("%s\\%s", ImageProc_PatternFind_MIL->GetPatternFolderPath(), PatternFileName_Source);

	PatternFileName_Destination = FormatString("Work%03d_L.ptn", m_pRecipe_Destination.Recipe_Data.st_RecipeInfo.nRcipeID);
	//PatternFilePath_Destination = FormatString("%s\\", ImageProc_PatternFind_MIL->GetPatternFolderPath());

	DiskObject.CopyFile(PatternFilePath_Source, PatternFilePath_Destination, PatternFileName_Destination);


	PatternFileName_Source = FormatString("Work%03d_R.ptn", m_pRecipe_Source.Recipe_Data.st_RecipeInfo.nRcipeID);
	//PatternFilePath_Source  = FormatString("%s\\%s", ImageProc_PatternFind_MIL->GetPatternFolderPath(), PatternFileName_Source);

	PatternFileName_Destination = FormatString("Work%03d_R.ptn", m_pRecipe_Destination.Recipe_Data.st_RecipeInfo.nRcipeID);
	//PatternFilePath_Destination = FormatString("%s\\", ImageProc_PatternFind_MIL->GetPatternFolderPath());

	DiskObject.CopyFile(PatternFilePath_Source, PatternFilePath_Destination, PatternFileName_Destination);


	//PatternFind Sticker郎狡籹
	PatternFileName_Source = FormatString("Work%03d_L.bmp", m_pRecipe_Source.Recipe_Data.st_RecipeInfo.nRcipeID);
	//PatternFilePath_Source  = FormatString("%s\\%s", ImageProc_PatternFind_MIL_Sticker->GetPatternFolderPath(), PatternFileName_Source);

	PatternFileName_Destination = FormatString("Work%03d_L.bmp", m_pRecipe_Destination.Recipe_Data.st_RecipeInfo.nRcipeID);
	//PatternFilePath_Destination = FormatString("%s\\", ImageProc_PatternFind_MIL_Sticker->GetPatternFolderPath());

	DiskObject.CopyFile(PatternFilePath_Source, PatternFilePath_Destination, PatternFileName_Destination);


	PatternFileName_Source = FormatString("Work%03d_R.bmp", m_pRecipe_Source.Recipe_Data.st_RecipeInfo.nRcipeID);
	//PatternFilePath_Source  = FormatString("%s\\%s", ImageProc_PatternFind_MIL_Sticker->GetPatternFolderPath(), PatternFileName_Source);

	PatternFileName_Destination = FormatString("Work%03d_R.bmp", m_pRecipe_Destination.Recipe_Data.st_RecipeInfo.nRcipeID);
	//PatternFilePath_Destination = FormatString("%s\\", ImageProc_PatternFind_MIL_Sticker->GetPatternFolderPath());

	DiskObject.CopyFile(PatternFilePath_Source, PatternFilePath_Destination, PatternFileName_Destination);

	PatternFileName_Source = FormatString("Work%03d_L.ptn", m_pRecipe_Source.Recipe_Data.st_RecipeInfo.nRcipeID);
	//PatternFilePath_Source  = FormatString("%s\\%s", ImageProc_PatternFind_MIL_Sticker->GetPatternFolderPath(), PatternFileName_Source);

	PatternFileName_Destination = FormatString("Work%03d_L.ptn", m_pRecipe_Destination.Recipe_Data.st_RecipeInfo.nRcipeID);
	//PatternFilePath_Destination = FormatString("%s\\", ImageProc_PatternFind_MIL_Sticker->GetPatternFolderPath());

	DiskObject.CopyFile(PatternFilePath_Source, PatternFilePath_Destination, PatternFileName_Destination);


	PatternFileName_Source = FormatString("Work%03d_R.ptn", m_pRecipe_Source.Recipe_Data.st_RecipeInfo.nRcipeID);
	//PatternFilePath_Source  = FormatString("%s\\%s", ImageProc_PatternFind_MIL_Sticker->GetPatternFolderPath(), PatternFileName_Source);

	PatternFileName_Destination = FormatString("Work%03d_R.ptn", m_pRecipe_Destination.Recipe_Data.st_RecipeInfo.nRcipeID);
	//PatternFilePath_Destination = FormatString("%s\\", ImageProc_PatternFind_MIL_Sticker->GetPatternFolderPath());

	DiskObject.CopyFile(PatternFilePath_Source, PatternFilePath_Destination, PatternFileName_Destination);

	//タ郎狡籹
	CString CaliFileName_Source = FormatString("Work%03d.ini", m_pRecipe_Source.Recipe_Data.st_RecipeInfo.nRcipeID);
	//CString CaliFilePath_Source = FormatString("%s\\CtrlPrms\\%s\\%s", Project_Path, AlignmentProcess->GetName(), CaliFileName_Source);

	CString CaliFileName_Destination = FormatString("Work%03d.ini", m_pRecipe_Destination.Recipe_Data.st_RecipeInfo.nRcipeID);
	//CString CaliFilePath_Destination  = FormatString("%s\\CtrlPrms\\%s\\", Project_Path, AlignmentProcess->GetName());

	//DiskObject.CopyFile(CaliFilePath_Source, CaliFilePath_Destination, CaliFileName_Destination);



	//禟タ郎狡籹
	CString CaliFileNameSticker_Source = FormatString("Work%03d.ini", m_pRecipe_Source.Recipe_Data.st_RecipeInfo.nRcipeID);
	//CString CaliFilePathSticker_Source = FormatString("%s\\CtrlPrms\\%s\\%s", Project_Path, AlignmentProcess_Sticker->GetName(), CaliFileName_Source);

	CString CaliFileNameSticker_Destination = FormatString("Work%03d.ini", m_pRecipe_Destination.Recipe_Data.st_RecipeInfo.nRcipeID);
	//CString CaliFilePathSticker_Destination  = FormatString("%s\\CtrlPrms\\%s\\", Project_Path, AlignmentProcess_Sticker->GetName());

	//DiskObject.CopyFile(CaliFilePathSticker_Source, CaliFilePathSticker_Destination, CaliFileNameSticker_Destination);


	UpdateList();
	ShowSystemMessageBox("╰参", "╰参ЧΘ狡籹", true);
}

void CRecipeListDlg::OnCbnDropdownComboRecipeListCopySource()
{
	CGetRecipe::RECIPE_INDEX_INFO info ;

	CString RecipeName, sz;
	int recipe_no;
	POSITION pos;

	CGetRecipe getRecipe(Project_Path);

	recipe_no = getRecipe.GetTotalRecipeName(cListrecipedata) ;
	pos = cListrecipedata.GetHeadPosition();

	m_RecipeSourceSel.ResetContent();

	UINT nIndex = 0;

	for(int x = 0; x < recipe_no; x++)
	{
		RecipeName = cListrecipedata.GetNext(pos);
		if( !getRecipe.GetRecipeIndexInfo(RecipeName , info ) )
			continue;

		m_RecipeSourceSel.AddString(info.csFileName);

		nIndex ++;
	}
}

void CRecipeListDlg::OnCbnDropdownComboRecipeListCopyDestination()
{
	CGetRecipe::RECIPE_INDEX_INFO info ;

	CString RecipeName, sz;
	int recipe_no;
	POSITION pos;

	CGetRecipe getRecipe(Project_Path);

	recipe_no = getRecipe.GetTotalRecipeName(cListrecipedata) ;
	pos = cListrecipedata.GetHeadPosition();

	m_RecipeDestinationSel.ResetContent();

	UINT nIndex = 0;

	for(int x = 0; x < recipe_no; x++)
	{
		RecipeName = cListrecipedata.GetNext(pos);
		if( !getRecipe.GetRecipeIndexInfo(RecipeName , info ) )
			continue;

		m_RecipeDestinationSel.AddString(info.csFileName);

		nIndex ++;
	}
}
