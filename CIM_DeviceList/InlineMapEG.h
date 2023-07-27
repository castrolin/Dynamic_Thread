#pragma once
#pragma pack(push,1)
#include "CommonFunc.h"

/************************************************************************/
/* EG1NB. Equipment Glass data                                                                    */
/************************************************************************/
struct EG1ND_DATA
{

	UINT8 EventType_E:4;
	UINT16 EventType_Spare:12;

	UINT8 Date_Time_Hour;
	UINT8 Date_Time_Day;
	UINT8 Date_Time_Sec;
	UINT8 Date_Time_Min;

	UINT8 WorkID[18];

	UINT16 RecipeNo:10;
	UINT16 RecipeNo_Spare:6;

	UINT8 WorkAttribute1_T;
	UINT8 WorkAttribute1_p:4;
	UINT8 WorkAttribute1_c:1;
	UINT8 WorkAttribute1_w:1;
	UINT8 WorkAttribute1_Spare:2;


	UINT8 WorkAttribute2_y:1;
	UINT8 WorkAttribute2_x:1;
	UINT8 WorkAttribute2_d:1;
	UINT8 WorkAttribute2_Spare1:1;

	UINT8 WorkAttribute2_b:1;
	UINT8 WorkAttribute2_a:1;
	UINT8 WorkAttribute2_c:1;
	UINT8 WorkAttribute2_v:1;
	UINT8 WorkAttribute2_Spare2;

	UINT16 SpareData[3];

	UINT8 OperatorID[10];

	UINT16 EG1_Index;

	EG1ND_DATA()
	{
		memset(this, 0, sizeof(EG1ND_DATA));
	}
};

struct EG_SPARE
{
	UINT16 SpareData[8];

	EG_SPARE()
	{
		memset(this, 0, sizeof(EG_SPARE));
	}
};
#pragma pack(pop)