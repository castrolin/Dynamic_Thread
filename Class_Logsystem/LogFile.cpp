#include "stdafx.h"
#include "LogFile.h"

#pragma warning(disable : 4996)	// disable bogus deprecation warning
CLogFile::CLogFile()
{
	_m_pLogFile = NULL;
	_m_bOpen = false;
	_m_Filename = _T("");
	InitializeCriticalSection(&_m_CS);
}

CLogFile::~CLogFile()
{
	DeleteCriticalSection(&_m_CS);
	CloseFile();
}

bool CLogFile::OpenFile(CString csFile)
{
	CloseFile();
	_m_Filename = csFile;
	_m_pLogFile = fopen(_m_Filename, "a");
	if(_m_pLogFile == NULL)
	{
		_m_bOpen = false;
		return false;
	}
	_m_bOpen = true;

	return true;
}

void CLogFile::CloseFile()
{
	if(_m_pLogFile)
	{
		fclose(_m_pLogFile);
		_m_pLogFile = NULL;
		_m_bOpen = false;
	}
}

void CLogFile::Write(CString csMsg)
{
	if(_m_pLogFile == NULL)
	{
		return;
	}
	EnterCriticalSection(&_m_CS);
	fputs(csMsg, _m_pLogFile);
	fflush(_m_pLogFile);
	LeaveCriticalSection(&_m_CS);
}

long CLogFile::GetFileSize()
{
	fflush(_m_pLogFile);
	return ftell(_m_pLogFile);
}

bool CLogFile::CreateDirectory(CString csPath)
{
	LPCWSTR pwcStr = NULL;
	int nOK = 0;
	USES_CONVERSION; 
	pwcStr = A2CW((LPCSTR)csPath);
	nOK = SHCreateDirectory(NULL, pwcStr);
	if((nOK == ERROR_SUCCESS) || (nOK == ERROR_FILE_EXISTS) || (nOK == ERROR_ALREADY_EXISTS))
	{
		return true;
	}

	return false;
}

bool CLogFile::DirectoryExist(CString csPath)
{
	WIN32_FIND_DATA wfd;
	bool bValue = false;
	HANDLE hFind = FindFirstFile(csPath, &wfd);
	if((hFind != INVALID_HANDLE_VALUE) && (wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
	{
		bValue = true;
	}
	FindClose(hFind);
	return bValue;
}

bool CLogFile::FileExist(CString csFilename)
{
	CFileFind fFind;
	return (fFind.FindFile(csFilename) == TRUE ? true:false);
}
