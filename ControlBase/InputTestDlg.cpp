// InputTest.cpp : 實作檔
//

#include "stdafx.h"
#include "ControlBase.h"
#include "InputTestDlg.h"
#include "afxdialogex.h"


// CInputTest 對話方塊

IMPLEMENT_DYNAMIC(CInputTestDlg, CDialog)

UINT CInputTestDlg::InputProc( LPVOID pObj )
{
	CInputTestDlg *pObject = (CInputTestDlg*)pObj;

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
				if(pObject->m_InputArray != NULL)
				{
					for(UINT i=0; i < pObject->m_InputArray->size(); i++)
						pObject->m_InputInfoList.SetItemText(i, 2, pObject->m_InputArray->at(i)->GetValue() ? "●" : "");
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

CInputTestDlg::CInputTestDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CInputTestDlg::IDD, pParent)
{
	HINSTANCE ORG = AfxGetResourceHandle();
#ifdef _DEBUG
	HINSTANCE ControlBaseInstanceHandle = GetModuleHandle("..\\Debug\\ControlBase.dll");
#elif
	HINSTANCE ControlBaseInstanceHandle = GetModuleHandle("..\\Release\\ControlBase.dll");
#endif
	AfxSetResourceHandle(ControlBaseInstanceHandle);

	this->Create(IDD_DIALOG_OPTION_INPUT, pParent);

	AfxSetResourceHandle(ORG);

	m_InputArray = NULL;

}

CInputTestDlg::~CInputTestDlg()
{
	SetEvent(m_hDead);

	WaitForSingleObject(m_InputThd->m_hThread, INFINITE);

	delete m_InputThd;

	CloseHandle(m_hDead);
	CloseHandle(m_hOutputUpdate);
}

void CInputTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_LIST_INPUT_INFO, m_InputInfoList);
}


BEGIN_MESSAGE_MAP(CInputTestDlg, CDialog)
	ON_WM_TIMER()
	ON_WM_SHOWWINDOW()
	ON_MESSAGE(CWM_SYS_UPDATE_LANG, OnMessageChangeLang)
END_MESSAGE_MAP()



// CInputTest 訊息處理常式
BOOL CInputTestDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	CFont * pFont = GetFont();
	LOGFONT lf;
	pFont->GetLogFont( &lf );
	lf.lfWeight = FW_BOLD;
	m_Font.CreateFontIndirect( &lf );

	SendMessageToDescendants( WM_SETFONT, (WPARAM) m_Font.m_hObject );

	m_InputInfoList.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_FLATSB);

	m_InputInfoList.InsertColumn(0, "編號", LVCFMT_CENTER, 50);
	m_InputInfoList.InsertColumn(1, "名稱", LVCFMT_LEFT, 200);
	m_InputInfoList.InsertColumn(2, "輸入狀態", LVCFMT_CENTER, 100);
	
	m_hDead = CreateEvent(NULL, TRUE, FALSE, NULL);
	m_hOutputUpdate = CreateEvent(NULL, TRUE, FALSE, NULL);

	m_InputThd = AfxBeginThread(InputProc, (LPVOID)this, THREAD_PRIORITY_NORMAL, 0, CREATE_SUSPENDED);
	m_InputThd->m_bAutoDelete = FALSE;
	m_InputThd->ResumeThread();

	return TRUE;
}

void CInputTestDlg::InitialInputInfo( std::vector<CInputBase*> *Array )
{
	m_InputArray = Array;

	for(UINT nIndex = 0; nIndex < m_InputArray->size(); nIndex++)
	{
		m_InputInfoList.InsertItem(nIndex, FormatString("%03d", nIndex));

		m_InputInfoList.SetItemText(nIndex, 0, FormatString("%03d", nIndex));
		m_InputInfoList.SetItemText(nIndex, 1, m_InputArray->at(nIndex)->GetInputName());
	}

}

void CInputTestDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此加入您的訊息處理常式程式碼和 (或) 呼叫預設值

	CDialog::OnTimer(nIDEvent);
}

void CInputTestDlg::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialog::OnShowWindow(bShow, nStatus);

	if(bShow)
		SetEvent(m_hOutputUpdate);
	else
		ResetEvent(m_hOutputUpdate);
}

long CInputTestDlg::OnMessageChangeLang( WPARAM wparam, LPARAM lparam )
{
	CString DlgName = "InputTestDlg";

	std::vector<CString>StaticList;

	StaticList = LanguageCtrl->GetInterfaceStaticNameList(DlgName, (UINT)wparam);
	
	//更換List表頭
	CHeaderCtrl* m_Header=(CHeaderCtrl*)m_InputInfoList.GetDlgItem(0); 
	int nCount = m_Header->GetItemCount(); 

	for(int x = 0; x < nCount;  x++)
	{
		if(UINT(x + 1) > StaticList.size())
			break;

		LVCOLUMN lvCol;
		::ZeroMemory((void *)&lvCol, sizeof(LVCOLUMN));
		lvCol.mask=LVCF_TEXT;
		m_InputInfoList.GetColumn(x,&lvCol);

		lvCol.pszText = StaticList.at(x).GetBuffer(StaticList.at(x).GetLength());

		m_InputInfoList.SetColumn(x,&lvCol);

	}

	return 0;
}
