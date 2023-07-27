#pragma once
#pragma pack(push,1)
#include "CommonFunc.h"

/************************************************************************/
/*ED1NA. Work ID Data                                                                      */
/************************************************************************/
struct ED1NA_DATA
{
	UINT8 WorkID[18];
	
	UINT32 SpareData1;

	UINT8 InspectionResult:2;
	UINT8 WorkIDState:2;

	UINT8 SpareData2;
	
	UINT8 EventType:4;

	UINT16 ED1_Index;

	ED1NA_DATA()
	{
		memset(this, 0, sizeof(ED1NA_DATA));
	}
};


/************************************************************************/
/*ED2NA. EDC Data                                                                      */
/************************************************************************/

struct ED2NA_DATA
{
	//UINT16 Unit;
	UINT8 SpareData1;
	UINT8 SPC_Flag:1;
	UINT8 SpareData2:3;
	UINT8 EqUnitNo:4;

	//UINT16 Date_Time;
	UINT8 Date_Time_Hour;
	UINT8 Date_Time_Day;
	UINT8 Date_Time_Sec;
	UINT8 Date_Time_Min;

	//Work ID Data
	UINT8 WorkID[18];

	//Data
	UINT16 Data[30];

	UINT16 ED2_Index;

	ED2NA_DATA()
	{
		memset(this, 0, sizeof(ED2NA_DATA));
	}
};
/************************************************************************/
/* ED3NA. Recipe body                                                                     */
/************************************************************************/
struct ED3NA_DATA
{
	//UINT16 Data_type_EQ_status;
	UINT8 DataType_EqStatus_idle:1;
	UINT8 DataType_EqStatu_down:1;
	UINT8 DataType_EqStatu_run:1;
	UINT8 SpareData1:1;
	UINT8 SpareData2:1;
	UINT8 SpareData3:1;
	UINT8 SpareData4:1;
	UINT8 SpareData5:1;
	UINT8 SpareData6:4;
	UINT8 DataType_EqStatu_DataType:4;
	//-------------------------------

	//UINT16 Date_Time;
	UINT8 Date_Time_Hour;
	UINT8 Date_Time_Day;
	UINT8 Date_Time_Sec;
	UINT8 Date_Time_Min;

	//-------------------------------
	UINT16 RecipeNo;
	UINT8 RecipeID[16];

	UINT16 RecipeDate_Year;
	UINT8 RecipeDate_Day;
	UINT8 RecipeDate_Month;
	UINT8 RecipeDate_Min;
	UINT8 RecipeDate_Hour;
	UINT8 RecipeDate_Spare;
	UINT8 RecipeDate_Sec;

	UINT16 SpareData7[27];
	
	UINT16 ED3_Index;
	
	ED3NA_DATA()
	{
		memset(this, 0, sizeof(ED3NA_DATA));
	}
};


/************************************************************************/
/*ED7NA. Daily Check Data                                                                      */
/************************************************************************/
struct ED7NA_DATA
{
	//UINT16 Data_type_EQ_status;
	UINT8 Data_type_EQ_status_idle:1;
	UINT8 Data_type_EQ_status_down:1;
	UINT8 Data_type_EQ_status_run:1;

	UINT16 SpareData1:12;

	//UINT16 Date_Time;
	UINT8 Date_Time_Hour;
	UINT8 Date_Time_Day;
	UINT8 Date_Time_Sec;
	UINT8 Date_Time_Min;

	//機台參數
	UINT16 Data[30];

	ED7NA_DATA()
	{
		memset(this, 0, sizeof(ED7NA_DATA));
	}
};

/************************************************************************/
/*ED9NA. Recipe Body Modify Notice                                                                */
/************************************************************************/
struct ED9NA_DATA
{
	//UINT16 Data_type_EQ_status;
	UINT16 RecipeNo:10;
	UINT8 SpareData1:6;

	//UINT16 Date_Time;
	UINT8 Date_Time_Hour;
	UINT8 Date_Time_Day;
	UINT8 Date_Time_Sec;
	UINT8 Date_Time_Min;

	UINT8 OperatorID[12];

	UINT16 ED9_Index;

	ED9NA_DATA()
	{
		memset(this, 0, sizeof(ED9NA_DATA));
	}
};

#pragma pack(pop)