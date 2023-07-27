#pragma once

class CCardBase
{

public:
	//若要進行繼承，須撰寫LoadParam進行每一元件參數設定
	CCardBase();
	virtual ~CCardBase();

private:

public:
	virtual bool InitialCard() = 0;

	
};