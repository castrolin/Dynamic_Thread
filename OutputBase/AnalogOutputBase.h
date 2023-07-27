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
	//�Y�n�i���~�ӡA�����gLoadParam�i��C�@����ѼƳ]�w
	CAnalogOutputBase();
	virtual ~CAnalogOutputBase();

protected:

public:
	virtual bool GetValue(double &fValue) = 0;
	virtual bool SetValue(float fValue) = 0;
	virtual CString GetOutputName() = 0;

};