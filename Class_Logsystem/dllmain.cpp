// dllmain.cpp : 定義 DLL 的初始化常式。
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
	// 如果您使用 lpReserved，請移除這個
	UNREFERENCED_PARAMETER(lpReserved);

	if (dwReason == DLL_PROCESS_ATTACH)
	{
		TRACE0("Logsystem.DLL 正在初始化!\n");
		
		// 擴充 DLL 的一次初始化
		if (!AfxInitExtensionModule(LogsystemDLL, hInstance))
			return 0;

		// 將這個 DLL 插入資源鏈結
		// 注意: 如果這個擴充 DLL 是由
		//  MFC 標準 DLL (例如 ActiveX 控制項)，
		//  而非 MFC 應用程式以隱含方式連結，
		//  請從 DllMain 移除這一行，並且將它
		//  置入從這個擴充 DLL 所匯出的單獨函式中。使用這個擴充 DLL 的
		//  標準 DLL 應該就會明確地呼叫那個
		//  函式來初始化這個擴充 DLL。否則，
		//  CDynLinkLibrary 物件將不會附加到
		//  標準 DLL 的資源鏈結，同時會造成嚴重的
		//  問題。

		new CDynLinkLibrary(LogsystemDLL);

	}
	else if (dwReason == DLL_PROCESS_DETACH)
	{
		TRACE0("Logsystem.DLL 正在終止!\n");

		// 呼叫解構函式前先終止程式庫
		AfxTermExtensionModule(LogsystemDLL);
	}
	return 1;   // 確定
}
