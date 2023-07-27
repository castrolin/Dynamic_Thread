#pragma once

struct MOTOR_INFO_BASE
{
	CString sCardName;
	CString sMotorName;
	long nScale;

	MOTOR_INFO_BASE()
	{
		nScale = 0;
	}
};

class CMotorBase
{

public:
	//若要進行繼承，須撰寫LoadParam進行每一元件參數設定
	CMotorBase();
	CMotorBase(HANDLE hBreak, BOOL bSelfStop = TRUE);
	virtual ~CMotorBase();

protected:

	BOOL m_bDataLoaded;
	BOOL m_bInitialed;

	HANDLE m_hDead;
	HANDLE m_hBreak;

	CWinThread *m_MotorThd;
	static UINT MotorProc(LPVOID pObj);

	//Delay Function
	BOOL DoEvents();
	void Delay(DWORD Msecs);

public:
	//馬達資料初始化Flag
	bool IsMotorDataLoaded();

	virtual bool SetMotorSoftLimitEnable(BOOL bEnable) = 0;
	virtual bool SetMotorSoftLimit(double dLimit_P, double dLimit_N) = 0;
	
	//馬達操作
	virtual bool MotorResetAlarm() = 0;

	virtual bool MotorServoOn(bool bEnable) = 0;

	virtual bool MotorInitial(double Spd ,bool bWait = true, bool bBlockWaiting = false) = 0;

	//dPos(mm), dSpd(mm/s), dAcc(ms), dDec(ms)
	virtual bool MotorMoveAbs(double dPos, double dSpd, UINT nAcc, UINT nDec, bool bWait = true, bool bBlockWaiting = false) = 0;

	//dPos(mm), dSpd(mm/s), dAcc(ms), dDec(ms)
	virtual bool MotorMoveRel(double dDis, double dSpd, UINT nAcc, UINT nDec, bool bWait = true, bool bBlockWaiting = false) = 0;

	virtual bool MotoMoveWithGantry( UINT_PTR SlaveHANDLE ,double dPos, double dSpd, UINT nAcc, UINT nDec, SHORT RefSrc, bool Dir,bool bWait, bool bBlockWaiting)=0;
	
	virtual bool MotorJog(double dSpd, UINT nAcc, UINT nDec) = 0;

	virtual bool MotorStop(bool bWait = true, bool bBlockWaiting = false) = 0;

	virtual bool MotorJogStop(bool bWait = true, bool bBlockWaiting = false) = 0;

	virtual bool MotorWaitStop(bool bBlockWaiting) = 0;

	//馬達狀態

	virtual bool GetMotorPos_P(double &dPosP) = 0;

	virtual bool GetMotorPos_L(double &dPosL) = 0;

	virtual bool IsMotorServoOn() = 0;

	virtual bool IsMotorBusy() = 0;
	
	virtual bool IsMotorAlarm() = 0;
	
	virtual bool IsMotorInPos(double dPos, double dRange) = 0;
	
	virtual bool IsMotorInPEL() = 0;
	
	virtual bool IsMotorInNEL() = 0;
	
	virtual bool IsMotorInORG() = 0;

	virtual bool IsMotorInitialed() = 0;

	//馬達參數
	virtual CString GetMotorName() = 0;

	virtual long GetEncoderScale() = 0;

	virtual void SetInitialStatus(bool bInitialed) = 0;

	virtual bool MotorResetPos()=0;


};