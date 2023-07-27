#pragma once

#include <Gdiplus.h>
#include "DiskObject.h"

class AFX_EXT_CLASS CStepProcess_Sticker
{
private:

public:
	CStepProcess_Sticker();
	~CStepProcess_Sticker();

private:

	double m_nImagePos_X;/////////////I->D
	double m_nImagePos_Y;/////////////I->D

	double m_nImagePosL_X;/////////////I->D
	double m_nImagePosL_Y;/////////////I->D
	double m_nImagePosR_X;/////////////I->D
	double m_nImagePosR_Y;/////////////I->D

	CString m_FilePath_Org;
	CString m_FilePath_Ret;

	BOOL m_bManualClickResultCompelete;


	UINT16 m_PLC_LastMode;

public:

	//CCD & Image Process

	BOOL Do_MarkSearch(CString PatternName, double &Pos_Xpixel, double &Pos_Ypixel, double &Score, BOOL bSavePic, FOV_ORG_TYPE nORG_Type);

	BOOL Do_MarkSearch(CString PatternName_L, CString PatternName_R, POINT_DATA_2F &Pos_L, POINT_DATA_2F &Pos_R, BOOL bSavePic, FOV_ORG_TYPE nORG_Type);

	BOOL Do_CCDAlign(POINT_DATA_2F &RetPoint_L, POINT_DATA_2F &RetPoint_R, double &Offset_X, double &Offset_Y, double &Offset_T, BOOL bSavePic);

	BOOL Do_WaitForRobotCalibrateSignal_ORG(DWORD Timeout);
	BOOL Do_WaitForRobotCalibrateSignal_DIS(DWORD Timeout);
	BOOL Do_WaitForRobotCalibrateSignal_ANGLE(DWORD Timeout);

	BOOL Do_ManualClickResultComplete();

	BOOL Proc_CCD_Calibrate();

	BOOL Proc_CCD_Align(double &dOffset_X, double &dOffset_Y, double &dOffset_T);

};
