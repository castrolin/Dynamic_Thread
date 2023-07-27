#pragma once
#pragma pack(push,1)
#include "CommonFunc.h"

/************************************************************************/
/* HD1NA. Un-loader Cassette Data                                                                     */
/************************************************************************/
struct SLOT_DATA
{
	UINT8 WorkID[18];
	UINT8 WorkAttribute_b:1;
	UINT8 WorkAttribute_a:1;
	UINT16 WorkAttribute_Spare:14;

	SLOT_DATA()
	{
		memset(this, 0, sizeof(SLOT_DATA));
	}
};

struct HD1NA_DATA
{
	//UINT16 Product_ID_Code;
	UINT16 ProductID_Code_p:10;
	UINT16 ProductID_Code_Spare:6;
	//-------------------------------
	//UINT16 CST_Seq;
	UINT8 CST_Seq_Spare1;
	UINT8 CST_Seq_d:4;
	UINT8 CST_Seq_Spare2:4;
	//-------------------------------
	//UINT16 Attribute;
	UINT8 Attribute_Spare1;
	UINT8 Attribute_Spare2:6;
	UINT8 Attribute_C:1;
	UINT8 Attribute_T:1;

	UINT8 CST_Count;
	UINT8 SpareData:4;
	UINT8 CST_Position:4;

	UINT8 CST_ID[8];

	UINT8 SlotCount;
	UINT8 SlotCount_Spare;

	UINT8 CST_SETTING[4];

	UINT8 UnloadSortCriteria_Spare:4;
	UINT8 UnloadSortCriteria:4;

	UINT8 Q_TQP_Flag_Spare1:3;
	UINT8 Q_TQP_Flag:1;
	UINT8 Q_TQP_Flag_Spare2:4;

	UINT16 HD1_Index;

	HD1NA_DATA()
	{
		memset(this, 0, sizeof(HD1NA_DATA));
	}
};

struct HD2NA_DATA
{
	UINT16 RepcipeNo:10;
	UINT8 RecipeNo_Spare:6;

	UINT8 WorkType_Spare1:8;
	UINT8 WorkType:4;
	UINT8 WorkType_Spare2:4;

	UINT16 Attribute_Spare:13;
	UINT8 Attribute_V:1;
	UINT8 Attribute_C:1;
	UINT8 Attribute_T:1;

	UINT8 CST_WorkCount;
	UINT8 LoadCSTPort_Spare:4;
	UINT8 LoadCSTPort:4;

	UINT8 SlotCount;
	UINT8 SlotCount_Spare;

	UINT8 CST_ID[8];

	UINT8 UnloaderSortCriteria_Spare:4;
	UINT8 UnloaderSortCriteria:4;
	UINT8 Q_TapFlag_Spare1:3;
	UINT8 Q_TapFlag:1;
	UINT8 Q_TapFlag_Spare2:4;

	SLOT_DATA SlotData[20];

	UINT16 HD2_Index;

	HD2NA_DATA()
	{
		memset(this, 0, sizeof(HD2NA_DATA));
	}
};

struct HD_SPAREDATA_1
{
	UINT16 SpareData[4];

	HD_SPAREDATA_1()
	{
		memset(this, 0, sizeof(HD_SPAREDATA_1));
	}
};

struct HD_SPAREDATA_2
{
	UINT16 SpareData[10];

	HD_SPAREDATA_2()
	{
		memset(this, 0, sizeof(HD_SPAREDATA_2));
	}
};

#pragma pack(pop)