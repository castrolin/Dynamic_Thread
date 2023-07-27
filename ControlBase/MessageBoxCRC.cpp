// MessageBoxCRC.cpp : 實作檔
//

#include "stdafx.h"
#include "MessageBoxCRC.h"

// CMessageBoxCRC 對話方塊

IMPLEMENT_DYNAMIC(CMessageBoxCRC, CDialog)

CMessageBoxCRC::CMessageBoxCRC(CWnd* pParent /*=NULL*/)
	: CDialog(CMessageBoxCRC::IDD, pParent)
{
	
}

CMessageBoxCRC::~CMessageBoxCRC()
{
}

void CMessageBoxCRC::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_MESSAGE_BOX_CRC_GROUP, m_GroupBox);
}


BEGIN_MESSAGE_MAP(CMessageBoxCRC, CDialog)
	ON_WM_SHOWWINDOW()
	ON_BN_CLICKED(IDC_BST_MESSAGE_CANCEL, &CMessageBoxCRC::OnBnClickedBstMessageCancel)
	ON_BN_CLICKED(IDC_BST_MESSAGE_RETRY, &CMessageBoxCRC::OnBnClickedBstMessageRetry)
	ON_BN_CLICKED(IDC_BST_MESSAGE_CONTINUE, &CMessageBoxCRC::OnBnClickedBstMessageContinue)
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()

BOOL CMessageBoxCRC::OnInitDialog()
{
	CDialog::OnInitDialog();

	this->SetWindowTextA(m_CaptureText);
	this->GetDlgItem(IDC_STATIC_MESSAGE)->SetWindowText(m_Message);
	this->ShowWindow(SW_SHOW);
	this->SetForegroundWindow();

	m_GroupBox.SetXPGroupStyle(CXPGroupBox::XPGB_FRAME);
	m_GroupBox.SetBackgroundColor(RGB(180, 230, 30), ::GetSysColor(COLOR_BTNFACE));
	m_GroupBox.SetBorderColor(RGB(180, 230, 30));
	m_GroupBox.SetBorderWidth(5);

	m_GroupBox.SetFontBold(TRUE);
	m_GroupBox.SetAlignment(SS_CENTER);

	switch(m_ShowType)
	{
	case BST_CANCEL_RETRY_CONTINUE:
		GetDlgItem(IDC_BST_MESSAGE_CANCEL)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_BST_MESSAGE_RETRY)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_BST_MESSAGE_CONTINUE)->ShowWindow(SW_SHOW);
		break;

	case BST_CANCEL_RETRY:
		GetDlgItem(IDC_BST_MESSAGE_CANCEL)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_BST_MESSAGE_RETRY)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_BST_MESSAGE_CONTINUE)->ShowWindow(SW_HIDE);
		break;

	case BST_CANCEL_CONTINUE:
		GetDlgItem(IDC_BST_MESSAGE_CANCEL)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_BST_MESSAGE_RETRY)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_BST_MESSAGE_CONTINUE)->ShowWindow(SW_SHOW);
		break;

	case BST_RETRY_CONTINUE:
		GetDlgItem(IDC_BST_MESSAGE_CANCEL)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_BST_MESSAGE_RETRY)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_BST_MESSAGE_CONTINUE)->ShowWindow(SW_SHOW);
		break;

	}
		
	return TRUE;
}


// CMessageBoxCRC 訊息處理常式
void CMessageBoxCRC::SetMessage(CString CaptureText, CString Message, _SHOW_BST_TYPE ShowType, bool AutoClose, DWORD WaitTime)
{
	m_GroupBox.SetWindowText(CaptureText);
	m_CaptureText = CaptureText;
	m_Message = Message;
	m_ShowType = ShowType;
	m_AutoClose = AutoClose;
	m_WaitTime = WaitTime;
}

void CMessageBoxCRC::CloseMessage()
{
	this->SetWindowTextA("");
	this->GetDlgItem(IDC_STATIC_MESSAGE)->SetWindowText("");
	this->ShowWindow(SW_HIDE);
}

void CMessageBoxCRC::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialog::OnShowWindow(bShow, nStatus);

	if(bShow)
	{
		if(m_AutoClose)
		{
			Delay(m_WaitTime);
			this->ShowWindow(SW_HIDE);
		}
	}
}

void CMessageBoxCRC::OnBnClickedBstMessageCancel()
{
	EndDialog(IDCANCEL);
}

void CMessageBoxCRC::OnBnClickedBstMessageRetry()
{
	EndDialog(IDRETRY);
}

void CMessageBoxCRC::OnBnClickedBstMessageContinue()
{
	EndDialog(IDCONTINUE);
}


void CMessageBoxCRC::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此加入您的訊息處理常式程式碼和 (或) 呼叫預設值

	CDialog::OnLButtonDown(nFlags, point);

	this->SendMessage(WM_NCLBUTTONDOWN,HTCAPTION);
}
