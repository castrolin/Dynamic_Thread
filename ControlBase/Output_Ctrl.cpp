// IOControl.cpp: implementation of the IOControl class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Output_Ctrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#pragma warning(disable : 4996)	// disable bogus deprecation warning

UINT COutputControl::LoopThread(LPVOID pParam)
{
	COutputControl* this_obj = (COutputControl*) pParam; 

	BOOL bLoop = TRUE ;
	bool bOn = false;

	while (bLoop)
	{
		if(WaitForSingleObject(g_hExit, 0) != WAIT_OBJECT_0)	//系統沒有退出時
		{
			
			if(WaitForSingleObject(this_obj->m_hLoopStart, 0) == WAIT_OBJECT_0)
			{
				try{

						Sleep(this_obj->m_dLoopInerval);

						bOn = !bOn;
						for(UINT x = 0; x < this_obj->m_OutputNum; x++)
						{
							if(this_obj->m_LoopFlag[x] == true)
								this_obj->m_Output_Array.at(x)->SetValue(bOn);
						}
					}
				catch(SYSTEM_ERROR &e)
				{
					e.SetLocation("LoopThread");
					return 0 ;

				}
				

			}
			Sleep(250);
		}
		
	}
	
	return 0 ;
}

COutputControl::COutputControl()
{

	m_ADO = new CADODatabase();

	m_LoopFlag = NULL;
	m_dLoopInerval = 1000;	//Led Buzzer間隔1秒

	m_tLoopThread = AfxBeginThread(LoopThread, (LPVOID)this, THREAD_PRIORITY_NORMAL, 0, CREATE_SUSPENDED);
	m_tLoopThread->m_bAutoDelete = FALSE;
	m_tLoopThread->ResumeThread();

	m_hLoopStart = CreateEvent(NULL, TRUE, FALSE, NULL);

}

COutputControl::~COutputControl()
{
	CloseHandle(m_hLoopStart);
}

//bool COutputControl::Initial_Info_Advantech_DAQ_Output(CIO_CentraCtrl_DAQ *IO_Ctrl)
//{
//	
//	CString csDBName,  sz;
//	std::vector< CString > m_Infos1, m_Infos2;
//
//	csDBName.Format("%s\\CtrlPrms\\%s", Project_Path, "ContrelSystem.mdb");
//
//	for(UINT x = 0; x <m_Output_Advantech_DAQ_Array.size(); x ++)
//	{
//		delete m_Output_Advantech_DAQ_Array.at(x);
//	}
//
//	m_Output_Advantech_DAQ_Array.clear();
//
//	m_Infos1.clear();
//
//	if( m_ADO->GetDataArray_Column("Output_Advantech_DAQ", "BitName", m_Infos1, csDBName) == false )
//		return false ;
//
//	m_OutputNum = m_Infos1.size();
//
//
//	for(UINT i=0; i<m_Infos1.size(); i++)
//	{	
//		CDigital_Output_Advantech_DAQ *Output = NULL;
//		Output = new CDigital_Output_Advantech_DAQ();
//
//		m_Infos2.clear();
//
//		if( m_ADO->GetDataArray_Row("Output_Advantech_DAQ", "BitName", m_Infos1.at(i), m_Infos2, csDBName ) != false )
//		{
//			OUTPUT_INFO_ADVANTECH_DAQ OutputInfoData;
//
//			//OutputInfoData.m_Devhand		= DevHandle;
//			OutputInfoData.bDummy			= IO_Ctrl->CheckDummy();
//			OutputInfoData.sBitName			= m_Infos2.at(0);
//			OutputInfoData.sCardName		= m_Infos2.at(1);
//			OutputInfoData.nBitIndex		= atoi(m_Infos2.at(2));
//			OutputInfoData.nPortID			= atoi(m_Infos2.at(3));
//			OutputInfoData.nCardID          = atoi(m_Infos2.at(4));
//
//			OutputInfoData.m_PanelInfo = IO_Ctrl->CreateInstanceCtrl_Output(OutputInfoData.sCardName, FormatString("%d", OutputInfoData.nCardID));
//
//			if(OutputInfoData.m_PanelInfo == NULL && OutputInfoData.bDummy == FALSE)
//			{
//				UINT nRet = _ALARM_PROC_ADVANTECH_DAQ_NOT_FOUND;
//				throw(SYSTEM_ERROR("CreateInstanceCtrl_Output",_MODULE_ERROR_ADVANTECH_DAQ, &nRet));
//				return false;
//			}
//
//			if( Output->InitialCtrlInfo(OutputInfoData) == false )
//				return false ;
//
//			m_Output_Advantech_DAQ_Array.push_back(Output);
//		}
//		
//	}
//	m_Output_Advantech_DAQ_Array.at(10);
//	
//	return (true) ;
//}

bool COutputControl::Initial_All_Output()
{

	//m_Output_Array.clear();

	//m_Output_Array.insert(m_Output_Array.end(),m_Output_Advantech_DAQ_Array.begin(),m_Output_Advantech_DAQ_Array.end());

	//m_OutputNum = m_Output_Array.size();

	//if(m_LoopFlag != NULL)
	//	delete []m_LoopFlag;

	//m_LoopFlag = new bool[m_OutputNum];

	//memset(m_LoopFlag, 0, sizeof(bool) * m_OutputNum);

	//SetEvent(m_hLoopStart);

	return false;
}

bool COutputControl::SetOutput( UINT nIndex , bool bOn)
{
	try
	{
		if(nIndex >= m_Output_Array.size())
			return false;

		m_LoopFlag[nIndex] = false; 

		m_Output_Array.at(nIndex)->SetValue(bOn);

		return true;
	}
	catch(SYSTEM_ERROR &e)
	{
		e.SetLocation("COutputControl::SetOutput");
		throw;
		return false;
	}

	return true;
}

bool COutputControl::GetOutput( UINT nIndex )
{
	try
	{
		if(nIndex >= m_Output_Array.size())
			return false;

		return m_Output_Array.at(nIndex)->GetValue();
	}
	catch(SYSTEM_ERROR &e)
	{
		e.SetLocation("COutputControl::GetOutput");
		throw;
		return false;
	}

	return true;
}

void COutputControl::SetLoop(UINT nIndex)
{
	if(nIndex >= m_Output_Array.size())
		return ;
	m_LoopFlag[nIndex] = true; 

}