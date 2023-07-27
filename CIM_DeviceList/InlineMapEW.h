#pragma once
#pragma pack(push,1)
#include "CommonFunc.h"

/************************************************************************/
/* EW1NA. Work Count                                                                     */
/************************************************************************/

struct TRAN_DATA
{
	UINT16 SlotIndex:8;
	UINT16 PortIndex:4;
	UINT16 TransferType:4;

	char WorkID[18];

	UINT16 RecipeNo:10;
	UINT16 RecipeNo_Spare:6;


	UINT16 WorkAttribute1_Unloader_Sort_Criteria:4;
	UINT16 WorkAttribute1_SpareData1:4;
	UINT16 WorkAttribute1_LOI_Unit_Index:4;
	UINT16 WorkAttribute1_WorkType:1;
	UINT16 WorkAttribute1_CIM_Mode:1;
	UINT16 WorkAttribute1_SpareData2:1;
	UINT16 WorkAttribute1_ForceStay:1;

	UINT16 WorkAttribute2_BondingAOI_InspectRet:2;
	UINT16 WorkAttribute2_LOI_Non_InspectFlag:1;
	UINT16 WorkAttribute2_MES_LSRC_Skip_Flag:1;

	UINT16 WorkAttribute2_LOI_Judge_Flag:1;
	UINT16 WorkAttribute2_RTP_NG_Flag:1;
	UINT16 WorkAttribute2_From:2;


	UINT16 WorkAttribute2_PanelVerifyNG_Flag:1;
	UINT16 WorkAttribute2_PanelCut_Flag:1;
	UINT16 WorkAttribute2_PanelCutNG_Flag:1;
	UINT16 WorkAttribute2_LSRC_VCR_NG_Flag:1;

	UINT16 WorkAttribute2_LOI_MustCheck_Flag:1;
	UINT16 WorkAttribute2_RTP_SamplingFlag:1;
	UINT16 WorkAttribute2_Spare:2;

	char GRADE[2];

	char LoseCode[4];

	UINT16 WorkAttribute3_Spare:8;

	UINT16 WorkAttribute3_Disp_Finish:1;
	UINT16 WorkAttribute3_Disp_NG:1;
	UINT16 WorkAttribute3_Disp_Flag:1;
	UINT16 WorkAttribute3_SpareData:1;

	UINT16 WorkAttribute3_Cut_Finish:1;
	UINT16 WorkAttribute3_Cut_NG:1;
	UINT16 WorkAttribute3_Cut_Flag:1;
	UINT16 WorkAttribute3_Verify_NG:1;

};

struct REMOVE_DATA
{
	UINT8 TransType;
	UINT8 PortIndex:4;
	UINT8 TransfferedLocation_Spare:4;

	UINT8 WorkID[18];

	UINT16 RecipeNo:10;
	UINT8 RecipeNo_Spare:6;


	UINT8 WorkAttribute1_SlotIndex;
	UINT8 WorkAttribute1_PortIndex:4;
	UINT8 WorkAttribute1_WorkType:1;
	UINT8 WorkAttribute1_CIM_Mode:1;
	UINT8 WorkAttribute1_SpareData:2;


	UINT8 WorkAttribute2_Disp_Finish:1;
	UINT8 WorkAttribute2_Disp_NG:1;
	UINT8 WorkAttribute2_Disp_Flag:1;
	UINT8 WorkAttribute2_SpareData:1;

	UINT8 WorkAttribute2_Cut_Finish:1;
	UINT8 WorkAttribute2_Cut_NG:1;
	UINT8 WorkAttribute2_Cut_Flag:1;
	UINT8 WorkAttribute2_Verify_NG:1;

	UINT16 SpareData1;

	WORD_DATA EQ_Insp_Hist[2];

	UINT16 SpareData2;

};

struct CRITICAL_POS
{
	UINT8 WorkID_1[18];

	UINT8 PositionNumber_1;
	UINT8 ProcessStatus_1:4;
	UINT8 ProcessStatus_Spare1:4;

	UINT8 WorkID_Data_2[18];

	UINT8 PositionNumber_2;
	UINT8 ProcessStatus_2:4;
	UINT8 ProcessStatus_Spare2:4;

	UINT16 PositionStayTime:10;
	UINT16 PositionStayTime_Spare:6;

	UINT16 PositionTackTime:10;
	UINT16 PositionTackTime_Spare:6;

	UINT16 FDC_Value[2];

	UINT16 SpareData;

};

struct EW1NA_DATA
{
	UINT16 CF_Work_Count;

	UINT16 TFT_Work_Count;

	UINT16 Dummy_Work_Count;
	
	UINT16 Product_Work_Count;
	
	UINT16 SpareData;
	
	UINT16 EW1_Index;

	EW1NA_DATA()
	{
		memset(this, 0, sizeof(EW1NA_DATA));
	}
};

/************************************************************************/
/* EW2NB. Work Transfer                                                                     */
/************************************************************************/

struct EW2NA_DATA
{
	
	TRAN_DATA TransferData[4];

    UINT16 EW2_Index;


	EW2NA_DATA()
	{
		memset(this, 0, sizeof(EW2NA_DATA));
	}
};

/************************************************************************/
/* EW3NB_Work_Remove                                                                     */
/************************************************************************/


struct EW3NA_DATA
{
	REMOVE_DATA RemoveData;

	UINT16 EW3_Index;

	EW3NA_DATA()
	{
		memset(this, 0, sizeof(EW3NA_DATA));
	}
};

/************************************************************************/
/* EW5NA Criticall Position/FDC/Tack Time/Stay Time report                                                                    */
/************************************************************************/
struct EW5NA_DATA
{
	
	CRITICAL_POS CriticalPosData[15];

	UINT16 EW5_Index;

	EW5NA_DATA()
	{
		memset(this, 0, sizeof(EW5NA_DATA));
	}
};

#pragma pack(pop)