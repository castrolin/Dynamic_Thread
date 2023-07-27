// LogMainWindow.cpp : 實作檔
//

#include "stdafx.h"
#include ".\logmainwindow.h"


// CLogMainWindow 對話方塊

IMPLEMENT_DYNAMIC(CLogMainWindow, CDialog)
CLogMainWindow::CLogMainWindow(CWnd* pParent /*=NULL*/)
	: CDialog(/*CLogMainWindow::IDD, pParent*/)
{
	AfxSetResourceHandle(AfxLoadLibrary(_T("Class_LogSystem.dll")));	// 避免資源衝突
}

CLogMainWindow::~CLogMainWindow()
{
}

void CLogMainWindow::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB, m_Tab);
}


BEGIN_MESSAGE_MAP(CLogMainWindow, CDialog)
END_MESSAGE_MAP()


// CLogMainWindow 訊息處理常式

BOOL CLogMainWindow::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_Tab.SetFonts();
	m_Tab.EnableDraw(BTC_ALL);
	CMAIN_Tab::EnableCustomLook(TRUE, CMAIN_Tab::ETC_FLAT|CMAIN_Tab::ETC_COLOR|CMAIN_Tab::ETC_SELECTION|CMAIN_Tab::ETC_GRADIENT|CMAIN_Tab::ETC_BACKTABS);
	AfxSetResourceHandle(AfxGetInstanceHandle());

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX 屬性頁應傳回 FALSE
}

BOOL CLogMainWindow::PreTranslateMessage(MSG* pMsg)
{
	if( WM_KEYDOWN == pMsg->message )
	{
		if(pMsg->wParam == VK_RETURN
			|| pMsg->wParam == VK_ESCAPE )
		{
			::TranslateMessage(pMsg);
			::DispatchMessage(pMsg);
			return TRUE;
		}
	}

	return CDialog::PreTranslateMessage(pMsg);
}
