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
	//�Y�n�i���~�ӡA�����gLoadParam�i��C�@����ѼƳ]�w
	CAnalogInputBase();
	virtual ~CAnalogInputBase();

protected:
	CString m_sName;

public:
	virtual bool GetValue(double &fValue) = 0;
	virtual CString GetInputName() = 0;
};