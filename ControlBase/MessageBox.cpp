// MessageBox.cpp : 實作檔
//

#include "stdafx.h"
#include "MessageBox.h"

// CMessageBox 對話方塊

IMPLEMENT_DYNAMIC(CMessageBox, CDialog)

CMessageBox::CMessageBox(CWnd* pParent /*=NULL*/)
	: CDialog(CMessageBox::IDD, pParent)
{
	HINSTANCE ORG = AfxGetResourceHandle();
#ifdef _DEBUG
	HINSTANCE ControlBaseInstanceHandle = GetModuleHandle("..\\Debug\\ControlBase.dll");
#elif
	HINSTANCE ControlBaseInstanceHandle = GetModuleHandle("..\\Release\\ControlBase.dll");
#endif
	AfxSetResourceHandle(ControlBaseInstanceHandle);

	this->Create(IDD_DIALOG_MESSAGE_BOX, pParent);

	AfxSetResourceHandle(ORG);
}

CMessageBox::~CMessageBox()
{
}

void CMessageBox::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_MESSAGE_BOX_GROUP, m_GroupBox);
}


BEGIN_MESSAGE_MAP(CMessageBox, CDialog)
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()

BOOL CMessageBox::OnInitDialog()
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

	return TRUE;
}


// CMessageBox 訊息處理常式
void CMessageBox::ShowMessage(CString CaptureText, CString Message, bool ShowButton, bool AutoClose, DWORD WaitTime)
{
	m_GroupBox.SetWindowText(CaptureText);

	this->SetWindowTextA(CaptureText);
	this->GetDlgItem(IDC_STATIC_MESSAGE)->SetWindowText(Message);
	this->ShowWindow(SW_SHOW);
	this->SetForegroundWindow();

	if(ShowButton)
		this->GetDlgItem(IDOK)->ShowWindow(true);
	else
		this->GetDlgItem(IDOK)->ShowWindow(false);

	m_GroupBox.Invalidate();

	if(AutoClose)
	{
		Delay(WaitTime);
		this->ShowWindow(SW_HIDE);
	}
	
}

void CMessageBox::CloseMessage()
{
	this->SetWindowTextA("");
	this->GetDlgItem(IDC_STATIC_MESSAGE)->SetWindowText("");
	this->ShowWindow(SW_HIDE);
}

void CMessageBox::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此加入您的訊息處理常式程式碼和 (或) 呼叫預設值

	CDialog::OnLButtonDown(nFlags, point);

	this->SendMessage(WM_NCLBUTTONDOWN,HTCAPTION);
}
