#pragma once

class CCardBase
{

public:
	//�Y�n�i���~�ӡA�����gLoadParam�i��C�@����ѼƳ]�w
	CCardBase();
	virtual ~CCardBase();

private:

public:
	virtual bool InitialCard() = 0;

	
};