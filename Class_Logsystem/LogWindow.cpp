// LogWindow.cpp : 實作檔
//

#include "stdafx.h"
#include ".\logwindow.h"
#include <math.h>


// CLogWindow 對話方塊

IMPLEMENT_DYNAMIC(CLogWindow, CDialog)
CLogWindow::CLogWindow(IN CString csLogName, IN CString csLogPath, CWnd* pParent /* = NULL */)
	: CDialog(/*CLogWindow::IDD, pParent*/)
{
	m_pList = NULL;
	_m_FileDay = 0;
	_m_LogName = csLogName;
	_m_LogPath = csLogPath;
	m_LogList.RemoveAll();
	const int FontSize = 100;		//FontSize 10
	m_Font.CreateFont(
		-(int)(fabs((double)FontSize*(double)GetDeviceCaps(::GetDC(this->m_hWnd),LOGPIXELSY)/72)/10.0+0.5),
		0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, DEFAULT_CHARSET, 0, 0, 0, 0, "Arial");
	m_bNoLog = false;
}

CLogWindow::~CLogWindow()
{
	m_Font.DeleteObject();
}

void CLogWindow::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CLogWindow, CDialog)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// CLogWindow 訊息處理常式

BOOL CLogWindow::OnInitDialog()
{
	CDialog::OnInitDialog();

	//Log ListBox
	m_pList->SetFont(&m_Font);
	m_pList->SetGutterWidth(18);
	m_pList->SetLineNoColor(RGB(255,255,255));
	m_pList->SetGutterColor(RGB(128,128,128));
	m_pList->EnableLineNumbers(TRUE, 19, 23);
	m_pList->SetContextMenuId(IDR_MENU_XLISTBOX);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX 屬性頁應傳回 FALSE
}

int CLogWindow::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;

	m_pList = new CXListBox();
	if(!m_pList->Create(LBS_OWNERDRAWFIXED | LBS_HASSTRINGS | LBS_NOINTEGRALHEIGHT 
		| LBS_EXTENDEDSEL | WS_VSCROLL | WS_HSCROLL | WS_TABSTOP, CRect(0,0, 10, 10), this, 3000))
	{
		return -1;
	}

	return 0;
}

void CLogWindow::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	CRect rect;
	this->GetClientRect(&rect);
	m_pList->SetWindowPos(&CWnd::wndTop, rect.left+2, rect.top+2, rect.Width()-2, rect.Height()-2, SWP_SHOWWINDOW);
}

void CLogWindow::OnDestroy()
{
	CDialog::OnDestroy();

	m_bNoLog = true;
	m_LogList.RemoveAll();
	if(m_pList)
	{
		if(m_pList->GetSafeHwnd())
		{
			m_pList->DestroyWindow();
		}
		delete m_pList;
		m_pList = NULL;
	}
}

BOOL CLogWindow::OnCommand(WPARAM wParam, LPARAM lParam)
{
	switch(wParam)
	{
	case WM_UPDATE_LOG:
		UpdateLog();
		break;
	}

	return CDialog::OnCommand(wParam, lParam);
}

void CLogWindow::UpdateLog()
{
	while(m_LogList.GetCount())
	{
		LogMsg logmsg;
		CString csMsg, csPath, csFilename;
		int nCurrentDay = 0;
		CTime ctTime = CTime::GetCurrentTime();

		CSingleLock slock(&m_CollectionLock);
		slock.Lock();
		logmsg = m_LogList.RemoveHead();
		slock.Unlock();
		nCurrentDay = ctTime.GetYear()*10000+ctTime.GetMonth()*100+ctTime.GetDay();
		csPath.Format("%s\\%04d%02d%02d", _m_LogPath, ctTime.GetYear(), ctTime.GetMonth(), ctTime.GetDay());
		csFilename.Format("%s\\%s.log", csPath, _m_LogName);
		if(_m_FileDay != nCurrentDay)
		{
			if(!_m_File.DirectoryExist(csPath))
			{
				_m_File.CreateDirectory(csPath);
			}
			if(_m_File.IsOpen())
			{
				_m_File.CloseFile();
			}
			_m_File.OpenFile(csFilename);
			_m_FileDay = nCurrentDay;
		}
		if(!_m_File.IsOpen())
		{
			_m_File.OpenFile(csFilename);
		}
		csMsg.Format("%s", logmsg.GetMessage());
		if(m_pList->GetSafeHwnd())
		{
			if(m_pList->GetCount() > 300)
			{
				m_pList->ResetContent();
			}
			if(logmsg.IsError())
			{
				m_pList->AddLine(CXListBox::White, CXListBox::Red, csMsg);
			}
			else if(logmsg.IsWarning())
			{
				m_pList->AddLine(CXListBox::Black, CXListBox::Yellow, csMsg);
			}
			else
			{
				m_pList->AddString(csMsg);
			}
		}
		_m_File.Write(csMsg+"\n");
	}
}

BOOL CLogWindow::PreTranslateMessage(MSG* pMsg)
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
