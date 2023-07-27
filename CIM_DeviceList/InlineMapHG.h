#pragma once
#pragma pack(push,1)
#include "CommonFunc.h"

/************************************************************************/
/* HG1NG-1. Host Glass data - Common in Line                                                                   */
/************************************************************************/

struct HG1NG_DATA
{
	//UINT16 Instruction_code;
	UINT16 Instruction_Code_c:4;
	UINT16 Instruction_Code_Spare:12;

	//UINT16 Event_Type;
	UINT16 Event_Type_E:4;
	UINT16 Event_Type_Spare:12;

	UINT8 Work_ID_Data[18];

	UINT16 RecipeNo:10;
	UINT16 RecipeNo_Spare:6;

	UINT16 WorkAttribute1_U:4;
	UINT16 WorkAttribute1_Spare1:4;
	UINT16 WorkAttribute1_p:4;
	UINT16 WorkAttribute1_c:1;
	UINT16 WorkAttribute1_w:1;
	UINT16 WorkAttribute1_Spare2:1;
	UINT16 WorkAttribute1_f:1;


	UINT8 WorkAttribute2_y:1;
	UINT8 WorkAttribute2_x:1;
	UINT8 WorkAttribute2_d:1;
	UINT8 WorkAttribute2_Spare1:1;

	UINT8 WorkAttribute2_b:1;
	UINT8 WorkAttribute2_a:1;
	UINT8 WorkAttribute2_c:1;
	UINT8 WorkAttribute2_v:1;
	UINT8 WorkAttribute2_Spare2;

	UINT16 SpareData[4];
	UINT16 HG1_Index;

	HG1NG_DATA()
	{
		memset(this, 0, sizeof(HG1NG_DATA));
	}
};

#pragma pack(pop)	