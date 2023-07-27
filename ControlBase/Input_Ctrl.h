#pragma once
#include <algorithm> 
#include <vector>
#include "ADODatabase.h"
#include "InputBase.h"
//#include "Digital_Input_Advantech_DAQ.h"


enum InputMapping
{
	X000_AUTO_MANUAL_KEY	 = 0,
	X001_EMO_1				 = 1,
	X002_CDA_PS				 = 2,
	X003_VAC_PS				 = 3,
	X004_INTERLOCK_1		 = 4,
	X005_INTERLOCK_2		 = 5,
	X006_INTERLOCK_3		 = 6,
	X007_INTERLOCK_4		 = 7,
	X008					 = 8,
	X009					 = 9,
	X010					 = 10,
	X011					 = 11,
	X012_PCB_FORWAARD		 = 12,
	X013_PCB_BACKWARD		 = 13,
	X014_PCB_DOWN			 = 14,
	X015_PCB_UP				 = 15,
	X016_TAPE_EMPTY			 = 16,
	X017					 = 17,
	X018					 = 18,
	X019					 = 19,
	X020					 = 20,
	X021_CV_EMPTY			 = 21,
	X022					 = 22,
	X023					 = 23,
	X024					 = 24,
	X025_RB_READY			 = 25,
	X026_RB_VAC				 = 26,
	X027_RB_ERROR			 = 27,
	X028_RB_SERROR			 = 28,
	X029_RB_WARNING			 = 29,
	X030_RB_PRG_ERR			 = 30,
	X031_AUTO_MANUAL_KEY	 = 31,


};


class CInputControl
{
private:
	CADODatabase *m_ADO;

	//std::vector<CDigital_Input_Advantech_DAQ *> m_Input_Advantech_DAQ_Array;
	std::vector<CInputBase *> m_Input_Array;



	//std::vector<ADVANTECH_DI_CONTROL> m_DigInputObj;
	
public:

	CInputControl();
	virtual ~CInputControl();

	//std::vector<CDigital_Input_Advantech_DAQ *>* GetInputArrayPointer_Advantech_DAQ(){return &m_Input_Advantech_DAQ_Array;}
	std::vector<CInputBase *>* GetInputArrayPointer(){return &m_Input_Array;}

	//bool Initial_Info_Advantech_DAQ_Input(CIO_CentraCtrl_DAQ *IO_Ctrl);

	bool Initial_All_Input();


	//各IO控制功能
	bool GetInput(UINT nIndex,bool bWait = false ,DWORD nTimeout=5000);
	
};