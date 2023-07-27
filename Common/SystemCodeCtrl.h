#pragma once

#include <stdarg.h>

#define _CODE_EN_	0
#define _CODE_CH_	1

#define _CODE_ALARM_	0
#define _CODE_WARNING_	1
#define _CODE_NORMAL_	2

class AFX_EXT_CLASS CSystemCodeCtrl
{
public:
	CSystemCodeCtrl();
	~CSystemCodeCtrl();

	void SetCodeLanguage(UINT nLanguageIndex);
	CString GetCode(UINT nCodeType, UINT nCodeIndex, ...);

private:
	CString Project_Path;
	UINT m_nLanguageIndex;
	CString m_CodeListPath_Alarm;
	CString m_CodeListPath_Warning;
	CString m_CodeListPath_Normal;
};