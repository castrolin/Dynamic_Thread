// SystemTraceDlg.cpp : 實作檔
//

#include "stdafx.h"
#include "ControlBase.h"
#include "SystemTraceDlg.h"
#include "afxdialogex.h"


// CSystemTraceDlg 對話方塊

IMPLEMENT_DYNAMIC(CSystemTraceDlg, CDialog)

CSystemTraceDlg::CSystemTraceDlg(CWnd* pParent)
	: CDialog(CSystemTraceDlg::IDD, pParent)
{
	HINSTANCE ORG = AfxGetResourceHandle();
#ifdef _DEBUG
	HINSTANCE ControlBaseInstanceHandle = GetModuleHandle("..\\Debug\\ControlBase.dll");
#elif
	HINSTANCE ControlBaseInstanceHandle = GetModuleHandle("..\\Release\\ControlBase.dll");
#endif
	AfxSetResourceHandle(ControlBaseInstanceHandle);

	this->Create(IDD_DIALOG_SYSTEM_TRACE, pParent);

	AfxSetResourceHandle(ORG);
}

CSystemTraceDlg::~CSystemTraceDlg()
{
}

void CSystemTraceDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_SYSTEM_TRACE, m_GroupBox);
	DDX_Control(pDX, IDC_LIST_TRACE_MESSAGE, m_pMessageList);
}


BEGIN_MESSAGE_MAP(CSystemTraceDlg, CDialog)
	ON_WM_SHOWWINDOW()
	ON_MESSAGE(CWM_SYS_UPDATE_TRACE, OnMessageUpdateTrace)
	ON_BN_CLICKED(IDCANCEL, &CSystemTraceDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// CSystemTraceDlg 訊息處理常式

BOOL CSystemTraceDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	CFont * pFont = GetFont();
	LOGFONT lf;
	pFont->GetLogFont( &lf );
	lf.lfWeight = FW_BOLD;
	m_Font.CreateFontIndirect( &lf );

	SendMessageToDescendants( WM_SETFONT, (WPARAM) m_Font.m_hObject );

	m_GroupBox.SetXPGroupStyle(CXPGroupBox::XPGB_FRAME);
	m_GroupBox.SetBackgroundColor(RGB(180, 230, 30), ::GetSysColor(COLOR_BTNFACE));
	m_GroupBox.SetBorderColor(RGB(180, 230, 30));
	m_GroupBox.SetBorderWidth(5);

	m_GroupBox.SetFontBold(TRUE);
	m_GroupBox.SetAlignment(SS_CENTER);


	m_pMessageList.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES |LVS_EX_FLATSB);
	m_pMessageList.InsertColumn(0,	_T("Time"),	LVCFMT_CENTER, 200, 2);
	m_pMessageList.InsertColumn(1,	_T("Trace Message"),	LVCFMT_LEFT, 1500, 2);

	return TRUE;
}

BOOL CSystemTraceDlg::PreTranslateMessage( MSG* pMsg )
{
	if(pMsg->message==WM_KEYDOWN)
	{

		if(pMsg->wParam==VK_ESCAPE) 
		{
			pMsg->wParam=NULL;
		}

		
		if(pMsg->wParam==VK_RETURN) 
		{
			pMsg->wParam=NULL;
		}

	}

	if(pMsg->message == WM_LBUTTONDOWN && pMsg->hwnd == this->GetSafeHwnd())
	{
		this->SendMessage(WM_NCLBUTTONDOWN,HTCAPTION);

		return 1;
	}

	return CDialog::PreTranslateMessage(pMsg);
}

void CSystemTraceDlg::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialog::OnShowWindow(bShow, nStatus);

}

long CSystemTraceDlg::OnMessageUpdateTrace( WPARAM wparam, LPARAM lparam )
{
	CString Message((char *)(wparam));


	if(Message.IsEmpty() == TRUE)
		return 0;

	if(Message.Find('\n') != -1)
	{
		while(Message.Find('\n') != -1)
		{
			int nIndex = Message.Find('\n');
			CString SubString = Message.Mid(0, nIndex + 1);
			Message = Message.Mid(nIndex + 1, Message.GetLength() - nIndex);

			if(m_pMessageList.GetItemCount() > TRACE_MESSAGE_MAX_NUM)
			{
				m_pMessageList.DeleteItem(TRACE_MESSAGE_MAX_NUM - 1);
			}

			CTime NowTime = CTime::GetCurrentTime ();

			m_pMessageList.InsertItem(0, NowTime.Format("%Y-%m-%d %H:%M:%S"));
			m_pMessageList.SetItemText(0, 1, SubString);
		}
	}
	else
	{
		if(m_pMessageList.GetItemCount() > TRACE_MESSAGE_MAX_NUM)
		{
			m_pMessageList.DeleteItem(TRACE_MESSAGE_MAX_NUM);
		}

		CTime NowTime = CTime::GetCurrentTime ();

		m_pMessageList.InsertItem(0, NowTime.Format("%Y-%m-%d %H:%M:%S"));
		m_pMessageList.SetItemText(0, 1, Message);
	}
	

	return 0;
}

void CSystemTraceDlg::OnBnClickedCancel()
{
	CDialog::OnCancel();
}

