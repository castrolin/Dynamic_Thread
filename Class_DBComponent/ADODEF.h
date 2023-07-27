#ifndef _ADODEF_H_
#define _ADODEF_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
#include <afx.h>
#include <afxdisp.h>
#include <math.h>
#include <icrsint.h>

#pragma warning (disable: 4146)

// ADO library needs to be used in the #import statement
#import "C:\Program Files\Common Files\System\ADO\msado15.dll" rename_namespace("ControlADO") rename("EOF", "EndOfFile")
using namespace ControlADO;

#define ChunkSize 100

struct CADOFieldInfo
{
	char m_strName[30]; 
	short m_nType;
	long m_lSize; 
	long m_lDefinedSize;
	long m_lAttributes;
	short m_nOrdinalPosition;
	BOOL m_bRequired;   
	BOOL m_bAllowZeroLength; 
	long m_lCollatingOrder;  

	CADOFieldInfo()
	{
		memset(m_strName , 0 , sizeof(m_strName)); 
		m_nType				= 0 ;
		m_lSize				= 0 ; 
		m_lDefinedSize		= 0 ;
		m_lAttributes		= 0 ;
		m_nOrdinalPosition	= 0 ;
		m_lCollatingOrder	= 0 ;  
		m_bRequired			= FALSE ;   
		m_bAllowZeroLength	= FALSE ; 
	};
};

CString IntToStr(int nVal);

CString LongToStr(long lVal);

CString ULongToStr(unsigned long ulVal);

CString DblToStr(double dblVal, int ndigits = 20);

CString DblToStr(float fltVal);

#endif//_ADODEF_H_