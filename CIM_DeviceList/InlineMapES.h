#pragma once
#pragma pack(push,1)
#include "CommonFunc.h"

struct ALARM_STATUS
{
	UINT8 Unit;
	UINT8 StatusType:2;
	UINT8 StatusMode:1;
	UINT8 SpareData:5;
	
	UINT16 Code;
};

struct UNIT_STATUS_TACKTIME
{
	UINT8 Unit_TackTime:4;

	UINT8 SpareData1:4;

	UINT8 SignalTower_B:2;
	UINT8 SignalTower_G:2;
	UINT8 SignalTower_Y:2;
	UINT8 SignalTower_R:2;

	UINT16 TackTime:14;
	UINT16 nSpare:2;
};

/************************************************************************/
/* ES1NA_PLC_Status                                                                     */
/************************************************************************/
 struct ES1NA_DATA
{	
	UINT8 PLC_NodeID_n;
	UINT8 PLC_NodeID_l;
	
	ES1NA_DATA()
	{	
		memset(this, 0, sizeof(ES1NA_DATA));
	}
};


/************************************************************************/
/* ES2NA_Equipment_Status                                                                     */
/************************************************************************/

struct  ES2NA_DATA
{	
	UINT8 EQ_ID_n;
	UINT8 EQ_ID_Spare;

	UINT8 EQ_Status_u:1;
	UINT8 EQ_Status_y:1;
	UINT8 EQ_Status_i:1;
	UINT8 EQ_Status_a:1;
	UINT8 EQ_Status_s:1;
	UINT8 EQ_Status_r:1;
	UINT8 EQ_Status_Spare1:2;
	UINT8 EQ_Status_w:1;
	UINT8 EQ_Status_m:1;
	UINT8 EQ_Status_Spare2:2;
	UINT8 EQ_Status_f:1;
	UINT8 EQ_Status_d:1;
	UINT8 EQ_Status_Spare3:1;
	UINT8 EQ_Status_k:1;

	UINT16 Cur_Recipe_r:10;
	UINT8 Cur_Recipe_Spare:5;
	UINT8 Cur_Recipe_b:1;

	UINT8 Sampling_Rate_s;
	UINT8 Sampling_Rate_Spare:4;
	UINT8 Sampling_Rate_T:4;

	UINT16 ProcessType_n:10;
	UINT16 ProcessType_Spare:2;
	UINT16 ProcessType_c:2;
	UINT16 ProcessType_p:2;

	UINT8 RecipeID[16];

	UINT8 Signal_Tower_check_r:1;
	UINT8 Signal_Tower_check_P:1;
	UINT8 Signal_Tower_check_C:1;
	UINT8 Signal_Tower_check_V:1;
	UINT8 Signal_Tower_check_N:1;
	UINT8 Signal_Tower_check_D:1;
	UINT8 Signal_Tower_check_M:1;
	UINT8 Signal_Tower_check_spare:1;
	UINT8 Signal_Tower_check_BB:2;
	UINT8 Signal_Tower_check_GG:2;
	UINT8 Signal_Tower_check_YY:2;
	UINT8 Signal_Tower_check_RR:2;

	UINT16 ES2_Index;
//-------------------------------
 	ES2NA_DATA()
 	{
		memset(this, 0, sizeof(ES2NA_DATA));
 	}

};

/************************************************************************/
/* ES3NA.Alarm/Warning Status                                                                     */
/************************************************************************/

struct ES3NA_DATA
{	

	ALARM_STATUS AlarmStatus[6];

	UINT16 SpareData[2];

	//-------------------------------
	//CString ES3_Index_address;
	UINT16 ES3_Index;
	

	ES3NA_DATA()
	{
		memset(this, 0, sizeof(ES3NA_DATA));
	}
};

/************************************************************************/
/*ES4NA. Unit Status                                                                      */
/************************************************************************/

struct ES4NA_DATA
{
	
	UNIT_STATUS_TACKTIME UnitStatus[6];
	UINT16 nSpareData;
	UINT16 ES4_Index;



	ES4NA_DATA()
	{
		memset(this, 0, sizeof(ES4NA_DATA));
	}
};

/************************************************************************/
/*ES5NA. Spare status                                                                      */
/************************************************************************/

struct ES5NA_DATA
{

	UINT8 Unit_Mode_M;
	UINT8 Unit_Mode_Spare:4;

	UINT8 Unit_Mode_a:1;
	UINT8 Unit_Mode_s:1;
	UINT8 Unit_Mode_i:1;
	UINT8 Unit_Mode_b:1;
	
	UINT8 Robot_Status1:4;
	UINT8 Robot_Status2:4;
	UINT8 Robot_Status3:4;
	UINT8 Robot_Status4:4;
	
	UINT16 ES5_Index;

	ES5NA_DATA()
	{
		memset(this, 0, sizeof(ES5NA_DATA));
	}
};

/************************************************************************/
/*ES6NA. Equopment Safety Data Report                                                                      */
/************************************************************************/

struct ES6NA_DATA
{
	
	UINT16 FireStatus:4;
	UINT16 FireStatsStatus_Spare:12;

	UINT16 InterlockStatus:4;
	UINT16 InterlockStatus_Spare:12;

	UINT16 WaterLeakStatus:4;
	UINT16 WaterLeakStatus_Spare:12;

	
	UINT16 SpareData;

	UINT16 ES6_Index;

	ES6NA_DATA()
	{
		memset(this, 0, sizeof(ES6NA_DATA));
	}
};

#pragma pack(pop)