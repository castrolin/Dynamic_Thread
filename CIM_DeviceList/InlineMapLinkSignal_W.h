#pragma once
#pragma pack(push,1)
#include "CommonFunc.h"


struct INLINE_STREAM_DATA
{

	UINT8 WorkSlotIndex;
	UINT8 WorkCSTIndex:7;
	UINT8 WorkCIMFlag:1;

	UINT8 PanelType[3];

	UINT16 PanelID:10;
	UINT8 PanelCount:6;

	UINT8 WorkType:4;
	UINT8 GroupNo:4;
	UINT8 CF_TFT_Flag:1;
	UINT8 InspectionFlag:1;
	UINT8 RejectFlag:1;
	UINT8 CSTModeFlag:1;
	UINT8 OverQ_TimeFlag:1;
	UINT8 NO_VCRFlag:1;
	UINT8 GlassSize:1;
	UINT8 LineNumber:1;

	UINT8 UnloaderSortingCriteria:4;
	UINT16 UnloaderSortingCriteria_Spare:12;

	UINT16 SpareData[9];

	INLINE_STREAM_DATA()
	{
		memset(this, 0, sizeof(INLINE_STREAM_DATA));
	}
};

#pragma pack(pop)	