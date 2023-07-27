#pragma once
#include "DiskObject.h"


struct CP_CALIBRATE_DATA
{
	double Mst1_dX1, Mst1_dX2, Mst1_dY1, Mst1_dY2;
	double Mst2_dX1, Mst2_dX2, Mst2_dY1, Mst2_dY2;

	/*
	  命名規則
	  Msx_dXx
	    ↑------------CCD拍照點位左右邊
		    ↑------------目前動作(平移前、平移後 OR 旋轉前、旋轉後)
	*/

	/*
	Mst1_dX1:平移前拍照左邊點位X
	Mst1_dY1:平移前拍照左邊點位Y
	Mst2_dX1:平移前拍照右邊點位X
	Mst2_dY1:平移前拍照右邊點位Y


	Mst1_dX2::平移後拍照左邊點位X
	Mst1_dY2::平移後拍照左邊點位Y
	Mst2_dX2::平移後拍照右邊點位X
	Mst2_dY2::平移後拍照右邊點位Y

	*/


	double dT;	
	//校正時旋轉角度
	//dX"a"	a = CCD Index
	double N_dX1, N_dX2, N_dY1, N_dY2;

	double TN_dX1, TN_dX2, TN_dY1, TN_dY2;

	/*
	  命名規則
	  x_dXx
	  ↑------------動作(N：旋轉前；TN：旋轉後)
		  ↑------------CCD拍照點位左右邊
	*/


	/*
	N_dX1:旋轉前拍照左邊點位X
	N_dY1:旋轉前拍照左邊點位Y
	N_dX2:旋轉前拍照右邊點位X
	N_dY2:旋轉前拍照右邊點位Y

	TN_dX1:旋轉後拍照左邊點位X
	TN_dY1:旋轉後拍照左邊點位Y
	TN_dX2:旋轉後拍照右邊點位X
	TN_dY2:旋轉後拍照右邊點位Y
	*/
	CP_CALIBRATE_DATA()
	{
		memset(this, 0, sizeof(CP_CALIBRATE_DATA));
	}
};


struct CP_ALIGNMENT_DATA
{
	
	double O_dX1, O_dX2, O_dY1, O_dY2;
	double N_dX1, N_dX2, N_dY1, N_dY2;

	/*
	O_dX1: Golden Sample 左邊X點位
	O_dY1: Golden Sample 左邊X點位
	O_dX2: Golden Sample 右邊Y點位
	O_dY2: Golden Sample 右邊Y點位

	N_dX1: 入料左邊X點位
	N_dY1: 入料左邊Y點位
	N_dX2: 入料右邊X點位
	N_dY2: 入料右邊Y點位
	*/


	CP_ALIGNMENT_DATA()
	{
		memset(this, 0, sizeof(CP_ALIGNMENT_DATA));
	}
};

class AFX_EXT_CLASS CAlignmentProcess
{

public:
	CAlignmentProcess(CString AlignmentName, BOOL bDistanceX);
	~CAlignmentProcess();

private:
	CString m_Project_Path;
	CString m_AlignmentName;
	BOOL m_bDistanceX;


	double m_CCD_1_Ang_dX;
	double m_CCD_1_Ang_dY;
	double m_CCD_2_Ang_dX;
	double m_CCD_2_Ang_dY;	

	double m_CCD_1_MarkToMark_dX; 
	double m_CCD_1_MarkToMark_dY;
	double m_CCD_2_MarkToMark_dX;
	double m_CCD_2_MarkToMark_dY;

	double L_Pixel;
	double R_Pixel;

	double L_PixelSize;
	double R_PixelSize;




	double m_CCD_1_dT; 
	//CCD1與平台夾角
	double m_CCD_2_dT; 
	//CCD2與平台夾角

	double m_Mark_1_Cx, m_Mark_1_Cy;
	double m_Mark_2_Cx, m_Mark_2_Cy;

	double m_CCD_dX, m_CCD_dY; //二CCD距離

	double m_W_RCenter_X, m_W_RCenter_Y; //旋轉中心(機構座標系, 但原點為CCD1原點)

	double CCD_dT(double CCD_dX, double CCD_dY);
	double AngTORad(double ANG);
	double RadTOAng(double Rad);
	double CDR_CNV(double T, double ORG_X, double ORG_Y, double &NEW_X, double &NEW_Y);
	double W_CCD_dXY(double &CCD_dX, double &CCD_dY);
	double W_RCenter(double &W_RCenter_X, double &W_RCenter_Y);
	double W_CenterToMark(double dT, double MarkToMark_dX, double MarkToMark_dY, double &Mark_Cx, double &Mark_Cy);
	double MarkToMark_Center(double Mark_1_dX, double Mark_1_dY, double Mark_2_dX, double Mark_2_dY, double &MarkToMark_Center_X, double &MarkToMark_Center_Y , double &MarkToMark_Center_T);
	void SetCalibrateData(double dCCD_1_dT,double dCCD_2_dT,double dW_RCenter_X,double dW_RCenter_Y, double dCCD_dX, double dCCD_dY);




public:

	CP_CALIBRATE_DATA m_CalibrateData;
	CP_ALIGNMENT_DATA m_AlignmentData;

	bool Calibrate(CString ID, CP_CALIBRATE_DATA CalibrateData,double &CCD_1_dT_Out,double &CCD_2_dT_Out,double &W_RCenter_X_Out,double &W_RCenter_Y_Out,double &dCCD_dX,double &dCCD_dY,double Move_Dis,double Tuen_Angle);

	bool Calibrate(CString ID, CP_CALIBRATE_DATA CalibrateData,double Move_Dis,double Tuen_Angle);

	bool Alignment(CString ID, CP_ALIGNMENT_DATA AlignmentData, double &MotionMoveXYT_X, double &MotionMoveXYT_Y, double &MotionMoveXYT_TT,double Addoffset_X=0,double Addoffset_Y=0,double Addoffset_T=0);

	bool GetPixelSize(CString ID, double &dPixelSize);

	CString GetName();

};