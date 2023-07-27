#pragma once

struct ANALOG_OUTPUT_INFO_BASE
{
	CString sCardName;
	CString sBitName;
	UINT nBitIndex;

	ANALOG_OUTPUT_INFO_BASE()
	{
		nBitIndex = 0;
	}
};

class CAnalogOutputBase
{

public:
	//若要進行繼承，須撰寫LoadParam進行每一元件參數設定
	CAnalogOutputBase();
	virtual ~CAnalogOutputBase();

protected:

public:
	virtual bool GetValue(double &fValue) = 0;
	virtual bool SetValue(float fValue) = 0;
	virtual CString GetOutputName() = 0;

};