#pragma once
#pragma pack(push,1)
#include "CommonFunc.h"

struct CST_CTRL
{
	UINT8 InstructionCode:4;
	UINT8 InstructionCode_Spare:4;
};

/************************************************************************/
/* HC1NA. Work Count                                                                     */
/************************************************************************/
struct HC1NA_DATA
{
	//UINT16 BC_Ready;
	UINT16 BC_Ready:1;
	UINT16 BC_Ready_Spare:15;
	//-------------------------------
	//UINT16 TOD_Year_Month;
	UINT8 TOD_Month;
	UINT8 TOD_Year;
	//-------------------------------
	//UINT16 TOD_Day_Hour;
	UINT8 TOD_Hour;
	UINT8 TOD_Day;
	//-------------------------------
	//UINT16 TOD_Min_Sec;
	UINT8 TOD_Sec;
	UINT8 TOD_Min;
	//-------------------------------
	//UINT16 TOD_Day_of_Week;
	UINT16 TOD_Day_of_Week:4;
	UINT16 TOD_Day_of_Week_Spare:12;
	//-------------------------------
	UINT16 HC1_Index;

	HC1NA_DATA()
	{
		memset(this, 0, sizeof(HC1NA_DATA));
	}
};

/************************************************************************/
/*HC4NA : CIM Message                                                                      */
/************************************************************************/

struct HC4NA_DATA
{
	//UINT16 CIM_Message;
	UINT8 CIM_Message_s;
	UINT8 CIM_Message_c:2;
	UINT8 CIM_Message_n:6;

	UINT8 Message[80];

	UINT16 HC4_Index;

	HC4NA_DATA()
	{
		memset(this, 0, sizeof(HC4NA_DATA));
	}
};

/************************************************************************/
/* HC2NA. Recipe body data Control                                                                     */
/************************************************************************/
struct HC2NA_DATA
{
	UINT16 All_Line:1;
	UINT16 All_Line_Spare:15;

	UINT8 Tool_NodeNumber;
	UINT8 Tool_NodeNumber_Spare;

	UINT16 Recipe_Body_Data_p:10;
	UINT16 Recipe_Body_Data_Spare1:2;
	UINT16 Recipe_Body_Data_k:1;
	UINT16 Recipe_Body_Data_Spare2:3;
	//-------------------------------
	UINT16 Spare_16;
	//-------------------------------
	UINT16 HC2_Index;

	HC2NA_DATA()
	{
		memset(this, 0, sizeof(HC2NA_DATA));
	}
};

/************************************************************************/
/*HB. Stop Bit for Process EQ - Command in line                                                                      */
/************************************************************************/
struct HB1_DATA
{
	WORD_DATA StopBit[2];

	UINT16 SpareData;

	UINT16 HB1_Index;

	HB1_DATA()
	{
		memset(this, 0, sizeof(HB1_DATA));
	}
};

/************************************************************************/
/*HC. Spare                                                                      */
/************************************************************************/
struct HC_SPARE
{
	UINT16 SpareData[7];
	

	HC_SPARE()
	{
		 memset(this, 0, sizeof(HC_SPARE));
	}
};

/************************************************************************/
/* HC3NA. Equipment Control Data- Common in line                                                                     */
/************************************************************************/
struct HC3NA_DATA
{

	UINT8 EQ_Node;
	UINT8 EQ_Node_Spare;

	CST_CTRL CstCtrlData[6];

	UINT16 SpareData;

	UINT16 HC3_Index;
	
	HC3NA_DATA()
	{
		memset(this, 0, sizeof(HC3NA_DATA));
	}
};

#pragma pack(pop)