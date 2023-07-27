#pragma once
#include <algorithm> 
#include <vector>
#include "ADODatabase.h"
#include "OutputBase.h"
//#include "Digital_Output_Advantech_DAQ.h"


enum OutputMapping
{
	Y000_LED_RED			 = 0,
	Y001_LED_YELLOW			 = 1,
	Y002_LED_GREEN			 = 2,
	Y003_LED_BUZZER			 = 3,
	Y004_INTERLOCK_1		 = 4,
	Y005_INTERLOCK_2		 = 5,
	Y006_INTERLOCK_3		 = 6,
	Y007_INTERLOCK_4		 = 7,
	Y008					 = 8,
	Y009					 = 9,
	Y010					 = 10,
	Y011					 = 11,
	Y012_PCB_FORWAARD		 = 12,
	Y013_PCB_BACKWARD		 = 13,
	Y014_PCB_DOWN			 = 14,
	Y015_PCB_UP				 = 15,
	Y016					 = 16,
	Y017					 = 17,
	Y018					 = 18,
	Y019					 = 19,
	Y020					 = 20,
	Y021_REQ_CV_STOP		 = 21,
	Y022					 = 22,
	Y023					 = 23,
	Y024					 = 24,
	Y025_RB_READY			 = 25,
	Y026_RB_RUNNING			 = 26,
	Y027_RB_ERROR			 = 27,
	Y028_RB_SERROR			 = 28,
	Y029_RB_WARNING			 = 29,
	Y030_RB_PRG_ERR			 = 30,
	Y031_AUTO_MANUAL_KEY	 = 31,

};


class COutputControl
{

private:

	CADODatabase *m_ADO;

	//std::vector<CDigital_Output_Advantech_DAQ *> m_Output_Advantech_DAQ_Array;

	std::vector<COutputBase *> m_Output_Array;

	UINT m_OutputNum;
public:
	COutputControl();
	virtual ~COutputControl();

	//std::vector<CDigital_Output_Advantech_DAQ *>* GetOutputArrayPointer_Advantech_DAQ(){return &m_Output_Advantech_DAQ_Array;}

	std::vector<COutputBase *>* GetOutputArrayPointer(){return &m_Output_Array;}

	//bool Initial_Info_Advantech_DAQ_Output(CIO_CentraCtrl_DAQ *IO_Ctrl);

	bool Initial_All_Output();
public:

	//Thread 相關
	static		UINT LoopThread(LPVOID pParam); 
	CWinThread	*m_tLoopThread;
	HANDLE		m_hLoopStart;
	DWORD m_dLoopInerval;


	//變數相關
	bool *m_LoopFlag;


	//Function相關
	bool SetOutput(UINT nIndex, bool bOn);
	bool GetOutput(UINT nIndex);
	void SetLoop(UINT nIndex);
};
