// dllmain.cpp : �w�q DLL ����l�Ʊ`���C
//

#include "stdafx.h"
#include <afxwin.h>
#include <afxdllx.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

static AFX_EXTENSION_MODULE LogsystemDLL = { NULL, NULL };

extern "C" int APIENTRY
DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
	// �p�G�z�ϥ� lpReserved�A�в����o��
	UNREFERENCED_PARAMETER(lpReserved);

	if (dwReason == DLL_PROCESS_ATTACH)
	{
		TRACE0("Logsystem.DLL ���b��l��!\n");
		
		// �X�R DLL ���@����l��
		if (!AfxInitExtensionModule(LogsystemDLL, hInstance))
			return 0;

		// �N�o�� DLL ���J�귽�쵲
		// �`�N: �p�G�o���X�R DLL �O��
		//  MFC �з� DLL (�Ҧp ActiveX ���)�A
		//  �ӫD MFC ���ε{���H���t�覡�s���A
		//  �бq DllMain �����o�@��A�åB�N��
		//  �m�J�q�o���X�R DLL �ҶץX����W�禡���C�ϥγo���X�R DLL ��
		//  �з� DLL ���ӴN�|���T�a�I�s����
		//  �禡�Ӫ�l�Ƴo���X�R DLL�C�_�h�A
		//  CDynLinkLibrary ����N���|���[��
		//  �з� DLL ���귽�쵲�A�P�ɷ|�y���Y����
		//  ���D�C

		new CDynLinkLibrary(LogsystemDLL);

	}
	else if (dwReason == DLL_PROCESS_DETACH)
	{
		TRACE0("Logsystem.DLL ���b�פ�!\n");

		// �I�s�Ѻc�禡�e���פ�{���w
		AfxTermExtensionModule(LogsystemDLL);
	}
	return 1;   // �T�w
}
