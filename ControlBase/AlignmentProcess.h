#pragma once
#include "DiskObject.h"


struct CP_CALIBRATE_DATA
{
	double Mst1_dX1, Mst1_dX2, Mst1_dY1, Mst1_dY2;
	double Mst2_dX1, Mst2_dX2, Mst2_dY1, Mst2_dY2;

	/*
	  �R�W�W�h
	  Msx_dXx
	    ��------------CCD����I�쥪�k��
		    ��------------�ثe�ʧ@(�����e�B������ OR ����e�B�����)
	*/

	/*
	Mst1_dX1:�����e��ӥ����I��X
	Mst1_dY1:�����e��ӥ����I��Y
	Mst2_dX1:�����e��ӥk���I��X
	Mst2_dY1:�����e��ӥk���I��Y


	Mst1_dX2::�������ӥ����I��X
	Mst1_dY2::�������ӥ����I��Y
	Mst2_dX2::�������ӥk���I��X
	Mst2_dY2::�������ӥk���I��Y

	*/


	double dT;	
	//�ե��ɱ��ਤ��
	//dX"a"	a = CCD Index
	double N_dX1, N_dX2, N_dY1, N_dY2;

	double TN_dX1, TN_dX2, TN_dY1, TN_dY2;

	/*
	  �R�W�W�h
	  x_dXx
	  ��------------�ʧ@(N�G����e�FTN�G�����)
		  ��------------CCD����I�쥪�k��
	*/


	/*
	N_dX1:����e��ӥ����I��X
	N_dY1:����e��ӥ����I��Y
	N_dX2:����e��ӥk���I��X
	N_dY2:����e��ӥk���I��Y

	TN_dX1:������ӥ����I��X
	TN_dY1:������ӥ����I��Y
	TN_dX2:������ӥk���I��X
	TN_dY2:������ӥk���I��Y
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
	O_dX1: Golden Sample ����X�I��
	O_dY1: Golden Sample ����X�I��
	O_dX2: Golden Sample �k��Y�I��
	O_dY2: Golden Sample �k��Y�I��

	N_dX1: �J�ƥ���X�I��
	N_dY1: �J�ƥ���Y�I��
	N_dX2: �J�ƥk��X�I��
	N_dY2: �J�ƥk��Y�I��
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
	//CCD1�P���x����
	double m_CCD_2_dT; 
	//CCD2�P���x����

	double m_Mark_1_Cx, m_Mark_1_Cy;
	double m_Mark_2_Cx, m_Mark_2_Cy;

	double m_CCD_dX, m_CCD_dY; //�GCCD�Z��

	double m_W_RCenter_X, m_W_RCenter_Y; //���त��(���c�y�Шt, �����I��CCD1���I)

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