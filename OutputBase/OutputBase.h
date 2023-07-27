#pragma once

struct OUTPUT_INFO_BASE
{
	CString sCardName;
	CString sBitName;
	UINT nBitIndex;

	OUTPUT_INFO_BASE()
	{
		nBitIndex = 0;
	}
};

class COutputBase
{

public:
	//若要進行繼承，須撰寫LoadParam進行每一元件參數設定
	COutputBase();
	virtual ~COutputBase();

protected:

public:
	virtual bool GetValue(void) = 0;
	virtual bool SetValue(bool bOn) = 0;
	virtual CString GetOutputName() = 0;

};