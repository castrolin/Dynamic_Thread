// MaintainPageDlg.cpp : 實作檔
//

#include "stdafx.h"
#include "MaintainPageDlg.h"


// CMaintainPageDlg 對話方塊

IMPLEMENT_DYNAMIC(CMaintainPageDlg, CDialog)

CMaintainPageDlg::CMaintainPageDlg(CSystemParams *SystemParams, CWnd* pParent /*=NULL*/)
	: CDialog(CMaintainPageDlg::IDD, pParent)
{

	HINSTANCE ORG = AfxGetResourceHandle();
#ifdef _DEBUG
	HINSTANCE ControlBaseInstanceHandle = GetModuleHandle("..\\Debug\\ControlBase.dll");
#elif
	HINSTANCE ControlBaseInstanceHandle = GetModuleHandle("..\\Release\\ControlBase.dll");
#endif
	AfxSetResourceHandle(ControlBaseInstanceHandle);

	this->Create(IDD_DIALOG_OPTION_MAINTAIN, pParent);

	AfxSetResourceHandle(ORG);

	m_SystemParams = SystemParams;
	CTime time = CTime::GetCurrentTime();
	m_sTimeStr.Format("%04d/%02d/%02d/%02d:%02d", time.GetYear(), time.GetMonth(), time.GetDay(), time.GetHour(), time.GetMinute());

}

CMaintainPageDlg::~CMaintainPageDlg()
{
}

void CMaintainPageDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CMaintainPageDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_SHOWWINDOW()
	ON_BN_CLICKED(IDC_BUTTON_EXIT_OPTION_DLG, &CMaintainPageDlg::OnBnClickedButtonExitOptionDlg)
END_MESSAGE_MAP()


// CMaintainPageDlg 訊息處理常式

BOOL CMaintainPageDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	CRect FullScreenRect;
	FullScreenRect.top = 0;
	FullScreenRect.left = 0;

	FullScreenRect.right = GetSystemMetrics(SM_CXSCREEN);
	FullScreenRect.bottom = GetSystemMetrics(SM_CYSCREEN);

	this->MoveWindow(FullScreenRect);
	GetDlgItem(IDC_STATIC_MAINTAIN)->MoveWindow(FullScreenRect);
	return TRUE;
}


void CMaintainPageDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	
	CBitmap myBitmap;

	myBitmap.LoadBitmap(IDB_BITMAP_MAINTAIN);

	BITMAP bm;
	myBitmap.GetBitmap(&bm); // 計算圖形大小，並將結果存入 BITMAP 結構中

	int nBitmap_Width = bm.bmWidth;
	int nBitmap_Height = bm.bmHeight;

	CRect ImageRect;

	GetDlgItem(IDC_STATIC_MAINTAIN)->GetClientRect(ImageRect);

	CDC *pDC =  GetDlgItem(IDC_STATIC_MAINTAIN)->GetDC();

	CDC SourceDC;

	SourceDC.CreateCompatibleDC(pDC);
	CBitmap* pOldBitmap = SourceDC.SelectObject(&myBitmap);
	pDC->StretchBlt(0,0,  ImageRect.Width(), ImageRect.Height(), &SourceDC,0, 0, nBitmap_Width, nBitmap_Height, SRCCOPY );
	
	CFont font;
	VERIFY(font.CreateFont(60, 0, 0, 0, FW_BOLD, FALSE, FALSE, 0, 0, 0, 0, 0, 0, "微軟正黑體"));

	CFont* def_font;
	def_font = (CFont*)pDC->SelectObject( &font);

	SetTextColor(pDC->m_hDC, RGB(0, 0, 0));
	SetBkMode(pDC->m_hDC, TRANSPARENT);
	
	pDC->TextOutA(1220, 800, m_SystemParams->GetMachineID());

	pDC->TextOutA(1220, 850,m_sTimeStr);

	pDC->TextOutA(920, 980, m_SystemParams->GetMaintenanceEG_Name()+ "/" + m_SystemParams->GetMaintenanceEG_Phone());

	pDC->SelectObject(def_font);

	ReleaseDC(&SourceDC); 
	SourceDC.DeleteDC();
	font.DeleteObject(); 
	ReleaseDC(pDC);
}

BOOL CMaintainPageDlg::PreTranslateMessage( MSG* pMsg )
{
	if(pMsg->message==WM_KEYDOWN)
	{
		if(pMsg->wParam==VK_ESCAPE) 
		{
			pMsg->wParam=NULL;
		}
	}
	else if ( pMsg->message == WM_SYSKEYDOWN)
	{ 
		return TRUE;
	}

	return CDialog::PreTranslateMessage(pMsg);
}


void CMaintainPageDlg::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialog::OnShowWindow(bShow, nStatus);

	if(bShow)
	{
		GetDlgItem(IDC_STATIC_USER_NAME)->SetWindowText(ControlBase->GetOperatorName());
		LOG->Message_Warning(Log_Main, "Maintain window is Opened by %s", ControlBase->GetOperatorName());
	}
	else
	{
		LOG->Message_Warning(Log_Main, "Maintain window is Closed by %s", m_MaintainPageLevelCheckDlg.GetOperatorName());
	}
}

void CMaintainPageDlg::OnBnClickedButtonExitOptionDlg()
{
	HINSTANCE ORG = AfxGetResourceHandle();
#ifdef _DEBUG
	HINSTANCE ControlBaseInstanceHandle = GetModuleHandle("..\\Debug\\ControlBase.dll");
#elif
	HINSTANCE ControlBaseInstanceHandle = GetModuleHandle("..\\Release\\ControlBase.dll");
#endif
	AfxSetResourceHandle(ControlBaseInstanceHandle);


	if(m_MaintainPageLevelCheckDlg.DoModal() == IDOK)
	{
		if(m_MaintainPageLevelCheckDlg.GetAccessRet() > 0 && m_MaintainPageLevelCheckDlg.GetAccessClass() < 2)
		{
			CString UserID = m_MaintainPageLevelCheckDlg.GetOperatorName();
			AfxMessageBox(FormatString("User : %s is not Access Level to Modify Product Data", UserID));
			return;
		}
		else
		{
			this->ShowWindow(SW_HIDE);

			ShowSystemStatusDlg();
		}
		
	}
	
	AfxSetResourceHandle(ORG);

}
