// OutputTestDlg.cpp : 實作檔
//

#include "stdafx.h"
#include "ControlBase.h"
#include "OutputTestDlg.h"
#include "afxdialogex.h"


// COutputTestDlg 對話方塊

IMPLEMENT_DYNAMIC(COutputTestDlg, CDialog)


UINT COutputTestDlg::OutputProc( LPVOID pObj )
{
	COutputTestDlg *pObject = (COutputTestDlg*)pObj;

	HANDLE h[2];
	h[0] = pObject->m_hDead;
	h[1] = pObject->m_hOutputUpdate;

	bool bLoop = true;

	while(bLoop)
	{
		DWORD nEvent = WaitForMultipleObjects(2, h, FALSE, INFINITE) - WAIT_OBJECT_0;

		switch(nEvent)
		{
		case 0:
			bLoop = false;
			break;
		case 1:
			try
			{
				if(pObject->m_OutputArray != NULL)
				{
					for(UINT i=0; i < pObject->m_OutputArray->size(); i++)
						pObject->m_OutputInfoList.SetItemText(i, 2, pObject->m_OutputArray->at(i)->GetValue() ? "●" : "");
				}
			}
			catch(SYSTEM_ERROR &e)
			{
				LOG->Message_Error(Log_Main, e.GetErrorMessage());
			}

			Sleep(200);
			break;
		}
	}

	return 0;
}

COutputTestDlg::COutputTestDlg(CWnd* pParent /*=NULL*/)
	: CDialog(COutputTestDlg::IDD, pParent)
{
	HINSTANCE ORG = AfxGetResourceHandle();
#ifdef _DEBUG
	HINSTANCE ControlBaseInstanceHandle = GetModuleHandle("..\\Debug\\ControlBase.dll");
#elif
	HINSTANCE ControlBaseInstanceHandle = GetModuleHandle("..\\Release\\ControlBase.dll");
#endif
	AfxSetResourceHandle(ControlBaseInstanceHandle);

	this->Create(IDD_DIALOG_OPTION_OUTPUT, pParent);

	AfxSetResourceHandle(ORG);

	m_OutputArray = NULL;

}

COutputTestDlg::~COutputTestDlg()
{
	SetEvent(m_hDead);

	WaitForSingleObject(m_OutputThd->m_hThread, INFINITE);

	delete m_OutputThd;

	CloseHandle(m_hDead);
	CloseHandle(m_hOutputUpdate);
}

void COutputTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_OUTPUT_INFO, m_OutputInfoList);
	DDX_Control(pDX, IDC_CHECK_OPTION_OUTPUT_CH1, m_OutputChEnable_1);
	DDX_Control(pDX, IDC_CHECK_OPTION_OUTPUT_CH2, m_OutputChEnable_2);

	DDX_Control(pDX, IDC_COMBO_OPTION_OUTPUT_CH1, m_OutputCh1);
	DDX_Control(pDX, IDC_COMBO_OPTION_OUTPUT_CH2, m_OutputCh2);

	DDX_Control(pDX, IDC_BUTTON_OPTION_INPUT_ON, m_OutputOn);
	DDX_Control(pDX, IDC_BUTTON_OPTION_INPUT_OFF, m_OutputOff);
	DDX_Control(pDX, IDC_BUTTON_OPTION_OUTPUT_REPEAT, m_OutputRepeat);
	DDX_Control(pDX, IDC_BUTTON_OPTION_OUTPUT_STOP, m_OutputStop);

}


BEGIN_MESSAGE_MAP(COutputTestDlg, CDialog)
	ON_WM_TIMER()
	ON_WM_SHOWWINDOW()
	ON_MESSAGE(CWM_SYS_UPDATE_LANG, OnMessageChangeLang)
	ON_BN_CLICKED(IDC_BUTTON_OPTION_INPUT_ON, &COutputTestDlg::OnBnClickedButtonOptionInputOn)
	ON_BN_CLICKED(IDC_BUTTON_OPTION_INPUT_OFF, &COutputTestDlg::OnBnClickedButtonOptionInputOff)
	ON_BN_CLICKED(IDC_BUTTON_OPTION_OUTPUT_REPEAT, &COutputTestDlg::OnBnClickedButtonOptionOutputRepeat)
	ON_CBN_SETFOCUS(IDC_COMBO_OPTION_OUTPUT_CH1, &COutputTestDlg::OnCbnSetfocusComboOptionOutputCh1)
	ON_CBN_SETFOCUS(IDC_COMBO_OPTION_OUTPUT_CH2, &COutputTestDlg::OnCbnSetfocusComboOptionOutputCh2)
	ON_BN_CLICKED(IDC_BUTTON_OPTION_OUTPUT_STOP, &COutputTestDlg::OnBnClickedButtonOptionOutputStop)
	ON_BN_CLICKED(IDC_CHECK_OPTION_OUTPUT_CH1, &COutputTestDlg::OnBnClickedCheckOptionOutputCh1)
	ON_BN_CLICKED(IDC_CHECK_OPTION_OUTPUT_CH2, &COutputTestDlg::OnBnClickedCheckOptionOutputCh2)
END_MESSAGE_MAP()


// COutputTestDlg 訊息處理常式
BOOL COutputTestDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	CFont * pFont = GetFont();
	LOGFONT lf;
	pFont->GetLogFont( &lf );
	lf.lfWeight = FW_BOLD;
	m_Font.CreateFontIndirect( &lf );

	SendMessageToDescendants( WM_SETFONT, (WPARAM) m_Font.m_hObject );

	m_OutputChEnable_1.SetShade(CShadeButtonST::SHS_HARDBUMP, 8, 20, 5, RGB(55,55,255));
	m_OutputChEnable_1.SetIcon(IDI_ICON_MIN_LED_GREEN,IDI_ICON_MIN_LED_NONE);
	m_OutputChEnable_1.OffsetColor(CButtonST::BTNST_COLOR_BK_IN, 30);
	m_OutputChEnable_1.SetColor(CButtonST::BTNST_COLOR_FG_IN, RGB(0, 0, 255));
	m_OutputChEnable_1.SetAlwaysTrack(FALSE);

	m_OutputChEnable_2.SetShade(CShadeButtonST::SHS_HARDBUMP, 8, 20, 5, RGB(55,55,255));
	m_OutputChEnable_2.SetIcon(IDI_ICON_MIN_LED_GREEN,IDI_ICON_MIN_LED_NONE);
	m_OutputChEnable_2.OffsetColor(CButtonST::BTNST_COLOR_BK_IN, 30);
	m_OutputChEnable_2.SetColor(CButtonST::BTNST_COLOR_FG_IN, RGB(0, 0, 255));
	m_OutputChEnable_2.SetAlwaysTrack(FALSE);

	m_OutputOn.SetShade(CShadeButtonST::SHS_HARDBUMP, 8, 20, 5, RGB(55,55,255));
	m_OutputOn.SetIcon(IDI_ICON_MIN_LED_GREEN,IDI_ICON_MIN_LED_NONE);
	m_OutputOn.OffsetColor(CButtonST::BTNST_COLOR_BK_IN, 30);
	m_OutputOn.SetColor(CButtonST::BTNST_COLOR_FG_IN, RGB(0, 0, 255));
	m_OutputOn.SetAlwaysTrack(FALSE);

	m_OutputOff.SetShade(CShadeButtonST::SHS_HARDBUMP, 8, 20, 5, RGB(55,55,255));
	m_OutputOff.SetIcon(IDI_ICON_MIN_LED_GREEN,IDI_ICON_MIN_LED_NONE);
	m_OutputOff.OffsetColor(CButtonST::BTNST_COLOR_BK_IN, 30);
	m_OutputOff.SetColor(CButtonST::BTNST_COLOR_FG_IN, RGB(0, 0, 255));
	m_OutputOff.SetAlwaysTrack(FALSE);

	m_OutputRepeat.SetShade(CShadeButtonST::SHS_HARDBUMP, 8, 20, 5, RGB(55,55,255));
	m_OutputRepeat.SetIcon(IDI_ICON_MIN_LED_GREEN,IDI_ICON_MIN_LED_NONE);
	m_OutputRepeat.OffsetColor(CButtonST::BTNST_COLOR_BK_IN, 30);
	m_OutputRepeat.SetColor(CButtonST::BTNST_COLOR_FG_IN, RGB(0, 0, 255));
	m_OutputRepeat.SetAlwaysTrack(FALSE);

	m_OutputStop.SetShade(CShadeButtonST::SHS_HARDBUMP, 8, 20, 5, RGB(55,55,255));
	m_OutputStop.SetIcon(IDI_ICON_MIN_LED_GREEN,IDI_ICON_MIN_LED_NONE);
	m_OutputStop.OffsetColor(CButtonST::BTNST_COLOR_BK_IN, 30);
	m_OutputStop.SetColor(CButtonST::BTNST_COLOR_FG_IN, RGB(0, 0, 255));
	m_OutputStop.SetAlwaysTrack(FALSE);

	m_OutputInfoList.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_FLATSB);
	m_OutputInfoList.InsertColumn(0, "編號", LVCFMT_CENTER, 50);
	m_OutputInfoList.InsertColumn(1, "名稱", LVCFMT_LEFT, 200);
	m_OutputInfoList.InsertColumn(2, "輸出狀態", LVCFMT_CENTER, 100);

	m_hDead = CreateEvent(NULL, TRUE, FALSE, NULL);
	m_hOutputUpdate = CreateEvent(NULL, TRUE, FALSE, NULL);

	m_OutputThd = AfxBeginThread(OutputProc, (LPVOID)this, THREAD_PRIORITY_NORMAL, 0, CREATE_SUSPENDED);
	m_OutputThd->m_bAutoDelete = FALSE;
	m_OutputThd->ResumeThread();

	return TRUE;
}

void COutputTestDlg::InitialOutputInfo( std::vector<COutputBase*> *Array )
{
	m_OutputArray = Array;

	for(UINT nIndex = 0; nIndex < m_OutputArray->size(); nIndex++)
	{
		m_OutputInfoList.InsertItem(nIndex, FormatString("%03d", nIndex));

		m_OutputInfoList.SetItemText(nIndex, 0, FormatString("%03d", nIndex));
		m_OutputInfoList.SetItemText(nIndex, 1, m_OutputArray->at(nIndex)->GetOutputName());
	}

}

void COutputTestDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此加入您的訊息處理常式程式碼和 (或) 呼叫預設值

	CDialog::OnTimer(nIDEvent);

	switch(nIDEvent)
	{
	case _OUTPUT_REPEAT_TIMER:

		try
		{
			if(m_OutputChEnable_1.GetCheck() == TRUE)
			{
				bool bValue = m_OutputArray->at(m_OutputCh1.GetCurSel())->GetValue();
				m_OutputArray->at(m_OutputCh1.GetCurSel())->SetValue(!bValue);
			}

			if(m_OutputChEnable_2.GetCheck() == TRUE)
			{
				bool bValue = m_OutputArray->at(m_OutputCh2.GetCurSel())->GetValue();
				m_OutputArray->at(m_OutputCh2.GetCurSel())->SetValue(!bValue);
			}
		}
		catch(SYSTEM_ERROR &e)
		{
			LOG->Message_Error(Log_Main, e.GetErrorMessage());
		}
		break;
		
	}

}

void COutputTestDlg::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialog::OnShowWindow(bShow, nStatus);

	if(bShow)
	{
		SetEvent(m_hOutputUpdate);
		if(GetSystemMode() == MODE_AUTO)
		{
			m_OutputChEnable_1.EnableWindow(FALSE);
			m_OutputChEnable_2.EnableWindow(FALSE);
			m_OutputOn.EnableWindow(FALSE);
			m_OutputOff.EnableWindow(FALSE);
			m_OutputRepeat.EnableWindow(FALSE);
			m_OutputStop.EnableWindow(FALSE);
		}
		else
		{
			m_OutputChEnable_1.EnableWindow(TRUE);
			m_OutputChEnable_2.EnableWindow(TRUE);
			m_OutputOn.EnableWindow(TRUE);
			m_OutputOff.EnableWindow(TRUE);
			m_OutputRepeat.EnableWindow(TRUE);
			m_OutputStop.EnableWindow(TRUE);
		}
	}
	else
		ResetEvent(m_hOutputUpdate);
}

void COutputTestDlg::OnBnClickedButtonOptionInputOn()
{
	try
	{
		if(m_OutputInfoList.GetSelectionMark() < 0)
		{
			AfxMessageBox("請選擇Channel\nPlease Select an Channel!");
			return;
		}
		
		m_OutputArray->at(m_OutputInfoList.GetSelectionMark())->SetValue(true);
	}
	catch(SYSTEM_ERROR &e)
	{
		LOG->Message_Error(Log_Main, e.GetErrorMessage());
	}
	
}

void COutputTestDlg::OnBnClickedButtonOptionInputOff()
{
	try
	{
		if(m_OutputInfoList.GetSelectionMark() < 0)
		{
			AfxMessageBox("請選擇Channel\nPlease Select an Channel!");
			return;
		}

		m_OutputArray->at(m_OutputInfoList.GetSelectionMark())->SetValue(false);
	}
	catch(SYSTEM_ERROR &e)
	{
		LOG->Message_Error(Log_Main, e.GetErrorMessage());
	}
}

void COutputTestDlg::OnBnClickedButtonOptionOutputRepeat()
{
	SetTimer(_OUTPUT_REPEAT_TIMER, GetRepeatTimeSetting(), NULL);
}

void COutputTestDlg::OnBnClickedButtonOptionOutputStop()
{
	KillTimer(_OUTPUT_REPEAT_TIMER);
}

void COutputTestDlg::OnCbnSetfocusComboOptionOutputCh1()
{
	m_OutputCh1.ResetContent();

	if(m_OutputArray == NULL)
		return;

	for(UINT nIndex = 0; nIndex < m_OutputArray->size() ; nIndex++)
		m_OutputCh1.AddString(FormatString("%03d", nIndex));
}


void COutputTestDlg::OnCbnSetfocusComboOptionOutputCh2()
{
	m_OutputCh2.ResetContent();

	if(m_OutputArray == NULL)
		return;

	for(UINT nIndex = 0; nIndex < m_OutputArray->size(); nIndex++)
		m_OutputCh2.AddString(FormatString("%03d", nIndex));
}

UINT COutputTestDlg::GetRepeatTimeSetting()
{
	return GetDlgItemInt(IDC_EDIT_OPTION_OUTPUT_REPEATTIME);
}

void COutputTestDlg::OnBnClickedCheckOptionOutputCh1()
{
	if(m_OutputChEnable_1.GetCheck() == FALSE)
		m_OutputChEnable_1.SetCheck(TRUE);
	else
		m_OutputChEnable_1.SetCheck(FALSE);
}

void COutputTestDlg::OnBnClickedCheckOptionOutputCh2()
{
	if(m_OutputChEnable_2.GetCheck() == FALSE)
		m_OutputChEnable_2.SetCheck(TRUE);
	else
		m_OutputChEnable_2.SetCheck(FALSE);
}

long COutputTestDlg::OnMessageChangeLang( WPARAM wparam, LPARAM lparam )
{
	CString DlgName = "OutputTestDlg";

	std::vector<CString>ButtonList;
	std::vector<CString>StaticList;

	ButtonList = LanguageCtrl->GetInterfaceButtonNameList(DlgName, (UINT)wparam);
	StaticList = LanguageCtrl->GetInterfaceStaticNameList(DlgName, (UINT)wparam);

	m_OutputOn.SetWindowText(ButtonList.at(0));
	m_OutputOff.SetWindowText(ButtonList.at(1));
	m_OutputRepeat.SetWindowText(ButtonList.at(2));
	m_OutputStop.SetWindowText(ButtonList.at(3));

	//更換List表頭
	CHeaderCtrl* m_Header=(CHeaderCtrl*)m_OutputInfoList.GetDlgItem(0); 
	int nCount = m_Header->GetItemCount(); 

	for(int x = 0; x < nCount;  x++)
	{
		if(UINT(x + 1) > StaticList.size())
			break;

		LVCOLUMN lvCol;
		::ZeroMemory((void *)&lvCol, sizeof(LVCOLUMN));
		lvCol.mask=LVCF_TEXT;
		m_OutputInfoList.GetColumn(x,&lvCol);

		lvCol.pszText = StaticList.at(x).GetBuffer(StaticList.at(x).GetLength());

		m_OutputInfoList.SetColumn(x,&lvCol);

	}

	GetDlgItem(IDC_STATIC_OPTION_OUTPUT_REPEATTIME)->SetWindowText(StaticList.at(nCount));

	return 0;
}
