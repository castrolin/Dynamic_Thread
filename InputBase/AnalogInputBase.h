#pragma once

struct ANALOG_INPUT_INFO_BASE
{
	CString sCardName;
	CString sBitName;
	UINT nBitIndex;

	ANALOG_INPUT_INFO_BASE()
	{
		nBitIndex = 0;
	}
};

class CAnalogInputBase
{

public:
	//若要進行繼承，須撰寫LoadParam進行每一元件參數設定
	CAnalogInputBase();
	virtual ~CAnalogInputBase();

protected:
	CString m_sName;

public:
	virtual bool GetValue(double &fValue) = 0;
	virtual CString GetInputName() = 0;
};