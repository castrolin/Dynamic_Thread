#pragma once

#include "afxcmn.h"
#include "MAIN_Tab.h"


// CLogMainWindow ��ܤ��

class CLogMainWindow : public CDialog
{
	DECLARE_DYNAMIC(CLogMainWindow)

public:
	CMAIN_Tab m_Tab;

public:
	CLogMainWindow(CWnd* pParent = NULL);   // �зǫغc�禡
	virtual ~CLogMainWindow();

// ��ܤ�����
// 	enum { IDD = IDD_DIALOG_CONTAINER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �䴩

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
