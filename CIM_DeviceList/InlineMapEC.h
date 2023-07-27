#pragma once
#pragma pack(push,1)
#include "CommonFunc.h"

struct PORT_STATUS
{
	UINT8 Down			:1;
	UINT8 CST			:1;
	UINT8 Barcode		:1;
	UINT8 AGV_Mode		:1;
	UINT8 Unload_Comp	:1;
	UINT8 Unload_Req	:1;
	UINT8 Load_Comp		:1;
	UINT8 Load_Req		:1;
	UINT8 Status		:4;
	UINT8 Port_Mode		:4;
};

struct SLOT_WORK
{
	UINT8 SlotWork_s;
	UINT8 SlotWork_c:7;
	UINT8 SlotWork_F:1;

	UINT8 WorkAttribute_Q:1;
	UINT8 WorkAttribute_I:1;
	UINT8 WorkAttribute_Spare1:2;
	UINT8 WorkAttribute_b:2;
	UINT8 WorkAttribute_C:1;
	UINT8 WorkAttribute_R:1;
	UINT8 WorkAttribute_p:1;
	UINT8 WorkAttribute_g:1;
	UINT8 WorkAttribute_Spare2:2;
	UINT8 WorkAttribute_M:1;
	UINT8 WorkAttribute_L:1;
	UINT8 WorkAttribute_P:2;

	UINT8 WorkAttribute_LightGrade[2];
	UINT8 WorkAttribute_LostCode[4];


};

/************************************************************************/
/* EC1NA. Cassette Port Status                                                                    */
/************************************************************************/
struct EC1NA_DATA
{
	UINT8 CST_Setting_Code_1[4];
	UINT8 CST_Setting_Code_2[4];
	
	PORT_STATUS PortStatus[6];
	
	UINT16 PortWorkCount[6];
	
	UINT8 Unloader_sort_criteria_1:4;
	UINT8 Unloader_sort_criteria_2:4;
	UINT8 Unloader_sort_criteria_3:4;
	UINT8 Unloader_sort_criteria_4:4;
	UINT8 Unloader_sort_criteria_5:4;
	UINT8 Unloader_sort_criteria_6:4;
	UINT8 Unloader_sort_criteria_spare_8;
	//-------------------------------
	UINT16 EC1_Index;

	EC1NA_DATA()
	{
		memset(this,0,sizeof(EC1NA_DATA));
	}
};

/************************************************************************/
/* EC2NA. Load Cassette Data                                                                     */
/************************************************************************/

struct EC2NA_DATA
{
	//UINT16 Loaded_CST_Port;
	UINT16 Loaded_CST_p:4;
	UINT16 Loaded_CST_i:8;
	UINT16 Loaded_CST_f:4;
	//-------------------------------
	//UINT16 Date_Time;
	UINT8 Date_Time_Hour;
	UINT8 Date_Time_Day;
	UINT8 Date_Time_Sec;
	UINT8 Date_Time_Min;
	//-------------------------------
	char CST_ID[8];
	UINT16 CST_Map_Flag_e:1;
	UINT16 CST_Map_Flag_spare1:3;
	UINT16 CST_Map_Flag_w:1;
	UINT16 CST_Map_Flag_spare2:7;
	UINT16 CST_Map_Flag_p:1;
	UINT16 CST_Map_Flag_t:1;
	UINT16 CST_Map_Flag_spare3:1;
	UINT16 CST_Map_Flag_m:1;
	//-------------------------------

	WORD_DATA CST_Map[3];

	UINT16 EC2_Index;


	EC2NA_DATA()
	{
		memset(this,0,sizeof(EC2NA_DATA));
	}
};

/************************************************************************/
/* EC4NA. Load Cassette Data                                                                     */
/************************************************************************/

struct EC4NA_DATA
{
	//UINT16 Loaded_CST_Port;
	UINT8 PortIndex:4;
	UINT8 SortFlag:1;
	UINT8 SpareData1:2;
	UINT8 PortType:1;
	UINT8 WorkCount;

	UINT8 Date_Time_Hour;
	UINT8 Date_Time_Day;
	UINT8 Date_Time_Sec;
	UINT8 Date_Time_Min;

	UINT16 FinishCode;

	char CST_ID[8];

	UINT16 RejectReason:10;
	UINT8 SpareData2:2;
	UINT8 ForceStay:1;
	UINT8 RejectPort:1;
	UINT8 SpareData3:2;

	UINT8 SlotCount;
	UINT8 SpareData4;

	UINT16 EC4_Index;

	EC4NA_DATA()
	{
		memset(this,0,sizeof(EC4NA_DATA));
	}
};

/************************************************************************/
/* EC. Spare                                                                     */
/************************************************************************/
struct EC_SPARE
{
	UINT16 SpareData[8];

	EC_SPARE()
	{
		memset(this, 0, sizeof(EC_SPARE));
	}
};

#pragma pack(pop)