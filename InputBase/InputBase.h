#pragma once

struct INPUT_INFO_BASE
{
	CString sCardName;
	CString sBitName;
	UINT nBitIndex;
	BOOL nBitTypeA;

	INPUT_INFO_BASE()
	{
		nBitIndex = 0;
		nBitTypeA = TRUE;
	}
};

class CInputBase
{

public:
	//若要進行繼承，須撰寫LoadParam進行每一元件參數設定
	CInputBase();
	virtual ~CInputBase();

protected:
	CString m_sName;

public:
	virtual bool GetValue(bool bWait = false ,DWORD nTimeout=5000) = 0;
	virtual CString GetInputName() = 0;
};