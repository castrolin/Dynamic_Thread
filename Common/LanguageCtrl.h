#pragma once
#include <stdarg.h>
#include <vector>
#include <fstream>

//LanguageType
#define SYSTEM_LANGUAGE_EN	0
#define SYSTEM_LANGUAGE_CN	1

class CLanguageCtrl
{
public:
	CLanguageCtrl();
	~CLanguageCtrl();


private:
	CString m_Project_Path;
	CString m_FileDocPath;

	std::vector<CString>m_ButtonList;
	std::vector<CString>m_StaticList;

public:
	std::vector<CString>GetInterfaceButtonNameList(CString DlgName, UINT nType);
	std::vector<CString>GetInterfaceStaticNameList(CString DlgName, UINT nType);

};