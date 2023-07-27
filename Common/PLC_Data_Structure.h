#pragma once
#pragma pack(push, 1)

#include "CommonFunc.h"
#include "InlineMapEC.h"
#include "InlineMapED.h"
#include "InlineMapEG.h"
#include "InlineMapES.h"
#include "InlineMapEW.h"
#include "InlineMapHC.h"
#include "InlineMapHD.h"
#include "InlineMapHG.h"
#include "InlineMapLinkSignal_B.h"
#include "InlineMapLinkSignal_W.h"

//PLC Write Data Group
#define _PLC_WRITEYPE_ALL						0xFFFF			//16Bit
#define _PLC_WRITEYPE_HMI_SERVO					0x0001 << 0
#define _PLC_WRITEYPE_WORKTYPE					0x0001 << 1
#define _PLC_WRITEYPE_MACHINEPARAM				0x0001 << 2
#define _PLC_WRITEYPE_PROCESSPARAM				0x0001 << 3
#define _PLC_WRITEYPE_PROCESSFLOW				0x0001 << 4
#define _PLC_WRITEYPE_WORKTYPEFLOW				0x0001 << 5
#define _PLC_WRITEYPE_FUNCTION					0x0001 << 6

#pragma pack(pop)
#define _MODE_AUTO 2
#define _MODE_MANUAL 1

#define _STATUS_ERROR 2
#define _STATUS_NORMAL 1


struct HANDSHAKE_DATA_SECTION_PLC
{	
	//Word1
	UINT16 Start_REQ : 1;
	UINT16 End_ACK : 1;
	UINT16 Err_ACK : 1;
	UINT16 Spare1 : 13;

	//Word2
	UINT16 OUT_00 : 1;
	UINT16 OUT_01 : 1;
	UINT16 OUT_02 : 1;
	UINT16 OUT_03 : 1;
	UINT16 OUT_04 : 1;
	UINT16 OUT_05 : 1;
	UINT16 OUT_06 : 1;
	UINT16 OUT_07 : 1;
	UINT16 OUT_08 : 1;
	UINT16 OUT_09 : 1;
	UINT16 OUT_10 : 1;
	UINT16 OUT_11 : 1;
	UINT16 OUT_12 : 1;
	UINT16 OUT_13 : 1;
	UINT16 OUT_14 : 1;
	UINT16 OUT_15 : 1;

	UINT16 PARA_01;
	UINT16 PARA_02;
	UINT16 PARA_03;
	UINT16 PARA_04;
	UINT16 PARA_05;
	UINT16 PARA_06;
	UINT16 PARA_07;
	UINT16 PARA_08;

	HANDSHAKE_DATA_SECTION_PLC()
	{
		memset(this, 0, sizeof(HANDSHAKE_DATA_SECTION_PLC));
	}

	void Clear_Data()
	{
		memset(this, 0, sizeof(HANDSHAKE_DATA_SECTION_PLC));
	}

};

struct HANDSHAKE_DATA_SECTION_PC
{	
	//Word1
	UINT16 Start_ACK : 1;
	UINT16 End_REQ : 1;
	UINT16 Err_REQ : 1;
	UINT16 Buzzer_REQ : 1;
	UINT16 Spare1 : 12;

	//Word2
	UINT16 OUT_00 : 1;
	UINT16 OUT_01 : 1;
	UINT16 OUT_02 : 1;
	UINT16 OUT_03 : 1;
	UINT16 OUT_04 : 1;
	UINT16 OUT_05 : 1;
	UINT16 OUT_06 : 1;
	UINT16 OUT_07 : 1;
	UINT16 OUT_08 : 1;
	UINT16 OUT_09 : 1;
	UINT16 OUT_10 : 1;
	UINT16 OUT_11 : 1;
	UINT16 OUT_12 : 1;
	UINT16 OUT_13 : 1;
	UINT16 OUT_14 : 1;
	UINT16 OUT_15 : 1;

	UINT16 PARA_01;
	UINT16 PARA_02;
	UINT16 PARA_03;
	UINT16 PARA_04;
	UINT16 PARA_05;
	UINT16 PARA_06;
	UINT16 PARA_07;
	UINT16 PARA_08;

	HANDSHAKE_DATA_SECTION_PC()
	{
		memset(this, 0, sizeof(HANDSHAKE_DATA_SECTION_PC));
	}

	void Clear_Data()
	{
		memset(this, 0, sizeof(HANDSHAKE_DATA_SECTION_PLC));
	}
};

struct HANDSHAKE_DATA_PLC
{

	HANDSHAKE_DATA_SECTION_PLC HandShake_00;
	HANDSHAKE_DATA_SECTION_PLC HandShake_01;
	HANDSHAKE_DATA_SECTION_PLC HandShake_02;
	HANDSHAKE_DATA_SECTION_PLC HandShake_03;
	HANDSHAKE_DATA_SECTION_PLC HandShake_04;
	HANDSHAKE_DATA_SECTION_PLC HandShake_05;

	HANDSHAKE_DATA_PLC()
	{
		memset(this, 0, sizeof(HANDSHAKE_DATA_PLC));
	}


};


struct HANDSHAKE_DATA_PC
{

	HANDSHAKE_DATA_SECTION_PC HandShake_00;	//Recipe Change
	HANDSHAKE_DATA_SECTION_PC HandShake_01; //CCD Calibration
	HANDSHAKE_DATA_SECTION_PC HandShake_02; //CCD Align
	HANDSHAKE_DATA_SECTION_PC HandShake_03; //Sticker CCD Calibration
	HANDSHAKE_DATA_SECTION_PC HandShake_04; //Sticker CCD Calibration
	HANDSHAKE_DATA_SECTION_PC HandShake_05; //Sticker CCD Align

	HANDSHAKE_DATA_PC()
	{
		memset(this, 0, sizeof(HANDSHAKE_DATA_PC));
	}

	void Clear_Data()
	{
		HandShake_00.Clear_Data();
		HandShake_01.Clear_Data();
		HandShake_02.Clear_Data();
		HandShake_04.Clear_Data();
		HandShake_05.Clear_Data();
	}
};

struct STATUS_DATA_PLC
{
	UINT16 HeartBit;
	UINT16 Mode;
	UINT16 Status;
	UINT16 ErrorCode;
	UINT16 RecipeIndex;
	BYTE RecipeName[50];

	STATUS_DATA_PLC()
	{
		memset(this, 0, sizeof(STATUS_DATA_PLC));
	}
};

struct STATUS_DATA_PC
{

	UINT16 HeartBit;
	UINT16 Mode;
	UINT16 Status;
	UINT16 ErrorCode;
	UINT16 RecipeIndex;
	BYTE RecipeName[50];

	STATUS_DATA_PC()
	{
		memset(this, 0, sizeof(STATUS_DATA_PC));
	}
};


struct PLC_DATA_BIT_SECTION		//拿來存取PLC BIT 區 Raw Data
{
private:
	CString sDeviceName;
	UINT nDeviceStartIndex;
	UINT nSectionSize;
public:
	BYTE *bData;

	PLC_DATA_BIT_SECTION()
	{
		bData = NULL;
	}

	~PLC_DATA_BIT_SECTION()
	{
		delete []bData;
		bData = NULL;
	}

	void Initial(CString sName, UINT nDataStartIndex, UINT nDataSize)
	{
		_ASSERTE(nDataSize <= 900);

		sDeviceName = sName;
		nSectionSize = nDataSize; 
		bData = new BYTE[nSectionSize];
		memset(bData, 0, (sizeof(BYTE) / sizeof(char)) * nSectionSize);
		nDeviceStartIndex = nDataStartIndex;
	}

	void Initial(CString sName, UINT nDataStartIndex, BYTE *Data, UINT nDataSize)
	{
		_ASSERTE(nDataSize <= 900);

		sDeviceName = sName;
		nSectionSize = nDataSize; 
		bData = Data;
		nDeviceStartIndex = nDataStartIndex;
	}

	char GetDeviceName()
	{
		return *sDeviceName.GetBuffer(0);
	}

	UINT GetDeviceStartIndex()
	{
		return nDeviceStartIndex;
	}

	UINT GetSectionSize()
	{
		return nSectionSize;
	}

	bool GetBitData_BOOL(UINT nDataIndex)
	{
		UINT nDataLocation = nDataIndex - nDeviceStartIndex;
		_ASSERTE(nDataLocation < nSectionSize);
		bool bRet;
		if(bData[nDataLocation] == '1')
			bRet = true;
		else
			bRet = false;

		return bRet;
	}


	char GetBitData_CHAR(UINT nDataIndex)
	{
		UINT nDataLocation = nDataIndex - nDeviceStartIndex;
		_ASSERTE(nDataLocation < nSectionSize);
		return bData[nDataLocation];
	}

	void SetBitData(UINT nDataIndex, bool bStatus)
	{
		UINT nDataLocation = nDataIndex - nDeviceStartIndex;
		_ASSERTE(nDataLocation < nSectionSize);

		if(bStatus)
			bData[nDataLocation] = 1;
		else
			bData[nDataLocation] = 0;
	}


};

struct PLC_DATA_WORD_SECTION	//拿來存取PLC WORD 區 Raw Data
{
private:
	CString sDeviceName;
	UINT nDeviceStartIndex;
	UINT nSectionSize;
public:
	WORD *wData;

	PLC_DATA_WORD_SECTION()
	{
		wData = NULL;
	}

	~PLC_DATA_WORD_SECTION()
	{
		delete []wData;
		wData = NULL;
	}

	void Initial(CString sName, UINT nDataStartIndex, WORD *Data, UINT nDataSize)
	{
		_ASSERTE(nDataSize < 900);

		sDeviceName = sName;
		nSectionSize = nDataSize; 
		wData = Data;
		nDeviceStartIndex = nDataStartIndex;
	}

	void Initial(CString sName, UINT nDataStartIndex, UINT nDataSize)
	{
		_ASSERTE(nDataSize < 900);

		sDeviceName = sName;
		nSectionSize = nDataSize; 
		wData = new WORD[nDataSize];
		memset(wData, 0, (sizeof(WORD) / sizeof(char)) * nSectionSize);
		nDeviceStartIndex = nDataStartIndex;
	}

	char GetDeviceName()
	{
		return *sDeviceName.GetBuffer(0);
	}

	UINT GetDeviceStartIndex()
	{
		return nDeviceStartIndex;
	}

	UINT GetSectionSize()
	{
		return nSectionSize;
	}

	int GetIntData(UINT nDataIndex, bool bDoubleWord = false)
	{
		UINT nDataLocation = nDataIndex - nDeviceStartIndex;
		if(bDoubleWord)
		{
			_ASSERTE(nDataLocation + 1 < nSectionSize);
			int *nRet = NULL;

			nRet = (int*)&wData[nDataLocation + 0];
			return *nRet;

		}
		else
		{
			_ASSERTE(nDataLocation < nSectionSize);
			return wData[nDataLocation];
		}

	}

	void SetIntData(UINT nDataIndex, int nData, bool bDoubleWord = false)
	{
		UINT nDataLocation = nDataIndex - nDeviceStartIndex;
		if(bDoubleWord)
		{
			_ASSERTE(nDataLocation + 1 < nSectionSize);
			wData[nDataLocation + 0] = nData;
			wData[nDataLocation + 1] = nData >> 16;
		}
		else
		{
			_ASSERTE(nDataLocation < nSectionSize);
			wData[nDataLocation] = (short)nData;
		}

	}

	float GetFloatData(UINT nDataIndex)
	{
		UINT nDataLocation = nDataIndex - nDeviceStartIndex;
		_ASSERTE(nDataLocation + 1 < nSectionSize);

		float *nRet = NULL;

		nRet = (float*)&wData[nDataLocation + 0];
		return *nRet;
	}

	void SetFloatData(UINT nDataIndex, float fData)
	{
		UINT nDataLocation = nDataIndex - nDeviceStartIndex;

		_ASSERTE(nDataLocation + 1 < nSectionSize);
		memcpy(&wData[nDataLocation], &fData, sizeof(fData));
	}

	double GetDoubleData(UINT nDataIndex)
	{
		UINT nDataLocation = nDataIndex - nDeviceStartIndex;
		_ASSERTE(nDataLocation + 3 < nSectionSize);

		double *nRet = NULL;
		nRet = (double*)&wData[nDataLocation + 0];

		return *nRet;

	}

	void SetDoubleData(UINT nDataIndex, double fData)
	{
		UINT nDataLocation = nDataIndex - nDeviceStartIndex;
		_ASSERTE(nDataLocation + 3 < nSectionSize);
		memcpy(&wData[nDataLocation], &fData, sizeof(fData));
	}

	CString GetASCIIData(UINT nDataIndex, UINT nDeviceNum)
	{
		UINT nDataLocation = nDataIndex - nDeviceStartIndex;
		_ASSERTE(nDataLocation + nDeviceNum < nSectionSize);

		char *sData;
		sData = new char[nDeviceNum * 2];
		memcpy(sData, &wData[nDataLocation], nDeviceNum * 2);
		CString sRet;
		sRet.Format("%s", sData);
		sRet = sRet.Mid(0, nDeviceNum * 2);
		delete []sData;
		return sRet;

	}

	void SetASCIIData(UINT nDataIndex, CString sData)
	{
		UINT nDataLocation = nDataIndex - nDeviceStartIndex;
		_ASSERTE(nDataLocation + sData.GetLength() - 1 < nSectionSize);
		char *sCharData;

		sCharData = sData.GetBuffer(0);

		memcpy(&wData[nDataLocation], sCharData, sData.GetLength());
	}

	bool GetBitData(UINT nDataIndex, UINT nBitIndex)
	{
		UINT nDataLocation = nDataIndex - nDeviceStartIndex;
		_ASSERTE(nDataLocation < nSectionSize);
		_ASSERTE(nBitIndex < 16);

		WORD WordData = wData[nDataLocation];
		bool bBit;

		if((WordData & (1 << nBitIndex)) > 0)
			bBit = true;
		else
			bBit = false;

		return bBit;
	}

	void SetBitData(UINT nDataIndex, UINT nBitIndex, bool bStatus)
	{
		UINT nDataLocation = nDataIndex - nDeviceStartIndex;
		_ASSERTE(nDataLocation < nSectionSize);
		_ASSERTE(nBitIndex < 16);

		WORD WordData = wData[nDataLocation];

		if( bStatus == true )
			wData[nDataLocation] = WordData | ( 1 << nBitIndex ) ;	// 強制 On
		else
			wData[nDataLocation] = WordData & ~( 1 << nBitIndex ) ;	// 強制 Off

	}


};
