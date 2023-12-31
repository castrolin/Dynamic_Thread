#pragma once

struct CAMERA_INFO_BASE
{
	

	CString sDeviceName;
	CString sIP;
	BOOL bDummyMode;
	BOOL bShowUint;
	BOOL bShowCross;
	BOOL bShowMeansureScale;
	BOOL bShowMousePoint;
	BOOL bShowRange;
	BOOL bStretch;
	BOOL bFlip_H;
	BOOL bFlip_V;

	int nRotateFlag;
	//ROTATE_90_CLOCKWISE = 0
	//ROTATE_180 = 1
	//ROTATE_90_COUNTERCLOCKWISE = 2

	CWnd *pShowUintDC;
	UINT nShowUnitWidth;
	UINT nShowUnitHeight;

	UINT nImageWidth;
	UINT nImageHeight;

	UINT nExposureTime;

	UINT nCameraFramerate;
	
	double dPixelSize_X;
	double dPixelSize_Y;


	CPoint RangeCenter;

	double dRange_X;
	double dRange_Y;


	CAMERA_INFO_BASE()
	{
		sDeviceName.Empty();

		bDummyMode = FALSE;

		bShowUint = FALSE;
		bShowCross = FALSE;
		bShowMeansureScale = FALSE;
		bShowMousePoint = FALSE;
		bStretch = FALSE;
		bShowRange = FALSE;

		pShowUintDC = NULL;

		bFlip_H = FALSE;
		bFlip_V = FALSE;

		nRotateFlag = -1;

		nShowUnitWidth = 0;
		nShowUnitHeight = 0;

		nImageWidth = 0;
		nImageHeight = 0;

		nExposureTime = 0;

		nCameraFramerate = 0;

		dPixelSize_X = 0.0;
		dPixelSize_Y = 0.0;

		dRange_X = 0;
		dRange_Y = 0;
	}
};

class CCameraBase
{

public:
	//若要進行繼承，須撰寫LoadParam進行每一元件參數設定
	CCameraBase();
	virtual ~CCameraBase();

protected:

	CString Project_Path;

	int m_nShowImageOrg_X;
	int m_nShowImageOrg_Y;

	CPoint m_MousePointMeansure_Down;
	CPoint m_MousePointMeansure_Up;

	CPoint m_MousePointDown_L;
	CPoint m_MousePointDown_R;

public:
	CAMERA_INFO_BASE m_Info;

	virtual bool CameraInitial(BOOL bDummyMode, double PixelSize_X, double PixelSize_Y) = 0;

	virtual bool SetExposureTimeRaw(UINT Value) = 0;
	virtual bool SetImageSize(UINT Width, UINT Height) = 0;
	virtual bool SetCameraFramerate(UINT nRate) = 0;

	virtual void SetShowUint(BOOL bEnable) = 0;
	virtual void SetShowCross(BOOL bEnable) = 0;
	virtual void SetMeansureMode(BOOL bEnable) = 0;
	virtual void SetShowRange(BOOL bEnable) = 0;
	virtual void SetMousePoint(BOOL bEnable) = 0;
	virtual void SetShowMode(BOOL bStretch) = 0;
	virtual void SetShowImageOrg_X(int nPos_X) = 0;
	virtual void SetShowImageOrg_Y(int nPos_Y) = 0;
	virtual void SetParentShowImageDC(CWnd *Parent) = 0;

	virtual bool OpenCamera() = 0;
	virtual bool CloseCamera() = 0;

	virtual bool GrabImageStart() = 0;
	virtual bool GrabImageStop() = 0;

	virtual bool SaveOriginalImage(CString OutputFileName) = 0;
	virtual bool SaveImageWithLabel(CString InputFileName, CString OutputFileName, CString Time, UINT X, UINT Y) = 0;

	virtual void SaveParameters() = 0;
	virtual void LoadParameters() = 0;

	virtual CString GetDeviceName() = 0;

	virtual BOOL GetFlip_H() = 0;
	virtual BOOL GetFlip_V() = 0;

	virtual UINT GetExposure() = 0;
	virtual UINT GetFrameRate() = 0;
	virtual UINT GetImageWidth() = 0;
	virtual UINT GetImageHeight() = 0;

	virtual bool IsCameraOpen() = 0;
	virtual bool IsCameraStart() = 0;

	virtual CPoint OnMouseBstDown_L(CPoint point) = 0;
	virtual CPoint OnMouseBstDown_R(CPoint point) = 0;

	virtual CPoint OnMouseBstUp_L(CPoint point) = 0;
	virtual CPoint OnMouseBstUp_R(CPoint point) = 0;

	virtual void ResetMouseHistory() = 0;
};