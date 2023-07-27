
#include "stdafx.h"
#include "AlignmentProcess.h"

CAlignmentProcess::CAlignmentProcess(CString AlignmentName, BOOL bDistanceX)
{
	TCHAR tcPath[MAX_PATH];
	TCHAR tcDriver[MAX_PATH];
	TCHAR tcDir[MAX_PATH];
	::GetModuleFileName(AfxGetInstanceHandle(), tcPath, MAX_PATH);
	_tsplitpath(tcPath, tcDriver, tcDir, NULL, NULL);
	m_Project_Path.Format("%s%s", tcDriver, tcDir);

	m_AlignmentName = AlignmentName;
	m_bDistanceX = bDistanceX;
}

CAlignmentProcess::~CAlignmentProcess()
{

}

double CAlignmentProcess::AngTORad( double ANG )
{
	return (double)(ANG * 3.14159 / 180.0);
}

double CAlignmentProcess::RadTOAng( double Rad )
{
	return (double)(Rad * 180.0 / 3.14159);
}


double CAlignmentProcess::CCD_dT( double CCD_dX, double CCD_dY )
{
	double dCCD_dT = 0.0;

	if(m_bDistanceX)
		dCCD_dT = RadTOAng(atan(  CCD_dY /CCD_dX));	
	else
		dCCD_dT = RadTOAng(atan(  CCD_dX /CCD_dY));	

	return dCCD_dT;
}

double CAlignmentProcess::CDR_CNV( double T, double ORG_X, double ORG_Y, double &NEW_X, double &NEW_Y )
{
	double TempX, TempY;

	TempX = ORG_X * cos(AngTORad(T)) - ORG_Y * sin(AngTORad(T));
	TempY = ORG_X * sin(AngTORad(T)) + ORG_Y * cos(AngTORad(T));

	NEW_X = TempX;
	NEW_Y = TempY;

	return 0;
}

double CAlignmentProcess::W_CCD_dXY(double &dCCD_dX, double &dCCD_dY)
{
	W_CenterToMark(m_CalibrateData.dT, m_CCD_1_MarkToMark_dX, m_CCD_1_MarkToMark_dY, m_Mark_1_Cx, m_Mark_1_Cy);

	W_CenterToMark(m_CalibrateData.dT, m_CCD_2_MarkToMark_dX, m_CCD_2_MarkToMark_dY, m_Mark_2_Cx, m_Mark_2_Cy);

	dCCD_dX = m_CalibrateData.N_dX1 + m_Mark_2_Cx - m_Mark_1_Cx - m_CalibrateData.N_dX2;
	dCCD_dY = m_CalibrateData.N_dY1 + m_Mark_2_Cy - m_Mark_1_Cy - m_CalibrateData.N_dY2;

	return 0;
}

double CAlignmentProcess::W_RCenter( double &dW_RCenter_X, double &dW_RCenter_Y)
{
	dW_RCenter_X = m_CalibrateData.N_dX1 - m_Mark_1_Cx;
	dW_RCenter_Y = m_CalibrateData.N_dY1 - m_Mark_1_Cy;

	return 0;
}

double CAlignmentProcess::W_CenterToMark(double dT, double fMarkToMark_dX, double fMarkToMark_dY, double &fMark_Cx, double &fMark_Cy)
{
	double ALGN_1 = cos(AngTORad(dT))-1;
	double ALGN_2 = sin(AngTORad(dT));
	fMark_Cy = (fMarkToMark_dY - (fMarkToMark_dX * (ALGN_2/ALGN_1))) / ((ALGN_2 * (ALGN_2/ALGN_1)) + ALGN_1);
	fMark_Cx = (fMarkToMark_dY - (fMark_Cy * ALGN_1)) / ALGN_2;
	return 0;
}

double CAlignmentProcess::MarkToMark_Center( double Mark_1_dX, double Mark_1_dY, double Mark_2_dX, double Mark_2_dY, double &MarkToMark_Center_X, double &MarkToMark_Center_Y , double &MarkToMark_Center_T )
{
	MarkToMark_Center_X = (double)((m_CCD_dX + Mark_2_dX - Mark_1_dX) * 0.5 + Mark_1_dX);
	MarkToMark_Center_Y = (double)((m_CCD_dY + Mark_2_dY - Mark_1_dY) * 0.5 + Mark_1_dY);
	double MarkToMark_dX = m_CCD_dX + Mark_2_dX - Mark_1_dX;
	double MarkToMark_dY = m_CCD_dY + Mark_2_dY - Mark_1_dY;
	MarkToMark_Center_T = RadTOAng(atan(MarkToMark_dY / MarkToMark_dX));
	
	
	if(MarkToMark_dX < 0)
		MarkToMark_Center_T = MarkToMark_Center_T + 180;
	
	return 0;
}

bool CAlignmentProcess::Calibrate( CString ID,CP_CALIBRATE_DATA CalibrateData,double &CCD_1_dT_Out,double &CCD_2_dT_Out,double &W_RCenter_X_Out,double &W_RCenter_Y_Out,double &dCCD_dX,double &dCCD_dY ,double Move_Dis,double Tuen_Angle)
{

	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	CFileFind finder; 


	CString Machine_ParamFileName,FileDirectory;

	FileDirectory = FormatString("%s\\CtrlPrms\\%s\\", m_Project_Path, m_AlignmentName);

	if (!finder.FindFile(FileDirectory))
	{
		CreateDirectory(FileDirectory, NULL);
	}

	Machine_ParamFileName.Format("%s\\CtrlPrms\\%s\\%s.ini", m_Project_Path, m_AlignmentName, ID);



	m_CalibrateData = CalibrateData;

	m_CCD_1_MarkToMark_dX = m_CalibrateData.TN_dX1 - m_CalibrateData.N_dX1;
	m_CCD_1_MarkToMark_dY = m_CalibrateData.TN_dY1 - m_CalibrateData.N_dY1;

	m_CCD_2_MarkToMark_dX = m_CalibrateData.TN_dX2 - m_CalibrateData.N_dX2;
	m_CCD_2_MarkToMark_dY = m_CalibrateData.TN_dY2 - m_CalibrateData.N_dY2;

	m_CCD_1_Ang_dX = m_CalibrateData.Mst1_dX2 - m_CalibrateData.Mst1_dX1;
	m_CCD_1_Ang_dY = m_CalibrateData.Mst1_dY2 - m_CalibrateData.Mst1_dY1;

	m_CCD_2_Ang_dX = m_CalibrateData.Mst2_dX2 - m_CalibrateData.Mst2_dX1;
	m_CCD_2_Ang_dY = m_CalibrateData.Mst2_dY2 - m_CalibrateData.Mst2_dY1;


	m_CCD_1_dT = -1 * CCD_dT(m_CCD_1_Ang_dX, m_CCD_1_Ang_dY); //-1是為了把角度反向
	m_CCD_2_dT = -1 * CCD_dT(m_CCD_2_Ang_dX, m_CCD_2_Ang_dY);


	CDR_CNV(m_CCD_1_dT, m_CalibrateData.N_dX1, m_CalibrateData.N_dY1, m_CalibrateData.N_dX1,  m_CalibrateData.N_dY1); //把CCD看到的值轉為機構座標
	CDR_CNV(m_CCD_1_dT, m_CCD_1_MarkToMark_dX, m_CCD_1_MarkToMark_dY, m_CCD_1_MarkToMark_dX,  m_CCD_1_MarkToMark_dY);

	CDR_CNV(m_CCD_2_dT, m_CalibrateData.N_dX2, m_CalibrateData.N_dY2, m_CalibrateData.N_dX2,  m_CalibrateData.N_dY2); //把CCD看到的值轉為機構座標
	CDR_CNV(m_CCD_2_dT, m_CCD_2_MarkToMark_dX, m_CCD_2_MarkToMark_dY, m_CCD_2_MarkToMark_dX,  m_CCD_2_MarkToMark_dY);

	TRACE("CCD_1與世界座標角度差 %f\n", m_CCD_1_dT);
	TRACE("CCD_2與世界座標角度差 %f\n", m_CCD_2_dT);	
	TRACE("(N_dX1=%f, N_dY1=%f)\n", m_CalibrateData.N_dX1, m_CalibrateData.N_dY1);
	TRACE("(CCD_1_MarkToMark_dX=%f, CCD_1_MarkToMark_dY=%f)\n", m_CCD_1_MarkToMark_dX, m_CCD_1_MarkToMark_dY);
	TRACE("(N_dX2=%f, N_dY2=%f)\n", m_CalibrateData.N_dX2, m_CalibrateData.N_dY2);
	TRACE("(CCD_2_MarkToMark_dX=%f, CCD_2_MarkToMark_dY=%f)\n", m_CCD_2_MarkToMark_dX, m_CCD_2_MarkToMark_dY);	


	W_CCD_dXY(m_CCD_dX, m_CCD_dY);
	TRACE("CCD1&2距離(%f, %f)\n", m_CCD_dX, m_CCD_dY);
	dCCD_dX = m_CCD_dX;
	dCCD_dY = m_CCD_dY;
	W_RCenter(m_W_RCenter_X, m_W_RCenter_Y);
	TRACE("機構旋轉中心(%f, %f)\n", m_W_RCenter_X, m_W_RCenter_Y);
	CCD_1_dT_Out = m_CCD_1_dT;
	CCD_2_dT_Out = m_CCD_2_dT;
	W_RCenter_X_Out = m_W_RCenter_X;
	W_RCenter_Y_Out = m_W_RCenter_Y;


	L_Pixel =fabs(CalibrateData.Mst1_dY2-CalibrateData.Mst1_dY1) ;//Y平移左側PIXEL SIZE
	R_Pixel =fabs(CalibrateData.Mst2_dY2-CalibrateData.Mst2_dY1) ;//Y平移右側PIXEL SIZE

	L_PixelSize = Move_Dis*cos(abs(m_CCD_1_dT)*3.14159/180)/L_Pixel ;
	R_PixelSize = Move_Dis*cos(abs(m_CCD_1_dT)*3.14159/180)/R_Pixel ;



	::WritePrivateProfileString("Calibrate" , "CCD_1_dT" , FormatString("%.7lf", CCD_1_dT_Out), Machine_ParamFileName) ;
	::WritePrivateProfileString("Calibrate" , "CCD_2_dT" , FormatString("%.7lf", CCD_2_dT_Out), Machine_ParamFileName) ;
	::WritePrivateProfileString("Calibrate" , "W_RCenter_X" , FormatString("%.7lf", W_RCenter_X_Out), Machine_ParamFileName) ;
	::WritePrivateProfileString("Calibrate" , "W_RCenter_Y" , FormatString("%.7lf", W_RCenter_Y_Out), Machine_ParamFileName) ;
	::WritePrivateProfileString("Calibrate" , "CCD_dX" , FormatString("%.7lf", dCCD_dX), Machine_ParamFileName) ;
	::WritePrivateProfileString("Calibrate" , "CCD_dY" , FormatString("%.7lf", dCCD_dY), Machine_ParamFileName) ;
	::WritePrivateProfileString("Calibrate" , "L_PixelSize" , FormatString("%.7lf", L_PixelSize), Machine_ParamFileName) ;
	::WritePrivateProfileString("Calibrate" , "R_PixelSize" , FormatString("%.7lf", R_PixelSize), Machine_ParamFileName) ;

	LOG->Message_Warning(Log_Main, "CCD_1_dT = %.7lf", CCD_1_dT_Out);
	LOG->Message_Warning(Log_Main, "CCD_2_dT = %.7lf", CCD_2_dT_Out);
	LOG->Message_Warning(Log_Main, "W_RCenter_X = %.7lf", W_RCenter_X_Out);
	LOG->Message_Warning(Log_Main, "W_RCenter_Y = %.7lf", W_RCenter_Y_Out);
	LOG->Message_Warning(Log_Main, "CCD_dX = %.7lf", dCCD_dX);
	LOG->Message_Warning(Log_Main, "CCD_dY = %.7lf", dCCD_dY);
	LOG->Message_Warning(Log_Main, "L_PixelSize = %.7lf", L_PixelSize);
	LOG->Message_Warning(Log_Main, "R_PixelSize = %.7lf", R_PixelSize);

	return true;

}

bool CAlignmentProcess::Calibrate( CString ID,CP_CALIBRATE_DATA CalibrateData,double Move_Dis,double Tuen_Angle)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	CFileFind finder; 
	
	CString Machine_ParamFileName,FileDirectory;

	CalibrateData.dT=Tuen_Angle;

	FileDirectory = FormatString("%s\\CtrlPrms\\%s\\", m_Project_Path, m_AlignmentName);

	if (!finder.FindFile(FileDirectory))
	{
		CreateDirectory(FileDirectory, NULL);
	}

	Machine_ParamFileName.Format("%s\\CtrlPrms\\%s\\%s.ini", m_Project_Path, m_AlignmentName, ID);

	m_CalibrateData = CalibrateData;

	m_CCD_1_MarkToMark_dX = m_CalibrateData.TN_dX1 - m_CalibrateData.N_dX1;
	m_CCD_1_MarkToMark_dY = m_CalibrateData.TN_dY1 - m_CalibrateData.N_dY1;

	m_CCD_2_MarkToMark_dX = m_CalibrateData.TN_dX2 - m_CalibrateData.N_dX2;
	m_CCD_2_MarkToMark_dY = m_CalibrateData.TN_dY2 - m_CalibrateData.N_dY2;

	m_CCD_1_Ang_dX = m_CalibrateData.Mst1_dX2 - m_CalibrateData.Mst1_dX1;
	m_CCD_1_Ang_dY = m_CalibrateData.Mst1_dY2 - m_CalibrateData.Mst1_dY1;

	m_CCD_2_Ang_dX = m_CalibrateData.Mst2_dX2 - m_CalibrateData.Mst2_dX1;
	m_CCD_2_Ang_dY = m_CalibrateData.Mst2_dY2 - m_CalibrateData.Mst2_dY1;



	m_CCD_1_dT = -1 * CCD_dT(m_CCD_1_Ang_dX, m_CCD_1_Ang_dY); //-1是為了把角度反向
	m_CCD_2_dT = -1 * CCD_dT(m_CCD_2_Ang_dX, m_CCD_2_Ang_dY);


	CDR_CNV(m_CCD_1_dT, m_CalibrateData.N_dX1, m_CalibrateData.N_dY1, m_CalibrateData.N_dX1,  m_CalibrateData.N_dY1); //把CCD看到的值轉為機構座標
	CDR_CNV(m_CCD_1_dT, m_CCD_1_MarkToMark_dX, m_CCD_1_MarkToMark_dY, m_CCD_1_MarkToMark_dX,  m_CCD_1_MarkToMark_dY);

	CDR_CNV(m_CCD_2_dT, m_CalibrateData.N_dX2, m_CalibrateData.N_dY2, m_CalibrateData.N_dX2,  m_CalibrateData.N_dY2); //把CCD看到的值轉為機構座標
	CDR_CNV(m_CCD_2_dT, m_CCD_2_MarkToMark_dX, m_CCD_2_MarkToMark_dY, m_CCD_2_MarkToMark_dX,  m_CCD_2_MarkToMark_dY);

	TRACE("CCD_1與世界座標角度差 %f\n", m_CCD_1_dT);
	TRACE("CCD_2與世界座標角度差 %f\n", m_CCD_2_dT);	
	TRACE("(N_dX1=%f, N_dY1=%f)\n", m_CalibrateData.N_dX1, m_CalibrateData.N_dY1);
	TRACE("(CCD_1_MarkToMark_dX=%f, CCD_1_MarkToMark_dY=%f)\n", m_CCD_1_MarkToMark_dX, m_CCD_1_MarkToMark_dY);
	TRACE("(N_dX2=%f, N_dY2=%f)\n", m_CalibrateData.N_dX2, m_CalibrateData.N_dY2);
	TRACE("(CCD_2_MarkToMark_dX=%f, CCD_2_MarkToMark_dY=%f)\n", m_CCD_2_MarkToMark_dX, m_CCD_2_MarkToMark_dY);	


	W_CCD_dXY(m_CCD_dX, m_CCD_dY);
	TRACE("CCD1&2距離(%f, %f)\n", m_CCD_dX, m_CCD_dY);

	W_RCenter(m_W_RCenter_X, m_W_RCenter_Y);
	TRACE("機構旋轉中心(%f, %f)\n", m_W_RCenter_X, m_W_RCenter_Y);


	L_Pixel =fabs(CalibrateData.Mst1_dY2-CalibrateData.Mst1_dY1) ;//Y平移左側PIXEL SIZE
	R_Pixel =fabs(CalibrateData.Mst2_dY2-CalibrateData.Mst2_dY1) ;//Y平移右側PIXEL SIZE

	L_PixelSize = fabs(Move_Dis*cos(abs(m_CCD_1_dT)*3.14159/180))/L_Pixel ;
	R_PixelSize = fabs(Move_Dis*cos(abs(m_CCD_2_dT)*3.14159/180))/R_Pixel ;

	::WritePrivateProfileString("Calibrate" , "CCD_1_dT" , FormatString("%.7lf", m_CCD_1_dT), Machine_ParamFileName) ;
	::WritePrivateProfileString("Calibrate" , "CCD_2_dT" , FormatString("%.7lf", m_CCD_2_dT), Machine_ParamFileName) ;
	::WritePrivateProfileString("Calibrate" , "W_RCenter_X" , FormatString("%.7lf", m_W_RCenter_X), Machine_ParamFileName) ;
	::WritePrivateProfileString("Calibrate" , "W_RCenter_Y" , FormatString("%.7lf", m_W_RCenter_Y), Machine_ParamFileName) ;
	::WritePrivateProfileString("Calibrate" , "CCD_dX" , FormatString("%.7lf", m_CCD_dX), Machine_ParamFileName) ;
	::WritePrivateProfileString("Calibrate" , "CCD_dY" , FormatString("%.7lf", m_CCD_dY), Machine_ParamFileName) ;
	::WritePrivateProfileString("Calibrate" , "L_PixelSize" , FormatString("%.7lf", L_PixelSize), Machine_ParamFileName) ;
	::WritePrivateProfileString("Calibrate" , "R_PixelSize" , FormatString("%.7lf", R_PixelSize), Machine_ParamFileName) ;

	LOG->Message_Warning(Log_Main, "CCD_1_dT = %.7lf", m_CCD_1_dT);
	LOG->Message_Warning(Log_Main, "CCD_2_dT = %.7lf", m_CCD_2_dT);
	LOG->Message_Warning(Log_Main, "W_RCenter_X = %.7lf", m_W_RCenter_X);
	LOG->Message_Warning(Log_Main, "W_RCenter_Y = %.7lf", m_W_RCenter_Y);
	LOG->Message_Warning(Log_Main, "CCD_dX = %.7lf", m_CCD_dX);
	LOG->Message_Warning(Log_Main, "CCD_dY = %.7lf", m_CCD_dY);
	LOG->Message_Warning(Log_Main, "L_PixelSize = %.7lf", L_PixelSize);
	LOG->Message_Warning(Log_Main, "R_PixelSize = %.7lf", R_PixelSize);

	return true;
}

bool CAlignmentProcess::Alignment(CString ID,CP_ALIGNMENT_DATA AlignmentData, double &MotionMoveXYT_X, double &MotionMoveXYT_Y, double &MotionMoveXYT_T,double Addoffset_X,double Addoffset_Y,double Addoffset_T)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	CFileFind finder; 

	CString Machine_ParamFileName,FileDirectory;

	Machine_ParamFileName.Format("%s\\CtrlPrms\\%s\\%s.ini", m_Project_Path, m_AlignmentName, ID);


	if (!finder.FindFile(Machine_ParamFileName))
	{
		MotionMoveXYT_X = 0;
		MotionMoveXYT_Y = 0;
		MotionMoveXYT_T = 0;
		return false;
	}

	double CCD_1_dT= GetPrivateProfileDouble("Calibrate", "CCD_1_dT", 0.0, Machine_ParamFileName);
	double CCD_2_dT= GetPrivateProfileDouble("Calibrate", "CCD_2_dT", 0.0, Machine_ParamFileName);
	double W_RCenter_X= GetPrivateProfileDouble("Calibrate", "W_RCenter_X", 0.0, Machine_ParamFileName);
	double W_RCenter_Y= GetPrivateProfileDouble("Calibrate", "W_RCenter_Y", 0.0, Machine_ParamFileName);
	double CCD_dX = GetPrivateProfileDouble("Calibrate", "CCD_dX", 0.0, Machine_ParamFileName);
	double CCD_dY = GetPrivateProfileDouble("Calibrate", "CCD_dY", 0.0, Machine_ParamFileName);
	double L_PixelSize = GetPrivateProfileDouble("Calibrate", "L_PixelSize", 0.0, Machine_ParamFileName);
	double R_PixelSize = GetPrivateProfileDouble("Calibrate", "R_PixelSize", 0.0, Machine_ParamFileName);


	SetCalibrateData(CCD_1_dT,CCD_2_dT,W_RCenter_X,W_RCenter_Y,CCD_dX,CCD_dY);


	m_AlignmentData = AlignmentData;

	CDR_CNV(m_CCD_1_dT, m_AlignmentData.N_dX1, m_AlignmentData.N_dY1, m_AlignmentData.N_dX1,  m_AlignmentData.N_dY1); //把CCD看到的值轉為機構座標
	CDR_CNV(m_CCD_1_dT, m_AlignmentData.O_dX1, m_AlignmentData.O_dY1, m_AlignmentData.O_dX1,  m_AlignmentData.O_dY1);
	CDR_CNV(m_CCD_2_dT, m_AlignmentData.N_dX2, m_AlignmentData.N_dY2, m_AlignmentData.N_dX2,  m_AlignmentData.N_dY2); //把CCD看到的值轉為機構座標
	CDR_CNV(m_CCD_2_dT, m_AlignmentData.O_dX2, m_AlignmentData.O_dY2, m_AlignmentData.O_dX2,  m_AlignmentData.O_dY2);

	TRACE("NdX1, NdY1(%f, %f)\n", m_AlignmentData.N_dX1, m_AlignmentData.N_dY1);
	TRACE("OdX1, OdY1(%f, %f)\n", m_AlignmentData.O_dX1, m_AlignmentData.O_dY1);
	TRACE("(%f, %f)\n", m_CCD_1_MarkToMark_dX, m_CCD_1_MarkToMark_dY);
	TRACE(" NdX2, NdY2(%f, %f)\n", m_AlignmentData.N_dX2, m_AlignmentData.N_dY2);
	TRACE("OdX2, OdY2(%f, %f)\n", m_AlignmentData.O_dX2, m_AlignmentData.O_dY2);
	TRACE("(%f, %f)\n", m_CCD_2_MarkToMark_dX, m_CCD_2_MarkToMark_dY);	

	double MarkToMark_Center_NX, MarkToMark_Center_NY;
	double MarkToMark_Center_OX, MarkToMark_Center_OY;
	double MarkToMark_Center_NT, MarkToMark_Center_OT;

	MarkToMark_Center(m_AlignmentData.N_dX1, m_AlignmentData.N_dY1, m_AlignmentData.N_dX2, m_AlignmentData.N_dY2, MarkToMark_Center_NX, MarkToMark_Center_NY, MarkToMark_Center_NT);
	MarkToMark_Center(m_AlignmentData.O_dX1, m_AlignmentData.O_dY1, m_AlignmentData.O_dX2, m_AlignmentData.O_dY2, MarkToMark_Center_OX, MarkToMark_Center_OY, MarkToMark_Center_OT);

	TRACE("移動端mark的連線中心點座標 (%f, %f)\n",MarkToMark_Center_NX, MarkToMark_Center_NY);
	TRACE("固定端mark的連線中心點座標 (%f, %f)\n",MarkToMark_Center_OX, MarkToMark_Center_OY);
	TRACE("移動端mark的連線角度 %f\n",MarkToMark_Center_NT);
	TRACE("固定端mark的連線角度 %f\n",MarkToMark_Center_OT);

	double Mark_Center_dX = MarkToMark_Center_NX - MarkToMark_Center_OX; //平移X差
	double Mark_Center_dY = MarkToMark_Center_NY - MarkToMark_Center_OY; //平移Y差
	double Mark_Center_dT = (MarkToMark_Center_NT - MarkToMark_Center_OT) * -1; //角度差 


	//OFFSET補償值要加在這邊
	TRACE("mark連線中心點差值計算(平移) (%f, %f)\n",Mark_Center_dX, Mark_Center_dY);
	TRACE("mark連線角度差值計算 %f\n",Mark_Center_dT);

	double Mark_CenterToRCenter_dX;// = MarkToMark_Center_NX - W_RCenter_X; //mark連線中心點與旋轉中心差值X
	double Mark_CenterToRCenter_dY;// = MarkToMark_Center_NY - W_RCenter_Y; //mark連線中心點與旋轉中心差值Y
	Mark_Center_dT+=Addoffset_T;
	CDR_CNV(Mark_Center_dT, MarkToMark_Center_NX - m_W_RCenter_X, MarkToMark_Center_NY - m_W_RCenter_Y, Mark_CenterToRCenter_dX, Mark_CenterToRCenter_dY);

	Mark_CenterToRCenter_dX = Mark_CenterToRCenter_dX - (MarkToMark_Center_NX - m_W_RCenter_X);
	Mark_CenterToRCenter_dY = Mark_CenterToRCenter_dY - (MarkToMark_Center_NY - m_W_RCenter_Y);
	TRACE("mark連線中心點與旋轉中心差值旋轉產生的XY差值 (%f, %f)\n",Mark_CenterToRCenter_dX, Mark_CenterToRCenter_dY);

	MotionMoveXYT_T = Mark_Center_dT;
	MotionMoveXYT_X = -1 * (Mark_CenterToRCenter_dX + Mark_Center_dX);
	MotionMoveXYT_Y = -1 * (Mark_CenterToRCenter_dY + Mark_Center_dY);
	//XY平移補償

	MotionMoveXYT_X+=Addoffset_X;
	MotionMoveXYT_Y+=Addoffset_Y;
	TRACE("補償值(%f, %f, %f)\n",MotionMoveXYT_X, MotionMoveXYT_Y, MotionMoveXYT_T);



	return true;
}

void CAlignmentProcess::SetCalibrateData( double dCCD_1_dT,double dCCD_2_dT,double dW_RCenter_X,double dW_RCenter_Y, double dCCD_dX, double dCCD_dY )
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	m_CCD_1_dT = dCCD_1_dT;
	m_CCD_2_dT = dCCD_2_dT;
	m_W_RCenter_X = dW_RCenter_X;
	m_W_RCenter_Y = dW_RCenter_Y;
	m_CCD_dX = dCCD_dX;
	m_CCD_dY = dCCD_dY;
}

bool CAlignmentProcess::GetPixelSize( CString ID, double &dPixelSize )
{

	CFileFind finder; 
	
	CString Machine_ParamFileName;
	
	Machine_ParamFileName.Format("%s\\CtrlPrms\\%s\\%s.ini", m_Project_Path, m_AlignmentName, ID);

	if (!finder.FindFile(Machine_ParamFileName))
	{
		return false;
	}

	double L_PixelSize = GetPrivateProfileDouble("Calibrate", "L_PixelSize", 0.0, Machine_ParamFileName);
	double R_PixelSize = GetPrivateProfileDouble("Calibrate", "R_PixelSize", 0.0, Machine_ParamFileName);

	dPixelSize = (L_PixelSize + R_PixelSize) / 2.0;

	return true;
}

CString CAlignmentProcess::GetName()
{
	return m_AlignmentName;
}

