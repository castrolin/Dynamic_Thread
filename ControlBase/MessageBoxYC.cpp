// MessageBoxYC.cpp : 實作檔
//

#include "stdafx.h"
#include "ControlBase.h"
#include "MessageBoxYC.h"
#include "afxdialogex.h"


// CMessageBoxYC 對話方塊

IMPLEMENT_DYNAMIC(CMessageBoxYC, CDialog)

CMessageBoxYC::CMessageBoxYC(CWnd* pParent /*=NULL*/)
	: CDialog(CMessageBoxYC::IDD, pParent)
{

}

CMessageBoxYC::~CMessageBoxYC()
{
}

void CMessageBoxYC::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_STATIC_MESSAGE_BOX_YC_GROUP, m_GroupBox);
}


BEGIN_MESSAGE_MAP(CMessageBoxYC, CDialog)
	ON_BN_CLICKED(IDC_BST_MESSAGE_YES, &CMessageBoxYC::OnBnClickedBstMessageYes)
	ON_BN_CLICKED(IDC_BST_MESSAGE_CANCEL, &CMessageBoxYC::OnBnClickedBstMessageCancel)
	ON_WM_SHOWWINDOW()
END_MESSAGE_MAP()




// CMessageBoxYC 訊息處理常式
BOOL CMessageBoxYC::OnInitDialog()
{
	CDialog::OnInitDialog();

	CFont * pFont = GetFont();
	LOGFONT lf;
	pFont->GetLogFont( &lf );
	lf.lfWeight = FW_BOLD;
	m_Font.CreateFontIndirect( &lf );

	SendMessageToDescendants( WM_SETFONT,
		(WPARAM) m_Font.m_hObject );

	m_GroupBox.SetXPGroupStyle(CXPGroupBox::XPGB_FRAME);
	m_GroupBox.SetBackgroundColor(RGB(180, 230, 30), ::GetSysColor(COLOR_BTNFACE));
	m_GroupBox.SetBorderColor(RGB(180, 230, 30));
	m_GroupBox.SetBorderWidth(5);

	m_GroupBox.SetFontBold(TRUE);
	m_GroupBox.SetAlignment(SS_CENTER);

	return TRUE;
}

BOOL CMessageBoxYC::PreTranslateMessage( MSG* pMsg )
{
	if(pMsg->message==WM_KEYDOWN && (pMsg->wParam==VK_ESCAPE || pMsg->wParam==VK_RETURN)) 
	{ 
		pMsg->wParam=NULL;                                  
	} 

	return CDialog::PreTranslateMessage(pMsg);
}

void CMessageBoxYC::OnBnClickedBstMessageYes()
{
	EndDialog(IDYES);
}


void CMessageBoxYC::OnBnClickedBstMessageCancel()
{
	EndDialog(IDCANCEL);
}

INT_PTR CMessageBoxYC::ShowMessageBox( CString CaptureText, CString Message )
{
	m_ShowTitle = CaptureText;
	m_sShowMsg = Message;

	INT_PTR nReturn = this->DoModal();

	return nReturn;
}


void CMessageBoxYC::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialog::OnShowWindow(bShow, nStatus);

	if(bShow)
	{	
		GetDlgItem(IDC_STATIC_MESSAGE_BOX_YC_GROUP)->SetWindowText(m_ShowTitle);
		GetDlgItem(IDC_STATIC_MESSAGE)->SetWindowText(m_sShowMsg);
	}
}
