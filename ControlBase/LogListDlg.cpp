// CLogListDlg.cpp : 實作檔
//

#include "stdafx.h"
#include "ControlBase.h"
#include "LogListDlg.h"
#include "afxdialogex.h"


// CCLogListDlg 對話方塊

IMPLEMENT_DYNAMIC(CLogListDlg, CDialog)

CLogListDlg::CLogListDlg(CString FilePath, CWnd* pParent /*=NULL*/)
	: CDialog(CLogListDlg::IDD, pParent)
{
	HINSTANCE ORG = AfxGetResourceHandle();
#ifdef _DEBUG
	HINSTANCE ControlBaseInstanceHandle = GetModuleHandle("..\\Debug\\ControlBase.dll");
#elif
	HINSTANCE ControlBaseInstanceHandle = GetModuleHandle("..\\Release\\ControlBase.dll");
#endif
	AfxSetResourceHandle(ControlBaseInstanceHandle);

	this->Create(IDD_DIALOG_LOGLIST, pParent);

	m_DiskObj = new CDiskObject();

	m_path = FilePath;

	LogDataLoad();

	TimeRangeVector = new std::vector<CString>;

	AfxSetResourceHandle(ORG);

}

CLogListDlg::~CLogListDlg()
{
	
}

void CLogListDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_LOGVIEW, m_LogList);
	DDX_Control(pDX, IDC_COMBO_DATE, m_DateComboBox);
	DDX_Control(pDX, IDC_COMBO_TIME, m_TimeComboBox);
	DDX_Control(pDX, IDC_COMBO_LOGFILE, m_FileSelector);
}


BEGIN_MESSAGE_MAP(CLogListDlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_CLEANLOG, &CLogListDlg::OnBnClickedCleanLog)
	ON_BN_CLICKED(IDC_BUTTON_OPENLOG, &CLogListDlg::OnBnClickedOpenLog)

	ON_CBN_SELCHANGE(IDC_COMBO_DATE, &CLogListDlg::OnCbnSelchangeComboDateSelect)
	ON_CBN_SELCHANGE(IDC_COMBO_TIME, &CLogListDlg::OnCbnSelchangeComboTimeSelect)
	ON_CBN_SELCHANGE(IDC_COMBO_LOGFILE, &CLogListDlg::OnCbnSelchangeComboFileSelect)

END_MESSAGE_MAP()



BOOL CLogListDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	CFont * pFont = GetFont();
	CFont m_logviewFont;
	LOGFONT lf;
	pFont->GetLogFont( &lf );
	lf.lfWeight = 10;
	lf.lfHeight = 16;

	m_logviewFont.CreateFontIndirect( &lf );

	CFont m_font;
	m_font.CreatePointFont (40,"Times New Roman");

	
	m_LogList.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES |LVS_EX_FLATSB);
	m_LogList.SetFont(&m_logviewFont);
	m_LogList.InsertColumn(0,	_T("Description."),	LVCFMT_CENTER, 1000000, 2);

	GetDlgItem(IDC_STATIC_DATE)->SetFont(&m_font);
	GetDlgItem(IDC_STATIC_FILE)->SetFont(&m_font);
	GetDlgItem(IDC_STATIC_TIME)->SetFont(&m_font);

	GetDlgItem(IDC_BUTTON_OPENLOG)->SetFont(&m_font);
	GetDlgItem(IDC_BUTTON_CLEANLOG)->SetFont(&m_font);

	
	


	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX 屬性頁應傳回 FALSE
}
// CCLogListDlg 訊息處理常式

bool CLogListDlg::LogDataLoad()
{
	if(m_DiskObj->DirectoryExists(m_path)== FALSE)
		return false;

	CString srcdir;
	CStringArray dirctories;
	CString DateName;
	CString TimeName;

	m_DiskObj->EnumDirectories(m_path, dirctories);

	for(int i=0; i < dirctories.GetSize(); i++)
	{
		DateName = dirctories[i];
		m_DateComboBox.AddString(DateName);
	}

	for(int ind=0; ind<24; ind++)
	{
		if(ind < 10)
			TimeName.Format("0%d",ind);
		else
			TimeName.Format("%d",ind);

		m_TimeComboBox.AddString(TimeName);
	}
	m_TimeComboBox.AddString("All");

	return true;
}

void CLogListDlg::OnBnClickedCleanLog()
{
	m_LogList.DeleteAllItems();
}

void CLogListDlg::OnBnClickedOpenLog()
{
	CString TextContent = m_LogList.GetItemText(0,0);

	if(!TextContent.IsEmpty())
	{
		m_LogList.DeleteAllItems();
	}
	
	CString FilePath = m_path + m_ChosenDate + "\\" + m_FileName;
	TCHAR* pFileName = (FilePath.GetBuffer(FilePath.GetLength()));
	CStdioFile f1;
	if(!f1.Open(pFileName,CFile::shareDenyRead)) 
	{
		ShowSystemMessageBox("系統", "此Log 記錄檔無法開啟，請確認!", true);
		return;
	}

	CString LineData;
	BOOL next = TRUE;
	int ind = 0; 
	while(next==TRUE )
	{
		f1.ReadString(LineData);
		if(LineData != "")
		{
			//AllLogDataVector->push_back(LineData);
			m_LogList.InsertItem(ind,"");
			m_LogList.SetItemText(ind,0,LineData);
			next= TRUE;
			ind++;
		}
		else
			next= FALSE; 
	}


}

void CLogListDlg::OnCbnSelchangeComboDateSelect()
{

	if(m_FileSelector.GetCount()!=0)
	{
		int index = 0;
		do 
		{
			m_FileSelector.DeleteString(index);
			index++;
		} while (m_FileSelector.GetCount()!=0);
	}

	CString EntirePath;

	m_DateComboBox.GetLBText(m_DateComboBox.GetCurSel(),m_ChosenDate);

	if(m_DateComboBox.GetCurSel() == -1)
		return;
	
	EntirePath = m_path + m_ChosenDate + "\\";
	
	CStringArray AllFiles;
	m_DiskObj->EnumAllFiles(EntirePath, AllFiles,0);

	for(int i=0; i < AllFiles.GetSize(); i++)
	{
		m_FileName = AllFiles[i];
		m_FileSelector.AddString(m_FileName);
	}
	
}

void CLogListDlg::OnCbnSelchangeComboTimeSelect()
{
	if(!TimeRangeVector->empty())
		TimeRangeVector->clear();


	CString TimeData;
	CString ChosenTime;

	m_TimeComboBox.GetLBText(m_TimeComboBox.GetCurSel(),ChosenTime);
	if(ChosenTime == "All")
	{
		OnBnClickedOpenLog();
		return;
	}

	for(int i=0; i< m_LogList.GetItemCount(); i++)
	{
		TimeData = GetTimeFromString(i);

		if(TimeData != " ")
		{
			if(TImeFilter(TimeData, ChosenTime))
			{
				TimeRangeVector->push_back(m_LogList.GetItemText(i,0));
			}
		}
		
	}
	m_LogList.DeleteAllItems();
	for(UINT ind= 0; ind< TimeRangeVector->size(); ind++)
	{
		m_LogList.InsertItem(ind,"");
		m_LogList.SetItemText(ind,0,TimeRangeVector->at(ind));
	}


}

void CLogListDlg::OnCbnSelchangeComboFileSelect()
{	
	
}

CString CLogListDlg::GetTimeFromString(int nRow)
{
	CString TextContent = m_LogList.GetItemText(nRow,0);
	if(TextContent == " ") 
		return " ";

	char *ch = (char*)TextContent.GetBuffer(0);

	CString temp;
	CString tempNext;
	CString Currtime;

	
	for(int i =0; i<TextContent.GetLength(); i++)
	{
		temp = ch[i];
		TRACE(temp);
		if(temp ==" ")
		{
			int j = i+1;
			tempNext = ch[j];

			while(tempNext != " ")
			{
				tempNext = ch[j];
				Currtime += tempNext;
				j++;
			}
			break;

			if(!Currtime.IsEmpty())
				break;
		}

	}

	char* firststring = (char*) Currtime.GetBuffer(0);
	char index = firststring[0];
	switch(index)
	{
	case '0':
		return Currtime;
	case '1':
		return Currtime;
	case '2':
		return Currtime;
			
	}

	return " ";
}

BOOL CLogListDlg::TImeFilter(CString InputTime, CString p_filter)
{

	char* TempChar = (char*)InputTime.GetBuffer(0);

	if(p_filter[0] == InputTime[0] && p_filter[1] == InputTime[1] )
		return TRUE;
	return FALSE;

}