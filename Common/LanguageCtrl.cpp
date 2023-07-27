#include "stdafx.h"
#include "LanguageCtrl.h"

CLanguageCtrl::CLanguageCtrl()
{
	TCHAR tcPath[MAX_PATH];
	TCHAR tcDriver[MAX_PATH];
	TCHAR tcDir[MAX_PATH];

	::GetModuleFileName(AfxGetInstanceHandle(), tcPath, MAX_PATH);
	_tsplitpath(tcPath, tcDriver, tcDir, NULL, NULL);
	m_Project_Path.Format("%s%s", tcDriver, tcDir);

	m_FileDocPath = m_Project_Path + "CtrlPrms\\Language\\";
}

CLanguageCtrl::~CLanguageCtrl()
{

}

std::vector<CString> CLanguageCtrl::GetInterfaceButtonNameList( CString DlgName, UINT nType )
{
	CString FileName;
	m_ButtonList.clear();

	switch(nType)
	{
	case SYSTEM_LANGUAGE_EN:
		FileName.Format("%s%s\\Button_EN.csv",m_FileDocPath ,DlgName);
		
		break;

	case SYSTEM_LANGUAGE_CN:
		FileName.Format("%s%s\\Button_CN.csv",m_FileDocPath ,DlgName);
		
		break;

	default:
		return m_ButtonList;
	}

	int NUM = 0;
	char p[512];
	CString ReadLine;

	std::fstream FileCtrl;

	FileCtrl.open(FileName,std::ios::in);


	if (FileCtrl.is_open())
	{
		while (!FileCtrl.eof())
		{
			FileCtrl.getline(p, 512);
			ReadLine.Format("%s",p);
			m_ButtonList.push_back(ReadLine);
		}
	}

	return m_ButtonList;
}

std::vector<CString> CLanguageCtrl::GetInterfaceStaticNameList( CString DlgName, UINT nType )
{
	CString FileName;
	m_StaticList.clear();

	switch(nType)
	{
	case SYSTEM_LANGUAGE_EN:
		FileName = m_FileDocPath + DlgName + "\\Static_EN.csv";
		break;

	case SYSTEM_LANGUAGE_CN:
		FileName = m_FileDocPath + DlgName + "\\Static_CN.csv";
		break;

	default:
		return m_ButtonList;
	}

	int NUM = 0;
	char p[512];
	CString ReadLine;

	std::fstream FileCtrl;

	FileCtrl.open(FileName,std::ios::in);


	if (FileCtrl.is_open())
	{
		while (!FileCtrl.eof())
		{
			FileCtrl.getline(p, 512);
			ReadLine.Format("%s",p);

			if(ReadLine.IsEmpty() == false)
				m_StaticList.push_back(ReadLine);
		}
	}
	return m_StaticList;
}
