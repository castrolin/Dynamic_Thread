// ControlBase.h : ControlBase DLL ���D�n���Y��
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�� PCH �]�t���ɮ׫e���]�t 'stdafx.h'"
#endif

#include "resource.h"		// �D�n�Ÿ�


// CControlBaseApp
// �o�����O����@�аѾ\ ControlBase.cpp
//

class CControlBaseApp : public CWinApp
{
public:
	CControlBaseApp();

// �мg
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
